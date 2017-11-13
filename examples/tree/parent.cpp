#include "parent.h"
#include "parent_states.h"

Parent::Parent()
{
	// parent initialization

	fsm_.reset(new Fsm(this));
}

Parent::~Parent()
{
	fsm_.reset();

	// parent deinitialization
}

ParentStates::State& Parent::currentState()
{
	return static_cast<ParentStates::State&>(fsm_->currentState());
}
