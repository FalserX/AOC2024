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
    int safeReports = 0;
    FileOperations *operations = new FileOperations();

    std::tuple<vector<vector<string>>, FileOperations::FILE_OPERATIONS_FLAGS> result =
        operations->getDataFormatted("../day2/input.txt");

    if (std::get<1>(result) == FileOperations::ERROR_FILE_NOT_EXISTS)
    {
        cerr << "An error occured when opening the file. Do you have provided the correct path?" << endl;
        return -1;
    }
    else
    {
        vector<int> increaseDecreaseReportValues;
        bool safe = true;
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
            for (size_t i = 0; i < report.size() - 2; i++)
            {
                if (
                    (report.at(i) < report.at(i + 1) && report.at(i + 1) < report.at(i + 2)) ||
                    (report.at(i) > report.at(i + 1) && report.at(i + 1) > report.at(i + 2)))
                {
                    continue;
                }
                else
                {
                    safe = false;
                    break;
                }
            }

            if (safe)
            {
                for (size_t i = 0; i < report.size() - 1; i++)
                {
                    increaseDecreaseReportValues.push_back(report.at(i) - report.at(i + 1));
                }
                for (int reportValue : increaseDecreaseReportValues)
                {
                    if (abs(reportValue) < 1 || abs(reportValue) > 3)
                    {
                        safe = false;
                        break;
                    }
                }
            }
            if (safe)
            {
                safeReports++;
            }
            safe = true;
            increaseDecreaseReportValues.clear();
        }
        cout << "The number of safe reports are " << safeReports << endl;
    }
    return 0;
}
