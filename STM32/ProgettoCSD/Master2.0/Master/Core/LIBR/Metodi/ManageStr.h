/*
 * ManageStr.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Utente
 */

#ifndef LIBR_MANAGESTR_H_
#define LIBR_MANAGESTR_H_
#define MAX_BUFFER_LENGTH 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{

	float Temp;
	float Hmdy;
	int Mode;

}Stringa_TypeDef;


Stringa_TypeDef CutString(char*);
float AdaptSetPoint(char*);

#endif /* LIBR_MANAGESTR_H_ */
