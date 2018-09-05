#ifndef _CONSTRUCT_H
#define _CONSTRUCT_H

#include <new>
#include "TypeTraits.h"

namespace TinySTL
{

	template <class T1, class T2>
	inline void construct(T1 *p, const T2& val)
	{
		new (p) T1(val);
	}

	template <class T>
	inline void destroy(T *p)
	{
		p->~T();
	}

	template <class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last)
	{
		typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
		_destroy(first, last, is_POD_type());
	}

	template <class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) { }

	template <class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type)
	{
		for (; first != last; ++first)
			destroy(&*first);		//应该是为了避免迭代器和指针的类型转换
	}

}


#endif
