#pragma once
namespace drawers
{
	class IDrawer
	{
	public:
		virtual void Draw() const = 0;
	};
}