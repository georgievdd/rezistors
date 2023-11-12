#pragma once
#include <iostream>
#include <string>

//переделать
namespace gdd_string {
	class String {
	private:
		char* str;
		int L;
		int len(const char*);
	public:

		String();
		String(const String&);
		String(const char*);
		String(char* str);
		String(String&&);
		~String();

		char& operator[](int i);
		String& operator=(const String& obj);
		String& operator=(const char* obj);

		String operator+(const String& obj);
		String operator+(const char* obj);
		void operator+=(const String& obj);
		void operator+=(const char* obj);
		void operator+=(char obj);
		String operator-(const int j);
		void operator-=(const int j);
		String operator*(const int k);
		void operator*=(const int k);

		bool operator==(const String& obj);
		bool operator==(const char* obj);

		friend std::ostream& operator<<(std::ostream& out, const String& obj) {
			for (int i = 0; i < obj.L; i++) {
				out << obj.str[i];
			}
			return out;
		}
		friend std::istream& operator>>(std::istream& in, String& obj) {
			string buff;
			in >> buff;
			obj.L = buff.size();
			if (obj.str != nullptr) { delete[] obj.str; }
			obj.str = new char[obj.L + 1];
			for (int i = 0; i < obj.L; i++) {
				obj.str[i] = buff[i];
			}
			obj.str[obj.L] = '\0';
			return in;
		}

		long double to();
		char* get_char_ptr();
		int length();

	};
	String to_String(double a);
	String to_String(int a, int);
}



typedef gdd_string::String gstr;








int gdd_string::String::len(const char* str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}

gdd_string::String::String() {
	this->str = nullptr;
	L = 0;
}
gdd_string::String::String(const String& other) {
	this->str = new char[other.L + 1];
	this->L = other.L;
	for (int i = 0; i < other.L; i++) {
		this->str[i] = other.str[i];
	}
	this->str[this->L] = '\0';
}
gdd_string::String::String(const char* str) {
	this->L = len(str);
	this->str = new char[L + 1];
	for (int i = 0; i < L; i++) {
		this->str[i] = str[i];
	}
	this->str[this->L] = '\0';
}
gdd_string::String::String(char* str) {
	this->L = len(str);
	this->str = new char[L + 1];
	for (int i = 0; i < L; i++) {
		this->str[i] = str[i];
	}
	this->str[this->L] = '\0';
}
gdd_string::String::String(String&& other) {
	this->L = other.L;
	this->str = other.str;
	other.str = nullptr;
}
gdd_string::String::~String() {
	if (this->str != nullptr) delete[] this->str;
}

char& gdd_string::String::operator[](int i) {
	return this->str[i];
}
gdd_string::String& gdd_string::String::operator=(const String& obj) {
	if (str != nullptr) { delete[] str; }
	this->L = obj.L;
	this->str = new char[this->L + 1];
	for (int i = 0; i < this->L; i++) this->str[i] = obj.str[i];
	this->str[this->L] = '\0';
	return *this;
}
gdd_string::String& gdd_string::String::operator=(const char* obj) {
	if (str != nullptr) { delete[] str; }
	this->L = this->len(obj);
	this->str = new char[this->L + 1];
	for (int i = 0; i < this->L; i++) this->str[i] = obj[i];
	this->str[this->L] = '\0';
	return *this;
}

gdd_string::String gdd_string::String::operator+(const String& obj) {
	String string;
	string.L = this->L + obj.L + 1;
	string.str = new char[string.L + 1];

	for (int i = 0; i < this->L; i++) {
		string.str[i] = this->str[i];
	}
	for (int i = this->L; i < string.L; i++) {
		string.str[i] = obj.str[i - this->L];
	}
	string.str[string.L] = '\0';
	return string;
}
gdd_string::String gdd_string::String::operator+(const char* obj) {
	String string;
	string.L = this->L + this->len(obj) + 1;
	string.str = new char[string.L + 1];

	for (int i = 0; i < this->L; i++) {
		string.str[i] = this->str[i];
	}
	for (int i = this->L; i < string.L; i++) {
		string.str[i] = obj[i - this->L];
	}
	string.str[string.L] = '\0';
	return string;
}
void gdd_string::String::operator+=(const String& obj) {
	String string;
	string.L = this->L + obj.L + 1;
	string.str = new char[string.L + 1];

	for (int i = 0; i < this->L; i++) {
		string.str[i] = this->str[i];
	}
	for (int i = this->L; i < string.L; i++) {
		string.str[i] = obj.str[i - this->L];
	}
	string.str[string.L] = '\0';
	*this = string;
}
void gdd_string::String::operator+=(const char* obj) {
	String string;
	string.L = this->L + this->len(obj) + 1;
	string.str = new char[string.L + 1];

	for (int i = 0; i < this->L; i++) {
		string.str[i] = this->str[i];
	}
	for (int i = this->L; i < string.L; i++) {
		string.str[i] = obj[i - this->L];
	}
	string.str[string.L] = '\0';
	*this = string;
}
void gdd_string::String::operator+=(const char obj) {
	String string;
	string.L = this->L + 1;
	string.str = new char[string.L + 1];

	for (int i = 0; i < this->L; i++) {
		string.str[i] = this->str[i];
	}
	string.str[string.L - 1] = obj;
	string.str[string.L] = '\0';
	*this = string;
}
gdd_string::String gdd_string::String::operator-(const int j) {
	String string;
	if (L - j > 0) {
		string.L = this->L - j;
		string.str = new char[string.L + 1];

		for (int i = 0; i < L - j; i++) {
			string.str[i] = this->str[i];
		}
		string.str[string.L] = '\0';
		return string;
	}
	string.L = 0;
	string.str = nullptr;
	return string;
}
void gdd_string::String::operator-=(int j) {
	String string;
	if (L - j > 0) {
		string.L = this->L - j;
		string.str = new char[string.L + 1];

		for (int i = 0; i < L - j; i++) {
			string.str[i] = this->str[i];
		}
		string.str[string.L] = '\0';
		*this = string;
		return;
	}
	string.L = 0;
	string.str = nullptr;
	*this = string;
}
gdd_string::String gdd_string::String::operator*(const int k) {
	String string;
	string.L = this->L * k;
	string.str = new char[string.L + 1];
	for (int i = 0; i < this->L; i++) {
		for (int j = i; j < string.L; j += this->L) {
			string.str[j] = this->str[i];
		}
	}
	string.str[string.L] = '\0';
	return string;
}
void gdd_string::String::operator*=(const int k) {
	String string;
	string.L = this->L * k;
	string.str = new char[string.L + 1];
	for (int i = 0; i < this->L; i++) {
		for (int j = i; j < string.L; j += this->L) {
			string.str[j] = this->str[i];
		}
	}
	string.str[string.L] = '\0';
	*this = string;
}
bool gdd_string::String::operator==(const String& obj) {
	if (this->L != obj.L) return false;
	for (int i = 0; i < this->L; i++)
		if (str[i] != obj.str[i]) return false;
	return true;
}
bool gdd_string::String::operator==(const char* obj) {
	if (this->L != this->len(obj)) return false;
	for (int i = 0; i < this->L; i++)
		if (str[i] != obj[i]) return false;
	return true;
}

long double gdd_string::String::to() {
	long double t = 0, s = 0.1, flag = 0;
	int begin = 0, sign = 1;
	if (str[begin] == '-') { sign *= -1; begin++; }
	for (int i = begin; i < L; i++) {
		if (str[i] != '.') {
			t = t * 10 + (str[i] - '0');
		}
		else { flag = 1; }
		if (flag == 1) { s *= 10; }
	}

	if (flag == 1) { return t / s * sign; }
	return t * sign;
}
char* gdd_string::String::get_char_ptr() {
	return this->str;
}
int gdd_string::String::length() {
	return this->L;
}

gdd_string::String gdd_string::to_String(double a) {
	char str[100];
	int i = 0;
	a *= 100000000;
	long long b = (long long)a;
	while (b > 0) {
		str[i++] = (b % 10 + '0');
		b /= 10;
		if (i == 8) { str[i++] = '.'; }
	}
	if (str[i - 1] == '.') str[i++] = '0';
	char* str2 = new char[i + 1];
	for (int j = i - 1; j >= 5; j--) {
		str2[i - j - 1] = str[j];
	}
	str2[i] = '\0';
	return str2;
}

gdd_string::String gdd_string::to_String(int a, int) {
	if (a == 0) return "0";
	char str[10];
	int i = 0;
	while (a > 0) {
		str[i++] = (a % 10 + '0');
		a /= 10;
	}
	char* str2 = new char[i + 1];
	for (int j = i - 1; j >= 0; j--) {
		str2[i - j - 1] = str[j];
	}
	str2[i] = '\0';
	return str2;
}
