#ifndef _MERGESORT_
#define _MERGESORT_

#include <iostream>
#include <string>
#include "mergesort.h"

using namespace std;

string* arr; string* ans;
string size, input;

int main();
void MergeSort(string* arr, int start, int end);
void Merge(string* a, int aStart, int aEnd, string* b, int bStart, int bEnd);
void PrintArray(string* arr, int len);
int findMiddle(int start, int len) { return (len + start) / 2; }

#endif