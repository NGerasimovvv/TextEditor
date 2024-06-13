#include "MyString.h"

//Default constructor
MS::MyString() {
	this->myStrSize = 0;
	this->myStrCapacity = 0;
	this->myString = new char[0];
}

//Init class with count characters of �char string�
MS::MyString(const char String[], size_t count) {
	this->myStrSize = count;
	this->myStrCapacity = this->myStrSize + 1;
	this->myString = new char[count + 1];

	for (size_t i = 0; i < count; i++)
		this->myString[i] = String[i];
	this->myString[count] = '\0';
}

//Char array constructor
MS::MyString(const char String[]) : MyString(String, strlen(String)) { }

//Initializer list constructor
MS::MyString(initializer_list<char> chars) {
	this->myStrSize = chars.size();
	this->myStrCapacity = this->myStrSize + 1;
	this->myString = new char[chars.size() + 1];
	const char* chr = chars.begin();
	size_t i = 0;
	for (; i < (size_t)chars.size(); i++, chr++)
		this->myString[i] = *chr;
	this->myString[i] = '\0';
}

//std::string constructor
MS::MyString(const string stroka) : MyString(stroka.c_str()) { }

//Init class with count of characters
MS::MyString(size_t count, const char sim) {
	this->myStrSize = count;
	this->myStrCapacity = this->myStrSize + 1;
	this->myString = new char[count + 1];

	for (size_t i = 0; i < count; i++)
		this->myString[i] = sim;
	this->myString[count] = '\0';
}

//Copy constructor
MS::MyString(const MyString& other) {
	this->myStrSize = other.myStrSize;
	this->myStrCapacity = other.myStrCapacity;
	this->myString = new char[other.myStrCapacity];

	for (size_t i = 0; i < other.myStrCapacity; i++)
		this->myString[i] = other.myString[i];
}

//Destructor
MS::~MyString(void) {
	delete[] this->myString;
}

//Concatenate with Mystring
MyString MS::operator +(const MyString& other) {
	MyString temp(*this);
	return temp.append(other.myString);
}

//MyString assignment
MyString MS::operator =(const MyString& other) {
	this->clear();
	return this->append(other.myString);
}

//Concatenate with char array
MyString MS::operator +(const char String[]) {
	MyString temp(*this);
	return temp.append(String);
}

//Concatenate with std::string
MyString MS::operator +(const string stroka) {
	MyString temp(*this);
	return temp.append(stroka);
}

//Assignment concatenate with char array
MyString MS::operator +=(const char String[]) {
	return this->append(String);

}

//Assignment concatenate with std::string
MyString MS::operator +=(const string stroka) {
	return this->append(stroka);
}

MyString MS::operator +=(const MyString& other) {
	return this->append(other.myString);
}

//Char string assignment
MyString MS::operator =(const char String[]) {

	MyString temp(String);
	return *this = temp;
}

//std::string assignment
MyString MS::operator =(const string stroka) {
	MyString temp(stroka);
	return *this = temp;
}

//Char assignment
MyString MS::operator =(const char chr) {
	char pChr[] = { chr, '\0' };
	MyString temp(pChr);
	return *this = temp;
}

//Index operator
char MS::operator [](const size_t idx) {
	if (idx <= this->myStrSize && idx >= 0 && this->myStrSize > 0)
		return this->myString[idx];
	else
		throw "Out of range";
}

//Lexicographical comparing
bool MS::operator ==(MyString& other) {
	if (this->myStrSize == other.myStrSize) {
		size_t i = 0;
		while (i < this->myStrSize)
			if (this->myString[i] != other.myString[i++]) return false;
		return true;
	}
	else return false;
}

//Lexicographical comparing
bool MS::operator !=(MyString& other) {
	return !(*this == other);
}

//Lexicographical comparing
bool MS::operator >(MyString& other) {
	if (this->myStrSize == other.myStrSize) {
		size_t i = 0;
		while (this->myString[i] == other.myString[i++]);
		i--;
		return (this->myString[i] > other.myString[i]);
	}
	else return (this->myStrSize > other.myStrSize);
}

//Lexicographical comparing
bool MS::operator <(MyString& other) {
	return !((*this > other) || (*this == other));
}

//Lexicographical comparing
bool MS::operator >=(MyString& other) {
	return !(*this < other);
}

//Lexicographical comparing
bool MS::operator <=(MyString& other) {
	return !(*this > other);
}

//A pointer to null-terminated character array
const char* MS::c_str(void) {
	char* temp = new char[this->myStrCapacity + 1];
	size_t i = 0;
	while (i <= this->myStrSize) temp[i] = this->myString[i++];
	if (temp[this->myStrSize] != '\0')
		temp[this->myStrSize + 1] = '\0';
	return temp;
}

//A pointer to array data that not required to be null-terminated
const char* MS::data(void) {
	return this->myString;
}

//Return the number of char elements in string
size_t MS::size() {
	return this->myStrSize;
}

//Return the number of char elements in string
size_t MS::length() {
	return this->myStrSize;
}

//True if string is empty
bool MS::empty() {
	return this->myStrSize == 0;
}

//Return the current amount of allocated memory for array
size_t MS::capacity() {
	return this->myStrCapacity;
}

//Reduce the capacity to size
MyString MS::shrink_to_fit() {
	if (this->myStrCapacity > this->myStrSize + 1) {
		char* temp = new char[this->myStrSize + 1];
		for (size_t i = 0; i <= this->myStrSize; i++)
			temp[i] = this->myString[i];
		delete[] this->myString;
		this->myString = temp;
		this->myStrCapacity = this->myStrSize + 1;
	}
	return *this;
}

//Remove all char element in string
void MS::clear() {
	this->erase(0, this->myStrSize);
}

//
ostream& operator <<(ostream& os, MyString& MyS) {
	for (size_t i = 0; i < MyS.myStrSize; i++)
		os << MyS.myString[i];
	return os;
}

//��������� �� ���� � ������
istream& operator >>(istream& in, MyString& MyS) {
	if (!in) MyS = MyString();
	else {
		MyS.clear();
		char r;
		in.get(r);
		while (r != '\n') {
			MyS.append(1, r);
			in.get(r);
		}
	}
	return in;
}

//Insert count of null-terminated char string at index position
//Main insert
MyString MS::insert(const size_t idx, const char String[], size_t count) {
	if (idx > this->myStrSize)
		throw "Out of range";

	size_t size = min(count, strlen(String));

	if (this->myStrCapacity > this->myStrSize + size) {
		size_t i = this->myStrSize + size - 1;
		for (; i >= idx + size && i < this->myStrSize + size; i--)
			this->myString[i] = this->myString[i - size];
		for (size_t j = size - 1; i >= idx && i < idx + size; i--, j--)
			this->myString[i] = String[j];

		this->myStrSize += size;
	}
	else {
		size_t i = 0;

		if (this->myStrCapacity == 0) this->myStrCapacity++;
		char* temp = new char[this->myStrCapacity + size];
		for (; i < idx; i++)
			temp[i] = this->myString[i];
		for (size_t k = 0; k < size; i++, k++)
			temp[i] = String[k];
		for (size_t j = idx; j < this->myStrSize; i++, j++)
			temp[i] = this->myString[j];
		temp[i] = '\0';

		delete[] this->myString;
		this->myString = temp;
		this->myStrSize += size;
		this->myStrCapacity = this->myStrSize + 1;
	}

	return *this;
}

//Insert count of char in index position
MyString MS::insert(const size_t idx, const size_t count, char chr) {
	if (idx > this->myStrSize + 1)
		throw "Out of range";

	char pChr[] = { chr, '\0' };
	for (size_t i = idx; i < idx + count; i++) {
		this->insert(i, pChr, 1);
	}

	return *this;
}

//Insert null-terminated char string at index position
MyString MS::insert(const size_t idx, const char String[]) {
	return this->insert(idx, String, strlen(String));
}

//Insert std::string at index position
MyString MS::insert(const size_t idx, string stroka) {
	return this->insert(idx, stroka.c_str());
}

//Insert count of std::string at index position
MyString MS::insert(const size_t idx, string stroka, size_t count) {
	return this->insert(idx, stroka.c_str(), min(stroka.size(), count));
}

//Erase count of char at index position
MyString MS::erase(const size_t idx, size_t count) {
	if (idx > this->myStrSize)
		throw "Out of range";

	size_t i = idx;
	for (; i < this->myStrSize - count; i++)
		this->myString[i] = this->myString[i + count];
	while (i < this->myStrSize)
		this->myString[i++] = '\0';

	this->myStrSize -= count;

	return *this;
}

//Append count of char
MyString MS::append(size_t count, const char chr) {
	return this->insert(this->myStrSize, count, chr);
}

//Append null-terminated char string
MyString MS::append(const char String[]) {
	return this->insert(this->myStrSize, String, strlen(String));
}

//Append a count of null-terminated char string by index position
MyString MS::append(const char String[], const size_t idx, size_t count) {
	return this->insert(this->myStrSize, String + idx, count);
}

//Append std:: string
MyString MS::append(const string stroka) {
	return this->insert(this->myStrSize, stroka);
}

//Append a count of std:: string by index position
MyString MS::append(const string stroka, const size_t idx, size_t count) {
	return this->insert(this->myStrSize, stroka.c_str()+idx, min(stroka.size(), (size_t)count));
}

//Replace a count of char at index by �string�
MyString MS::replace(const size_t idx, size_t count, const char String[]) {
	this->erase(idx, count);
	return this->insert(idx, String);
}

//Replace a count of char at index by std::string
MyString MS::replace(const size_t idx, size_t count, const string stroka) {
	return this->replace(idx, count, stroka.c_str());
}

//Return a substring starts with index position
MyString MS::substr(const size_t idx) {
	return this->substr(idx, this->myStrSize);
}

//Return a count of substring�s char starts with index position
MyString MS::substr(const size_t idx, size_t count) {
	MyString sub(this->myString + idx, count);
	return sub;
}

//If founded return the index of "char array" substring. Search starts from index position
//Main find
size_t MS::find(const char String[], const size_t idx) {
	size_t size = strlen(String);
	size_t i = idx;
	if (this->myStrSize < size)
		return -1;
	for (; i <= this->myStrSize - size; i++)
		for (size_t j = 0; j < size; j++) {
			if (this->myString[i + j] != String[j]) {

				i += j;
				break;
			}
			if (j == size - 1 && this->myString[i + j] == String[j]) return i;
		}
	return -1;
}

//If founded return the index of "char array" substring
size_t MS::find(const char String[]) {
	return this->find(String, 0);
}

//If founded return the index of std::string substring
size_t MS::find(const string stroka) {
	return this->find(stroka.c_str());
}

//If founded return the index of std::string substring. Search starts from index position
size_t MS::find(const string stroka, const size_t idx) {
	return this->find(stroka.c_str(), idx);
}
