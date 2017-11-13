#pragma once

#include <utility>

namespace PlainFsm
{

namespace Utils
{
	template <typename... Args> struct MaxSize;

	template <typename T, typename... Args>
	struct MaxSize < T, Args... >
	{
		enum { value = sizeof(T) > MaxSize<Args...>::value ? sizeof(T) : MaxSize<Args...>::value };
	};

	template <typename T>
	struct MaxSize < T >
	{
		enum { value = sizeof(T) };
	};

	template <typename T, typename... Args>
	struct FirstArg
	{
		typedef T value;
	};

	template <typename TContext>
	struct ContextSize
	{
		static const int value = (sizeof(TContext) / sizeof(void*) + 1) * sizeof(void*); // alignment to pointer size
	};
}

class State
{
public:
	virtual ~State() {}

	template <typename TState, typename... Args>
	bool transit(Args... args)
	{
		this->~State();
		new (this) TState(args...);
		return true;
	}
};

template <typename TContext>
class StateWithContext
{
protected:
	TContext& ctx;

	StateWithContext()
		: ctx(*reinterpret_cast<TContext*>(reinterpret_cast<char*>(reinterpret_cast<void*>(this))
		- Utils::ContextSize<TContext>::value))
	{
	}

public:
	virtual ~StateWithContext() {}

	template <typename TState, typename... Args>
	bool transit(Args... args)
	{
		this->~StateWithContext();
		new (this) TState(args...);
		return true;
	}
};

template <typename... TStates>
class Fsm
{
	char state_[Utils::MaxSize<TStates...>::value];

public:

	template <typename... Args>
	Fsm(Args... args)
	{
		new (&currentState()) typename Utils::FirstArg<TStates...>::value(args...);
	}

	~Fsm()
	{
		currentState().~State();
	}

	State& currentState()
	{
		return *reinterpret_cast<State*>(state_);
	}

	const State& currentState() const
	{
		return *reinterpret_cast<const State*>(state_);
	}
};

template <typename TContext, typename... TStates>
class FsmWithContext
{
	char state_[Utils::ContextSize<TContext>::value + Utils::MaxSize<TStates...>::value];

public:

	template <typename... Args>
	FsmWithContext(const TContext& context, Args... args)
	{
		new (state_) TContext(context);
		new (&currentState()) typename Utils::FirstArg<TStates...>::value(args...);
	}

	template <typename... Args>
	FsmWithContext(TContext&& context, Args... args)
	{
		new (state_) TContext(std::move(context));
		new (&currentState()) typename Utils::FirstArg<TStates...>::value(args...);
	}

	~FsmWithContext()
	{
		currentState().~StateWithContext<TContext>();
		reinterpret_cast<TContext*>(state_)->~TContext();
	}

	StateWithContext<TContext>& currentState()
	{
		return *reinterpret_cast<StateWithContext<TContext>*>(state_ + Utils::ContextSize<TContext>::value);
	}

	const StateWithContext<TContext>& currentState() const
	{
		return *reinterpret_cast<const StateWithContext<TContext>*>(state_ + Utils::ContextSize<TContext>::value);
	}
};

}
