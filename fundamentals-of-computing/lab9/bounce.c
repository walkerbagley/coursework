// Walker Bagley
// CSE 20311 Lab 9
// bounce.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

#define XLEN 600
#define YLEN 800
#define RAD 30

void bounce(int[2], int[2]);

int main () {
    char c;
    int p[2], v[2];
    srand(time(0));
    p[0] = rand() % XLEN;
    p[1] = rand() % YLEN;
    v[0] = rand() % 10 - 5;
    v[1] = rand() % 10 - 5;
    gfx_open(600, 800, "Bounce");
    while (1) {
        gfx_clear();
        gfx_circle(p[0], p[1], RAD);
        gfx_flush();
        bounce(p, v);
        p[0] += v[0];
        p[1] += v[1];
        usleep(7500);
        if (gfx_event_waiting()){
            c = gfx_wait();
            if (c == 'q') break;
            if (c == 1){
                p[0] = gfx_xpos();
                p[1] = gfx_ypos();
                v[0] = rand() % 10 - 5;
                v[1] = rand() % 10 - 5;
            }
        }
    }
    return 0;
}

void bounce(int p[2], int v[2]){
    if (p[0] + v[0] > XLEN - RAD || p[0] + v[0] < RAD) v[0] = -v[0];
    if (p[1] + v[1] > YLEN - RAD || p[1] + v[1] < RAD) v[1] = -v[1];
}