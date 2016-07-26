#include "FSM.h"


FSM::FSM(string state, function<void()> onEnter)
{
	_currentState = state;
	_previousState = "";
	this->addState(state, onEnter);
}


FSM* FSM::addState(string state, function<void()> onEnter)
{
	//防御式编程，state不能为空字符串
	if ("" == state)
	{
		cocos2d::log("FSM::addState: state can't be empty string!");
		return nullptr;
	}
	//保存变量的值
	_states.insert(state);
	_onEnter.insert(pair<string, function<void()>>(state, onEnter));
	return this;
}


FSM* FSM::create(string state, function<void()> onEnter)
{
	FSM* fsm = new FSM(state, onEnter);
	if (fsm && fsm->init())
	{
		fsm->autorelease();
		return fsm;
	}
	else
	{
		CC_SAFE_DELETE(fsm);
		return nullptr;
	}
}


//查看state是否包含
bool FSM::isContainState(std::string stateName)
{
	return _states.find(stateName) != _states.end();
}


//打印当前的所有状态
void FSM::printState()
{
	//	std::for_each(_states.begin(), _states.end(), &FSM::print);
	cocos2d::log("FSM::printState: list of states");
	for (auto iter = _states.begin(); iter != _states.end(); iter++)
	{
		cocos2d::log(iter->c_str());
	}
}

void FSM::changeToState(std::string state)
{
	//如果states在列表当中
	if (isContainState(state))
	{
		_previousState = _currentState;
		_currentState = state;
		cocos2d::log("FSM::changeToState: %s -> %s", _previousState.c_str(), _currentState.c_str());
		
		//如果有函数就执行
		if (_onEnter[state])
			_onEnter[state]();
	}
	//state是否在列表当中
	else
	{
		cocos2d::log("FSM::changeToState: no such state as %s , state unchanged", state.c_str());
	}
}

FSM* FSM::addEvent(std::string eventName, std::string from, std::string to)
{
	if ("" == eventName)
	{
		cocos2d::log("FSM::addEvent: eventName can't be empty!");
		return nullptr;
	}
	if (!isContainState(from))
	{
		cocos2d::log("FSM::addEvent: from state %s does not exit", from.c_str());
		return nullptr;
	}
	if (!isContainState(to))
	{
		cocos2d::log("FSM::addEvent: to state %s does not exit", to.c_str());
		return nullptr;
	}
	std::unordered_map<std::string, std::string>& oneEvent = _events[eventName];
	oneEvent[from] = to;
	return this;
}

bool FSM::canDoEvent(std::string eventName)
{
	return _events[eventName].find(_currentState) != _events[eventName].end();
}

void FSM::doEvent(std::string eventName)
{
	if (canDoEvent(eventName))
	{
		cocos2d::log("FSM::doEvent: doing event %s", eventName.c_str());
		changeToState(_events[eventName][_currentState]);
	}
	else
	{
		cocos2d::log("FSM::doEvent: cannot do event %s", eventName.c_str());
	}
}

void FSM::setOnEnter(std::string state, std::function<void()> onEnter)
{
	if (isContainState(state))
	{
		_onEnter[state] = onEnter;
	}
	else
	{
		cocos2d::log("FSM::setOnEnter: no state named %s", state.c_str());
	}
}

bool FSM::init()
{
	this->addState("walking", []() {cocos2d::log("Enter walking"); })
		->addState("attacking", []() {cocos2d::log("Enter attacking"); })
		->addState("dead", []() {cocos2d::log("Enter dead"); });

	this->addEvent("walk", "idle", "walking")
		->addEvent("walk", "attacking", "walking")
		->addEvent("attack", "idle", "attacking")
		->addEvent("attack", "walking", "attacking")
		->addEvent("die", "idle", "dead")
		->addEvent("die", "walking", "dead")
		->addEvent("die", "attacking", "dead")
		->addEvent("stop", "walking", "idle")
		->addEvent("stop", "attacking", "idle")
		->addEvent("walk", "walking", "walking");

	//this->doEvent("walk");
	//this->doEvent("attack");
	//this->doEvent("stop");
	//this->doEvent("die");
	//this->doEvent("walk");
	//this->doEvent("eat");

	//this->changeToState("eating");
	//this->changeToState("idle");
	//this->changeToState("walking");
	//this->changeToState("dead");
	//this->printState();
	return true;
}
