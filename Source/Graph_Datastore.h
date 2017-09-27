#pragma once
#include "Core/Context.h"
#include "Core/Object.h"
#include "Core/Variant.h"

class URHO3D_API Graph_Datastore : Urho3D::Object
{
	URHO3D_OBJECT(Graph_Datastore, Object)

public:
	Graph_Datastore(Urho3D::Context* context) : Object(context) {};
	~Graph_Datastore() {};

	///Gets data from the storage
	float GetFloat(Urho3D::StringHash key, float& value);

	///Sets data to the storage
	void SetDataItem(Urho3D::StringHash key, const Urho3D::Variant& value);

private:

	Urho3D::VariantMap dataTable_;
};