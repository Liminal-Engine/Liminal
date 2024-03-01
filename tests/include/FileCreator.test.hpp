/**
 * @file FileCreator.test.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
*/


#ifndef LIMINAL_TESTS_FILECREATOR_HPP_
#define LIMINAL_TESTS_FILECREATOR_HPP_

#include <string>

/**
 * @brief This class aims to help file creation for test purposes
 * 
*/
class FileCreator {
    public:
        FileCreator(void);
        FileCreator(const std::string &content, const std::string &fileName = "tmp");
        ~FileCreator();
        std::string getPath(void) const;
        std::string getContent(void) const;

    private:
        std::string _path;
        std::string _content;
};


#endif // LIMINAL_TESTS_FILECREATOR_HPP_
