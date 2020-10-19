/* Iain Weissburg */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 70

void move(int* h, int*t) {
    int r = (rand() % 10) + 1;
    switch (r) {
    case 1 ... 5:
        *t += 3;
        break;
    case 6 ... 7:
        *t -= 6;
        break;
    case 8 ... 10:
        *t += 1;
        break;
    }

    r = (rand() % 10) + 1;  
    switch (r) {
    case 3 ... 4:
        *h += 9;
        break;
    case 5:
        *h -= 12;
        break;
    case 6 ... 8:
        *h += 1;
        break;
    case 9 ... 10:
        *h -= 2;
        break;
    }

    if (*t < 1)
        *t = 1;
    if (*h < 1) 
        *h = 1;
}

void setTrack(int h, int t, char track[]) {
    h--; t--;
    int i;
    char ouch[7] = "OUCH!!!";
    for (i=0;i<SIZE;i++) 
        track[i] = '-';       
    for (i=0;i<SIZE;i++)
        if (h == i && t == i)
            for (int j=0;j<7;j++)
                track[i+j] = ouch[j];
        else if (h == i)
            track[i] = 'H';
        else if (t == i)
            track[i] = 'T';
}

void printTrack(char track[]) {
    printf("|START|\n");
    for (int i=0;i<SIZE;i++) 
        putchar(track[i]);       
    printf("|FINISH|\n");
}

int main(void) {
    char track[SIZE];
    int h=1,t=1;
    printf("BANG !!!!!\nAND THEY'RE OFF !!!!!\n");
    while (h < SIZE && t < SIZE) {
        move(&h,&t);
        setTrack(h,t,track);
        printTrack(track);
        sleep(1);
    }
    if (t >= 70)
        printf("TORTOISE WINS!!! YAY!!!\n");
    else
        printf("Hare wins. Yuck.\n");
}