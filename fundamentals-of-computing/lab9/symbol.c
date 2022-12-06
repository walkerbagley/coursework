// Walker Bagley
// CSE 20311 Lab 9
// symbol.c

#include <stdio.h>
#include <math.h>
#include "gfx.h"

#define SIZE 50

void drawSquare(int, int);
void drawCircle(int, int);
void drawTriangle(int, int);
void drawPolygon(int, int, int);

int main () {
    char c;
    int run = 1;
    gfx_open(800, 800, "Symbol");
    while (run) {
        c = gfx_wait();
        switch (c){
            case 1:
                drawSquare(gfx_xpos(), gfx_ypos());
                break;
            case 'c':
                drawCircle(gfx_xpos(), gfx_ypos());
                break;
            case 't':
                drawTriangle(gfx_xpos(), gfx_ypos());
                break;
            case '3' ... '9':
                drawPolygon(gfx_xpos(), gfx_ypos(), (int) c - 48);
                break;
            case 'q':
                run = 0;
                break;
            case 27:
                gfx_clear();
                break;
            default:
                break;
        }
    }
    return 0;
}

void drawSquare(int x, int y){
    gfx_color(0,100,200);
    gfx_line(x - SIZE / 2, y - SIZE / 2, x + SIZE / 2, y - SIZE / 2);
    gfx_line(x - SIZE / 2, y - SIZE / 2, x - SIZE / 2, y + SIZE / 2);
    gfx_line(x - SIZE / 2, y + SIZE / 2, x + SIZE / 2, y + SIZE / 2);
    gfx_line(x + SIZE / 2, y - SIZE / 2, x + SIZE / 2, y + SIZE / 2);
}
void drawCircle(int x, int y){
    gfx_color(200,200,200);
    gfx_circle(x, y, SIZE / 2);
}
void drawTriangle(int x, int y){
    gfx_color(0,200,100);
    int m = sqrt(2 * pow(SIZE, 2));
    gfx_line(x - m / 2, y + m / 4, x + m / 2, y + m / 4);
    gfx_line(x - m / 2, y + m / 4, x, y - m / 4);
    gfx_line(x + m / 2, y + m / 4, x, y - m / 4);
}
void drawPolygon(int x, int y, int n){
    gfx_color(200, 0, 200);
    int i;
    int r = SIZE / 2;
    float t = 0;
    // step for angle to rotate around the center
    float step = (2 * M_PI) / n;
    for (i = 0; i < n; i++){
        // using x=r*cos(theta) and y=r*sin(theta) to find the endpoints of each line
        gfx_line(x + r * cos(t), y + r * sin(t), x + r * cos(t + step), y + r * sin(t + step));
        t += step;
    }
}