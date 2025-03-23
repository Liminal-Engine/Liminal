#ifndef _TEST_LIMINAL_JSONIO_INJSON_HELPER_HPP_
#define _TEST_LIMINAL_JSONIO_INJSON_HELPER_HPP_

#include <string>
#include <algorithm>

#include <fs/Path.hpp>

namespace test {
    namespace jsonio {
        namespace OutJson {
            class Helper {
                public:
                    static std::string removeQuotes(const std::string &str);
                    static ::fs::Path generateTmpOutputPath(void);
                    static bool filesAreEqual(const ::fs::Path & path1, const ::fs::Path &path2);
            };
        } // OutJson
    } // namespace jsonio
} // namespace test


#endif // _TEST_LIMINAL_JSONIO_INJSON_HELPER_HPP_
