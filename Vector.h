#ifndef _VECTOR_H
#define _VECTOR_H

#include <algorithm>
#include <type_traits>

#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"

namespace TinySTL
{
	template <class T, class Alloc = allocator<T>>
	class vector
	{
	private:
		T *item;
		size_t size;
		size_t capacity;
		
		typedef Alloc dataAllocator;
	public:
		typedef T value_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef iterator pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	public:
		vector() : item(nullptr), size(0), capacity(0) { }
		explicit vector(const size_type n);
		vector(const size_type n, const value_type& val);
		template <class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& v);
		vector& operator=(const vector& v);
		~vector();

		bool operator==(const vector& v) const;
		bool operator!=(const vector& v) const;

		iterator begin()
		{
			return item;
		}

		const_iterator begin() const
		{
			return item;
		}

		const_iterator cbegin()
		{
			return item;
		}
		iterator end()
		{
			return item + size;
		}
		const_iterator end() const
		{
			return item + size;
		}
		const_iterator cend()
		{
			return item + size;
		}

		difference_type size() const
		{
			return size;
		}

		difference_type capacity() const
		{
			return capacity;
		}

		bool empty() const
		{
			return size == 0;
		}
		
		bool resize(size_type n, value_type val = value_type());
		void reserve(size_type n);
		void shrink_to_fit();

		reference operator[](const difference_type index)
		{
			return *(begin() + index);
		}
		const_reference operator[](const difference_type index) const
		{
			return *(cbegin() + index);
		}
		reference front()
		{
			return *begin();
		}
		reference back()
		{
			return *(end() - 1);
		}
		pointer data()
		{
			return item;
		}
		
		void clear();
		void swap(vector& v);
		void push_back(const value_type& val);
		void pop_back();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type& n, const value_type& n);
		template <class InputIterator>
		void insert(InputIterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		Alloc get_allocator()
		{
			return dataAllocator;	
		}
	private:
		void destroyAndDeallocateAll();
		void allocateAndFillN(const size_type& n, const value_type& val);
		template <class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		template <class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type);
		template <class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::true_type);
		template <class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		template <class Integer>
		void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);
		template <class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& val);
		size_type getNewCapacity(size_type len) const;
	
	};
}
#include "Vector.cpp"

#endif
