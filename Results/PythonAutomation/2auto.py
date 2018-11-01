import os
import subprocess
import pandas as pd
import numpy as np



folders_of_par = ["qsort_pthreads", "qsort_cilk", "qsort_openmp", "qsort_pthreads_beastmaster_9000"]
main_name = "/qsort.exe"

reps = 10
p_arr = []
n_arr = []
vers_arr = []
min_p_arr = []
min_n_arr = []
min_vers_arr = []
for fld in folders_of_par:
    print(fld)
    n_arr = []
    min_n_arr = []
    for n in range(12,21):
        p_arr = [n]
        min_p_arr =[n]
        min = 10
        print('n = ' + str(n))
        for p in range(1,9):
            print('p = ' + str(p))
            time = 0
            for rep in range(0,reps):
                output = subprocess.run(['../../' + fld + main_name , '24' , str(p) , str(n)], stdout = subprocess.PIPE)
                temp = float(output.stdout.decode('utf-8'))/reps
                time = time + temp
                if min > temp:
                    min = temp
            p_arr.append(time)
            min_p_arr.append(min)
        n_arr.append(p_arr)
        min_n_arr.append(min_p_arr)
    vers_arr.append(n_arr)
    min_vers_arr.append(min_n_arr)



output_folders = ['outExtraPth', 'outExtraCilk' , 'outExtraOpenmp' , 'outExtraPth9000']
extension = '.csv'
rel_path = '../'

for i in range(0,4):
    numpy_array = np.array(vers_arr[i])
    cs = pd.DataFrame(numpy_array,columns = ['N' , '1' , '2' , '3' , '4' , '5' , '6', '7' , '8'])
    cs.to_csv(rel_path + output_folders[i] + extension , index = False)
print(numpy_array)

output_folders = ['minOutExtraPth', 'minOutExtraCilk' , 'minOutExtraOpenmp' , 'minOutExtraPth9000']
for i in range(0,4):
    numpy_array = np.array(min_vers_arr[i])
    cs = pd.DataFrame(numpy_array,columns = ['N' , '1' , '2' , '3' , '4' , '5' , '6', '7' , '8'])
    cs.to_csv(rel_path + output_folders[i] + extension , index = False)
print(numpy_array)