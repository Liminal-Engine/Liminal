#include "_private/_lexing/_types.hpp"

namespace liminal_json_io {
    namespace _private  {
        namespace _lexing {
            namespace _types {

                std::string _convertTokenTypeToString(const _TokenTypes_e_c &tokenType) {
                    switch (tokenType) {
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

                const std::string _Index::getPosDescription(void) const {
                    return std::to_string(this->line) + ":" + std::to_string(this->lineOffset);
                }

            } // namespace _types
        } // namespace _lexing
    } // namespace _private
} // namespace liminal_json_io
