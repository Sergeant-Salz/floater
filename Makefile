all: integrate_fpu integrate_i_float
full: integrate_fpu_full integrate_i_float_full

integrate_fpu_full:
	@gcc integration_fpu.c -o ./executables/integrate_fpu
	@gcc -O1 integration_fpu.c -o ./executables/integrate_fpu_O1
	@gcc -O2 integration_fpu.c -o ./executables/integrate_fpu_O2
	@gcc -O3 integration_fpu.c -o ./executables/integrate_fpu_O3

integrate_fpu:
	@gcc integration_fpu.c -o ./executables/integrate_fpu

integrate_i_float_full:
	@gcc integration_i_float.c -o ./executables/integrate_i_float
	@gcc -O1 integration_i_float.c -o ./executables/integrate_i_float_O1
	@gcc -O2 integration_i_float.c -o ./executables/integrate_i_float_O2
	@gcc -O3 integration_i_float.c -o ./executables/integrate_i_float_O3

integrate_i_float:
	@gcc integration_i_float.c -o ./executables/integrate_i_float