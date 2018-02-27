#pragma once
#include <cyPoint.h>

struct Vertex_data {
	cyPoint3f position;
	cyPoint3f normal;
	cyPoint3f uv;

	Vertex_data(cyPoint3f pos, cyPoint3f nrml, cyPoint3f vtuv) :
		position(pos), normal(nrml), uv(vtuv) {}

	Vertex_data() :
		position(cyPoint3f(0.0,0.0,0.0)), normal(cyPoint3f(0.0, 0.0, 0.0)), uv(cyPoint3f(0.0, 0.0, 0.0)) {}
};
