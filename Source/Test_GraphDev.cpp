#include "gtest/gtest.h"

#include "Core/Context.h"
#include "Core/Object.h"
#include "IO/File.h"
#include "IO/FileSystem.h"

#include <functional>

using namespace Urho3D;

Context* ctx;
FileSystem* fs;

void Init()
{
	ctx = new Context();
	fs = new FileSystem(ctx);
	ctx->RegisterSubsystem(fs);
}



/// Template implementation of the event handler invoke helper (std::function instance).
class GraphFunction : public RefCounted
{
public:
	typedef typename std::function<void(const VariantVector& inputs, VariantVector& outputs)> GraphFunctionType;

	/// Construct with receiver and function pointers and userdata.
	GraphFunction(GraphFunctionType function, void* userData = 0) :
		RefCounted(),
		function_(function),
		userData_(userData)
	{
		assert(function_);
	}

	/// Invoke event handler function.
	virtual void Invoke(const VariantVector& inputs, VariantVector& outputs)
	{
		function_(inputs, outputs);
	}

	/// Return a unique copy of the event handler.
	virtual GraphFunction* Clone() const
	{
		return new GraphFunction(function_, userData_);
	}

private:
	/// Class-specific pointer to handler function.
	std::function<void(const VariantVector& inputs, VariantVector& outputs)> function_;
	///container for user data
	void* userData_;
};




//a link is hyper edge with a function
struct GraphLink
{
	GraphLink() {};

	Vector<String> sources_;
	Vector<String> targets_;
};

//graph def
class  GraphEngine : public Object
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

class MyClassA
{
public:
	MyClassA() 
	{
	};

	//special signature function
	void Multiplier(const VariantVector& in, VariantVector& out)
	{
		float a = 1.0;
		for (int i = 0; i < in.Size(); i++)
		{
			a += in[i].GetFloat();
		}

		out[0] = a;
	}
};
/// Convenience macro to construct an EventHandler that points to a receiver object and its member function.
#define CREATE_GRAPH_FUNCTION(function, instance)(new GraphFunction(std::bind(&function, &instance, std::placeholders::_1, std::placeholders::_2)));

TEST(Base, Graph)
{
	if (!ctx) {
		Init();
	}

	VariantVector in;
	VariantVector out;

	GraphEngine* ge = new GraphEngine(ctx);
	MyClassA mca;
	//auto fp = std::bind(&MyClassA::Multiplier, &mca, std::placeholders::_1, std::placeholders::_2);
	GraphFunction* gf = CREATE_GRAPH_FUNCTION(MyClassA::Multiplier, mca);

	gf->Invoke(in, out);


}
