#include <iostream>
#include "FileOperations.h"
#include <algorithm>

using namespace std;
bool comp(int a, int b)
{
    return a <= b;
};
int main(int argc, char const *argv[])
{
    int totalDistance = 0;
    FileOperations *operations = new FileOperations();

    std::tuple<vector<string>, vector<string>, FileOperations::FILE_OPERATIONS_FLAGS> result =
        operations->getDataFormatted("../day1/input.txt");

    if (std::get<2>(result) == FileOperations::ERROR_FILE_NOT_EXISTS)
    {
        cerr << "An error occured when opening the file. Do you have provided the correct path?" << endl;
        return -1;
    }
    else
    {
        vector<string> in1 = std::get<0>(result);
        vector<string> in2 = std::get<1>(result);

        vector<int> col1;
        vector<int> col2;

        for (string s : in1)
        {
            col1.push_back(stoi(s));
        }
        for (string s : in2)
        {
            col2.push_back(stoi(s));
        }
        in1.clear();
        in2.clear();

        sort(col1.begin(), col1.end(), comp);
        sort(col2.begin(), col2.end(), comp);

        for (auto i = 0; i < col1.size(); i++)
        {
            totalDistance += abs(col1.at(i) - col2.at(i));
        }
        cout << "The total minimum distance between points is " << totalDistance << endl;
    }
    return 0;
}
