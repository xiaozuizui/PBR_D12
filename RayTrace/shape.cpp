#include "shape.h"

Shape::Shape(XMFLOAT4X4 ObjectToWorld, XMFLOAT4X4 WorldToObject)
{
	this->ObjectToWorld = ObjectToWorld;
	this->WorldToObject = WorldToObject;

}

