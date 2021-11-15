#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "Person.h"
using namespace std;

void *PersonProgram (void *a);

int main () {

    srand (time(NULL));

    Person N[20];

    // Males
    N[0].Name = "Abner";
    N[1].Name = "Barney";
    N[2].Name = "Charles";
    N[3].Name = "David";
    N[4].Name = "Edward";
    N[5].Name = "Frank";
    N[6].Name = "George";
    N[7].Name = "Harold";
    N[8].Name = "Ian";
    N[9].Name = "James";

    // Females
    N[10].Name = "Kathleen";
    N[11].Name = "Laura";
    N[12].Name = "Mandy";
    N[13].Name = "Naomi";
    N[14].Name = "Ophelia";
    N[15].Name = "Petunia";
    N[16].Name = "Queenie";
    N[17].Name = "Rowena";
    N[18].Name = "Sally";
    N[19].Name = "Tina";

    for (int i=0; i < 20; i++) N[i].sex = i < 10 ? 'M' : 'F';

    pthread_t PTH[20];

    for (int i=0; i < 20; i++) pthread_create (&PTH[i], nullptr, PersonProgram, &N[i]);

    for (int i=0; i < 20; i++) pthread_join (PTH[i], nullptr);

            /* I've done it! */
    cout << "You've reached the end!!\n";
}

void *PersonProgram (void *a) {
    Person P  = *(Person *)a;

    for (int i=0; i < 2; i++) {
        sleep (1+rand()%10);
        P.EnterBathroom ();
        sleep (1+rand()%10);
        P.ExitBathroom ();
    }
    return nullptr;
}