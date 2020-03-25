import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('Agg')
import numpy as np
import os
import pandas as pd

#mainDir='~/thesis/MMMHT/generate_benchmark'
mainDir='.'

exceptionList=['.','FWER','figure']
title={
    'length_data':'',
    'length_pattern':'',
    'ratio':'',
    'num_data':''
    }
name_x={
    'length_data':'Lenth of Each Data',
    'length_pattern':'Length of Motif',
    'ratio':'Ratio of Significant Subsequence with Tag 1',
    'num_data':'Number of Data in Dataset'
    }
name_y={
    'time':'Execution Time [s]',
    'factor':'Correction Factor',
    'reject':'Ratio of Correct Detections'
    }
x_list={
    'length_data': np.array([20*i for i in range(1,10+1)]),
    'length_pattern':np.array([i for i in range(1,10+1)]),
    'ratio':np.array([0.1*i for i in range(0,10+1)]),
    'num_data':np.array([50*i for i in range(1,10+1)])
    }
attributes=['time','reject','factor']

for directory, dirs, files in os.walk(mainDir):
        print(directory)
        directory=directory.replace('.\\','').replace('./','')
        print(directory)
        if(not (directory in exceptionList)):
            for attribute in attributes:
                fig, ax = plt.subplots()
                ax.set_title(title[directory])
                ax.set_xlabel(name_x[directory])
                ax.set_ylabel(name_y[attribute])
                for i in range(3):
                    name='./'+directory+'/'+attribute+'_wild'+str(i)+'.log'
                    print(name)
                    data = pd.read_csv(name, header=None)
                    print(data.head())
                    y=list(data.mean())
                    print(y)
                    print(x_list[directory])
                    ax.plot(x_list[directory],y,label=(str(i)+' wildcards'))
                ax.legend(loc=0)
                plt.savefig("./figure/"+attribute+"_"+directory+".png")
