#include "MyString.h"

std::allocator<char> MyString::aloc_ = std::allocator<char>();  //static 成员初始化放在.cpp中
MyString::MyString(const MyString& rhs) :start_(0), finish_(0), endOfStorage_(0)
{
	allocateAndCopy(rhs.start_, rhs.finish_);
}

MyString::MyString(const MyString& str, size_t pos, size_t len) : start_(0), finish_(0), endOfStorage_(0)
{
	if (len == npos || pos + len > str.size())
		allocateAndCopy(str.start_ + pos, str.finish_);
	else
		allocateAndCopy(str.start_ + pos, str.start_ + pos + len);
}

MyString::MyString(const char* s) :start_(0), finish_(0), endOfStorage_(0)
{
	allocateAndCopy(s, s + strlen(s));
}

MyString::MyString(const char* s, size_t n) : start_(0), finish_(0), endOfStorage_(0)
{
	allocateAndCopy(s, s + n);
}

MyString::MyString(size_t n, char c) : start_(0), finish_(0), endOfStorage_(0)
{
	allocateAndFillN(n, c);
}

MyString& MyString::operator=(const MyString& str)
{
	if (this != &str)  //注意处理自赋值的情况
	{
		destroyAndDeallocate();
		allocateAndCopy(str.begin(), str.end());
	}
	return *this;
}

MyString& MyString::operator=(const char* s)
{
	destroyAndDeallocate();
	allocateAndCopy(s, s + strlen(s));
	return *this;
}

MyString& MyString::operator=(char c)
{
	destroyAndDeallocate();
	allocateAndFillN(1, c);
	return *this;
}


MyString::~MyString()
{
	destroyAndDeallocate();
}

void MyString::resize(size_t n)
{
	resize(n, value_type());
}

void MyString::resize(size_t n, char c)
{
	size_t capacity = endOfStorage_ - start_;
	if (n < size())
	{
		destroy(start_ + n, start_ + size());
		finish_ = start_ + n;
	}
	else if (n <= capacity)
	{
		auto count = n - size();
		finish_ = std::uninitialized_fill_n(finish_, count, c);
	}
	else if (n > capacity)
	{
		auto newStart = aloc_.allocate(n);
		auto newFinish = std::uninitialized_copy(start_, finish_, newStart);
		newFinish = std::uninitialized_fill_n(newFinish, n - size(), c);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + n;
	}
}

void MyString::reserve(size_t n)
{
	if (n < capacity())
		return;
	auto newStart = aloc_.allocate(n);
	auto newFinish = std::uninitialized_copy(start_, finish_, newStart);
	destroyAndDeallocate();
	start_ = newStart;
	finish_ = newFinish;
	endOfStorage_ = start_ + n;
}

MyString& MyString::insert(size_t pos, const MyString& str)
{
	insert(start_ + pos, str.begin(), str.end());
	return *this;
}

MyString& MyString::insert(size_t pos, const char* s)
{
	insert(start_ + pos, s, s + strlen(s));
	return *this;
}

MyString& MyString::insert(size_t pos, const char* s, size_t n)
{
	insert(start_ + pos, s, s + n);
	return *this;
}

MyString& MyString::insert(size_t pos, size_t n, char c)
{
	insert(start_ + pos, n, c);
	return *this;
}

MyString::iterator MyString::insert(iterator p, size_t n, char c)
{
	auto lengthOfLeft = capacity() - size();
	if (n <= lengthOfLeft)
	{
		for (auto it = finish_ - 1; it >= p; --it)
			* (it + n) = *it;
		std::uninitialized_fill_n(p, n, c);
		finish_ += n;
		return (p + n);
	}
	else  //重新分配空间
	{
		auto newCapacity = getNewCapacity(n);
		iterator newStart = aloc_.allocate(newCapacity);
		iterator newFinish = std::uninitialized_copy(start_, p, newStart);
		newFinish = std::uninitialized_fill_n(newFinish, n, c);
		iterator res = newFinish;
		newFinish = std::uninitialized_copy(p, finish_, newFinish);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return res;
	}
}

MyString::iterator MyString::insert(iterator p, char c)
{
	if (p == 0)
		p = start_;
	return insert(p, 1, c);
}

MyString& MyString::append(const MyString& str)
{
	append(str.begin(), str.end());
	return *this;
}

MyString& MyString::append(const char* s)
{
	append(s, s + strlen(s));
	return *this;
}

MyString& MyString::append(const char* s, size_t n)
{
	append(s, s + n);
	return *this;
}

MyString& MyString::append(size_t n, char c)
{
	insert(end(), n, c);
	return *this;
	/*size_t lengthOfLeft = endOfStorage_ - finish_;
	if (n <= lengthOfLeft)
	{
		finish_ = std::uninitialized_fill_n(finish_, n, c);
		return *this;
	}
	else
	{
		auto newCapacity = getNewCapacity(n);
		iterator newStart = aloc_.allocate(newCapacity);
		iterator newFinish = std::uninitialized_copy(start_, finish_, newStart);
		newFinish = std::uninitialized_fill_n(newFinish, n, c);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return *this;
	}*/
}

MyString& MyString::operator+=(const MyString& str)
{
	return append(str);
}

MyString& MyString::operator+=(const char* s)
{
	return append(s);
}

MyString& MyString::operator+=(char c)
{
	return append(1, c);
}

MyString& MyString::erase(size_t pos, size_t len)
{
	if (len == npos || pos + len > size())
	{
		erase(start_ + pos, finish_);
		return *this;
	}
	else
	{
		erase(start_ + pos, start_ + pos + len);
		return *this;
	}
}

MyString::iterator MyString::erase(iterator p)
{
	return erase(p, p + 1);
}

MyString::iterator MyString::erase(iterator first, iterator last)
{
	auto len = last - first;
	for (auto it = first; it + len < finish_; ++it)
		* it = *(it + len);
	destroy(finish_ - len, finish_);
	finish_ -= len;
	return first;
}

MyString& MyString::replace(size_t pos, size_t len, const MyString& str)
{
	return replace(start_ + pos, start_ + pos + len, str.begin(), str.end());
}

MyString& MyString::replace(iterator i1, iterator i2, const MyString& str)
{
	return replace(i1, i2, str.begin(), str.end());
}

MyString& MyString::replace(size_t pos, size_t len, const char* s)
{
	return replace(start_ + pos, start_ + pos + len, s, s + strlen(s));
}

MyString& MyString::replace(iterator i1, iterator i2, const char* s)
{
	return replace(i1, i2, s, s + strlen(s));
}

MyString& MyString::replace(size_t pos, size_t len, const char* s, size_t n)
{
	return replace(start_ + pos, start_ + pos + len, s, s + n);
}

MyString& MyString::replace(iterator i1, iterator i2, const char* s, size_t n)
{
	return replace(i1, i2, s, s + n);
}

MyString& MyString::replace(size_t pos, size_t len, size_t n, char c)
{
	return replace(start_ + pos, start_ + pos + len, n, c);
}

MyString& MyString::replace(iterator i1, iterator i2, size_t n, char c)
{
	erase(i1, i2);
	insert(i1, n, c);
	return *this;
}

size_t MyString::find(const MyString& str, size_t pos) const
{
	return find_aux(str.begin(), str.end(), pos);
}

size_t MyString::find(const char* s, size_t pos) const
{
	return find_aux(s, s + strlen(s), pos);
}

size_t MyString::find(const char* s, size_t pos, size_t n) const
{
	return find_aux(s, s + n, pos);
}

size_t MyString::find(char c, size_t pos) const
{
	for (size_t i = pos; i < size(); ++i)
	{
		if (*(start_ + pos + i) == c)
			return i;
	}
	return npos;
}

size_t MyString::rfind(const MyString& str, size_t pos) const
{
	return rfind_aux(str.begin(), str.end(), pos);
}

size_t MyString::rfind(const char* s, size_t pos) const
{
	return rfind_aux(s, s + strlen(s), pos);
}

size_t MyString::rfind(const char* s, size_t pos, size_t n) const
{
	return rfind_aux(s, s + n, pos);
}

size_t MyString::rfind(char c, size_t pos) const
{
	for (size_t i = size()-1; i >= pos; --i)
	{
		if (*(start_ + i) == c)
			return i;
	}
	return npos;
}

size_t MyString::find_first_of(const MyString& str, size_t pos) const
{
	return find_first_of(str.begin(), pos, str.size());
}

size_t MyString::find_first_of(const char* s, size_t pos) const
{
	return find_first_of(s, pos, strlen(s));
}

size_t MyString::find_first_of(const char* s, size_t pos, size_t n) const
{
	for (size_t i = pos; i < size(); ++i)
	{
		for (auto it = s; it != s + n; ++it)
		{
			if (*it == *(start_ + i))
				return i;
		}
	}
	return npos;
}

size_t MyString::find_first_of(char c, size_t pos) const
{
	for (size_t i = pos; i < size(); ++i)
	{
		if (c == *(start_ + i))
			return i;
	}
	return npos;
}

size_t MyString::find_last_of(const MyString& str, size_t pos) const
{
	return find_last_of(str.begin(), pos, str.size());
}

size_t MyString::find_last_of(const char* s, size_t pos) const
{
	return find_last_of(s, pos, strlen(s));
}

size_t MyString::find_last_of(const char* s, size_t pos, size_t n) const
{
	for (size_t i = size() - 1; i != pos; --i)
	{
		for (auto it = s; it != s + n; ++it)
		{
			if (*it == *(start_ + i))
				return i;
		}
	}
	return npos;
}

size_t MyString::find_last_of(char c, size_t pos) const
{
	for (size_t i = size() - 1; i != pos; --i)
	{
		if (c == *(start_ + i))
			return i;
	}
	return npos;
}

size_t MyString::find_first_not_of(const MyString& str, size_t pos) const
{
	return find_first_not_of(str.begin(), pos, str.size());
}

size_t MyString::find_first_not_of(const char* s, size_t pos) const
{
	return find_first_not_of(s, pos, strlen(s));
}

size_t MyString::find_first_not_of(const char* s, size_t pos, size_t n) const
{
	for (size_t i = pos; i < size(); ++i)
	{
		for (auto it = s; it != s + n; ++it)
		{
			if (*it == *(start_ + i))
				break;
			if (it == s + n - 1)
				return i;
		}
	}
	return npos;
}

size_t MyString::find_first_not_of(char c, size_t pos) const
{
	for (size_t i = pos; i < size(); ++i)
	{
		if (*(start_ + i) != c)
			return i;
	}
	return npos;
}

size_t MyString::find_last_not_of(const MyString& str, size_t pos) const
{
	return find_last_not_of(str.begin(), pos, str.size());
}

size_t MyString::find_last_not_of(const char* s, size_t pos) const
{
	return find_last_not_of(s, pos, strlen(s));
}

size_t MyString::find_last_not_of(const char* s, size_t pos, size_t n) const
{
	for (size_t i = size() - 1; i != pos; --i)
	{
		for (auto it = s; it != s + n; ++it)
		{
			if (*it == *(start_ + i))
				break;
			if (it == s + n - 1)
				return i;
		}
	}
	return npos;
}

size_t MyString::find_last_not_of(char c, size_t pos) const
{
	for (size_t i = size() - 1; i != pos; --i)
	{
		if (*(start_ + i) != c)
			return i;
	}
	return npos;
}

int MyString::compare(const MyString& str) const
{
	return compare(0, size(), str.begin(), str.size());
}

int MyString::compare(size_t pos, size_t len, const MyString& str) const
{
	return compare(pos, len, str.begin(), str.size());
}

int MyString::compare(const char* s) const
{
	return compare(0, size(), s, strlen(s));
}

int MyString::compare(size_t pos, size_t len, const char* s) const
{
	return compare(pos, len, s, strlen(s));
}

int MyString::compare(size_t pos, size_t len, const char* s, size_t n) const
{
	size_t i = pos, j = 0;
	for (; i - pos < len && j < n; ++i, ++j)
	{
		if (*(start_ + i) > * (s + j))
			return 1;
		else if (*(start_ + i) < *(s + j))
			return -1;
	}
	if (i == pos + len && j == n)
		return 0;
	else if (i == pos + len)
		return -1;
	else
		return 1;
}

void MyString::allocateAndFillN(size_t n, char c)
{
	start_ = aloc_.allocate(n);
	finish_ = std::uninitialized_fill_n(start_, n, c);
	endOfStorage_ = finish_;
}

void MyString::destroyAndDeallocate()
{
	destroy(start_, finish_);
	aloc_.deallocate(start_, endOfStorage_ - start_);
}

inline size_t MyString::getNewCapacity(size_t n)
{
	auto oldCapacity = capacity();
	auto newCapacity = n > oldCapacity ? n : oldCapacity;
	return oldCapacity + newCapacity;
}

size_t MyString::find_aux(const_iterator first, const_iterator last, size_t pos)const
{
	size_t len = last - first;
	for (size_t i = pos; i <= size()-len; ++i)
	{
		size_t j = 0;
		for (auto it = first; it != last; ++it)
		{
			if (*it != *(start_ + i + j++))
				break;
			if (it + 1 == last)
				return i;
		}
	}
	return npos;
}

size_t MyString::rfind_aux(const_iterator first, const_iterator last, size_t pos) const
{
	size_t len = last - first;
	for (size_t i = size()-len; i>=pos && i<=size()-len; --i)  //注意无符号数永远会>=0，死循环！！
	{
		size_t j = 0;
		for (auto it = first; it != last; ++it)
		{
			if (*it != *(start_ + i + j++))
				break;
			if (it + 1 == last)
				return i;
		}
	}
	return npos;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	for (const auto ch : str)
	{
		os << ch;
	}
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char c;
	while (is >> c)
	{
		str.push_back(c);
	}
	return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res(lhs);
	res += rhs;
	return res;
}

MyString operator+(const MyString& lhs, const char* rhs)
{
	MyString res(lhs);
	res += rhs;
	return res;
}

MyString operator+(const char* lhs, const MyString& rhs)
{
	MyString res(lhs);
	res += rhs;
	return res;
}

MyString operator+(const MyString& lhs, char rhs)
{
	MyString res(lhs);
	res += rhs;
	return res;
}

MyString operator+(char lhs, const MyString& rhs)
{
	MyString res(1, lhs);
	res += rhs;
	return res;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	auto it1 = lhs.begin();
	auto it2 = rhs.begin();
	for (; it1 != lhs.end(); ++it1, ++it2)
	{
		if (*it1 != *it2)
			return false;
	}
	return true;
}

bool operator==(const MyString& lhs, const char* rhs)
{
	if (lhs.size() != strlen(rhs))
		return false;
	auto it1 = lhs.begin();
	auto it2 = rhs;
	for (; it1 != lhs.end(); ++it1, ++it2)
	{
		if (*it1 != *it2)
			return false;
	}
	return true;
}

bool operator==(const char* lhs, const MyString& rhs)
{
	return rhs == lhs;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator!=(const MyString& lhs, const char* rhs)
{
	return !(lhs == rhs);
}

bool operator!=(const char* lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return lhs.compare(rhs) >= 0;
}

bool operator>=(const MyString& lhs, const char* rhs)
{
	return lhs.compare(rhs) >= 0;
}

bool operator>=(const char* lhs, const MyString& rhs)
{
	return rhs.compare(lhs) <= 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return lhs.compare(rhs) <= 0;
}

bool operator<=(const MyString& lhs, const char* rhs)
{
	return lhs.compare(rhs) <= 0;
}

bool operator<=(const char* lhs, const MyString& rhs)
{
	return rhs.compare(lhs) >= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return lhs.compare(rhs) > 0;
}

bool operator>(const MyString& lhs, const char* rhs)
{
	return lhs.compare(rhs) > 0;
}

bool operator>(const char* lhs, const MyString& rhs)
{
	return rhs.compare(lhs) < 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return lhs.compare(rhs) < 0;
}

bool operator<(const MyString& lhs, const char* rhs)
{
	return lhs.compare(rhs) < 0;
}

bool operator<(const char* lhs, const MyString& rhs)
{
	return rhs.compare(lhs) > 0;
}
