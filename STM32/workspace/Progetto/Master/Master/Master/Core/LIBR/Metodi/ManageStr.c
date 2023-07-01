/*
 * ManageStr.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Utente
 */
# include "ManageStr.h"
Stringa_TypeDef str;
Stringa_TypeDef CutString(char* buffer){
	// Troviamo l'indice del carattere '+' nel buffer
	   int plus_index = strchr(buffer, '+') - buffer;

	   // Estraiamo la stringa contenente il valore della temperatura
	   char temp_str[MAX_BUFFER_LENGTH];
	   strncpy(temp_str, buffer, plus_index);
	   temp_str[plus_index] = '\0';

	   // Estraiamo la stringa contenente il valore dell'umidità
	   char hmdy_str[MAX_BUFFER_LENGTH];
	   strncpy(hmdy_str, buffer + plus_index + 1, MAX_BUFFER_LENGTH - plus_index - 1);
	   hmdy_str[MAX_BUFFER_LENGTH - plus_index - 1] = '\0';

	   // Convertiamo le stringhe in valori di tipo float
	   float temp = atof(temp_str);
	   float hmdy = atof(hmdy_str);
	   str.Temp=temp;
	   str.Hmdy=hmdy;


return str;

}












