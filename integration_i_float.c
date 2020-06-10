#include <stdio.h>
#include "integration.h"
#include "floater.c"
#include "floater.h"

#define FUNC_CONST1 0b01000000000011110000001000001100 // ~2.2345
#define FUNC_CONST2 0b01000010011001000000000000000000 // 57.0
#define STEPSIZE 0b00111011101000111101011100001010 // ~0.005
#define START_VALUE 0b00111111100000000000000000000000 // 1
#define ONE 0b00111111100000000000000000000000 // 1
#define ONE_HALF 0b00111111000000000000000000000000 // 0.5

i_float integrate(i_float (*function)(i_float), i_float start, i_float stepSize, int steps){
    i_float sum = 0;
    step_f = 0;
    for(int step = 0; step < steps; step++){
        step_f = f_add(step_f, ONE);
        //sum += (function(start + step * stepSize) + function(start + (step + 1) * stepSize)) / 2;
        sum = f_add(sum, f_add( 
            function(f_add(start, f_mul(step_f, stepSize))),
            f_mul(function(f_add(start, f_mul( f_add(step_f, ONE), stepSize))), ONE_HALF);
    }

    return f_mul(sum, stepSize);
}

i_float myFunc(i_float x){
    // 2.2345f*x*x - 57*x
    return  f_sub( f_mul(f_mul(FUNC_CONST1,x) x) , f_mul(FUNC_CONST2, x));
}

int main(int argc, char** argv){
    printf("Result is:"); pint_i_float(integrate(myFunc, START_VALUE, STEPSIZE, STEPS));
    for(int i = 0; i < ITERATION_COUNT; i++){
        integrate(myFunc, START_VALUE, STEPSIZE, STEPS);
    }
}