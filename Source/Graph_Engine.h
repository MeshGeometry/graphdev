#pragma once
#include "Core/Context.h"
#include "Core/Object.h"
#include "Core/Variant.h"

#include "Graph_Function.h"

using Urho3D::String;
using Urho3D::Vector;
using Urho3D::Variant;
using Urho3D::SharedPtr;

struct Graph_Link
{
	Graph_Function* function_;
	Urho3D::Vector<String> sources_;
	Urho3D::Vector<String> targets_;
	
	Graph_Link() {};

	Graph_Link(Graph_Function* f, Urho3D::Vector<String> sources, Urho3D::Vector<String> targets)
	{
		function_ = f;
		sources_ = sources;
		targets_ = targets_;
	}

	Graph_Link(Graph_Function* f, Urho3D::String source, Urho3D::String target)
	{
		function_ = f;
		sources_.Push(source);
		targets_.Push(target);
	}

	Graph_Link(Graph_Function* f, Urho3D::String sourceA, Urho3D::String sourceB, Urho3D::String target)
	{
		function_ = f;
		sources_.Push(sourceA);
		sources_.Push(sourceB);
		targets_.Push(target);
	}
};

class URHO3D_API Graph_Engine : Urho3D::Object
{
	URHO3D_OBJECT(Graph_Engine, Object)

public:
	Graph_Engine(Urho3D::Context* context) : Object(context) {};
	~Graph_Engine() {};

	void Solve();

	bool RegisterFunction(String name, Graph_Function* function);
	void AddLink(Graph_Link link);
	void AddData(String name, Variant value);
	void GetData(String name, Variant& value);

private:

	Urho3D::HashMap<String, Graph_Function*> graphFunctions_;
	Urho3D::Vector<Graph_Link> graphLinks_;
	Urho3D::VariantMap graphData_;

};