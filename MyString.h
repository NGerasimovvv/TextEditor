#pragma once
#ifndef _MYSTRING_H_

#define _MYSTRING_H_
#include <iostream>
#include <string>
#include <cstdarg>
#include <initializer_list>
#include <string.h>
using namespace std;

#define MS MyString

class MyString {
public:
	MyString();
	MyString(const char String[]);
	MyString(initializer_list<char> chars);
	MyString(const string stroka);
	MyString(const char String[], size_t count);
	MyString(size_t count, const char sim);
	MyString(const MyString& other);
	~MyString(void);

	MyString operator =(const MyString& other);
	MyString operator =(const char String[]);
	MyString operator =(const string stroka);
	MyString operator =(const char chr);

	MyString operator +(const MyString &other);
	MyString operator +(const char String[]);
	MyString operator +(const string stroka);

	MyString operator +=(const char String[]);
	MyString operator +=(const string stroka);
	MyString operator +=(const MyString& other);

	char operator [](const size_t id);

	bool operator >(MyString& other);
	bool operator <(MyString& other);
	bool operator >=(MyString& other);
	bool operator <=(MyString& other);
	bool operator !=(MyString& other);
	bool operator ==(MyString& other);

	const char* c_str(void);
	const char* data(void);

	size_t size(void);
	size_t length(void);
	bool empty(void);
	size_t capacity(void);

	MyString shrink_to_fit(void);

	void clear(void);

	friend ostream& operator <<(ostream& os, MyString& MyS);
	friend istream& operator >>(istream& in, MyString& MyS);

	MyString insert(const size_t id, size_t count, char chr);
	MyString insert(const size_t id, const char String[]);
	MyString insert(const size_t id, const char String[], size_t count);
	MyString insert(const size_t id, string stroka);
	MyString insert(const size_t id, string stroka, size_t count);

	MyString erase(const size_t id, size_t count);

	MyString append(size_t count, const char chr);
	MyString append(const char String[]);
	MyString append(const char String[], const size_t id, size_t count);
	MyString append(const string stroka);
	MyString append(const string stroka, const size_t id, size_t count);

	MyString replace(const size_t id, size_t count, const char String[]);
	MyString replace(const size_t id, size_t count, const string stroka);

	MyString substr(const size_t id);
	MyString substr(const size_t id, size_t count);

	size_t find(const char String[]);
	size_t find(const char String[], const size_t id);
	size_t find(const string stroka);
	size_t find(const string stroka, const size_t id);

private:
	size_t myStrSize, myStrCapacity;
	char* myString;
};

ostream& operator <<(ostream& os, MyString& MyS);
istream& operator >>(istream& in, MyString& MyS);

#endif // _MYSTRING_H_
