#pragma once
#include <cstring>
#include <initializer_list>
#include <utility>
#include "IIterator.h"

namespace structs
{
	template<typename T, size_t size>
	struct CircularList
		: public IIterator<T>
	{
	private:
		T _list[size];

		mutable size_t _index = 0;
	public:
		constexpr CircularList(const T(&params)[size])
		{
			for (size_t i = 0; i < size; ++i)
			{
				_list[i] = params[i];
			}
		}

		CircularList( const CircularList& copy ) : _index(copy._index)
		{
			std::copy(copy._list, copy._list + size, _list);
		}

		CircularList& operator=( const CircularList& other )
		{
			if (this != &other)
			{
				_index = other._index;
				std::copy(other._list, other._list + size, _list);
			}
			return *this;
		}

		~CircularList() = default;

		CircularList( CircularList&& other ) noexcept : _index(other._index)
		{
			std::move(other._list, other._list + size, _list);
			other._index = 0;
		}

		CircularList& operator=( CircularList&& other ) noexcept
		{
			if (this != &other)
			{
				_index = other._index;
				std::move(other._list, other._list + size, _list);
				other._index = 0;
			}
			return *this;
		}

		const T& GetNext() const
		{
			const T& param = _list[_index];
			_index = (_index + 1) % size;
			return param;
		}

		bool TryGetNext(T*& ptrNext) const override
		{
			ptrNext = const_cast<T*>(&_list[_index]);
			_index = (_index + 1) % size;
			return true;
		}

		T* GetFirst() const override { return const_cast<T*>(&_list[_index]); }
		T* GetLast() const override { return const_cast<T*>(&_list[(size - 1 + _index) % size]); }

		void ResetIterator() const override { _index = 0; }
	};
}
