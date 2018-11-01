/**********************************************************************
 *
 * qsort-sequential.h -- Sequential implementation of QuickSort
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


#ifndef _QSORT_SEQUENTIAL_H_
#define _QSORT_SEQUENTIAL_H_

/* qsortseq -- Sort vector v (of length n) using QuickSort */
void qsort_pthread(int *v, int n, int number_of_threads, int minN);

#endif /* _QSORT-SEQUENTIAL_H_ */



