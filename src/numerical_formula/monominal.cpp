/* ========================================================================
   ╦┌┬┐┌─┐┌┐┌┌─┐
   ║│││├─┤│││├─┤
   ╩┴ ┴┴ ┴┘└┘┴ ┴
   2018/03/03

   $File: monominal.cpp $
   $Date: 2018/03/05 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2018 by Creative GP, Inc. All Rights Reserved. $
   ======================================================================== */

#include "monominal.hpp"

template<class T> std::vector<std::string> split(const std::string& s, const T& separator, bool ignore_empty = 0, bool split_empty = 0) {
    struct {
        auto len(const std::string&             s) { return s.length(); }
        auto len(const std::string::value_type* p) { return p ? std::char_traits<std::string::value_type>::length(p) : 0; }
        auto len(const std::string::value_type  c) { return c == std::string::value_type() ? 0 : 1; /*return 1;*/ }
    } util;

    if (s.empty()) { /// empty string ///
        if (!split_empty || util.len(separator)) return {""};
        return {};
    }

    auto v = std::vector<std::string>();
    auto n = static_cast<std::string::size_type>(util.len(separator));
    if (n == 0) {    /// empty separator ///
        if (!split_empty) return {s};
        for (auto&& c : s) v.emplace_back(1, c);
        return v;
    }

    auto p = std::string::size_type(0);
    while (1) {      /// split with separator ///
        auto pos = s.find(separator, p);
        if (pos == std::string::npos) {
            if (ignore_empty && p - n + 1 == s.size()) break;
            v.emplace_back(s.begin() + p, s.end());
            break;
        }
        if (!ignore_empty || p != pos)
            v.emplace_back(s.begin() + p, s.begin() + pos);
        p = pos + n;
    }
    return v;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

Monominal::Monominal()
{
}

Monominal::Monominal(string str)
    : _str(str)
{
    parse();
}

void
Monominal::parse()
{
    /*
      単項式を表す文字列を最大まで分解します
      3 * a * 4 -> [3(scalar), 4(scalar), a(variable)]
      3 / 2 * a -> [(3(scalar)/2(scalar))(fraction), a(variable)]
      3 / (2 * a) -> [(3(scalar) / [2(scalar), a(variable)])(fraction)]
     */
    string::size_type pos = 0;
    while ((pos = _str.find(" ", pos)) != string::npos) {
        _str.replace(pos, 1, "");
    }

    vector<string> par = split(_str, "*");
    for (string e : par) {
        if (is_number(e)) {
            _scalars.push_back(atoi(e.c_str()));
        } else {
            _variables.push_back(e);
        }
    }

}

void
Monominal::simplify()
{
    // 現状は数量を全てかけ合わせるだけ
    long long n = 1;
    for (int i : _scalars) {
        n *= i;
    }
    _scalars.clear();
    _scalars.push_back(n);
}

string
Monominal::to_string()
{
    string result;
    ostringstream ss;

    simplify();

    ss << _scalars[0];

    for (string var : _variables) {
        ss << var;
    }

    result = ss.str();

    return result;
}
