#include "pch.h"
#include "Scene.h"

namespace XYZEngine
{
	bool Scene::IsFinished()
	{
		return isFinished;
	}
	void Scene::SetFinished(bool isFinished)
	{
		this->isFinished = isFinished;
	}
}