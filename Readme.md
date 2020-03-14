# Motif Mining with Multiple Hypothsis Testing 

Build with the command "make". 

## Requirement  
 GNU MP 6.2.0

## Usage

./main [-w number] [FILE (negative dataset)] [FILE (positive dataset)]   

Do pattern mining with the statistical significance for negative and positive datasets in 2 FASTA format FILEs.

### Option  
-w
  Set the number of wildcards. The wildcard "\*" is used instead of one character.  

## Example  
$ ./main data_negative.txt data_positive.txt  
letters: ACGT  
alpha: 0.05  
debug: off  
minsup(one-path): 4  
minsup(last): 8  
total: 20  
0: 10  
1: 10  
delta: 0.000819672  
the number of frequent patterns: 61 
 
Statistical significant pattern:  
"ACACG": p_value: 5.41254e-06  
"ACACGG": p_value: 5.41254e-06  
"ATGCAA": p_value: 5.41254e-06  
"TATG": p_value: 5.41254e-06  
"TATGC": p_value: 5.41254e-06  
"TATGCA": p_value: 5.41254e-06  
"TATGCAA": p_value: 5.41254e-06  
"TTAT": p_value: 5.41254e-06  
"TTATG": p_value: 5.41254e-06  
"TTATGC": p_value: 5.41254e-06  
"TTATGCA": p_value: 5.41254e-06  
"TTATGCAA": p_value: 5.41254e-06  
"ACAC": p_value: 5.9538e-05  
"ATG": p_value: 5.9538e-05  
"ATGC": p_value: 5.9538e-05  
"ATGCA": p_value: 5.9538e-05  
"GCAA": p_value: 5.9538e-05  
"TGCAA": p_value: 5.9538e-05  
"TTA": p_value: 5.9538e-05  
"CACGG": p_value: 0.000357228  
"TGCA": p_value: 0.000357228  
 
the number of significant patterns: 21

time: 0.015625 seconds
