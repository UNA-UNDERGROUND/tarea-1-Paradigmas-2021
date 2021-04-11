#include <stddef.h>
#include <stdbool.h>

typedef struct String String;

String *newString();
void deleteString(String *self);
const char *getString(String *self);
size_t getStringLenght(String *str);
size_t getStringSize(String *str);
bool resizeString(String *self, size_t new_size);
bool setString(String *self, const char *str);
