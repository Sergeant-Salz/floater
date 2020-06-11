#include "floater.h"
#include <stdio.h>

#define DEBUG_PRINT 1

void print_i_float(i_float val){
    if(!DEBUG_PRINT){
        return;
    }
    i_float valCopy = val;
    for(int i = 0; i < 32; i++){
        if(i == 1 || i == 9){ printf(" ");}
        printf("%u", valCopy & (1 << 31) ? 1 : 0);
        valCopy = valCopy << 1;
    }
    printf("\n");
}

void print_i_float_sci(i_float val){
    if(!DEBUG_PRINT){
        return;
    }
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

/*
 * Multipy two floating point values 
 */
i_float f_mul(i_float num1, i_float num2){

    /* Wie merken uns das Vorzeichen (Nicht nach rechts gesiftet!)*/ 
    int s1 = num1 & (1 << 31);
    int s2 = num2 & (1 << 31);

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

    /* Neues Vorzeichen einfach durch XOR bestimmen */
    int s_sum = s1 ^ s2;


    /* Bevor wir multipizieren können müssen wir die beiden Mantissen so weit nach rechts schieben, dass
    es keinen Überlauf geben kann. Dies hat natürlich potentiell große Präzisionsverluste zur Folge. */
    b1 = b1 >> 8;
    b2 = b2 >> 8;

    int b_sum = b1 * b2;
    
    /* Addiere die beiden Exponenten, bedenke den bias abzuziehen da er sonst doppelt enthalten ist */
    int e_sum = e1 + e2 - 127;
    
    /*Dieses Ergebnis passt in allen fällen in 32 bit. Da wir zwei Zahlen mutiplizeren die eine 1 vor dem Komma stehen haben,
    können wir sicher sein dass an der 30. (oder 31. falls overflow) stelle eine 1 stehen muss. 
    Daher können wir das Ergebnis um eine feste menge nach rechts schieben um es wieder zu normalisieren */
    if(b_sum & (1 << 31)){
        /*Bedenke das hierbei führende 1-en vor alle s geschoben wird. Diese entfernen wir später wenn wir auch die führende 1 entfernen
        Außerdem schieben wir in diesem fall 1 mal mehr als sonst, daher müssen wir den exponenten entsprechend erhöhen*/
        b_sum = b_sum >> 8;
        e_sum++;
    } else {
        b_sum = b_sum >> 7;
    }

    /* Nicht vergessen die führende(n) 1 wieder zu entfernen */
    b_sum = b_sum & 0x7FFFFF;

    /* Ergebnis wieder zusammensetzen */
    int sum = s_sum | (e_sum << 23) | b_sum;
    return sum;
}

/* Substract the secound argument from the first one*/
i_float f_sub(i_float num1, i_float num2){
    /*Einfach das Vorzeichen der zweiten Zahl tauschen, und dann eine Addition durchführen*/
    return f_add(num1, num2 ^ (1 << 31));
}

/**
 * Add number one and two, returning a float.
 */
i_float f_add(i_float num1, i_float num2){
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
    /* Überprüfe ob eine der beiden Zahlen null ist (+0/-0) */
    if(!b1 && !e1){
        return num2;
    } else if (!b2 && !e2){
        return num1;
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
    }

    /* Wir normalisieren das Ergebnis wieder */
    while(!(b_sum & (1 << 23))){
        e_sum--;
        b_sum = b_sum << 1;
    }

    /* Und entfernen dann die führende 1 */
    b_sum = b_sum ^ (1<<23);
    
    int sum = s_sum | (e_sum << 23) | b_sum;
    print_i_float(sum);
    return sum;
}