#import <stdio.h>
#import <math.h>

int get_quadrant(double, double); 
double get_radius(double, double); 
double get_angle(double, double); 
void show_info(int, double, double);

int main(){
    double x, y;

    printf("Enter x and y: ");
    scanf("%lf %lf", &x, &y);

    show_info(get_quadrant(x, y), get_radius(x, y), get_angle(x, y));

    return 0;
}

int get_quadrant(double x, double y){
    if (x > 0){
        if (y > 0){
            return 1;
        }
        else {
            return 4;
        }
    }
    else {
        if (y > 0){
            return 2;
        }
        else {
            return 3;
        }
    }
}
double get_radius(double x, double y){
    return sqrt(pow(x, 2) + pow(y, 2));
}
double get_angle(double x, double y){
    double a = atan2(y, x);
    return a * 180 / M_PI;
}
void show_info(int q, double r, double a){
    printf("Quadrant: %d\nRadius: %0.2lf\nAngle: %0.2lf degrees\n", q, r, a);
}