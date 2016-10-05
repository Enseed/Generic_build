/*******************************************************************************
Copyright 2010 Enseed inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Author: Gaspard Petit
*******************************************************************************/
#ifndef __STATEMACHINE_IMPL_H__
#define __STATEMACHINE_IMPL_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "StateMachine.h"

BEGIN_GENERIC_NAMESPACE

//------------------------------------------------------------------------------
//
template<class T>
StateMachine<T>::StateMachine()
:
	_stateLevel(),
	_nextState()
{}

//------------------------------------------------------------------------------
//
template<class T>
void StateMachine<T>::execute()
{
	executeTransitionTo();
	while (!_transition.empty())
	{
		StateCb cb = _transition.front();
		_transition.pop_front();
		cb();
		executeTransitionTo();
	}

	if (_stateLevel.empty() || !_stateLevel.back()._state)
		return;

	StateCb cb = _stateLevel.back()._state;
	cb();

	executeTransitionTo();
	while (!_transition.empty())
	{
		StateCb cb = _transition.front();
		_transition.pop_front();
		cb();
		executeTransitionTo();
	}
}

//------------------------------------------------------------------------------
//
template<class T>
void StateMachine<T>::transitionTo(const char *aStateName, StateCb aEnterState, StateCb aState, StateCb aLeaveState)
{
	_transitionTo = StateLevel(aStateName, aEnterState, aState, aLeaveState);
}


//------------------------------------------------------------------------------
//
template<class T>
void StateMachine<T>::executeTransitionTo()
{
	if (_transitionTo.isValid())
	{
		if (_stateLevel.empty())
			return;

		if (_stateLevel.back()._stateLeave)
			_transition.push_back(_stateLevel.back()._stateLeave);

		if (_transitionTo._stateEnter)
			_transition.push_back(_transitionTo._stateEnter);

		_stateLevel.back() = _transitionTo;
		_transitionTo = StateLevel();
	}
}

//------------------------------------------------------------------------------
//
template<class T>
void StateMachine<T>::pushState(const char *aStateName, StateCb aEnterState, StateCb aState, StateCb aLeaveState)
{
	if (aEnterState)
		_transition.push_back(aEnterState);

	_stateLevel.push_back(StateLevel(aStateName, aEnterState, aState, aLeaveState));
}

//------------------------------------------------------------------------------
//
template<class T>
void StateMachine<T>::popState()
{
	if (_stateLevel.empty())
		return;

	if (_stateLevel.back()._stateLeave)
		_transition.push_back(_stateLevel.back()._stateLeave);

	_stateLevel.pop_back();
}

//------------------------------------------------------------------------------
//
template<class T>
const char* StateMachine<T>::state() const
{
	if (_stateLevel.empty())
		return nullptr;

	return _stateLevel.back()._stateName;
}

//------------------------------------------------------------------------------
//
template<class T>
StateMachine<T>::StateLevel::StateLevel(const char *aName, StateCb aEnterStateCb, StateCb aStateCb, StateCb aLeaveStateCb)
:
	_stateEnter(aEnterStateCb),
	_stateName(aName),
	_state(aStateCb),
	_stateLeave(aLeaveStateCb)
{}

//------------------------------------------------------------------------------
//
template<class T>
bool StateMachine<T>::StateLevel::operator == (const StateLevel &rhs)
{
	return _stateName == rhs._stateName;
}

//------------------------------------------------------------------------------
//
template<class T>
bool StateMachine<T>::StateLevel::operator != (const StateLevel &rhs)
{
	return !operator==(rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
StateMachine<T>::StateLevel::StateLevel(const StateLevel &rhs)
:
	_stateName(rhs._stateName),
	_stateEnter(rhs._stateEnter),
	_state(rhs._state),
	_stateLeave(rhs._stateLeave)
{}

//------------------------------------------------------------------------------
//
template<class T>
typename StateMachine<T>::StateLevel& StateMachine<T>::StateLevel::operator=(const StateLevel &rhs)
{
	_stateName = rhs._stateName;
	_stateEnter = rhs._stateEnter;
	_state = rhs._state;
	_stateLeave = rhs._stateLeave;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
StateMachine<T>::StateLevel::StateLevel()
:
	_stateName(nullptr),
	_stateEnter(StateCb()),
	_state(StateCb()),
	_stateLeave(StateCb())
{}

//------------------------------------------------------------------------------
//
template<class T>
bool StateMachine<T>::StateLevel::isValid()
{
	return !_state.empty();
}

END_GENERIC_NAMESPACE

#endif // __STATEMACHINE_IMPL_H__
