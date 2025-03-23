/**
 * @file Json.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
*/


#include "Json.hpp"
#include "_private/_JsonBase.hpp"

namespace jsonio {

    class Json::_JsonImpl : public _private::_JsonBase {

        public:
            _JsonImpl(void) :
            _private::_JsonBase()
            {}

    };

    // Public :
    Json::Json(void) :
    _impl{std::make_unique<_JsonImpl>()}
    {
    }

    Json::~Json() = default;

    Status Json::parse(const fs::Path &path) { return this->_impl->parse(path); }

    types::ValueTypes Json::getType(const std::string &jsonPath, const std::array<std::string, 3> &separators) const {
        return this->_impl->getType(jsonPath, separators);
    }

    template <typename T>
    requires is_in_variant_v<T, types::Any_t>
    std::optional<T> Json::get(const std::string &jsonPath, const std::array<std::string, 3> &separators) const {
        return this->_impl->get<T>(jsonPath, separators);
    }

    #define instantiate_json_get_template_method(TYPE)\
        template std::optional<TYPE> Json::get(const std::string &, const std::array<std::string, 3> &) const;

        instantiate_json_get_template_method(types::String_t)
        instantiate_json_get_template_method(types::IntNum_t)
        instantiate_json_get_template_method(types::FloatNum_t)
        instantiate_json_get_template_method(types::Bool_t)
        instantiate_json_get_template_method(types::Null_t)
        instantiate_json_get_template_method(types::Object_t)
        instantiate_json_get_template_method(types::Array_t)

    #undef instantiate_json_get_template_method

    template <typename T>
    requires is_in_variant_v<T, types::Any_t>
    Status Json::insert(
        const std::string &jsonPath,
        const T &value,
        const bool &erase,
        const std::array<std::string, 3> &separators
    ) { return this->_impl->insert<T>(jsonPath, value, erase, separators); }

    #define instantiate_json_insert_template_method(TYPE)\
        template Status Json::insert<TYPE>(\
            const std::string &, const TYPE &, const bool &, const std::array<std::string, 3> &\
        );

        instantiate_json_insert_template_method(types::String_t)
        instantiate_json_insert_template_method(types::IntNum_t)
        instantiate_json_insert_template_method(types::FloatNum_t)
        instantiate_json_insert_template_method(types::Bool_t)
        instantiate_json_insert_template_method(types::Null_t)
        instantiate_json_insert_template_method(types::Object_t)
        instantiate_json_insert_template_method(types::Array_t)
    #undef instantiate_json_insert_template_method


    Status Json::write(const bool &erase) const { return this->_impl->write(erase); }
    Status Json::write(const fs::Path &path, const bool &erase) const { return this->_impl->write(path, erase); }

    
} // namespace jsonio
