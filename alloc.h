#ifndef _ALLOC_H
#define _ALLOC_H

#include <cstdlib>

namespace TinySTL 
{
	class alloc
	{
	private:
		enum { _ALIGN = 8 };
		enum { _MAX_BYTES = 128 };
		enum { _NFREELISTS = 16 };
	
	private:
		union _obj
		{
			union obj *_next;
			char _client[1];
		};

		static obj *_free_list[_NFREELISTS];
	

	private:
		static size_t _round_up(size_t _bytes)
		{
			return (_bytes + (size_t)_ALIGN - 1) & ~((size_t)_ALGIN - 1);
		}

		static size_t _free_list_index(size_t _bytes)
		{
			return (_bytes + (size_t)_ALIGN - 1) / (size_t)_ALIGN - 1;
		}
		
		static void *_refill(size_t _n);
		static char *_chunk_alloc(size_t _n, int &_nobjs);
	
	private:
		static char *_start_free;
		static char *_end_free;

		static size_t _heap_size;
	
	public:
		static void *allocate(size_t _n)
		{
			void *_ret =  0;
			if (_n > (size_t)_MAX_BYTES
			{
				return malloc(_n);
			}
			else
			{
				_obj** _my_free_list = _free_list + 
					_free_list_index(_n);
				_obj* _result = *_my_free_list;
				if (result == nullptr)
					_ret = _refill(_round_up(_n));
				else
				{
					*my_free_list = result->_next;
					_ret = _result;
				}
			}
			return _ret;
		}
	
		static void deallocate(void *_p, size_t _n)
		{
			if (_n > _MAX_BYTES)
				free(p);
			else
			{
				_obj** _my_free_list = _free_list + _free_list_index(_n);
				_obj* _q = (_obj*) _p;
				_q->_next = *_my_free_list;
				*_my_free_list = _q;
			}
		}

		void *reallocate(void *_p, size_t _old_size, size_t _new_size)
		{
			deallocate(_p, _old_size);
			return allocate(_p, _new_size);
		}
	};
}

#endif
