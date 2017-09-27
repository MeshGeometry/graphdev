#pragma once
#include "Core/Context.h"
#include "Core/Object.h"
#include <functional>

class Graph_Function : public Urho3D::RefCounted
{
public:
	typedef typename std::function<void(const Urho3D::VariantVector& inputs, Urho3D::VariantVector& outputs)> Graph_FunctionType;

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

	virtual void Invoke(const Urho3D::VariantVector& inputs, Urho3D::VariantVector& outputs)
	{
		function_(inputs, outputs);
	}

	virtual Graph_Function* Clone() const
	{
		return new Graph_Function(function_, numInputs_, numOutputs_, isModifiable_, userData_);
	}

	int GetNumInputs() { return numInputs_; };
	int GetNumOutputs() { return numOutputs_; };

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

/// Convenience macro
#define CREATE_GRAPH_FUNCTION(function, instance, numInputs, numOutputs)(new Graph_Function(std::bind(&function, &instance, std::placeholders::_1, std::placeholders::_2), numInputs, numOutputs, false));