# Motif Mining with Multiple Hypothsis Testing 

Build with the command "make". 

## Requirement  
 GNU MP 6.2.0  (C++ Support)
 To install it, see [this URL](https://gmplib.org/manual/Installing-GMP.html).  
 Notice that the build option "--enable-cxx" is necessary for configuration like this:  
 ./configure --enable-cxx  

## Usage

./main [-a float] [-w non-negative integer] [FILE (negative dataset)] [FILE (positive dataset)]   

Do pattern mining with the statistical significance for negative and positive datasets in 2 FASTA format FILEs.

### Option  
-a  
  Configure the significance level. The default value is 0.05.  
-w  
  Set the number of wildcards. The default number is 0. The wildcard "\*" is used instead of one character.  

## Example1  
$ ./main data_negative.txt data_positive.txt   
Significant Level before Multiple Correction: 0.05  
minsup(one-path): 4  
minsup(last): 8  
the total size of the datasets: 20  
the number of negative data: 10  
the number of positive data: 10  
Significant Level after Multiple Correction: 0.00121951  
the number of frequent patterns: 41  

Statistical significant patterns:  
"ATGCA": p_value: 5.41254e-06  
"TATGC": p_value: 5.41254e-06  
"TATGCA": p_value: 5.41254e-06  
"TTATG": p_value: 5.41254e-06  
"TTATGC": p_value: 5.41254e-06  
"TTATGCA": p_value: 5.41254e-06  
"ACA": p_value: 5.9538e-05  
"ACAC": p_value: 5.9538e-05  
"ATGC": p_value: 5.9538e-05  
"TATG": p_value: 5.9538e-05  
"TTA": p_value: 5.9538e-05  
"TTAT": p_value: 5.9538e-05  

the number of significant patterns: 12

time: 0.015625 seconds

## Example2  
$ ./main -a 0.01 -w 1 data_negative.txt data_positive.txt  
wild card: \*  
Significant Level before Multiple Correction: 0.01  
minsup(one-path): 6  
minsup(last): 9  
the total size of the datasets: 20  
the number of negative data: 10  
the number of positive data: 10  
Significant Level after Multiple Correction: 8.92857e-05  
the number of frequent patterns: 112  
 
Statistical significant patterns:  
"A\*ACA": p_value: 5.41254e-06  
"A\*ACAC": p_value: 5.41254e-06  
"A\*GCA": p_value: 5.41254e-06  
"AT\*CA": p_value: 5.41254e-06  
"ATGCA": p_value: 5.41254e-06  
"ATGCA\*A": p_value: 5.41254e-06  
"ATGCA\*AC": p_value: 5.41254e-06  
"ATGCA\*ACA": p_value: 5.41254e-06  
"ATGCA\*ACAC": p_value: 5.41254e-06  
"CA\*AC": p_value: 5.41254e-06  
"CA\*ACA": p_value: 5.41254e-06  
"CA\*ACAC": p_value: 5.41254e-06  
"GCA\*AC": p_value: 5.41254e-06  
"GCA\*ACA": p_value: 5.41254e-06  
"GCA\*ACAC": p_value: 5.41254e-06  
"T\*ATGC": p_value: 5.41254e-06  
"T\*ATGCA": p_value: 5.41254e-06  
"TA\*GC": p_value: 5.41254e-06  
"TA\*GCA": p_value: 5.41254e-06  
"TAT\*CA": p_value: 5.41254e-06  
"TATG\*A": p_value: 5.41254e-06  
"TATGC": p_value: 5.41254e-06  
"TATGCA": p_value: 5.41254e-06  
"TATGCA\*A": p_value: 5.41254e-06  
"TATGCA\*AC": p_value: 5.41254e-06  
"TATGCA\*ACA": p_value: 5.41254e-06  
"TATGCA\*ACAC": p_value: 5.41254e-06  
"TGCA\*AC": p_value: 5.41254e-06  
"TGCA\*ACA": p_value: 5.41254e-06  
"TGCA\*ACAC": p_value: 5.41254e-06  
"TT\*TG": p_value: 5.41254e-06  
"TT\*TGC": p_value: 5.41254e-06  
"TT\*TGCA": p_value: 5.41254e-06  
"TTA\*G": p_value: 5.41254e-06  
"TTA\*GC": p_value: 5.41254e-06  
"TTA\*GCA": p_value: 5.41254e-06  
"TTAT\*C": p_value: 5.41254e-06  
"TTAT\*CA": p_value: 5.41254e-06  
"TTATG": p_value: 5.41254e-06  
"TTATG\*A": p_value: 5.41254e-06  
"TTATGC": p_value: 5.41254e-06  
"TTATGCA": p_value: 5.41254e-06  
"TTATGCA\*A": p_value: 5.41254e-06  
"TTATGCA\*AC": p_value: 5.41254e-06  
"TTATGCA\*ACA": p_value: 5.41254e-06  
"TTATGCA\*ACAC": p_value: 5.41254e-06  
"ACA": p_value: 5.9538e-05  
"ACAC": p_value: 5.9538e-05  
"ATG\*A": p_value: 5.9538e-05  
"ATGC": p_value: 5.9538e-05  
"CA\*A": p_value: 5.9538e-05  
"GCA\*A": p_value: 5.9538e-05  
"T\*ATG": p_value: 5.9538e-05  
"TA\*G": p_value: 5.9538e-05  
"TAT\*C": p_value: 5.9538e-05  
"TATG": p_value: 5.9538e-05  
"TGCA\*A": p_value: 5.9538e-05  
"TTA": p_value: 5.9538e-05  
"TTAT": p_value: 5.9538e-05  
  
the number of significant patterns: 59

time: 0.031250 seconds
