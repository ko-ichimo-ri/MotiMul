import sys
import numpy
import os
import pandas as pd

n=10

mainDir='.'
attributes=['time','reject','factor']
exception_list=[mainDir]

fnameout='top'+str(n)+'.log'
print(fnameout)
if os.path.exists(fnameout):
    os.remove(fnameout)
fout=open(fnameout,'w+')
def write_top(fin,fout,n):
    num=0
    for s_read in fin:
        if num==0:
            if 'Statistical significant' in s_read:
                num=1
        else:
            if num <= n:
                fout.write(s_read)
                num+=1
            else:
                break
    return None

for current, dirs, files in os.walk(mainDir):
        print(current)
        for directory in dirs:
            for current2, dirs2, files2 in os.walk(directory):
                if not (directory in exception_list):
                    fnameout='top'+str(n)+'_'+directory+'.log'
                    fout2=open(fnameout,'w+')
                    for fnamein in files2:
                        fnamein='.\\'+directory+'\\'+fnamein
                        fin=open(fnamein,'r')
                        fout.write(fnamein+'\n')
                        write_top(fin,fout,n)
                        fout.write('\n\n')
                        fin.close()
                        fin=open(fnamein,'r')
                        fout2.write(fnamein+'\n')
                        write_top(fin,fout2,n)
                        fout2.write('\n\n')
                        fin.close()