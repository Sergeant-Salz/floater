#include <stdio.h>
#include "integration.h"

float integrate(float (*function)(float), float start, float stepSize, int steps){
    float sum = 0;

    for(int step = 0; step < steps; step++){
        if(DEBUG){printf("%f\n",  sum);}
        sum += function(start + step * stepSize) + (function(start + (step + 1) * stepSize)  * 0.5);
    }

    return sum * stepSize;
}

float quadratic(float x){
    return x*x;
}

float myFunc(float x){
    return 15*x*x - 57*x;
}

int main(int argc, char** argv){
    printf("Function at x=1 is:%f\n", myFunc(1));
    printf("Result is:%f\n", integrate(myFunc, 1, 0.005, STEPS));
    for(int i = 0; i < ITERATION_COUNT; i++){
        integrate(myFunc, 1, 0.005, STEPS);
    }
}