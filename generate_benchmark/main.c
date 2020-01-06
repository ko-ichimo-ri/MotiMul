#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "macro.h"
//dbのfreeをやる

#define N_MAX 1000

char let[NUMBER_LETTER]="abcdefghijklmnopqrstuvwxyz1234567890";
char subseq[NUMBER_LETTER]="";
char file_name_positive[NUMBER_LETTER]="data0.txt";
char file_name_negative[NUMBER_LETTER]="data1.txt";

int let_len = 36;
int sub_len = 0;
int g=0,G=0;
int n=10,m=10,L=10;
double p=1.0,q=0.0;
char wild_card='*';
int flag_seed=0;
//  int debug=0;

int check_int(int n,int gap_list[N_MAX],int g){
  int i;
  for(i=0;i<g;i++){
    if(n==gap_list[i]) return 1;
  }
  return 0;
}

void generate_data(int num,int n,double p,unsigned seed, FILE*fp){
  if(flag_seed==0){
    srand((unsigned)time(NULL)+num*600-300);
  }else{
    srand(2*seed-num);
  }
  int gap_list[N_MAX];
  for(int i=0;i<g;i++)gap_list[i]=-1;
  int i_g=0;
  int g_random,sub_count;
  for(int count1=0;count1<n;count1++){
//    printf("count1=%d\n",count1);
    if(count1<n*p){
      i_g=0;
      while(i_g<g){
//        printf("rand\n");
        g_random=rand()%(sub_len-1);//the last character will never be the beginning of a gap.
        if(1-check_int(g_random,gap_list,g)){
          gap_list[i_g]=g_random;
          i_g++;
        }
      }
      int i_initial=rand()%(L-sub_len-g*G);
      sub_count=0;
      fprintf(fp,">foo bar\n");     
      for(int i=0;i<L;i++){
        if(i<i_initial || sub_count>=sub_len){
//          printf("0\n");
          fprintf(fp,"%c",let[rand()%let_len]);
        }else{
//          printf("1\n");
          if(subseq[sub_count]!=wild_card){
            fprintf(fp,"%c",subseq[sub_count]);
          }else{
            fprintf(fp,"%c",let[rand()%let_len]);
          }

          if(check_int(sub_count,gap_list,g)){
            for(int j=0;j<G;j++){
              fprintf(fp,"%c",let[rand()%let_len]);
              i++;
            }
          }
          sub_count++;
        }
      }
    }else{
      fprintf(fp,">hoge \n");
      for(int i=0;i<L;i++){
        fprintf(fp,"%c",let[rand()%let_len]);
      }
    }
    
    if(count1!=n-1)
        fprintf(fp,"\n");
  }    
}

int main(int argc,char **argv){
  unsigned seed=0;

  extern char *optarg;
  extern int optind;
  int opt;

  strcpy(file_name_positive,argv[optind]);
  strcpy(file_name_negative,argv[optind+1]);

  while((opt=getopt(argc,argv,"l:s:p:q:n:m:L:g:G:dw:r:"))!=EOF){
    switch(opt){
      case 'l':
        strcpy(let,optarg);
        break;
      case 's': 
        strcpy(subseq,optarg);
        break;
      case 'p':
        p=atof(optarg); //the probability of appearance of s on data 1
        break;
      case 'q':
        q=atof(optarg); ////the probability of appearance of s on data 1
        break;

      case 'n':
        n=atoi(optarg); //the number of data 1 on database
        break;
      case 'm':
        m=atoi(optarg); //the number of data 0 on database
        break;

      case 'L':
        L=atoi(optarg); //the length of data
        break;

      case 'g':
        g=atoi(optarg);
        break;
      case 'G':
        G=atoi(optarg);
        break;
//      case 'd':
//        debug=1;
//      break;
      case 'w':
        wild_card=optarg[0];
        break;
      case 'r':
        flag_seed=1;
        seed=(unsigned)atoi(optarg);
        break;

      default:
        break;
    }
  }

  FILE *fp_p, *fp_n;
  if ((fp_p = fopen(file_name_positive, "w")) == NULL) {
    fprintf(stderr, "%sのオープンに失敗しました.\n", file_name_positive);
    exit(EXIT_FAILURE);
  }
  if ((fp_n = fopen(file_name_negative, "w")) == NULL) {
    fprintf(stderr, "%sのオープンに失敗しました.\n", file_name_negative);
    exit(EXIT_FAILURE);
  }

  let_len = strlen(let);
  sub_len = strlen(subseq);

  if(sub_len<=g-1){
    perror("Tha number of gap is too much with reference to the subsequence");
  }
  if(sub_len+g*G>=L){
    perror("the total configured length is too long");
  }

  generate_data(1,n,p,seed,fp_p);
  generate_data(0,m,q,seed,fp_n);

  fclose(fp_p);
  fclose(fp_n);
  return 0;
}

