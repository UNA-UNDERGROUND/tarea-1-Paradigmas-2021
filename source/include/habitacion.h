#pragma once
#include <informacion.h>
#include <cliente.h>

typedef struct Habitacion{
	String* id;
	char estado;
	Cliente* cliente;
	Informacion* informacion;
}Habitacion;