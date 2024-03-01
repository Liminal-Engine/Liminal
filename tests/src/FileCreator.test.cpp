/**
 * @file FileCreator.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "FileCreator.test.hpp"
#include "constants.test.hpp"

#include <filesystem>
#include <fstream>

// Public :
FileCreator::FileCreator(void) :
_path{""},
_content{""}
{}

FileCreator::FileCreator(const std::string &content, const std::string &fileName) :
_path{std::string{constants::TMP_FILE_DEFAULT_DIR} + std::string{fileName}},
_content{content}
{
    std::filesystem::path dirPath{std::string{constants::TMP_FILE_DEFAULT_DIR}};    
    std::filesystem::remove_all(dirPath);
    std::filesystem::create_directories(dirPath);
    std::ofstream tmpFile(this->_path);
    tmpFile << this->_content;
    tmpFile.close();
}

FileCreator::~FileCreator() {
    std::filesystem::remove_all(std::filesystem::path{std::string(constants::TMP_FILE_DEFAULT_DIR)});
    this->_path = "";
    this->_content = "";
}


std::string FileCreator::getPath(void) const { return this->_path; }
std::string FileCreator::getContent(void) const { return this->_content; }