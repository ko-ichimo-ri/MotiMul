#ifndef FUNC
#define FUNC
#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
extern "C" {
   #include <quadmath.h>
}
#include "macro.h"

int debug,flag_nsp,flag_bonferroni_factor,flag_wild;
char wild_card;

void combination(ld2 &ans,unsigned long n,unsigned long r);
double least(ll support,ll count0,ll count1);
void prefixspan(succession suc,string let,database db,ll minsup, pattern &pattern,constraint c);
void print_result(string let,pattern &pattern,ll num_minsup,double alpha,ll minsup,ll total,ll count0,ll count1,database db,string fname_nsp);
string complement(string s);
#endif
