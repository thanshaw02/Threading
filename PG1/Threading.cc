/*
	Tylor J. Hanshaw

	This is the Threading.cc file that contains all of the defined methods from the Threading.h file
	Most of the comments about the methods here are in the Threading.h file, except for the mm() and createMatrix() methods

	One note, I prefer to read input in as strings if possible, so that's why I did that in the beginning of my main() method, and then converted them all to integers
	I'm not sure if this slows my program down, it probably does but it's something that stuck with me from PG3 in CS 222, the maze solving assignment
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <pthread.h>
#include <vector>
#include "Threading.h"

using namespace std;

// All of my matrices are global, so I don't need to return anything here
// Simply creates a 2d arrayand fills it with floats
// I found that I couldn't fully create the 2d array in here, I think it may be because of scope issues
void createMatrix(float** matrix, int rows, int cols) {
	float input;
	for(int i = 0; i < rows; i++) {
		matrix[i] = new float[cols];
		for(int j = 0; j < cols; j++) {
			cin >> input;
			matrix[i][j] = input;
		}
	}
}

// Matrix multiplication method for 'numOfThreads' threads
// Using a struct to hold the indices needed for each thread to throw it's product in to
void* mm(void* arg) {
	int struct_id = *(int*)arg;
	struct indexOf temp = structArr[struct_id];
	for(int i = 0; i < n; i++) {
		ret[temp.indZ][temp.indO] += m1[temp.indZ][i] * m2[i][temp.indO];
	}
	return nullptr;
}

void printMatrix(float** arg, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) cout << arg[i][j] << "\t";
        cout << endl;
    }
}

void printStruct(struct indexOf arg) {
	cout << "=========================" << endl;
    cout << "Index zero: " << arg.indZ << endl;
    cout << "Index one: " << arg.indO << endl;
	cout << "=========================" << endl;
}

int main() {

	string dm1, dm2, dm3; // m, n, p are integers read in as strings
	int tracker = 0; // Used for putting my 'indexOf' structures into an array *see lines 136-138*
	float input;

	getline(cin, dm1);
	getline(cin, dm2);
	getline(cin, dm3);
	m = stoi(dm1), n = stoi(dm2), p = stoi(dm3);
	
	// Creating and filling matrices
	m1 = new float*[m];
	m2 = new float*[n];

	createMatrix(m1, m, n);
	createMatrix(m2, n, p);

	// DEBUGGING
	// printMatrix(m1, m, n);
	// printMatrix(m2, n, p);

	
	int numOfThreads = m * p; // Number of threads needed
	tid = new pthread_t[numOfThreads];
	structArr = new indexOf[numOfThreads];
	id = new int[numOfThreads];
	ret = new float*[m];
	for(int i = 0; i < m; i++) { 
		ret[i] = new float[p];
		for(int j = 0; j < p; j++) {
			structArr[tracker].indZ = i;
			structArr[tracker].indO = j;
			tracker++;
		}
	}

	// DEBUGGING
	// for(int i = 0; i < numOfThreads; i++) printStruct(structArr[i]);

	// Creating and rejoining all of my threads
	// Also error checking just in case
	for(int i = 0; i < numOfThreads; i++) { id[i] = i; if(pthread_create(&tid[i], nullptr, mm, &id[i]) != 0) perror("One of the threads was not able to properly be created."); }
	for(int i = 0; i < numOfThreads; i++) if(pthread_join(tid[i], nullptr) != 0) perror("One of the threads was not able to properly join.");

	// printing out the new matrix
	printMatrix(ret, m, p);
	
	// Deallocating my pointers
	for(int i = 0; i < m; i++) delete [] ret[i];
	delete [] ret;
	for(int i = 0; i < m; i++) delete [] m1[i];
	delete [] m1;
	for(int i = 0; i < n; i++) delete [] m2[i];
	delete [] m2;
	delete [] tid;
	delete [] structArr;
	delete [] id;
	

	return 0;
}

/*
	- This is the non-threading version of my matrix multiplication method
	- I first finished the assignment without threading, then implemented threading afterwards
	- This made it a little easier to come up with an algorithm to handle multiplying matrices and then to translate it to accomodate the threading aspect of the assignment


vector<vector<float>> mm(vector<vector<float>> m1, vector<vector<float>> m2, int m, int n, int p) {
	vector<vector<float>> ret(m, vector<float>(p, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < n; k++) {
				ret[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	return ret;
}
*/