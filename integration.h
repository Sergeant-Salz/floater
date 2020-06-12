
//Print results after each step of integration
#define DEBUG 0

//How often the integration proccess is repeated
#define ITERATION_COUNT 1000

// The number of integrations steps to be taken 
#define STEPS 10000

// Print the results of the integration at the beginning of the function
#define PRINT_RESULTS 0

//Definitions for integrate_fpu
#define FUNC_CONST1_FPU 15.0
#define FUNC_CONST2_FPU 57.0
#define STEPSIZE_FPU 0.005
#define START_VALUE_FPU 1.0


// Definitions for integrate_i_float
#define FUNC_CONST1_I_FLOAT 0b01000001011100000000000000000000 // 15
#define FUNC_CONST2_I_FLOAT 0b01000010011001000000000000000000 // 57.0
#define STEPSIZE_I_FLOAT 0b00111011101000111101011100001010 // ~0.005
#define START_VALUE_I_FLOAT 0b00111111100000000000000000000000 // 1
#define ONE_I_FLOAT 0b00111111100000000000000000000000 // 1
#define ONE_HALF_I_FLOAT 0b00111111000000000000000000000000 // 0.5