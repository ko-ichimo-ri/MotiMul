#ifndef MACRO
#define MACRO
extern "C" {
   #include <quadmath.h>
}
#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

#define LENGTH_DATA 128
#define LENGTH_GAP 128
#define NUMBER_DATA 1024
#define NUMBER_LETTER 128
#define NUMBER_COMB 8192

typedef long long ll;
typedef struct constraint0{
    ll num_wild;    
    ll max_size;
    ll min_size;
}constraint;
typedef struct succession0{
    string s;
    ll num_wilds;
}succession;

typedef struct each_succession0{
}each_succession;

typedef long double ld;
typedef mpf_class ld2;

//typedef vector<tuple<ld2,string,int,int>> pattern;//(p-value,pattern,support_all,support1)
typedef tuple<ld2,string,int,int> member_of_pattern;//(p-value,pattern,support_all,support1)
typedef vector<member_of_pattern> pattern;
typedef vector<tuple<ll,string,int,each_succession>> database;//(id,data,tag,suc)

#endif
