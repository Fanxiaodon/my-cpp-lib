#include "StringTest.h"

void StringTest::testCase1()  //构造函数测试1
{
	const char* ptr = "hello world";
	stdStr str1(ptr);
	MyString str2(ptr);
	assert(containerEuqal(str1, str2));

	stdStr str3(ptr, 4);
	MyString str4(ptr, 4);
	assert(containerEuqal(str3, str4));

	stdStr str5(10, 'a');
	MyString str6(10, 'a');
	assert(containerEuqal(str5, str6));
	
	stdStr str7(ptr, ptr + 5);
	MyString str8(ptr, ptr + 5);
	assert(containerEuqal(str7, str8));
}

void StringTest::testCase2()  //构造函数测试2，copy构造
{
	stdStr temp1("hello world");
	MyString temp2("hello world");

	stdStr s1(temp1);
	MyString s2(temp2);
	assert(containerEuqal(s1, s2));

	stdStr s3(temp1, 3);
	MyString s4(temp2, 3);
	assert(containerEuqal(s3, s4));

	stdStr s5(temp1, 2, 6);
	MyString s6(temp2, 2, 6);
	assert(containerEuqal(s5, s6));

}

void StringTest::testCase3()  //赋值运算符测试
{
	char c = 'a';
	const char* temp = "Hello fxd";
	stdStr s1;
	MyString s2;

	s1 = c;
	s2 = c;
	assert(containerEuqal(s1, s2));

	s1 = temp;
	s2 = temp;
	assert(containerEuqal(s1, s2));

	stdStr s3 = s1;
	MyString s4 = s2;
	assert(containerEuqal(s3, s4));
}

void StringTest::testCase4()
{
	MyString s1;
	assert(s1.size() == 0);

	s1 = "Hello world";
	assert(s1.capacity() >= s1.size());
	stdStr s2(s1.begin(), s1.end());
	assert(containerEuqal(s2, s1));
}

void StringTest::testCase5()
{
	MyString s;
	assert(s.empty());

	s = "hello world";
	assert(!s.empty());

	s.clear();
	assert(s.empty());
}

void StringTest::testCase6()
{
	stdStr s1 = "hello world";
	MyString s2 = "hello world";

	s1.resize(5);
	s2.resize(5);
	assert(containerEuqal(s1, s2));

	s1.resize(20,'c');
	s2.resize(20, 'c');
	assert(containerEuqal(s1, s2));

	s1.reserve(100);
	s2.reserve(100);
	assert(s2.capacity() == 100);
	assert(containerEuqal(s1, s2));

	s1.shrink_to_fit();
	s2.shrink_to_fit();
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase7()
{
	stdStr s1 = "hello world";
	MyString s2 = "hello world";

	assert(s1.front() == s2.front());
	assert(s1.back() == s2.back());
}

void StringTest::testCase8()
{
	stdStr s1;
	MyString s2;
	int i = 5;
	while (i-- > 0)
	{
		s1.push_back('c');
		s2.push_back('c');
	}
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase9()
{
	stdStr s1;
	MyString s2;

	s1.insert(0, "hello");
	s2.insert(0, "hello");
	assert(containerEuqal(s1, s2));

	s1.insert(0, "fan");
	s2.insert(0, "fan");
	assert(containerEuqal(s1, s2));

	s1.insert(2, "fanxiaodong", 4);
	s2.insert(2, "fanxiaodong", 4);
	assert(containerEuqal(s1, s2));

	s1.insert(0, 10, 'a');
	s2.insert(static_cast<size_t>(0), 10, 'a');
	assert(containerEuqal(s1, s2));

	s1.insert(s1.begin(), 'b');
	s2.insert(s2.begin(), 'b');
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase10()
{
	stdStr s1;
	MyString s2;
	
	s1.append("hello");
	s2.append("hello");
	assert(containerEuqal(s1, s2));

	s1.append("world", 2);
	s2.append("world", 2);
	assert(containerEuqal(s1, s2));
	
	s1.append(stdStr("fxd"));
	s2.append(MyString("fxd"));
	assert(containerEuqal(s1, s2));

	s1.append(10, 'a');
	s2.append(10, 'a');
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase11()
{
	stdStr s1;
	MyString s2;
	s1 += 'c';
	s2 += 'c';
	assert(containerEuqal(s1, s2));

	s1 += "hello";
	s2 += "hello";
	assert(containerEuqal(s1, s2));

	s1 += stdStr("fxd");
	s2 += MyString("fxd");
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase12()
{
	stdStr s1 = "hello world";
	MyString s2 = "hello world";

	s1.pop_back();
	s2.pop_back();
	assert(containerEuqal(s1, s2));

	s1.erase(s1.begin());
	s2.erase(s2.begin());
	assert(containerEuqal(s1, s2));

	s1.erase(2);
	s2.erase(2);
	assert(containerEuqal(s1, s2));

	s1.erase(s1.begin(), s1.end() - 1);
	s2.erase(s2.begin(), s2.end() - 1);
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase13()
{
	stdStr s1;
	MyString s2;
	s1.replace(0, 0, "hello");
	s2.replace(static_cast<size_t> (0), 0, "hello");
	assert(containerEuqal(s1, s2));

	s1.replace(s1.begin(), s1.end() - 1, "fxd");
	s2.replace(s2.begin(), s2.end() - 1, "fxd");
	assert(containerEuqal(s1, s2));

	s1.replace(2, 1, "hhhh", 2);
	s2.replace(2, 1, "hhhh", 2);
	assert(containerEuqal(s1, s2));

	s1.replace(0, 3, 3, 'c');
	s2.replace(0, 3, 3, 'c');
	assert(containerEuqal(s1, s2));
}

void StringTest::testCase14()
{
	stdStr s1, s3("hello");
	MyString s2, s4("hello");
	s1.swap(s3);
	s2.swap(s4);
	assert(containerEuqal(s1, s2));
	assert(containerEuqal(s3, s4));

	char s5[10];
	char s6[10];
	s1.copy(s5, 3, 0);
	s2.copy(s6, 3, 0);
	assert(s5[0] == s6[0] && s5[1] == s6[1] && s5[2] == s6[2]);
}

void StringTest::testCase15()
{
	MyString s = "hello I am the best man hello hhhh";
	MyString s1 = "hello";
	assert(s.find("hello") == 0);
	assert(s.find("hello", 2) == 24);
	assert(s.find('h') == 0);
	assert(s.find("mmm") == s.npos);
	s.replace(s.find(s1), s1.size(), "here");
	assert(containerEuqal(stdStr("here I am the best man hello hhhh"), s));
}

void StringTest::testCase16()
{
	MyString s = "hello I am the best man hello hhhh";
	MyString s1 = "hello";
	assert(s.rfind("hello") == 24);
	assert(s.rfind("hello", 2) == 24);
	assert(s.rfind('h') == s.size()-1);
	assert(s.rfind("mmm") == s.npos);
	s.replace(s.rfind(s1), s1.size(), "here");
	assert(containerEuqal(stdStr("hello I am the best man here hhhh"), s));
}

void StringTest::testCase17()
{
	MyString s = "hello I am the best man hello hhhh";
	assert(s.find_first_of("abc") == 8);
	assert(s.find_first_of('a', 3) == 8);
	assert(s.find_first_of("abc", 0, 2) == 8);
}

void StringTest::testCase18()
{
	MyString s = "hello I am the best ma";
	assert(s.find_last_of("abc") == 21);
	assert(s.find_last_of('a', 3) == 21);
	assert(s.find_last_of("bc", 15, 2) == s.npos);
}

void StringTest::testCase19()
{
	MyString s = "hello I am the best man hello hhhh";
	assert(s.find_first_not_of("abc") == 0);
	assert(s.find_first_not_of("hello", 0) == 5);
	assert(s.find_first_not_of("olleh", 0, 5) == 5);
	assert(s.find_first_not_of(s) == s.npos);
}

void StringTest::testCase20()
{
	MyString s = "hello";
	assert(s.find_last_not_of("abc") == 4);
	assert(s.find_last_not_of("hello", 2) == s.npos);
	assert(s.find_last_not_of("olleh", 0, 3) == 1);
}

void StringTest::testCase21()
{
	stdStr s1 = "my name is fxd";
	MyString s2 = "my name is fxd";

	assert(containerEuqal(s1.substr(), s2.substr()));
	assert(containerEuqal(s1.substr(2), s2.substr(2)));
	assert(containerEuqal(s1.substr(2, 5), s2.substr(2, 5)));
}

void StringTest::testCase22()
{
	MyString s1 = "hello this is cpp";
	MyString s2 = "hello this is cpp";
	assert(s1.compare(1, 1, s2) == -1);
	assert(s1.compare(s2) == 0);
	s2.insert(0, 'a');
	assert(s1.compare(s2) == 1);
	s2.erase(s2.begin(), s2.begin() + 2);
	assert(s1.compare(s2) == 1);
}

void StringTest::testCase23()
{
	MyString s1 = "this is cout test";
	stdStr s2 = "this";
	std::cout << s1 << std::endl;
	std::istringstream is(s2);
	MyString s3;
	is >> s3;
	std::cout << s3 << std::endl;
	assert(s3 == "this");
}

void StringTest::testCase24()
{
	MyString s1 = "fxd";
	MyString s2 = "I am ";
	assert(s2 + s1 == "I am fxd");
	MyString s3;
	assert(s1 + s3 == s1);
	assert(s1 != s3);
	assert(s3 != s2);
	assert(s3 == s3);
}

void StringTest::testCase25()
{
	MyString s1 = "aaaaabb";
	MyString s2 = "bbb";
	assert(s2 >= s1);
	assert(s2 > s1);
	assert(s1 <= s2);
	assert(s1 < s2);
}

void StringTest::testAll()
{
	testCase1();
	testCase2();
	testCase3();
	testCase4();
	testCase5();
	testCase6();
	testCase7();
	testCase8();
	testCase9();
	testCase10();
	testCase11();
	testCase12();
	testCase13();
	testCase14();
	testCase15();
	testCase16();
	testCase17();
	testCase18();
	testCase19();
	testCase20();
	testCase21();
	testCase22();
	testCase23();
	testCase24();
	testCase25();
}

bool StringTest::containerEuqal(stdStr str1, MyString str2)
{
	if (str1.size() != str2.size())
		return false;
	for (size_t i = 0; i < str1.size(); ++i)
	{
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

