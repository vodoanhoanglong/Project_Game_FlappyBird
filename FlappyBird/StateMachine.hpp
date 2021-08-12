#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace BTL
{
	//Sử dụng unique_ptr khi bạn muốn có một quyền sở hữu duy nhất(Độc quyền) đối với tài nguyên.
    //Chỉ một unique_ptr có thể trỏ đến một tài nguyên.Vì có thể có một unique_ptr cho một tài nguyên nên không thể sao chép một unique_ptr này sang một tài nguyên khác.
	typedef std::unique_ptr<State> StateRef; // định nghĩa lại class unique_ptr<State> thành StateRef
	class StateMachine
	{
	public:
		StateMachine() { }
		~StateMachine() { }

		void AddState(StateRef newState, bool isReplacing = true); // newState là 1 biến chứa con trỏ, trỏ tới vùng nhớ của State
		void RemoveState();
		// Chạy khi bắt đầu mỗi vòng lặp trong Game.cpp
		void ProcessStateChanges();

		StateRef &GetActiveState();

	private:
		std::stack<StateRef> _states;
		StateRef _newState; 

		bool _isRemoving;
		bool _isAdding, _isReplacing;
	};
}