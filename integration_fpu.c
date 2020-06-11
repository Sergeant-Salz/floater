#include <stdio.h>
#include "integration.h"

float integrate(float (*function)(float), float start, float stepSize, int steps){
    float sum = 0;

    for(int step = 0; step < steps; step++){
        if(DEBUG){printf("%f\n",sum);}
        sum += (function(start + step * stepSize) + function(start + (step + 1) * stepSize)) / 2;
    }

    return sum * stepSize;
}

float myFunc(float x){
    return 2.2345*x*x - 57*x;
}

int main(int argc, char** argv){
    printf("Function at point 1 is:%f\n", myFunc(1));
    printf("Result is:%f\n", integrate(myFunc, 1, 0.005, STEPS));
    for(int i = 0; i < ITERATION_COUNT; i++){
        integrate(myFunc, 1, 0.005, STEPS);
    }
}