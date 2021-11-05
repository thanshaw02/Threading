#include "testsort.h"
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

/*
    - I'm pretty stuck, can't seem to get this to work
    - I know my MergeSort is correct for the most part, minus the threading. It spits out all of the correct starting, ending, and middle indices that I would expect to get
    - But when I do get some kind of output it's either bits of the original array or just a core dump
*/

// void Merge(string *a, int aLen, string* b, int bLen) {

//     cout << "aLen: " << aLen << "\nbLen: " << bLen << "\n";
//     cout.flush();

//     cout << "array 1:\n";
//     cout.flush();
//     printArray(a, aLen);
//     cout << "array 2:\n";
//     cout.flush();
//     printArray(b, bLen);
//     cout << "\n";
//     cout.flush();

//     int aIndex = 0, bIndex = 0, copyIndex = globalIndex;

//     string* myCopy = new string[aLen + bLen];

//     // Comparing the two sub-arrays of strings
//     while(aIndex < aLen && bIndex < bLen) {
//         if(a[aIndex] < b[bIndex]) {
//             cout << "Global Index: " << globalIndex << "\n";
//             cout.flush();
//             myCopy[globalIndex++] = a[aIndex++];
//             // Put a[aIndex] in first, then check the next two indicies (if there are more to check)
//             // Increment aIndex
//             // **Maybe increment the index of where I am in the original array?**
//         }
//         else {
//             cout << "Global Index: " << globalIndex << "\n";
//             cout.flush();
//             myCopy[globalIndex++] = b[bIndex++];
//             // Put b[bIndex] in first, then check the next two indicies (if there are more to check)
//             // Increment bIndex
//             // **Maybe increment the index of where I am in the original array?**
//         }
//     }

//     // If there are indicies left in 'a' but not in 'b', then throw all the indicies left in 'a' into the original array (or into the ans array, not sure)
//     while(aIndex < aLen) {
//         cout << "Global Index: " << globalIndex << "\n";
//         cout.flush();
//         myCopy[globalIndex++] = a[aIndex++];
//         // Put a[aIndex] into the partially sorted array
//         // Increment aIndex
//         // **Maybe increment the index of where I am in the original array?**
//     }

//     // If there are indicies left in 'b' but not in 'a', then throw all the indicies left in 'b' into the original array (or into the ans array, not sure)
//     while(bIndex < bLen) {
//         cout << "Global Index: " << globalIndex << "\n";
//         cout.flush();
//         myCopy[globalIndex++] = b[bIndex++];
//         // Put b[bIndex] into the partially sorted array
//         // Increment bIndex
//         // **Maybe increment the index of where I am in the original array?**
//     }
// }

void Merge(string* a, int start, int end) {
    
    int mid = findMid(start, end);
    int aLen = (mid - start) + 1, bLen = (end - (mid + 1)) + 1;

    string* aCopy = copyArr(&a[start], aLen);
    string* bCopy = copyArr(&a[mid + 1], bLen);

    int aIndex = 0, bIndex = 0, mergedIndex = start;

    while(aIndex < aLen && bIndex < bLen) {
        if(aCopy[aIndex] < bCopy[bIndex]) {
            arr[mergedIndex++] = aCopy[aIndex++];
        }
        else {
            arr[mergedIndex++] = bCopy[bIndex++];
        }
    }

    while(aIndex < aLen) {
        arr[mergedIndex++] = aCopy[aIndex++]; 
    }

    while(bIndex < bLen) {
        arr[mergedIndex++] = bCopy[bIndex++];
    }

    delete [] aCopy;
    delete [] bCopy;
}

// Try not to change this thread, work on getting Merge() working!!
// Results from printing out "aLen" and "bLen" in Merge() are giving the expected results for any given size array
void* MergeSort(void* args) {
    MergeSortData temp = *(MergeSortData*)args;
    
    if(temp.start >= temp.end) return nullptr;

    pthread_t myThread1;
    MergeSortData data1, data2;

    // Splitting the array
    int mid = findMid(temp.start, temp.end);
    data1 = { temp.start, mid };
    data2 = { mid + 1, temp.end };

    // Recursively calling MergeSort 
    // I was only using one thread, but haven't been able to get it to work so I switched to two hoping for better luck
    pthread_create(&myThread1, nullptr, MergeSort, &data1);
    MergeSort(&data2);
    pthread_join(myThread1, nullptr);

    // Merging the split "arrays"
    Merge(arr, temp.start, temp.end);

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

    for(int i = 0; i < stoi(size); i++) {
        getline(cin, input);
        arr[i] = input;
    }

    MergeSortData data = { 0, stoi(size) - 1 };

    cout << "Original array:\n";
    printArray(arr, stoi(size));

    MergeSort(&data);

    cout << "Sorted array:\n";
    printArray(arr, stoi(size));

    delete [] arr;

    return 0;
}

/*

// DEBUGGING
    cout << "Hit MergeSort()\n";
    cout.flush();
    cout << "Temp->start:\t" << temp.start << "\n";
    cout.flush();
    cout << "Temp->end:\t" << temp.end << "\n\n";
    cout.flush();
    printArray(temp.array, temp.end - temp.start);


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

