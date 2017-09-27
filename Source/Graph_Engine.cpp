#include "Graph_Engine.h"

using namespace Urho3D;


void Graph_Engine::Solve()
{
	//TODO: order the links according to graph connectivity
	//for now, just solve in default order
	for (int i = 0; i < graphLinks_.Size(); i++)
	{
		Graph_Link link = graphLinks_[i];

		//create inputs
		VariantVector in;
		for (int j = 0; j < link.sources_.Size(); j++)
		{
			Variant value;
			graphData_.TryGetValue(link.sources_[j], value);
			in.Push(value);
		}

		//create outputs
		//not sure about this: do we need the value?
		VariantVector out;
		for (int j = 0; j < link.targets_.Size(); j++)
		{
			Variant value;
			graphData_.TryGetValue(link.targets_[j], value);
			out.Push(value);
		}

		//call the function
		link.function_->Invoke(in, out);

		//set the output data
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
