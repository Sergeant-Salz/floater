#include <stdio.h>
/*
 * Calculate the integral of a given function function from start to end.
 * The area is divided into a given number of steps > 0.
 **/
float integrate(float (*function)(float), float start, float end, int steps){
    float stepSize = (end-start) / steps;
    float sum = 0;

    for(int step = 0; step < steps; step++){
        sum += (function(start + step * stepSize) + function(start + (step + 1) * stepSize)) / 2;
    }

    return sum * stepSize;
}

float myFunc(float x){
    return 2.2345f * x*x - x*x*x + 57*x;
}

int main(int argc, char** argv){
    printf("Result is:%f\n", integrate(myFunc, 0, 5, 1000));
    for(int i = 0; i < 100000; i++){
        integrate(myFunc, 0, 5, 1000);
    }
}