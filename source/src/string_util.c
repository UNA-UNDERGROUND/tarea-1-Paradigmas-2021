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
		deleteString(self);
	}
	return self;
}

void deleteString(String *self) {
	if (self) {
		if (self->size) {
			free(self->buffer);
			free(self);
			self = NULL;
		}
	}
}
const char *getString(String *self) {
	return self && self->lenght ? self->buffer : "";
}
size_t getStringLenght(String *self) { return self ? self->lenght : 0; }
size_t getStringSize(String *self) { return self ? self->size : 0; }
bool resizeString(String *self, size_t new_size) {
	if (self) {
		if (self->size != new_size) {
			char *newBuffer = malloc(new_size);
			if (newBuffer) {
				// hay que copiar los valores y liberar la memoria
				if (self->size) {
					strcpy_s(newBuffer, new_size, self->buffer);
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
		size_t new_len = strlen(str);
		// practicamente no hay costo de copia
		// en un string nuevo ya que es solo reservar
		if (self->size < new_len && !resizeString(self, new_len + 1)) {
			return false;
		}
		strcpy_s(self->buffer, self->size, str);
		self->lenght = new_len;
		return true;
	}
	return false;
}
