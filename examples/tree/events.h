#pragma once

#include <typeinfo>

class Event
{
public:
	virtual ~Event() {} // to enable rtti

	template <typename T>
	bool isA() const
	{
		return typeid(T) == typeid(*this);
	}

	template <typename T>
	const T* tryCast() const
	{
		if (isA<T>())
			return static_cast<const T*>(this);
		else
			return nullptr;
	}
};

class EventUpdate : public Event {};

class EventMouse : public Event {};

class EventKeyboard : public Event {};
