import sys
import numpy
import os
import pandas as pd

mainDir='.'
attributes=['time','reject','factor']
exception_list=[mainDir]

fnameout='shortest_motif.log'
print(fnameout)
if os.path.exists(fnameout):
    os.remove(fnameout)
fout=open(fnameout,'w+')

def write_typical(fin,fout):
    length_min=100000000000
    list_result=[]
    for s_read in fin:
        if 'p_value' in s_read:
            length=s_read.rfind('\"')-s_read.find('\"')-1
            if length<length_min:
                list_result=[s_read]
                length_min=length
            elif length==length_min:
                list_result.append(s_read)
    for result in list_result:
        fout.write(result)
    fout.write('size: '+str(length_min)+'\n')
    return None

for current, dirs, files in os.walk(mainDir):
        print(current)
        for directory in dirs:
            for current2, dirs2, files2 in os.walk(directory):
                if not (directory in exception_list):
                    fnameout='shortest_motif_'+directory+'.log'
                    fout2=open(fnameout,'w+')
                    for fnamein in files2:
                        fnamein='.\\'+directory+'\\'+fnamein
                        fin=open(fnamein,'r')
                        fout.write(fnamein+'\n')
                        write_typical(fin,fout)
                        fout.write('\n\n')
                        fin.close()
                        fin=open(fnamein,'r')
                        fout2.write(fnamein+'\n')
                        write_typical(fin,fout2)
                        fout2.write('\n\n')
                        fin.close()