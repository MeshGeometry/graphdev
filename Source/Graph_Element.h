#pragma once
#include "Graph_Function.h"
#include "Graph_Engine.h"
#include "Core/Object.h"
#include "Core/Context.h"

using Urho3D::Variant;
using Urho3D::VariantMap;
using Urho3D::VariantVector;
using Urho3D::String;

//Graph elements are classes that interact with data fields or functions.
//Usually, they consist of some kind of UI, for example a slider that directly sets the value of a data field.
//Another example is a bar chart that receives some numbers (from a data field) and renders them.

//The mechanism to interact with the graph engine (and properties thereof), is done here by event sending/handling.
//This approach is very robust and, fortunately for us, well implemented by Urho. Other platforms might require something else.
//The main advantage is that no actual reference to the graph engine, or function, or data field is needed.

//Base class
//This would inherit from app level UIElement and probably implement some basic visual styles.
//All that is omitted here.
class Graph_Element : public Urho3D::Object
{
public:
	Graph_Element(Urho3D::Context* context) : Object(context) {};
	~Graph_Element() {};
};

//a slider class (ignoring any actual ui code).
class MySlider : public Graph_Element
{
public:
	MySlider(Urho3D::Context* context) : Graph_Element(context),
		myValue_(0.0f)
	{
	};

	~MySlider() {};
	
	void SetValue(float value)
	{
		//In actual use, this would set the position of a screen element or something.
		myValue_ = value;

		//update the data field by event
		VariantMap data;
		data["TargetField"] = target_;
		SendEvent("SetDataField", data);
	}

private:
	float myValue_;
	Urho3D::String target_;
};

//A plot (as in F(x)) class. Here, the class renders something on screen AND has a function that is bound to the engine.
class MyPlot : public Graph_Element
{
public:
	MyPlot(Urho3D::Context* context) : Graph_Element(context),
		power_(2.0f)
	{
	};

	~MyPlot() {};

	//a function that grabs a value from a ui element and stores it.
	void SetPower(float power)
	{
		power_ = power;
	}

	//the function we want to expose to the graph engine
	void Plot(const VariantVector& in, VariantVector& out)
	{
		out[0] = Urho3D::Pow(in[0].GetFloat(), power_);
	}

private:
	float power_;

};