#ifndef _TESTSORT_
#define _TESTSORT_

#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct MergeSortData {
    int start, end; // Start is the beginning of the array is, and end is the length or where the array ends
};

string input, size;
string* arr;

int main();
void* MergeSort(void* args);
void Merge(string* a, int start, int end);
void printArray(string* arr, int len);
int findMid(int start, int end) { return (start + end) / 2; }
string* copyArr(string* orig, int origLen);


#endif