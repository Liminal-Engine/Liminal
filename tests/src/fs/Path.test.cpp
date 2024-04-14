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
#include <filesystem>

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

using FSPathInsertParam = std::tuple<
    std::optional<std::string>, // path to build instances from, if has no value, constructor fs::Path{} will be used
    fs::Entry_t, // add entry ...
    std::optional<std::size_t>, // to the wanted optional positions
    fs::Status // expected return status
>;
class FSPathInsertMethod : public ::testing::TestWithParam<FSPathInsertParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathInsertMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {}
};

TEST_P(FSPathInsertMethod, ReturnGivenStatus) {
    fs::Entry_t entry{std::get<1>(GetParam())};
    std::optional<std::size_t> pos{std::get<2>(GetParam())};

    for (fs::Path &path : _instances) {
        if (pos.has_value()) EXPECT_EQ(path.insert(entry, pos.value()), std::get<3>(GetParam()));
        else EXPECT_EQ(path.insert(entry), std::get<3>(GetParam()));
    }
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidEntriesAtValidPos,
    FSPathInsertMethod,
    testing::Values(
        std::make_tuple("/tmp", ".", 1, fs::Status::OK),
        std::make_tuple("/tmp", "/etc", 0, fs::Status::OK),
        std::make_tuple("/aaa/bbb", "/ccc", 0, fs::Status::OK),
        std::make_tuple("/aaa/bbb", "ccc", 1, fs::Status::OK),
        std::make_tuple("/aaa/bbb", "ccc", 2, fs::Status::OK),
        std::make_tuple(std::nullopt, "aaa", std::nullopt, fs::Status::OK),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 2, fs::Status::OK),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 1, fs::Status::OK),
        std::make_tuple("/tmp_oojopjop99---/bbb", "/Проекты", 0, fs::Status::OK),
        std::make_tuple("/home/user", "documents", 0, fs::Status::OK),
        std::make_tuple("/var/log", "syslog", 1, fs::Status::OK),
        std::make_tuple("/usr/local", "bin", 2, fs::Status::OK),
        std::make_tuple("/etc", "/passwd", 0, fs::Status::OK),
        std::make_tuple(std::nullopt, "root", std::nullopt, fs::Status::OK),
        std::make_tuple("/opt/software", "config", 1, fs::Status::OK),
        std::make_tuple("/usr/share", "locale", 0, fs::Status::OK),
        std::make_tuple("/lib/modules", "kernel", 2, fs::Status::OK),
        std::make_tuple("/srv/http", "public_html", 1, fs::Status::OK),
        std::make_tuple("/home/user", "Downloads", 0, fs::Status::OK),
        std::make_tuple("/var/www", "html", 1, fs::Status::OK),
        std::make_tuple("/usr/lib", "/python3.8", 2, fs::Status::OK),
        std::make_tuple("/etc/systemd", "system", 0, fs::Status::OK),
        std::make_tuple(std::nullopt, "etc", std::nullopt, fs::Status::OK),
        std::make_tuple("/tmp/complex-dir-name", "subdir", 1, fs::Status::OK),
        std::make_tuple("usrlocal", "include", 1, fs::Status::OK),
        std::make_tuple("/etc", "hosts", 1, fs::Status::OK),
        std::make_tuple("/var/log", "messages", 2, fs::Status::OK),
        std::make_tuple("/usr/share", "/fonts", 0, fs::Status::OK),
        std::make_tuple("/lib/modules", "module1", 1, fs::Status::OK),
        std::make_tuple("/srv/http", "index.html", 1, fs::Status::OK),
        std::make_tuple("/home/user", "Pict          ures", 0, fs::Status::OK),
        std::make_tuple("/var/www", "index.php", 1, fs::Status::OK),
        std::make_tuple("/usr/lib", "lib1", 2, fs::Status::OK),
        std::make_tuple("/etc/systemd", "service1", 0, fs::Status::OK),
        std::make_tuple("/tmp/complex-dir-name", "/subdir2", 2, fs::Status::OK),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 2, fs::Status::OK),
        std::make_tuple(std::nullopt, ".entry1", std::nullopt, fs::Status::OK),
        std::make_tuple("/path/to/directory", ".entry2", std::nullopt, fs::Status::OK),
        std::make_tuple(std::nullopt, "/entry3", 0, fs::Status::OK),
        std::make_tuple("/path/to/directory", "..entry4", 1, fs::Status::OK),
        std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", 10, fs::Status::OK),
        std::make_tuple("/path/to/directory", "entry9", 1, fs::Status::OK),
        std::make_tuple("/path/to/directory", "entry10", 2, fs::Status::OK),
        std::make_tuple("/path/to/directory", "entry11", 3, fs::Status::OK),
        std::make_tuple("./var/log", "messages", 2, fs::Status::OK),
        std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", 2, fs::Status::OK),
        std::make_tuple("./../usr/share", "/...ezrrete        rtert-----reteezrz.errte", 2, fs::Status::OK),
        std::make_tuple("../lib/modules", "module1", std::nullopt, fs::Status::OK),
        std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", 0, fs::Status::OK),
        std::make_tuple("srv/http", "index.html", 1, fs::Status::OK),
        std::make_tuple("home/user", "Pictures", 0, fs::Status::OK),
        std::make_tuple("/lib/modules", "/kernel", 2, fs::Status::OK)

    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenInvalidEntriesAtValidPos,
    FSPathInsertMethod,
    testing::Values(
        std::make_tuple("/tmp", "et/c", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/aaa/bbb", "c\\cc", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/aaa/bbb", "cc\"c", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/aaa/bbb", "cc><c", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "a*aa", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "a*aa", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Пр/оекты", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/home/user", "documen<>ts", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/log", "/s\\y<s>l\"o   -|g", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/local", "b*in", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc", "pas|swd", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "r&oot", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/opt/software", "/\\<>:\"|*&~", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/srv/http", "public_htm:l", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/home/user", "Downlo:ads", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/www", "ht/ml", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/lib", "python3:8", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc/systemd", "s|y/s/t&em", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "et<>><c", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "subdi//r", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("usrlocal", "i:\"/nclude", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc", "hosts*", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/log", "me<>ssages", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/share", "fo|?*&nts", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/lib/modules", "mo/////dule1", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/srv/http", "/index:html", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/home/user", "Pictu****res", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/var/www", "index*php", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/lib/modules", "//kernel", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/lib/modules", "//ker/nel", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/usr/lib", "lib:1", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/etc/systemd", "ser//vice1", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "s/ubdir2", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "//subdir2", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/tmp/complex-dir-name", "//su/bdir2", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "en:::try1", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "e**ntry2", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple(std::nullopt, "entr~~~~~y3", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "~.entry4", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", ":entry5", 10, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "entry|9", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "entry|10", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("/path/to/directory", "entry|11", 3, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("./var/log", "mess>>ages", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("./../usr/share", "...ezrretertert-----reteezrz.errte/", 2, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("../lib/modules", "//module1", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("../lib/modules", "module1/", std::nullopt, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("../lib/modules", "..:.aaa.bbb.c.d.e.s.f.e.q.z.er.", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("srv/http", "/index~html", 1, fs::Status::E_PATH_INVALID_ENTRY_NAME),
        std::make_tuple("home/user", "Pictures&", 0, fs::Status::E_PATH_INVALID_ENTRY_NAME)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidEntriesAtInvalidPos,
    FSPathInsertMethod,
    testing::Values(
        std::make_tuple("/tmp", "etc", 10, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/aaa/bbb", "ccc", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/aaa/bbb", "ccc", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/aaa/bbb", "ccc", 6, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/share", "locale/", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple(std::nullopt, "aaa", 1, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/home/user", "documents", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/var/log", "syslog", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/local", "bin", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/etc", "passwd", 3, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/opt/software", "config", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/share", "locale", 10, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/lib/modules", "kernel", 202, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/srv/http", "public_html", 1000, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/home/user", "Downloads", 40, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/var/www", "html", 105, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/lib", "python3.8", 55, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/etc/systemd", "system", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/tmp/complex-dir-name", "subdir", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/local", "include", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/etc", "hosts", 3, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/var/log", "messages", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/share", "fonts", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/lib/modules", "module1", 10, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/srv/http", "index.html", 10, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/home/user", "Pict          ures", 120, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/var/www", "index.php", 10, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/usr/lib", "lib1", 20, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/etc/systemd", "service1", 50, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 20, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/tmp/complex-dir-name", "subdir2", 20, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple(std::nullopt, ".entry1", 40, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", ".entry2", 78, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple(std::nullopt, "entry3", 2, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", "..entry4", 10, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", 12, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("path/to/directory", "entry9", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", "entry10", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("/path/to/directory", "entry11", 6, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("./var/log", "messages", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", 6, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("../lib/modules", "module1", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", 5, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("srv/http", "index.html", 4, fs::Status::E_PATH_INVALID_INDEX),
        std::make_tuple("home/user", "Pictures", 4, fs::Status::E_PATH_INVALID_INDEX)
    )
);

using FSPathCleanParam = std::tuple<
    std::optional<std::string>, // path to build instances from, if has no value, constructor fs::Path{} will be used
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // optional vector of entry to add to given optional indices
    fs::Status, // expected return status
    fs::Path // expected Path result
>;
class FSPathCleanMethod : public ::testing::TestWithParam<FSPathCleanParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathCleanMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
        }
};

TEST_P(FSPathCleanMethod, ReturnGivenStatusAndProduceGivenPath) {
    for (fs::Path &path : _instances) {
        EXPECT_EQ(path.clean(), std::get<2>(GetParam()));
        EXPECT_TRUE(path == std::get<3>(GetParam()));
    }
}

INSTANTIATE_TEST_SUITE_P(
    WhenInstanciatingVariousTypeOfPath,
    FSPathCleanMethod,
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
                std::make_pair(std::string("/ddd"), std::optional<std::size_t>(0)),
            },
            fs::Status::OK,
            fs::Path{"/ddd/usr/aaa/bbb"}
        ),
        std::make_tuple(
            std::optional<std::string>("/"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            fs::Status::OK,
            fs::Path{"/"}
        ),
        std::make_tuple(
            std::optional<std::string>("////////////////////////////////////////////////"),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            fs::Status::OK,
            fs::Path{"/"}
        ),
        std::make_tuple(
            std::optional<std::string>(""),
            std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>{},
            fs::Status::OK,
            fs::Path{}
        )
    )
);

using FSPathGetEntryParam = std::tuple<
    std::optional<std::string>, // original path
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
    bool, // whether to clean the path
    std::vector<std::pair<std::optional<fs::Entry_t>, std::optional<std::size_t>>> // expected entries to given indices
>;

class FSPathGetEntryMethod : public ::testing::TestWithParam<FSPathGetEntryParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathGetEntryMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
            cleanIfNeeded(_instances, std::get<2>(GetParam()));
        }
};

TEST_P(FSPathGetEntryMethod, ReturnsGivenEntries) {
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
    FSPathGetEntryMethod,
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
                std::make_pair("/aaa", std::optional<std::size_t>(0)),
            },
            false,
            std::vector{
                std::make_pair(std::optional<fs::Entry_t>("aaa"), std::optional<std::size_t>(0)),
                std::make_pair(std::optional<fs::Entry_t>("tmp"), std::optional<std::size_t>(1)),
                std::make_pair(std::optional<fs::Entry_t>("user"), std::optional<std::size_t>(2)),
                std::make_pair(std::optional<fs::Entry_t>("ccc"), std::optional<std::size_t>(3)),
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
    FSPathGetEntryMethod,
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

using FSPathGetNEntryParam = std::tuple<
    std::optional<std::string>, // original path
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
    bool, // whether to clean the path
    std::size_t // expected N entries
>;

class FSPathGetNEntryMethod : public ::testing::TestWithParam<FSPathGetNEntryParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathGetNEntryMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
            cleanIfNeeded(_instances, std::get<2>(GetParam()));
        }
};

TEST_P(FSPathGetNEntryMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getNEntry(), std::get<3>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousEntries,
    FSPathGetNEntryMethod,
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
                std::make_pair("/ddd", std::optional<std::size_t>(0)),
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

using FSPathGetExtensionParam = std::tuple<
    std::optional<std::string>, // original path
    std::vector<std::pair<fs::Entry_t, std::optional<std::size_t>>>, // entries to add,
    bool, // whether to clean the path
    std::optional<std::string> // expected extension
>;

class FSPathGetExtensionMethod : public ::testing::TestWithParam<FSPathGetExtensionParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathGetExtensionMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
            addEntries(_instances, std::get<1>(GetParam()));
            cleanIfNeeded(_instances, std::get<2>(GetParam()));
        }
};

TEST_P(FSPathGetExtensionMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getExtension(), std::get<3>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousEntries,
    FSPathGetExtensionMethod,
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


using FSPathGetTypeParam = std::tuple<
    std::string, // original path string to build from
    fs::Entry::Type // expected result
>;

class FSPathGetTypeMethod : public ::testing::TestWithParam<FSPathGetTypeParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathGetTypeMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathGetTypeMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getType(), std::get<1>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathGetTypeMethod,
    testing::Values(
        std::make_tuple("../../tests/assets/fs/.hidden", fs::Entry::Type::REGULAR_FILE),
        std::make_tuple("../../tests/assets/fs/!@#$%^&*().!@#$%^&*()", fs::Entry::Type::REGULAR_FILE),
        std::make_tuple("../../tests/assets/json/valid/basic.json", fs::Entry::Type::REGULAR_FILE),
        std::make_tuple("../../tests/assets/fs/|||empty|||", fs::Entry::Type::REGULAR_FILE),
        std::make_tuple("../../tests/assets/fs/", fs::Entry::Type::DIRECTORY),
        std::make_tuple("../../tests/assets/fs", fs::Entry::Type::DIRECTORY),
        std::make_tuple("../../tests/assets/json/", fs::Entry::Type::DIRECTORY),
        std::make_tuple("../../tests/assets/json/valid", fs::Entry::Type::DIRECTORY),
        std::make_tuple("../../tests/assets/json/invalid/", fs::Entry::Type::DIRECTORY),
        std::make_tuple("./I/DO/no/exists", fs::Entry::Type::UNKNOWN),
        std::make_tuple("../../tests/assets/fs/sym_link", fs::Entry::Type::SYM_LINK),
        std::make_tuple("../../tests/assets/fs/ImABlockDevice", fs::Entry::Type::BLOCK_DEVICE), // FIXME : may work only on Linux
        std::make_tuple("../../tests/assets/fs/ImACharDevice", fs::Entry::Type::CHARACTER_DEVICE), // FIXME : may work only on Linux
        std::make_tuple("../../tests/assets/fs/ImAFifo", fs::Entry::Type::FIFO), // TODO : check if works on Windows
        std::make_tuple("", fs::Entry::Type::UNKNOWN),
        std::make_tuple("/", fs::Entry::Type::DIRECTORY),
        std::make_tuple("/path/with spaces", fs::Entry::Type::UNKNOWN),
        std::make_tuple("/path/with!@#$%^&*()_+special", fs::Entry::Type::UNKNOWN),        
        std::make_tuple("/" + std::string(10000, 'a'), fs::Entry::Type::UNKNOWN),
        std::make_tuple("/path/with/trailing/slashes////", fs::Entry::Type::UNKNOWN),        
        std::make_tuple(".", fs::Entry::Type::DIRECTORY),
        std::make_tuple("..", fs::Entry::Type::DIRECTORY),
        std::make_tuple("...", fs::Entry::Type::UNKNOWN),
        std::make_tuple("....", fs::Entry::Type::UNKNOWN),
        std::make_tuple("/path/with\\mixed/separators", fs::Entry::Type::UNKNOWN),
        std::make_tuple("..///..///tests///assets///fs///!@#$%^&*().!@#$%^&*()", fs::Entry::Type::REGULAR_FILE),
        std::make_tuple("././././.", fs::Entry::Type::DIRECTORY),
        std::make_tuple("./. . /./ . ", fs::Entry::Type::UNKNOWN),
        // Edge case: Path containing special device names (may work only on Windows) // FIXME?
        std::make_tuple("CON", fs::Entry::Type::UNKNOWN),
        std::make_tuple("PRN", fs::Entry::Type::UNKNOWN),
        std::make_tuple("/path/with/very/long/name/that/is/very/super/super//////long//////", fs::Entry::Type::UNKNOWN)
    )
);

using FSPathIsEmptyParam = std::tuple<
    std::string, // original path string to build from
    bool // expected result
>;

class FSPathIsEmptyMethod : public ::testing::TestWithParam<FSPathIsEmptyParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathIsEmptyMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathIsEmptyMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.isEmpty(), std::get<1>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathIsEmptyMethod,
    testing::Values(
        std::make_tuple("../../tests/assets/fs/.hidden", false),
        std::make_tuple("./I/DO/no/exists", false),
        std::make_tuple("/path/to/non_empty_file.txt", false),
        std::make_tuple("/path/to/non_empty_dir", false),
        std::make_tuple("/path/to/non_empty_dir/", false),
        std::make_tuple("", true),
        std::make_tuple("./", false),
        std::make_tuple(".", false),
        std::make_tuple("..", false),
        std::make_tuple(".3/", false)
    )
);

using FSPathGetParentParam = std::tuple<
    std::string, // original path string to build from
    std::optional<fs::Path> // expected result
>;

class FSPathGetParentMethod : public ::testing::TestWithParam<FSPathGetParentParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathGetParentMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathGetParentMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getParent(), std::get<1>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathGetParentMethod,
    testing::Values(
        std::make_tuple("../../tests/assets/fs/.hidden", std::optional<fs::Path>{"../../tests/assets/fs/"}),
        std::make_tuple("../../tests/assets/fs/.hidden", std::optional<fs::Path>{"../../tests/assets/fs"}),
        std::make_tuple("./I/DO/no/exists", std::optional<fs::Path>{"./I/DO/no"}),
        std::make_tuple("/path/to/non_empty_file.txt", std::optional<fs::Path>{"/path/to"}),
        std::make_tuple("/a/b/c/d/e/f/g/h", std::optional<fs::Path>{"/a/b/c/d/e/f/g"}),
        std::make_tuple("..////.//a/b/c/d/e/f/g/h", std::optional<fs::Path>{"..////.//a/b/c/d/e/f/g/"}),
        std::make_tuple("..////.//a/b/c/d/e/f/g/h", std::optional<fs::Path>{"..////.//a/b/c/d/e/f/g"}), // they are not thge same, last one does not have '/' at the end of expected result
        std::make_tuple("", std::optional<fs::Path>{}),
        std::make_tuple("./", std::optional<fs::Path>{}),
        std::make_tuple("/", std::optional<fs::Path>{}),
        std::make_tuple("..", std::optional<fs::Path>{}),
        std::make_tuple("../..", std::optional<fs::Path>{".."}),
        std::make_tuple("/rootfile.txt", std::optional<fs::Path>{}),
        std::make_tuple("/path/with spaces/file.txt", std::optional<fs::Path>{"/path/with spaces"}),
        std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", std::optional<fs::Path>{"/path/with!@#$%^&*()_+special"})
    )
);

using FSPathGetResolutionParam = std::tuple<
    std::string, // original path string to build from
    fs::Path::Resolution // expected result
>;

class FSPathGetResolutionMethod : public ::testing::TestWithParam<FSPathGetResolutionParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathGetResolutionMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathGetResolutionMethod, ReturnsGivenValue) {
    for (const fs::Path &path : _instances) {
        EXPECT_EQ(path.getResolution(), std::get<1>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathGetResolutionMethod,
    testing::Values(
        std::make_tuple("../../tests/assets/fs/.hidden", fs::Path::Resolution::RELATIVE),
        std::make_tuple("../../tests/assets/fs/.hidden", fs::Path::Resolution::RELATIVE),
        std::make_tuple("./I/DO/no/exists", fs::Path::Resolution::RELATIVE),
        std::make_tuple("/path/to/non_empty_file.txt", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("/a/b/c/d/e/f/g/h", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("..////.//a/b/c/d/e/f/g/h", fs::Path::Resolution::RELATIVE),
        std::make_tuple("..////.//a/b/c/d/e/f/g/h", fs::Path::Resolution::RELATIVE),
        std::make_tuple("", fs::Path::Resolution::RELATIVE),
        std::make_tuple("./", fs::Path::Resolution::RELATIVE),
        std::make_tuple("/", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("..", fs::Path::Resolution::RELATIVE),
        std::make_tuple("../..", fs::Path::Resolution::RELATIVE),
        std::make_tuple("/rootfile.txt", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("/path/with spaces/file.txt", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("/path/with/trailing/slashes////", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("/path/with\\mixed/separators", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("//path//with//consecutive//slashes", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple(".", fs::Path::Resolution::RELATIVE),
        std::make_tuple("..", fs::Path::Resolution::RELATIVE),
        std::make_tuple("...", fs::Path::Resolution::RELATIVE),
        std::make_tuple("....", fs::Path::Resolution::RELATIVE),
        std::make_tuple("././././.", fs::Path::Resolution::RELATIVE),
        std::make_tuple("./. . /./ . ", fs::Path::Resolution::RELATIVE),
        std::make_tuple("TEST123", fs::Path::Resolution::RELATIVE),
        std::make_tuple("KODEROZP", fs::Path::Resolution::RELATIVE),
        std::make_tuple("/path/with/very/long/name/that/exceeds/system/limits", fs::Path::Resolution::ABSOLUTE),
        std::make_tuple("./path/with!@#$%^&*()_+special/characters", fs::Path::Resolution::RELATIVE),
        std::make_tuple("./path/with spaces", fs::Path::Resolution::RELATIVE),
        std::make_tuple("./.", fs::Path::Resolution::RELATIVE),
        std::make_tuple("../.", fs::Path::Resolution::RELATIVE),
        std::make_tuple("//", fs::Path::Resolution::ABSOLUTE)
    )
);

using FSPathToAbsoluteParam = std::tuple<
    std::string, // original path string to build from
    fs::Path, // expected new path
    fs::Status // expected returned status
>;

class FSPathToAbsoluteMethod : public ::testing::TestWithParam<FSPathToAbsoluteParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathToAbsoluteMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathToAbsoluteMethod, HasExpectedBehavior) {
    for (fs::Path &path : _instances) {
        EXPECT_EQ(path.toAbsolute(), std::get<2>(GetParam()));
        EXPECT_EQ(path, std::get<1>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathToAbsoluteMethod,
    testing::Values(
        std::make_tuple("./bin", fs::Path(std::filesystem::current_path().string() + std::string("/./bin")), fs::Status::OK),
        std::make_tuple("../../tests/assets/fs/.hidden", fs::Path(std::filesystem::current_path().string() + std::string("/../../tests/assets/fs/.hidden")), fs::Status::OK),
        std::make_tuple("./IDontExists", fs::Path(std::filesystem::current_path().string() + std::string("/./IDontExists")), fs::Status::OK),
        std::make_tuple("./../../tests/assets/fs/.hidden", fs::Path(std::filesystem::current_path().string() + std::string("/./../../tests/assets/fs/.hidden")), fs::Status::OK),
        std::make_tuple("./I/DO/no/exists", fs::Path(std::filesystem::current_path().string() + std::string("/./I/DO/no/exists")), fs::Status::OK),
        std::make_tuple("/path/to/non_empty_file.txt", fs::Path(std::string("/////path/to///non_empty_file.txt")), fs::Status::OK),
        std::make_tuple("/a/b/c/d/e/f/g/h", fs::Path(std::string("/a/b/c/d/e/f/g/h")), fs::Status::OK),
        std::make_tuple("..////.//a/b/c/d/e/f/g/h", fs::Path(std::filesystem::current_path().string() + std::string("/..////.//a/b/c/d/e/f/g/h")), fs::Status::OK),
        std::make_tuple("..////.//a/b/c/d/e/f/g/h", fs::Path(std::filesystem::current_path().string() + std::string("/..////.//a/b/c/d/e/f/g/h")), fs::Status::OK),
        std::make_tuple("", fs::Path(std::string("")), fs::Status::E_PATH_EMPTY),
        std::make_tuple("./", fs::Path(std::filesystem::current_path().string() + std::string("/./")), fs::Status::OK),
        std::make_tuple("..", fs::Path(std::filesystem::current_path().string() + std::string("/..")), fs::Status::OK),
        std::make_tuple("../..", fs::Path(std::filesystem::current_path().string() + std::string("/../..")), fs::Status::OK),
        std::make_tuple("../.", fs::Path(std::filesystem::current_path().string() + std::string("/../.")), fs::Status::OK),
        std::make_tuple("/rootfile.tx", fs::Path(std::string("/rootfile.tx")), fs::Status::OK),
        std::make_tuple("/path/with spaces/file.txt", fs::Path(std::string("/path/with spaces/file.txt")), fs::Status::OK),
        std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", fs::Path(std::string("/path/with!@#$%^&*()_+special/file.txt")), fs::Status::OK),
        std::make_tuple("/path/with/trailing/slashes////", fs::Path(std::string("/path/with/trailing/slashes////")), fs::Status::OK),
        std::make_tuple(".", fs::Path(std::filesystem::current_path().string() + std::string("/.")), fs::Status::OK),
        std::make_tuple("././././.", fs::Path(std::filesystem::current_path().string() + std::string("/././././.")), fs::Status::OK),
        std::make_tuple("TEST123", fs::Path(std::filesystem::current_path().string() + std::string("/TEST123")), fs::Status::OK),
        std::make_tuple("KODEROZP", fs::Path(std::filesystem::current_path().string() + std::string("/KODEROZP")), fs::Status::OK),
        std::make_tuple("path/with/very/long/name/that/exceeds/system/limits", fs::Path(std::filesystem::current_path().string() + std::string("/path/with/very/long/name/that/exceeds/system/limits")), fs::Status::OK),
        std::make_tuple("./path/with!@#$%^&*()_+special/characters", fs::Path(std::filesystem::current_path().string() + std::string("/./path/with!@#$%^&*()_+special/characters")), fs::Status::OK),
        std::make_tuple("../path/with!@#$%^&*()_+special/characters", fs::Path(std::filesystem::current_path().string() + std::string("/../path/with!@#$%^&*()_+special/characters")), fs::Status::OK),
        std::make_tuple("./path/with spaces", fs::Path(std::filesystem::current_path().string() + std::string("/./path/with spaces")), fs::Status::OK),
        std::make_tuple("/", fs::Path(std::string("/")), fs::Status::OK),
        std::make_tuple("//", fs::Path(std::string("//")), fs::Status::OK)
    )
);

using FSPathToRelativeParam = std::tuple<
    std::string, // original path string to build from
    fs::Path, // expected new path
    fs::Status // expected returned status
>;

class FSPathToRelativeMethod : public ::testing::TestWithParam<FSPathToRelativeParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathToRelativeMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathToRelativeMethod, HasExpectedBehavior) {
    for (fs::Path &path : _instances) {
        EXPECT_EQ(path.toRelative(), std::get<2>(GetParam()));
        EXPECT_EQ(path, std::get<1>(GetParam()));
    }
};

std::string createCleanedPathStr(const std::string &pathStr) {
    fs::Path tmp{pathStr};
    tmp.clean();
    tmp.toAbsolute();
    return tmp.toStr();
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathToRelativeMethod,
    testing::Values(
        std::make_tuple(std::filesystem::current_path().string() + "/bin", fs::Path("./bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/bin", fs::Path("bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/./bin", fs::Path("./bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/./bin", fs::Path("bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/////.//a/b/c/d/e/f/g/h", fs::Path(".//a/b/c/d/e/f/g/h"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/////.//a/b/c/d/e/f/g/h", fs::Path("a/b/c/d/e/f/g/h"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/./////.//a/b/c/d/e/f/g/h", fs::Path(".//a/b/c/d/e/f/g/h"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/./////.//a/b/c/d/e/f/g/h", fs::Path("a/b/c/d/e/f/g/h"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string(), fs::Path("."), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string(), fs::Path("./"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/../../.test123/789.abc", fs::Path("./../../.test123/789.abc"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/../../.test123/789.abc", fs::Path("../../.test123/789.abc"), fs::Status::OK),
        std::make_tuple("/home/matteo/Projects/Liminal/tests/assets/fs", fs::Path("../../tests/assets/fs/"), fs::Status::OK),
        std::make_tuple(createCleanedPathStr(std::filesystem::current_path().string() + "/../../tests/assets/fs/"), fs::Path("../../tests/assets/fs/"), fs::Status::OK),
        std::make_tuple(createCleanedPathStr(std::filesystem::current_path().string() + "/../aaa/b b.j/-n--$h/."), fs::Path("../aaa/b b.j/-n--$h/."), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "//bin", fs::Path("./bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/././bin", fs::Path("./bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/../../bin", fs::Path("../../bin"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/bin$#@", fs::Path("./bin$#@"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/bin folder", fs::Path("./bin folder"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/bin📁", fs::Path("./bin📁"), fs::Status::OK),
        std::make_tuple(std::filesystem::current_path().string() + "/../", fs::Path(".."), fs::Status::OK),
        std::make_tuple("", fs::Path(""), fs::Status::E_PATH_EMPTY)        
    )
);

using FSPathPointsToParam = std::tuple<
    std::string, // original path string to build from
    fs::Path, // other path
    bool, // wether to clean path
    bool // expected returned status
>;

class FSPathPointsToMethod : public ::testing::TestWithParam<FSPathPointsToParam> {
    protected:
        std::vector<fs::Path> _instances;

        FSPathPointsToMethod(void) :
        _instances{createInstances(std::get<0>(GetParam()))}
        {
        }
};

TEST_P(FSPathPointsToMethod, HasExpectedBehavior) {
    for (fs::Path &path : _instances) {
        if (std::get<2>(GetParam())) path.clean();
        EXPECT_EQ(path.pointsTo(std::get<1>(GetParam())), std::get<3>(GetParam()));
    }
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousPaths,
    FSPathPointsToMethod,
    testing::Values(
        std::make_tuple(std::filesystem::current_path().string() + "/bin", fs::Path("./bin"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/../bin", fs::Path("../bin"), false, true),
        std::make_tuple(std::filesystem::current_path().string() + "/../bin", fs::Path("../bin"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt", fs::Path("-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt"), false, true),
        std::make_tuple(std::filesystem::current_path().string() + "/-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt", fs::Path("-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/nonexistent", fs::Path("./nonexistent"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/../nonexistent", fs::Path("../nonexistent"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/../../nonexistent", fs::Path("../../nonexistent"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/./././nonexistent", fs::Path("./nonexistent"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/./././bin", fs::Path("./bin"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/../../bin", fs::Path("../../bin"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/bin$#@", fs::Path("./bin$#@"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/bin folder", fs::Path("./bin folder"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/bin📁", fs::Path("./bin📁"), true, true),
        std::make_tuple(std::filesystem::current_path().string() + "/../", fs::Path(".."), true, true),
        std::make_tuple("/", fs::Path("/"), true, true),
        std::make_tuple("/", fs::Path("/"), false, true),
        std::make_tuple("/", fs::Path("/////"), true, true),
        std::make_tuple("/", fs::Path("/////"), false, true),
        std::make_tuple("", fs::Path(""), true, true),
        std::make_tuple("/../", fs::Path(".."), false, false),
        std::make_tuple("/../", fs::Path(".."), true, false),
        std::make_tuple("nonexistent", fs::Path("./nonexistent"), false, true),
        std::make_tuple("nonexistent", fs::Path("./nonexistent"), true, true),
        std::make_tuple("/bin$#@", fs::Path("./bin$#@"), false, false),
        std::make_tuple("/bin$#@", fs::Path("./bin$#@"), true, false),
        std::make_tuple("/bin$#@", fs::Path("./other"), true, false)
    )
);

/**
 *  TODO
 * test this PATHS on wndows : I thinkg those are special paths on windows
    std::make_tuple("CON", std::string("/CON")), fs::Status::OK),
    std::make_tuple("PRN", std::string("/PRN")), fs::Status::OK),
 * 
 */