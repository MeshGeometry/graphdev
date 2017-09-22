#include "gtest/gtest.h"

#include "Core/Context.h"
#include "Core/Object.h"
#include "IO/File.h"
#include "IO/FileSystem.h"


using namespace Urho3D;

Context* ctx;
FileSystem* fs;

void Init()
{
	ctx = new Context();
	fs = new FileSystem(ctx);
	ctx->RegisterSubsystem(fs);
}

//ok some stuff
struct GraphItem : public RefCounted
{

public:
	// Construct
	GraphItem()
	{
	}

	/// Work function. Called with the work item and thread index (0 = main thread) as parameters.
	void(*workFunction_)(const Variant& in, Variant& out);

};

void Add_Test(const Variant& in, Variant& out)
{
	float a = in.GetFloat();
	out = a + a;
}


TEST(Base, GraphItem)
{
	if (!ctx) {
		Init();
	}

	GraphItem* gi = new GraphItem();
	gi->workFunction_ = Add_Test;
	Variant a = 5;
	Variant b = 6;
	Add_Test(a, b);
}
