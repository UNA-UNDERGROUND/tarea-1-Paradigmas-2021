#include <cliente.h>
#include <contenedora.h>
#include <habitacion.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void guardarCadena(String *cadena) {
	char *buffer = malloc(sizeof(char) * 100);
	scanf("%s", buffer);
	setString(cadena, buffer);
}

void crearCliente(Cliente *cliente) {
	String *id = createString("a");
	String *nombre = createString("a");
	String *telefono = createString("a");

	int hw = 1;
	while (hw) {
		printf("\nIngrese los datos del cliente:");
		printf("\nID:");
		guardarCadena(id);
		cliente->id = id;
		printf("\n Edad:");
		scanf("%d", &cliente->edad);

		if (cliente->edad < 18) {
			printf("Un menor de edad no puede solicitar una habitacion\n");
			printf("Vuelva a ingresar los datos");
		} else {
			printf("\nNombre: ");
			guardarCadena(nombre);
			cliente->nombreCliente = nombre;
			printf("\nTelefono: ");
			guardarCadena(telefono);
			cliente->telefono = nombre;
			printf("\nMetodo de pago: ");
			cliente->metodoPago = efectivo;
			hw = 0;
		}
	}
}

void llenarInformacion(Informacion *informacion) {

	printf("\nReservacion todo incluido? ");
	printf("\n 1.Si \n 2.No \n(Ingrese el numero de la respuesta  )");
	scanf("%d", &informacion->todoIncluido);

	printf("\nNumero de adultos: ");
	scanf("%d", &informacion->numeroAdultos);

	printf("\nNumero de infantes: ");
	scanf("%d", &informacion->numeroInfante);

	printf("\nNumero de dias: ");
	scanf("%d", &informacion->numeroDias);
}

void reservarHabitacion(Habitacion *habitacion) {
	Cliente cliente;
	Informacion informacion;

	habitacion->estado = 'O';
	crearCliente(&cliente);
	char *tex = getString(cliente.nombreCliente);
	printf("Hola %s!\n", tex);
	char *tex2 = getString(cliente.id);
	printf("Hola %s!\n", tex2);
	llenarInformacion(&informacion);
	habitacion->cliente = &cliente;
	habitacion->informacion = &informacion;
}
