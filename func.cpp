/*
Copyright <2020> <Koichi Mori>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <tuple>
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

extern int debug,flag_nsp,flag_wild,flag_testable,flag_complement;
extern char wild_card;
extern ld comb[NUMBER_COMB][NUMBER_COMB];

void combination(ld2 &ans,unsigned long n,unsigned long r){
   mpz_t rop;
   mpf_t rop_f;
   mpz_init(rop);
   mpf_init(rop_f);
   mpz_bin_uiui(rop,n,r);
   mpf_set_z(rop_f,rop);
   ld2 ans_f(rop_f);
   ans=ans_f;
   mpz_clear(rop);
   mpf_clear(rop_f);
} 

char comp(char c){
    switch (c){
        case 'A':
            return 'T';
        case 'T':
            return 'A';
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        case '*':
            return '*';        
        default:
            return '\0';
    }

}

string complement(string s){
  string s2="";
  for(unsigned int i=0;i<s.length();i++){
    s2.push_back(comp(s[s.length()-i-1]));
  }
  return s2;
}


void l(ld2 &ans,ll support,ll count0,ll count1){
  ll total = count0+count1;
  ld2 ans0,ans1;

  if(support<=count1){
    combination(ans0,count1,support);
    combination(ans1,total,support);
    ans=ans0/ans1;
  }else{
    ans0="1.0";
    combination(ans1,total,count1);
    ans=ans0/ans1;
  }
};

double least(ll support,ll count0,ll count1){
  ld2 l_value;
  l(l_value,support,count0,count1); 
  return l_value.get_d();
};

void prefixspan(succession suc,string let,database db,ll minsup, pattern &pattern,constraint c){
//  cout<<suc.s<<" "<<suc.num_wilds<<endl;
//  cout<<"constraint: "<<c.num_wild<<endl;
  int flag_initial=0;
  if(suc.s==""){
    flag_initial=1;
  }
  
  int n_char,sum_char;
  ll support_all,support1,support_all_with_constraints,support1_with_constraints;
  database projected_db;
  string buf;
  ll id,tag,id_old;
  each_succession each_suc;
  int flag_support_all,flag_support_all_with_constraints;
  int flag_support_all_old;//The data with the same id has already count support.
  int flag_support_all_with_constraints_old;
  string s_origin=suc.s;
  ll num_wilds_origin=suc.num_wilds;

  int s_length=suc.s.length();
 
  if(debug)cout<<"new_prefixspan"<<minsup<<endl;
  if((c.max_size<0||s_length+1<=c.max_size)
    &&(flag_wild==0||suc.num_wilds<=c.num_wild)){  //no patterns, the length of which is greater than that of max_size
    for(unsigned int i=0;i<let.size();i++){
      suc.s=s_origin+let[i];
      support_all=0;
      support1=0;
      support_all_with_constraints=0;
      support1_with_constraints=0;
      projected_db.clear();
      id=-1;
      flag_support_all_old=0;
      flag_support_all_with_constraints_old=0;
      for(int j=0;j<db.end()-db.begin();j++){
        id_old=id;
        id=get<0>(db[j]);
        buf=get<1>(db[j]);
        tag=get<2>(db[j]);

        sum_char=0;
        flag_support_all_with_constraints=0;
        flag_support_all=0;
        while(1){
          if(flag_wild && let[i]==wild_card){
            suc.num_wilds=num_wilds_origin+1;
            if(buf.empty()||flag_initial){
              n_char=(int)string::npos;
            }else{
              n_char=0;
            }
          }else{
            suc.num_wilds=num_wilds_origin;
            n_char=buf.find(let[i]);
          }
          if(n_char==(int)string::npos)break;

          flag_support_all=1;
          sum_char+=n_char;

          buf.erase(buf.begin(),buf.begin()+n_char+1);
          if(debug)cout<<"buf="<<buf<<" nchar="<<n_char<<endl;

            
          if(!flag_initial && sum_char>0)break;

          if((c.min_size<0||s_length+1>=c.min_size)
          &&let[i]!=wild_card){
            flag_support_all_with_constraints=1;
          }

          projected_db.push_back(make_tuple(id,buf,tag,each_suc));
          flag_support_all=1;
          sum_char++; //count deleted character
        }
        if(id!=id_old){
          flag_support_all_old=0;
          flag_support_all_with_constraints_old=0;
        }
        if(flag_support_all && !flag_support_all_old){
          support_all++;
          if(tag==1){
            support1++;
          }
        }
        if(flag_support_all_with_constraints&&!flag_support_all_with_constraints_old){
          support_all_with_constraints++;
          if(tag==1){
            support1_with_constraints++;
          }
        }
        flag_support_all_old=max(flag_support_all,flag_support_all_old);
        flag_support_all_with_constraints_old=max(flag_support_all_with_constraints,flag_support_all_with_constraints_old);
      }
      if(debug){
        cout<<suc.s;
        printf("%c; support_all=%Ld\n",let[i],support_all);
      }

      if(support_all>=minsup){
        if(support_all_with_constraints>=minsup){
          if(flag_complement==0){
            pattern.push_back(make_tuple(0.0,suc.s,support_all_with_constraints,support1_with_constraints));
          }else{
            if(suc.s<=complement(suc.s)){
              pattern.push_back(make_tuple(0.0,suc.s,support_all_with_constraints,support1_with_constraints));
            }
          }
        }
        prefixspan(suc,let,projected_db,minsup,pattern,c);
      }
    }
  }
};

ld2 p_value(ll support_all,ll support1,ll count0,ll count1){
  ld2 p;
  ld2 pre_p(0.0);
  ll total=count0+count1;
  ld2 buf0,buf1,buf2;
  for(ll i=support1;i<= support_all && i<= count1;i++){
    combination(buf0,count1,i);
    combination(buf1,count0,support_all-i);
    buf2=buf0*buf1;
    pre_p=pre_p+buf2;
  }
  ld2 buf3;
  combination(buf3,total,support_all);
  p=pre_p/buf3;
  return p;
};

void print_result(string let,pattern &pattern,ll num_minsup,double alpha,ll minsup,ll total,ll count0,ll count1,database db,string fname_nsp){
  int i,count_sig=0;
  ld2 delta(alpha/(double)num_minsup);

  ofstream fs_nsp;
  if(flag_nsp){
    fs_nsp.open(fname_nsp,ios::app);
    if(!fs_nsp){
      cout<<"file \""<<fname_nsp<<"\" open error"<<endl;
      exit(EXIT_FAILURE);
    }        
  }
  if(debug)cout<<"letters+wild card: "<<let<<endl;
  printf("the total size of the datasets: %Ld\nthe number of negative data: %Ld\nthe number of positive data: %Ld\n",total,count0,count1);
  cout<<"Significant Level after Multiple Correction: ";
  cout<<delta;//ldprintf
  cout<<endl;
  cout<<"the number of frequent patterns: "<<num_minsup<<endl;
  if(debug){
    cout<<"minsup: "<<minsup<<endl;
    cout<<"l(minsup-1): ";
    ld2 buf_l;
    l(buf_l,minsup-1,count0,count1);
    cout<<buf_l;
    cout<<endl;
    cout<<"l(minsup): ";
    l(buf_l,minsup,count0,count1);
    cout<<buf_l;
    cout<<endl;
  }
  if(1-(debug||flag_testable))printf("\nStatistical significant patterns:\n");
  for(ll i=0;i<num_minsup;i++){
    get<0>(pattern[i])=p_value(get<2>(pattern[i]),get<3>(pattern[i]),count0,count1);
  }
  sort(pattern.begin(),pattern.end()); 
  string pattern_complement;
  for(i=0;i<num_minsup;i++){
    if(debug||flag_testable){
      printf("pattern[%d]=",i);
      cout<<get<1>(pattern[i])<<" ";
      cout<<"p_value: ";
      cout<<get<0>(pattern[i]);//ldprintf
      cout<<"; reject? ";
      if(get<0>(pattern[i])<=delta){
        printf("Yes;\n\n");
      }else{
        printf("No;\n\n");
      }
    }else{
      if(get<0>(pattern[i])<=delta){
        count_sig++;
        printf("\"");
        cout<<get<1>(pattern[i]);
        pattern_complement=complement(get<1>(pattern[i]));
        if(flag_complement==1 && get<1>(pattern[i])!=pattern_complement){
          cout<<"\" | \""<<pattern_complement;
        }
        cout<<"\": p_value: ";
        cout<<get<0>(pattern[i]);//ldprintf
        cout<<endl;
      }else{
        break;
      }
    }
  }
  printf("\nthe number of significant patterns: %d\n",count_sig);

  if(flag_nsp){
    fs_nsp<<count_sig<<endl;
  }
}
