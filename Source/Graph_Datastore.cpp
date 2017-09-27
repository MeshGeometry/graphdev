#include "Graph_Datastore.h"
#include "IO/Log.h"

using namespace Urho3D;

///Gets data from the storage
float Graph_Datastore::GetFloat(Urho3D::StringHash key, float& value)
{
	//always return something
	value = 0.0f;

	//safely get the data
	Variant tmpVal;
	if (dataTable_.TryGetValue(key, tmpVal))
	{
		if (tmpVal.GetType() == VAR_FLOAT)
		{
			value = tmpVal.GetFloat();
		}
	}

	//return
	return value;
}

///Sets data to the storage
void Graph_Datastore::SetDataItem(Urho3D::StringHash key, const Urho3D::Variant& value)
{
	if (dataTable_.Keys().Contains(key))
	{
		URHO3D_LOGINFO("Data table already contains key: " + key.ToString() + ". Overwriting....");
	}

	dataTable_[key] = value;
}