#pragma once
#include <cliente.h>
#include <informacion.h>

typedef enum Clasificacion {
	primera = 1,
	segunda = 2,
	tercera = 3
} Clasificacion;

typedef struct Habitacion {
	String *id;
	char estado;
	Cliente *cliente;
	Informacion *informacion;
	int camas;
	Clasificacion clasificacion;
} Habitacion;