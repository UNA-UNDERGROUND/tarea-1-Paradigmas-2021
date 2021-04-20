#pragma once
#include <string_util.h>

typedef enum tipoPago { efectivo, tarjetaDebito, tarjetaCredito } tipoPago;

typedef struct Cliente {
	String *nombreCliente;
	String *id;
	tipoPago metodoPago;
	String *telefono;
	String *numeroCuenta;
	int edad;
} Cliente;