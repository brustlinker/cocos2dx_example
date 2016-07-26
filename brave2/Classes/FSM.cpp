#include "FSM.h"

namespace fsm
{
	void FSM::addState(State state)
	{
		_states.push_back(state);
	}
	

	void FSM::printState()
	{
		//遍历
		for (auto iter = _states.begin(); iter != _states.end(); iter++)
		{
			cocos2d::log(iter->name.c_str());
		}
	}

	bool FSM::init()
	{
		this->addState(State("sth"));
		this->printState();
		return true;
	}
};