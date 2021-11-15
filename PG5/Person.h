/* Tylor J. Hanshaw */

#ifndef _PERSON_
#define _PERSON_

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "monitor.h"

using namespace std;

class Person;
class monitor;

// Custom monitor class that is used for entering and exiting the bathroom
// I also have the two conditions needed for this program in this class
class BathroomMonitor : public monitor {
public:
    void EnterBathroom(Person p);
    void ExitBathroom(Person p);
    cond female, male;
};

class Person {
public:
    string Name;
    char sex; // either 'M' or 'F'
    void EnterBathroom();
    void ExitBathroom();
};

// Debugging function
void testingBathroomOccupancySize(int nmu, int nwu);


#endif