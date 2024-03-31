/**
 * @file Path.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-27
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <fs/Path.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include <optional>

// TODO : implement tests for Path::getAbsolute but first :
// - have a system to know the installation path, from which we'll deduce de cwd
// - make sure to compile on windows to have specfifc absolute path (from root) on windows and linux

// TODO : test getType()
// TODO : finish to test all methods

std::vector<fs::Path> createInstances(const std::optional<std::string> &path) {
    std::vector<fs::Path> res{};
     
    if (path.has_value()) {
        res.push_back(fs::Path{path.value()});
        res.push_back(fs::Path{res.at(0)});
        fs::Path tmpPath = res.at(0);
        res.push_back(tmpPath);
    } else {
        res.push_back(fs::Path{});
    }
    return res;
}

void addEntries(std::vector<fs::Path> &instances, std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>> entries) {
    for (fs::Path &path : instances) {
        for (const auto &[entry, index] : entries) {
            if (index.has_value()) path.insert(entry, index.value());
            else path.insert(entry);
        }
    }
}

void cleanIfNeeded(std::vector<fs::Path> &instances, const bool &clean) {
    if (clean) {
        for (fs::Path &path : instances) path.clean();
    }
}

using InsertMethodParam = std::tuple<
    std::optional<std::string>, // path to build instances from, if has no value, constructor fs::Path{} will be used
    fs::Entry_t, // add entry ...
    std::optional<std::size_t>, // to the wanted optional positions
    fs::Status // expected return status
>;
class FSInsertMethod : public ::testing::TestWithParam<InsertMethodParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSInsertMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {}
};

TEST_P(FSInsertMethod, ReturnGivenStatus) {
    fs::Entry_t entry{std::get<1>(GetParam())};
    std::optional<std::size_t> pos{std::get<2>(GetParam())};

    for (fs::Path &path : _instances) {
        if (pos.has_value()) EXPECT_EQ(path.insert(entry, pos.value()), std::get<3>(GetParam()));
        else EXPECT_EQ(path.insert(entry), std::get<3>(GetParam()));
    }
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidEntriesAtValidPos,
    FSInsertMethod,
    testing::Values(
        std::make_tuple("/tmp", "etc", 0, fs::Status::OK),
        std::make_tuple("/aaa/bbb", "ccc", 0, fs::Status::OK),
        std::make_tuple("/aaa/bbb", "ccc", 1, fs::Status::OK),
        std::make_tuple("/aaa/bbb", "ccc", 2, fs::Status::OK),
        std::make_tuple(std::nullopt, "aaa", std::nullopt, fs::Status::OK),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 2, fs::Status::OK),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 1, fs::Status::OK),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 0, fs::Status::OK),
        std::make_tuple("/home/user", "documents", 0, fs::Status::OK),
        std::make_tuple("/var/log", "syslog", 1, fs::Status::OK),
        std::make_tuple("/usr/local", "bin", 2, fs::Status::OK),
        std::make_tuple("/etc", "passwd", 0, fs::Status::OK),
        std::make_tuple(std::nullopt, "root", std::nullopt, fs::Status::OK),
        std::make_tuple("/opt/software", "config", 1, fs::Status::OK),
        std::make_tuple("/usr/share", "locale", 0, fs::Status::OK),
        std::make_tuple("/lib/modules", "kernel", 2, fs::Status::OK),
        std::make_tuple("/srv/http", "public_html", 1, fs::Status::OK),
        std::make_tuple("/home/user", "Downloads", 0, fs::Status::OK),
        std::make_tuple("/var/www", "html", 1, fs::Status::OK),
        std::make_tuple("/usr/lib", "python3.8", 2, fs::Status::OK),
        std::make_tuple("/etc/systemd", "system", 0, fs::Status::OK),
        std::make_tuple(std::nullopt, "etc", std::nullopt, fs::Status::OK),
        std::make_tuple("/tmp/complex-dir-name", "subdir", 1, fs::Status::OK),
        std::make_tuple("usrlocal", "include", 1, fs::Status::OK),
        std::make_tuple("/etc", "hosts", 1, fs::Status::OK),
        std::make_tuple("/var/log", "messages", 2, fs::Status::OK),
        std::make_tuple("/usr/share", "fonts", 0, fs::Status::OK),
        std::make_tuple("/lib/modules", "module1", 1, fs::Status::OK),
        std::make_tuple("/srv/http", "index.html", 1, fs::Status::OK),
        std::make_tuple("/home/user", "Pict          ures", 0, fs::Status::OK),
        std::make_tuple("/var/www", "index.php", 1, fs::Status::OK),
        std::make_tuple("/usr/lib", "lib1", 2, fs::Status::OK),
        std::make_tuple("/etc/systemd", "service1", 0, fs::Status::OK),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 2, fs::Status::OK),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 2, fs::Status::OK),
        std::make_tuple(std::nullopt, ".entry1", std::nullopt, fs::Status::OK),
        std::make_tuple("/path/to/directory", ".entry2", std::nullopt, fs::Status::OK),
        std::make_tuple(std::nullopt, "entry3", 0, fs::Status::OK),
        std::make_tuple("/path/to/directory", "..entry4", 1, fs::Status::OK),
        std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", 10, fs::Status::OK),
        std::make_tuple("/path/to/directory", "entry9", 1, fs::Status::OK),
        std::make_tuple("/path/to/directory", "entry10", 2, fs::Status::OK),
        std::make_tuple("/path/to/directory", "entry11", 3, fs::Status::OK),
        std::make_tuple("./var/log", "messages", 2, fs::Status::OK),
        std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", 2, fs::Status::OK),
        std::make_tuple("../lib/modules", "module1", std::nullopt, fs::Status::OK),
        std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", 0, fs::Status::OK),
        std::make_tuple("srv/http", "index.html", 1, fs::Status::OK),
        std::make_tuple("home/user", "Pictures", 0, fs::Status::OK)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenInvalidEntriesAtValidPos,
    FSInsertMethod,
    testing::Values(
        std::make_tuple("/tmp", "et/c", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/aaa/bbb", "c\\cc", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/aaa/bbb", "cc\"c", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/aaa/bbb", "cc><c", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "a*aa", std::nullopt, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "a*aa", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Пр/оекты", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/home/user", "documen<>ts", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/log", "/s\\y<s>l\"o   -|g", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/local", "b*in", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc", "pas|swd", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "r&oot", std::nullopt, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/opt/software", "/\\<>:\"|*&~", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/share", "locale/", 1000, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/lib/modules", "kernel*.", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/srv/http", "public_htm:l", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/home/user", "Downlo:ads", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/www", "ht/ml", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/lib", "python3:8", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc/systemd", "s|y/s/t&em", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "et<>><c", std::nullopt, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "subdi//r", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("usrlocal", "i:\"/nclude", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc", "hosts*", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/log", "me<>ssages", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/share", "fo|?*&nts", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/lib/modules", "mo/////dule1", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/srv/http", "index:html", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/home/user", "Pictu****res", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/www", "index*php", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/lib", "lib:1", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc/systemd", "ser//vice1", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "s/ubdir2", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "/subdir2", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "en:::try1", std::nullopt, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "e**ntry2", std::nullopt, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "entr~~~~~y3", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "~.entry4", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", ":entry5", 10, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "entry|9", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "entry|10", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "entry|11", 3, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("./var/log", "mess>>ages", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("./../usr/share", "...ezrretertert-----reteezrz.errte/", 2, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("../lib/modules", "/module1", std::nullopt, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("../lib/modules", "..:.aaa.bbb.c.d.e.s.f.e.q.z.er.", 0, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("srv/http", "index~html", 1, fs::Status::PATH_INVALID_ENTRY_NAME),
        std::make_tuple("home/user", "Pictures&", 0, fs::Status::PATH_INVALID_ENTRY_NAME)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidEntriesAtInvalidPos,
    FSInsertMethod,
    testing::Values(
        std::make_tuple("/tmp", "etc", 10, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/aaa/bbb", "ccc", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/aaa/bbb", "ccc", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/aaa/bbb", "ccc", 6, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple(std::nullopt, "aaa", 1, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/home/user", "documents", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/var/log", "syslog", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/usr/local", "bin", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/etc", "passwd", 3, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/opt/software", "config", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/usr/share", "locale", 10, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/lib/modules", "kernel", 202, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/srv/http", "public_html", 1000, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/home/user", "Downloads", 40, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/var/www", "html", 105, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/usr/lib", "python3.8", 55, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/etc/systemd", "system", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/tmp/complex-dir-name", "subdir", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/usr/local", "include", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/etc", "hosts", 3, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/var/log", "messages", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/usr/share", "fonts", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/lib/modules", "module1", 10, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/srv/http", "index.html", 10, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/home/user", "Pict          ures", 120, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/var/www", "index.php", 10, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/usr/lib", "lib1", 20, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/etc/systemd", "service1", 50, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 20, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 20, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple(std::nullopt, ".entry1", 40, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", ".entry2", 78, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple(std::nullopt, "entry3", 2, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", "..entry4", 10, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", 12, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("path/to/directory", "entry9", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", "entry10", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", "entry11", 6, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("./var/log", "messages", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", 6, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("../lib/modules", "module1", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", 5, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("srv/http", "index.html", 4, fs::Status::PATH_INVALID_INDEX),
        std::make_tuple("home/user", "Pictures", 4, fs::Status::PATH_INVALID_INDEX)
    )
);

using CleanMethodParam = std::tuple<
    std::optional<std::string>, // path to build instances from, if has no value, constructor fs::Path{} will be used
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // optional vector of entry to add to given optional indices
    fs::Status, // expected return status
    fs::Path // expected Path result
>;
class FSCleanMethod : public ::testing::TestWithParam<CleanMethodParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSCleanMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
        }
};

TEST_P(FSCleanMethod, ReturnGivenStatusAndProduceGivenPath) {
    for (fs::Path &path : _instances) {
        EXPECT_EQ(path.clean(), std::get<2>(GetParam()));
        EXPECT_TRUE(path == std::get<3>(GetParam()));
    }
}

INSTANTIATE_TEST_SUITE_P(
    WhenInstanciatingVariousTypeOfPath,
    FSCleanMethod,
    testing::Values(
        std::make_tuple(
            std::optional<std::string>("/tmp"),
            std::vector{
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("usr"), std::optional<std::size_t>()),
            },
            fs::Status::OK,
            fs::Path{"/usr"}
        ),
        std::make_tuple(
            std::optional<std::string>("/tmp"),
            std::vector{
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string("usr"), std::optional<std::size_t>()),
            },
            fs::Status::OK,
            fs::Path{"/usr"}
        ),
        std::make_tuple(
            std::optional<std::string>(),
            std::vector{
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string("usr"), std::optional<std::size_t>()),
            },
            fs::Status::OK,
            fs::Path{"../usr"}
        ),
        std::make_tuple(
            std::optional<std::string>("/usr/aaa/bbb"),
            std::vector{
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string("ccc"), std::optional<std::size_t>()),
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("ddd"), std::optional<std::size_t>()),
            },
            fs::Status::OK,
            fs::Path{"/usr/ddd"}
        ),
        std::make_tuple(
            std::optional<std::string>("../usr/aaa/bbb"),
            std::vector{
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string(".."), std::optional<std::size_t>()),
                std::make_pair(std::string("."), std::optional<std::size_t>()),
                std::make_pair(std::string("ccc"), std::optional<std::size_t>()),
            },
            fs::Status::OK,
            fs::Path{"../ccc"}
        ),
        std::make_tuple(
            std::optional<std::string>("../usr/aaa/bbb"),
            std::vector{
                std::make_pair(std::string("ooo"), std::optional<std::size_t>(0)),
                std::make_pair(std::string("ddd"), std::optional<std::size_t>(0)),
            },
            fs::Status::OK,
            fs::Path{"ddd/usr/aaa/bbb"}
        )
    )
);

using GetEntryMethodParam = std::tuple<
    std::optional<std::string>, // original path
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
    bool, // whether to clean the path
    std::vector<std::pair<std::optional<fs::Entry_t>, std::optional<std::size_t>>> // expected entries to given indices
>;

class FSGetEntryMethod : public ::testing::TestWithParam<GetEntryMethodParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSGetEntryMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
            cleanIfNeeded(_instances, std::get<2>(GetParam()));
        }
};

TEST_P(FSGetEntryMethod, ReturnsGivenEntries) {
    for (const fs::Path &path : _instances) {
        for (const auto &[entry, index] : std::get<3>(GetParam())) {
            if (index.has_value())
                EXPECT_EQ(path.getEntry(index.value()), entry);
            else
                EXPECT_EQ(path.getEntry(), entry);
        }
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGiveExpectingnExistingEntries,
    FSGetEntryMethod,
    testing::Values(
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>("tmp"), std::optional<std::size_t>(0)),
                std::make_pair(std::optional<fs::Entry_t>("user"), std::optional<std::size_t>(1))
            }
        ),
    
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            false,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>("tmp"), std::optional<std::size_t>(0)),
                std::make_pair(std::optional<fs::Entry_t>("user"), std::optional<std::size_t>(1)),
                std::make_pair(std::optional<fs::Entry_t>("ccc"), std::optional<std::size_t>(2)),
                std::make_pair(std::optional<fs::Entry_t>("index.html"), std::optional<std::size_t>())
            }
        ),

        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            true,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>("tmp"), std::optional<std::size_t>(0)),
                std::make_pair(std::optional<fs::Entry_t>("user"), std::optional<std::size_t>(1)),
                std::make_pair(std::optional<fs::Entry_t>("index.html"), std::optional<std::size_t>())
            }
        ),

        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("aaa", std::optional<std::size_t>(2)),
                std::make_pair("bbb", std::optional<std::size_t>(2)),
                std::make_pair("index.html", std::optional<std::size_t>())
            },
            true, // once cleaned, path should be bbb/aaa/index.html
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>("bbb"), std::optional<std::size_t>(0)),
                std::make_pair(std::optional<fs::Entry_t>("aaa"), std::optional<std::size_t>(1)),
                std::make_pair(std::optional<fs::Entry_t>("index.html"), std::optional<std::size_t>())
            }
        )
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGiveExpectingnInvalidEntries,
    FSGetEntryMethod,
    testing::Values(
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(3)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(4))
            }
        ),
    
        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(0)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(1)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(2)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>())
            }
        ),

        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>())
            },
            true,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(3)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(4)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(5))
            }
        ),

        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("aaa", std::optional<std::size_t>(2)),
                std::make_pair("bbb", std::optional<std::size_t>(2)),
                std::make_pair("index.html", std::optional<std::size_t>())
            },
            true, // once cleaned, path should be bbb/aaa/index.html
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(3)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(4)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(5))
            }
        ),

        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>()),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(1)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(2)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(3)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(4)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(5)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(6)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(6)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(7)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(8)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(8)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(9)),
                std::make_pair(std::optional<fs::Entry_t>(), std::optional<std::size_t>(10))
            }
        )
    )
);

using GetNEntryMethodParam = std::tuple<
    std::optional<std::string>, // original path
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
    bool, // whether to clean the path
    std::size_t // expected N entries
>;

class FSGetNEntryMethod : public ::testing::TestWithParam<GetNEntryMethodParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSGetNEntryMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
            cleanIfNeeded(_instances, std::get<2>(GetParam()));
        }
};

TEST_P(FSGetNEntryMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getNEntry(), std::get<3>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousEntries,
    FSGetNEntryMethod,
    testing::Values(
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            2
        ),
    
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            false,
            4
        ),

        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            false,
            5
        ),

        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            true,
            3
        ),

        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("ddd", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("aaa", std::optional<std::size_t>(2)),
                std::make_pair("bbb", std::optional<std::size_t>(2)),
                std::make_pair("index.html", std::optional<std::size_t>())
            },
            true,
            4
        ),


        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            0
        )
    )
);

using GetExtensionMethodParam = std::tuple<
    std::optional<std::string>, // original path
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
    bool, // whether to clean the path
    std::optional<std::string> // expected extension
>;

class FSGetExtensionMethod : public ::testing::TestWithParam<GetExtensionMethodParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSGetExtensionMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
            cleanIfNeeded(_instances, std::get<2>(GetParam()));
        }
};

TEST_P(FSGetExtensionMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getExtension(), std::get<3>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousEntries,
    FSGetExtensionMethod,
    testing::Values(
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            std::optional<std::string>()
        ),
    
        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            false,
            std::optional<std::string>("html")
        ),

        std::make_tuple(
            std::optional<std::string>("/tmp/user"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("index.ftp--zeraaa", std::optional<std::size_t>()),
            },
            false,
            std::optional<std::string>("ftp--zeraaa")
        ),

        std::make_tuple(
            std::optional<std::string>("aaa//////bbb/ddd/eeee///"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("index.html", std::optional<std::size_t>()),
            },
            true,
            std::optional<std::string>("html")
        ),

        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{
                std::make_pair("ccc", std::optional<std::size_t>()),
                std::make_pair("ddd", std::optional<std::size_t>()),
                std::make_pair("..", std::optional<std::size_t>()),
                std::make_pair("aaa", std::optional<std::size_t>(2)),
                std::make_pair("bbb", std::optional<std::size_t>(2)),
                std::make_pair("index", std::optional<std::size_t>())
            },
            true,
            std::optional<std::string>()
        ),


        std::make_tuple(
            std::optional<std::string>(),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            false,
            std::optional<std::string>()
        )
    )
);

