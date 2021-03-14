#pragma once
template <typename Max>
class SmartArray {
public:
	struct Element {
		size_t hash{};
		Max value{};
	};
	SmartArray() {}
	template <typename T>
	void push_back(T value) {
		if (typeid(value).hash_code() != typeid(Element).hash_code()) 
			vec.push_back(Element{ typeid(value).hash_code(), *(double*)&value });
		else
			vec.push_back(*(Element*)&value);
	}
	size_t type(int index) {
		return vec[index].hash;
	}
	template <typename T>
	T get(int index) {
		return *(T*)&vec[index].value;
	}
	size_t size() {
		return vec.size();
	}
	void reserve(size_t size) {
		vec.reserve(size);
	}

	template <typename T>
	T top() {
		return *(T*)&vec.back();
	}
	Element top() {
		return vec.back();
	}
	size_t top_type() {
		return vec.back().hash;
	}
	void pop() {
		vec.pop_back();
	}
	bool empty() {
		return vec.empty();
	}
	/*template <class Max>
	std::ostream& operator << (std::ostream& out, SmartArray<Max> ar) {
		for (int i = 0; i < ar.size(); i++) {
			std::cout << i << ' ';
			if (ar.type(i) == typeid(binary_operator).hash_code()) 
				std::cout << "bin op : " << (int)ar.get<binary_operator>(i) << std::endl;
			if (ar.type(i) == typeid(unary_operator).hash_code()) 
				std::cout << "un op : " << (int)ar.get<unary_operator>(i) << std::endl;
			if (ar.type(i) == typeid(double).hash_code()) 
				std::cout << "double : " << ar.get<double>(i) << std::endl;
			if (ar.type(i) == typeid(operators).hash_code()) 
				std::cout << "operators? : " << (int)ar.get<operators>(i) << std::endl;
		}
		return out;
	}*/
private:
	std::vector<Element> vec;
};

