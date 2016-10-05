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
#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <Enseed/Generic/Base/Base.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <deque>

//==============================================================================
//	NAMESPACE Generic
//==============================================================================
BEGIN_GENERIC_NAMESPACE

//==============================================================================
//	CLASS StateMachine
//------------------------------------------------------------------------------
//	Simple StateMachine definition for classes
//
//	Usage:
//
// 		class YourClass: public StateMachine<YourClass>
// 		{
// 		public:
// 			YourClass() {
// 				SEED_ENTER_STATE(YourClass, SomeState);
// 			}
// 
// 		private:
// 			SEED_MEMBER_STATE(SomeState) {
// 				if (conditionToGoToOtherStateIsMet) {
// 					SEED_TRANSITION_TO(YourClass, SomeOtherState);
// 				}
// 			}
// 					
// 			SEED_MEMBER_STATE(SomeOtherState) {
// 				if (conditionToGoToOtherStateIsMet) {
// 					SEED_TRANSITION_TO(YourClass, SomeState);
// 				}
// 			}
// 		};
// 
// 		YourClass myClass;
// 		myClass.execute();
//
//==============================================================================
template<class T>
class StateMachine
{
public:
	typedef boost::function<void()> StateCb;

public:
	//--------------------------------------------------------------------------
	//
	class StateLevel
	{
	public:
		//----------------------------------------------------------------------
		//
		StateLevel(const char *aName, StateCb aEnterStateCb, StateCb aStateCb, StateCb aLeaveStateCb);
		StateLevel(const StateLevel &rhs);
		StateLevel& operator=(const StateLevel &rhs);
		StateLevel();

		//----------------------------------------------------------------------
		//
		bool operator == (const StateLevel &rhs);
		bool operator != (const StateLevel &rhs);

		//----------------------------------------------------------------------
		//
		bool isValid();

	public:
		const char *_stateName;
		StateCb _stateEnter;
		StateCb _state;
		StateCb _stateLeave;
	};

public:
	//--------------------------------------------------------------------------
	//
	StateMachine();

	//----------------------------------------------------------------------
	//
	void execute();
	void transitionTo(const char *aStateName, StateCb aEnterState, StateCb aState, StateCb aLeaveState);
	void executeTransitionTo();
	void pushState(const char *aStateName, StateCb aEnterState, StateCb aState, StateCb aLeaveState);
	void popState();

	//----------------------------------------------------------------------
	//
	const char* state() const;
	bool running() const { return state() != nullptr; }

private:
	std::vector<StateLevel> _stateLevel;
	std::deque<StateCb> _transition;
	StateLevel _nextState;
	StateLevel _transitionTo;
};

#define SEED_ENTER_STATE(_CLASS, _NAME) this->pushState(#_CLASS "::" #_NAME, boost::bind(&_CLASS::Enter_##_NAME,this), boost::bind(&_CLASS::Execute_##_NAME, this), boost::bind(&_CLASS::Leave_##_NAME, this))
#define SEED_TRANSITION_TO(_CLASS, _NAME) this->transitionTo(#_CLASS "::" #_NAME, boost::bind(&_CLASS::Enter_##_NAME,this), boost::bind(&_CLASS::Execute_##_NAME, this), boost::bind(&_CLASS::Leave_##_NAME, this))
#define SEED_EXIT_STATE() this->popState()

#define SEED_DECLARE_STATE_ENTER(_NAME) void Enter_##_NAME()
#define SEED_DECLARE_STATE_RUN(_NAME) void Execute_##_NAME()
#define SEED_DECLARE_STATE_LEAVE(_NAME) void Leave_##_NAME()

#define SEED_DEFINE_STATE_ENTER(_CLASS, _NAME) void _CLASS::Enter_##_NAME()
#define SEED_DEFINE_STATE_RUN(_CLASS, _NAME) void _CLASS::Execute_##_NAME()
#define SEED_DEFINE_STATE_LEAVE(_CLASS, _NAME) void _CLASS::Leave_##_NAME()

#define SEED_DECLARE_STATE(_NAME) SEED_DECLARE_STATE_ENTER(_NAME); SEED_DECLARE_STATE_RUN(_NAME); SEED_DECLARE_STATE_LEAVE(_NAME)
#define SEED_DEFINE_STATE(_CLASS, _NAME) SEED_DEFINE_STATE_ENTER(_CLASS, _NAME){} SEED_DEFINE_STATE_LEAVE(_CLASS, _NAME){} SEED_DEFINE_STATE_RUN(_CLASS, _NAME)

#define SEED_MEMBER_STATE_ENTER(_NAME) void Enter_##_NAME()
#define SEED_STATE_ENTER(_CLASS, _NAME) void _CLASS::Enter_##_NAME()

#define SEED_MEMBER_STATE_RUN(_NAME) void Execute_##_NAME()
#define SEED_STATE_RUN(_CLASS, _NAME) void _CLASS::Execute_##_NAME()

#define SEED_MEMBER_STATE_LEAVE(_NAME) void Leave_##_NAME()
#define SEED_STATE_LEAVE(_CLASS, _NAME) void _CLASS::Leave_##_NAME()

#define SEED_MEMBER_STATE(_NAME) SEED_MEMBER_STATE_ENTER(_NAME){} SEED_MEMBER_STATE_LEAVE(_NAME){} SEED_MEMBER_STATE_RUN(_NAME)

#define SEED_STATE_NAME(_CLASS, _NAME) (std::string(#_CLASS "::" #_NAME))


END_GENERIC_NAMESPACE

#include "src/StateMachine.impl.h"

#endif // __STATEMACHINE_H__
