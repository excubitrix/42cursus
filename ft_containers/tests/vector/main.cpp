#include "../../vector.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

void test_constructors();
void test_assignment_operator();
void test_begin();
void test_end();
void test_rbegin();
void test_rend();
void test_size();
void test_max_size();
void test_resize();
void test_capacity();
void test_empty();
void test_reserve();
void test_subscript_operator();
void test_at();
void test_front();
void test_back();
void test_assign();
void test_push_back();
void test_pop_back();
void test_insert();
void test_erase();
void test_swap_member();
void test_clear();
void test_get_allocator();
void test_swap_non_member();
void test_lexicographical_compare();
void test_enable_if_and_is_integral();
void test_reverse_iterator_relational_operators();

std::ofstream outputfile;

template <class T>
void print_vector(NAMESPACE::vector<T> v)
{
	typename NAMESPACE::vector<T>::iterator it;

	for (it = v.begin(); it != v.end(); it++)
		outputfile << *it << ", ";
	outputfile << std::endl;
}

int main(void)
{
	if (FT == 1)
		outputfile.open("output.ft.out");
	else
		outputfile.open("output.std.out");

	NAMESPACE::vector<int> v_int_100;
	for (int i = 0; i < 100; i++)
		v_int_100.push_back(i);
	print_vector(v_int_100);
	
	/* --- CONSTRUCTORS & CAPACITY --- */
	{
		outputfile << YELLOW "fill constructor" RESET << std::endl;
		
		NAMESPACE::vector<int> v((unsigned int)3, 100);
		outputfile << "v.front(): " << v.front() << std::endl;
		outputfile << "v.back(): " << v.back() << std::endl;
		outputfile << "v.size(): " << v.size() << std::endl;
		outputfile << "v.capacity(): " << v.capacity() << std::endl;
	}
	{
		outputfile << YELLOW "range constructor (int)" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin(), v_int_100.end());
		outputfile << "v.front(): " << v.front() << std::endl;
		outputfile << "v.back(): " << v.back() << std::endl;
		outputfile << "v.size(): " << v.size() << std::endl;
		outputfile << "v.capacity(): " << v.capacity() << std::endl;
	}
	{
		outputfile << YELLOW "range constructor (string)" RESET << std::endl;
		
		NAMESPACE::vector<std::string> v1;
		v1.push_back("one");
		v1.push_back("two");
		v1.push_back("three");
		NAMESPACE::vector<std::string> v2(v1.begin(), v1.end());
		outputfile << "v2.front(): " << v2.front() << std::endl;
		outputfile << "v2.back(): " << v2.back() << std::endl;
	}
	{
		outputfile << YELLOW "assignment operator" RESET << std::endl;
		
		NAMESPACE::vector<int> v1(v_int_100.begin() + 5, v_int_100.begin() + 15);
		NAMESPACE::vector<int> v2;
		outputfile << "v2.empty(): " << v2.empty() << std::endl;
		v2 = v1;
		outputfile << "v2.empty(): " << v2.empty() << std::endl;
		outputfile << "v2.at(0): " << v2.at(0) << std::endl;
		outputfile << "v2.at(9): " << v2.at(9) << std::endl;
		outputfile << "v2.size(): " << v2.size() << std::endl;
		outputfile << "v2.capacity(): " << v2.capacity() << std::endl;
	}
	{
		outputfile << YELLOW "copy constructor" RESET << std::endl;
		
		NAMESPACE::vector<int> v1(v_int_100.begin() + 5, v_int_100.begin() + 15);
		NAMESPACE::vector<int> v2(v1);
		outputfile << "v2.at(0): " << v2.at(0) << std::endl;
		outputfile << "v2.at(9): " << v2.at(9) << std::endl;
		outputfile << "v2.size(): " << v2.size() << std::endl;
		outputfile << "v2.capacity(): " << v2.capacity() << std::endl;
	}
	
	/* --- CAPACITY --- */
	
	{
		// std::vector<char> v_char;
		// outputfile << "sizeof(char): " << sizeof(char) << std::endl;
		// outputfile << "9223372036854775807 / sizeof(char): " << 9223372036854775807 / sizeof(char) << std::endl;
		// outputfile << "sizeof(int): " << sizeof(int) << std::endl;
		// outputfile << "9223372036854775807 / sizeof(int): " << 9223372036854775807 / sizeof(int) << std::endl;
		// outputfile << "sizeof(std::string): " << sizeof(std::string) << std::endl;
		// outputfile << "9223372036854775807 / sizeof(std::string): " << 9223372036854775807 / sizeof(int) << std::endl;
		// outputfile << "v_char.max_size(): " << v_char.max_size() << std::endl;
		// std::vector<int> v_int;
		// outputfile << "v_int.max_size(): " << v_int.max_size() << std::endl;
		// std::vector<std::string> v_str;
		// outputfile << "v_str.max_size(): " << v_str.max_size() << std::endl;
	}
	{
		// outputfile << YELLOW "max_size" RESET << std::endl;
		// unsigned long size;
		// NAMESPACE::vector<char> v_char;
		// size = v_char.max_size();
		// outputfile << "v_char.max_size(): " << size << std::endl;
		
		// NAMESPACE::vector<int> v_int;
		// size = v_int.max_size();
		// outputfile << "v_int.max_size(): " << size << std::endl;

		// NAMESPACE::vector<std::string> v_str;
		// size =v_str.max_size();
		// outputfile << "v_str.max_size(): " << size << std::endl;
	}
	{
		outputfile << YELLOW "reserve" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 1, v_int_100.begin() + 6);
		outputfile << "v.capacity(): " << v.capacity() << std::endl;
		v.reserve(3);
		outputfile << "v.capacity(): " << v.capacity() << std::endl;
		v.reserve(13);
		outputfile << "v.capacity(): " << v.capacity() << std::endl;
	}
	
	/* --- ELEMENT ACCESS --- */
	
	{
		outputfile << YELLOW "front" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 1, v_int_100.begin() + 6);
		outputfile << "v.front(): " << v.front() << std::endl;
		int &front = v.front();
		front++;
		outputfile << "v.front(): " << v.front() << std::endl;
	}
	{
		outputfile << YELLOW "const front" RESET << std::endl;

		const NAMESPACE::vector<int> const_v(v_int_100.begin() + 1, v_int_100.begin() + 6);
		const int &const_front = const_v.front();
		(void)const_front;
		outputfile << "const_v.front(): " << const_v.front() << std::endl;
	}
	{
		outputfile << YELLOW "back" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 1, v_int_100.begin() + 6);
		outputfile << "v.back(): " << v.back() << std::endl;
		int &back = v.back();
		back++;
		outputfile << "v.back(): " << v.back() << std::endl;
	}
	{
		outputfile << YELLOW "const back" RESET << std::endl;
	
		const NAMESPACE::vector<int> const_v(v_int_100.begin() + 1, v_int_100.begin() + 6);
		const int &const_back = const_v.back();
		(void)const_back;
		outputfile << "const_v.back(): " << const_v.back() << std::endl;
	}

	/* --- MODIFIERS --- */

	{
		outputfile << YELLOW "assign (int)" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 6, v_int_100.begin() + 11);
		outputfile << "v.back(): " << v.back() << std::endl;
		v.assign(v_int_100.begin() + 1, v_int_100.begin() + 16);
		outputfile << "v.front(): " << v.front() << std::endl;
		outputfile << "v.back(): " << v.back() << std::endl;
		outputfile << "v.size(): " << v.size() << std::endl;
		outputfile << "v.capacity(): " << v.capacity() << std::endl;
	}
	{
		outputfile << YELLOW "push_back (inc capacity expansion)" RESET << std::endl;
		ft::vector<int> v;
		
		v.push_back(1);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 1);
		
		v.push_back(2);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 2);
		
		v.push_back(3);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 4);
		
		v.push_back(4);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 4);
		
		v.push_back(5);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 8);
		
		v.push_back(6);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 8);
		
		v.push_back(7);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 8);
		
		v.push_back(8);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 8);
		
		v.push_back(9);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 16);
		
		v.push_back(10);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 16);
		
		v.push_back(11);
		outputfile << "v.size(): " << v.size() << std::endl;
		assert(v.capacity() == 16);
	}
	{
		outputfile << YELLOW "push_back & pop_back" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(3);
		v.push_back(6);
		v.push_back(9);

		outputfile << "v.front(): " << v.front() << std::endl;
		outputfile << "v.back(): " << v.back() << std::endl;
		outputfile << "v.size(): " << v.size() << std::endl;
		
		assert(v.capacity() == 4);
		
		v.pop_back();
		
		outputfile << "v.front(): " << v.front() << std::endl;
		outputfile << "v.back(): " << v.back() << std::endl;
		outputfile << "v.size(): " << v.size() << std::endl;
		
		assert(v.capacity() == 4);
	}

	/* --- ITERATOR --- */ 
	
	{
		// Is default-constructible, copy-constructible, copy-assignable and destructible
		// X a
		// X b(a)
		// b = a
		
		outputfile << YELLOW "iterator ctors, operator= & dtor" RESET << std::endl;
		
		// default-constructor
		NAMESPACE::vector<int>::iterator it1;
		// copy-constructor
		NAMESPACE::vector<int>::iterator it2(it1);
		// operator=
		it2 = it1;
		NAMESPACE::vector<int> v(v_int_100.begin() + 5, v_int_100.begin() + 8);
		// parameter constructor
		NAMESPACE::vector<int>::iterator it3 = v.begin();
		NAMESPACE::vector<int>::iterator it4(it3);
		outputfile << *it4 << std::endl;
	}
	{
		// Is default-constructible, copy-constructible, copy-assignable and destructible
		// X a
		// X b(a)
		// b = a
		
		outputfile << YELLOW "const_iterator ctors, operator= & dtor" RESET << std::endl;
		
		// default-constructor
		NAMESPACE::vector<int>::const_iterator it1;
		// copy-constructor
		NAMESPACE::vector<int>::const_iterator it2(it1);
		// operator=
		it2 = it1;
		NAMESPACE::vector<int> v(v_int_100.begin() + 5, v_int_100.begin() + 8);
		// parameter constructor
		NAMESPACE::vector<int>::const_iterator it3 = v.begin();
		NAMESPACE::vector<int>::const_iterator it4(it3);
		assert(*it4 == 5);
		outputfile << *it4 << std::endl;
	}
	{
		// Can be compared for equivalence using the equality/inequality operators
		// (meaningful when both iterator values iterate over the same underlying sequence).
		// a == b
		// a != b
		
		outputfile << YELLOW "comparison" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 5, v_int_100.begin() + 8);
		NAMESPACE::vector<int>::iterator it1 = v.begin();
		NAMESPACE::vector<int>::iterator it2 = v.begin();
		assert(it1 == it2);
		it2++;
		assert(it1 != it2);
	}
	{
		// Can be dereferenced as an rvalue (if in a dereferenceable state).
		// *a
		// a->m
		
		outputfile << YELLOW "*it" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 5, v_int_100.begin() + 8);
		NAMESPACE::vector<int>::iterator it = v.begin();
		outputfile << "*it: " << *it << std::endl;
	}
	{
		// For mutable iterators (non-constant iterators):
		// Can be dereferenced as an lvalue (if in a dereferenceable state).
		// *a = t
		
		outputfile << YELLOW "*it" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 5, v_int_100.begin() + 8);
		NAMESPACE::vector<int>::iterator it = v.begin();
		outputfile << "*it: " << *it << std::endl;
		*it = 123;
		outputfile << "*it: " << *it << std::endl;
		outputfile << "*v.begin(): " << *it << std::endl;
	}
	{
		// Can be incremented (if in a dereferenceable state).
		// The result is either also dereferenceable or a past-the-end iterator.
		// Two iterators that compare equal, keep comparing equal after being both increased.
		// ++a
		// a++
		// *a++

		outputfile << YELLOW "increment & decrement" RESET << std::endl;
		
		NAMESPACE::vector<int> v(v_int_100.begin() + 5, v_int_100.begin() + 8);
		NAMESPACE::vector<int>::iterator it = v.begin();
		outputfile << "*it: " << *it << std::endl;
		outputfile << "*it: " << *++it << std::endl;
		outputfile << "*it: " << *it++ << std::endl;
		outputfile << "*it: " << *it << std::endl;
		
		it++;
		// outputfile << "*it: " << *it << std::endl; // invalid read; UB; could segfault
		
		// Can be decremented (if a dereferenceable iterator value precedes it).
		// --a
		// a--
		// *a--
		
		outputfile << "*it: " << *--it << std::endl;
		outputfile << "*it: " << *it-- << std::endl;
		outputfile << "*it: " << *it << std::endl;
	}
	{
		// Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
		// it + n
		// n + it
		// it - n
		// it - it
		
		outputfile << YELLOW "arithmetic operators + and -" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(6);
		NAMESPACE::vector<int>::iterator it = v.begin();
		NAMESPACE::vector<int>::iterator it2 = it + 1; // it + n
		outputfile << "*it2: " << *it2 << std::endl;

		it2 = 1 + it2; // n + it
		outputfile << "*it2: " << *it2 << std::endl;

		it2 = it2 - 1; // it - n
		outputfile << "*it2: " << *it2 << std::endl;

		it2 = v.begin() + 2;
		int dif = it - it2; // it - it
		outputfile << dif << std::endl;

		dif = it2 - it;
		outputfile << dif << std::endl;

		NAMESPACE::vector<int>::const_iterator it3(it2);
		outputfile << (it - it3) << std::endl;

	}
	{
		// Can be compared with inequality relational operators (<, >, <= and >=).
		// a < b
		// a > b
		// a <= b
		// a >= b
		
		outputfile << YELLOW "<, >, <=, >=" RESET << std::endl;

		NAMESPACE::vector<int> v;
		v.push_back(3);
		v.push_back(1);

		NAMESPACE::vector<int>::iterator it1 = v.begin();
		NAMESPACE::vector<int>::iterator it2 = v.begin() + 1;

		outputfile << bool(it1 < it2) << std::endl;
		outputfile << bool(it2 < it1) << std::endl;
		
		outputfile << bool(it1 > it2) << std::endl;
		outputfile << bool(it2 > it1) << std::endl;

		outputfile << bool(it1 >= it2) << std::endl;
		outputfile << bool(it2 >= it1) << std::endl;
		
		it1++;
		outputfile << bool(it1 >= it2) << std::endl;
		outputfile << bool(it2 >= it1) << std::endl;
		
		outputfile << bool(it1 <= it2) << std::endl;
		outputfile << bool(it2 <= it1) << std::endl;
	}
	{
		// Supports compound assignment operations += and -=
		// a += n
		// a -= n
		
		outputfile << YELLOW "+=, -=" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);

		NAMESPACE::vector<int>::iterator it = v.begin();
		it += 1;
		outputfile << *it << std::endl;

		it -= 1;
		outputfile << *it << std::endl;
	}
	{
		// Supports the offset dereference operator ([])
		// a[n]
		
		outputfile << YELLOW "it[n]" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(6);

		NAMESPACE::vector<int>::iterator it = v.begin();
		outputfile << "*it[0]: " << it[0] << std::endl;
		outputfile << "*it[1]: " << it[1] << std::endl;
		outputfile << "*it[2]: " << it[2] << std::endl;
		it[2] = 9;
		outputfile << "*it[2]: " << it[2] << std::endl;
	}



	{
		outputfile << YELLOW "insert (single element)" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(6);
		NAMESPACE::vector<int>::iterator it;

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		it = v.begin() + 1;
		v.insert(it, 2);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		it = v.begin();
		v.insert(it, 0);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		it = v.end();
		v.insert(it, 7);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;
	}
	{
		outputfile << YELLOW "insert (fill)" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(6);
		NAMESPACE::vector<int>::iterator it = v.begin() + 1;

		v.insert(it, (size_t)3, -2);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		it = v.begin();
		v.insert(it, (size_t)2, 0);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		
		it = v.end();
		v.insert(it, (size_t)4, 9);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;
	}
	{
		outputfile << YELLOW "insert (range)" RESET << std::endl;
		
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(6);

		NAMESPACE::vector<int>::iterator it = v.begin();
		// 1, 3, 6
		//^
		//1
		// 1, 1, 3, 6
		v.insert(it, v.begin(), v.begin() + 1);

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		it = v.begin() + 3;
		v.insert(it, v.begin() + 1, v.end());
		// 1, 1, 3, 6
		//         ^
		//         1, 3, 6
		// 1, 1, 3, 1, 3, 6, 6

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;

		it = v.end();
		v.insert(it, v.begin() + 1, v.end() - 1);
		// 1, 1, 3, 1, 3, 6, 6
		//                    ^
		// 					  1, 3, 1, 3, 6
		// 1, 1, 3, 1, 3, 6, 6, 1, 3, 1, 3, 6

		for (it = v.begin(); it != v.end(); it++)
			outputfile << *it << ", ";
		outputfile << std::endl;
	}
	{
		outputfile << YELLOW "erase (single element)" RESET << std::endl;

		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(6);
		v.push_back(9);

		NAMESPACE::vector<int>::iterator it;
		print_vector(v);
		assert(v.size() == 4);

		it = v.begin();
		v.erase(it);
		print_vector(v);
		assert(v.size() == 3);

		it = v.begin() + 1;
		v.erase(it);
		print_vector(v);
		assert(v.size() == 2);

		// it = v.end(); // exception
		it = v.end() - 1;
		v.erase(it);
		print_vector(v);
		assert(v.size() == 1);
	}
	{
		outputfile << YELLOW "erase (range)" RESET << std::endl;

		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		NAMESPACE::vector<int>::iterator it = v.erase(v.begin(), v.begin());
		assert(*it == 1);
		outputfile << "erase returned: " << *it << std::endl;
		print_vector(v);
		
		it = v.erase(v.begin(), v.begin() + 1);
		outputfile << "erase returned: " << *it << std::endl;
		print_vector(v);

		it = v.erase(v.begin() + 2, v.end());
		assert(*it == 4);
		outputfile << "erase returned: " << *it << std::endl;
		print_vector(v);
	}
	{
		outputfile << YELLOW "swap" RESET << std::endl;

		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		NAMESPACE::vector<int>::iterator it = v.begin();
		outputfile << *it << std::endl;

		NAMESPACE::vector<int> v2;
		v2.push_back(6);
		v2.push_back(7);
		v2.push_back(8);
		v2.push_back(9);
		v2.push_back(10);

		NAMESPACE::vector<int>::iterator it2 = v2.begin();
		outputfile << *it2 << std::endl;

		v.swap(v2);

		outputfile << *it << std::endl;
		outputfile << *it2 << std::endl;
		
		print_vector(v);
		print_vector(v2);
	}
	{
		outputfile << YELLOW "get_allocator" RESET << std::endl;
		NAMESPACE::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

		outputfile << "The allocated array contains:";
		for (i=0; i<5; i++) outputfile << ' ' << p[i];
		outputfile << '\n';

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}

	/* --- RELATIONAL OPERATORS (VECTOR) --- */

	{
		outputfile << YELLOW "relational operator: v == v, v != v" RESET << std::endl;
		NAMESPACE::vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		NAMESPACE::vector<int> v2(v1);
		v2.push_back(4);
		
		if (v1 == v2)
			outputfile << "v1 and v2 are equal\n";
		
		if (v1 != v2)
			outputfile << "v1 and v2 are not equal\n";

		v2.pop_back();

		if (v1 == v2)
			outputfile << "v1 and v2 are equal\n";
		
		if (v1 != v2)
			outputfile << "v1 and v2 are not equal\n";
	}
	{
		outputfile << YELLOW "relational operator: v < v" RESET << std::endl;
		NAMESPACE::vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		NAMESPACE::vector<int> v2(v1);
		v2.push_back(4); // v2 is now longer than v1

		if (v1 < v2) outputfile << "v1 is smaller than v2\n";
		else outputfile << "v1 is not smaller than v2\n";
		
		if (v2 < v1) outputfile << "v2 is smaller than v1\n";
		else outputfile << "v2 is not smaller than v1\n";

		v2.pop_back(); // v2 is now the same length as v1

		if (v1 < v2) outputfile << "v1 is smaller than v2\n";
		else outputfile << "v1 is not smaller than v2\n";
		
		if (v2 < v1) outputfile << "v2 is smaller than v1\n";
		else outputfile << "v2 is not smaller than v1\n";
		
		v2.pop_back(); // v2 is now smaller than v1

		if (v1 < v2) outputfile << "v1 is smaller than v2\n";
		else outputfile << "v1 is not smaller than v2\n";
		
		if (v2 < v1) outputfile << "v2 is smaller than v1\n";
		else outputfile << "v2 is not smaller than v1\n";
	}
	{
		outputfile << YELLOW "relational operator: v > v" RESET << std::endl;
		NAMESPACE::vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		NAMESPACE::vector<int> v2(v1);
		v2.push_back(4); // v2 is now longer than v1

		if (v1 > v2) outputfile << "v1 is greater than v2\n";
		else outputfile << "v1 is not greater than v2\n";
		
		if (v2 > v1) outputfile << "v2 is greater than v1\n";
		else outputfile << "v2 is not greater than v1\n";

		v2.pop_back(); // v2 is now the same length as v1

		if (v1 > v2) outputfile << "v1 is greater than v2\n";
		else outputfile << "v1 is not greater than v2\n";
		
		if (v2 > v1) outputfile << "v2 is greater than v1\n";
		else outputfile << "v2 is not greater than v1\n";
		
		v2.pop_back(); // v2 is now greater than v1

		if (v1 > v2) outputfile << "v1 is greater than v2\n";
		else outputfile << "v1 is not greater than v2\n";
		
		if (v2 > v1) outputfile << "v2 is greater than v1\n";
		else outputfile << "v2 is not greater than v1\n";
	}
	{
		outputfile << YELLOW "relational operator: v <= v" RESET << std::endl;
		NAMESPACE::vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		NAMESPACE::vector<int> v2(v1);
		v2.push_back(4); // v2 is now longer than v1

		if (v1 <= v2) outputfile << "v1 is smaller or equal to v2\n";
		else outputfile << "v1 is not smaller or equal to v2\n";
		
		if (v2 <= v1) outputfile << "v2 is smaller or equal to v1\n";
		else outputfile << "v2 is not smaller or equal to v1\n";

		v2.pop_back(); // v2 is now the same length as v1

		if (v1 <= v2) outputfile << "v1 is smaller or equal to v2\n";
		else outputfile << "v1 is not smaller or equal to v2\n";
		
		if (v2 <= v1) outputfile << "v2 is smaller or equal to v1\n";
		else outputfile << "v2 is not smaller or equal to v1\n";
		
		v2.pop_back(); // v2 is now smaller or equal to v1

		if (v1 <= v2) outputfile << "v1 is smaller or equal to v2\n";
		else outputfile << "v1 is not smaller or equal to v2\n";
		
		if (v2 <= v1) outputfile << "v2 is smaller or equal to v1\n";
		else outputfile << "v2 is not smaller or equal to v1\n";
	}
	{
		outputfile << YELLOW "relational operator: v >= v" RESET << std::endl;
		NAMESPACE::vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		NAMESPACE::vector<int> v2(v1);
		v2.push_back(4); // v2 is now longer than v1

		if (v1 >= v2) outputfile << "v1 is greater or equal to v2\n";
		else outputfile << "v1 is not greater or equal to v2\n";
		
		if (v2 >= v1) outputfile << "v2 is greater or equal to v1\n";
		else outputfile << "v2 is not greater or equal to v1\n";

		v2.pop_back(); // v2 is now the same length as v1

		if (v1 >= v2) outputfile << "v1 is greater or equal to v2\n";
		else outputfile << "v1 is not greater or equal to v2\n";
		
		if (v2 >= v1) outputfile << "v2 is greater or equal to v1\n";
		else outputfile << "v2 is not greater or equal to v1\n";
		
		v2.pop_back(); // v2 is now greater or equal to v1

		if (v1 >= v2) outputfile << "v1 is greater or equal to v2\n";
		else outputfile << "v1 is not greater or equal to v2\n";
		
		if (v2 >= v1) outputfile << "v2 is greater or equal to v1\n";
		else outputfile << "v2 is not greater or equal to v1\n";
	}
	{
		outputfile << YELLOW "swap" RESET << std::endl;

		NAMESPACE::vector<int>foo((size_t)3,100);
		NAMESPACE::vector<int>bar((size_t)5,200);

		foo.swap(bar);

		outputfile << "foo contains:";
		for (NAMESPACE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			outputfile << ' ' << *it;
		outputfile << '\n';

		outputfile << "bar contains:";
		for (NAMESPACE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			outputfile << ' ' << *it;
		outputfile << '\n';
	}
	{
		outputfile << YELLOW "reverse iterator" RESET << std::endl;

		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		NAMESPACE::vector<int>::reverse_iterator r_it = v.rbegin();
		outputfile << "*r_it: '" << *r_it << "'" << std::endl;
		r_it++;
		outputfile << "*r_it: '" << *r_it << "'" << std::endl;
		r_it = v.rend();
		r_it--;
		outputfile << "*r_it: '" << *r_it << "'" << std::endl;

		for (r_it = v.rbegin(); r_it != v.rend(); r_it++)
			outputfile << *r_it << ", ";
		outputfile << std::endl;
	}

	test_constructors();
	test_assignment_operator();
	test_begin();
	test_end();
	test_rbegin();
	test_rend();
	test_size();
	test_max_size();
	test_resize();
	test_capacity();
	test_empty();
	// test_reserve(); // works but capacity grows differently
	test_subscript_operator();
	test_at();
	test_front();
	test_back();
	test_assign();
	// test_push_back(); // use cin
	test_pop_back();
	test_insert();
	test_erase();
	test_swap_member();
	test_clear();
	test_get_allocator();
	test_swap_non_member();
	test_lexicographical_compare();
	test_enable_if_and_is_integral();
	test_reverse_iterator_relational_operators();
}

void test_constructors()
{
	outputfile << "\ntest_constructors\n";
	// constructors used in the same order as described above:
	NAMESPACE::vector<int> first;                               // empty vector of ints
	NAMESPACE::vector<int> second((size_t)4, 100);              // four ints with value 100
	NAMESPACE::vector<int> third(second.begin(), second.end()); // iterating through second
	NAMESPACE::vector<int> fourth(third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16, 2, 77, 29};
	NAMESPACE::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	outputfile << "The contents of fifth are:";
	for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

void test_assignment_operator()
{
	outputfile << "\ntest_assignment_operator\n";
	NAMESPACE::vector<int> foo(3, 0);
	NAMESPACE::vector<int> bar(5, 0);

	bar = foo;
	foo = NAMESPACE::vector<int>();

	outputfile << "Size of foo: " << int(foo.size()) << '\n';
	outputfile << "Size of bar: " << int(bar.size()) << '\n';
}

void test_begin()
{
	outputfile << "\ntest_begin\n";
	NAMESPACE::vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	outputfile << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

void test_end()
{
	outputfile << "\ntest_end\n";
	NAMESPACE::vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	outputfile << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

void test_rbegin()
{
	outputfile << "\ntest_rbegin\n";
	NAMESPACE::vector<int> myvector(5); // 5 default-constructed ints

	int i = 0;

	NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit != myvector.rend(); ++rit)
		*rit = ++i;

	outputfile << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

void test_rend()
{
	outputfile << "\ntest_rend\n";
	NAMESPACE::vector<int> myvector(5); // 5 default-constructed ints

	NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i = 0;
	for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
		*rit = ++i;

	outputfile << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

void test_size()
{
	outputfile << "\ntest_size\n";
	NAMESPACE::vector<int> myints;
	outputfile << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 10; i++)
		myints.push_back(i);
	outputfile << "1. size: " << myints.size() << '\n';

	myints.insert(myints.end(), 10, 100);
	outputfile << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	outputfile << "3. size: " << myints.size() << '\n';
}

void test_max_size()
{
	outputfile << "\ntest_max_size\n";
	NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i = 0; i < 100; i++)
		myvector.push_back(i);

	outputfile << "size: " << myvector.size() << "\n";
	// outputfile << "capacity: " << myvector.capacity() << "\n";
	// outputfile << "max_size: " << myvector.max_size() << "\n";
}

void test_resize()
{
	outputfile << "\ntest_resize\n";
	NAMESPACE::vector<int> myvector;

	// set some initial content:
	for (int i = 1; i < 10; i++)
		myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8, 100);
	myvector.resize(12);

	outputfile << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		outputfile << ' ' << myvector[i];
	outputfile << '\n';
}

void test_capacity()
{
	outputfile << "\ntest_capacity\n";
	NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i = 0; i < 100; i++)
		myvector.push_back(i);

	outputfile << "size: " << (int)myvector.size() << '\n';
	// outputfile << "capacity: " << (int)myvector.capacity() << '\n';
	outputfile << "max_size: " << (int)myvector.max_size() << '\n';
}

void test_empty()
{
	outputfile << "\ntest_empty\n";
	NAMESPACE::vector<int> myvector;
	int sum(0);

	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	outputfile << "total: " << sum << '\n';
}

void test_reserve()
{
	outputfile << "\ntest_reserve\n";
	NAMESPACE::vector<int>::size_type sz;

	NAMESPACE::vector<int> foo;
	sz = foo.capacity();
	outputfile << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			outputfile << "capacity changed: " << sz << '\n';
		}
	}

	NAMESPACE::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // this is the only difference with foo above
	outputfile << "making bar grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			outputfile << "capacity changed: " << sz << '\n';
		}
	}
}

void test_subscript_operator()
{
	outputfile << "\ntest_subscript_operator\n";
	NAMESPACE::vector<int> myvector(10); // 10 zero-initialized elements

	NAMESPACE::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i = 0; i < sz; i++)
		myvector[i] = i;

	// reverse vector using operator[]:
	for (unsigned i = 0; i < sz / 2; i++)
	{
		int temp;
		temp = myvector[sz - 1 - i];
		myvector[sz - 1 - i] = myvector[i];
		myvector[i] = temp;
	}

	outputfile << "myvector contains:";
	for (unsigned i = 0; i < sz; i++)
		outputfile << ' ' << myvector[i];
	outputfile << '\n';
}

void test_at()
{
	outputfile << "\ntest_at\n";
	NAMESPACE::vector<int> myvector(10); // 10 zero-initialized ints

	// assign some values:
	for (unsigned i = 0; i < myvector.size(); i++)
		myvector.at(i) = i;

	outputfile << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		outputfile << ' ' << myvector.at(i);
	outputfile << '\n';
}

void test_front()
{
	outputfile << "\ntest_front\n";
	NAMESPACE::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	outputfile << "myvector.front() is now " << myvector.front() << '\n';
}

void test_back()
{
	outputfile << "\ntest_back\n";
	NAMESPACE::vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back(myvector.back() - 1);
	}

	outputfile << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		outputfile << ' ' << myvector[i];
	outputfile << '\n';
}

void test_assign()
{
	outputfile << "\ntest_assign\n";
	NAMESPACE::vector<int> first;
	NAMESPACE::vector<int> second;
	NAMESPACE::vector<int> third;

	first.assign(7, 100); // 7 ints with a value of 100

	NAMESPACE::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3); // assigning from array.

	outputfile << "Size of first: " << int(first.size()) << '\n';
	outputfile << "Size of second: " << int(second.size()) << '\n';
	outputfile << "Size of third: " << int(third.size()) << '\n';
}

void test_push_back()
{
	outputfile << "\ntest_push_back\n";
	NAMESPACE::vector<int> myvector;
	int myint;

	outputfile << "Please enter some integers (enter 0 to end):\n";

	do
	{
		std::cin >> myint;
		myvector.push_back(myint);
	} while (myint);

	outputfile << "myvector stores " << int(myvector.size()) << " numbers.\n";
}

void test_pop_back()
{
	outputfile << "\ntest_pop_back\n";
	NAMESPACE::vector<int> myvector;
	int sum(0);
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	outputfile << "The elements of myvector add up to " << sum << '\n';
}

void test_insert()
{
	outputfile << "\ntest_insert\n";
	NAMESPACE::vector<int> myvector(3, 100);
	NAMESPACE::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert(it, 200);

	myvector.insert(it, 2, 300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	NAMESPACE::vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	int myarray[] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	outputfile << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

void test_erase()
{
	outputfile << "\ntest_erase\n";
	NAMESPACE::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	// erase the 6th element
	myvector.erase(myvector.begin() + 5);

	// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);

	outputfile << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		outputfile << ' ' << myvector[i];
	outputfile << '\n';
}

void test_swap_member()
{
	outputfile << "\ntest_swap_member\n";
	NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
	NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200
	NAMESPACE::vector<int>::iterator it = foo.begin();
	outputfile << "*it: " << *it << std::endl;
	foo.swap(bar);
	outputfile << "*it: " << *it << std::endl;

	outputfile << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		outputfile << ' ' << foo[i];
	outputfile << '\n';

	outputfile << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		outputfile << ' ' << bar[i];
	outputfile << '\n';
}

void test_clear()
{
	outputfile << "\ntest_clear\n";
	NAMESPACE::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	outputfile << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		outputfile << ' ' << myvector[i];
	outputfile << '\n';

	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);

	outputfile << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		outputfile << ' ' << myvector[i];
	outputfile << '\n';
}

void test_get_allocator()
{
	outputfile << "\ntest_get_allocator\n";
	NAMESPACE::vector<int> myvector;
	int *p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i = 0; i < 5; i++)
		myvector.get_allocator().construct(&p[i], i);

	outputfile << "The allocated array contains:";
	for (i = 0; i < 5; i++)
		outputfile << ' ' << p[i];
	outputfile << '\n';

	// destroy and deallocate:
	for (i = 0; i < 5; i++)
		myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p, 5);
}

void test_swap_non_member()
{
	outputfile << "\ntest_swap_non_member\n";
	//   unsigned int i;
	NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
	NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

	foo.swap(bar);

	outputfile << "foo contains:";
	for (NAMESPACE::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';

	outputfile << "bar contains:";
	for (NAMESPACE::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		outputfile << ' ' << *it;
	outputfile << '\n';
}

// lexicographical_compare example
#include <algorithm> // std::lexicographical_compare
#include <cctype>	 // std::tolower

// a case-insensitive comparison function:
bool mycomp(char c1, char c2)
{
	return std::tolower(c1) < std::tolower(c2);
}

void test_lexicographical_compare()
{
	outputfile << "\ntest_lexicographical_compare\n";
	
	char foo[] = "Apple";
	char bar[] = "apartment";

	outputfile << std::boolalpha;

	outputfile << "Comparing foo and bar lexicographically (foo<bar):\n";

	outputfile << "Using default comparison (operator<): ";
	outputfile << NAMESPACE::lexicographical_compare(foo, foo + 5, bar, bar + 9);
	outputfile << '\n';

	outputfile << "Using mycomp as comparison object: ";
	outputfile << NAMESPACE::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
	outputfile << '\n';
}

// enable_if example: two ways of using enable_if
#include <iostream>
// #include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type
is_odd(T i)
{
	return bool(i % 2);
}

// 2. the second template argument is only valid if T is an integral type:
template <class T>
bool is_even(T i,
	typename ft::enable_if<ft::is_integral<T>::value>::type* = NULL)
{
	return !bool(i % 2);
}

void test_enable_if_and_is_integral()
{
	outputfile << "\ntest_enable_if_and_is_integral\n";
	
	// float i = 1; // code does not compile if type of i is not integral
	short int i = 1;

	outputfile << std::boolalpha;
	outputfile << "i is odd: " << is_odd(i) << std::endl;
	outputfile << "i is even: " << is_even(i) << std::endl;
}

void test_reverse_iterator_relational_operators()
{

	NAMESPACE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	NAMESPACE::vector<int>::const_iterator c_it1 = v.begin();
	NAMESPACE::vector<int>::const_iterator c_it2 = v.begin() + 1;
	outputfile << "(c_it1 == c_it2): " << (c_it1 == c_it2) << std::endl;
	outputfile << "(c_it1 >= c_it2): " << (c_it1 >= c_it2) << std::endl;
	outputfile << "(c_it1 <= c_it2): " << (c_it1 <= c_it2) << std::endl;
	outputfile << "(c_it1 < c_it2): " << (c_it1 < c_it2) << std::endl;
	outputfile << "(c_it1 > c_it2): " << (c_it1 > c_it2) << std::endl;
	outputfile << "(c_it1 - c_it2): " << (c_it1 - c_it2) << std::endl;

	NAMESPACE::vector<int>::iterator it = v.begin() + 1;
	outputfile << "(c_it1 == it): " << (c_it1 == it) << std::endl;
	outputfile << "(c_it1 >= it): " << (c_it1 >= it) << std::endl;
	outputfile << "(c_it1 <= it): " << (c_it1 <= it) << std::endl;
	outputfile << "(c_it1 < it): " << (c_it1 < it) << std::endl;
	outputfile << "(c_it1 > it): " << (c_it1 > it) << std::endl;
	outputfile << "(c_it1 - it): " << (c_it1 - it) << std::endl;
	
	outputfile << "(it == c_it1): " << (it == c_it1) << std::endl;
	outputfile << "(it >= c_it1): " << (it >= c_it1) << std::endl;
	outputfile << "(it <= c_it1): " << (it <= c_it1) << std::endl;
	outputfile << "(it < c_it1): " << (it < c_it1) << std::endl;
	outputfile << "(it > c_it1): " << (it > c_it1) << std::endl;
	outputfile << "(it - c_it1): " << (it - c_it1) << std::endl;

	NAMESPACE::vector<int>::reverse_iterator r_it = v.rbegin();
	NAMESPACE::vector<int>::const_reverse_iterator c_r_it = v.rbegin() + 1;
	outputfile << "(c_r_it == r_it): " << (c_r_it == r_it) << std::endl;
	outputfile << "(c_r_it >= r_it): " << (c_r_it >= r_it) << std::endl;
	outputfile << "(c_r_it <= r_it): " << (c_r_it <= r_it) << std::endl;
	outputfile << "(c_r_it < r_it): " << (c_r_it < r_it) << std::endl;
	outputfile << "(c_r_it > r_it): " << (c_r_it > r_it) << std::endl;
	outputfile << "(c_r_it - r_it): " << (c_r_it - r_it) << std::endl;
	
	outputfile << "(r_it == c_r_it): " << (r_it == c_r_it) << std::endl;
	outputfile << "(r_it >= c_r_it): " << (r_it >= c_r_it) << std::endl;
	outputfile << "(r_it <= c_r_it): " << (r_it <= c_r_it) << std::endl;
	outputfile << "(r_it < c_r_it): " << (r_it < c_r_it) << std::endl;
	outputfile << "(r_it > c_r_it): " << (r_it > c_r_it) << std::endl;
	outputfile << "(r_it - c_r_it): " << (r_it - c_r_it) << std::endl;

	NAMESPACE::vector<int>::const_reverse_iterator c_r_it2 = v.rbegin() + 2;
	outputfile << "(c_r_it == c_r_it2): " << (c_r_it == c_r_it2) << std::endl;
	outputfile << "(c_r_it >= c_r_it2): " << (c_r_it >= c_r_it2) << std::endl;
	outputfile << "(c_r_it <= c_r_it2): " << (c_r_it <= c_r_it2) << std::endl;
	outputfile << "(c_r_it < c_r_it2): " << (c_r_it < c_r_it2) << std::endl;
	outputfile << "(c_r_it > c_r_it2): " << (c_r_it > c_r_it2) << std::endl;
	outputfile << "(c_r_it - c_r_it2): " << (c_r_it - c_r_it2) << std::endl;
	
	outputfile << "(c_r_it2 == c_r_it): " << (c_r_it2 == c_r_it) << std::endl;
	outputfile << "(c_r_it2 >= c_r_it): " << (c_r_it2 >= c_r_it) << std::endl;
	outputfile << "(c_r_it2 <= c_r_it): " << (c_r_it2 <= c_r_it) << std::endl;
	outputfile << "(c_r_it2 < c_r_it): " << (c_r_it2 < c_r_it) << std::endl;
	outputfile << "(c_r_it2 > c_r_it): " << (c_r_it2 > c_r_it) << std::endl;
	outputfile << "(c_r_it2 - c_r_it): " << (c_r_it2 - c_r_it) << std::endl;
}