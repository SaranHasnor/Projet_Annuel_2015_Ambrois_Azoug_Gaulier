#pragma once

extern "C" {
#include <Utils\vec3D.h>
}

class GeometryData
{
public:
	GeometryData(void);
	~GeometryData(void);

	float		position[3];
	float		angle[3];

	float		velocity[3];
	float		rotation[3];

	float		acceleration[3];
};

