

#ifndef heapsort_h
#define heapsort_h
/*************************heap sort*******************************/

#include <vector>

/** 
 * @pre: none 
 * @param: vector, and its size
 * @post: test whether input is sorted
 * @return: true if sorted, false otherwise
 */
bool isSorted( std::vector<int> array, size_t n ) {
    int i;

    for ( i = 1; i < n; ++i ) {
        if ( array[i - 1] > array[i] ) {
            return false;
        }
    }
    return true;
}


void percolateDown(std::vector<int>&, int, int);

/** 
 * @pre: 
 * @param: 
 * @post: 
 * @return: 
 */
void myheapSort(std::vector<int> & A) {
    for (int i = A.size() /2 -1; i >= 0; --i) 
        percolateDown(A, i, A.size());
    for (int j = A.size() - 1; j > 0; --j) {
        std::swap(A[0], A[j]);
        percolateDown(A, 0, j);
    }
}

/** 
 * @pre: none
 * @param: position
 * @post: none
 * @return: the index of its left child
 */
inline int leftChild(int i) {
    return 2 * i + 1;
}


/** 
 * @pre: none
 * @param: vector<int> and position, and the size
 * @post: create a max-heap
 * @return: none
 */
void percolateDown(std::vector<int> &A, int i, int n) {
    int child;
    int tmp;

    for (tmp = std::move(A[i]); leftChild(i) < n; i = child) {
        child = leftChild( i );
        if (child != n - 1 && A[child] < A[child + 1])
            ++ child;
        if (tmp < A[child] )
            A[i] = std::move(A[child]);
        else
            break;
    }
    A[i] = std::move( tmp );
}

#endif /* heapsort_h */
