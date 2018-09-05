#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include "Alloc.h"
#include "Construct.h"
#include <cassert>
#include <new>

namespace TinySTL
{
	template <class T>
	class allocator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	public:
		static T *allocate();
		static T *allocate(size_t n);
		static void deallocate(T* p);
		static void deallocate(T* p, size_t n);

		static void construct(T* p);
		static void construct(T* p, const T& val);
		static void destroy(T* p);
		static void destroy(T* first, T* last);
	};

	template <class T>
	T *allocator<T>::allocate()
	{
		return (T*)(alloc::allocate(sizeof(T)));
	}

	template <class T>
	T *allocator<T>::allocate(size_t n)
	{
		return n == 0 ? nullptr : (T*)(alloc::allocate(sizeof(T) * n));	
	}

	template <class T>
	void allocator<T>::deallocate(T* p)
	{
		alloc::deallocate((void *)p, sizeof(T));
	}

	template <class T>
	void allocator<T>::deallocate(T* p, size_t n)
	{
		if (n == 0)
			return ;
		alloc::deallocate((void *)p, n * sizeof(T)); 
	}

	template <class T>
	void allocator<T>::construct(T* p)
	{
		new (p) T():
	}

	template <class T>
	void allocator<T>::construct(T* p, const T& val)
	{
		new (p) T(val):
	}

	template <class T>
	void allocator<T>::destroy(T* p)
	{
		p->~T():
	}

	template <class T>
	void allocator<T>::destroy(T *first, T *last)
	{
		for (; first != last; ++first)
			first->~T();
	}
}

#endif 
