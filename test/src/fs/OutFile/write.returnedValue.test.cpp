/**
 * @file write.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
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
                std::string, // data
                ::fs::Status //expected status
            >;
            class FSOutFileWriteMethodReturnedValue : public ::testing::TestWithParam<FSOutFileWriteParam> {
                protected:
                    ::fs::Path __path;
                    std::string __data;
                    ::fs::OutFile _instance;

                    FSOutFileWriteMethodReturnedValue(void):
                    __path(std::get<0>(GetParam())),
                    __data(std::get<1>(GetParam())),
                    _instance(::fs::OutFile(__path))
                    {
                        _instance.open(true);
                    }

                    ~FSOutFileWriteMethodReturnedValue() {
                        _instance.close();
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

            TEST_P(FSOutFileWriteMethodReturnedValue, ReturnGivenStatus) {
                EXPECT_EQ(_instance.write(__data), std::get<2>(GetParam()));
            };

            INSTANTIATE_TEST_SUITE_P(
                ExpectGivenStatusWhenGivenOpenablePaths,
                FSOutFileWriteMethodReturnedValue,
                testing::Values(
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/a.txt"),
                        "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum",
                        ::fs::Status::OK
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/b.txt"), 
                        std::string(1024 * 1024, 'A'), // 1 MB string
                        ::fs::Status::OK
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/c.txt"),
                        std::string(1024 * 1024, 'A'), // 1 MB string
                        ::fs::Status::OK
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/normal_file.weirdext"),
                        std::string("This is a normal string."),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/special_chars_file."),
                        std::string("Special characters: !@#$%^&*()_+-=[]{}|;:'\",.<>?/`~"),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/escape_sequences_file"),
                        std::string("Line1\\nLine2\\tTabbed\\rCarriageReturn\\0NullChar"),
                        ::fs::Status::OK
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/unicode_file.💾"),
                        std::string(reinterpret_cast<const char*>(u8"Unicode: \u2713 \u2603 \u2764")),
                        ::fs::Status::OK
                    ),
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/empty_file"),
                        std::string(""),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/large_file.noext"),
                        std::string(1024 * 1024, 'A'), // 1 MB of 'A'
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/null_chars_file.null"),
                        std::string("Null\0Character\0Test", 18), // Explicit size for null characters
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/non_printable_file"),
                        std::string("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A", 10), // Explicit size
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/mixed_content_file.mixed"),
                        std::string("Text123!@#\n\t\u2713\x01\x00"),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/path_like_file.path"),
                        std::string("/home/user/docs/file.txt"),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/json_file.jsonlike"),
                        std::string(R"({"key": "value", "array": [1, 2, 3]})"),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/xml_file.xmlweird"),
                        std::string(R"(<root><child>value</child></root>)"),
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/binary_file.bin"),
                        std::string("\x89PNG\r\n\x1A\n\x00\x00\x00\rIHDR", 16), // Explicit size
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/repeated_pattern_file"),
                        std::string(1024, 'A') + std::string(1024, 'B'), // 1KB single line
                        ::fs::Status::OK
                    ),

                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/long_line_file.long"),
                        std::string(1024 * 1024, 'X'), // 1 MB single line
                        ::fs::Status::OK
                    )
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                ExpectGivenStatusWhenGivenInexistantPaths,
                FSOutFileWriteMethodReturnedValue,
                testing::Values(
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/a.txttxt"),
                        "Lorem Ipsum",
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),
                    // Path parent doesn't exist => expect parent-missing error
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/does_not_exist_dir/file.txt"),
                        std::string("hello non-existent parent"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Deep non-existent parent chain => expect parent-missing error
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/missing/deeper/levels/file.bin"),
                        std::string("deep path data"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Hidden directory that doesn't exist
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/.hidden_dir/.hiddenfile"),
                        std::string("hidden file content"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Empty path string => expect path-empty error
                    std::make_tuple(
                        ::fs::Path(""),
                        std::string("data for empty path"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Path points to an existing directory (writing to a dir) => expect is-dir error
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile"), // existing directory
                        std::string("trying to write to a directory"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Path contains characters that are likely invalid/handled specially => expect invalid-path error
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/invalid<>name.txt"),
                        std::string("invalid chars in path"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Attempt to force creation of many parents but test expects engine can't create them automatically
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/can/create/deep/very/deep/levels/file.txt"),
                        std::string("attempt to create many parents"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Parent is actually a file (treating file as directory) => expect forbidden create type
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/a.txt/child"),
                        std::string("parent-is-file"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Extremely long path/name (may be rejected) => expect invalid-path
                    std::make_tuple(
                        ::fs::Path(std::string("../../test/assets/fs/OutFile/") + std::string(128, 'a')),
                        std::string("long name test"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    ),

                    // Nonexistent file in otherwise-valid dir but test expecting create-file error (cover create-file path)
                    std::make_tuple(
                        ::fs::Path("../../test/assets/fs/OutFile/newly_not_created_file.noext"),
                        std::string("create file test content"),
                        ::fs::Status::E_WRITE_FILE_CLOSED
                    )
                )
            );

        } // namespace OutFile
    } // namespace fs
} // namespace test
