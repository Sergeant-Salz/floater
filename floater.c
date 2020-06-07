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

    /* Wir ergänzen wieder die weggelassene 1 vor den Mantrissen */
    b1 = b1 + (1 << 23);
    b2 = b2 + (1 << 23);

    /* Extrahiere die exponenten durch rechtsshift um 23 und bitwise AND mit
    Hex 0xFF = 0b1111 */
    int e1 = (num1 >> 23) & 0xFF;
    int e2 = (num2 >> 23) & 0xFF;

    /* Einer der Werte ist NaN */
    if( (!e1 && b1) || (!e2 && b2)){
        return !0;
    }


    /* Wie merken uns das Vorzeichen (Nicht nach rechts gesiftet!)*/ 
    int s1 = num1 & (1 << 31);
    int s2 = num2 & (1 << 31);

    /* Wir schieben die Zahl mit dem kleineren Exponenten so, dass die beiden Exponenten gleich groß sind */
    while(e1 != e2){
        if(e1 < e2){
            e1++;
            b1 = b1 >> 1;
        } else {
            e2++;
            b2 = b2 >> 1;
        }
    }

    printf("Nach dem exponenten auslgeichen:\n");
    print_i_float(b1);
    print_i_float(b2);

    int b_sum;
    int e_sum = e1;
    int s_sum;
    
    /* Wenn beide Zahlen das selbe Vorzeichen haben*/
    if(s1 == s2) {
        /* Das Vorzeichen des Ergebnisses ist dann das selbe wie die beiden summanden */
        s_sum = s1;

        /* Wie können nun die Mantrissen einfach addieren */
        b_sum = b1 + b2;

        /* Prüfen ob das Ergebnis in das 24.bit übergelaufen ist */
        if(b_sum &  (1 << 24)){
            b_sum = b_sum >> 1;
            e_sum++;
        }

        /* Wir normalisieren das Ergebnis wieder */
        while(!(b_sum & (1 << 23))){
            e_sum--;
            b_sum = b_sum << 1;
        }

        /* Und entfernen dann die führende 1 */
        b_sum = b_sum ^ (1<<23);
    } else {
        /* Wenn die beiden unterschiedliche Vorzeichen haben bedeutet dass, dass wir eigentlich eine Subtraktion durchführen */
        if(s1){
            b_sum = b2 - b1;
        } else {
            b_sum = b1- b2;
        }

        /* Nun können wir an dem 23.bit erkennen ob das ergebnis positiv oder negativ ist */
        if(b_sum < 0){
            /* Negativ, also müssen wir das 2.er kompliment bilden, potentielle overflow bits clrearen,
             und das Ergebnisvorziechen auf 1 setzen */
            b_sum = -b_sum;
            b_sum = (b_sum & 0x7FFFFF);
            s_sum = (1 << 31);
        } else {
            /* Das Ergebnis ist positiv, also müssen wir nichts tuen außer potentielle overflow bits zu clearen */
            b_sum = (b_sum & 0x7FFFFF);
            s_sum = 0;
        }

         /* Wir normalisieren das Ergebnis wieder */
        while(!(b_sum & (1 << 23))){
            e_sum--;
            b_sum = b_sum << 1;
        }

        /* Und entfernen dann die führende 1 */
        b_sum = b_sum ^ (1<<23);
    }
    
    int sum = s_sum | (e_sum << 23) | b_sum;
    print_i_float(sum);
    return sum;
}


int main(int argc, char** argv){
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