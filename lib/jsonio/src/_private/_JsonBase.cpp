/**
 * @file _JsonBase.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_JsonBase.hpp"
#include "_private/_syntax.hpp"
#include "_private/_lexing/_types.hpp"
#include "_private/_lexing/_lexing.hpp"
#include "_private/_parsing/_parsing.hpp"
#include "_private/_error/_Errors.hpp"
#include "_private/_JsonValue.hpp"

#include <fs/InFile.hpp>
#include <fs/OutFile.hpp>
#include <logger/logger.hpp>

#include <iostream>
#include <stdexcept>

#define _N_TAB(N) (std::string((N) * 4, ' '))

namespace jsonio {
    namespace _private {
        _JsonBase::_JsonBase(void) :
        __rootValue(std::nullopt),
        __filePath()
        {}

        // Public :
        Status _JsonBase::parse(const fs::Path &path) {
            try {
                this->__filePath = path;
                _lexing::_types::_Tokens_t tokens = _lexing::_processLexing(path);
                std::size_t index{0};
                this->__rootValue = std::make_unique<_JsonValue>(_parsing::_processParsing(tokens.at(0), tokens, index));
                return Status::OK;
            } catch (const error::Base &e) {
                e.log();
                if (dynamic_cast<const _error::_Parsing*>(&e)) return Status::E_PARSING; //TODO : create a ERROR_IS_OF_TYPE marcro instead ?
                if (dynamic_cast<const _error::_Type*>(&e)) return Status::E_TYPE;
                if (dynamic_cast<const _error::_Key*>(&e)) return Status::E_KEY;
                if (dynamic_cast<const _error::_Index*>(&e)) return Status::E_INDEX;
                if (dynamic_cast<const _error::_File*>(&e)) return Status::E_FILE;
                if (dynamic_cast<const _error::_NotLoaded*>(&e)) return Status::E_NOT_LOADED;
            } catch (...) {
                return Status::E_NOK;
            }
            return Status::E_NOK;
        }

        
        types::ValueTypes _JsonBase::getType(
            const std::string &jsonPath,
            const std::array<std::string, 3> &separators
        ) const {
            const _private::_JsonValueTypes jsonValueType = this->_getJsonValueFromPath(jsonPath, separators)->getType();
            
            switch (jsonValueType) {
                case _private::_JsonValueTypes::_STRING :
                    return types::ValueTypes::STRING;
                case _private::_JsonValueTypes::_INT:
                    return types::ValueTypes::INT_NUM;
                case _private::_JsonValueTypes::_FLOAT:
                    return types::ValueTypes::FLOAT_NUM;
                case _private::_JsonValueTypes::_BOOL:
                    return types::ValueTypes::BOOL;
                case _private::_JsonValueTypes::_JSON_NULL:
                    return types::ValueTypes::NULL_VALUE;
                case _private::_JsonValueTypes::_OBJECT:
                    return types::ValueTypes::OBJECT;
                case _private::_JsonValueTypes::_ARRAY:
                    return types::ValueTypes::ARRAY;
                default:
                    return types::ValueTypes::UNKNOWN;
                }                
        }

        template <typename T>
        requires is_in_variant_v<T, types::Any_t>
        std::optional<T> _JsonBase::get(
            const std::string &jsonPath,
            const std::array<std::string, 3> &separators
        ) const {
            std::shared_ptr<_private::_JsonValue> jsonValue = _getJsonValueFromPath(jsonPath, separators);
            if constexpr (!std::is_same_v<T, types::Object_t> && !std::is_same_v<T, types::Array_t>)
            {
                std::optional<T> res{};
                _private::_parsing::_types::_Any_t resAnyValue = jsonValue->getValue();
                T *resPtr = std::get_if<T>(&resAnyValue);
                if (resPtr != nullptr) {
                    res.emplace(*resPtr);
                }
                return res;
            }
            if constexpr (std::is_same_v<T, types::Object_t>) return types::Object_t(*jsonValue);
            if constexpr (std::is_same_v<T, types::Array_t>) return types::Array_t(*jsonValue);
        }

        #define instantiate_jsonbase_get_template_method(TYPE)\
            template std::optional<TYPE> _JsonBase::get(const std::string &, const std::array<std::string, 3> &) const;

            instantiate_jsonbase_get_template_method(types::String_t)
            instantiate_jsonbase_get_template_method(types::IntNum_t)
            instantiate_jsonbase_get_template_method(types::FloatNum_t)
            instantiate_jsonbase_get_template_method(types::Bool_t)
            instantiate_jsonbase_get_template_method(types::Null_t)
            instantiate_jsonbase_get_template_method(types::Object_t)
            instantiate_jsonbase_get_template_method(types::Array_t)

        #undef instantiate_jsonbase_get_template_method

        template<typename T>
        requires is_in_variant_v<T, types::Any_t>
        Status _JsonBase::insert(
            const std::string &jsonPath,
            const T &value,
            const bool &erase,
            const std::array<std::string, 3> &separators
        ) {
            try { //1. In case the json path already exists
                if (jsonPath.empty() && !std::is_same_v<types::Object_t, T> && !std::is_same_v<types::Array_t, T>) return Status::E_TYPE;
                std::shared_ptr<_private::_JsonValue> jsonValue = this->_getJsonValueFromPath(jsonPath, separators);
                return erase ? jsonValue->update<T>(value) : Status::E_VALUE_EXISTS;
            } catch(const error::Base &) { // 2. In case json path does not exist, deduce new key and retry
                try {
                    // 1. If we are at json root
                    if (jsonPath.empty()) {
                        if constexpr (std::is_same_v<T, types::Object_t>)
                           this->__rootValue.emplace(std::make_shared<_private::_JsonValue>(_private::_JsonValue(_parsing::_types::_Object_t())));
                        else if constexpr (std::is_same_v<T, types::Array_t>)
                            this->__rootValue.emplace(std::make_shared<_private::_JsonValue>(_private::_JsonValue(_parsing::_types::_Array_t())));
                        else {
                            THROW(_private::_error::_Type, "Trying to insert a simple typed value at json root. Aborting...");
                            return Status::E_TYPE;
                        }
                        return Status::OK;
                    }
                    // 2. Else, insert in new key or index
                    return parseop::endsWith(jsonPath, separators.at(2)) ?
                    this->__insertInNewArrayIndex(jsonPath, value, separators) :
                    this->__insetInNewObjectKey(jsonPath, value, separators);
                }
                catch (const error::Base &) { return Status::E_JSON_PATH; }
                catch (...) { return Status::E_NOK; }
            } catch (...) { return Status::E_NOK; }
            return Status::E_NOK;
        }

        #define instantiate_jsonbase_insert_template_method(TYPE)\
            template Status _JsonBase::insert(const std::string &, const TYPE &, const bool &, const std::array<std::string, 3> &);

            instantiate_jsonbase_insert_template_method(types::String_t)
            instantiate_jsonbase_insert_template_method(types::IntNum_t)
            instantiate_jsonbase_insert_template_method(types::FloatNum_t)
            instantiate_jsonbase_insert_template_method(types::Bool_t)
            instantiate_jsonbase_insert_template_method(types::Null_t)
            instantiate_jsonbase_insert_template_method(types::Object_t)
            instantiate_jsonbase_insert_template_method(types::Array_t)

        #undef instantiate_jsonbase_insert_template_method

        Status _JsonBase::write(const bool &erase) const { return this->write(this->__filePath, erase); }

        Status _JsonBase::write(const fs::Path &path, const bool &erase) const {
            if ( !this->__rootValue.has_value() ) return Status::E_NO_ROOT_VALUE;
            std::shared_ptr<_private::_JsonValue> tmpJsonValue(this->__rootValue.value());
            std::stringstream ss;
            ss.precision(std::numeric_limits<long double>::max_digits10);
            std::size_t depth = 0;                
            Status tmpStatus = Status::E_NOK;
            if (tmpJsonValue->getType() == _private::_JsonValueTypes::_OBJECT) {
                ss << '{';
                if ( (tmpStatus = __writeObject(tmpJsonValue, ss, depth)) != Status::OK ) return tmpStatus;
            } else if (tmpJsonValue->getType() == _private::_JsonValueTypes::_ARRAY) {
                if ( (tmpStatus = __writeArray(tmpJsonValue, ss, depth)) != Status::OK ) return tmpStatus;
            } else return Status::E_PARSING;
            if (path.exists()) return erase ? __writeFileContent(path, ss.str()) : Status::E_FILE;
            else if ( path.create(fs::Entry::Type::REGULAR_FILE, true) != fs::Status::OK) return Status::E_FILE;
            return __writeFileContent(path, ss.str());
        }

        // Protected :
        std::shared_ptr<_JsonValue> _JsonBase::_getJsonValueFromPath(
            const std::string &jsonPath,
            const std::array<std::string, 3> &separators
        ) const {
            if (this->__rootValue.has_value() == false)
                THROW(_error::_NotLoaded, "JSON has yet not been loaded.");
            std::shared_ptr<_JsonValue> tmpJsonValue(this->__rootValue.value());
            if (jsonPath.empty()) return tmpJsonValue;
            std::vector<std::string> tokenizedPath = parseop::tokenize(jsonPath, std::vector<std::string>(separators.begin(), separators.end()));
            
            for (const std::string &key : tokenizedPath) {
                if (tmpJsonValue->getType() == _JsonValueTypes::_OBJECT) {
                    tmpJsonValue = __getObjectValue(tmpJsonValue, key);
                }
                else if (tmpJsonValue->getType() == _JsonValueTypes::_ARRAY) {
                    tmpJsonValue = __getArrayValue(tmpJsonValue, key);
                }
            }
            return tmpJsonValue;
        }
        
        // Private :
        template<typename T>
        requires is_in_variant_v<T, types::Any_t>
        Status _JsonBase::__insetInNewObjectKey(
            const std::string &jsonPath,
            const T &value,
            const std::array<std::string, 3> &separators
        ) {
            std::vector<std::string> splittedPath = parseop::tokenize(jsonPath, separators.at(0));

            const std::string key = splittedPath.back();
            splittedPath.pop_back();
            const std::string newJsonPath = parseop::join(splittedPath, separators.at(0));
            std::shared_ptr<_private::_JsonValue> jsonValue = this->_getJsonValueFromPath(newJsonPath, separators);
            Status status = jsonValue->update<T>(key, value);
            return status;
            return jsonValue->update<T>(key, value);
        }

        #define instantiate_jsonbase_insertinnewobjectkey_template_method(TYPE)\
            template Status _JsonBase::__insetInNewObjectKey(const std::string &, const TYPE &, const std::array<std::string, 3> &);

            instantiate_jsonbase_insertinnewobjectkey_template_method(types::String_t)
            instantiate_jsonbase_insertinnewobjectkey_template_method(types::IntNum_t)
            instantiate_jsonbase_insertinnewobjectkey_template_method(types::FloatNum_t)
            instantiate_jsonbase_insertinnewobjectkey_template_method(types::Bool_t)
            instantiate_jsonbase_insertinnewobjectkey_template_method(types::Null_t)
            instantiate_jsonbase_insertinnewobjectkey_template_method(types::Object_t)
            instantiate_jsonbase_insertinnewobjectkey_template_method(types::Array_t)

        #undef instantiate_jsonbase_insertinnewobjectkey_template_method

        template<typename T>
        requires is_in_variant_v<T, types::Any_t>            
        Status _JsonBase::__insertInNewArrayIndex(
            const std::string &jsonPath,
            const T &value,
            const std::array<std::string, 3> &separators
        ) {
            // 1. Deduce index and jsonPathWithout index
            std::vector<std::string> splittedPath = parseop::tokenize(jsonPath, std::vector<std::string>(separators.begin(), separators.end()), true);
            if (
                splittedPath.size() < 3 ||
                splittedPath[splittedPath.size() - 3] != separators.at(1) ||
                !parseop::isPositiveInteger(splittedPath[splittedPath.size() - 2])
            ) return Status::E_JSON_PATH;

            const std::size_t index = parseop::toSize_t(splittedPath[splittedPath.size() - 2]);
            splittedPath.erase(splittedPath.end() - 3, splittedPath.end()); // remove last [x]
            const std::string jsonPathWithoutIndex = parseop::join(splittedPath);
            std::shared_ptr<_private::_JsonValue> jsonValue = this->_getJsonValueFromPath(jsonPathWithoutIndex, separators);
            return jsonValue->update<T>(index, value);
        }

        #define instantiate_jsonbase_insertinnewarrayindex_template_method(TYPE)\
            template Status _JsonBase::__insertInNewArrayIndex(const std::string &, const TYPE &, const std::array<std::string, 3> &);

            instantiate_jsonbase_insertinnewarrayindex_template_method(types::String_t)
            instantiate_jsonbase_insertinnewarrayindex_template_method(types::IntNum_t)
            instantiate_jsonbase_insertinnewarrayindex_template_method(types::FloatNum_t)
            instantiate_jsonbase_insertinnewarrayindex_template_method(types::Bool_t)
            instantiate_jsonbase_insertinnewarrayindex_template_method(types::Null_t)
            instantiate_jsonbase_insertinnewarrayindex_template_method(types::Object_t)
            instantiate_jsonbase_insertinnewarrayindex_template_method(types::Array_t)

        #undef instantiate_jsonbase_insertinnewarrayindex_template_method

        Status _JsonBase::__writeSimpleTypedValue(const _private::_parsing::_types::_Any_t &value, std::stringstream &ss) const {
            return std::visit([&ss](auto&& arg) -> Status {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, _private::_parsing::_types::_String_t>) ss << "\"" << arg << "\"";
                else if constexpr (
                    std::is_same_v<T, _private::_parsing::_types::_IntNum_t> ||
                    std::is_same_v<T, _private::_parsing::_types::_FloatNum_t>
                ) { ss << arg; }
                else if constexpr (std::is_same_v<T, _private::_parsing::_types::_Bool_t>) ss << std::boolalpha << arg;
                else if constexpr (std::is_same_v<T, _private::_parsing::_types::_Null_t>) ss << "null";
                else return Status::E_TYPE;
                return Status::OK;
            }, value);
        }

        Status _JsonBase::__writeObject(
            const std::shared_ptr<_private::_JsonValue> &jsonValue,
            std::stringstream &ss,
            std::size_t &depth
        ) const {                
            _private::_parsing::_types::_Any_t jsonValueAsAny = jsonValue->getValue();
            _private::_parsing::_types::_Object_t *jsonValueAsObject = std::get_if<_private::_parsing::_types::_Object_t>(&jsonValueAsAny);
            if ( !jsonValueAsObject ) {
                logger::error << "Value is not an object" << std::endl;
                return Status::E_TYPE;
            }
            Status tmpStatus = Status::E_NOK;
            depth++;
            for (auto it = jsonValueAsObject->begin(); it != jsonValueAsObject->end(); ++it) {
                const auto &[key, value] = *it;
                ss << '\n' << _N_TAB(depth) << "\"" << key << "\": ";
                if (value->getType() == _private::_JsonValueTypes::_OBJECT) {
                    ss << "{";
                    if ( (tmpStatus = __writeObject(value, ss, depth)) != Status::OK ) return tmpStatus;
                } else if (value->getType() == _private::_JsonValueTypes::_ARRAY) {
                    if (  (tmpStatus = __writeArray(value, ss, depth)) != Status::OK) return tmpStatus;
                } else if (value->hasSimpleType()) {
                    if ( (tmpStatus = __writeSimpleTypedValue(value->getValue(), ss)) != Status::OK) return tmpStatus;
                } else return Status::E_TYPE;
                if (std::next(it) != jsonValueAsObject->end()) ss << ','; // if it's not yet the last key of the object
            }
            if (jsonValueAsObject->empty()) ss << '\n';
            ss << '\n' <<_N_TAB(--depth) << '}';
            return Status::OK;
        }

        Status _JsonBase::__writeArray(
            const std::shared_ptr<_private::_JsonValue> &jsonValue,
            std::stringstream &ss,
            std::size_t &depth
        ) const {
            _private::_parsing::_types::_Any_t jsonValueAsAny = jsonValue->getValue();
            _private::_parsing::_types::_Array_t *jsonValueAsArray = std::get_if<_private::_parsing::_types::_Array_t>(&jsonValueAsAny);
            if ( !jsonValueAsArray ) {
                logger::error << "Value is not an array" << std::endl;
                return Status::E_TYPE;
            }
            Status tmpStatus = Status::E_NOK;
            ss << "[\n";
            depth++;
            for (auto it = jsonValueAsArray->begin(); it != jsonValueAsArray->end(); ++it) {                    
                if ((*it)->getType() == _private::_JsonValueTypes::_OBJECT) {
                    ss << _N_TAB(depth) << '{';
                    if ( (tmpStatus = __writeObject(*it, ss, depth)) != Status::OK ) return tmpStatus;
                } else if ((*it)->getType() == _private::_JsonValueTypes::_ARRAY) {
                    if (  (tmpStatus = __writeArray(*it, ss, depth)) != Status::OK) return tmpStatus;
                } else if ((*it)->hasSimpleType()) {
                    ss << _N_TAB(depth);
                    if ( (tmpStatus = __writeSimpleTypedValue((*it)->getValue(), ss)) != Status::OK) return tmpStatus;
                } else return Status::E_TYPE;
                if (std::next(it) != jsonValueAsArray->end()) ss << ",\n";
            }
            ss << '\n' << _N_TAB(--depth) << "]";
            return Status::OK;
        }
        
        std::shared_ptr<_JsonValue> _JsonBase::__getObjectValue(const std::shared_ptr<_JsonValue> &objectAsJsonValue, const std::string &key) {
            _parsing::_types::_Any_t tmpAnyValue = objectAsJsonValue->getValue();
            _parsing::_types::_Object_t *tmpObjectPtr = std::get_if<_parsing::_types::_Object_t>(&tmpAnyValue);

            if (tmpObjectPtr == nullptr)
                THROW(_error::_Parsing, "Value is set as object but is not an actual object. Critical error in parsing.");
            // Now, find the specific key
            
            std::optional<std::shared_ptr<_JsonValue>> jsonValue = _JsonValue::getOptionalJsonValueOfObject(*tmpObjectPtr, key);
            if ( !jsonValue.has_value() )
                THROW(_error::_Key, "Failed to find given key in Object. Got key = %s", key.c_str());
            return jsonValue.value();
        }

        std::shared_ptr<_JsonValue> _JsonBase::__getArrayValue(const std::shared_ptr<_JsonValue> &arrayAsJsonValue, const std::string &indexAsString) {
            _parsing::_types::_Any_t tmpAnyValue = arrayAsJsonValue->getValue();
            _parsing::_types::_Array_t *tmpArrayPtr = std::get_if<_parsing::_types::_Array_t>(&tmpAnyValue);

            if (tmpArrayPtr == nullptr)
                THROW(_error::_Parsing, "Value is set as array but is not an actual array. Critical error in parsing.");
            if (parseop::isPositiveInteger(indexAsString) == false)
                THROW(_error::_Index, "Received an invalid index : %s", indexAsString.c_str());
            std::size_t index = parseop::toSize_t(indexAsString);
            if (index >= tmpArrayPtr->size())
                THROW(_error::_Index, "Index greater than the array size. Index = %s array size = %ld", indexAsString.c_str(), std::to_string((*tmpArrayPtr).size()));
            return tmpArrayPtr->at(index);
        }

        Status _JsonBase::__writeFileContent(const fs::Path &path, const std::string &str) {
            fs::OutFile file(path);

            if (file.clear() != fs::Status::OK ||
                file.write(str) != fs::Status::OK ||
                file.close() != fs::Status::OK
            ) return Status::E_FILE;
            return Status::OK;
        }

    } // namespace _private
} // namespace jsonio
