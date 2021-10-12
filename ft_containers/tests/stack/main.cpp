#include "../../stack.hpp"

#include <stack>
#include <iostream>
#include <fstream>

void test_empty();
void test_size();
void test_top();
void test_push_and_pop();

std::ofstream outputfile;

int main(void)
{
	if (FT == 1)
		outputfile.open("output.ft.out");
	else
		outputfile.open("output.std.out");

	{
		outputfile << "\nTEST METHODS\n";

		NAMESPACE::stack<int> s;
		outputfile << "s.empty(): " << s.empty() << std::endl;
		outputfile << "s.size(): " << s.size() << std::endl;
		// outputfile << "s.top(): " << s.top() << std::endl; // both segfault
		s.push(1);
		outputfile << "s.empty(): " << s.empty() << std::endl;
		outputfile << "s.size(): " << s.size() << std::endl;
		outputfile << "s.top(): " << s.top() << std::endl;
		s.push(2);
		outputfile << "s.top(): " << s.top() << std::endl;
		s.push(3);
		outputfile << "s.top(): " << s.top() << std::endl;
		s.pop();
		outputfile << "s.top(): " << s.top() << std::endl;
		s.pop();
		outputfile << "s.top(): " << s.top() << std::endl;
		s.pop();
		// s.pop(); // std: segfault
		outputfile << "s.empty(): " << s.empty() << std::endl;
		outputfile << "s.size(): " << s.size() << std::endl;
	}
	{
		outputfile << "\nTEST RELATIONAL OPERATORS\n";

		NAMESPACE::stack<int> s1;
		s1.push(1);
		NAMESPACE::stack<int> s2(s1);
		outputfile << (s1 == s2) << std::endl;
		outputfile << (s1 < s2) << std::endl;
		outputfile << (s1 > s2) << std::endl;
		outputfile << (s1 <= s2) << std::endl;
		outputfile << (s1 >= s2) << std::endl;
		s2.push(2);
		outputfile << (s1 == s2) << std::endl;
		outputfile << (s1 < s2) << std::endl;
		outputfile << (s1 > s2) << std::endl;
		outputfile << (s1 <= s2) << std::endl;
		outputfile << (s1 >= s2) << std::endl;
	}

	outputfile << "\nRUN cplusplus.com CODE EXAMPLES\n";

	test_empty();
	test_size();
	test_top();
	test_push_and_pop();

	return (0);
}

void test_empty()
{
	NAMESPACE::stack<int> mystack;
	int sum(0);

	for (int i = 1; i <= 10; i++)
		mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	outputfile << "total: " << sum << '\n';
}

void test_size()
{
	NAMESPACE::stack<int> myints;
	outputfile << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 5; i++)
		myints.push(i);
	outputfile << "1. size: " << myints.size() << '\n';

	myints.pop();
	outputfile << "2. size: " << myints.size() << '\n';
}

void test_top()
{
	NAMESPACE::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	outputfile << "mystack.top() is now " << mystack.top() << '\n';
}

void test_push_and_pop()
{
	NAMESPACE::stack<int> mystack;

	for (int i = 0; i < 5; ++i)
		mystack.push(i);

	outputfile << "Popping out elements...";
	while (!mystack.empty())
	{
		outputfile << ' ' << mystack.top();
		mystack.pop();
	}
	outputfile << '\n';
}
