#pragma once
#include "IChessmanBehavior.h"
#include <type_traits>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace chessmans
{
	class BehaviorContainer
	{
	private:
		mutable std::unordered_map<std::type_index, IChessmanBehavior*> _behaviors;

	public:
		BehaviorContainer() = default;
		~BehaviorContainer()
		{
			for (auto& pair : _behaviors)
			{
				delete pair.second;
			}
			_behaviors.clear();
		}

		template<typename TChessmanBehavior>
		TChessmanBehavior* GetOrCreate() const
		{
			static_assert(std::is_convertible_v<TChessmanBehavior*, IChessmanBehavior*>, "TChessmanBehavior* must be convertible to IChessmanBehavior*");

			std::type_index typeIndex(typeid(TChessmanBehavior));

			auto it = _behaviors.find(typeIndex);
			if (it != _behaviors.end())
			{
				return static_cast<TChessmanBehavior*>(it->second);
			}

			TChessmanBehavior* instance = new TChessmanBehavior();
			_behaviors[typeIndex] = instance;
			return instance;
		}		
	};
}
