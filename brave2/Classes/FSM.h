
#ifndef __FSM__
#define __FSM__

#include "cocos2d.h"

using namespace std;


namespace fsm
{
	class Event
	{
		public:
			string name;
			string from;
			string to;
			Event(string name, string from, string to)
			{
				this->name = name;
				this->from = from;
				this->to = to;
			}
	};

	class State
	{
		public:
			string name;
			function<void()> onEnter;
			function<void()> onExit;
			State(string name)
				{
					this->name = name;
					this->onEnter = []() {};
					this->onExit = []() {};
				}
	};

	class FSM :public cocos2d::Ref
	{
		public:
			bool init();
			CREATE_FUNC(FSM);
			
			FSM() {}
			void addState(State state);
			void printState();
		private:
			vector<State> _states;
			vector<Event> _events;
	};
};


#endif