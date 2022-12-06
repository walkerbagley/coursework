// Walker Bagley
// CSE 20311 Lab 9
// funanim.c

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

#define LEN 800

void drawPolygon(int, int, int, int);

int main () {
    srand(time(0));
    char c;
    int p[2];
    int color[3] = {rand() % 200, rand() % 200, rand() % 200};
    p[0] = LEN * 3 / 4;
    p[1] = LEN / 2;
    int sides = 3, radius = 30, step = 1, speed = 150, run = 1;
    gfx_open(LEN, LEN, "Fun Animation");
    while (run) {
        gfx_clear();
        gfx_color(color[0], color[1], color[2]);
        drawPolygon(p[0], p[1], sides, radius);
        gfx_flush();
        p[0] = LEN / 2 + (LEN / 4) * cos(step * M_PI / speed);
        p[1] = LEN / 2 + (LEN / 4) * sin(step * M_PI / speed);
        step++;
        usleep(7500);
        if (gfx_event_waiting()){
            c = gfx_wait();
            switch (c){
                case 1:
                    color[0] = rand() % 200;
                    color[1] = rand() % 200;
                    color[2] = rand() % 200;
                    break;
                case 'S':
                    radius = radius < 96 ? radius + 5 : radius;
                    break;
                case 'Q':
                    radius = radius > 14 ? radius - 5 : radius;
                    break;
                case 'R':
                    speed = speed > 54 ? speed - 5 : speed;
                    break;
                case 'T':
                    speed = speed < 196 ? speed + 5 : speed;
                    break;
                case '3' ... '9':
                    sides = (int) c - 48;
                    break;
                case 'q':
                    run = 0;
                    break;
                default:
                    break;
            }
            if (c == 'q') break;
        }
    }
    return 0;
}

void drawPolygon(int x, int y, int n, int r){
    int i;
    float t = 0;
    // step for angle to rotate around the center
    float step = (2 * M_PI) / n;
    for (i = 0; i < n; i++){
        // using x=r*cos(theta) and y=r*sin(theta) to find the endpoints of each line
        gfx_line(x + r * cos(t), y + r * sin(t), x + r * cos(t + step), y + r * sin(t + step));
        t += step;
    }
}