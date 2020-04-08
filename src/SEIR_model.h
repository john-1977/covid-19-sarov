#pragma once

enum SEIR_State
{
	Susceptible = 0,	// Восприимчивый
	Exposed,			// Контактный
	Infectious,			// Инфицированный
	Recovered,			// Выздоровевший
	Dead				// Умерший
};
