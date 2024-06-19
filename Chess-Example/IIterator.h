#pragma once
namespace structs
{
	template<typename T>
	struct IIterator
	{
	public:
		virtual bool TryGetNext(T** ptrNext) const = 0;

		virtual T* GetFirst() const = 0;
		virtual T* GetLast() const = 0;

		virtual void ResetIterator() const {}
	};
}