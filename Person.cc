/* Tylor J. Hanshaw */

#include "Person.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/*
        *********************** CHANGES FROM PG4 *************************
        - Everything should be looking good now! I understand what you're saying in your last .out file
        - I changed it so that "turnToUseBathroom" starts as 'U', then when the first person enters the bathroom I change "turnToUseBathroom" to whatever the sex is of the first person
        - 
*/

// Only 6 people can be in the bathroom at one time
#define MAX_CAPACITY 6

// Globals
int nmw = 0, nmu = 0; // number of men waiting, number of men using
int nww = 0, nwu = 0; // number of women waiting, number of women using

// This keeps track of how many people have used the bathroom in a row
// I only allow up to 6 people of each sex to use the bathroom in a row before passing the baton to the other sex
int nphu = 0;

// Only allowing up to 6 people of each sex to use the bathroom consecutively
// I only useda variable here instead of "#define" because this does need to change to take into account people leaving towards the end
int MAX_CONSECUTIVE_TURNS = 6;

// 'M' means it males are allowed to use the bathroom, 'F' means females are allowed to use the bathroom
// This is just here to switch between the sex's once all of one sex has used the bathroom
char turnToUseBathroom = 'U';

// Bathroom monitor custom class
BathroomMonitor btMon;

// Just debug code making sure that nmu and nwu never exceeds 6
void testingBathroomOccupancySize(int nmu, int nwu) {
    if(nmu > MAX_CAPACITY || nwu > MAX_CAPACITY) { cout << "ERROR" << endl; exit(-1); }
}

/* BATHROOM MONITOR */
void BathroomMonitor::EnterBathroom(Person p) {
    mbegin();

    if(turnToUseBathroom == 'U') turnToUseBathroom = p.sex; // Here' I'm having "turnToUseBathroom" be the sex of the first person to enter the bathroom
    if((nmu == MAX_CAPACITY || nwu == MAX_CAPACITY) || p.sex != turnToUseBathroom || nphu == MAX_CONSECUTIVE_TURNS) {
        if(p.sex == 'M') {
            nmw++;
            cout << p.Name << " is waiting to use the bathroom.\n";
            cout.flush();
            // cout << "Number of MEN waiting to use the bathroom (incremented): " << nmw << endl; // DEBUGGING
            male.wait(this);
        }
        else if(p.sex == 'F') {
            nww++;
            cout << p.Name << " is waiting to use the bathroom.\n";
            cout.flush();
            // cout << "Number of WOMAN waiting to use the bathroom (incremented): " << nww << endl; // DEBUGGING
            female.wait(this);
        }
    }
    if(p.sex == turnToUseBathroom && (nmu < MAX_CAPACITY || nwu < MAX_CAPACITY) && nphu < MAX_CONSECUTIVE_TURNS) {
        if(p.sex == 'M' && nwu == 0) { // Added the second big AND statament here
            nmu++;
            nphu++; // Tryign to get the fairness thing working
            cout << p.Name << " is using the bathroom.\n";
            cout.flush();
            // cout << "Number of MEN using the bathroom (incremented): " << nmu << "\tNumber of MEN that have used the bathroom (incremented): " << nmhu << endl; // DEBUGGING
            if((nmw > 0 && nmu < MAX_CAPACITY) && nphu < MAX_CONSECUTIVE_TURNS) {
                nmw--;
                // cout << "I am a MAN and I am letting another MAN go to the bathroom (nmw decremented): " << nmw << endl; // DEBUGGING
                male.signal(this);
            }
        }
        else if(p.sex == 'F' && nmu == 0) {
            nwu++;
            nphu++; // Tryign to get the fairness thing working
            cout << p.Name << " is now using the bathroom.\n";
            cout.flush();
            // cout << "Number of WOMAN using the bathroom (incremented): " << nwu << "\tNumber of WOMEN that have used the bathroom (incremented): " << nwhu << endl; // DEBUGGING
            if((nww > 0 && nwu < MAX_CAPACITY) && nphu < MAX_CONSECUTIVE_TURNS) {
                nww--;
                // cout << "I am a WOMAN and I am letting another WOMEN go to the bathroom (nww decremented): " << nww << endl; // DEBUGGING
                female.signal(this);
            }
        }
    }

    mend();
}

void BathroomMonitor::ExitBathroom(Person p) {
    mbegin();
    
    if(p.sex == 'M') {
        nmu--;
        cout << p.Name << " is leaving the stinky bathroom.\n";
        cout.flush();
        // cout << "Number of MEN that are using the bathroom (decremented): " << nmu << endl; // DEBUGGING
        if((nmw > 0 && nmu < MAX_CAPACITY) && nphu < MAX_CONSECUTIVE_TURNS) {
            nmw--;
            male.signal(this);
        }
        else if(nmu == 0 && nphu == MAX_CONSECUTIVE_TURNS) {
            nphu = 0; // Tryign to get the fairness thing working
            if(nww > 0) { 
                if(nww < MAX_CONSECUTIVE_TURNS) MAX_CONSECUTIVE_TURNS = nww;
                turnToUseBathroom = 'F';
                nww--;
                // cout << "I am a MAN and there are WOMEN waiting to use the bathroom (decremented): " << nww << endl; // DEBUGGING
                female.signal(this);
            }
            else {
                // This is only called when the last person is leaving the bathroom AND if women are using the bathroom first 
                cout << "There are no MEN waiting or using and there are no WOMEN waiting!" << endl;
            }
        }
    }
    else if(p.sex == 'F') {
        nwu--;
        cout << p.Name << " is leaving the stinky bathroom.\n";
        cout.flush();
        // cout << "Number of WOMAN that are using the bathroom (decremented): " << nwu << endl; // DEBUGGING
        if((nww > 0 && nwu < MAX_CAPACITY) && nphu < MAX_CONSECUTIVE_TURNS) {
            nww--;
            female.signal(this);
        }
        else if(nwu == 0 && nphu == MAX_CONSECUTIVE_TURNS) {
            nphu = 0; // Tryign to get the fairness thing working
            if(nmw > 0) {
                if(nmw < MAX_CONSECUTIVE_TURNS) MAX_CONSECUTIVE_TURNS = nmw;
                turnToUseBathroom = 'M';
                nmw--;
                // cout << "I am a WOMAN and there are MEN waiting to use the bathroom (decremented): " << nmw << endl; // DEBUGGING
                male.signal(this);
            }
            else {
                // This is only called when the last person is leaving the bathroom AND if men are using the bathroom first 
                cout << "There are no WOMEN waiting or using and there are no MEN waiting!" << endl;
            }
        }
    }

    mend();
}

/* PERSON CLASS */
void Person::EnterBathroom() { btMon.EnterBathroom(*this); }

void Person::ExitBathroom() { btMon.ExitBathroom(*this); }