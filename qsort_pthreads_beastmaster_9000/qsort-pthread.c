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
typedef struct{
  int* v;
  int n;
  int id;
}pth_input;
pth_input* threads_data;            //data to be provided at each thread
pthread_t* threads_id;              //array of pthread_t for the threads to be created
int* availableThreads;              //shows if a certain pthread_t is in use (1 for in use , 0 for not)
int* resultFromThread;              //necessary for communication between 2 threads
int maxNforParallel;
int maxThreads;
int* flagForWait;                   //make 1, so the other thread knows it has finished the partitioning
pthread_cond_t* conds;              //array of conds, to signal the other to wake (it has finished his job earlier)
pthread_mutex_t* mutexForConds;     //array of mutex, in case 2 threads try to communicate at the same time
pthread_mutex_t lock;               //necessary lock for not giving 2 threads the same pthread_t
//for stats

//FUNCTIONS
void swap(int *v, int k, int l);
int partition(int *v, int n);
void qsort_pthread(int *v, int n, int number_of_threads, int minN);
//MUFUNCTIONS
void initialise(int maxThreads, int minN);
int strPartition(int *v, int n);
int inversePartition(int* v, int n);
int restSwaps(int* v,int n, int res1 , int res2);
void* first_thqsort(void* in);
void* thqsort(void* in);  //for pthreads
void sqsort(int* v, int n); //for seq
int findAvailableThread();
void releaseThread(int id);
void onlySqsort(int* v, int n);



void initialise(int maxTh, int minN){ 
  maxThreads = maxTh;
  maxNforParallel = pow(2,minN);
  availableThreads = (int*)malloc(maxTh*sizeof(int));
  resultFromThread = (int*)malloc(maxTh*sizeof(int));
  threads_id = (pthread_t*)malloc(maxTh*sizeof(pthread_t));
  threads_data = (pth_input*)malloc(maxTh*sizeof(pth_input));
  conds = (pthread_cond_t*)malloc(maxTh*sizeof(pthread_cond_t));
  flagForWait = (int*)malloc(maxTh*sizeof(int));
  mutexForConds = (pthread_mutex_t*)malloc(maxTh*sizeof(pthread_mutex_t));
  pthread_mutex_init(&lock,NULL);
  for(int i = 0; i < maxTh; i++){
    availableThreads[i] = 0;
    resultFromThread[i] = 0;
    flagForWait[i] = 0;
    pthread_cond_init(&conds[i],NULL);
    pthread_mutex_init(&mutexForConds[i], NULL);
  }
}
/*searches the availableThreads array for 0 and returns the index
 *if none is available return -1*/
int findAvailableThread(){
  pthread_mutex_lock(&lock);
  for(int i = 0; i < maxThreads; i++){
    if( availableThreads[i] == 0){
      availableThreads[i]= 1;
      pthread_mutex_unlock(&lock);
      return i;
    }
  }
  pthread_mutex_unlock(&lock);
  return -1;
}
/*makes the availableThread[index] zero, so it can be reused*/
void releaseThread(int id){
  pthread_mutex_lock(&lock);
  availableThreads[id] = 0;
  flagForWait[id] = 0;
  resultFromThread[id] = 0;
  pthread_mutex_unlock(&lock);
}
/*function to be called with pthread_create()*/
void* thqsort(void* in){
  pth_input* input = (pth_input*) in;
  int id = input->id;
  int n = input->n;
  int* v = input->v;
  int res2 = inversePartition(v,n);
  int p;
  //Wait for the other half of partition
  pthread_mutex_lock(&mutexForConds[id]);
  if(flagForWait[id] == 1){           // if the other thread has finished and waiting
    p = restSwaps(v,n,resultFromThread[id],res2);     //do the rest of swaps
    resultFromThread[id] = p;                         //pass the result
    pthread_cond_signal(&conds[id]);                  //and signal the other
  }else{                              // if this this thread finishes first, it sleeps
    flagForWait[id]=1;                                //states that it has finished 
    resultFromThread[id] =res2;                       //pass the result
    pthread_cond_wait(&conds[id], &mutexForConds[id]);//and sleep
    p = resultFromThread[id];
  }
  pthread_mutex_unlock(&mutexForConds[id]);
  sqsort(v , p);                      //proceed with recursive call

}

void sqsort(int* v, int n){
  if(n > 1){
    if(n > maxNforParallel ){
      int id = findAvailableThread(); //locking is internal
      //If there is available thread
      if(id != -1){
        threads_data[id].id = id;
        threads_data[id].n = n;
        threads_data[id].v = v;
        resultFromThread[id] = 0;
        pthread_create(&threads_id[id], NULL, thqsort, &threads_data[id]);
        int res1 = strPartition(v, n);
        int p;
        //Do the math and wake the other sleeping thread
        pthread_mutex_lock(&mutexForConds[id]);
        if(flagForWait[id] == 1){
          p = restSwaps(v,n,res1,resultFromThread[id]);
          resultFromThread[id] = p;
          pthread_cond_signal(&conds[id]);
        }else{
          //or sleep until the other is ready
          flagForWait[id] = 1;
          resultFromThread[id] = res1;
          pthread_cond_wait(&conds[id], &mutexForConds[id]);
          p = resultFromThread[id];
        }
        pthread_mutex_unlock(&mutexForConds[id]);
        sqsort(&v[p+1] , n -p -1);
        pthread_join(threads_id[id], NULL);
        releaseThread(id);
      }else{ //if there is no available thread
        int p = partition(v , n);
        sqsort(v , p);
        sqsort(&v[p+1],n-p-1);
      }
    }else{ //if n is not large enough for parallelisation
      int p = partition(v,n);
      onlySqsort(v,p);
      onlySqsort(&v[p+1], n-p-1);
    }
  }
}

void onlySqsort(int* v, int n){
  if(n > 1){
    int p = partition(v,n);
    onlySqsort(v,p);
    onlySqsort(&v[p+1], n-p-1);
  }
  
  }
/* swap -- swap elements k and l of vector v */
void swap(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}

int partition(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;
  
  for (int j = 0; j < n - 1; j++) 
    if (v[j] < pivot) 
      swap(v,i++,j);

  swap(v, i, n - 1);
  return (i);
}



/* partition -- in-place update of elements */
int strPartition(int *v, int n) {
  int pivot = v[n-1];
  int mid = n/2;
  int i = 0;
  for(int j = 0; j < mid; j++){
      if(v[j] < pivot){
          swap(v , i , j);
          i++;
      }
  }
  return i;
}

int inversePartition(int* v, int n){
  int pivot = v[n-1];
  int mid = n/2;
  int i = n-2;
  for(int j = n-2; j >= mid; j--){
      if(v[j] >= pivot){
          swap(v , i , j);
          i--;
      }
  }
  return i;

}
int restSwaps(int* v,int n, int res1 , int res2){
    int a = res1;
    int b = res2;
    while(a < n/2 + 1 && b > n/2 - 1){
        swap(v,a,b);
        a++; b--;
    }
    int unordered1 = n/2 - res1;
    int unordered2 = res2 - n/2 + 1;
    int p = res2 - unordered1 + 1;
    swap(v , n-1 , p);
    return p;
}



/* qsortseq -- Entry point for QuickSort */
void qsort_pthread(int *v, int n, int number_of_threads, int minN) {
  initialise(number_of_threads , minN); // -1 if main thread counts
  sqsort(v,n);
  
  free(threads_data);
  free(availableThreads);
  free(resultFromThread);
  free(flagForWait);
  free(conds);
  free(mutexForConds);
}




