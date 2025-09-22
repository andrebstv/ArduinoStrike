/*
 * io_init.h
 *
 *  Created on: 10/12/2009
 *      Author: Andre
 */
#ifndef IO_INIT_
#define IO_INIT_
#include <avr/io.h>
#include "sbit.h"
#define NOVO_PROTOTIPO
//==========================================================================================================//
//													SAIDAS
//==========================================================================================================//
	//SAIDAS
	#define LED				SBIT(PORTC,7)
	//ENTRADAS
	#define CARREGANDO		SBIT(PINC,1)

void io_init(void);

#endif
