#pragma once
#include <stdexcept>

namespace structs
{
	template<typename T, size_t max_size>
	struct LineArray
	{
	private:
		T* _data[max_size];

		T** _begin;
		T** _end;

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
			}
		}

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
		}

		bool TryGetNext(T** ptrNext)
		{
			if (!IsEmpty() && _begin <= _end)
			{
				*ptrNext = *_begin;
				++_begin;
				return true;
			}

			return false;
		}

		bool IsEmpty() const { return _begin == nullptr || _end == nullptr; }
	};
}