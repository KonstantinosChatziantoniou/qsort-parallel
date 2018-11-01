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
#include <cilk/cilk.h>
#include <cilk/cilk_api_linux.h>


void qsort_c(int *v, int n);
void initialise(int minN);

int minNforParallel;
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
    if (v[j] < pivot){
      swap(v,i,j);
      i++;
    }

  swap(v, i, n - 1);
  return (i);
}

/* qsortcilk -- Entry point for QuickSort 
   added cilk spawn for parallelization   */
void qsort_cilk(int *v, int n, int minN) {
  initialise(minN);
  qsort_c(v,n);
}

void qsort_c(int *v, int n) {
  if (n > 1) {
    int p = partition(v, n);
    if(n > minNforParallel){
      cilk_spawn qsort_c(v,p);
      qsort_c(&v[p+1],n-p-1);
      //cilk_sync;
    }else{
      qsort_c(v,p);
      qsort_c(&v[p+1],n-p-1);
    }    
  }
}

void initialise(int minN){
  minNforParallel = pow(2,minN);
}
