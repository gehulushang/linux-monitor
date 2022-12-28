#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

class FileUtil {
public:
    FileUtil();

    ~FileUtil();

    bool PathExists(const std::string path);

    bool IsDir(const std::string path);

    bool IsFile(const std::string path);

    std::map<std::string, std::vector<std::string>> 
        RecursiveDirAll(const std::string dirname);

    std::vector<std::string> ListDir(const std::string dirname);

    std::vector<std::string> ListDirAll(const std::string dirname);

    std::string Join(const std::string prepath, const std::string subpath);

    std::string Find(const std::string root, const std::string object);

    std::string GetContent(const std::string path);

    long GetSize(const std::string path);

private:
    std::string raw_string_;

    std::int16_t replace(std::string& raw_str, const std::string oldvalue, 
                                               const std::string newvalue);

    bool startswith(const std::string raw_str, const std::string prefix);

    std::vector<std::string> list_dir(const std::string dirname, bool all);

};
#endif