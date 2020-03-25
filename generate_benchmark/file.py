import sys
import numpy
import os
import pandas as pd
print('hoge')
mainDir='.'
attributes=['time','reject','factor']
for current, dirs, files in os.walk(mainDir):
        print(current)
        for directory in dirs:
            directory=directory.replace('./','')
            if not (directory == 'figure'):
                for attribute in attributes:
                    for j in range(0,3):
                        fnameout='./'+directory+'/'+attribute+'_wild'+str(j)+'.log'
                        fnamein='./'+directory+'/'+attribute+'_wild'+str(j)+'_buf.log'
                        print(fnamein,fnameout)
                        if os.path.exists(fnamein):
                            os.remove(fnamein)
                        if os.path.exists(fnameout):
                            os.remove(fnameout)
                        fin=open(fnamein,'a')
                        for i in range(1,12):
                            fnameresults='./'+directory+'/'+attribute+str(i)+'-'+str(j)+'.log'
                            if os.path.exists(fnameresults):
                                fresults=open(fnameresults,'r')
                                print(fnameresults)
                                s=fresults.read()
                                print(s)
                                fin.write(s+'\n')
                        fin.close()
                        fin=open(fnamein,'r')
                        fout=open(fnameout,'w+')                    
                        for line in numpy.array([s.strip('\n').split(',') for s in fin]).T:
                                fout.write(",".join(line) + "\n")
                        fin.close()
                        os.remove(fnamein)            