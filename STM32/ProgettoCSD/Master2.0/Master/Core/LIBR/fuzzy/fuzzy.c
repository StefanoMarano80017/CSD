/*
 * fuzzy.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Utente
 */

#include "fuzzy.h"

double calcola_fuzzy(float inputA, float inputB){
	    // Valuta le funzioni di appartenenza per A e B
	    float mA = membershipA(inputA);
	    float mB = membershipB(inputB);

	    if ((mA == 0 && mB == 0) || (mA == 2 && mB == 2)){
	        return -70; //forte
	    } else if ((mA == 0 && mB == 1) || (mA == 1 && mB == 0) || (mA == 1 && mB == 1) || (mA == 2 && mB == 1)) {
	        return -35; //medio
	    } else if ((mA == 0 && mB == 2) || (mA == 1 && mB == 2) || (mA == 2 && mB == 0)){
	        return -5; //debole
	    }


	    // Restituisci l'operatore MIN per aggregare i risultati
	    return (mA < mB) ? mA : mB;
}

float membershipA(float x) {
    if (x <= 15) {
        return 0; //freddo
    } else if (x > 15 && x <= 25) {
        return 1; //mite
    } else if (x > 25) {
        return 2; //caldo
    }
}

float membershipB(float x) {
    if (x <= 30) {
        return 0; //asciutto
    } else if (x > 20 && x <= 50) {
        return 1; //normale
    } else if (x > 50) {
        return 2; //umido
    }
}
