#include "Math_System.h"

using namespace Urho3D;

Math_System::Math_System(Urho3D::Context* context) : Object(context)
{

}

void Math_System::Add(const Urho3D::VariantVector& in, Urho3D::VariantVector& out)
{
	assert(in.Size() == 2);
	assert(out.Size() == 1);

	//just deal with float for now
	out[0] = in[0].GetFloat() + in[1].GetFloat();
}

void Math_System::Multiply(const Urho3D::VariantVector& in, Urho3D::VariantVector& out)
{
	assert(in.Size() == 2);
	assert(out.Size() == 1);

	//just deal with float for now
	out[0] = in[0].GetFloat() * in[1].GetFloat();
}