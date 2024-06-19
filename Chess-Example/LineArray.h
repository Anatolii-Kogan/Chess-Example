#pragma once
#include <stdexcept>
#include <cstddef>
#include "IIterator.h"

namespace structs
{
	template<typename T, size_t max_size>
	struct LineArray 
		: public IIterator<T>
	{
    private:
        T* _data[max_size];

        mutable size_t _currentIndex;
        size_t _size;

    public:
        LineArray() : _currentIndex(0), _size(0)
        {
            std::fill_n(_data, max_size, nullptr);
        }

        void Set(int index, T* value)
        {
            if (index >= max_size)
            {
                throw std::out_of_range("Index out of range");
            }

            _data[index] = value;

            if (index >= _size)
            {
                _size = index + 1;
            }
        }

        T* GetFirst() const override
        {
            if (_size == 0)
            {
                throw std::out_of_range("Array is empty");
            }
            return _data[0];
        }

        T* GetLast() const override
        {
            if (_size == 0)
            {
                throw std::out_of_range("Array is empty");
            }
            return _data[_size - 1];
        }

        void Reset()
        {
            std::fill_n(_data, max_size, nullptr);
            ResetIterator();
            _size = 0;
        }

        bool TryGetNext(T*& next) const override
        {
            if (_currentIndex >= _size)
            {
                return false;
            }

            next = _data[_currentIndex++];
            return true;
        }

        void ResetIterator() const override { _currentIndex = 0; }

        bool IsEmpty() const{ return _size == 0; }
	};
}