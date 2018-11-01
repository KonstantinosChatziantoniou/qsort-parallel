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
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

//VARIABLES
typedef struct {
  int* v;
  int n;
  int id;
}pth_input;

int max_threads;                    //given by the user
pthread_t* tid;                     //array of pthread_t for the threads to be created
int* availableThreads;              //shows if a certain pthread_t is in use (1 for in use , 0 for not)
int threadCounter;
pth_input* thData;                  //data to be provided at each thread
pthread_mutex_t lock;               //necessary lock for not giving 2 threads the same pthread_t
int minNforParallel; 


//FUNCTIONS
void swap(int *v, int k, int l);
int partition(int *v, int n);
void qsort_pthread(int *v, int n, int number_of_threads, int minN);
void initialise(int minN);
int findAvailableThread();
void* th_qsort(void* input);
void seq_qsort(pth_input input);

/*memory allocation and variable instantiation*/
void initialise(int minN){
  tid = (pthread_t*)malloc(max_threads*sizeof(pthread_t));
  availableThreads = (int*)malloc(max_threads*sizeof(int));
  thData = (pth_input*)malloc(max_threads*sizeof(pth_input));
  if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        //return 1;
    }
  for(int i=0; i<max_threads; i++){
    availableThreads[i]=0;
  }
  threadCounter = 0;
  minNforParallel = (int) pow(2,minN);
}

/*searches the availableThreads array for 0 and returns the index
 *if none is available return -1*/
int findAvailableThread(){
  for(int i=0; i<max_threads; i++){
    if(availableThreads[i]==0){
      return i;
    }
  }
  return -1;
}

/*function to be created by pthread_create*/
void* th_qsort(void* input){
  pth_input* in = (pth_input*) input;
  int n = in->n;
  int*v = in->v;
  int id = in->id;
  if(n > 1){
    int p = partition(v,n);
    pth_input in2;
    in2.n = n-p-1;
    in2.v = &v[p+1];
    //if n is small enough go sequential
    if(n<minNforParallel){
      pth_input in1;
      in1.n = p;
      in1.v = v;
      seq_qsort(in1);
      seq_qsort(in2);
    }else{
      pthread_mutex_lock(&lock);
      int at = findAvailableThread();
      if(at == -1){
        //if there are no available threads, go sequential
        pthread_mutex_unlock(&lock);
        pth_input in1;
        in1.n = p;
        in1.v = v;
        seq_qsort(in1);
        seq_qsort(in2);
      }else{
        //if there is an available thread, reserve it and create pthread
        thData[at].id = at;
        thData[at].v = v;
        thData[at].n = p;
        pthread_create(&tid[at],NULL, th_qsort,&thData[at]);
        threadCounter++;
        availableThreads[at] = 1;
        pthread_mutex_unlock(&lock);
        seq_qsort(in2);
        //wait for the created thread and make it available again
        pthread_join(tid[at],NULL);
        pthread_mutex_lock(&lock);
        availableThreads[at] = 0;
        threadCounter--;
        pthread_mutex_unlock(&lock);

      }
    }
    
    
  } 
}

/*function to be called when sequential apporach is needed*/
void seq_qsort(pth_input in){
  //parsing input
  int n = in.n;
  int*v = in.v;
  if(n > 1){
    int p = partition(v,n);
    pth_input in2;
    in2.n = n-p-1;
    in2.v = &v[p+1];
    //if n is small enough go sequential
    if(n < minNforParallel){
      pth_input in1;
      in1.n = p;
      in1.v = v;
      seq_qsort(in1);
      seq_qsort(in2);
    }else{
      
      pthread_mutex_lock(&lock);
      int at = findAvailableThread();
      if(at == -1){
        //if there are no available threads, go sequential
        pthread_mutex_unlock(&lock);
        pth_input in1;
        in1.n = p;
        in1.v = v;
        seq_qsort(in1);
        seq_qsort(in2);
      }else{
        //if there is an available thread, reserve it and create pthread
        thData[at].id = at;
        thData[at].v = v;
        thData[at].n = p;
        pthread_create(&tid[at],NULL, th_qsort,&thData[at]);
        threadCounter++;
        availableThreads[at] = 1;
        pthread_mutex_unlock(&lock);
        seq_qsort(in2);
        //wait for the created thread and make it available again
        pthread_join(tid[at],NULL);
        pthread_mutex_lock(&lock);
        availableThreads[at] = 0;
        threadCounter--;
        pthread_mutex_unlock(&lock);
      }
    
    }
  }
}


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
void qsort_pthread(int *v, int n, int number_of_threads, int minN) {
  max_threads = number_of_threads;
  initialise(minN);
  

  pth_input in;
  in.n = n;
  in.v = v;
  seq_qsort(in);
  
  
  
  free(availableThreads);
  free(tid); 
  free(thData);
 
}




