#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------
struct tile {
	uint firstgid;
	char* name;
	uint tilewidth;
	uint tileheight;
	uint spacing;
	uint margin;
};

// TODO 1: Create a struct needed to hold the information to Map node
struct map {
	uint version;
	enum orientation
	{
		orthogonal = 1,
		isometric
	};
	enum renderorder
	{
		RIGHT = 1,
		RIGHTUP,
		UP,
		LEFTUP,
		LEFT,
		LEFTDOWN,
		DOWN,
		DOWNRIGHT
	};
	uint width;
	uint height;
	uint tilewidth;
	uint tileheight;
	uint nextobjectid;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:
	map CallandFillMap();

public:

	// TODO 1: Add your struct for map info as public for now
	map Map;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__