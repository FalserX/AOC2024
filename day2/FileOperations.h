#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS
#endif // !FILE_OPERATIONS
#include <string>
#include <tuple>
#include <vector>

#pragma once

class FileOperations
{
public:
    enum FILE_OPERATIONS_FLAGS
    {
        SUCCESS = 0,
        ERROR_FILE_NOT_EXISTS = 1
    };
    FileOperations();
    ~FileOperations();
    const std::tuple<std::vector<std::vector<std::string>>, FILE_OPERATIONS_FLAGS> getDataFormatted(const std::string &filePath);

private:
    const std::vector<std::string> split(const std::string &s, const std::string &delimiter);
};