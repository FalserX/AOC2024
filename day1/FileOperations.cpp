#include "FileOperations.h"
#include <fstream>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

FileOperations::FileOperations()
{
}

FileOperations::~FileOperations()
{
}

const std::tuple<vector<string>, vector<string>, FileOperations::FILE_OPERATIONS_FLAGS> FileOperations::getDataFormatted(const std::string &filePath)
{
    vector<std::string> v1;
    vector<std::string> v2;
    std::tuple<vector<string>, vector<string>, FileOperations::FILE_OPERATIONS_FLAGS> result =
        make_tuple(v1, v2, FileOperations::FILE_OPERATIONS_FLAGS::ERROR_FILE_NOT_EXISTS);
    ifstream file;
    file.open(filePath);
    if (file.is_open())
    {
        string line;
        string delim = " ";
        string elem1;
        string elem2;
        while (getline(file, line))
        {
            vector<std::string> words = split(line, delim);

            v1.push_back(words.at(0));
            v2.push_back(words.at(1));
            words.clear();
        }

        result = make_tuple(v1, v2, FileOperations::FILE_OPERATIONS_FLAGS::SUCCESS);
    }
    file.close();
    return result;
}

const std::vector<std::string> FileOperations::split(const std::string &s, const std::string &delimiter)
{
    std::string currentString = s;
    std::vector<std::string> stringCharacters;
    size_t pos_end = currentString.length();
    std::string currentCharacters;

    while ((pos_end = currentString.find(delimiter)) != std::string::npos)
    {
        currentCharacters = currentString.substr(0, pos_end);
        if (currentCharacters != delimiter && currentCharacters != "")
        {
            stringCharacters.push_back(currentCharacters);
            currentString.erase(0, currentCharacters.length());
            currentCharacters.clear();
        }
        else
        {
            currentString.erase(0, pos_end + 1);
        }
    }
    if (currentString.find("\r") != std::string::npos)
    {
        currentString.erase(currentString.find("\r"));
    }
    stringCharacters.push_back(currentString);
    return stringCharacters;
}