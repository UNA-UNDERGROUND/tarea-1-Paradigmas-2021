#include <cliente.h>
#include <contenedora.h>
#include <habitacion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string_util.h>
#include <utils.h>
#include <time.h>

const int max_pisos = 5;
const int max_habitaciones = 5;

Contenedora contenedor;

bool continuar = true;

bool readValue(void *ptr, size_t size, FILE *stream) {
	if (!continuar) {
		return false;
	}
	continuar = (fread(ptr, size, 1, stream) == size);
	return continuar;
}

void inicializarMemoria() {
	srand(time(0));
	contenedor.pisos = max_pisos;
	contenedor.habitaciones = max_habitaciones;
	contenedor.vec = malloc(sizeof(Habitacion *) * max_pisos);

	FILE *fhab = fopen("habitacion.bin", "w+");
	FILE *fcli = fopen("cliente.bin", "w+");
	FILE *finf = fopen("informacion.bin", "w+");

	// con esto aseguramos siempre estar inicializado
	for (size_t i = 0; i < contenedor.pisos; i++) {
		contenedor.vec[i] =
		    malloc(sizeof(Habitacion) * contenedor.habitaciones);
		for (size_t j = 0; j < contenedor.habitaciones; j++) {
			size_t len = snprintf(NULL, 0, "%zu-%zu", i, j);
			char *buffer = malloc(len + 1);
			snprintf(buffer, len + 1, "%zu-%zu", i, j);
			contenedor.vec[i][j].id = generateString(buffer, len + 1, len + 1);
			contenedor.vec[i][j].estado = 'L';
			contenedor.vec[i][j].cliente = NULL;
			contenedor.vec[i][j].informacion = NULL;
			contenedor.vec[i][j].camas = 2 + (rand() % (5 - 2));
			contenedor.vec[i][j].clasificacion = 1 + (rand() % (3 - 1));
		}
	}

	if (fhab && fcli && finf) {
		for (size_t i = 0; i < contenedor.pisos; i++) {
			contenedor.vec[i] =
			    malloc(sizeof(Habitacion) * contenedor.habitaciones);
			for (size_t j = 0; j < contenedor.habitaciones; j++) {
				Habitacion *hab = &contenedor.vec[i][j];
				char *id = NULL;
				size_t id_len;
				char estado;
				int camas;
				Clasificacion clasificacion;
				char cCli;
				char cInf;
				Cliente *cliente = NULL;
				Informacion *informacion = NULL;

				readValue(&id_len, sizeof(size_t), fhab);
				if (continuar) {
					id = malloc(id_len);
					readValue(&id, id_len, fhab);
					readValue(&estado, sizeof(char), fhab);
					readValue(&camas, sizeof(int), fhab);
					readValue(&clasificacion, sizeof(clasificacion), fhab);
					readValue(&cCli, sizeof(char), fhab);
					readValue(&cInf, sizeof(char), fhab);
				}

				if (continuar && cCli == '1') {
					cliente = malloc(sizeof(Cliente));
					size_t nomCli_len;
					size_t idCli_len;
					size_t telefono_len;
					size_t numeroCuenta_len;
					char *nomCli = NULL;
					char *idCli = NULL;
					tipoPago metodoPago;
					char *telefono = NULL;
					char *numeroCuenta = NULL;
					int edad;
					readValue(&nomCli_len, sizeof(size_t), fcli);
					nomCli = malloc(nomCli_len);
					readValue(&nomCli, nomCli_len, fcli);
					readValue(&idCli_len, sizeof(size_t), fcli);
					idCli = malloc(idCli_len);
					readValue(&idCli, idCli_len, fcli);
					readValue(&metodoPago, sizeof(tipoPago), fcli);
					readValue(&telefono_len, sizeof(size_t), fcli);
					telefono = malloc(telefono_len);
					readValue(&telefono, telefono_len, fcli);
					readValue(&numeroCuenta_len, sizeof(size_t), fcli);
					numeroCuenta = malloc(numeroCuenta_len);
					readValue(&numeroCuenta, numeroCuenta_len, fcli);
					readValue(&edad, sizeof(int), fcli);

					if (continuar) {
						cliente->nombreCliente =
						    generateString(nomCli, nomCli_len, nomCli_len);
						cliente->id =
						    generateString(idCli, idCli_len, idCli_len);
						cliente->metodoPago = metodoPago;
						cliente->telefono = generateString(
						    telefono, telefono_len, telefono_len);
						cliente->numeroCuenta = generateString(
						    numeroCuenta, numeroCuenta_len, numeroCuenta_len);
						cliente->edad = edad;
					} else {
						free(cliente);
						free(nomCli);
						free(idCli);
						free(telefono);
						free(numeroCuenta);
					}
				}
				if (continuar && cInf == '1') {
					informacion = malloc(sizeof(Informacion));
					readValue(&informacion, sizeof(Informacion), finf);
					if (!continuar) {
						free(informacion);
					}
				}
				if (continuar) {
					//eliminamos el id anterior ya creado
					deleteString(&hab->id);
					hab->id = generateString(id, id_len, id_len);
					hab->estado = estado;
					hab->cliente = cliente;
					hab->informacion = informacion;
					hab->camas = camas;
					hab->clasificacion = clasificacion;
				} else {
					free(id);
				}
			}
		}
		fclose(fhab);
		fclose(fcli);
		fclose(finf);
	} else {
	}
}

void liberarMemoria() {
	FILE *fhab = fopen("habitacion.bin", "w+");
	FILE *fcli = fopen("cliente.bin", "w+");
	FILE *finf = fopen("informacion.bin", "w+");
	if (fhab && fcli && finf) {
		for (size_t i = 0; i < contenedor.pisos; i++) {
			for (size_t j = 0; j < contenedor.habitaciones; j++) {
				Habitacion *hab = &contenedor.vec[i][j];
				const char *id = getString(hab->id);
				size_t id_len = (strlen(id) + 1);
				char estado = hab->estado;
				int camas = hab->camas;
				Clasificacion clasificacion = hab->clasificacion;
				Cliente *cliente = hab->cliente;
				Informacion *informacion = hab->informacion;

				fwrite(&id_len, sizeof(size_t), 1, fhab);
				fwrite(id, id_len, 1, fhab);
				fwrite(&estado, sizeof(char), 1, fhab);
				fwrite(&camas, sizeof(int), 1, fhab);
				fwrite(&clasificacion, sizeof(clasificacion), 1, fhab);
				fwrite(cliente ? "1" : "0", sizeof(char), 1, fhab);
				fwrite(informacion ? "1" : "0", sizeof(char), 1, fhab);

				if (cliente) {

					const char *nomCli = getString(cliente->nombreCliente);
					size_t nomCli_len = strlen(nomCli) + 1;
					const char *idCli = getString(cliente->id);
					size_t idCli_len = strlen(idCli) + 1;
					tipoPago metodoPago = cliente->metodoPago;
					const char *telefono = getString(cliente->telefono);
					size_t telefono_len = strlen(telefono) + 1;
					const char *numeroCuenta = getString(cliente->numeroCuenta);
					size_t numeroCuenta_len = strlen(numeroCuenta) + 1;
					int edad = cliente->edad;
					fwrite(&nomCli_len, sizeof(size_t), 1, fcli);
					fwrite(nomCli, nomCli_len, 1, fcli);
					fwrite(&idCli_len, sizeof(size_t), 1, fcli);
					fwrite(idCli, idCli_len, 1, fcli);
					fwrite(&metodoPago, sizeof(tipoPago), 1, fcli);
					fwrite(&telefono_len, sizeof(size_t), 1, fcli);
					fwrite(telefono, telefono_len, 1, fcli);
					fwrite(&numeroCuenta_len, sizeof(size_t), 1, fcli);
					fwrite(numeroCuenta, numeroCuenta_len, 1, fcli);
					fwrite(&edad, sizeof(int), 1, fcli);
				}
				if (informacion) {
					fwrite(informacion, sizeof(Informacion), 1, finf);
				}
				return;
			}
			free(contenedor.vec[i]);
		}
		fclose(fhab);
		fclose(fcli);
		fclose(finf);
	} else {
		for (size_t i = 0; i < contenedor.pisos; i++) {
			free(contenedor.vec[i]);
		}
	}

	free(contenedor.vec);
}