#include <stdio.h>
#include <string_util.h>

int main() {
	String* s = createString("Jonathan");
    printf("hola %s\n", getString(s));
	deleteString(&s);
	//podemos borrarlo varias veces, pues ya es nulo
	deleteString(&s);
	if (!s) {
		printf("eliminado el string\n");
	}
}

