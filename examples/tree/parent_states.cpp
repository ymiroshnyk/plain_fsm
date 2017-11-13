#include "parent_states.h"
#include "parent_state2_states.h"

namespace ParentStates
{

State2::State2()
{

	fsm_.reset(new Fsm(this));
}

State2::~State2()
{
	fsm_.reset();

}

bool State2::event(const Event& evt)
{
	if (!static_cast<State2States::State&>(fsm_->currentState()).event(evt))
		// don't forget to call own events
		return BaseState::event(evt);

	return true;
}

}
