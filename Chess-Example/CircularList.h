#pragma once
#include <initializer_list>
namespace structs
{
	template<typename T>
	struct CircularList
	{
	public:
		CircularList(std::initializer_list<T> params)
			:
			_size(static_cast<int>(params.size())),
			_index(0)
		{
			_list = new T[_size];

			int index = 0;
			for (auto param : params)
			{
				_list[index] = param;
				++index;
			}
		}

		CircularList(const CircularList& copy) : _size(copy._size), _index(copy._index)
		{
			_list = new T[_size];
			std::memcpy(_list, copy._list, _size * sizeof(T));
		}

		CircularList& operator=(const CircularList& other)
		{
			if (this != &other)
			{
				delete[] _list;
				_size = other._size;
				_index = other._index;
				_list = new T[_size];
				std::memcpy(_list, other._list, _size * sizeof(T));
			}
			return *this;
		}

		~CircularList() { delete[] _list; }

		CircularList( CircularList&& other ) noexcept : _list(nullptr), _size(0), _index(0)
		{
			*this = std::move(other);
		}

		CircularList& operator=( CircularList&& other ) noexcept
		{
			if (this != &other)
			{
				delete[] _list;
				_list = other._list;
				_size = other._size;
				_index = other._index;

				other._list = nullptr;
				other._size = 0;
				other._index = 0;
			}

			return *this;
		}

		const T& GetNext() const
		{
			const T& param = _list[_index];

			++_index;
			if (_index == _size)
			{
				_index = 0;
			}

			return param;
		}

	private:
		int _size;
		T* _list;

		mutable int _index;
	};
}
