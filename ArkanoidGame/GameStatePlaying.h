#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameStateData.h"
#include "LevelLoader.h"
#include "GameMemento.h"
#include <unordered_map>

namespace RoguelikeGame
{
	class Game;

	class GameStatePlayingData: public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		/*void CreatBlocks();
		void CreateBonus(sf::Vector2f bonusPos);*/

		void Save();
		void Load(GameMemento& objects);

	private:
		sf::Font font;
		sf::Texture platformTex;
		sf::Texture ballTex;
		sf::Texture blockTex;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Bonus>> bonuses;

		int totalScore = 0;

		sf::RectangleShape background;

		LevelLoader levelloader;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
		sf::Sound gameWinSound;

		bool isGameStart = false;
	};
	
}
