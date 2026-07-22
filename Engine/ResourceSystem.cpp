#include "pch.h"
#include "ResourceSystem.h"

namespace XYZEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		LOG_INFO("ResourceSystem::LoadTexture name='" + name + "', path='" + sourcePath + " - starting");

		if (textures.find(name) != textures.end())
		{
			return;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
			LOG_INFO("ResourceSystem::LoadTexture name='" + name + "', path='" + sourcePath + " - loaded successfully");
		}
		else
		{
			LOG_ERROR("ResourceSystem::LoadTexture name='" + name + "', path='" + sourcePath + " - FAILED to load");
		}
	}
	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		return textures.find(name)->second;
	}
	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return new sf::Texture(*textures.find(name)->second);
	}
	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		LOG_INFO("ResourceSystem::DeleteSharedTexture texture name='" + name + " - was delet");

		auto texturePair = textures.find(name);

		sf::Texture* deletingTexure = texturePair->second;
		textures.erase(texturePair);
		delete deletingTexure;
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		LOG_INFO("ResourceSystem::LoadTextureMap name='" + name + "', path='" + sourcePath + " - starting");

		if (textureMaps.find(name) != textureMaps.end())
		{
			return;
		}

		sf::Texture textureMap;
		if (textureMap.loadFromFile(sourcePath))
		{
			LOG_INFO("ResourceSystem::LoadTextureMap name='" + name + "', path='" + sourcePath + " - loaded successfully");

			auto textureMapElements = new std::vector<sf::Texture*>();

			auto textureSize = textureMap.getSize();
			int loadedElements = 0;

			for (int y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (int x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements->push_back(newTextureMapElement);
					}
					loadedElements++;
				}
			}

			textureMaps.emplace(name, *textureMapElements);
		}
		else
		{
			LOG_ERROR("ResourceSystem::LoadTextureMap name='" + name + "', path='" + sourcePath + " - FAILED to load");
		}
	}
	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures[elementIndex];
	}
	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return new sf::Texture(*textures[elementIndex]);
	}
	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures.size();
	}
	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		LOG_INFO("ResourceSystem::DeleteSharedTextureMap texture map name='" + name + " - was delet");
		auto textureMap = textureMaps.find(name);
		auto deletingTextures = textureMap->second;

		for (int i = 0; i < deletingTextures.size(); i++)
		{
			delete deletingTextures[i];
		}

		textureMaps.erase(textureMap);
	}

	void ResourceSystem::LoadMusic(const std::string& name, std::string sourcePath)
	{
		LOG_INFO("ResourceSystem::LoadMusic name='" + name + "', path='" + sourcePath + " - starting");

		if (musics.find(name) != musics.end())
		{
			return;
		}

		sf::Music* newMusic = new sf::Music();
		if (newMusic->openFromFile(sourcePath))
		{
			LOG_INFO("ResourceSystem::LoadMusic name='" + name + "', path='" + sourcePath + " - loaded successfully");
			musics.emplace(name, newMusic);
		}
		else
		{
			LOG_ERROR("ResourceSystem::LoadMusic name='" + name + "', path='" + sourcePath + " - FAILED to load");
		}
	}
	sf::Music* ResourceSystem::GetMusicShared(const std::string& name) 
	{
		return musics.find(name)->second;
	}
	void ResourceSystem::DeleteSharedMusic(const std::string& name)
	{
		LOG_INFO("ResourceSystem::DeleteSharedMusic sound buffer name='" + name + " - was delet");
		auto musicPair = musics.find(name);

		sf::Music* deletingMusic = musicPair->second;
		musics.erase(musicPair);
		delete deletingMusic;
	}

	void ResourceSystem::LoadSoundBuffer(const std::string& name, std::string sourcePath)
	{
		LOG_INFO("ResourceSystem::LoadSoundBuffer name='" + name + "', path='" + sourcePath + " - starting");

		if (sounds.find(name) != sounds.end())
		{
			return;
		}

		sf::SoundBuffer* newSound = new sf::SoundBuffer();
		if (newSound->loadFromFile(sourcePath))
		{
			LOG_INFO("ResourceSystem::LoadSoundBuffer name='" + name + "', path='" + sourcePath + " - loaded successfully");
			sounds.emplace(name, newSound);
		}
		else
		{
			LOG_ERROR("ResourceSystem::LoadSoundBuffer name='" + name + "', path='" + sourcePath + " - FAILED to load");
		}
	}
	sf::SoundBuffer* ResourceSystem::GetSoundBufferShared(const std::string& name)
	{
		return sounds.find(name)->second;
	}
	void ResourceSystem::DeleteSharedSoundBuffer(const std::string& name)
	{
		LOG_INFO("ResourceSystem::GetSoundBufferShared sound buffer name='" + name + " - was delet");
		auto soundPair = sounds.find(name);

		sf::SoundBuffer* deletingSound = soundPair->second;
		sounds.erase(soundPair);
		delete deletingSound;
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllMusic();
		DeleteAllSoundsBuffer();
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}
	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}
	void ResourceSystem::DeleteAllMusic()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& musicPair : musics)
		{
			keysToDelete.push_back(musicPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedMusic(key);
		}
	}
	void ResourceSystem::DeleteAllSoundsBuffer()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& soundPair : sounds)
		{
			keysToDelete.push_back(soundPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedSoundBuffer(key);
		}
	}

}