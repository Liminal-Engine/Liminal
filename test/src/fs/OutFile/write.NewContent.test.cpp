/**
 * @file write.content.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-13-10
 * @copyright Copyright (c) 2024
 */ 


#include <fs/OutFile.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <filesystem>

// TODO : test files with wrong permissions

namespace test {
    namespace fs {
        namespace OutFile {
            using FSOutFileWriteParam = std::tuple<
                ::fs::Path, // path
                std::string // data
            >;
            class FSOutFileWriteMethodNewContent : public ::testing::TestWithParam<FSOutFileWriteParam> {
                protected:
                    ::fs::Path __path;
                    std::string __data;
                    ::fs::OutFile _instance;

                    FSOutFileWriteMethodNewContent(void):
                    __path(std::get<0>(GetParam())),
                    __data(std::get<1>(GetParam())),
                    _instance(::fs::OutFile(__path))
                    {                        
                        _instance.open(true);
                        if ( !_instance.isOpen() ) {
                            std::cerr << "Fail to open file : " << __path.asStr() << std::endl;
                        }
                    }

                    ~FSOutFileWriteMethodNewContent() {
                        if (_instance.isOpen()) _instance.close();
                        this->__clearFile();
                    }
                private:
                    void __clearFile() {
                        if ( !std::filesystem::exists(this->__path.asStr()) ) return;
                        std::ofstream ofs(__path.asStr(), std::ofstream::out | std::ofstream::trunc);
                        if (ofs.is_open()) {
                            ofs.close();
                        }
                    }
            };

            TEST_P(FSOutFileWriteMethodNewContent, ExpectGivenContent) {
                _instance.write(__data);
                _instance.close();
                std::ifstream file(__path.asStr()); // Open the file
                if (!file.is_open()) {
                    FAIL() << "Failed to open the file in CPP way to read it's content";
                }
                std::ostringstream buffer;
                buffer << file.rdbuf();
                file.close();
                std::string cppWayContent = buffer.str(); 
                EXPECT_EQ(__data, cppWayContent);
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenOpenablePaths,
                FSOutFileWriteMethodNewContent,
                testing::Values(
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/a.txt"),
                        "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum"
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/b.txt"), 
                        std::string(1024 * 1024, 'A') // 1 MB string
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/normal_file.weirdext"),
                        std::string("This is a normal string.")
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/normal_file.weirdext"),
                        std::string("This is a normal string with new line.\n")
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/special_chars_file."),
                        std::string("Special characters: !@#$%^&*()_+-=[]{}|;:'\",.<>?/`~")
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/escape_sequences_file"),
                        std::string("Line1\\nLine2\\tTabbed\\rCarriageReturn\\0NullChar")
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/unicode_file.💾"),
                        std::string(reinterpret_cast<const char*>(u8"Unicode: \u2713 \u2603 \u2764"))
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/empty_file"),
                        std::string("")
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/large_file.noext"),
                        std::string(1024 * 1024, 'A') // 1 MB of 'A'
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/null_chars_file.null"),
                        std::string("Null\0Character\0Test", 18) // Explicit size for null characters
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/non_printable_file"),
                        std::string("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A", 10) // Explicit size
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/mixed_content_file.mixed"),
                        std::string("Text123!@#\n\t\u2713\x01\x00")
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/path_like_file.path"),
                        std::string("/home/user/docs/file.txt")
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/json_file.jsonlike"),
                        std::string(R"({"key": "value", "array": [1, 2, 3]})")
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/xml_file.xmlweird"),
                        std::string(R"(<root><child>value</child></root>)")
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/binary_file.bin"),
                        std::string("\x89PNG\r\n\x1A\n\x00\x00\x00\rIHDR", 16) // Explicit size
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/repeated_pattern_file"),
                        std::string(1024, 'A') + std::string(1024, 'B')
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/long_line_file.long"),
                        std::string(1024, 'X') // 1 KB line string
                    )
                )
            );

        } // namespace OutFile
    } // namespace fs
} // namespace test
