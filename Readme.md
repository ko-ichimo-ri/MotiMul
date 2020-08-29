# MotiMul (v1.2.0)  

Build with the command "make". 

## Requirement  
 GNU MP 6.2.0  (C++ Support)
 
 To install that,  
 `sudo apt-get install libgmp3-dev`  
 if you use Linux.  
 Or see [this URL](https://gmplib.org/manual/Installing-GMP.html). Notice that the build option "--enable-cxx" is necessary for configuration like this:  
 ./configure --enable-cxx  

## Usage

./main [-a float] [-w non-negative integer] [-l integer] [-L integer] [-s string] [-v] [FILE (negative dataset)] [FILE (positive dataset)]   

Do pattern mining with the statistical significance for negative and positive datasets in 2 FASTA format FILEs.

### Option  
-a (float)  
  Set the significance level. The default value is 0.05.  
-w (non-negative integer)  
  Set the number of wildcards. The default number is 0. The wildcard "\*" is used instead of one character.  
-l (integer)  
  Set the minimum length of output sequences. If the option argument is negative, there are no constraints on the minimum length. The default value is -1.  
-L (integer)  
  Set the maximum length of output sequences. If the option argument is negative, there are no constraints on the maximum length. The default value is -1.  
-s (string)  
  Set the kind of sequences for the analysis. The default value is "dna".  
- If the option argument is 'd' or 'dna', one can analyze DNA sequences, which are the strings composed of the alphabets 'A', 'T', 'G', 'C'.  
- If the option argument is 'r' or 'rna', one can analyze RNA sequences, which are the strings composed of the alphabets 'A', 'U', 'G', 'C'.  
- If the option argument is 'p' or 'protein', one can analyze protein sequences, which are the strings composed of the alphabets 'G', 'A', 'V', 'L', 'I', 'P', 'F', 'W', 'C', 'M', 'Y', 'S', 'T', 'N', 'Q', 'H', 'K', 'R', 'D', 'E'.  

-v  
  Print the MotiMul version number and exit.

## Example1  
$ ./main data_negative.fa data_positive.fa   
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
$ ./main -a 0.01 -w 1 -l 4 -L 6 -s d data_negative.fa data_positive.fa  
wild card: \*  
Significant Level before Multiple Correction: 0.01  
minsup(one-path): 6  
minsup(last): 9  
the total size of the datasets: 20  
the number of negative data: 10  
the number of positive data: 10  
Significant Level after Multiple Correction: 0.000222222  
the number of frequent patterns: 45  
  
Statistical significant patterns:  
"A\*ACA": p_value: 5.41254e-06  
"A\*ACAC": p_value: 5.41254e-06  
"A\*GCA": p_value: 5.41254e-06  
"AT\*CA": p_value: 5.41254e-06  
"ATGCA": p_value: 5.41254e-06  
"CA\*AC": p_value: 5.41254e-06  
"CA\*ACA": p_value: 5.41254e-06  
"GCA\*AC": p_value: 5.41254e-06  
"T\*ATGC": p_value: 5.41254e-06  
"TA\*GC": p_value: 5.41254e-06  
"TA\*GCA": p_value: 5.41254e-06  
"TAT\*CA": p_value: 5.41254e-06  
"TATG\*A": p_value: 5.41254e-06  
"TATGC": p_value: 5.41254e-06  
"TATGCA": p_value: 5.41254e-06  
"TT\*TG": p_value: 5.41254e-06  
"TT\*TGC": p_value: 5.41254e-06  
"TTA\*G": p_value: 5.41254e-06  
"TTA\*GC": p_value: 5.41254e-06  
"TTAT\*C": p_value: 5.41254e-06  
"TTATG": p_value: 5.41254e-06  
"TTATGC": p_value: 5.41254e-06  
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
"TTAT": p_value: 5.9538e-05  
  
the number of significant patterns: 33  
  
time: 0.015625 seconds  

## License  

Copyright (c) [2020] [Koichi Mori]  
This software is released under the MIT License, see LICENSE.txt.  
