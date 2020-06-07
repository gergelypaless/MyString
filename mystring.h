#pragma once

#include <ostream>
#include <istream>

class MyString
{
	class StringValue;
	class Char;
public:
	MyString();
	MyString(const MyString&);
	MyString(MyString&&) noexcept;
	MyString(const char*);
	MyString(char);
	~MyString();

	MyString& operator=(const MyString&);
	MyString& operator=(MyString&&) noexcept;

	MyString operator+(const MyString&) const;
	MyString& operator+=(const MyString&);

	MyString operator+(char) const;
	MyString& operator+=(char);

	const char& operator[](unsigned long long index) const;
	Char operator[](unsigned long long index);

	inline unsigned long long length() const;

private:
	MyString(StringValue*);
	void ForgetValue();
	void CopyIfNecessary();

	StringValue* value;

private:
	class StringValue
	{
	public:
		StringValue();
		StringValue(const StringValue&);
		StringValue(const char*);
		StringValue(const char&);
		~StringValue();

		StringValue& operator=(const StringValue&) = delete;

		const char& operator[](unsigned long long idx) const;
		char& operator[](unsigned long long idx);

		StringValue* operator+(const StringValue& other);
		StringValue* operator+(char);

		inline void Inc_count();
		inline void Dec_count();
		inline unsigned int Count();
		inline unsigned long long Len();

	private:
		unsigned int count;
		char* data;

		StringValue(unsigned long long len);
	};

	class Char
	{
	public:
		Char(MyString& s, unsigned long long idx) : str(s), index(idx) {}

		operator char();
		Char& operator=(const Char& other);
		Char& operator=(const char& c);

	private:
		MyString& str;
		unsigned long long index;
	};
};

std::ostream& operator<<(std::ostream& os, const MyString&);
std::istream& operator>>(std::istream& is, MyString&);



