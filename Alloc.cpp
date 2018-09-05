#include "Alloc.h"

namespace TinySTL
{
	char *alloc::_start_free = 0;
	char *alloc::_end_free = 0;
	size_t alloc::_heap_size = 0;

	alloc::obj *alloc::_free_list[alloc::_NFREELISTS] = 
		{ 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0 };

	void *alloc::_refill(size_t _n)
	{
		int _nobjs = 20;
		char *_chunk = _chunk_alloc(_n, _nobjs);
		_obj** _my_free_list;
		_obj* _result;
		_obj* _curr_obj;
		_obj* _next_obj;
		int _i;

		if (_nobjs == 1)
			return _chunk;
		_my_free_list = _free_list + _free_list_index(_n);
		_result = (_obj*)_chunk;
		*_my_free_list = _next_obj = (_obj*)(_chunk + _n);
		for (_i = 1; ; ++i)
		{
			_curr_obj = _next_obj;
			_next_obj = (_obj*)((char*)_next_obj + _n);
			if (_nobjs - 1 == _i)
			{
				_curr_obj->_next = nullptr;
				break;
			}
			else
			{
				_current_obj->_next = _next_obj;
			}
		}
		return _result;
	}
	
	char *alloc::_chunk_alloc(size_t _size, size_t &_nobjs)
	{
		char *_result;
		size_t _total_bytes = _size * _nobjs;
		size_t _bytes_left = _end_free - _start_free;
		if (_bytes_left >= _total_bytes)
		{
			_result = _start_free;
			_start_free += _total_bytes;
			return _result;
		}
		else if (_bytes_left >= _size)
		{
			_nobjs = (int)(_bytes_left / _size);
			_total_bytes = _nobjs * _size;
			_result = _start_free;
			_start_free += _total_bytes;
			return _result;
		}
		else
		{
			size_t _bytes_to_get = 2 * _total_bytes + _round_up(_heap_size >> 4);
			if (_bytes_left > 0)
			{
				_obj** _my_free_list = _free_list + _free_list_index(_bytes_left);
				(_obj*)_start_free->_next = *_my_free_list;
				*_my_free_list = (_obj*)_start_free;
			}
			
			_start_free = (char*)malloc(_bytes_to_get);
			if (_start_free == nullptr)
			{
				size_t _i;
				_obj** _my_free_list;
				_obj *_p;
				for (_i = _size; _i <= (size_t)_MAX_BYTES; _i += _ALIGN)
				{
					_my_free_list = _free_list + _free_list_index(_i);
					_p = *_my_free_list;
					if (_p != nullptr)
					{
						*_my_free_list = _p->_next;
						_start_free = (char*)_p;
						_end_free = _start_free + _i;
						return _chunk_alloc(_size, _nobjs);
					}
				}
				_end_free = nullptr;
				
			}
			_heap_size += _bytes_to_get;
			_end_free = _start_free + _bytes_to_get;
			return _chunk_alloc(_size, _nobjs);
		}
	}
}

