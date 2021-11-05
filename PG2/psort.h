/*
    Tylor J. Hanshaw

    - Comments for the Merge() and MergeSort() methods are in psort.cc
*/

#ifndef _PSORT_
#define _PSORT_

#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h> // for using the pause() call when debugging

using namespace std;

/*
    - Class that holds the starting and ending indices for each split call
    - Included a constructor so I could just use a new instance of MergeSortData whenever I recursively call MergeSort()
        - Instead of creating two MergesortData instance I can just create a new on in the MergeSort() call
    - Also created two "getter" methods for the MergeSort() method
*/
class MergeSortData {
    int start, end;

public:
    MergeSortData(int s, int e) { start = s; end = e; } // Start is the beginning of the array is and end is where that sub-array ends
    int getStart() { return start; }
    int getEnd() { return end; }
};

string input, size;
string* arr;

int main(); // Main functions
void* MergeSort(void* args);
void Merge(string* a, int start, int end);
void printArray(string* arr, int len); // For displaying the array
int findMid(int start, int end) { return start + (end - start) / 2; }
// int findMid(int start, int end) { return (start + end) / 2; } // For finding the mid pos, didn't want to type the equation every time
string* copyArr(string* orig, int origLen); // Copying the array, possible memory leaks here? I was just lazy and didn't want to copy the array manually

#endif

/*

My first lazy attempt at the Merge function, shouldn't have turned this version in

OLD MERGE()
    // int aIndex = 0, bIndex = 0, mergedArr = aStart;
    
    // while(aIndex < aEnd && bIndex < bEnd ) {
    //     if(a[aStart] <= b[bStart]) {
    //         ans[mergedArr] = a[aIndex];
    //         aIndex++;
    //     }
    //     else {
    //         ans[mergedArr] = b[bIndex];
    //         bIndex++;
    //     }
    //     mergedArr++;
    // }

    // while(aIndex < aEnd) {
    //     ans[mergedArr] = a[aIndex];
    //     aIndex++;
    //     mergedArr++;
    // }

    // while(bIndex < bEnd) {
    //     ans[mergedArr] = b[bIndex];
    //     bIndex++;
    //     mergedArr++;
    // }
*/