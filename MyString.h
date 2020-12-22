#pragma once
#include <cstring>
#include <iostream>
#include <memory>

class MyString
{
public:
	typedef char value_type;
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef char& reference;
	typedef const char& const_reference;
	typedef size_t size_type;
	static const size_t npos = -1;
public:
	MyString() :start_(0), finish_(0), endOfStorage_(0) {}
	MyString(const MyString& str);
	MyString(const MyString& str, size_t pos, size_t len = npos);
	MyString(const char* s);
	MyString(const char* s, size_t n);
	MyString(size_t n, char c);
	template <typename InputIterator>
	MyString(InputIterator first, InputIterator last);
	MyString& operator=(const MyString& str);
	MyString& operator=(const char* s);
	MyString& operator=(char c);

	~MyString();

	iterator begin() { return start_; };
	const_iterator begin() const { return start_; };  //本质上const函数是形参为const this,故可以重载，通常const对象会调用此版本
	const_iterator cbegin() const { return start_; };
	iterator end() { return finish_; };
	const_iterator end() const { return finish_; };
	const_iterator cend() const { return finish_; };
	size_t size() const { return finish_ - start_; };
	size_t length() const { return size(); };
	size_t capacity() const { return endOfStorage_ - start_; };
	void clear()
	{
		destroy(start_, finish_);
		finish_ = start_;
	}
	bool empty()const { return start_ == finish_; };
	void resize(size_t n);
	void resize(size_t n, char c);
	void reserve(size_t n = 0);
	void shrink_to_fit()
	{
		MyString tmp(*this);
		swap(tmp);
	}
	char& operator[](size_t pos) { return *(start_ + pos); };
	const char& operator[](size_t pos)const { return *(start_ + pos); };
	char& back() { return *(finish_ - 1); };
	const char& back() const { return *(finish_ - 1); };
	char& front() { return *(start_); };
	const char& front() const { return *(start_); };

	void push_back(char c) { insert(finish_, c); };
	MyString& insert(size_t pos, const MyString& str);
	MyString& insert(size_t pos, const char* s);
	MyString& insert(size_t pos, const char* s, size_t n);
	MyString& insert(size_t pos, size_t n, char c);
	iterator insert(iterator p, size_t n, char c);
	iterator insert(iterator p, char c);
	template<typename InputIterator>
	iterator insert(iterator p, InputIterator first, InputIterator last);
	MyString& append(const MyString& str);
	MyString& append(const char* s);
	MyString& append(const char* s, size_t n);
	MyString& append(size_t n, char c);
	template<typename InputIterator>
	MyString& append(InputIterator first, InputIterator last);
	MyString& operator+=(const MyString& str);
	MyString& operator+=(const char* s);
	MyString& operator+=(char c);

	void pop_back() { erase(end() - 1, end()); };
	MyString& erase(size_t pos = 0, size_t len = npos);
	iterator erase(iterator p);
	iterator erase(iterator first, iterator last);

	MyString& replace(size_t pos, size_t len, const MyString& str);
	MyString& replace(iterator i1, iterator i2, const MyString& str);
	MyString& replace(size_t pos, size_t len, const char* s);
	MyString& replace(iterator i1, iterator i2, const char* s);
	MyString& replace(size_t pos, size_t len, const char* s, size_t n);
	MyString& replace(iterator i1, iterator i2, const char* s, size_t n);
	MyString& replace(size_t pos, size_t len, size_t n, char c);
	MyString& replace(iterator i1, iterator i2, size_t n, char c);
	template<typename InputIterator>
	MyString& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

	void swap(MyString& str)
	{
		std::swap(start_, str.start_);
		std::swap(finish_, str.finish_);
		std::swap(endOfStorage_, str.endOfStorage_);
	}
	size_t copy(char* s, size_t len, size_t pos = 0)const
	{
		iterator p = std::uninitialized_copy(start_ + pos, start_ + pos + len, s);
		return (p - s);
	}

	size_t find(const MyString& str, size_t pos = 0)const;
	size_t find(const char* s, size_t pos = 0)const;
	size_t find(const char* s, size_t pos, size_t n)const;
	size_t find(char c, size_t pos = 0)const;
	size_t rfind(const MyString& str, size_t pos = 0)const;
	size_t rfind(const char* s, size_t pos = 0)const;
	size_t rfind(const char* s, size_t pos, size_t n)const;
	size_t rfind(char c, size_t pos = 0)const;
	size_t find_first_of(const MyString& str, size_t pos = 0)const;
	size_t find_first_of(const char* s, size_t pos = 0)const;
	size_t find_first_of(const char* s, size_t pos, size_t n)const;
	size_t find_first_of(char c, size_t pos = 0)const;
	size_t find_last_of(const MyString& str, size_t pos = 0)const;
	size_t find_last_of(const char* s, size_t pos = 0)const;
	size_t find_last_of(const char* s, size_t pos, size_t n)const;
	size_t find_last_of(char c, size_t pos = 0)const;
	size_t find_first_not_of(const MyString& str, size_t pos = 0)const;
	size_t find_first_not_of(const char* s, size_t pos = 0)const;
	size_t find_first_not_of(const char* s, size_t pos, size_t n)const;
	size_t find_first_not_of(char c, size_t pos = 0)const;
	size_t find_last_not_of(const MyString& str, size_t pos = 0)const;
	size_t find_last_not_of(const char* s, size_t pos = 0)const;
	size_t find_last_not_of(const char* s, size_t pos, size_t n)const;
	size_t find_last_not_of(char c, size_t pos = 0)const;

	MyString substr(size_t pos = 0, size_t len = npos)const
	{
		if (len == npos || pos + len > size())
			len = size() - pos;
		return MyString(start_ + pos, start_ + pos + len);
	}

	int compare(const MyString& str)const;
	int compare(size_t pos, size_t len, const MyString& str)const;
	int compare(const char* s)const;
	int compare(size_t pos, size_t len, const char* s)const;
	int compare(size_t pos, size_t len, const char* s, size_t n)const;

private:
	char* start_;
	char* finish_;
	char* endOfStorage_;
public:
	static std::allocator<char> aloc_;
private:
	void allocateAndFillN(size_t n, char c);
	template<typename InputIterator>
	void allocateAndCopy(InputIterator first, InputIterator last);
	template<typename InputIterator>
	void destroy(InputIterator first, InputIterator last);
	void destroyAndDeallocate();
	inline size_t getNewCapacity(size_t n);
	size_t find_aux(const_iterator first, const_iterator last, size_t pos)const;  //必须声明为const，const函数不能调用non-const函数
	size_t rfind_aux(const_iterator first, const_iterator last, size_t pos)const;

public:
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend MyString operator+ (const MyString& lhs, const char* rhs);
	friend MyString operator+ (const char* lhs, const MyString& rhs);
	friend MyString operator+ (const MyString& lhs, char rhs);
	friend MyString operator+ (char lhs, const MyString& rhs);
	friend bool operator==(const MyString& lhs, const MyString& rhs);
	friend bool operator==(const MyString& lhs, const char* rhs);
	friend bool operator==(const char*lhs, const MyString& rhs);
	friend bool operator!=(const MyString& lhs, const MyString& rhs);
	friend bool operator!=(const MyString& lhs, const char* rhs);
	friend bool operator!=(const char* lhs, const MyString& rhs);
	friend bool operator>=(const MyString& lhs, const MyString& rhs);
	friend bool operator>=(const MyString& lhs, const char* rhs);
	friend bool operator>=(const char* lhs, const MyString& rhs);
	friend bool operator<=(const MyString& lhs, const MyString& rhs);
	friend bool operator<=(const MyString& lhs, const char* rhs);
	friend bool operator<=(const char* lhs, const MyString& rhs);
	friend bool operator>(const MyString& lhs, const MyString& rhs);
	friend bool operator>(const MyString& lhs, const char* rhs);
	friend bool operator>(const char* lhs, const MyString& rhs);
	friend bool operator<(const MyString& lhs, const MyString& rhs);
	friend bool operator<(const MyString& lhs, const char* rhs);
	friend bool operator<(const char* lhs, const MyString& rhs);

};


template<typename InputIterator>
MyString::MyString(InputIterator first, InputIterator last) :start_(0), finish_(0), endOfStorage_(0)
{
	allocateAndCopy(first, last);
}

template<typename InputIterator>
MyString::iterator MyString::insert(iterator p, InputIterator first, InputIterator last)
{
	size_t len = last - first;
	size_t lengthOfLeft = capacity() - size();
	if (len <= lengthOfLeft)
	{
		for (auto it = finish_ - 1; it >= p; --it)
			* (it + len) = *it;
		std::uninitialized_copy(first, last, p);
		finish_ += len;
		return p + len;
	}
	else  //重新分配空间
	{
		auto newCapacity = getNewCapacity(len);
		iterator newStart = aloc_.allocate(newCapacity);
		iterator newFinish = std::uninitialized_copy(start_, p, newStart);
		newFinish = std::uninitialized_copy(first, last, newFinish);
		iterator res = newFinish;
		newFinish = std::uninitialized_copy(p, finish_, newFinish);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return res;
	}
}

template<typename InputIterator>
MyString& MyString::append(InputIterator first, InputIterator last)
{
	insert(end(), first, last);
	return *this;
	/*size_t lengthOfLeft = endOfStorage_ - finish_;
	size_t len = last - first;
	if (len <= lengthOfLeft)
	{
		finish_ = std::uninitialized_fill_n(finish_, len, c);
		return *this;
	}
	else
	{
		auto newCapacity = getNewCapacity(len);
		iterator newStart = aloc_.allocate(newCapacity);
		iterator newFinish = std::uninitialized_copy(start_, finish_, newStart);
		newFinish = std::uninitialized_copy(first, last, newFinish);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return *this;
	}*/
}

template<typename InputIterator>
MyString& MyString::replace(iterator i1, iterator i2, InputIterator first, InputIterator last)
{
	erase(i1, i2);
	insert(i1, first, last);
	return *this;
}

template<typename InputIterator>
inline void MyString::allocateAndCopy(InputIterator first, InputIterator last)
{
	start_ = aloc_.allocate(last - first);
	finish_ = std::uninitialized_copy(first, last, start_);
	endOfStorage_ = finish_;
}
template<typename InputIterator>
inline void MyString::destroy(InputIterator first, InputIterator last)
{
	for (; first != last; ++first)
	{
		aloc_.destroy(first);
	}
}