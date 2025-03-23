/**
 * @file OutJson.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "OutJson.hpp"
#include "_private/_JsonBase.hpp"
#include "_private/_JsonValue.hpp"
#include "_private/_JsonValueTypes.hpp"
#include "_private/_error/_Errors.hpp"

#include <logger/logger.hpp>
#include <parseop/parseop.hpp>
#include <fs/OutFile.hpp>

#include <vector>
#include <optional>
#include <sstream>


namespace jsonio {
    class OutJson::_OutJsonImpl : public _private::_JsonBase {
        public:
            _OutJsonImpl(void) :
            _private::_JsonBase()
            {}

    };

    OutJson::OutJson(void) :
    _pImpl(std::make_unique<_OutJsonImpl>())
    {

    }

    OutJson::~OutJson() = default;

    Status OutJson::parse(const fs::Path &path) { return this->_pImpl->parse(path); }

    template <typename T>
    requires is_in_variant_v<T, types::Any_t>
    Status OutJson::insert(
        const std::string &jsonPath,
        const T &value,
        const bool &erase,
        const std::array<std::string, 3> &separators
    ) { return this->_pImpl->insert<T>(jsonPath, value, erase, separators); }

    #define instantiate_outjson_insert_template_method(TYPE)\
        template Status OutJson::insert<TYPE>(\
            const std::string &, const TYPE &, const bool &, const std::array<std::string, 3> &\
        );

        instantiate_outjson_insert_template_method(types::String_t)
        instantiate_outjson_insert_template_method(types::IntNum_t)
        instantiate_outjson_insert_template_method(types::FloatNum_t)
        instantiate_outjson_insert_template_method(types::Bool_t)
        instantiate_outjson_insert_template_method(types::Null_t)
        instantiate_outjson_insert_template_method(types::Object_t)
        instantiate_outjson_insert_template_method(types::Array_t)
    #undef instantiate_outjson_insert_template_method


    Status OutJson::write(const bool &erase) const { return this->_pImpl->write(erase); }
    Status OutJson::write(const fs::Path &path, const bool &erase) const { return this->_pImpl->write(path, erase); }

} // namespace jsonio
