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
    FileUtil() {}

    ~FileUtil() {}

    bool PathExists(const std::string path) {
        bool exist = true;
        struct stat info;
        if (stat(path.c_str(), &info) != 0)
            exist = false;

        return exist;
    }

    bool IsDir(const std::string path) {
        bool result = false;
        struct stat info;
        if (stat(path.c_str(), &info) != 0) {
            result = false;
        } else if (info.st_mode & S_IFDIR) {
            result = true;
        }
        return result;
    }

    bool IsFile(const std::string path) {
        bool result = false;
        struct stat info;
        if (stat(path.c_str(), &info) != 0) {
            result = false;
        } else if (info.st_mode & S_IFREG) {
            result = true;
        }
        return result;
    }

    std::map<std::string, std::vector<std::string>> 
        RecursiveDirAll(const std::string dirname) {
        std::map<std::string, std::vector<std::string>> results;
        std::vector<std::string> subs = ListDir(dirname);
        results[dirname] = subs;
        for (auto item : subs) {
            auto full_sub_path = Join(dirname, item);
            if (IsDir(full_sub_path)) {
                std::map<std::string, std::vector<std::string>> res = 
                                                 RecursiveDirAll(full_sub_path);
                results.insert(res.begin(), res.end());
            }
        }
        
        return results;
    }

    std::vector<std::string> ListDir(const std::string dirname) {
        std::vector<std::string> results = list_dir(dirname, false);
        return results;
    }

    std::vector<std::string> ListDirAll(const std::string dirname) {
        std::vector<std::string> results = list_dir(dirname, true);
        return results;
    }

    std::string Join(const std::string prepath, const std::string subpath) {
        std::string path;
        path = prepath + "/" + subpath;
        replace(path, "//", "/");
        if (!PathExists(path)) {
            std::cout << "path join result: " << path 
                      << " is abnormal." << std::endl;
            path = "";
        }
        return path;
    }

    std::string Find(const std::string root, const std::string object) {
        std::string path{""};
        if (IsDir(root)) {
            std::vector<std::string> paths = ListDirAll(root);
            for (auto item : paths) {
                if (item == object) {
                    path = Join(root, object);
                    break;
                }
            }
        } else {
            std::cout << "cd " << root << " failed" << std::endl;
        }
        return path;
    }

    std::string GetContent(const std::string path) {
        std::string content{""};
        if (IsFile(path)) {
            std::ifstream ifs(path, std::ios::in);
            if (!ifs.is_open()) {
                std::cout << "open " << path << " failed." << std::endl;
                return content;
            }
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            content = buffer.str();
            ifs.close();
        } else {
            std::cout << path << " is unreadable." << std::endl;
        }
        return content;
    }

    long GetSize(const std::string path) {
        long filesize(0);

        if (IsFile(path)) {
            std::ifstream ifs(path, std::ios::in);
            filesize = ifs.rdbuf()->pubseekoff(0, std::ios::end, std::ios::in);
            // filesize = ifs.tellg();
            ifs.close();
            std::cout << filesize << std::endl;
            filesize = (filesize == -1) ? 0 : filesize;
        } else {
            std::cout << "can not get " << path << " size." << std::endl;
        }
        return filesize;
    }

private:

    std::int16_t replace(std::string& raw_str, const std::string oldvalue, 
                                               const std::string newvalue) {
        std::int16_t result{0};

        while(raw_str.find(oldvalue) != std::string::npos) {
            int pos = raw_str.find(oldvalue);
            raw_str.replace(pos, oldvalue.size(), newvalue);
        }
        return result;
    }

    bool startswith(const std::string raw_str, const std::string prefix) {
        bool res = true;
        int pos = raw_str.find(prefix);
        if (pos != 0) {
            res = false;
        }
        return res;
    }

    std::vector<std::string> list_dir(const std::string dirname, bool all) {
        std::vector<std::string> results;
        DIR * dirp = opendir(dirname.c_str());
        dirent * dp = NULL;
        int len = dirname.size();
        while ((dp = readdir(dirp)) != NULL) {
            std::string d_name = dp->d_name;
            if (all) {
                results.push_back(d_name);
            } else if (!startswith(d_name, ".")) {
                results.push_back(d_name);
            }
            if (strlen(dp->d_name) == len && 
                strcmp(dp->d_name, dirname.c_str()) == 0) {
                closedir(dirp);
                break;
            }
        }
        closedir(dirp);
        return results;
    }

    std::string raw_string_;

};
#endif