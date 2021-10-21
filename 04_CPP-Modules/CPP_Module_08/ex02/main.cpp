#include <iostream>
#include "MutantStack.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"

int main()
{
	std::cout << YELLOW << "FROM SUBJECT (INT)" << RESET << std::endl;
	{
		MutantStack<int> mstack;

		std::cout << "Push: 5" << std::endl;
		mstack.push(5);
		std::cout << "Push: 17" << std::endl;
		mstack.push(17);

		std::cout << "Pop: " << mstack.top() << std::endl;
		mstack.pop();

		std::cout << "Size of mstack: " << mstack.size() << std::endl;

		std::cout << "Push: 3" << std::endl;
		mstack.push(3);
		std::cout << "Push: 5" << std::endl;
		mstack.push(5);
		std::cout << "Push: 737" << std::endl;
		mstack.push(737);
		//[...]
		std::cout << "Push: 0" << std::endl;
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;
		std::cout << "mstack: ";
		while (it != ite)
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		std::cout << "s = mstack" << std::endl;
		std::stack<int> s(mstack);

		std::cout << YELLOW << "EXTRA" << RESET << std::endl;

		std::cout << "Size of s: " << s.size() << std::endl;
		while (!s.empty())
		{
			std::cout << "Pop: " << s.top() << std::endl;
			s.pop();
		}
		std::cout << "Size of s: " << s.size() << std::endl;
	}
	std::cout << YELLOW << "CHAR" << RESET << std::endl;
	{
		MutantStack<char> mstack;
		MutantStack<char>::iterator it;

		std::cout << "Push: a" << std::endl;
		mstack.push('a');
		std::cout << "Push: b" << std::endl;
		mstack.push('b');
		std::cout << "Push: c" << std::endl;
		mstack.push('c');
		std::cout << "Push: d" << std::endl;
		mstack.push('d');

		std::cout << "Size: " << mstack.size() << std::endl;
		std::cout << "Stack: ";
		for (it = mstack.begin(); it != mstack.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;

		while (!mstack.empty())
		{
			std::cout << "Pop: " << mstack.top() << std::endl;
			mstack.pop();
		}
		std::cout << "Size: " << mstack.size() << std::endl;
	}
	std::cout << YELLOW << "DOUBLE" << RESET << std::endl;
	{
		MutantStack<double> mstack;
		MutantStack<double>::iterator it;

		std::cout << "Push: 0.0" << std::endl;
		mstack.push(0.0);
		std::cout << "Push: 1.1" << std::endl;
		mstack.push(1.1);
		std::cout << "Push: 2.2" << std::endl;
		mstack.push(2.2);
		std::cout << "Push: 3.3" << std::endl;
		mstack.push(3.3);

		std::cout << "Size: " << mstack.size() << std::endl;
		std::cout << "Stack: ";
		for (it = mstack.begin(); it != mstack.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;

		while (!mstack.empty())
		{
			std::cout << "Pop: " << mstack.top() << std::endl;
			mstack.pop();
		}
		std::cout << "Size: " << mstack.size() << std::endl;
	}
	std::cout << YELLOW << "STRING" << RESET << std::endl;
	{
		MutantStack<std::string> mstack;
		MutantStack<std::string>::reverse_iterator it;

		std::cout << "Push: :D" << std::endl;
		mstack.push(":D");
		std::cout << "Push: fun!" << std::endl;
		mstack.push("fun!");
		std::cout << "Push: are" << std::endl;
		mstack.push("are");
		std::cout << "Push: Iterators" << std::endl;
		mstack.push("Iterators");

		std::cout << "Size: " << mstack.size() << std::endl;
		std::cout << "Stack (reversed): ";
		for (it = mstack.rbegin(); it != mstack.rend(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;

		while (!mstack.empty())
		{
			std::cout << "Pop: " << mstack.top() << std::endl;
			mstack.pop();
		}
		std::cout << "Size: " << mstack.size() << std::endl;
	}
	return 0;
}
