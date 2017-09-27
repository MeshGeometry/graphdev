#include "Core/Context.h"
#include "Core/Object.h"
#include "Core/Variant.h"

#include "Graph_Function.h"

class URHO3D_API Graph_Engine : Urho3D::Object
{
	URHO3D_OBJECT(Graph_Engine, Object)

public:
	Graph_Engine(Urho3D::Context* context) : Object(context) {};
	~Graph_Engine() {};

	void Solve();

	void AddFunction(Graph_Function* function) { graphFunctions_.Push(function); };

private:

	Urho3D::Vector<Graph_Function*> graphFunctions_;

};