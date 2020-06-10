#include <stdio.h>
#include "integration.h"
#include "floater.c"

float integrate(float (*function)(float), float start, float stepSize, int steps){
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
    printf("Result is:%f\n", integrate(myFunc, 0, 0.005, 1000));
    f_sub(0,0);
    for(int i = 0; i < ITERATION_COUNT; i++){
        integrate(myFunc, 0, 5, 1000);
    }
}