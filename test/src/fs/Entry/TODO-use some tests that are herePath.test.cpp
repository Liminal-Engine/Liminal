// /**
//  * @file Path.test.cpp
//  * @author DE VITA Matteo (matteo.devita7@gmail.com)
//  * @brief 
//  * @version 0.1
//  * @date 2024-03-27
//  * 
//  * @copyright Copyright (c) 2024
//  * 
// */

// #include <fs/Path.hpp>

// #include <test/fs/create.hpp>

// #include <gtest/gtest.h>
// #include <gmock/gmock.h>
// #include <vector>
// #include <tuple>
// #include <string>
// #include <utility>
// #include <optional>
// #include <filesystem>

// // TODO : implement tests for Path::getAbsolute but first :
// // - have a system to know the installation path, from which we'll deduce de cwd
// // - make sure to compile on windows to have specfifc absolute path (from root) on windows and linux

// // TODO : test getType()
// // TODO : finish to test all methods

// void addEntries(std::vector<fs::Path> &instances, std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>> entries) {
//     for (fs::Path &path : instances) {
//         for (const auto &[entry, index] : entries) {
//             if (index.has_value()) path.insert(entry, index.value());
//             else path.insert(entry);
//         }
//     }
// }

// void cleanIfNeeded(std::vector<fs::Path> &instances, const bool &clean) {
//     if (clean) {
//         for (fs::Path &path : instances) path.clean();
//     }
// }

// using FSPathGetExtensionParam = std::tuple<
//     std::optional<std::string>, // original path
//     std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
//     bool, // whether to clean the path
//     std::optional<std::string> // expected extension
// >;

// class FSPathGetExtensionMethod : public ::testing::TestWithParam<FSPathGetExtensionParam> {
//     protected:
//         std::vector<fs::Path> _instances;

//         FSPathGetExtensionMethod(void) :
//         _instances{createInstances(std::get<0>(GetParam()))}
//         {
//             addEntries(_instances, std::get<1>(GetParam()));
//             cleanIfNeeded(_instances, std::get<2>(GetParam()));
//         }
// };

// TEST_P(FSPathGetExtensionMethod, ReturnsGivenValue) {
//     for (const fs::Path &path : _instances) {
//         EXPECT_EQ(path.getExtension(), std::get<3>(GetParam()));
//     }
// };

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenVariousEntries,
//     FSPathGetExtensionMethod,
//     testing::Values(
//         std::make_tuple(
//             std::optional<std::string>("/tmp/user"),
//             std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
//             false,
//             std::optional<std::string>()
//         ),
    
//         std::make_tuple(
//             std::optional<std::string>("/tmp/user"),
//             std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
//                 std::make_pair("ccc", std::optional<std::size_t>()),
//                 std::make_pair("index.html", std::optional<std::size_t>()),
//             },
//             false,
//             std::optional<std::string>("html")
//         ),

//         std::make_tuple(
//             std::optional<std::string>("/tmp/user"),
//             std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
//                 std::make_pair("ccc", std::optional<std::size_t>()),
//                 std::make_pair("..", std::optional<std::size_t>()),
//                 std::make_pair("index.ftp--zeraaa", std::optional<std::size_t>()),
//             },
//             false,
//             std::optional<std::string>("ftp--zeraaa")
//         ),

//         std::make_tuple(
//             std::optional<std::string>("aaa//////bbb/ddd/eeee///"),
//             std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
//                 std::make_pair("ccc", std::optional<std::size_t>()),
//                 std::make_pair("..", std::optional<std::size_t>()),
//                 std::make_pair("index.html", std::optional<std::size_t>()),
//             },
//             true,
//             std::optional<std::string>("html")
//         ),

//         std::make_tuple(
//             std::optional<std::string>(),
//             std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
//                 std::make_pair("ccc", std::optional<std::size_t>()),
//                 std::make_pair("ddd", std::optional<std::size_t>()),
//                 std::make_pair("..", std::optional<std::size_t>()),
//                 std::make_pair("aaa", std::optional<std::size_t>(2)),
//                 std::make_pair("bbb", std::optional<std::size_t>(2)),
//                 std::make_pair("index", std::optional<std::size_t>())
//             },
//             true,
//             std::optional<std::string>()
//         ),


//         std::make_tuple(
//             std::optional<std::string>(),
//             std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
//             false,
//             std::optional<std::string>()
//         )
//     )
// );


// using FSPathGetTypeParam = std::tuple<
//     std::string, // original path string to build from
//     fs::Path::Entry::Type // expected result
// >;

// class FSPathGetTypeMethod : public ::testing::TestWithParam<FSPathGetTypeParam> {
//     protected:
//         std::vector<fs::Path> _instances;

//         FSPathGetTypeMethod(void) :
//         _instances{createInstances(std::get<0>(GetParam()))}
//         {
//         }
// };

// TEST_P(FSPathGetTypeMethod, ReturnsGivenValue) {
//     for (const fs::Path &path : _instances) {
//         EXPECT_EQ(path.getType(), std::get<1>(GetParam()));
//     }
// };

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenVariousPaths,
//     FSPathGetTypeMethod,
//     testing::Values(
//         std::make_tuple("../../tests/assets/fs/.hidden", fs::Path::Entry::Type::REGULAR_FILE),
//         std::make_tuple("../../tests/assets/fs/!@#$%^&*().!@#$%^&*()", fs::Path::Entry::Type::REGULAR_FILE),
//         std::make_tuple("../../tests/assets/json/valid/basic.json", fs::Path::Entry::Type::REGULAR_FILE),
//         std::make_tuple("../../tests/assets/fs/|||empty|||", fs::Path::Entry::Type::REGULAR_FILE),
//         std::make_tuple("../../tests/assets/fs/", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("../../tests/assets/fs", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("../../tests/assets/json/", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("../../tests/assets/json/valid", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("../../tests/assets/json/invalid/", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("./I/DO/no/exists", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("../../tests/assets/fs/sym_link", fs::Path::Entry::Type::SYM_LINK),
//         std::make_tuple("../../tests/assets/fs/ImABlockDevice", fs::Path::Entry::Type::BLOCK_DEVICE), // FIXME : may work only on Linux
//         std::make_tuple("../../tests/assets/fs/ImACharDevice", fs::Path::Entry::Type::CHARACTER_DEVICE), // FIXME : may work only on Linux
//         std::make_tuple("../../tests/assets/fs/ImAFifo", fs::Path::Entry::Type::FIFO), // TODO : check if works on Windows
//         std::make_tuple("", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("/", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("/path/with spaces", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("/path/with!@#$%^&*()_+special", fs::Path::Entry::Type::UNKNOWN),        
//         std::make_tuple("/" + std::string(10000, 'a'), fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("/path/with/trailing/slashes////", fs::Path::Entry::Type::UNKNOWN),        
//         std::make_tuple(".", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("..", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("...", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("....", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("/path/with\\mixed/separators", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("..///..///tests///assets///fs///!@#$%^&*().!@#$%^&*()", fs::Path::Entry::Type::REGULAR_FILE),
//         std::make_tuple("././././.", fs::Path::Entry::Type::DIRECTORY),
//         std::make_tuple("./. . /./ . ", fs::Path::Entry::Type::UNKNOWN),
//         // Edge case: Path containing special device names (may work only on Windows) // FIXME?
//         std::make_tuple("CON", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("PRN", fs::Path::Entry::Type::UNKNOWN),
//         std::make_tuple("/path/with/very/long/name/that/is/very/super/super//////long//////", fs::Path::Entry::Type::UNKNOWN)
//     )
// );

// using FSPathGetParentParam = std::tuple<
//     std::string, // original path string to build from
//     std::optional<fs::Path> // expected result
// >;

// class FSPathGetParentMethod : public ::testing::TestWithParam<FSPathGetParentParam> {
//     protected:
//         std::vector<fs::Path> _instances;

//         FSPathGetParentMethod(void) :
//         _instances{createInstances(std::get<0>(GetParam()))}
//         {
//         }
// };

// TEST_P(FSPathGetParentMethod, ReturnsGivenValue) {
//     for (const fs::Path &path : _instances) {
//         EXPECT_EQ(path.getParent(), std::get<1>(GetParam()));
//     }
// };

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenVariousPaths,
//     FSPathGetParentMethod,
//     testing::Values(
//         std::make_tuple("../../tests/assets/fs/.hidden", std::optional<fs::Path>{"../../tests/assets/fs/"}),
//         std::make_tuple("../../tests/assets/fs/.hidden", std::optional<fs::Path>{"../../tests/assets/fs"}),
//         std::make_tuple("./I/DO/no/exists", std::optional<fs::Path>{"./I/DO/no"}),
//         std::make_tuple("/path/to/non_empty_file.txt", std::optional<fs::Path>{"/path/to"}),
//         std::make_tuple("/a/b/c/d/e/f/g/h", std::optional<fs::Path>{"/a/b/c/d/e/f/g"}),
//         std::make_tuple("..////.//a/b/c/d/e/f/g/h", std::optional<fs::Path>{"..////.//a/b/c/d/e/f/g/"}),
//         std::make_tuple("..////.//a/b/c/d/e/f/g/h", std::optional<fs::Path>{"..////.//a/b/c/d/e/f/g"}), // they are not thge same, last one does not have '/' at the end of expected result
//         std::make_tuple("", std::optional<fs::Path>{}),
//         std::make_tuple("./", std::optional<fs::Path>{}),
//         std::make_tuple("/", std::optional<fs::Path>{}),
//         std::make_tuple("..", std::optional<fs::Path>{}),
//         std::make_tuple("../..", std::optional<fs::Path>{".."}),
//         std::make_tuple("/rootfile.txt", std::optional<fs::Path>{}),
//         std::make_tuple("/path/with spaces/file.txt", std::optional<fs::Path>{"/path/with spaces"}),
//         std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", std::optional<fs::Path>{"/path/with!@#$%^&*()_+special"})
//     )
// );

// using FSPathPointsToParam = std::tuple<
//     std::string, // original path string to build from
//     fs::Path, // other path
//     bool, // wether to clean path
//     bool // expected returned status
// >;


