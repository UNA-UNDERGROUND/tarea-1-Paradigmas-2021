#include <stddef.h>

typedef struct String String;

String *newString();
void deleteString(String *self);
const char *getString(String *self);
size_t getStringLenght(String *str);
size_t getStringSize(String *str);
void setString(String *self, const char *str);