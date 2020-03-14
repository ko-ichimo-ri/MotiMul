# Motif Mining with Multiple Hypothsis Testing 

Build with the command "make". 

#Usage

./main [-w number] [FILE (negative dataset)] [FILE (positive dataset)]   

Do pattern mining for negative and positive datasets in 2 FASTA format FILEs with the significant level.

##Option  
-w
  Set the number of wildcards. The wildcard "\*" is used instead of one character.  

###Example1
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

time: 0.000000 seconds

###Example2
$ ./main -w 1 data_negative.txt data_positive.txt
letters: ACGT
wild card: *
alpha: 0.05
debug: off
minsup(one-path): 4
minsup(last): 9
total: 20
0: 10
1: 10
delta: 0.000248756
the number of frequent patterns: 201

Statistical significant pattern:
"A\*ACA": p_value: 5.41254e-06
"A\*ACAC": p_value: 5.41254e-06
"A\*ACACG": p_value: 5.41254e-06
"A\*ACACGG": p_value: 5.41254e-06
"A\*ACG": p_value: 5.41254e-06
"A\*ACGG": p_value: 5.41254e-06
"A\*GCAA": p_value: 5.41254e-06
"AA\*AC": p_value: 5.41254e-06
"AA\*ACA": p_value: 5.41254e-06
"AA\*ACAC": p_value: 5.41254e-06
"AA\*ACACG": p_value: 5.41254e-06
"AA\*ACACGG": p_value: 5.41254e-06
"AC\*CGG": p_value: 5.41254e-06
"ACA\*G": p_value: 5.41254e-06
"ACA\*GG": p_value: 5.41254e-06
"ACAC\*G": p_value: 5.41254e-06
"ACACG": p_value: 5.41254e-06
"ACACGG": p_value: 5.41254e-06
"AT\*CAA": p_value: 5.41254e-06
"ATG\*AA": p_value: 5.41254e-06
"ATGC\*A": p_value: 5.41254e-06
"ATGCAA": p_value: 5.41254e-06
"ATGCAA\*A": p_value: 5.41254e-06
"ATGCAA\*AC": p_value: 5.41254e-06
"ATGCAA\*ACA": p_value: 5.41254e-06
"ATGCAA\*ACAC": p_value: 5.41254e-06
"ATGCAA\*ACACG": p_value: 5.41254e-06
"ATGCAA\*ACACGG": p_value: 5.41254e-06
"CAA\*AC": p_value: 5.41254e-06
"CAA\*ACA": p_value: 5.41254e-06
"CAA\*ACAC": p_value: 5.41254e-06
"CAA\*ACACG": p_value: 5.41254e-06
"CAA\*ACACGG": p_value: 5.41254e-06
"GCAA\*A": p_value: 5.41254e-06
"GCAA\*AC": p_value: 5.41254e-06
"GCAA\*ACA": p_value: 5.41254e-06
"GCAA\*ACAC": p_value: 5.41254e-06
"GCAA\*ACACG": p_value: 5.41254e-06
"GCAA\*ACACGG": p_value: 5.41254e-06
"T\*ATG": p_value: 5.41254e-06
"T\*ATGC": p_value: 5.41254e-06
"T\*ATGCA": p_value: 5.41254e-06
"T\*ATGCAA": p_value: 5.41254e-06
"TA\*GC": p_value: 5.41254e-06
"TA\*GCA": p_value: 5.41254e-06
"TA\*GCAA": p_value: 5.41254e-06
"TAT\*CA": p_value: 5.41254e-06
"TAT\*CAA": p_value: 5.41254e-06
"TATG": p_value: 5.41254e-06
"TATG\*A": p_value: 5.41254e-06
"TATG\*AA": p_value: 5.41254e-06
"TATGC": p_value: 5.41254e-06
"TATGC\*A": p_value: 5.41254e-06
"TATGCA": p_value: 5.41254e-06
"TATGCAA": p_value: 5.41254e-06
"TATGCAA\*A": p_value: 5.41254e-06
"TATGCAA\*AC": p_value: 5.41254e-06
"TATGCAA\*ACA": p_value: 5.41254e-06
"TATGCAA\*ACAC": p_value: 5.41254e-06
"TATGCAA\*ACACG": p_value: 5.41254e-06
"TATGCAA\*ACACGG": p_value: 5.41254e-06
"TGCAA\*A": p_value: 5.41254e-06
"TGCAA\*AC": p_value: 5.41254e-06
"TGCAA\*ACA": p_value: 5.41254e-06
"TGCAA\*ACAC": p_value: 5.41254e-06
"TGCAA\*ACACG": p_value: 5.41254e-06
"TGCAA\*ACACGG": p_value: 5.41254e-06
"TT\*TG": p_value: 5.41254e-06
"TT\*TGC": p_value: 5.41254e-06
"TT\*TGCA": p_value: 5.41254e-06
"TT\*TGCAA": p_value: 5.41254e-06
"TTA\*G": p_value: 5.41254e-06
"TTA\*GC": p_value: 5.41254e-06
"TTA\*GCA": p_value: 5.41254e-06
"TTA\*GCAA": p_value: 5.41254e-06
"TTAT": p_value: 5.41254e-06
"TTAT\*C": p_value: 5.41254e-06
"TTAT\*CA": p_value: 5.41254e-06
"TTAT\*CAA": p_value: 5.41254e-06
"TTATG": p_value: 5.41254e-06
"TTATG\*A": p_value: 5.41254e-06
"TTATG\*AA": p_value: 5.41254e-06
"TTATGC": p_value: 5.41254e-06
"TTATGC\*A": p_value: 5.41254e-06
"TTATGCA": p_value: 5.41254e-06
"TTATGCAA": p_value: 5.41254e-06
"TTATGCAA\*A": p_value: 5.41254e-06
"TTATGCAA\*AC": p_value: 5.41254e-06
"TTATGCAA\*ACA": p_value: 5.41254e-06
"TTATGCAA\*ACAC": p_value: 5.41254e-06
"TTATGCAA\*ACACG": p_value: 5.41254e-06
"TTATGCAA\*ACACGG": p_value: 5.41254e-06
"AC\*CG": p_value: 5.9538e-05
"ACAC": p_value: 5.9538e-05
"AT\*CA": p_value: 5.9538e-05
"ATG": p_value: 5.9538e-05
"ATG\*A": p_value: 5.9538e-05
"ATGC": p_value: 5.9538e-05
"ATGCA": p_value: 5.9538e-05
"CAA\*A": p_value: 5.9538e-05
"GCAA": p_value: 5.9538e-05
"T\*AT": p_value: 5.9538e-05
"T\*TGC": p_value: 5.9538e-05
"T\*TGCA": p_value: 5.9538e-05
"T\*TGCAA": p_value: 5.9538e-05
"TG\*AA": p_value: 5.9538e-05
"TGC\*A": p_value: 5.9538e-05
"TGCAA": p_value: 5.9538e-05
"TTA": p_value: 5.9538e-05

the number of significant patterns: 109

time: 0.078125 seconds
