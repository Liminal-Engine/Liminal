/*  *//**
 * @file InJson.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "InJson.hpp"

#include "is_in_variant_v.hpp"

#include <logger/logger.hpp>

#include "_private/_JsonValue.hpp"
#include "_private/_parsing/_types.hpp"
#include "_private/_JsonBase.hpp"
#include "_private/_error/_Errors.hpp"

#include <iostream>

namespace jsonio
{

    class InJson::_InJsonImpl : public _private::_JsonBase {

        public:
            _InJsonImpl(void) :
            _private::_JsonBase()
            {}

    };

    // Public :
    InJson::InJson(void) :
    _inJsonImpl{std::make_unique<_InJsonImpl>()}
    {
    }

    InJson::~InJson() = default;

    Status InJson::parse(const fs::Path &path) { return this->_inJsonImpl->parse(path); }

    types::ValueTypes InJson::getType(const std::string &jsonPath, const std::array<std::string, 3> &separators) const {
        return this->_inJsonImpl->getType(jsonPath, separators);
    }

    template <typename T>
    requires is_in_variant_v<T, types::Any_t>
    std::optional<T> InJson::get(const std::string &jsonPath, const std::array<std::string, 3> &separators) const {
        return this->_inJsonImpl->get<T>(jsonPath, separators);
    }

    #define instantiate_injson_get_template_method(TYPE)\
        template std::optional<TYPE> InJson::get(const std::string &, const std::array<std::string, 3> &) const;

        instantiate_injson_get_template_method(types::String_t)
        instantiate_injson_get_template_method(types::IntNum_t)
        instantiate_injson_get_template_method(types::FloatNum_t)
        instantiate_injson_get_template_method(types::Bool_t)
        instantiate_injson_get_template_method(types::Null_t)
        instantiate_injson_get_template_method(types::Object_t)
        instantiate_injson_get_template_method(types::Array_t)

    #undef instantiate_injson_get_template_method

} // namespace jsonio
