#include "StateMachine.hpp"

namespace BTL
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing; // = true

		this->_newState = std::move(newState); // std::move chuyển quyền sở hữu từ newState sang _newState
	}

	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		if (this->_isRemoving && !this->_states.empty()) // nếu _isRemoving = true và _states = false (k rỗng)
		{
			this->_states.pop(); // xóa ptu _states trên cùng của ngăn xếp là xóa ptu cuối

			if (!this->_states.empty()) // nếu k rỗng

			{
				this->_states.top()->Resume(); // lấy phần tử trên cùng của ngăn xếp là ptu cuối -> hàm ảo Resume
			}

			this->_isRemoving = false;
		}

		if (this->_isAdding) // nếu = true
		{
			if (!this->_states.empty()) // nếu k rỗng
			{
				if (this->_isReplacing) // nếu = true
				{
					this->_states.pop(); // xóa
				}
				else
				{
					this->_states.top()->Pause(); // ptu trên cùng -> hàm ảo Pause
				}
			}
			
			this->_states.push(std::move(this->_newState)); // vì đây là 1 TH đặc biệt nên k thể push vào bth đc nên phải có std::move mới bỏ nó vào _state đc
			this->_states.top()->Init(); // sau đó lấy ptu trên cùng lúc này là _newState -> hàm thuần ảo Init
			this->_isAdding = false; // đặt _isAdding lại thành false
		}
	}

	StateRef &StateMachine::GetActiveState()
	{
		return this->_states.top(); // trả về ptu cuối cùng
	}
}