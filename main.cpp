#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <tuple>
extern "C" {
   #include <quadmath.h>
}
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
  double alpha=0.05;
  int flag_mf=0;
  string let("abcdefghijklmnopqrstuvwxyz1234567890");//解析する文字

  ll count0=0;//与えられたデータで目的変数が0のものの個数（P値の下限を計算する時に用いる）
  ll count1=0;//与えられたデータで目的変数が1のものの個数（P値の下限を計算する時に用いる）

  string fname_nsp;
  string pattern_for_evaluation="";
  ofstream fs_time;
  ofstream fs_pattern;
  ofstream fs_factor;
  string name_mf[2];

  constraint c;
  c.min_size=-1;
  c.max_size=-1;
  c.min_gap=-1;
  c.max_gap=-1;
  c.min_count_gap=-1;
  c.max_count_gap=-1;
  while((opt=getopt(argc,argv,"db:l:a:o:O:s:S:g:G:n:N:p:r:w:f:"))!=EOF){
    switch(opt){
      case 'l':
        let=optarg;
        break;
      case 'a':
        alpha=atof(optarg);
        break;
      case 'd':
        debug=1;
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
      case 's':
        c.min_size=atoi(optarg);
        break;
      case 'S':
        c.max_size=atoi(optarg);
        break;
      case 'g':
        c.min_gap=atoi(optarg);
        break;
      case 'G':
        c.max_gap=atoi(optarg);
        break;
      case 'n':
        c.min_count_gap=atoi(optarg);
        break;
      case 'N':
        c.max_count_gap=atoi(optarg);
        break;
      case 'p':
        pattern_for_evaluation=optarg;
        break;
      case 'r':
        fs_pattern.open(optarg,ios::app);
        if(!fs_pattern){
          printf("file '%s' open error\n", argv[1]);
          exit(EXIT_FAILURE);
        }                
        break;
      case 'w':
        flag_wild=1;
        wild_card='*';
        c.num_wild = atoi(optarg);
        break;
      case 'f':
        flag_mf=1;
        name_mf[0]=optarg[0];
        name_mf[1]=optarg[1];
        break;
      default:
        break;
    }
  }
  cout<<"letters: "<< let <<endl;
  if(flag_wild)
  cout<<"wild card: "<< wild_card<<endl;
  cout<<"alpha: "<<alpha<<endl;
  if(debug){
    printf("debug: on\n");
  }else{
    printf("debug: off\n");
  }
  if(debug){
    printf("argv[optind]: %s\n",argv[optind]);
  }
  if(flag_wild)let+=wild_card;

  clock_t start,end;

  string filename = argv[optind];
  ifstream file;
  ifstream mf[2];
  if(flag_mf==1){
    for(int i=0;i<=1;i++)
      mf[i].open(name_mf[i],ios::in);
  }else{
    file.open(filename,ios::in);
  }
  string s,s2;

  database db;
  succession suc_initial;
  suc_initial.s="";
  suc_initial.count_gap_wilds=0;
  suc_initial.num_wilds=0;
  suc_initial.total_length_of_wilds=0;
  suc_initial.total_length_of_non_wilds=0;
  each_succession each_suc_initial;
  each_suc_initial.count_gap=0;
  each_suc_initial.total_length_of_gaps=0;
  each_suc_initial.total_length_of_non_gaps=0;

  start=clock(); 
  if(flag_mf==0){
    while(!file.eof()){
      getline(file,s);
      s2=s;
      s2.erase(s2.begin(),s2.begin()+2);
      if(s[0]=='0'){
        count0++;
        db.push_back(make_tuple(count0+count1,s2,0,each_suc_initial));
      }else if(s[0]=='1'){
        count1++;
        db.push_back(make_tuple(count0+count1,s2,1,each_suc_initial));
      }else{
        perror("error!\n");
        exit(EXIT_FAILURE);
      }
    }
  }else{
    s2="";
    for(int i=0;i<=1;i++){
      while(!mf[i].eof()){
        getline(mf[i],s);
        if(s[0]=='>'){
          if(s2!=""){
            db.push_back(make_tuple(count0+count1,s2,i,each_suc_initial));
            s2="";
          }
        }else{
          s2+=s;
        }
      }
    }
  }
  ll minsup;
  ll num_minsup_pre=0;//m_lambda
  ll num_minsup=0;//m_{lambda+1}
  ll total = count0+count1;
  pattern pattern[2];
  int flag_pattern=0;
  int flag_result=0;
  int flag_one_path=1;
  for(minsup=0;minsup<=total;minsup++){
    if(least(minsup,count0,count1)>alpha)continue;
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
    if(least(minsup,count0,count1)*num_minsup<=alpha){
      cout<<"minsup(last): "<<minsup<<endl;
      print_result(let,pattern[1-flag_pattern],num_minsup_pre,alpha,minsup,total,count0,count1,db,fname_nsp);
      flag_result=1;
      break;
    }
    flag_pattern=1-flag_pattern;
  }
  if(!flag_result){
      num_minsup_pre=num_minsup;
      print_result(let,pattern[1-flag_pattern],num_minsup_pre,alpha,minsup,total,count0,count1,db,fname_nsp);//Alright?
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

