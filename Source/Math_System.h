#pragma once
#include "Core/Context.h"
#include "Core/Object.h"

class URHO3D_API Math_System : Urho3D::Object
{
	URHO3D_OBJECT(Math_System, Object)

public:

	Math_System(Urho3D::Context* context);
	~Math_System() {};

	//define some math functions
	void Add(const Urho3D::VariantVector& in, Urho3D::VariantVector& out);
	void Multiply(const Urho3D::VariantVector& in, Urho3D::VariantVector& out);

};