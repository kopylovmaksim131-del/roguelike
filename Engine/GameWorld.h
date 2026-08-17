#pragma once

#include "GameObject.h"
#include "PhysicsSystem.h"
#include "Export.h"
#include "Scene.h"

namespace XYZEngine
{
	class ENGINE_API GameWorld
	{
	public:
		static GameWorld* Instance();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void LateUpdate();
		void SetActiveScene(std::shared_ptr<Scene> activeScene);
		void SceneUpdate(float deltaTime);

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(std::string name);
		void DestroyGameObject(GameObject* gameObject);
		void Clear();

		void Print() const;
		GameObject* GetGameObjectByName(const std::string& name);
		const std::vector<GameObject*>& GetGameObjects() const;
	private:
		GameWorld() {}
		~GameWorld() {}

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		float fixedCounter = 0.f;

		std::vector<GameObject*> gameObjects = {};
		std::vector<GameObject*> markedToDestroyGameObjects = {};
		std::shared_ptr<Scene> scene;

		void DestroyGameObjectImmediate(GameObject* gameObject);
	};
}