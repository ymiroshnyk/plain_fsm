#include "parent.h"
#include "parent_states.h"

#include "events.h"

#include <iostream>

int main(int argc, char* argv[])
{
	Parent parent;

	for (int step = 0; step < 3; ++step)
	{
		parent.currentState().event((const Event&)EventUpdate());
		parent.currentState().event((const Event&)EventUpdate());
		parent.currentState().event((const Event&)EventUpdate());
	}

	return 0;
}
