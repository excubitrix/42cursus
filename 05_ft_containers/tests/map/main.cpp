#include "../../map.hpp"

#include <map>
#include <iostream>
#include <fstream>

#define RESET "\033[0m"
#define YELLOW "\033[0;33m"

void test_constructors(void);
void test_assignment_operator(void);

void test_begin_end(void);
void test_rbegin_rend(void);

void test_empty(void);
void test_size(void);
void test_max_size(void);

void test_element_access_operator(void);

void test_insert(void);
void test_erase(void);
void test_swap(void);
void test_clear(void);

void test_key_comp(void);
void test_value_comp(void);

void test_find(void);
void test_count(void);
void test_lower_upper_bound(void);
void test_equal_range(void);

void test_get_allocator(void);


std::ofstream outputfile;

int main(void)
{
	if (FT == 1)
		outputfile.open("output.ft.out");
	else
		outputfile.open("output.std.out");
	
	outputfile << YELLOW "CONSTRUCTORS" RESET "\n";
	test_constructors();
	outputfile << YELLOW "ASSIGNMENT OPERATOR" RESET "\n";
	test_assignment_operator();

	outputfile << YELLOW "BEGIN | END" RESET "\n";
	test_begin_end();
	outputfile << YELLOW "RBEGIN | REND" RESET "\n";
	test_rbegin_rend();

	outputfile << YELLOW "EMPTY" RESET "\n";
	test_empty();
	outputfile << YELLOW "SIZE" RESET "\n";
	test_size();
	outputfile << YELLOW "MAX SIZE" RESET "\n";
	test_max_size();

	outputfile << YELLOW "OPERATOR[]" RESET "\n";
	test_element_access_operator();

	outputfile << YELLOW "INSERT" RESET "\n";
	test_insert();
	outputfile << YELLOW "ERASE" RESET "\n";
	test_erase();
	outputfile << YELLOW "SWAP" RESET "\n";
	test_swap();
	outputfile << YELLOW "CLEAR" RESET "\n";
	test_clear();

	outputfile << YELLOW "KEY COMP" RESET "\n";
	test_key_comp();
	outputfile << YELLOW "VALUE COMP" RESET "\n";
	test_value_comp();

	outputfile << YELLOW "FIND" RESET "\n";
	test_find();
	outputfile << YELLOW "COUNT" RESET "\n";
	test_count();
	outputfile << YELLOW "LOWER | UPPER BOUND" RESET "\n";
	test_lower_upper_bound();
	outputfile << YELLOW "EQUAL RANGE" RESET "\n";
	test_equal_range();

	outputfile << YELLOW "GET ALLOCATOR" RESET "\n";
	test_get_allocator();

	return 0;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

void test_constructors(void)
{

	NAMESPACE::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	NAMESPACE::map<char, int> second(first.begin(), first.end());

	NAMESPACE::map<char, int> third(second);

	NAMESPACE::map<char, int, classcomp> fourth; // class as Compare

	bool (*fn_pt)(char, char) = fncomp;
	NAMESPACE::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare

	// show content:
	outputfile << "first\n";
	for (NAMESPACE::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
	outputfile << "second\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
	outputfile << "third\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
	outputfile << "fourth\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
	outputfile << "fifth\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_assignment_operator(void)
{
	NAMESPACE::map<char, int> first;
	NAMESPACE::map<char, int> second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;				  // second now contains 3 ints
	first = NAMESPACE::map<char, int>(); // and first is now empty

	outputfile << "Size of first: " << first.size() << '\n';
	outputfile << "Size of second: " << second.size() << '\n';
}

void test_begin_end(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_rbegin_rend(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	NAMESPACE::map<char, int>::reverse_iterator rit;
	for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
		outputfile << rit->first << " => " << rit->second << '\n';
}

void test_empty(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;

	while (!mymap.empty())
	{
		outputfile << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

void test_size(void)
{
	NAMESPACE::map<char, int> mymap;
	mymap['a'] = 101;
	mymap['b'] = 202;
	mymap['c'] = 302;

	outputfile << "mymap.size() is " << mymap.size() << '\n';
}

void test_max_size(void)
{
	int i;
	NAMESPACE::map<int, int> mymap;

	if (mymap.max_size() > 1000)
	{
		for (i = 0; i < 1000; i++)
			mymap[i] = 0;
		outputfile << "The map contains 1000 elements.\n";
	}
	else
		outputfile << "The map could not hold 1000 elements.\n";
}

void test_element_access_operator(void)
{
	NAMESPACE::map<char, std::string> mymap;

	mymap['a'] = "an element";
	mymap['b'] = "another element";
	mymap['c'] = mymap['b'];

	outputfile << "mymap['a'] is " << mymap['a'] << '\n';
	outputfile << "mymap['b'] is " << mymap['b'] << '\n';
	outputfile << "mymap['c'] is " << mymap['c'] << '\n';
	outputfile << "mymap['d'] is " << mymap['d'] << '\n';

	outputfile << "mymap now contains " << mymap.size() << " elements.\n";
}

void test_insert(void)
{
	NAMESPACE::map<char, int> mymap;

	// first insert function version (single parameter):
	mymap.insert(NAMESPACE::pair<char, int>('a', 100));
	mymap.insert(NAMESPACE::pair<char, int>('z', 200));

	NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(NAMESPACE::pair<char, int>('z', 500));
	if (ret.second == false)
	{
		outputfile << "element 'z' already existed";
		outputfile << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	NAMESPACE::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, NAMESPACE::pair<char, int>('b', 300)); // max efficiency inserting
	mymap.insert(it, NAMESPACE::pair<char, int>('c', 400)); // no max efficiency inserting
	outputfile << "size:\n"
			  << mymap.size() << '\n';

	// third insert function version (range insertion):
	NAMESPACE::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	outputfile << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';

	outputfile << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_erase(void)
{
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::map<char, int>::iterator it;

	// insert some values:
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	it = mymap.find('b');
	mymap.erase(it); // erasing by iterator

	mymap.erase('c'); // erasing by key

	it = mymap.find('e');
	mymap.erase(it, mymap.end()); // erasing by range

	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_swap(void)
{
	NAMESPACE::map<char, int> foo, bar;

	foo['x'] = 100;
	foo['y'] = 200;

	bar['a'] = 11;
	bar['b'] = 22;
	bar['c'] = 33;

	foo.swap(bar);

	outputfile << "foo contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';

	outputfile << "bar contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_clear(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	outputfile << "mymap contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a'] = 1101;
	mymap['b'] = 2202;

	outputfile << "mymap contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_key_comp(void)
{
	NAMESPACE::map<char, int> mymap;

	NAMESPACE::map<char, int>::key_compare mycomp = mymap.key_comp();

	mymap['a'] = 100;
	mymap['b'] = 200;
	mymap['c'] = 300;

	outputfile << "mymap contains:\n";

	char highest = mymap.rbegin()->first; // key value of last element

	NAMESPACE::map<char, int>::iterator it = mymap.begin();
	do
	{
		outputfile << it->first << " => " << it->second << '\n';
	} while (mycomp((*it++).first, highest));
}

void test_value_comp(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['x'] = 1001;
	mymap['y'] = 2002;
	mymap['z'] = 3003;

	outputfile << "mymap contains:\n";

	NAMESPACE::pair<char, int> highest = *mymap.rbegin(); // last element

	NAMESPACE::map<char, int>::iterator it = mymap.begin();
	do
	{
		outputfile << it->first << " => " << it->second << '\n';
	} while (mymap.value_comp()(*it++, highest));
}

void test_find(void)
{
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::map<char, int>::iterator it;

	mymap['a'] = 50;
	mymap['b'] = 100;
	mymap['c'] = 150;
	mymap['d'] = 200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase(it);

	// print content:
	outputfile << "elements in mymap:" << '\n';
	outputfile << "a => " << mymap.find('a')->second << '\n';
	outputfile << "c => " << mymap.find('c')->second << '\n';
	outputfile << "d => " << mymap.find('d')->second << '\n';
}

void test_count(void)
{
	NAMESPACE::map<char, int> mymap;
	char c;

	mymap['a'] = 101;
	mymap['c'] = 202;
	mymap['f'] = 303;

	for (c = 'a'; c < 'h'; c++)
	{
		outputfile << c;
		if (mymap.count(c) > 0)
			outputfile << " is an element of mymap.\n";
		else
			outputfile << " is not an element of mymap.\n";
	}
}

void test_lower_upper_bound(void)
{
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::map<char, int>::iterator itlow, itup;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	itlow = mymap.lower_bound('b'); // itlow points to b
	itup = mymap.upper_bound('d');	// itup points to e (not d!)

	mymap.erase(itlow, itup); // erases [itlow,itup)

	// print content:
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		outputfile << it->first << " => " << it->second << '\n';
}

void test_equal_range(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;

	NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, NAMESPACE::map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');

	outputfile << "lower bound points to: ";
	outputfile << ret.first->first << " => " << ret.first->second << '\n';

	outputfile << "upper bound points to: ";
	outputfile << ret.second->first << " => " << ret.second->second << '\n';
}

void test_get_allocator(void)
{
	int psize;
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::pair<const char, int> *p;

	// allocate an array of 5 elements using mymap's allocator:
	p = mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(NAMESPACE::map<char, int>::value_type) * 5;

	outputfile << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p, 5);
}
