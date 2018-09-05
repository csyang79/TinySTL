#ifndef _UTILITY_H
#define _UTILITY_H

namespace TinySTL
{
	template <class T>
	void swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <class T1, class T2>
	class pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	public:
		pair() : first(T1()), second(T2()) { }
		pair(const first_type& a, const second_type& b) : first(a), second(b) { }
		
		template <class U, class V>
		pair(const pair<U, V>& p) : first(p.first), second(p.second) { }
		
		template <class U, class V>
		pair& operator=(const pair<U, V>& p)
		{
			if (this != &p)
			{
				first = p.first;
				second = p.second;
			}
			return *this;
		}
		void swap(pair& p)
		{
			TinySTL::swap(p.first, first);
			TinySTL::swap(p.second, second);
		}
	}
	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first == y.first && x.second == y.second;
	}
	template <class T1, class T2>
	inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(x == y);
	}
	template <class T1, class T2>
	inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first < y.first || (!(x.first > y.first) && (x.second < y.second));
	}
	template <class T1, class T2>
	inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(y < x);
	}
	template <class T1, class T2>
	inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(x < y);
	}
	template <class T1, class T2>
	inline bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return y < x;
	}
	template <class T1, class T2>
	inline pair<T1, T2> make_pair(const T1& x, const T2& y)
	{
		return pair<T1, T2>(x, y);
	}
}

#endif
