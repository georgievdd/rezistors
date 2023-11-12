#pragma once
#include <iostream>

namespace gdd_list {
	template <typename type>
	class __list {
	public:
		__list<type>* link_next;
		__list<type>* link_previous;
		type value;
		__list() {}
		__list(type, __list*, __list*);
		void clear();
	};

	template <typename type>
	class _list {
	public:
		__list<type>* link_begin;
		__list<type>* link_end;
		unsigned len;

		void print_error(int, int, const char*);
		_list();
		_list(type);
		~_list();

		type& operator[](int);

		void append();
		void append(type);
		void append(unsigned, type);

		void clear();
		void clear(unsigned);

		void print();
		void print(char, char);
		unsigned length();

		bool contains(type);
	};

#define ERROR_1 1
#define ERROR_2 2

}

typedef gdd_list::_list<int> Int_list;
typedef gdd_list::_list<char> Char_list;
typedef gdd_list::_list<float> Float_list;
typedef gdd_list::_list<double> Double_list;
typedef gdd_list::_list<long> Long_list;
typedef gdd_list::_list<long double> Long_Double_list;
typedef gdd_list::_list<long long> Long_Long_list;
typedef gdd_list::_list<unsigned> Unsigned_Int_list;














template <typename type>
gdd_list::__list<type>::__list(type value, __list* link_previous, __list* link_next) {
	this->value = value;
	this->link_previous = link_previous;
	this->link_next = link_next;
}
template <typename type>
inline void gdd_list::__list<type>::clear() {
	delete this;
}
//голова
template <typename type>
gdd_list::_list<type>::_list() {
	this->link_begin = nullptr;
	this->link_end = nullptr;
	this->len = 0;
}
template <typename type>
gdd_list::_list<type>::_list(type value) {
	this->link_begin = this->link_end = new __list<type>(value, nullptr, nullptr);
	this->len = 1;
}
template <typename type>
gdd_list::_list<type>::~_list() {
	__list<type>* ptr = this->link_end;
	if (ptr == nullptr) return;
	__list<type>* loc_ptr;
	while (true) {
		loc_ptr = ptr->link_previous;
		if (loc_ptr == nullptr) break;
		ptr->clear();
		ptr = loc_ptr;
	}
}

template <typename type>
type& gdd_list::_list<type>::operator[](int index) {
	if (index >= this->len || index < 0) {
		print_error(ERROR_1, __LINE__, __FILE__);
	}
	__list<type>* ptr = this->link_begin;
	for (int i = 0; i < index; i++) {
		ptr = ptr->link_next;
	}
	return ptr->value;
}
template <typename type>
void gdd_list::_list<type>::append() {
	if (!this->len) {
		this->link_begin = this->link_end = new __list<type>(type(), nullptr, nullptr);
		this->len = 1;
		return;
	}
	this->link_end->link_next = new __list(type(), this->link_end, nullptr);
	this->link_end = this->link_end->link_next;
	this->len++;
}
template <typename type>
void gdd_list::_list<type>::append(type value) {
	if (!this->len) {
		this->link_begin = this->link_end = new __list<type>(value, nullptr, nullptr);
		this->len = 1;
		return;
	}
	this->link_end->link_next = new __list<type>(value, this->link_end, nullptr);
	this->link_end = this->link_end->link_next;
	this->len++;
}
template <typename type>
void gdd_list::_list<type>::append(unsigned index, type value) {
	if (index < 0 && index > this->len && this->len) print_error(ERROR_1, __LINE__, __FILE__);
	__list<type>* ptr = this->link_begin;
	if (ptr == nullptr) {
		this->link_begin = this->link_end = new __list<type>(value, nullptr, nullptr);
		this->len = 1;
		return;
	}
	if (index == this->len) {
		this->append(value);
		return;
	}
	if (index == 0) {
		this->link_begin = new __list<type>(value, nullptr, ptr);
		ptr->link_previous = this->link_begin;
		this->len++;
		return;
	}
	for (int i = 0; i < index; i++) {
		ptr = ptr->link_next;
	}
	ptr->link_previous->link_next = new __list<type>(value, ptr->link_previous, ptr);
	ptr->link_previous = ptr->link_previous->link_next;
	this->len++;
}
template <typename type>
void gdd_list::_list<type>::clear() {
	if (len == 0) return;
	if (len == 1) {
		this->len = 0;
		this->link_begin->clear();
		this->link_begin = this->link_end = nullptr;
		return;
	}
	this->link_end = this->link_end->link_previous;
	this->link_end->link_next->clear();
	this->link_end->link_next = nullptr;
	len--;
}
template <typename type>
void gdd_list::_list<type>::clear(unsigned index) {
	if (index == this->len - 1) {
		clear();
		return;
	}
	if (index < 0 || index >= this->len) print_error(len == 0 ? ERROR_2 : ERROR_1, __LINE__, __FILE__);
	if (index == 0) {
		this->link_begin = this->link_begin->link_next;
		this->link_begin->link_previous->clear();
		this->link_begin->link_previous = nullptr;
		len--;
		return;
	}
	__list<type>* ptr = this->link_begin;
	for (int i = 0; i < index; i++) {
		ptr = ptr->link_next;
	}
	ptr->link_previous->link_next = ptr->link_next;
	ptr->link_next->link_previous = ptr->link_previous;
	ptr->clear();
	len--;
}

template <typename type>
void gdd_list::_list<type>::print() {
	__list<type>* ptr = this->link_begin;
	if (!this->len) return;
	do {
		std::cout << ptr->value << " ";
		ptr = ptr->link_next;
	} while (ptr != nullptr);
	std::cout << std::endl;
}
template <typename type>
void gdd_list::_list<type>::print(char sum1, char sum2) {
	__list<type>* ptr = this->link_begin;
	if (!this->len) print_error(ERROR_2, __LINE__, __FILE__);
	do {
		std::cout << sum1 << ptr->value << sum2 << " ";
		ptr = ptr->link_next;
	} while (ptr != nullptr);
	std::cout << std::endl;
}
template <typename type>
unsigned gdd_list::_list<type>::length() {
	return this->len;
}
template<typename type>
bool gdd_list::_list<type>::contains(type num) {
	__list<type>* ptr = this->link_begin;
	if (!this->len) return false;
	do {
		if (ptr->value == num) return true;
		ptr = ptr->link_next;
	} while (ptr != nullptr);
	return false;
}
template <typename type>
inline void gdd_list::_list<type>::print_error(int error, int line, const char* file) {
	std::cout << std::endl;
	switch (error)
	{
	case ERROR_1:
		std::cout << "file '" << file << "' line[" << line << "] : linegoing beyond the borders" << std::endl;
		break;
	case ERROR_2:
		std::cout << "file '" << file << "' line[" << line << "] : need to initialize the variable" << std::endl;
		break;
	default:
		break;
	}
	exit(error);
}