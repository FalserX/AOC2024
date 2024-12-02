#include <iostream>
#include "FileOperations.h"
#include "algorithm"

using namespace std;

bool isSafeReportWithDampener(vector<int> report)
{
    vector<int> increaseDecreaseValues;
    vector<string> increaseDecreaseState;
    bool safe = true;
    for (size_t reportIdx = 0; reportIdx < report.size() - 1; reportIdx++)
    {
        if (report.at(reportIdx) < report.at(reportIdx + 1))
        {
            increaseDecreaseState.push_back("Increase");
        }
        else if (report.at(reportIdx) > report.at(reportIdx + 1))
        {
            increaseDecreaseState.push_back("Decrease");
        }
        else
        {
            increaseDecreaseState.push_back("Stable");
        }
        increaseDecreaseValues.push_back(report.at(reportIdx) - report.at(reportIdx + 1));
    }
    if (
        (count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease") >= increaseDecreaseState.size() - 1 &&
         count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Increase") <= increaseDecreaseState.size() - 1) ||
        count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Increase") >= increaseDecreaseState.size() - 1 &&
            count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease") <= increaseDecreaseState.size() - 1)
    {
        string dd = "";
        for (int increaseDecreaseValue : increaseDecreaseValues)
        {
            if (abs(increaseDecreaseValue) < 1 || abs(increaseDecreaseValue) > 3)
            {
                safe = false;
                break;
            }
        }
    }
    else
    {
        safe = false;
    }

    return safe;
}
bool isSafeReport(vector<int> report)
{
    vector<int> increaseDecreaseValues;
    vector<string> increaseDecreaseState;
    bool safe = true;
    for (size_t reportIdx = 0; reportIdx < report.size() - 1; reportIdx++)
    {
        if (report.at(reportIdx) < report.at(reportIdx + 1))
        {
            increaseDecreaseState.push_back("Increase");
        }
        else if (report.at(reportIdx) > report.at(reportIdx + 1))
        {
            increaseDecreaseState.push_back("Decrease");
        }
        else
        {
            increaseDecreaseState.push_back("Stable");
        }
        increaseDecreaseValues.push_back(report.at(reportIdx) - report.at(reportIdx + 1));
    }
    if (
        (count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease") >= increaseDecreaseState.size() - 1 &&
         count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Increase") <= 0 && count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Stable") <= 0) ||
        count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Increase") >= increaseDecreaseState.size() - 1 &&
            count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease") <= 0 && count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Stable") <= 0)
    {
        string dd = "";
        for (int increaseDecreaseValue : increaseDecreaseValues)
        {
            if (abs(increaseDecreaseValue) < 1 || abs(increaseDecreaseValue) > 3)
            {
                safe = false;
                break;
            }
        }
    }
    else
    {
        safe = false;
    }

    return safe;
}

int main(int argc, char const *argv[])
{
    int safeReports = 0;
    int safeReportsDampener = 0;
    FileOperations *operations = new FileOperations();

    std::tuple<vector<vector<string>>, FileOperations::FILE_OPERATIONS_FLAGS> result =
        operations->getDataFormatted("../day2/example.txt");

    if (std::get<1>(result) == FileOperations::ERROR_FILE_NOT_EXISTS)
    {
        cerr << "An error occured when opening the file. Do you have provided the correct path?" << endl;
        return -1;
    }
    else
    {
        vector<vector<int>> reports;
        for (vector<string> reportsStr : std::get<0>(result))
        {
            vector<int> report;
            for (string s : reportsStr)
            {
                report.push_back(atoi(s.c_str()));
            }
            reports.push_back(report);
        }
        for (vector<int> report : reports)
        {
            if (isSafeReport(report))
            {
                safeReports++;
            }
            if (isSafeReportWithDampener(report))
            {
                safeReportsDampener++;
            }
        }
    }
    cout << "The number of safe reports are " << safeReports << endl;
    cout << "The number of safe reports are " << safeReportsDampener << " with problem dampener" << endl;
    return 0;
}
