#pragma once
#include <stdio.h>
#include <string_util.h>

String *readString();
String *readLine(char delim);
String *fReadString(FILE *stream);
String *fReadLine(FILE *stream, char delim);
const char *parseNumber(const float num, const char *fmt);