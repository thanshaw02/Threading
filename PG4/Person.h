#ifndef _PERSON_
#define _PERSON_

#include <iostream>
#include <string>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <vector>

using namespace std;

class Person {
public:
    Person();
    string Name;
    char sex; // either 'M' or 'F'
    void EnterBathroom();
    void ExitBathroom();
};

int main(); // Make sure to comment this out before submitting!!

#endif