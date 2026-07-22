#pragma once
#include "Export.h"

namespace XYZEngine
{
	class ENGINE_API Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;
		virtual void Start() = 0;
		virtual void Restart() = 0;
		virtual void Stop() = 0;
		virtual void Update(float deltaTime) = 0;
	};
}