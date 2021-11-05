/*
    Tylor J. Hanshaw

    - Finally have this method working, I had it working for the past few days but was accidentally using a capitalized word, which changed my output (forgot that capitalized characters are a totally different value)
    - The toughest thing for me in the assignment was figuring out how my Merge() function knows where to put the now sorted indices
    - What I did was changed the parameters of my Merge() method. So I'm only passing the the array I'm working with, and the starting and ending pos for the sub-array I'm working with
*/

#include "psort.h"
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h> // for using the pause() call when debugging

using namespace std;

// Using the starting and ending indices from splitting the array, I made two copies of the sub-array I'm currently working with
// Then using those two sub-arrays I compare them and put the sorted indices into the global array "arr"
void Merge(string* a, int start, int end) {
    int mid = findMid(start, end);
    int aLen = (mid - start) + 1, bLen = (end - (mid + 1)) + 1;

    string* aCopy = copyArr(&a[start], aLen);
    string* bCopy = copyArr(&a[mid + 1], bLen);

    int aIndex = 0, bIndex = 0, mergedIndex = start;

    // Sorts the two arrays until one or both array's have been fully iterated through
    while(aIndex < aLen && bIndex < bLen) {
        if(aCopy[aIndex] < bCopy[bIndex]) {
            arr[mergedIndex++] = aCopy[aIndex++];
        }
        else {
            arr[mergedIndex++] = bCopy[bIndex++];
        }
    }

    // If any indices are left in aCopy, this will toss those into arr
    while(aIndex < aLen) {
        arr[mergedIndex++] = aCopy[aIndex++];
    }

    // If any indices are left in bCopy, this will toss those into arr
    while(bIndex < bLen) {
        arr[mergedIndex++] = bCopy[bIndex++];
    }

    delete [] aCopy;
    delete [] bCopy;
}

// Method that recursively calls MargeSort, splitting the original array into smaller sub-arrays
// Only creating one extra thread per split, and using the main thread to do the other recursive call
void* MergeSort(void* args) {
    MergeSortData temp = *(MergeSortData*)args;
    
    if(temp.getStart() >= temp.getEnd()) return nullptr;

    pthread_t myThread1;

    // Splitting the array
    int mid = findMid(temp.getStart(), temp.getEnd());

    // Recursively calling MergeSort
    // Using one thread to call MergeSort, and the main thread to call MergeSort
    //pthread_create(&myThread1, nullptr, MergeSort, &data1);
    pthread_create(&myThread1, nullptr, MergeSort, new MergeSortData(temp.getStart(), mid));
    MergeSort(new MergeSortData(mid + 1, temp.getEnd()));
    pthread_join(myThread1, nullptr);

    // Merging the split "arrays"
    Merge(arr, temp.getStart(), temp.getEnd());

    return nullptr;
}

void printArray(string* arr, int len) {
    for(int i = 0; i < len; i++) {
        cout << arr[i] << " ";
        cout.flush();
    }
    cout << "\n";
    cout.flush();
}

// Possible memory leaks here?
string* copyArr(string* orig, int origLen) {
    string* copy = new string[origLen];
    for(int i = 0; i < origLen; i++) {
        copy[i] = orig[i];
    }
    return copy;
}

int main() {

    // Get the size of the array, and fill the array with user input
    getline(cin, size);

    arr = new string[stoi(size)];

    // Filling the array with user input
    for(int i = 0; i < stoi(size); i++) {
        getline(cin, input);
        arr[i] = input;
    }

    // cout << "Original array:\n";
    // printArray(arr, stoi(size));

    MergeSort(new MergeSortData(0, stoi(size) - 1));

    // cout << "Sorted array:\n";
    printArray(arr, stoi(size));

    delete [] arr;

    return 0;
}