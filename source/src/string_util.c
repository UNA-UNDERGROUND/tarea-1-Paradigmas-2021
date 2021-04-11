#include <stdlib.h>
#include <string.h>

typedef struct String {
	size_t size;
	size_t lenght;
	char *buffer;
} String;

String *newString() {
	String *newString = malloc(sizeof(String));
	newString->size = 0;
	newString->lenght = 0;
	newString->buffer = NULL;
	return newString;
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
void setString(String *self, const char *str);