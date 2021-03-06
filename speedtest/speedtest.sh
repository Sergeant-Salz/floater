EXECUTABLE_FOLDER="../executables/"

EXE1_NAME="integrate_fpu"
EXE1_NICE_NAME="FPU Integration"
EXE2_NAME="integrate_i_float"
EXE2_NICE_NAME="Custom Float Integration"

echo -e "Beginning speedtest using FPU:\n"
echo -e "----------------------------------\n"
echo "Testing "$EXE1_NICE_NAME" with -O0"
time $EXECUTABLE_FOLDER$EXE1_NAME
echo -e "\n----------------------------------"
echo -e "\nTesting "$EXE1_NICE_NAME" with -O1"
time $EXECUTABLE_FOLDER$EXE1_NAME"_O1"
echo -e "\n----------------------------------"
echo -e "\nTesting "$EXE1_NICE_NAME" with -O2"
time $EXECUTABLE_FOLDER$EXE1_NAME"_O2"
echo -e "\n----------------------------------"
echo -e "\nTesting "$EXE1_NICE_NAME" with -O3"
time $EXECUTABLE_FOLDER$EXE1_NAME"_O3"

echo "#####################################"
echo -e "\nBeginning speedtest using softfloat:\n"
echo -e "----------------------------------\n"
echo "Testing "$EXE2_NICE_NAME" with -O0"
time $EXECUTABLE_FOLDER$EXE2_NAME
echo -e "\n----------------------------------"
echo -e "\nTesting "$EXE2_NICE_NAME" with -O1"
time $EXECUTABLE_FOLDER$EXE2_NAME"_O1"
echo -e "\n----------------------------------"
echo -e "\nTesting "$EXE2_NICE_NAME" with -O2"
time $EXECUTABLE_FOLDER$EXE2_NAME"_O2"
echo -e "\n----------------------------------"
echo -e "\nTesting "$EXE2_NICE_NAME" with -O3"
time $EXECUTABLE_FOLDER$EXE2_NAME"_O3"
