#pragma once
#include "Core/Context.h"
#include "Core/Object.h"
#include <functional>

/// Template implementation of the event handler invoke helper (std::function instance).
class Graph_Function : public Urho3D::RefCounted
{
public:
	typedef typename std::function<void(const Urho3D::VariantVector& inputs, Urho3D::VariantVector& outputs)> Graph_FunctionType;

	/// Construct with receiver and function pointers and userdata.
	Graph_Function(Graph_FunctionType function, int numInputs, int numOutputs, bool modifiable, void* userData = 0) :
		RefCounted(),
		function_(function),
		userData_(userData),
		numInputs_(numInputs),
		numOutputs_(numOutputs),
		isModifiable_(modifiable)
	{
		assert(function_);
	}

	/// Invoke event handler function.
	virtual void Invoke(const Urho3D::VariantVector& inputs, Urho3D::VariantVector& outputs)
	{
		function_(inputs, outputs);
	}

	/// Return a unique copy of the event handler.
	virtual Graph_Function* Clone() const
	{
		return new Graph_Function(function_, numInputs_, numOutputs_, isModifiable_, userData_);
	}

private:
	/// Class-specific pointer to handler function.
	std::function<void(const Urho3D::VariantVector& inputs, Urho3D::VariantVector& outputs)> function_;
	///container for user data
	void* userData_;
	///some stuff
	int numInputs_;
	int numOutputs_;
	bool isModifiable_;
};

/// Convenience macro to construct an EventHandler that points to a receiver object and its member function.
#define CREATE_GRAPH_FUNCTION(function, instance, numInputs, numOutputs)(new Graph_Function(std::bind(&function, &instance, std::placeholders::_1, std::placeholders::_2), numInputs, numOutputs, false));