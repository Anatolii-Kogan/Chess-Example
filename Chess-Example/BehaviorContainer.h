#pragma once
#include "IChessmanBehavior.h"
#include <type_traits>
#include <vector>

namespace chessmans
{
	class BehaviorContainer
	{
	private:
		mutable std::vector<IChessmanBehavior*> _behaviors;

	public:
		BehaviorContainer() = default;
		~BehaviorContainer()
		{
			for (auto* behavior : _behaviors)
			{
				delete behavior;
			}
			_behaviors.clear();
		}

		template<typename TChessmanBehavior>
		TChessmanBehavior* GetOrCreate() const
		{
			static_assert(std::is_base_of<IChessmanBehavior, TChessmanBehavior>::value, "Method for descendant of IChessmanBehavior");

			for (auto& behavior : _behaviors)
			{
				if (auto casted = dynamic_cast<TChessmanBehavior*>(behavior))
				{
					return casted;
				}
			}

			TChessmanBehavior* instance = new TChessmanBehavior();
			_behaviors.push_back(instance);
			return instance;
		}		
	};
}
