#ifndef __FSM__
#define __FSM__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class FSM :public cocos2d::Ref
{

private:
	set<string> _states;

	//第一个参数是states，第二个参数是函数
	unordered_map<string, unordered_map<string, string>> _events;


	string _currentState;
	string _previousState;
	unordered_map<string, function<void()>> _onEnter;

public:
	//初始化
	bool init();
	static FSM* create(string state, function<void()> onEnter = nullptr);
	FSM(string state, function<void()> onEnter = nullptr);


	FSM* addState(string state, function<void()> onEnter = nullptr);

	FSM* addEvent(string eventName, string from, string to);

	bool isContainState(string stateName);

	void printState();

	void doEvent(string eventName);

	bool canDoEvent(string eventName);

	void setOnEnter(string state, function<void()> onEnter);

private:
	void changeToState(string state);


};


#endif