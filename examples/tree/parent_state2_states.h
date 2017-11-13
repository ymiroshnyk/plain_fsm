#pragma once

#include "base_state.h"

#include "plain_fsm.h"

#include <memory>

namespace ParentStates
{
class State2;

namespace State2States
{

class State : public BaseState<ParentStates::State2*>
{
public:
	virtual bool eventSpecificToState2() {}
};

class StateDefault;
class State1;
class State2;

class StateDefault : public State
{
public:
	bool event(const EventUpdate&) override
	{
		return transit<State1>();
	}
};

class State1 : public State
{
public:
	bool event(const EventUpdate&) override
	{
		return transit<State2>();
	}
};

class State2 : public State
{
public:
	bool event(const EventUpdate&) override
	{
		return transit<StateDefault>();
	}
};

}
}
