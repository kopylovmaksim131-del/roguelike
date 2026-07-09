#pragma once
#define NOMINMAX

#include "SFML/Graphics.hpp"
#include "Export.h"

namespace XYZEngine
{
	class ENGINE_API Engine
	{
	public:
		Engine(const Engine& app) = delete;
		Engine& operator= (const Engine&) = delete;

		void CreateWindowNew(unsigned width, unsigned height, const std::string& title);
		void PlayMusic(const std::string& name);

		static Engine* Instance();

		void Run();

	private:
		Engine();
		~Engine() = default;
	};
}

