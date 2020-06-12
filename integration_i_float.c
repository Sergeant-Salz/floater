#include <stdio.h>
#include "integration.h"
#include "floater.c"
#include "floater.h"

i_float integrate(i_float (*function)(i_float), i_float start, i_float stepSize, int steps){
    i_float sum = 0;
    i_float step_f = 0;
    for(int step = 0; step < steps; step++){
        if(DEBUG){print_i_float(sum);}
        sum = f_add(sum, 
            f_add( 
                function(
                    f_add(start, 
                        f_mul(step_f, stepSize))
                    ),
                f_mul(
                    function(
                        f_add(start, 
                            f_mul(
                                f_add(step_f, ONE_I_FLOAT),
                                stepSize)
                            )
                        ),
                    ONE_HALF_I_FLOAT
                    )
                )
        );
        step_f = f_add(step_f, ONE_I_FLOAT);
    }

    return f_mul(sum, stepSize);
}

i_float quadratic(i_float x){
    return f_mul(x,x);
}

i_float myFunc(i_float x){
    //15*x*x - 57*x
    return f_sub(
        f_mul(
            f_mul(FUNC_CONST1_I_FLOAT,x), 
            x),
        f_mul(FUNC_CONST2_I_FLOAT, x)
        );
}

int main(int argc, char** argv){
    if(PRINT_RESULTS){
        printf("Function at x=1 is:\n"); print_i_float(myFunc(START_VALUE_I_FLOAT));
        printf("Result is:\n"); print_i_float(integrate(myFunc, START_VALUE_I_FLOAT, STEPSIZE_I_FLOAT, STEPS));
    }
    for(int i = 0; i < ITERATION_COUNT; i++){
        integrate(myFunc, START_VALUE_I_FLOAT, STEPSIZE_I_FLOAT, STEPS);
    }
}