#include "gtest/gtest.h"

#include "Core/Context.h"
#include "Core/Object.h"
#include "IO/File.h"
#include "IO/FileSystem.h"

#include "Graph_Engine.h"
#include "Graph_Datastore.h"
#include "Graph_Function.h"

#include "Math_System.h"

using namespace Urho3D;

Context* ctx;
FileSystem* fs;

void Init()
{
	ctx = new Context();
	fs = new FileSystem(ctx);
	ctx->RegisterSubsystem(fs);
}


TEST(Base, Graph)
{
	if (!ctx) {
		Init();
	}

	//required graph systems
	Graph_Engine* ge = new Graph_Engine(ctx);
	//Graph_Datastore* ds = new Graph_Datastore(ctx);
	
	//additional system
	Math_System* ms = new Math_System(ctx);

	//register some functions
	Graph_Function* add = CREATE_GRAPH_FUNCTION(Math_System::Add, *ms, 2, 1);
	Graph_Function* mult = CREATE_GRAPH_FUNCTION(Math_System::Multiply, *ms, 2, 1);
	ge->RegisterFunction("Add", add);
	ge->RegisterFunction("Multiply", mult);

	//add some data fields
	ge->AddData("A", 1.0f);
	ge->AddData("B", 2.0f);
	ge->AddData("C", 0.0f);

	//add link with A and B as sources, and C as target.
	//specify that the relationship is defined by Add
	Graph_Link link(add, "A", "B", "C");
	ge->AddLink(link);

	//solve
	ge->Solve();

	//verify
	Variant value;
	ge->GetData("C", value);
	float res = value.GetFloat();
	EXPECT_EQ(res, 3.0f);

}
