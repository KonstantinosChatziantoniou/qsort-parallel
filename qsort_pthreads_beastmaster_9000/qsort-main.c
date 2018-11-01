/**********************************************************************
 *
 * qsort.c -- Sequential implementation of QuickSort
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

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-pthread.h"
#include <assert.h>
#include <math.h>

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);

/* --- Entry POINT --- */
int main(int argc, char **argv) {
  int minN = 15;
  /* parse input */
  if(argc == 4){
    minN = atoi(argv[3]);
  }else if (argc != 3) {
    printf("Usage: %s q and p\n  where n=2^q is problem size (power of two) and n2=2^p is the number of threads \n", 
	   argv[0]);
    exit(1);
  }

  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double seq_time;
 
  /* initiate vector of random integerts */
  int n  = 1<<atoi(argv[1]);
  int *a = (int *) malloc(n * sizeof(int));
  /* getting number of max threads from input*/
  int power = atoi(argv[2]);
  if(power > 8) power = 8;
  if(power < 0) power = 1;
  int num_of_threads = pow(2, power); 

  /* initialize vector */
  init(a, n);

  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  qsort_pthread(a, n, num_of_threads, minN);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  int pass = test(a, n);
  assert( pass != 0 );
  
    
  /* print execution time */
  printf("%f", seq_time);
  /* exit */
  return 0;
  
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  int pass = 1;
  for(int i = 0; i < n-1; i++){
    if(a[i] > a[i+1]){
      printf("error at %d\n" , a[i]);
      pass = 0;
    }
  }

  
  return pass;
  
  
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  int i;
  srand(666);
  if(0){
    srand(666);
  }
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d \n", a[i]);
  }
  printf("\n");
}


