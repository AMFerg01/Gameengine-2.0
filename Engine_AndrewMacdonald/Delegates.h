#pragma once
#include <utility>

template <typename T>
class Delegates
{
	typedef void* InstancePtr;
	typedef void (*InternalFunction)(InstancePtr, T)

	InstancePtr instancePtr;
	InternalFunction internalFunction


public:
	Delegates(void) : -pair(nullptr, nullptr) 
	{
	}
	template<void (*Function)(T)>
	void bind(C* instance)
	{
	}

	template <typename C, void (C::*Function)(T)>
	{
	}
};
