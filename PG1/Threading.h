/*
    Tylor J. Hanshaw

    This is the Threading.h file that contains the prototype methods for the Threading.cc file
    Comments for the mm() and createMatrix() methods are in the Threading.cc file
*/

#ifndef _THREADING_
#define _THREADING_

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <pthread.h>

using namespace std;

int m, n, p;
float** ret;
float** m1;
float** m2;
pthread_t *tid; // An array of threads, holds all of the threads needed to multiply both matricies
struct indexOf *structArr; // *See lines 20-22*
int *id; // An array of integers that holds a unique ID that each thread uses to obtain the correct structure, each ID corresponds to an index in the 'structArr' array

// This struct is my way of holding onto the coordinates that each thread needs after multiplying its portion of each matrix
// I first tried to use a vector of type string and then would extract the characters from each string in the vector, then I would convert the char's into integers
// That seemed like too much work, this structure idea came to me while laying on my bed brain storming - I'm sure it's not the fastest/best way to tackle this issue but it works!
struct indexOf {
    int indZ, indO; // indZ == index zero, indO == index one --> array[indZ][indO]
};

int main(); // Main method, where the execution of our program is done
void* mm(void* arg);
void printStruct(struct indexOf arg); // Debugging method to see what each thread's stuct looked like when it was created
void printMatrix(float** arg, int rows, int cols); // Debugging method as well as the method that prints out the final product
void createMatrix(float** matrix, int rows, int cols);

// float** mm(float** m1, float** m2, int m, int n, int p); // Original matrix multiplication method, no threading used

#endif