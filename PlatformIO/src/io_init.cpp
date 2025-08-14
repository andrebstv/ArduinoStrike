/*
 * io_init.cpp
 *
 *  Created on: 13/03/2016
 *      Author: Dimitri
 */

#include "io_init.h"

#define NOVO_PROTOTIPO

void io_init(void)
{
	//Funcao que faz a inicializacao da direcao das portas.
	// |= Saidas (1 saida)
	// &~ Entradas (0 entrada)
	// Setando PORT Correpondente ativa pull up qndo entrada.
	DDRC |= (1<<PIN7); //LED PLACA
//	DDRD |= (1<<PIN6);//BOTAO DIREITO e PULL UP TIRAR ISSO!!!!
	// DDRD &= ~(1<<PIN6);//BOTAO DIREITO e PULL UP
	// PORTD |= (1<<PIN6);
	// //PORTD |= (1<<PIN7);

	// DDRC &= ~(1<<PIN1);//ENTRADA CARREGANDO e PULL_up
	// PORTC |= (1<<PIN1);
}

