#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "Person.cc"

using namespace std;

void *PersonProgram (void *a);

int main () {

    srand (time(NULL));

    Person N[22];

    // Men
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

    // Women
    N[10].Name = "Garrett";
    N[11].Name = "Laura";
    N[12].Name = "Mandy";
    N[13].Name = "Naomi";
    N[14].Name = "Ophelia";
    N[15].Name = "Petunia";
    N[16].Name = "Queenie";
    N[17].Name = "Rowena";
    N[18].Name = "Sally";
    N[19].Name = "Tina";

    // Added by me
    N[20].Name = "Kathleen";
    N[21].Name = "Selena";

    for (int i=0; i < 22; i++) N[i].sex = i < 11 ? 'M' : 'F';

    pthread_t PTH[22];

    for (int i=0; i < 22; i++) pthread_create (&PTH[i],NULL,PersonProgram,&N[i]);

    for (int i=0; i < 22; i++) pthread_join (PTH[i],NULL);

            /* I've done it!! */
    cout << "You've reached the end!!\n";

    return 0;
}

void *PersonProgram (void *a) {
    Person P  = *(Person *)a;

    for (int i=0; i < 2; i++) {
        sleep (1+rand()%10);
        P.EnterBathroom ();
        sleep (1+rand()%10);
        P.ExitBathroom ();
    }

    return NULL;
}