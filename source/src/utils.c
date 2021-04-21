#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

const size_t BUFFER_SIZE = 256;

String *readString() { return fReadString(stdin); }
String *readLine(char delim) { return fReadLine(stdin, delim); }
String *fReadString(FILE *stream) {
	String *string = NULL;
	if (stream) {
		size_t len = 0;
		size_t size = BUFFER_SIZE;
		char *buffer = malloc(BUFFER_SIZE);

		char c = getc(stream);
		while (c != EOF) {
			if (c == ' ' || c == '\n') {
				break;
			}
			// redimensionar
			if (len == size) {
				size_t new_size = (size + 1) * 1.25;
				char *new_buffer = malloc(new_size);
				memcpy(new_buffer, buffer, size);
				free(buffer);
				size = new_size;
				buffer = new_buffer;
			}
			buffer[len++] = c;

			c = getc(stream);
		}
		if (len > 0) {
			// necesitamos uno mas para agregar el caracter nulo
			if (len == size) {
				char *new_buffer = malloc(size + 1);
				memcpy(new_buffer, buffer, size);
				free(buffer);
				size++;
				buffer = new_buffer;
			}
			buffer[len++] = '\0';
			string = generateString(buffer, len, size);
		}
	}

	return string;
}
String *fReadLine(FILE *stream, char delim) {
	String *string = NULL;
	if (stream) {
		size_t len = 0;
		size_t size = BUFFER_SIZE;
		char *buffer = malloc(BUFFER_SIZE);

		char c = getc(stream);
		while (c != EOF) {
			if (c == delim) {
				break;
			}
			// redimensionar
			if (len == size) {
				size_t new_size = (size + 1) * 1.25;
				char *new_buffer = malloc(new_size);
				memcpy(new_buffer, buffer, size);
				free(buffer);
				size = new_size;
				buffer = new_buffer;
			}
			buffer[len++] = c;

			c = getc(stream);
		}
		if (len > 0) {
			// necesitamos uno mas para agregar el caracter nulo
			if (len == size) {
				char *new_buffer = malloc(size + 1);
				memcpy(new_buffer, buffer, size);
				free(buffer);
				size++;
				buffer = new_buffer;
			}
			buffer[len++] = '\0';
			string = generateString(buffer, len, size);
		}
	}

	return string;
}