/**********************************************************************
 *
 * qsort-sequential.c -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/
/**********************************************************************
 * Modified by
 * Konstantinos Chatziantoniou <konstantic@ece.auth.gr
 * 
 * ********************************************************************/



#include <stdio.h>
#include <math.h>
#include <omp.h>
int minNforPar;
void initialise(int minN);
void qsort_omp(int* v, int n);
/* swap -- swap elements k and l of vector v */
void swap(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}


/* partition -- in-place update of elements */
int partition(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;
  
  for (int j = 0; j < n - 1; j++) 
    if (v[j] < pivot) 
      swap(v,i++,j);

  swap(v, i, n - 1);
  return (i);
}

/* qsortseq -- Entry point for QuickSort */
void qsort_openmp(int *v, int n, int minN) {
  initialise(minN);
  qsort_omp(v,n);
  

}

void qsort_omp(int *v, int n){
  if (n > 1) {
    int p = partition(v, n);
    if(n > minNforPar){
      #pragma omp task 
      {
        qsort_omp(v,p);
      }
    
    }else{
      qsort_omp(v,p);
    }
    
    qsort_omp(&v[p+1],n-p-1);
    
    
  }
}

void initialise(int minN){
  minNforPar = pow(2,minN);
}

