// Walker Bagley
// CSE 20311 Lab 10
// fractals.c

#include <math.h>
#include <unistd.h>
#include "gfx.h"

// fractal function prototypes
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingSquares(int x, int y, int s, int m);
void spiralSquares(int x, int y, float s);
void circularLace(int x, int y, int r, int m);
void snowflake(int x, int y, int l);
void tree(int x, int y, int l, float a);
void fern(int x, int y, int l, float a);
void spiral(int x, int y, float s, float t);

// helper function prototypes
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawSquare(int x, int y, int s);

int main() {
   	int width = 800, height = 800, mrgn = 20, run = 1;
	gfx_open(width, height, "Fractal Fun");
   	while(run) {
		// switch calling each respective fractal function with appropriate initial parameters
     	switch(gfx_wait()){
        	case '1':
				gfx_clear();
				sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
				break;
			case '2':
				gfx_clear();
				shrinkingSquares(width/2, height/2, (width-mrgn)/2, mrgn);
				break;
			case '3':
				gfx_clear();
				spiralSquares(width/2, height/2, 4);
				break;
			case '4':
				gfx_clear();
				circularLace(width/2, height/2, width/3, mrgn/3);
				break;
			case '5':
				gfx_clear();
				snowflake(width/2, height/2, width/2-6*mrgn);
				break;
			case '6':
				gfx_clear();
				tree(width/2, height - mrgn, height/3, M_PI/2);
				break;
			case '7':
				gfx_clear();
				fern(width/2, height - mrgn, 2*height/3, M_PI/2);
				break;
			case '8':
				gfx_clear();
				spiral(width/2, height/2, width/2, M_PI);
				break;
         		case 'q':
				run = 0;
				break;
			default:
				gfx_clear();
				break;
     		}
  	}
}

// draws the sierpinski triangle with the help of the drawTriangle helper function
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3){
	if(abs(x2-x1) < 5) return;

	drawTriangle(x1, y1, x2, y2, x3, y3);
	gfx_flush();
	usleep(1000);

	// recurses within the three corners of the previous triangle
	sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
	sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
	sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

// draws the shrinking squares with the help of the drawSquare helper function
void shrinkingSquares(int x, int y, int s, int m){
	if (s < 3) return;

	drawSquare(x, y, s);
	gfx_flush();
	usleep(1000);

	// recurses at each of the four corners of the previous square
	shrinkingSquares(x-s/2, y-s/2, s/2 - m, m/2);
	shrinkingSquares(x+s/2, y-s/2, s/2 - m, m/2);
	shrinkingSquares(x+s/2, y+s/2, s/2 - m, m/2);
	shrinkingSquares(x-s/2, y+s/2, s/2 - m, m/2);
}

// draws the spiral of squares with the help of the drawSquare helper function
void spiralSquares(int x, int y, float s){
	if (s > 40) return;
	drawSquare(x+exp(0.15*s)*cos(s), y+exp(0.15*s)*sin(s), exp(0.12*s));
	gfx_flush();
	usleep(50000);

	// iterates the angle/distance from the center out from 0
	spiralSquares(x, y, s + 0.75);
}

// draws the circular lace fractal with 6 new circles on the edge of each previous circle
void circularLace(int x, int y, int r, int m){
	if (r < 1) return;

	gfx_circle(x, y, r);
	gfx_flush();
	usleep(1000);

	// iterates around the 2*pi of a circle with cartesian/polar conversion
	int i;
	for (i = 0; i < 6; i++){
		circularLace(x+r*cos(i*M_PI/3), y+r*sin(i*M_PI/3), (r+m)/3, m/3);
	}
}

// draws the snowflake fractal by iterating 5 times over the 2*pi of a circle
void snowflake(int x, int y, int l){
	if (l < 1) return;

	int i;
	for (i = 0; i < 5; i++){
		gfx_line(x, y, x+l*cos(2*M_PI*i/5), y+l*sin(2*M_PI*i/5));
	}
	gfx_flush();
	usleep(1000);

	// recurses at the end of each line in the pentagonal snowflake
	for (i = 0; i < 5; i++){
		snowflake(x+l*cos(2*M_PI*i/5), y+l*sin(2*M_PI*i/5), l/3);
	}
}

// draws the tree fractal by calling two recursive functions, one for each side of the tree
void tree(int x, int y, int l, float a){
	if (l < 1) return;

	gfx_line(x, y, x-l*cos(a), y-l*sin(a));
	gfx_flush();
	usleep(1000);

	// recurses for each side by adding/subtracting the angle and decreasing the length of the "branch"
	tree(x-l*cos(a), y-l*sin(a), 2*l/3, a-M_PI/6);
	tree(x-l*cos(a), y-l*sin(a), 2*l/3, a+M_PI/6);
}

// draws the fern fractal by incrementing 4 times along each "branch" to start new ones
void fern(int x, int y, int l, float a){
	if (l < 3) return;

	gfx_line(x, y, x-l*cos(a), y-l*sin(a));
	gfx_flush();
	usleep(1000);

	// similar to the tree, one branch comes out of each side +/- the angle of rotation
	int i;
	for (i = 0; i < 4; i++){
		fern(x - (i+1)*l*cos(a)/4, y - (i+1)*l*sin(a)/4, l/3, a-M_PI/5);
		fern(x - (i+1)*l*cos(a)/4, y - (i+1)*l*sin(a)/4, l/3, a+M_PI/5);
	}
}

// draws the spiral of spirals fractal by drawing a point in the center of each spiral and then spiraling inward towards the center point
void spiral(int x, int y, float s, float t){
	if (s < 1) return;

	// center point
	gfx_point(x, y);
	gfx_flush();
	usleep(10);

	// each rotation
	s -= s/15;
	int xf = x+s*cos(t);
	int yf = y+s*sin(t);
	t += 0.5;

	// recursion
	spiral(xf, yf, s/3, 0);
	spiral(x, y, s, t);
}

// draws a triangle between the three points specified by the arguments
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 ){
	gfx_line(x1,y1,x2,y2);
	gfx_line(x2,y2,x3,y3);
	gfx_line(x3,y3,x1,y1);
}

// draws a square with a center at x,y and a side length of s
void drawSquare(int x, int y, int s){
	gfx_line(x-s/2, y-s/2, x+s/2, y-s/2);
	gfx_line(x-s/2, y-s/2, x-s/2, y+s/2);
	gfx_line(x+s/2, y+s/2, x+s/2, y-s/2);
	gfx_line(x+s/2, y+s/2, x-s/2, y+s/2);
}
