#include "Graph_Engine.h"
#include <functional>

using namespace Urho3D;

bool Graph_Engine::RegisterFunction(String name, Graph_Function* function)
{
	assert(function);

	graphsFunctions_[name] = function;

	return true;
}

void Graph_Engine::AddLink(Graph_Link link)
{
	graphLinks_.Push(link);
}

void Graph_Engine::AddData(String name, Variant value)
{
	graphData_[name] = value;
}

void Graph_Engine::Solve()
{
	//TODO: order the links according to graph connectivity
	//for now, just solve in default order
	for (int i = 0; i < graphLinks_.Size(); i++)
	{
		Graph_Link link = graphLinks_[i];

		//create inputs
		VariantVector in;
		in.Resize(link.function_->GetNumInputs());
		int counter = Min(link.function_->GetNumInputs(), link.sources_.Size());
		for (int j = 0; j < counter; j++)
		{
			Variant value;
			graphData_.TryGetValue(link.sources_[j], value);
			in[j] =value;
		}

		//create outputs
		//not sure about this: do we need the values?
		VariantVector out;
		out.Resize(link.function_->GetNumOutputs());
		counter = Min(link.function_->GetNumOutputs(), link.targets_.Size());
		for (int j = 0; j < counter; j++)
		{
			Variant value;
			graphData_.TryGetValue(link.targets_[j], value);
			out[j] = value;
		}

		//call the function
		link.function_->Invoke(in, out);

		//set the output data
		//this copies the data. Probably not optimal
		for (int j = 0; j < link.targets_.Size(); j++)
		{
			graphData_[link.targets_[j]] = out[j];
		}

		//done?
	}
}

void Graph_Engine::GetData(String name, Variant& value)
{
	graphData_.TryGetValue(name, value);
}
