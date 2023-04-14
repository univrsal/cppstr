/*
 * Copyright (c) 2023 Alex <uni@vrsal.xyz>
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define CHECK(t, what) t.Check(#what, (what))

constexpr unsigned int HeaderLength { 48 };

struct TestReport {
    std::string TestName;
    std::vector<std::string> FailedTests;
    int Total { 0 };
    int Failed { 0 };
};

using TestReports = std::vector<TestReport>;

class Test {
    std::string TestName;
    int TotalTests { 0 }, Failed { 0 }, Passed { 0 };
    std::vector<std::string> FailedTests;
    TestReports& Reports;
    bool bSilent{};

public:
    explicit Test(const char* Name, TestReports& inReports, bool inbSilent = true)
        : TestName(Name)
        , Reports(inReports)
        , bSilent(inbSilent)
    {
        TestName = Name + std::string(" Test");
        Section("Begin " + TestName);
    }

    ~Test()
    {
        std::cout << TotalTests << " tests run, " << Passed << " passed, " << Failed << " failed\n";
        Section("End " + TestName);
        Report();
    }

    void Check(const char* Name, bool bWhat)
    {
        if (!bWhat)
            std::cout << " [!] " << Name << "\n";
        else if (!bSilent)
            std::cout << " [+] " << Name << "\n";
        Check(bWhat);
        if (!bWhat)
            FailedTests.emplace_back(Name);
    }

    void Check(bool bWhat)
    {
        TotalTests++;
        bWhat ? Passed++ : Failed++;
    }

    static void Section(const std::string& SectionName)
    {
        int LengthLeft = int(roundf(float(HeaderLength - SectionName.length()) / 2.f));
        int LengthRight = int(HeaderLength - SectionName.length() - LengthLeft);

        std::string Header;
        for (int i = 0; i < LengthLeft; i++)
            std::cout << "=";
        std::cout << " " << SectionName.c_str() << " ";
        for (int i = 0; i < LengthRight; i++)
            std::cout << "=";
        std::cout << "\n";
    }

    void Report()
    {
        TestReport Report;
        Report.Failed = Failed;
        Report.Total = TotalTests;
        Report.TestName = TestName;
        Report.FailedTests = FailedTests;
        Reports.emplace_back(Report);
    }
};
