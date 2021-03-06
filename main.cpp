/*
Copyright <2020> <Koichi Mori>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <tuple>
#include <algorithm>
#include<time.h>
#include <stdio.h>
#include <gmp.h>
#include "func.h"

using namespace std;

int main(int argc,char **argv){
  extern char *optarg;
  extern int optind;
  int opt;
  debug=0;
  flag_bonferroni_factor=0;
  flag_nsp=0;
  flag_wild=0;
  flag_testable=0;
  double alpha=0.05;
  flag_complement=0;
  string let("ATGC");//The set of alphabets for analysis

  string fname_nsp;
  string pattern_for_evaluation="";
  ofstream fs_time;
  ofstream fs_pattern;
  ofstream fs_factor;
  string name_mf[2];

  constraint c;
  c.max_size=-1;
  c.min_size=-1;
  c.num_wild=0;

  while((opt=getopt(argc,argv,"a:dtb:o:O:p:r:w:cl:L:s:v"))!=EOF){
    switch(opt){
      case 'a':
        alpha=atof(optarg);
        break;
      case 'd':
        debug=1;
        break;
      case 't':
        flag_testable=1;
        break;
      case 'b':
        fs_factor.open(optarg,ios::app);
        if(!fs_factor){
          printf("file '%s' open error\n", argv[1]);
          exit(EXIT_FAILURE);
        }                
        break;
      case 'o':
        flag_nsp=1;
        fname_nsp=optarg;
        break; 
      case 'O':
        fs_time.open(optarg,ios::app);
        if(!fs_time){
          printf("file '%s' open error\n", argv[1]);
          exit(EXIT_FAILURE);
        }                
        break;
      case 'p':
        pattern_for_evaluation=optarg;
        transform(pattern_for_evaluation.begin(), pattern_for_evaluation.end(), pattern_for_evaluation.begin(), ::toupper);
        break;
      case 'r':
        fs_pattern.open(optarg,ios::app);
        if(!fs_pattern){
          printf("file '%s' open error\n", argv[1]);
          exit(EXIT_FAILURE);
        }                
        break;
      case 'w':
	if(atoi(optarg)>0){
	  flag_wild=1;
          wild_card='*';
          c.num_wild = atoi(optarg);
	}
        break;
      case 'c':
        flag_complement=1;
        break;
      case 'l':
        c.min_size=atoi(optarg);
        break;
      case 'L':
        c.max_size=atoi(optarg);
        break;
      case 's':
        if(optarg==string("d")||optarg==string("dna"))
          let="ATGC";
        else if(optarg==string("r")||optarg==string("rna"))
            let="AUGC";
        else if(optarg==string("p")||optarg==string("protein"))
            let="GAVLIPFWCMYSTNQHKRDE";
        break;
      case 'v':
        cout<<"MotiMul 1.2.3"<<endl;
        return 0;
        break;
      default:
        break;
    }
  }
 // cout<<"letters: "<< let <<endl;
  if(let!="ATGC"){
    flag_complement=0;
  }
  if(flag_wild)
  cout<<"wild card: "<< wild_card<<endl;
  cout<<"Significant Level before Multiple Correction: "<<alpha<<endl;
  if(debug){
    printf("debug: on\n");
  }else{
   // printf("debug: off\n");
  }
  if(debug){
    printf("argv[optind]: %s\n",argv[optind]);
    printf("argv[optind+1]: %s\n",argv[optind+1]);
  }
  if(flag_wild)let+=wild_card;

  clock_t start,end;

  ifstream file;
  ifstream mf[2];
  for(int i=0;i<=1;i++)
    mf[i].open(argv[optind+i],ios::in);
  string s,s2;

  database db;
  succession suc_initial;
  suc_initial.s="";
  suc_initial.num_wilds=0;
  each_succession each_suc_initial;

  ll count[2];
  count[0]=0;//the number of data in the negative dataset, which is used when one calculates the lower bound of p-value
  count[1]=0;////the number of data in the positive dataset, which is used when one calculates the lower bound of p-value

  start=clock(); 
  s2="";
  for(int i=0;i<=1;i++){
    while(!mf[i].eof()){
      getline(mf[i],s);
      if(s[0]=='>'){
        if(s2!=""){
          transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
          db.push_back(make_tuple(count[0]+count[1],s2,i,each_suc_initial));
          if(flag_complement)
            db.push_back(make_tuple(count[0]+count[1],complement(s2),i,each_suc_initial));
          s2="";
          count[i]++;
        }
      }else{
        s2+=s;
      }
    }
    if(s2!=""){
      transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
      db.push_back(make_tuple(count[0]+count[1],s2,i,each_suc_initial));
      if(flag_complement)
        db.push_back(make_tuple(count[0]+count[1],complement(s2),i,each_suc_initial));
      s2="";
      count[i]++;
    }
  }

  ll minsup;
  ll num_minsup_pre=0;//m_lambda
  ll num_minsup=0;//m_{lambda+1}
  ll total = count[0]+count[1];
  pattern pattern[2];
  int flag_pattern=0;
  int flag_result=0;
  int flag_one_path=1;
  for(minsup=0;minsup<=total;minsup++){
    if(least(minsup,count[0],count[1])>alpha)continue;
    if(flag_one_path==1){
      flag_one_path=0;
      cout<<"minsup(one-path): "<<minsup<<endl;
      pattern[flag_pattern].clear();
      prefixspan(suc_initial,let,db,minsup,pattern[flag_pattern],c);
      num_minsup=pattern[flag_pattern].size();
      flag_pattern=1-flag_pattern;
    }
    pattern[flag_pattern].clear();
    if(debug){
       printf("minsup=%Ld\n",minsup);
    }
//prefixspan
    prefixspan(suc_initial,let,db,minsup+1,pattern[flag_pattern],c);
    num_minsup_pre=num_minsup;
    num_minsup=pattern[flag_pattern].size();
//Tarone
    if(least(minsup,count[0],count[1])*num_minsup<=alpha){
      cout<<"minsup(last): "<<minsup<<endl;
      print_result(let,pattern[1-flag_pattern],num_minsup_pre,alpha,minsup,total,count[0],count[1],db,fname_nsp);
      flag_result=1;
      break;
    }
    flag_pattern=1-flag_pattern;
  }
  if(!flag_result){
      num_minsup_pre=num_minsup;
      print_result(let,pattern[1-flag_pattern],num_minsup_pre,alpha,minsup,total,count[0],count[1],db,fname_nsp);
  }
  end=clock();

  double time =(double)(end-start)/CLOCKS_PER_SEC;
  printf("\ntime: %lf seconds\n",time);

  if(fs_time){
    fs_time<<time;
  }
  if(fs_factor){
    fs_factor<<num_minsup_pre;
  }

  int ev_pattern=0;
  int i_pattern;
  i_pattern=1-flag_pattern;
  
  if(fs_pattern){
    for(unsigned int i=0;i<pattern[i_pattern].size();i++){
      if(get<1>(pattern[i_pattern][i])==pattern_for_evaluation){
        ev_pattern=1;
        break;
      }
    }
    fs_pattern<<ev_pattern;
  }

  return 0;
}

