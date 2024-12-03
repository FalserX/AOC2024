#include <iostream>
#include "FileOperations.h"
#include "algorithm"

using namespace std;
bool comp(int a)
{
    return a > 3 || a == 0;
}
bool isSafeReportWithDampener(vector<int> report)
{
    vector<int> increaseDecreaseValues;
    vector<string> increaseDecreaseState;
    int countIncrease = 0;
    int countDecrease = 0;
    int countStable = 0;
    bool safe = false;
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
        increaseDecreaseValues.push_back(abs(report.at(reportIdx) - report.at(reportIdx + 1)));
    }
    countIncrease = count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Increase");
    countDecrease = count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease");
    countStable = count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Stable");
    if (countIncrease + countDecrease + countStable == increaseDecreaseValues.size())
    {
        /*For decreasing or increasing only states */
        if ((countStable == 0 && countIncrease == 0 && countDecrease > 0) ||
            (countStable == 0 && countDecrease == 0 && countIncrease > 0))
        {
            for (int increaseDecreaseValue : increaseDecreaseValues)
            {
                if (abs(increaseDecreaseValue) < 1 || abs(increaseDecreaseValue) > 3)
                {
                    safe = false;
                    break;
                }
                else
                {
                    safe = true;
                }
            }
        }
        if (!safe)
        {
            vector<int> tempReportValues;
            /*For decreasing states*/
            if (countIncrease <= 1 && countStable <= 1)
            {
                auto posIdxIncreaseDecreaseValue = distance(increaseDecreaseValues.begin(), find_if(increaseDecreaseValues.begin(), increaseDecreaseValues.end(), comp));
                if (posIdxIncreaseDecreaseValue >= report.size() - 1)
                {
                    posIdxIncreaseDecreaseValue = distance(increaseDecreaseState.begin(), find(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease"));
                }
                for (size_t i = 0; i < report.size(); i++)
                {
                    if (i != posIdxIncreaseDecreaseValue + 1)
                    {
                        tempReportValues.push_back(report.at(i));
                    }
                }
                increaseDecreaseValues.clear();
                for (size_t idxValue = 0; idxValue < tempReportValues.size() - 1; idxValue++)
                {
                    increaseDecreaseValues.push_back(abs(tempReportValues.at(idxValue) - tempReportValues.at(idxValue + 1)));
                }

                for (int value : increaseDecreaseValues)
                {
                    if (value > 3 || value < 1)
                    {
                        safe = false;
                        break;
                        ;
                    }
                    else
                    {
                        safe = true;
                    }
                }
            }
            /*For increasing states */
            else if (countDecrease <= 1 && countStable <= 1)
            {
                auto posIdxIncreaseDecreaseValue = distance(increaseDecreaseValues.begin(), find_if(increaseDecreaseValues.begin(), increaseDecreaseValues.end(), comp));
                if (posIdxIncreaseDecreaseValue >= report.size() - 1)
                {
                    posIdxIncreaseDecreaseValue = distance(increaseDecreaseState.begin(), find(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease"));
                }
                else if (posIdxIncreaseDecreaseValue > 0 && posIdxIncreaseDecreaseValue < report.size() - 1 &&
                         ((report.at(posIdxIncreaseDecreaseValue - 1) > report.at(posIdxIncreaseDecreaseValue) &&
                           report.at(posIdxIncreaseDecreaseValue + 1) > report.at(posIdxIncreaseDecreaseValue) &&
                           abs(report.at(posIdxIncreaseDecreaseValue - 1) - report.at(posIdxIncreaseDecreaseValue + 1)) > 1 &&
                           abs(report.at(posIdxIncreaseDecreaseValue - 1) - report.at(posIdxIncreaseDecreaseValue + 1)) < 4) ||
                          (report.at(posIdxIncreaseDecreaseValue - 1) < report.at(posIdxIncreaseDecreaseValue) &&
                           report.at(posIdxIncreaseDecreaseValue + 1) < report.at(posIdxIncreaseDecreaseValue) &&
                           abs(report.at(posIdxIncreaseDecreaseValue - 1) - report.at(posIdxIncreaseDecreaseValue + 1)) > 1 &&
                           abs(report.at(posIdxIncreaseDecreaseValue - 1) - report.at(posIdxIncreaseDecreaseValue + 1)) < 4)))
                {
                    posIdxIncreaseDecreaseValue--;
                }
                for (size_t i = 0; i < report.size(); i++)
                {
                    if (i != posIdxIncreaseDecreaseValue + 1)
                    {
                        tempReportValues.push_back(report.at(i));
                    }
                }
                increaseDecreaseValues.clear();
                for (size_t idxValue = 0; idxValue < tempReportValues.size() - 1; idxValue++)
                {
                    increaseDecreaseValues.push_back(abs(tempReportValues.at(idxValue) - tempReportValues.at(idxValue + 1)));
                }

                for (int value : increaseDecreaseValues)
                {
                    if (value > 3 || value < 1)
                    {
                        safe = false;
                        break;
                        ;
                    }
                    else
                    {
                        safe = true;
                    }
                }
            }
            /* Not valid*/
            else
            {
                safe = false;
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
    int countIncrease = 0;
    int countDecrease = 0;
    int countStable = 0;
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
    countIncrease = count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Increase");
    countDecrease = count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Decrease");
    countStable = count(increaseDecreaseState.begin(), increaseDecreaseState.end(), "Stable");
    if (
        (countDecrease >= increaseDecreaseState.size() - 1 &&
         countIncrease <= 0 && countStable <= 0) ||
        countIncrease >= increaseDecreaseState.size() - 1 &&
            countDecrease <= 0 && countStable <= 0)
    {
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
        operations->getDataFormatted("../day2/input.txt");

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
    std::cout << "The number of safe reports are " << safeReports << endl;
    std::cout << "The number of safe reports are " << safeReportsDampener << " with problem dampener" << endl;
    return 0;
}
