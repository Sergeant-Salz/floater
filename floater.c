#include "floater.h"
#include <stdio.h>

i_float f_add(i_float num1, i_float num2){
    return 0;
}

void print_i_float(i_float val){
    i_float valCopy = val;
    for(int i = 0; i < 32; i++){
        if(i == 1 || i == 9){ printf(" ");}
        printf("%u", valCopy & (1 << 31) ? 1 : 0);
        valCopy = valCopy << 1;
    }
    printf("\n");
}

void print_i_float_sci(i_float val){
    if(sign(val)){
        printf("-");
    }
    double mantisse = 1;
    int mant = val << 9;
    
    for(int i = 0; i < 23; i++){
        if(mant & (1 << 31)){
            mantisse += 1.0/(2 << i);
        }
        mant = mant << 1;
    }
    printf("%fe%d ", mantisse, characteristic(val) - 127);
} 

/**
 * Add number one and two, returning a float.
 */
i_float f_add_demo(i_float num1, i_float num2){
    /* Extrahiere die Bruchanteile der beiden Zahlen indem wir ein bitwises AND mit Hex 0x7FFFFF = 23x 1 in binär
    durchführen */
    int b1 = num1 & 0x7FFFFF;
    int b2 = num2 & 0x7FFFFF;
    /* Extrahiere die exponenten durch rechtsshift um 23 und bitwise AND mit
    Hex 0xFF = 0b1111 */
    int e1 = (num1 >> 23) & 0xFF;
    int e2 = (num2 >> 23) & 0xFF;


    /* Wir ergänzen wieder die weggelassene 1 vor den Mantrissen */
    b1 = b1 + (1 << 23);
    b2 = b2 + (1 << 23);

    /* Exponenten vergleichen um die Werte auf den selben Exponenten zu bringen 
    Außerdem merken wir uns den größeren Exponenten */
    int e_sum;

    /* Wenn e2 > e1 muss b1 um die Differenz geschoben werden */
    if(e2 > e1){
        e_sum = e2;
        b1 = b1 >> (e2 - e1);
    } else { /* Ansonsten muss b2 um die entsprechende differenz geschoben werden */
        e_sum = e1;
        b2 = b2 >> (e1 - e2);
    }


    /* Jetzt geht es an die eigentliche Addition:
    Zuerst speichern wir die jeweiligen Vorzeichen */

    int s1 = num1 & (1 << 31);
    int s2 = num2 & (1 << 31);

    /*Fall I: Beide Summanden haben das selbe Vorzeichen
    - Normale Addition. Für das Vorzeichen wählen, wenn beide negativ, dann s_sum 1, sonst 0.
    Fall II: Einer der beiden Sumanden ist negativ
    - Wir bilden wir das 2'er Komliment und addieren dann. 
      Dann checken wir ob das Ergebnis positiv oder negativ ist uns setzen s_sum entsprechend */
    int b_sum, s_sum;

    if(s1 == s2){
        b_sum = b1 + b2;
        s_sum = s1 ? 1 : 0;
        /* Check auf overflow. Der maximale overflow kann 3 (11) betragen, da die mantrissen selber
        ja immer kleiner als 2 sind, somit müssen wir maximal um 1 nach rechts schieben.
        Wie bei Addition von Zweierkompliment zahlen üblich muss nur geprüft werden,
        ob es einen overflow gibt wenn die Vorzeichen untschiedlich gleich*/
        if(b_sum & (1 << 24)) {
            b_sum = b_sum >> 1;
            e_sum ++;
        }
    } else {
        int b_sum = (s1 ? -b1 : b1) + (s2 ? -b2 : b2);
        print_i_float((s1 ? -b1 : b1));
        print_i_float((s2 ? -b2 : b2));
        print_i_float(b_sum);
        /* Jetzt checken wir ob das Ergebnis negativ ist. In diesem Fall wandeln wir es in eine positive Zahl um, und merken uns das Vorzeichen */
        s_sum = 0;
        if(b_sum < 0){
            s_sum = 1;
            b_sum = -b_sum;
        }
    }


    /* Jetzt müssen wir sicherstellen dass die neue Mantrisse wieder eine führende 1 hat, d.h.
    wir führen so lange linksshifts durch, bis eine 1 an der 24. Position steht. 
    Dabei ist der Sonderfall b_sum = 0 zu beachten. Hier würden wir sonst in eine Endlosschleife geraten. Nach dem
    IEEE FPS setzen wir hierfür den Wert E = M = 0 */
    if(!b_sum){ return 0; }

    while(!(b_sum & (1 << 23))) {
        b_sum = b_sum << 1;
        e_sum--;
    }

    /* Daraufhin entfernen wir die führende 1 und erhalten so die fertige Mantisse*/
    b_sum = b_sum ^ (1 << 23);

    /* Jetzt müssen wir nur das Ergebnis rekonstruieren */
    i_float sum = (s_sum << 31) | (e_sum << 23) | b_sum;
    print_i_float(sum);

    return sum;
}


int main(int argc, char** argv){
    // Should be 3,5
    i_float val1 = 0b00111110101100101000000000000000; //0,3486328125
    i_float val2 = 0b10111110111100001000000000000000; //-0,4697265625
    i_float val3 = 0b10111111011100011000000000000000; //-0,943359375
    i_float val4 = 0b00111111011101011100000000000000; //0.9599609375

    printf("\nval1 + val4 = ");
    i_float result1 = f_add_demo(val1, val4);
    print_i_float_sci(result1);
    printf("\n\n");

    printf("\nval2 + val4: ");
    i_float result2 = f_add_demo(val2, val4);
    print_i_float_sci(result2);
    printf("\n\n");

    printf("\nval3 + val4: ");
    i_float result3 = f_add_demo(val3, val4);
    print_i_float_sci(result3);
    printf("\n\n");

    return 0;
}