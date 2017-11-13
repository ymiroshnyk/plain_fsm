#pragma once

#include "plain_fsm.h"
#include <memory>

namespace ParentStates
{
	class State;
	class StateDefault;
	class State1;
	class State2;
}

class Parent
{
	typedef PlainFsm::FsmWithContext<
			Parent*, // context
			ParentStates::StateDefault, // default state
			ParentStates::State1,
			ParentStates::State2> Fsm;

	std::unique_ptr<Fsm> fsm_;

public:
	Parent();
	~Parent();

	ParentStates::State& currentState();
};
