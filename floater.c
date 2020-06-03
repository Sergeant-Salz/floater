#include "floater.h"
#include <stdio.h>


int main(int argc, char** argv){
    // Should be 3,5
    i_float val = 0b01000000011000000000000000000000;
    printf("Value is: %e\n", val);
    printf("Sign is: %u\n", sign(val));
    printf("Characteristic is: %u\n", characteristic(val));
    printf("Fraction is: %x\n", fraction(val));
    return 0;
}

i_float f_add(i_float num1, i_float num2){
    return 0;
}

/**
 * Add number one and two, returning a float.
 */
i_float f_add_demo(i_float num1, i_float num2){
    /* Extrahiere die Bruchanteile der beiden Zahlen indem wir ein bitwises AND mit Hex 0x7FFFFF = 23x 1 in binär
    durchführen */
    uint b1 = num1 & 0x7FFFFF;
    uint b2 = num2 & 0x7FFFFF;
    /* Extrahiere die exponenten durch rechtsshift um 23 und bitwise AND mit
    Hex 0xFF = 0b1111 */
    uint e1 = (num1 >> 23) & 0xFF;
    uint e2 = (num2 >> 23) & 0xFF;

    /* Die Bruchanteile müssen wieder um ihre führende 1 erweitert werden */
    b1 = b1 | (1 << 24);
    b2 = b2 | (1 << 24);

    /* Exponenten vergleichen um die Werte auf den selben Exponenten zu bringen 
    Außerdem merken wir uns den größeren Exponenten */
    uint e_gemein;

    /* Wenn e2 > e1 muss b1 um die Differenz geschoben werden */
    if(e2 > e1){
        e_gemein = e2;
        e1 = e1 >> e2 - e1;
    } else { /* Ansonsten muss e2 um die entsprechende differenz geschoben werden */
        e_gemein = e1;
        e2 = e2 >> e1 - e2;
    }

    /* Jetzt können wir die Mantrissen, die jetzt den selben Exponenten haben, addieren */
}