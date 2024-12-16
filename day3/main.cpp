#include <iostream>
#include "FileOperations.h"
#include "algorithm"
#include "regex"

using namespace std;

const std::vector<std::string> split(const std::string &s, const std::string &delimiter)
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

bool isNumeric(const string &currentString)
{
    try
    {
        std::stoi(currentString);
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int multiplyResult = 0;
    FileOperations *operations = new FileOperations();

    std::tuple<vector<vector<string>>, FileOperations::FILE_OPERATIONS_FLAGS> result =
        operations->getDataFormatted("../day3/input.txt");

    if (std::get<1>(result) == FileOperations::ERROR_FILE_NOT_EXISTS)
    {
        cerr << "An error occured when opening the file. Do you have provided the correct path?" << endl;
        return -1;
    }
    else
    {
        vector<string> corrupted_memory_mem;
        vector<vector<string>> corrupted_memory = std::get<0>(result);
        for (vector<string> corrupted_memory_line : corrupted_memory)
        {
            corrupted_memory_mem.push_back(corrupted_memory_line.at(0));
        }
        for (string str : corrupted_memory_mem)
        {
            int currentMult = 0;
            std::regex rx("mul\\([[:digit:]]?[[:digit:]],[[:digit:]]?[[:digit:]]\\)");
            vector<string> currentsMult;
            vector<size_t> pos_mult;
            smatch regMatch;
            while (regex_search(str, regMatch, rx))
            {
                string match = regMatch.str(0);
                match.erase(match.find("mul("), match.find("mul(") + 4);
                match.erase(match.find(")"), match.find(")") + 1);
                vector<string> numbers = split(match, ",");
                string ddd = "";
                if (isNumeric(numbers.at(0)) && isNumeric(numbers.at(1)))
                {
                    currentMult += stoi(numbers.at(0)) * stoi(numbers.at(1));
                }
                str = regMatch.suffix().str();
            }
            multiplyResult += currentMult;
        }
        cout << "The result is " << multiplyResult << endl;
        return 0;
    }
}
