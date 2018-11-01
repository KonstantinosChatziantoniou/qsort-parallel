##TODO compare seq with others using 4 threads
##TODO compare parallel with 2^24 elements for different number of threads
##using python3
import os
import subprocess
import pandas as pd
import numpy as np


current_dir = os.path.dirname(os.path.realpath(__file__))
folders_of_seq = ["qsort_lib", "qsort_sequential"]
folders_of_par = ["qsort_pthreads", "qsort_cilk", "qsort_openmp", "qsort_pthreads_beastmaster_9000"]
main_name = "/qsort.exe"

th_num = [5 ,2 ,3 ,5]
opt_min_N = [16,16,16,16]
repetition_for_good_results = 10
results_diff_n = []
res_for_each = []
results_diff_minN = []
results_diff_p = []

min_results_diff_n = []
min_results_diff_minN = []
min_results_diff_p = []
min_res_for_each = []
subprocess.run(['python3',current_dir + '/2auto.py'])
dofordifferentN = True
dofordifferentP = True
dofordifferentminN = True
if(dofordifferentN):
    for i in range(12, 25):
        print('n = ' + str(i))
        res_for_each = [i]
        min_res_for_each = [i]
        ##get sequential first
        for fld in folders_of_seq:
            exe_path = current_dir + '/../../' + fld + main_name
            args = str(i)
            time = 0
            min = 10
            for rep in range(0,repetition_for_good_results):
                output = subprocess.run([exe_path , args], stdout = subprocess.PIPE)
                temp = float(output.stdout.decode('utf-8'))/repetition_for_good_results
                time = time + temp
                if min > temp:
                    min = temp
            min_res_for_each.append(min)
            res_for_each.append(time)

        ##get parallel
        index = 0
        for fld in folders_of_par:
            exe_path = current_dir + '/../../' + fld + main_name
            args = str(i)
            time = 0
            min = 10
            for rep in range(0,repetition_for_good_results):
                output = subprocess.run([exe_path , args , str(th_num[index]),str(opt_min_N[index])], stdout = subprocess.PIPE)
                temp = float(output.stdout.decode('utf-8'))/repetition_for_good_results
                time = time + temp
                if min > temp:
                    min = temp
            index = index + 1
            min_res_for_each.append(min)
            res_for_each.append(time)
        min_results_diff_n.append(min_res_for_each)
        results_diff_n.append(res_for_each)



    numpy_array = np.array(results_diff_n)
    cs = pd.DataFrame(numpy_array,columns=['elements',  'seq-stdlib','sequential', 'pthread', 'cilk', 'openmp' , 'pthread-9000'] )
    cs.set_index('elements')
    cs.to_csv(current_dir + '/../outN.csv', index=False)# , header=['sequential', 'pthread', 'cilk', 'openmp'])


    numpy_array = np.array(min_results_diff_n)
    cs = pd.DataFrame(numpy_array,columns=['elements',  'seq-stdlib','sequential', 'pthread', 'cilk', 'openmp' , 'pthread-9000'] )
    cs.set_index('elements')
    cs.to_csv(current_dir + '/../minOutN.csv', index=False)# , header=['sequential', 'pthread', 'cilk', 'openmp'])

if(dofordifferentP):
    print("doing for p")
    results_diff_p = []   
    for p in range(1,9):
        print(p)
        res_for_each = [p]
        min_res_for_each = [p]
        time = 0
        min = 10
        for fld in folders_of_par:
            exe_path = current_dir + '/../../' + fld + main_name
            time = 0
            for rep in range(0,repetition_for_good_results):
                ##print(exe_path)
                output = subprocess.run([exe_path , '24' , str(p) , '16'], stdout = subprocess.PIPE)
                temp = float(output.stdout.decode('utf-8'))/repetition_for_good_results
                time = time + temp
                if min > temp:
                    min = temp
            min_res_for_each.append(min)
            res_for_each.append(time)
        min_results_diff_p.append(min_res_for_each)
        results_diff_p.append(res_for_each)

    numpy_array = np.array(results_diff_p)
    cs = pd.DataFrame(numpy_array,columns=['num_threads', 'pthread', 'cilk', 'openmp' , 'pthread-9000'])
    cs.set_index('num_threads')
    cs.to_csv(current_dir + '/../outP.csv')

    numpy_array = np.array(min_results_diff_p)
    cs = pd.DataFrame(numpy_array,columns=['num_threads', 'pthread', 'cilk', 'openmp' , 'pthread-9000'])
    cs.set_index('num_threads')
    cs.to_csv(current_dir + '/..minOutP.csv')

if(dofordifferentminN):
    print("doing for minN")
    results_diff_minN = []
    for p in range(10,23):
        print(p)
        res_for_each = [p]
        min_res_for_each = [p]
        time = 0
        j = -1
        min = 10
        for fld in folders_of_par:
            j = j + 1
            exe_path = current_dir + '/../../' + fld + main_name
            time = 0
            for rep in range(0,repetition_for_good_results):
                ##print(exe_path)
                output = subprocess.run([exe_path , '24' , str(th_num[j]), str(p)], stdout = subprocess.PIPE)
                time = time + float(output.stdout.decode('utf-8'))/repetition_for_good_results
                if min > time:
                    min = time
            min_res_for_each.append(min)
            res_for_each.append(time)

        results_diff_minN.append(res_for_each)
        min_results_diff_minN.append(min_res_for_each)

    numpy_array = np.array(results_diff_minN)
    cs = pd.DataFrame(numpy_array,columns=['min-N', 'pthread', 'cilk', 'openmp' , 'pthread-9000'])
    cs.set_index('min-N')
    cs.to_csv(current_dir + '/../outminN.csv')

    numpy_array = np.array(min_results_diff_minN)
    cs = pd.DataFrame(numpy_array,columns=['min-N', 'pthread', 'cilk', 'openmp' , 'pthread-9000'])
    cs.set_index('min-N')
    cs.to_csv(current_dir + '/../minOutminN.csv')
        

print('end')


##subprocess.run(['python3',current_dir + '/2auto.py'])