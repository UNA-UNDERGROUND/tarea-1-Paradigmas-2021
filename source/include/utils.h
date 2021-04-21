#pragma once
#include <string_util.h>
#include <stdio.h>

String *readString();
String *readLine(char delim);
String *fReadString(FILE *stream);
String *fReadLine(FILE *stream, char delim);
