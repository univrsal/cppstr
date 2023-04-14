/*
 * Copyright (c) 2023 Alex <uni@vrsal.xyz>
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <iostream>
#include "cppstr.hpp"
#include "Test.h"

void basics(TestReports& reports)
{
    Test t("Basics", reports);
    cppstr str = "test123";

    CHECK(t, str == "test123");
    CHECK(t, str[0] == 't'); // str[0]
    CHECK(t, str[-2] == '2'); // str[-2]
}

void edges(TestReports& reports)
{
    Test t("Edge cases", reports);
    cppstr str = "test123";

    CHECK(t, str[{0}] == "test123"); // str[0:]
    CHECK(t, str[{}] == "test123"); // str[:]
    CHECK(t, str[{}] == "test123"); // str[:]
    t.Check("str[{0,0}] == \"\"", str[{0,0}] == ""); // str[0:0]
    t.Check("str[{{},0}] == \"\"", str[{{},0}] == ""); // str[:0]

    CHECK(t, str[{2}] == "st123"); // str[2:]
    t.Check("str[{2, {}}] == \"st123\"", str[{2, {}}] == "st123"); // str[2:]

    CHECK(t, str[{-2}] == "23"); // str[2:]
    t.Check("str[{-2, {}}] == \"23\"", str[{-2, {}}] == "23"); // str[-2:]

    t.Check("str[{2, 3}] == \"s\"", str[{2, 3}] == "s"); // str[2:3]

    t.Check("str[SLICE(2:3)] == \"s\"", str[SLICE(2:3)] == "s"); // str[2:3]

    t.Check("str[{{}, -2}] == \"test1\"", str[{{}, -2}] == "test1"); // str[:-2]

    t.Check("str[{2, -2}] == \"st1\"", str[{2, -2}] == "st1"); // str[2:-2]
}

void overlaps(TestReports& reports)
{
    Test t("Overlaps", reports);
    cppstr str = "test123";

    t.Check("str[20:-2] == \"\"", str[{20, -2}] == ""); // str[20:-2]
    t.Check("str[0:-20] == \"\"", str[{0, -20}] == ""); // str[0:-20]
    t.Check("str[20:-20] == \"\"", str[{20, -20}] == ""); // str[20:-20]
}

int main()
{
    TestReports Reports;
    basics(Reports);
    edges(Reports);
    overlaps(Reports);

    std::cout << "Final report\n";
    int Total { 0 }, TotalFailed { 0 };
    for (const auto& Report : Reports) {
        if (Report.Failed > 0) {
            std::cout << Report.TestName.c_str() << ":\n";
            for (const auto& Failed : Report.FailedTests) {
                std::cout << " [!] " << Failed << "\n";
            }
            std::cout << " " << Report.Failed << " out of " << Report.Total << " failed\n";
        }
        Total += Report.Total;
        TotalFailed += Report.Failed;
    }
    std::cout << Total << " tests run in total\n";
    if (TotalFailed > 0)
        std::cout << TotalFailed << " failed in total\n";
    else
        std::cout << "All tests passed!\n";
    return 0;
}
