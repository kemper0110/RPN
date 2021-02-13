#pragma once
#ifndef MY_LIST
#define MY_LIST
namespace dl {
	template <class T>
	class list {
	public:
		list() {

		}
		T back();
		//void erase(T* begin, T* end);
		void remove(T value);
		void front();
		void push_back();
		void push_front();
		void pop_back();
		void pop_front();

		bool empty() {
			return !(int)_size;
		}
		size_t size() {
			return _size;
		}
	private:
		size_t _size = 0;
	};
}


#endif // !MY_LIST
