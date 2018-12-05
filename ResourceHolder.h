#pragma once
#include "stdafx.h"


namespace Resource
{
	enum ID
	{
		// Textures
		Background, Menu, Sound, backCard, frontCard,

		// Sounds
		Click, cardFlip
	};
}


template <class T>
class ResourceHolder
{
private:

	std::unordered_map<std::string, std::shared_ptr<T>> resources;

public:

	void load(Resource::ID id, const std::string &filename)
	{
		T resource;
		if (!resource.loadFromFile(filename))
			throw std::runtime_error("Error! Failed to open file " + filename);
		resources.emplace(filename, std::make_shared<T>(resource));
	}

	const std::shared_ptr<T>& get(const std::string &filename)
	{
		return resources[filename];
	}
};