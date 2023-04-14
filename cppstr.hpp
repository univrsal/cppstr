/*
 * Copyright (c) 2023 Alex <uni@vrsal.xyz>
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once
#include <string>
#include <functional>

#define SLICE(s) (cppstr::slice { true ? s, false ? s})

class cppstr {
    std::string m_string;
public:
    using size = std::string::size_type;

    cppstr(const char* str) : m_string(str) {}
    cppstr(std::string const&  str) : m_string(str) {}
    cppstr(cppstr const&  str) : m_string(str.m_string) {}

    class index {
        friend struct cppstr;
        friend struct slice;
        bool initialized = false;
        int value = 0;
    public:
        index() = default;
        index(int v) { value = v; initialized = true;}
        operator int() const{ return value;}

        bool operator==(int const& i) const { return value == i;}
        bool operator>(int const& i) const { return value > i;}
        bool operator<(int const& i) const { return value < i;}
        bool operator>=(int const& i) const { return value >= i;}
        bool operator<=(int const& i) const { return value <= i;}
    };

    struct slice {
        index start{}, end{};
        slice(index s, index e) : start(s), end(e){ }
        slice(index s) : start(s){ }
        slice() = default;
    };

    operator std::string&() { return m_string;}
    operator std::string const&() const{ return m_string;}

    char operator[](index const& idx) const {
        if (idx >= 0)
            return m_string[idx];
        return m_string[m_string.length() + idx];
    }

    cppstr operator[](slice const& idx) const {
        if (!idx.start.initialized && !idx.end.initialized)
            return m_string;
        if (idx.start == 0 && !idx.end.initialized)
            return m_string;
        if (idx.start == 0 && idx.end == 0)
            return "";

        int end = idx.end.value;
        int start = idx.start.value;

        if (!idx.end.initialized)
            end = int(m_string.length());
        if (!idx.start.initialized)
            start = 0;

        if (start < 0)
            start = int(m_string.length()) + start;
        if (end < 0)
            end = int(m_string.length()) + end;
        if (end <= start || start + (end - start) > m_string.length())
            return "";
        return m_string.substr(start, end - start);
    }

    size find(const char c, size start = 0) const { return m_string.find(c, start); }
    size find(std::string const& str, size start = 0) const { return m_string.find(str, start); }
    size rfind(const char c, size start = 0) const { return m_string.rfind(c, start); }
    size rfind(std::string const& str, size start = 0) const { return m_string.rfind(str, start); }

    bool empty() const { return m_string.empty();}

    bool endswith(std::string const& str) const { return (*this)[{-int(str.length()), {}}] == str; }
    bool startswith(std::string const& str) const { return (*this)[{0, int(str.length())}] == str; }

    const char* c_str() const { return m_string.c_str();}
    const char* data() const { return m_string.data();}
    std::string const& str() const { return m_string;}
    std::string& str() { return m_string;}
    size length() const { return m_string.length(); }

    bool operator==(const char* str) const { return m_string == str;}
    bool operator==(std::string const& str) const { return m_string == str;}
    bool operator==(cppstr const& str) const { return m_string == str.m_string;}

    bool operator!=(const char* str) const { return m_string != str;}
    bool operator!=(std::string const& str) const { return m_string != str;}
    bool operator!=(cppstr const& str) const { return m_string != str.m_string;}

    std::string::iterator begin() { return m_string.begin(); }
    std::string::iterator end() { return m_string.end(); }

};

