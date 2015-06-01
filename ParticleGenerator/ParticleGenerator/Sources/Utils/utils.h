#ifndef UTILS_H_DEFINED
#define UTILS_H_DEFINED

#include "util_types.h"

int isInRange(float min, float val, float max);
char *newString(char *s);
char *newString2(char *s, unsigned int length);
unsigned int nbDigits(int n);
char *strFromInt(int n);
char *strFromFloat(float n);
char *strFromVec(float vec[3]);
char *strFromBinary(ubyte *bin);
void strip(char *s, char c);
void vecFromStr(float vec[3], char *str);

int randomIntBetween(int min, int max);
float randomValueBetween(float min, float max);
byte randomByte();

float atLeastOne(float x);
void strcpy_safe(char *dst, char *src);

void quit(void);

#endif