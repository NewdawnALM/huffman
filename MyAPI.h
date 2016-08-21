#ifndef MyAPI_h
#define MyAPI_h

#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<string>
#include<set>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
#define  For(i,s,t)  for(int i = s; i < t; ++i)

inline string itostr(int x) {
    char s[23];
    sprintf(s,"%d",x);
    return string(s);
}

inline string chtostr(char ch) {
    string res = "";
    return res + ch;
}

#endif