#include <stdlib.h>
#include <string.h>
#include <string_util.h>

typedef struct String {
	size_t size;
	size_t lenght;
	char *buffer;
} String;

String *newString() {
	String *self = malloc(sizeof(String));
	if (self) {
		self->size = 0;
		self->lenght = 0;
		self->buffer = NULL;
	}
	return self;
}
String *createString(const char *str) {
	String *self = newString();
	if (!setString(self, str)) {
		deleteString(&self);
	}
	return self;
}

String *generateString(char *buffer, size_t length, size_t size) {
	String *self = NULL;
	if (buffer) {
		self = newString();
		self->buffer = buffer;
		self->lenght = length;
		self->size = size;
	}
	return self;
}

void deleteString(String **self) {
	if (self && *self) {
		if ((*self)->size) {
			free((*self)->buffer);
			free(*self);
			(*self) = NULL;
		}
	}
}
const char *getString(String *self) {
	return (self && self->buffer != NULL) && self->lenght ? self->buffer : "";
}
size_t getStringLenght(String *self) { return self ? self->lenght : 0; }
size_t getStringSize(String *self) { return self ? self->size : 0; }
bool resizeString(String *self, size_t new_size) {
	if (self) {
		if (self->size != new_size) {
			char *newBuffer = calloc(new_size, sizeof(char));
			if (newBuffer) {
				// hay que copiar los valores y liberar la memoria
				if (self->size) {
					// si la longitud nueva es menor solo copiamos hasta donde
					// podemos teniendo en cuenta el caracter nulo
					size_t longitud = strlen(self->buffer) + 1;
					if (longitud > new_size) {
						longitud = new_size;
					}
					memcpy(newBuffer, self->buffer, longitud);
					// no es portable
					// strcpy_s(newBuffer, new_size, self->buffer);
					free(self->buffer);
				}
				self->buffer = newBuffer;
				self->size = new_size;
				self->lenght =
				    self->lenght > new_size ? new_size : self->lenght;
				return true;
			}
		} else {
			// no hacemos nada, es la misma longitud
			return true;
		}
	}
	// self == NULL || no se puede redimensionar
	return false;
}
bool setString(String *self, const char *str) {
	if (self) {
		size_t new_len = strlen(str) + 1;
		// practicamente no hay costo de copia
		// en un string nuevo ya que es solo reservar
		if (self->size < new_len && !resizeString(self, new_len + 1)) {
			return false;
		}
		// en C es importante contar el caracter nulo
		// y strlen no lo toma en cuenta
		if (strcmp(str, "")) {
			memcpy(self->buffer, str, new_len);
		} else {
			memset(self->buffer, 0, self->size);
		}

		// no es portable
		// strcpy_s(self->buffer, self->size, str);
		self->lenght = new_len;
		return true;
	}
	return false;
}
bool catString(String *self, String *other) {
	if (self && other) {
		size_t new_size = self->lenght + other->lenght - 1;
		// redimensionar si es requerido
		if (new_size > self->size && !resizeString(self, new_size)) {
			return false;
		}
		memcpy(self->buffer + (self->lenght - 1), other->buffer, other->lenght);
	}

	return false;
}
bool cmpString(String *self, String *other) {
	if (self == other) {
		return true;
	}
	if (!self || !other || self->lenght != other->lenght) {
		return false;
	}

	for (size_t i = 0; i < self->lenght; i++) {
		if (self->buffer[i] != other->buffer[i]) {
			return false;
		}
	}

	return true;
}