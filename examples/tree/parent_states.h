#pragma once

#include "base_state.h"

#include "plain_fsm.h"

#include <memory>

class Parent;

namespace ParentStates
{

// Base state for all Parent states
class State : public BaseState<Parent*>
{
public:
	virtual bool eventParentSpecific() {}
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

namespace State2States
{
class StateDefault;
class State1;
class State2;
}

class State2 : public State
{
	typedef PlainFsm::FsmWithContext<
			State2*,
			State2States::StateDefault,
			State2States::State1,
			State2States::State2
			> Fsm;
	std::unique_ptr<Fsm> fsm_;

public:
	State2();
	~State2();

	bool event(const EventUpdate&) override
	{
		return transit<StateDefault>();
	}

	// redirection to child fsm
	bool event(const Event& evt) override;
};
}
