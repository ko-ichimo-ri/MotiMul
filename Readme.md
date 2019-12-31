# Motif Mining with Multiple Hypothsis Testing 

Build with the command "make". 

#Usage

./main [-l string] [-a double] [-s number] [-S number] [-g number] [-G number] [-n number] [-N number] [FILE]   

Do pattern mining for the dataset in FILE with the significant level.

##Option  
-l  
 Configure characters given in the database you would like to analyze. The default value is "abcdefghijklmnopqrstuvwxyz1234567890".  
-a  
  Configure the significance level. The default value is 0.05.  
-s  
  Configure the minimum value of the length of patterns. If you set the value of argument a negative integer, the minimum value is not restricted.  
-S  
  Configure the maximum value of the length of patterns. If you set the value of argument a negative integer, the maximum value is not restricted.  
-g 
  Configure the minimum value of the length of gaps. If you set the value of argument a negative integer, the minimum value is not restricted.  
-G   
  Configure the maximum value of the length of gaps. If you set the value of argument a negative integer, the maximum value is not restricted.  
-n 
  Configure the minimum value of the number of gaps. If you set the value of argument a negative integer, the minimum value is not restricted.  
-N
  Configure the maximum value of the number of gaps. If you set the value of argument a negative integer, the maximum value is not restricted.  
-w
  Set wild card.