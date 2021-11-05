#include "Person.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

// Max head count for the bathroom
#define MAX_CAPACITY 6

int nmw = 0, nmu = 0; // number of men waiting, number of men using
int nww = 0, nwu = 0; // number of women waiting, number of women using

// This keeps track of how many men and women have used the bathroom
// Also makes my program more or less fair for everyone
int nmhu = 0; // Number of men that have used the bathroom
int nwhu = 0; // Number of women that have used the bathroom

// This is the number of times each sex can use the bathroom in a row before switching to the other sex
// The main reason I have this variable rather then hard coding it is so I can let eevryone endter and leave the bathroom when people start leaving
// So once there are less than 6 people of each sex, this variable changes depending on how many people are waiting to use the bathroom
int MAX_CONSECUTIVE_TURNS_PER_SEX = 6;

// Used for initializing my semaphores, is false after the first instance of Person is instantiated
bool first = true;

// The idea is that bathroom usage with flip flop back and forth, hopefully ensuring fairness
char turnToUseBathroom = 'F'; // 'M' means it males are allowed to use the bathroom, 'F' means females are allowed to use the bathroom

// Semaphores
sem_t admin, enterBathroomMale, enterBathroomFemale;

Person::Person() {
    if(first) {
        first = false;
        sem_init(&admin, false, 1);
        sem_init(&enterBathroomMale, false, 0);
        sem_init(&enterBathroomFemale, false, 0);
    }
}

void Person::EnterBathroom() {
    sem_wait(&admin);
    if((nmu == MAX_CAPACITY || nwu == MAX_CAPACITY) || sex != turnToUseBathroom || (nmhu == MAX_CONSECUTIVE_TURNS_PER_SEX || nwhu == MAX_CONSECUTIVE_TURNS_PER_SEX)) {
        if(sex == 'M') {
            nmw++;
            sem_post(&admin);
            cout << Name << " is waiting to use the bathroom.\n";
            cout.flush();
            sem_wait(&enterBathroomMale);
        }
        else if(sex == 'F') {
            nww++;
            sem_post(&admin);
            cout << Name << " is waiting to use the bathroom.\n";
            cout.flush();
            sem_wait(&enterBathroomFemale);
        }
    }
    if(sex == turnToUseBathroom && (nmu < MAX_CAPACITY || nwu < MAX_CAPACITY) && (nwhu < MAX_CONSECUTIVE_TURNS_PER_SEX || nmhu < MAX_CONSECUTIVE_TURNS_PER_SEX)) {
        if(sex == 'M' && (nwu == 0 && nwhu == 0)) {
            nmu++;
            nmhu++;
            cout << Name << " is using the bathroom.\n";
            cout.flush();
            if(nmw > 0 && (nmu < MAX_CAPACITY && nmhu < MAX_CONSECUTIVE_TURNS_PER_SEX)) {
                nmw--;
                sem_post(&admin);
                sem_post(&enterBathroomMale);
            }
            else sem_post(&admin);
        }
        else if(sex == 'F' && (nmu == 0 && nmhu == 0)) {
            nwu++;
            nwhu++;
            cout << Name << " is now using the bathroom.\n";
            cout.flush();
            if(nww > 0 && (nwu < MAX_CAPACITY && nwhu < MAX_CONSECUTIVE_TURNS_PER_SEX)) {
                nww--;
                sem_post(&admin);
                sem_post(&enterBathroomFemale);
            }
            else sem_post(&admin); 
        }
    }
}

void Person::ExitBathroom() {
    if(sex == 'M') {
        nmu--;
        cout << Name << " is leaving the stinky bathroom.\n";
        cout.flush();
        if(nmu == 0 && nmhu == MAX_CONSECUTIVE_TURNS_PER_SEX) {
            nmhu = 0;
            if(nww > 0) { 
                turnToUseBathroom = 'F';
                nww--;
                sem_post(&enterBathroomFemale);
            }
        }
        else if(nmw == 0 && nmu == 0) {
            if(nww > 0) {
                nwhu = 0;
                nmhu = 0;
                MAX_CONSECUTIVE_TURNS_PER_SEX = nww;
                nww--;
                turnToUseBathroom = 'F';
                sem_post(&enterBathroomFemale);
            }
        }
        else if(nww == 0 && nwu == 0) {
            if(nmw > 0 ) {
                nmhu = 0;
                nwhu = 0;
                MAX_CONSECUTIVE_TURNS_PER_SEX = nmw;
                nmw--;
                turnToUseBathroom = 'M';
                sem_post(&enterBathroomMale);
            }
        }
    }
    else if(sex == 'F') {
        nwu--;
        cout << Name << " is leaving the stinky bathroom.\n";
        cout.flush();
        if(nwu == 0 && nwhu == MAX_CONSECUTIVE_TURNS_PER_SEX) {
            nwhu = 0;
            if(nmw > 0) {
                turnToUseBathroom = 'M';
                nmw--;
                sem_post(&enterBathroomMale);
            }
        }
        else if(nww == 0 && nwu == 0) {
            if(nmw > 0) {
                nmhu = 0;
                nwhu = 0;
                MAX_CONSECUTIVE_TURNS_PER_SEX = nmw;
                nmw--;
                turnToUseBathroom = 'M';
                sem_post(&enterBathroomMale);
            }
        }
        else if(nmw == 0 && nmu == 0) {
            if(nww > 0) {
                nwhu = 0;
                nmhu = 0;
                MAX_CONSECUTIVE_TURNS_PER_SEX = nww;
                nww--;
                turnToUseBathroom = 'F';
                sem_post(&enterBathroomFemale);
            }
        }
    }
}