#include "..\Window\public.h"
#include "mem_libs.h"

#define _USE_MATH_DEFINES
#include <math.h>

/*
utils.c

- Utility functions
- Constant values
*/

float axis[3][3] = {{1.0f, 0.0f, 0.0f},
					{0.0f, 1.0f, 0.0f},
					{0.0f, 0.0f, 1.0f}};

float nullVec[3] = {0.0f, 0.0f, 0.0f};


void vectorSet(float v[3], float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

void vectorCopy(float dest[3], float src[3])
{
	vectorSet(dest, src[0], src[1], src[2]);
}

void vectorClear(float v[3])
{
	vectorCopy(v, nullVec);
}

void vectorNegate(float v[3])
{
	vectorSet(v, -v[0], -v[1], -v[2]);
}

float vectorLength(float v[3])
{
	return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

float vectorNormalize(float v[3])
{
	float length = vectorLength(v);
	if (length)
	{
		vectorSet(v, v[0]/length, v[1]/length, v[2]/length);
	}
	return length;
}

void vectorAdd(float dest[3], float a[3], float b[3])
{ // dest = a + b
	int i;
	for (i=0; i<3; i++)
		dest[i] = a[i] + b[i];
}

void vectorSubtract(float dest[3], float a[3], float b[3])
{ // dest = a - b
	int i;
	for (i=0; i<3; i++)
		dest[i] = a[i] - b[i];
}

void vectorMult(float dest[3], float a[3], float b[3])
{ // dest = a * b
	vectorSet(dest, a[0]*b[0], a[1]*b[1], a[2]*b[2]);
}

void vectorScale(float dest[3], float s, float src[3])
{ // dest = s * src
	vectorSet(dest, s*src[0], s*src[1], s*src[2]);
}

void vectorMA(float out[3], float org[3], float s, float move[3])
{ // v = org + s * move
	int i;
	for (i=0; i<3; i++)
	{
		out[i] = org[i] + s * move[i];
	}
}

void vectorTransition(float v[3], float org[3], float dest[3], float percentage)
{ // v = org + percentage * (dest - org)
	int i;
	for (i=0; i<3; i++)
	{
		v[i] = org[i] + percentage * (dest[i] - org[i]);
	}
}

float vectorDot(float a[3], float b[3])
{ // Returns the dot product of both vectors
	float res = 0;
	int i;
	for (i=0; i<3; i++)
	{
		res += a[i] * b[i];
	}
	return res;
}

void vectorRotate(float vec[3], float targetAxis[3][3])
{ // Rotates the given vector to match the target axis
	float newVec[3];

	newVec[0] = vectorDot(vec, targetAxis[0]);
	newVec[1] = vectorDot(vec, targetAxis[1]);
	newVec[2] = vectorDot(vec, targetAxis[2]);
	
	vec[0] = newVec[0];
	vec[1] = newVec[1];
	vec[2] = newVec[2];
}

float vectorDistance(float a[3], float b[3])
{
	float vec[3];
	vectorSubtract(vec, a, b);
	return vectorLength(vec);
}

int randomIntBetween(int min, int max)
{
	if (max < min)
	{
		int temp = min;
		min = max;
		max = temp;
	}

	return min+rand()%(max-min+1);
}

float randomValueBetween(float min, float max)
{
	if (max < min)
	{
		float temp = min;
		min = max;
		max = temp;
	}

	return min+((float)rand() / (float)RAND_MAX) * (max-min);
}

byte randomByte()
{
	byte res = 0;
	int i;
	for (i = 0; i < 8; i++)
	{
		res = (2*res) + rand() % 2;
	}
	return res;
}

void fillWithRandom(void *dst, size_t size)
{
	uint i;
	for (i = 0; i < size; i++)
	{
		((byte*)dst)[i] = randomByte();
	}
}

int isInRange(float min, float val, float max)
{
	return ((min <= val) && (val <= max));
}

char *newString(char *s)
{
	int length = strlen(s);
	char *r = (char*)mem_alloc(sizeof(char)*(length+1));
	strncpy(r, s, length);
	r[length] = '\0';
	return r;
}

char *newString2(char *s, unsigned int len)
{
	unsigned int sLen = strlen(s);
	int length = (sLen<len)?sLen:len;
	char *r = (char*)mem_alloc(sizeof(char)*(len+1));
	strncpy(r, s, length);
	r[length] = '\0';
	return r;
}

unsigned int nbDigits(int n)
{ // Returns the amount of digits in the integer (also counts the minus sign if required)
	unsigned int i=0;

	if (n == 0)
		return 1;

	while (abs(n) > 0)
	{
		i++;
		n /= 10;
	}

	if (n<0)
		i++;

	return i;
}

char *strFromInt(int n)
{
	uint len = nbDigits(n);
	char *res = (char*)mem_alloc(sizeof(char)*len+1);
	sprintf(res, "%d", n);
	return res;
}

char *strFromFloat(float n)
{
	uint len = nbDigits((int)n) + 10;	// Something like that...
	char *res = (char*)mem_alloc(sizeof(char)*len+1);
	sprintf(res, "%f", n);
	return res;
}

char *strFromVec(float vec[3])
{
	char *res = (char*)mem_alloc(sizeof(char)*48); // Sounds about right
	sprintf(res, "%f %f %f", vec[0], vec[1], vec[2]);
	return res;
}

char *strFromBinary(ubyte *bin)
{
	uint len = mem_size(bin);
	char *res;
	uint i;

	if (!len) len = 1;

	res = (char*)mem_alloc(sizeof(char)*(len*9)); // 8 digits, one space or \0

	for (i = 0; i < len; i++)
	{
		uint j;
		for (j = 0; j < 8; j++)
		{
			if (bin[i] & (1 << (7-j)))
			{
				res[9*i+j] = '1';
			}
			else
			{
				res[9*i+j] = '0';
			}
		}
		res[9*i+j] = ' ';
	}
	res[9*len-1] = '\0';
	return res;
}

void vecFromStr(float vec[3], char *str)
{
	char *pos;
	char *pos2;
	char *temp;
	
	temp = newString(str);
	pos = strchr(temp, ' ');
	*pos = '\0';
	pos2 = strchr(pos+1, ' ');
	*pos2 = '\0';
	vec[0] = (float)atof(temp);
	vec[1] = (float)atof(pos+1);
	vec[2] = (float)atof(pos2+1);
	mem_free(temp);
}

void vectoangles( float *vec, float *angles ) {
	double	forward;
	double	yaw, pitch;
	
	if ( vec[1] == 0 && vec[0] == 0 ) {
		yaw = 0;
		if ( vec[2] > 0 ) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if ( vec[0] ) {
			yaw = ( atan2 ( (double)vec[1], (double)vec[0] ) * 180 / M_PI );
		}
		else if ( vec[1] > 0 ) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if ( yaw < 0 ) {
			yaw += 360;
		}

		forward = (double)sqrtf( vec[0]*vec[0] + vec[1]*vec[1] );
		pitch = ( atan2((double)vec[2], forward) * 180 / M_PI );
		if ( pitch < 0 ) {
			pitch += 360;
		}
	}

	angles[0] = (float)(-pitch);
	angles[1] = (float)(yaw);
	angles[2] = 0.0f;
}

void strip(char *s, char c)
{
	unsigned int i=0,j=0;
	unsigned int len = strlen(s);
	short inString = 0;
	
	while (j < len)
	{
		if ((s[j] == '\"' || s[j] == '\'') && (j == 0 || s[j-1] != '\\') && s[j] != c)
			inString = !inString;

		if (!inString)
		{
			if (s[j] == c)
			{
				j++;
				continue;
			}
		}
		s[i] = s[j];
		i++;
		j++;
	}
	s[i] = '\0';
}

void AngleVectors(float *angles, float *forward, float *right, float *up) {
	double	angle;
	double	sr, sp, sy, cr, cp, cy;
	
	angle = angles[1] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[0] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[2] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);
	
	if (forward)
	{
		forward[0] = (float)(cp*cy);
		forward[1] = (float)(cp*sy);
		forward[2] = (float)(-sp);
	}
	if (right)
	{
		right[0] = (float)(-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (float)(-1*sr*sp*sy+-1*cr*cy);
		right[2] = (float)(-1*sr*cp);
	}
	if (up)
	{
		up[0] = (float)(cr*sp*cy+-sr*-sy);
		up[1] = (float)(cr*sp*sy+-sr*cy);
		up[2] = (float)(cr*cp);
	}
}

float atLeastOne(float x)
{ // Utility function that prevents x's rounded value to be equal to 0 unless it actually is 0 (yes, seriously)
	if (x > -1 && x < 0)
		return -1;
	if (x > 0 && x < 1)
		return 1;

	return x;
}

void strcpy_safe(char *dst, char *src)
{ // Copies string src to dst while respecting dst's memory size
	size_t maxSize = mem_size(dst);
	unsigned int i=0;

	if (!maxSize) return;

	while (src[i] != '\0' && i < maxSize)
	{
		dst[i] = src[i];
		i++;
	}

	if (i >= maxSize)
	{
		dst[maxSize-1] = '\0';
	}
	else
	{
		dst[i] = '\0';
	}
}

void quit(void)
{ // Exit the program
	mem_free_all();
	exit(0);
}