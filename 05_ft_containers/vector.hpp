#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // allocator
# include <stdexcept> // out_of_range, length_error
# include "utils/normal_iterator.hpp"
# include "utils/utils.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	struct vector_base
	{
		/* --- MEMBER TYPES --- */
			typedef typename Alloc::template rebind<T>::other	T_alloc_type;
			typedef typename T_alloc_type::pointer				pointer;

			struct vector_attr : public T_alloc_type
			{
				pointer _start;
				pointer _finish;
				pointer _end_of_storage;

				vector_attr()
				: T_alloc_type(0), _start(0), _finish(0), _end_of_storage(0) {}
				vector_attr(T_alloc_type const& a)
				: T_alloc_type(a), _start(0), _finish(0), _end_of_storage(0) {}

				void
				_swap_data(vector_attr& x)
				{
					std::swap(_start, x._start);
					std::swap(_finish, x._finish);
					std::swap(_end_of_storage, x._end_of_storage);
				}
			};

			typedef Alloc	allocator_type;

		/* --- MEMBER FUNCTIONS --- */
			T_alloc_type&
			get_T_allocator()
			{ return *static_cast<T_alloc_type*>(&this->_attr); }

			const T_alloc_type&
			get_T_allocator() const
			{ return *static_cast<const T_alloc_type*>(&this->_attr); }

		/* CONSTRUCTORS */
			vector_base()
			: _attr() {}

			vector_base(const allocator_type& a)
			: _attr(a) {}
			
			vector_base(size_t n)
			: _attr()
			{ this->_create_storage(n); }

			vector_base(size_t n, const allocator_type& a)
			: _attr(a)
			{ this->_create_storage(n); }

		/* DESTRUCTOR */
			~vector_base()
			{ this->_deallocate(this->_attr._start, this->_attr._end_of_storage - this->_attr._start); }

		/* --- MEMBER ATTRIBUTES --- */
			vector_attr		_attr;

		/* --- MEMBER FUNCTIONS (CONTINUED) --- */
			pointer
			_allocate(size_t n)
			{ return n != 0 ? + _attr.allocate(n) : 0; }

			void
			_deallocate(pointer p, size_t n)
			{ if (p) _attr.deallocate(p, n); }

			void
			_create_storage(size_t n)
			{
				this->_attr._start = this->_allocate(n);
				this->_attr._finish = this->_attr._start;
				this->_attr._end_of_storage = this->_attr._start + n;
			}
	};

	template <class T, class Alloc = std::allocator<T> >
	class vector : protected vector_base<T, Alloc>
	{
			typedef vector_base<T,Alloc>									base;
			typedef typename base::T_alloc_type								T_alloc_type;
			typedef std::allocator_traits<T_alloc_type>						alloc_traits;

		public:
		/* --- MEMBER TYPES --- */
			typedef T														value_type;
			typedef Alloc													allocator_type;

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef ft::normal_iterator<pointer, vector>					iterator;
			typedef ft::normal_iterator<const_pointer, vector>				const_iterator;
			typedef	ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef std::size_t												size_type;

		protected:
			using base::get_T_allocator;

		public:
		/* --- MEMBER FUNCTIONS (PUBLIC) --- */
		/* CONSTRUCTORS */
			explicit
			vector(const allocator_type& alloc = allocator_type())
			: base(alloc) {}

			explicit
			vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
			: base(n, alloc)
			{ this->_attr._finish = std::uninitialized_fill_n(this->_attr._start, n, val); }

			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
				   const allocator_type& alloc = allocator_type(),
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			: base(alloc)
			{
				this->_create_storage(std::distance(first, last));
				this->_attr._finish = std::uninitialized_copy(first, last, this->_attr._start);
			}

			vector(const vector& x)
			: base(x.size(), x.get_T_allocator())
			{ this->_attr._finish = std::uninitialized_copy(x.begin(), x.end(), this->_attr._start); }

		/* DESTRUCTOR */
			~vector()
			{ _destroy(this->_attr._start, this->_attr._finish); }

			vector&
			operator=(const vector& x)
			{
				if (this != &x)
				{
					const size_type xlen = x.size();
					if (xlen > capacity())
					{
						pointer tmp = _allocate_and_copy(xlen, x.begin(), x.end());
						_destroy(this->_attr._start, this->_attr._finish);
						this->_deallocate(this->_attr._start, this->capacity());
						this->_attr._start = tmp;
						this->_attr._end_of_storage = this->_attr._start + xlen;
					}
					else if (size() >= xlen)
					{
						_destroy(std::copy(x.begin(), x.end(), begin()), end());
					}
					else
					{
						std::copy(x._attr._start, x._attr._start + size(), this->_attr._start);
						std::uninitialized_copy(x._attr._start + size(), x._attr._finish, this->_attr._finish);
					}
					this->_attr._finish = this->_attr._start + xlen;
				}
				return *this;
			}

		protected:
			template<typename ForwardIterator>
			pointer
			_allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last)
			{
				pointer result = this->_allocate(n);
				try
				{
					std::uninitialized_copy(first, last, result);
					return result;
				}
				catch(...)
				{
					this->_deallocate(result, n);
					throw ;
				}
			}

			template<typename U>
			void
			_destroy(U* p)
			{ if (p) this->_attr.destroy(p); }

			template<typename ForwardIterator>
			void
			_destroy(ForwardIterator first, ForwardIterator last)
			{
				for (; first != last; ++first)
					this->_destroy(&*first);
			}

		public:
			iterator
			begin()
			{ return iterator(this->_attr._start); }

			const_iterator
			begin() const
			{ return const_iterator(this->_attr._start); }
			
    		iterator
			end()
			{ return iterator(this->_attr._finish); }

    		const_iterator
			end() const
			{ return const_iterator(this->_attr._finish); }
			
			reverse_iterator
			rbegin()
			{ return reverse_iterator(end()); }

			const_reverse_iterator
			rbegin() const
			{ return const_reverse_iterator(end()); }

			reverse_iterator
			rend()
			{ return reverse_iterator(begin()); }

			const_reverse_iterator
			rend() const
			{ return const_reverse_iterator(begin()); }

		/* --- CAPACITY --- */
			size_type
			size() const
			{ return size_type(this->_attr._finish - this->_attr._start); }

			size_type
			max_size() const
			{ return alloc_traits::max_size(get_T_allocator()); }

			void
			resize(unsigned int n, value_type val = value_type())
			{
				if (n > size())
					insert(end(), n - size(), val);
				else if (n < size())
					_erase_at_end(this->_attr._start + n);
			}

		protected:
			size_type
			_check_len(size_type n, const char* s) const
			{
				if (max_size() - capacity() < n)
					throw std::length_error(s);
				size_type len;
				if (std::max(capacity(), n) == n)
					len = size() + n;
				else
					len = capacity() + capacity();
				return (len < capacity() || len > max_size()) ? max_size() : len;
			}

			void
			_erase_at_end(pointer pos)
			{
				if (size_type n = this->_attr._finish - pos)
				{
					_destroy(pos, this->_attr._finish);
					this->_attr._finish = pos;
				}
			}

		public:
			size_type
			capacity() const
			{ return size_type(this->_attr._end_of_storage - this->_attr._start); }

			bool
			empty() const
			{ return begin() == end(); }

			void
			reserve(size_type n)
			{
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				if (this->capacity() < n)
				{
					const size_type old_size = size();
					pointer tmp = _allocate_and_copy(n, this->_attr._start, this->_attr._finish);
					this->_deallocate(this->_attr._start, this->capacity());
					this->_attr._start = tmp;
					this->_attr._finish = tmp + old_size;
					this->_attr._end_of_storage = this->_attr._start + n;
				}
			}

		/* --- ELEMENT ACCESS --- */
			reference
			operator[](size_type n)
			{ return *(this->_attr._start + n); }

			const_reference
			operator[](size_type n) const
			{ return *(this->_attr._start + n); }

			reference
			at(size_type n)
			{
				if (n >= this->size())
					throw std::out_of_range("vector::_range_check");
				return (*this)[n];
			}

			const_reference
			at(size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("vector::_range_check");
				return (*this)[n];
			}

			reference
			front(void)
			{ return *begin(); }

			const_reference
			front(void) const
			{ return *begin(); }

			reference
			back(void)
			{ return *(end() - 1); }

			const_reference
			back(void) const
			{ return *(end() - 1); }

		/* --- MODIFIERS --- */
			template <class InputIterator>
			void
			assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				typename ft::iterator_traits<InputIterator>::iterator_category IterCategory;
				_assign_aux(first, last, IterCategory);
			}

			void
			assign(size_type n, const value_type& val)
			{
				if (n > capacity())
				{
					vector tmp(n, val, get_T_allocator());
					tmp._attr._swap_data(this->_attr);
				}
				else if (n > size())
				{
					std::fill(begin(), end(), val);
					const size_type add = n - size();
					this->_attr._finish = std::uninitialized_fill_n(this->_attr._finish, add, val);
				}
				else
					_erase_at_end(std::fill_n(this->_attr._start, n, val));
			}

		protected:
			template <class InputIterator>
			void
			_assign_aux(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				pointer cur(this->_attr._start);
				for (; first != last && cur != this->_attr._finish; ++cur, ++first)
					*cur = *first;
				if (first == last)
					_erase_at_end(cur);
				else
					insert(end(), first, last);	
			}

			template <class ForwardIterator>
			void
			_assign_aux(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				const size_type len = std::distance(first, last);
				if (len > capacity())
				{
					pointer tmp(_allocate_and_copy(len, first, last));
					_destroy(this->_attr._start, this->_attr._finish);
					this->_deallocate(this->_attr._start, capacity());
					this->_attr._start = tmp;
					this->_attr._finish = this->_attr._start + len;
					this->_attr._end_of_storage = this->_attr._finish;
				}
				else if (size() >= len)
					_erase_at_end(std::copy(first, last, this->_attr._start));
				else
				{
					ForwardIterator mid = first;
					std::advance(mid, size());
					std::copy(first, mid, this->_attr._start);
					this->_attr._finish = std::uninitialized_copy(mid, last, this->_attr._finish);
				}
			}

		public:
			void
			push_back(const value_type& val)
			{
				if (this->_attr._finish != this->_attr._end_of_storage)
				{
					alloc_traits::construct(this->_attr, this->_attr._finish, val);
					++this->_attr._finish;
				}
				else
					_realloc_insert(end(), val);
			}

			void
			pop_back()
			{
				--this->_attr._finish;
				this->_destroy(this->_attr._finish);
			}

			iterator
			insert(iterator position, const value_type& val)
			{
				const size_type n = position - begin();
				if (this->_attr._finish != this->_attr._end_of_storage)
				{
					if (position == end())
					{
						alloc_traits::construct(this->_attr, this->_attr._finish, val);
						++this->_attr._finish;
					}
					else
						_insert_aux(position, val);
				}
				else
					_realloc_insert(position, val);
				return iterator(this->_attr._start + n);
			}

			void
			insert(iterator position, size_type n, const value_type& val)
			{ _fill_insert(position, n, val); }

			template<class InputIterator>
			void
			insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				typename ft::iterator_traits<InputIterator>::iterator_category IterCategory;
				_range_insert(position, first, last, IterCategory);
			}

		protected:
			void
			_insert_aux(iterator pos, const T& x)
			{
				alloc_traits::construct(this->_attr, this->_attr._finish, *(this->_attr._finish - 1));
				++this->_attr._finish;
				T x_copy = x;
				std::move_backward(pos.base(), this->_attr._finish - 2, this->_attr._finish - 1);
				*pos = x_copy;
			}

			void
			_realloc_insert(iterator pos, const T& x)
			{
				const size_type len = _check_len(size_type(1), "vector::_realloc_insert");
				pointer old_start = this->_attr._start;
				pointer old_finish = this->_attr._finish;
				const size_type elems_before = pos - begin();
				pointer new_start(this->_allocate(len));
				pointer new_finish(new_start);
				try
				{
					alloc_traits::construct(this->_attr, new_start + elems_before, x);
					new_finish = pointer();
					new_finish = std::uninitialized_copy(old_start, pos.base(), new_start);
					++new_finish;
					new_finish = std::uninitialized_copy(pos.base(), old_finish, new_finish);
				}
				catch(...)
				{
					if (!new_finish)
						_destroy(new_start + elems_before);
					else
						_destroy(new_start, new_finish);
					this->_deallocate(new_start, len);
					throw ;
				}
				_destroy(old_start, old_finish);
				this->_deallocate(old_start, this->_attr._end_of_storage - old_start);
				this->_attr._start = new_start;
				this->_attr._finish = new_finish;
				this->_attr._end_of_storage = new_start + len;
			}

			void
			_fill_insert(iterator pos, size_type n, const value_type& x)
			{
				if (n != 0)
				{
					if (size_type(this->_attr._end_of_storage - this->_attr._finish) >= n)
					{
						value_type x_copy = x;
						const size_type elems_after = end() - pos;
						pointer old_finish(this->_attr._finish);
						if (elems_after > n)
						{
							std::uninitialized_copy(this->_attr._finish - n,
								this->_attr._finish, this->_attr._finish);
							this->_attr._finish += n;
							std::copy_backward(pos.base(), old_finish - n, old_finish);
							std::fill(pos.base(), pos.base() + n, x_copy);
						}
						else
						{
							this->_attr._finish = std::uninitialized_fill_n(
								this->_attr._finish, n - elems_after, x_copy);
							std::uninitialized_copy(pos.base(), old_finish, this->_attr._finish);
							this->_attr._finish += elems_after;
							std::fill(pos.base(), old_finish, x_copy);
						}
					}
					else
					{
						const size_type len = _check_len(n, "vector::_fill_insert");
						const size_type elems_before = pos - begin();
						pointer new_start(this->_allocate(len));
						pointer new_finish(new_start);
						try
						{
							std::uninitialized_fill_n(new_start + elems_before, n, x);
							new_finish = pointer();
							new_finish = std::uninitialized_copy(this->_attr._start, pos.base(), new_start);
							new_finish += n;
							new_finish = std::uninitialized_copy(pos.base(), this->_attr._finish, new_finish);
						}
						catch(...)
						{
							if (!new_finish)
								_destroy(new_start + elems_before, new_start + elems_before + n);
							else
								_destroy(new_start, new_finish);
							this->_deallocate(new_start, len);
							throw ;
						}
						_destroy(this->_attr._start, this->_attr._finish);
						this->_deallocate(this->_attr._start, capacity());
						this->_attr._start = new_start;
						this->_attr._finish = new_finish;
						this->_attr._end_of_storage = new_start + len;
					}
				}
			}

			template<typename InputIterator>
			void
			_range_insert(iterator pos, InputIterator first, InputIterator last,
				std::input_iterator_tag)
			{
				if (pos == end())
				{
					for (; first != last; ++first)
						insert(end(), *first);
				}
				else if (first != last)
				{
					vector tmp(first, last, get_T_allocator());
					insert(pos, tmp.begn(), tmp.end());
				}
			}

			template<typename ForwardIterator>
			void
			_range_insert(iterator pos, ForwardIterator first, ForwardIterator last,
				std::forward_iterator_tag)
			{
				if (first != last)
				{
					const size_type n = std::distance(first, last);
					if (size_type(this->_attr._end_of_storage - this->_attr._finish) >= n)
					{
						const size_type elems_after = end() - pos;
						pointer old_finish(this->_attr._finish);
						if (elems_after > n)
						{
							std::uninitialized_copy(this->_attr._finish - n, this->_attr._finish, this->_attr._finish);
							this->_attr._finish += n;
							std::copy_backward(pos.base(), old_finish - n, old_finish);
							std::copy(first, last, pos);
						}
						else
						{
							ForwardIterator mid = first;
							std::advance(mid, elems_after);
							std::uninitialized_copy(mid, last, this->_attr._finish);
							this->_attr._finish += n - elems_after;
							std::uninitialized_copy(pos.base(), old_finish, this->_attr._finish);
							this->_attr._finish += elems_after;
							std::copy(first, mid, pos);
						}
					}
					else
					{
						const size_type len = _check_len(n, "vector::_range_insert");
						pointer new_start(this->_allocate(len));
						pointer new_finish(new_start);
						try
						{
							new_finish = std::uninitialized_copy(this->_attr._start, pos.base(), new_start);
							new_finish = std::uninitialized_copy(first, last, new_finish);
							new_finish = std::uninitialized_copy(pos.base(), this->_attr._finish, new_finish);
						}
						catch(...)
						{
							_destroy(new_start, new_finish);
							this->_deallocate(new_start, len);
							throw ;
						}
						_destroy(this->_attr._start, this->_attr._finish);
						this->_deallocate(this->_attr._start, capacity());
						this->_attr._start = new_start;
						this->_attr._finish = new_finish;
						this->_attr._end_of_storage = new_start + len;
					}
				}
			}

		public:
			iterator
			erase(iterator position)
			{
				if (position + 1 != end())
					std::copy(position + 1, end(), position);
				--this->_attr._finish;
				this->_destroy(this->_attr._finish);
				return position;
			}

			iterator
			erase(iterator first, iterator last)
			{
				if (first != last)
				{
					if (last != end())
						std::copy(last, end(), first);
					_erase_at_end(first.base() + (end() - last));
				}
				return first;
			}

			void
			swap(vector& x)
			{ this->_attr._swap_data(x._attr); }

			void
			clear()
			{ _erase_at_end(this->_attr._start); }

		/* --- ALLOCATORS --- */
			allocator_type
			get_allocator() const
			{ return allocator_type(get_T_allocator()); }
	}; // ft::vector

	/* --- NON-MEMBER FUNCTION OVERLOADS --- */

	template <class T, class Alloc>
	bool
	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

	template <class T, class Alloc>
	bool
	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <class T, class Alloc>
	bool
	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class T, class Alloc>
	bool
	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return !(rhs < lhs); }

	template <class T, class Alloc>
	bool
	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return rhs < lhs; }

	template <class T, class Alloc>
	bool
	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class T, class Alloc>
	void
	swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{ return x.swap(y); }

} // ft::

#endif
