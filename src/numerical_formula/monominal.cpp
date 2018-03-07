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


void Monominal_Without_Fraction::
add_token(string token)
{
    if (is_number(token)) {
        scalars.push_back(atoi(token.c_str()));
    } else {
        variables.push_back(token);
    }
}


void Monominal_Without_Fraction::
simplify_scalars()
{
    long long n = 1;
    for (int i : scalars) {
        n *= i;
    }
    scalars.clear();
    scalars.push_back(n);
}

Monominal::Monominal()
{
}

Monominal::Monominal(string str)
    : _str(str)
{
    parse();
}

void Monominal::
parse()
{
    /*
      単項式を表す文字列を最大まで分解します
      全ての単項式は分数で表せると思うから全部分数として定義する
      3 * a * 4 -> [3(scalar), 4(scalar), a(variable)]
      3 / 2 * a -> [(3(scalar)/2(scalar))(fraction), a(variable)]
      3 / (2 * a) -> [(3(scalar) / [2(scalar), a(variable)])(fraction)]
     */
    string strt = _str;
    string::size_type pos = 0;
    while ((pos = strt.find(" ", pos)) != string::npos) {
        strt.replace(pos, 1, "");
    }

    reverse(strt.begin(), strt.end());

    vector<string> up;
    vector<string> down;
    string token;
    for (char c : strt) {
        if (c == '*') {
            _up.add_token(token);
            token = "";
        } else if (c == '/') {
            _down.add_token(token);
            token = "";
        } else {
            token = c + token;
        }
    }

    _up.add_token(token);
}

void Monominal::
simplify()
{
    // 現状は数量を全てかけ合わせるだけ
    _up.simplify_scalars();
    _down.simplify_scalars();
}

string Monominal::
to_string()
{
    string result;
    stringstream upst, downst;

    simplify();

    if (_up.scalars[0]==1) upst << "";
    else upst << _up.scalars[0];
    for (string var : _up.variables) {
        upst << var;
    }
    if (upst.str() == "") upst << "1";

    if (_down.scalars[0]==1) downst << "";
    else downst << _down.scalars[0];
    for (string var : _down.variables) {
        downst << var;
    }

    result = upst.str() + (downst.str()=="" ? "" : " / "+downst.str());

    return result;
}
