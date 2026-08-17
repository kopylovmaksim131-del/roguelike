#pragma once
#include "Export.h"

namespace XYZEngine
{
	class ColliderComponent;
	struct ENGINE_API Trigger
	{
	public:
		Trigger(ColliderComponent* newFirst, ColliderComponent* newSecond) :
			first(newFirst), second(newSecond) {
		};

		ColliderComponent* GetFirst();
		ColliderComponent* GetSecond();

	private:
		ColliderComponent* first;
		ColliderComponent* second;
	};
}