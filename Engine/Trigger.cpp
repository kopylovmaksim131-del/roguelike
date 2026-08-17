#include "pch.h"
#include "Trigger.h"

namespace XYZEngine
{
	ColliderComponent* Trigger::GetFirst()
	{
		return first;
	}
	ColliderComponent* Trigger::GetSecond()
	{
		return second;
	}
}