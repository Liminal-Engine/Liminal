#include "_private/_lexing/_types.hpp"

namespace liminal_json_io {
    namespace _private  {
        namespace _lexing {
            namespace _types {

                _Token_s::_Token_s(const std::string &strValue, const _TokenTypes_e_c &type) :
                _strValue{strValue},
                _type{type}
                {}

                bool _Token_s::operator==(const char &value) const {
                    return this->_strValue == std::string{value};
                }

                bool _Token_s::operator==(const char value[]) const {
                    return this->_strValue.compare(value) == 0;
                }

                bool _Token_s::operator==(const std::string &value) const {
                    return this->_strValue == value;
                }

                std::string _Token_s::getValueAsStr(void) const {
                    return this->_strValue;
                }

                std::string _Token_s::getTypeAsStr(void) const {
                    switch (this->_type) {
                        case _TokenTypes_e_c::STRING:
                            return "string";
                        case _TokenTypes_e_c::INT_NUM:
                            return "integer";
                        case _TokenTypes_e_c::FLOAT_NUM:
                            return "float";
                        case _TokenTypes_e_c::NULL_:
                            return "null";
                        case _TokenTypes_e_c::BOOL:
                            return "bool";
                        case _TokenTypes_e_c::SYNTAX:
                            return "syntax";
                        default:
                            return "UNKNOWN";
                    }
                }

                _TokenTypes_e_c _Token_s::getType(void) const { return this->_type; }

                void _Token_s::setType(const _TokenTypes_e_c &type) { this->_type = type; }


                _Index::_Index(const char &value, const std::size_t &line, const std::size_t &lineOffset) :
                _value{value},
                _line{line},
                _lineOffset{lineOffset}
                {}

                char _Index::getValue(void) const { return this->_value; }

                const std::string _Index::getPosDescription(void) const {
                    return std::to_string(this->_line) + ":" + std::to_string(this->_lineOffset);
                }

            } // namespace _types
        } // namespace _lexing
    } // namespace _private
} // namespace liminal_json_io
