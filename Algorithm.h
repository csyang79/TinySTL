#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <cstring>
#include <utility>

#include "Functional.h"
#include "Allocator.h"
#include "Iterator.h"
#include "Utility.h"
#include "TypeTraits.h"

namespace TinySTL
{
	template <class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& val)
	{
		for (; first != last; ++first)
			*first = val;
	}
	inline void fill(char *first, char *last, const char& val)
	{
		char c = val;
		memset(first, static_cast<unsigned char>(c), last - first);
	}

	template <class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& val)
	{
		for (; n > 0; --n, ++first)
			*first = val;
		return first;
	}
	template <class Size>
	char *fill_n(char *first, Size n, const char& val)
	{
		char c = val;
		memset(first, static_cast<unsigned char>(c), n);
		return first + n;
	}
	
	template <class T>
	const T& min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}
	template <class T>
	const T& max(const T& a, const T& b)
	{
		return b < a ? a : b;
	}

	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare compare)
	{
		return compare(a, b) ? b : a;
	}
	template <class T, class Compare>
	const T& min(const T& a, const T& b, Compare compare)
	{
		return compare(b, a) ? b : a;
	}
	
	template <class RandomAccessIterator, class Compare>
	static void up(RandomAccessIterator first, RandomAccessIterator last, 
		RandomAccessIterator head, Compare comp)
	{
		if (first != last)
		{
			int index = last - head;
			int parentIndex = (index - 1) / 2;
			for (auto cur = last; parentIndex >= 0 && cur != head; parentIndex = (index - 1) / 2)
			{
				auto parent = head + parentIndex;
				if (comp(*parent, *cur)
					TinySTL::swap(*parent, *cur);
				cur = parent;
				index = cur - head;
			}
		}
	}
}

#endif
