#ifndef _VECTOR_CPP_H
#define _VECTOR_CPP_H

namespace TinySTL
{
	template <class T, class Alloc>
	vector<T, Alloc>::~vector()
	{
		destroyAndDeallocateAll();
	}
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n)
	{
		allocateAndFillN(n, value_type());
	}
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n, const value_type& value)
	{
		allocateAndFillN(n, value);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last)
	{
		vector_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const vector& v)
	{
		allocateAndCopy(v.item, v.item + size);
	}
	template <class T, class Alloc>
	vector<T, alloc>& vector<T, Alloc>::operator=(const vector& v)
	{
		if (this != &v)
		{
			allocateAndCopy(v.item, v.item + size):
		}
		return *this;
	}

	template <class T, class Alloc>

}

#endif
