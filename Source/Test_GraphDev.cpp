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

//a link is hyper edge with a function
struct GraphLink
{
	GraphLink() {};

	Vector<String> sources_;
	Vector<String> targets_;

	void(*function_)(const VariantVector& inputs, VariantVector& outputs);
};

//graph def
class GraphEngine : public Object
{
	URHO3D_OBJECT(GraphEngine, Object);

public:
	GraphEngine(Context* context) : Object(context) {};
	~GraphEngine() {};

	HashMap<String, Variant> graphValues_;
	HashMap<String, GraphLink> graphLinks_;

	void AddValue(String uniqueName, Variant value)
	{
		graphValues_[uniqueName] = value;
	}

	void Solve()
	{
		//for now, forget about ordering the solve
		HashMap<String, GraphLink>::ConstIterator itr;
		for (itr = graphLinks_.Begin(); itr != graphLinks_.End(); itr++)
		{
			//collect the inputs
			VariantVector inputs;
			for (int i = 0; i < itr->second_.sources_.Size(); i++)
			{
				Variant currentInput = graphValues_[itr->second_.sources_[i]];
				inputs.Push(currentInput);
			}

			//collect the outputs
			VariantVector outputs;
			for (int i = 0; i < itr->second_.targets_.Size(); i++)
			{
				Variant targetOutput = graphValues_[itr->second_.targets_[i]];
				outputs.Push(targetOutput);
			}

			//call the work functions
			itr->second_.function_(inputs, outputs);

			//propagate the results
			int size = Min(itr->second_.targets_.Size(), outputs.Size());
			for (int i = 0; i < size; i++)
			{
				Variant targetOutput = outputs[i];
				graphValues_[itr->second_.targets_[i]] = targetOutput;				
			}

			//done?
		}
	}

};

//special signature function
void Adder(const VariantVector& in, VariantVector& out)
{
	float a = 0.0;
	for (int i = 0; i < in.Size(); i++)
	{
		a += in[i].GetFloat();
	}

	out[0] = a;
}

TEST(Base, Graph)
{
	if (!ctx) {
		Init();
	}

	GraphEngine* ge = new GraphEngine(ctx);

	//add some values
	ge->AddValue("A", 1.0f);
	ge->AddValue("B", 2.0f);
	ge->AddValue("C", 0.0f);

	//add a link
	GraphLink gl;
	gl.sources_.Push("A");
	gl.sources_.Push("B");
	gl.targets_.Push("C");
	gl.function_ = Adder;
	ge->graphLinks_["AdderLink"] = gl;

	//solve
	ge->Solve();

	float result = ge->graphValues_["C"].GetFloat();
	EXPECT_EQ(result, 3.0f);
}
