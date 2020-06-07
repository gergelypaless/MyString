#include "mystring.h"
#include <cstring>


MyString::MyString() : value(new StringValue)
{
	value->Inc_count();
}

MyString::MyString(const MyString& other) : value(other.value)
{
	value->Inc_count();
}

MyString::MyString(MyString&& other) noexcept : value(other.value)
{
	other.value = nullptr;
}

MyString::MyString(const char* cstr) : value(new StringValue(cstr))
{
	value->Inc_count();
}

MyString::MyString(char c) : value(new StringValue(c))
{
	value->Inc_count();
}

MyString::~MyString()
{
	if (value) ForgetValue();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		ForgetValue();
		value = other.value;
		value->Inc_count();
    }
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		if (value) ForgetValue();
		value = other.value;
		other.value = nullptr;
	}
	return *this;
}

MyString MyString::operator+(const MyString& other) const
{
	return *value + *other.value;
}

MyString& MyString::operator+=(const MyString& other)
{
	CopyIfNecessary();
	*this = *this + other;
	return *this;
}

MyString MyString::operator+(char c) const
{
	return MyString(*value + c);
}

MyString& MyString::operator+=(char c)
{
	CopyIfNecessary();
	*this = *this + c;
	return *this;
}

MyString::Char MyString::operator[](unsigned long long index)
{
	if (index >= value->Len())
		throw std::out_of_range("index is too big");

	return MyString::Char(*this, index);
}

const char& MyString::operator[](unsigned long long index) const
{
	if (index >= value->Len())
		throw std::out_of_range("index is too big");

	return value->operator[](index);
}

inline unsigned long long MyString::length() const
{
	return value->Len();
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	for (unsigned int i = 0; i < str.length(); ++i)
		os << str[i];
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	str = "";
	char c;
	while ((c = static_cast<char>(getchar())) != EOF && c != '\n')
	{
		// nem fut valami gyorsan. Van jobb megoldás?
		str += c;
	}
	return is;
}

MyString::MyString(StringValue* sValue) : value(sValue)
{
	value->Inc_count();
}

void MyString::ForgetValue()
{
	if (value->Count() > 1) value->Dec_count();
	else delete value;
}

void MyString::CopyIfNecessary()
{
	if (value->Count() > 1)
	{
		value->Dec_count();
		value = new StringValue(*value);
		value->Inc_count();
	}
}



// ---------------------------------------------------------------------
// StringValue ---------------------------------------------------------
// ---------------------------------------------------------------------

MyString::StringValue::StringValue() : count(0)
{
	data = new char[1];
	data[0] = '\0';
}

MyString::StringValue::StringValue(const StringValue& other) : count(0)
{
	data = new char[strlen(other.data) + 1];
	strcpy(data, other.data);
}

MyString::StringValue::StringValue(const char* cstr) : count(0)
{

	data = new char[strlen(cstr) + 1];
	strcpy(data, cstr);
}

MyString::StringValue::StringValue(const char& c) : count(0)
{
	data = new char[1 + 1];
	data[0] = c;
	data[1] = '\0';
}

MyString::StringValue::~StringValue()
{
	delete[] data;
}

// nem kell megnézni az idx-et, hogy nem túl nagy-e, mert a MyString operator[]-ja megteszi
const char& MyString::StringValue::operator[](unsigned long long idx) const
{
	return data[idx];
}
char& MyString::StringValue::operator[](unsigned long long idx)
{
	return data[idx];
}

MyString::StringValue* MyString::StringValue::operator+(const StringValue& other)
{
	unsigned long long strLen = strlen(data) + strlen(other.data);
	StringValue* newStr = new StringValue(strLen); // ctor takes care of + 1

	strcpy(newStr->data, data);
	strcat(newStr->data, other.data);

	return newStr;
}

MyString::StringValue* MyString::StringValue::operator+(char c)
{
	unsigned long long strLen = strlen(data) + 1;
	StringValue* newStr = new StringValue(strLen); // ctor takes care of + 1

	strcpy(newStr->data, data);
	newStr->data[strLen - 1] = c;
	newStr->data[strLen] = '\0';

	return newStr;
}

void MyString::StringValue::Inc_count()
{
	++count;
}

void MyString::StringValue::Dec_count()
{
	--count;
}

unsigned int MyString::StringValue::Count()
{
	return count;
}

unsigned long long MyString::StringValue::Len()
{
	return strlen(data);
}

MyString::StringValue::StringValue(unsigned long long len)
	: count(0), data(new char[len + 1])
{}



// ---------------------------------------------------------------------
// Char ----------------------------------------------------------------
// ---------------------------------------------------------------------

MyString::Char::operator char()
{
	return str.value->operator[](index);
}

MyString::Char& MyString::Char::operator=(const MyString::Char& other)
{
	if (this != &other)
	{
		str.CopyIfNecessary();
		str.value->operator[](index) = other.str.value->operator[](other.index);
	}
	return *this;
}

MyString::Char& MyString::Char::operator=(const char& c)
{
	str.CopyIfNecessary();
	str.value->operator[](index) = c;
	return *this;
}

