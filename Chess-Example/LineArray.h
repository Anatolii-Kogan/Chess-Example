#pragma once
#include <stdexcept>
#include "IIterator.h"

namespace structs
{
	template<typename T, size_t max_size>
	struct LineArray 
		: public IIterator<T>
	{
	private:
		T* _data[max_size];

		T** _begin;
		T** _end;
		mutable T** _current;

	public:
		void Set(int index, T* value)
		{
			if (index >= max_size)
			{
				throw std::out_of_range("Index out of range");
			}

			_data[index] = value;
			T** ptr = &_data[index];

			if (ptr > _end || _end == nullptr)
			{
				_end = ptr;
			}
			if (ptr < _begin || _begin == nullptr)
			{
				_begin = ptr;

				if (_current < _begin)
				{
					_current = _begin;
				}
			}
		}

		T* GetFirst() const override { return *_begin; }
		T* GetLast() const override { return *_end; }

		void Reset()
		{
			if (IsEmpty())
			{
				return;
			}

			for (size_t i = 0; i < max_size; i++)
			{
				_data[i] = nullptr;
			}

			_begin = nullptr;
			_end = nullptr;
			ResetIterator();
		}

		bool TryGetNext(T** ptrNext) const override
		{
			if (IsEmpty() || _current > _end)
			{
				return false;
			}

			*ptrNext = *_current;
			++_current;

			return true;
		}

		void ResetIterator() const override { _current = _begin; }


		bool IsEmpty() const { return _begin == nullptr || _end == nullptr; }
	};
}