#include "plain_fsm.h"

#include <iostream>

class Fsm
{
	class State : public PlainFsm::State
	{
	public:
		virtual void update() = 0;
	};

	class StateIdle : public State
	{
	public:
		StateIdle(int, int)
		{
			std::cout << "Idle" << std::endl;
		}

		~StateIdle()
		{
			std::cout << "~Idle" << std::endl;
		}

		virtual void update()
		{
			return transit<StateScan>(/*scan parameters*/ 0);
		}
	};

	class StateScan : public State
	{
	public:
		StateScan(int)
		{
			std::cout << "Scan" << std::endl;
		}

		~StateScan()
		{
			std::cout << "~Scan" << std::endl;
		}

		virtual void update()
		{
			return transit<StateMinimal>(/*minimal parameters*/);
		}
	};

	class StateMinimal : public State
	{
		virtual void update()
		{
			return transit<StateIdle>(/*idle parameters*/ 100, 200);
		}
	};

	// first state is default
	PlainFsm::StatesPool<StateIdle, StateScan, StateMinimal> states_;

public:
	// if default state has no arguments, you don't need this constructor at all
	Fsm()
	: states_(/* arguments of default state */200, 100)
	{
	}

	void update()
	{
		state().update();
	}

private:
	State& state()
	{
		return static_cast<State&>(states_.currentState());
	}
};

int main()
{
	Fsm fsm;

	fsm.update();
	fsm.update();
	fsm.update();
	fsm.update();

	return 0;
}