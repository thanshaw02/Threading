#include <iostream>
#include <string>
#include "mergesort.h"

using namespace std;

void Merge(string* a, int aStart, int aEnd, string* b, int bStart, int bEnd) {

    // PrintArray(a, aEnd - aStart);
    // PrintArray(b, bEnd - bStart);


    int aBegin = 0, bBegin = 0, ansBegin = 0;

    while(aBegin < aEnd && bBegin < bEnd) {
        if(arr[aBegin] <= arr[bBegin]) {
            ans[ansBegin] = a[aBegin];
            aBegin++;
        }
        else {
            ans[ansBegin] = b[bBegin];
            bBegin++;
        }
        ansBegin++;
    }

    while(aStart < aEnd) {
        ans[ansBegin] = a[aBegin];
        aBegin++;
        ansBegin++;
    }

    while(bBegin < bEnd) {
        ans[ansBegin] = b[bBegin];
        bBegin++;
        ansBegin++;
    }
}

string* Split(string* arr, int start, int end) {
    int mid = (start + mid) /2;
    return &arr[mid];
}

void MergeSort(string* arr, int start, int end) {
    if(start >= end) return;

    int mid = (start + end) / 2;
    //cout << endl << mid << endl;
    MergeSort(&arr[start], start, mid - 1);
    MergeSort(&arr[mid], mid, end);

    // cout << "Start pos: " << start << endl;
    // cout << "End pos: " << end << endl;
    // cout << "Middle pos: " << mid << endl;

   Merge(&arr[start], start, mid - 1, &arr[mid], mid, end);

    PrintArray(ans, stoi(size));
    //PrintArray(&arr[start], end);
}

void PrintArray(string* arr, int len) {
    for(int i = 0; i < len; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {

    cout << "Enter size: ";
    getline(cin, size);

    arr = new string[stoi(size)];
    ans = new string[stoi(size)];

    for(int i = 0; i < stoi(size); i++) {
        cout << "Enter a string: ";
        getline(cin, input);
        arr[i] = input;
    }

    MergeSort(arr, 0, stoi(size) - 1);

    cout << "\nOriginal array: \n";
    PrintArray(arr, stoi(size));

    cout << "\nNew array: \n";
    PrintArray(ans, stoi(size));

    return 0;
}