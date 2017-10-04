#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>
#include "p2DynArray.h"

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	
	
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		Map = CallandFillMap(map_file);

	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

map j1Map::CallandFillMap(const pugi::xml_document& map_doc)
{	

	map ret;
	pugi::xml_node node = map_doc.child("map");
	ret.version = node.attribute("version").as_float();

	p2SString orientation = node.attribute("orientation").as_string();
	if (orientation == "orthogonal")
	{
		ret.orient = map::orthogonal;
	}
	else if (orientation == "isometric")
	{
		ret.orient = map::isometric;
	}

	p2SString renderorder = node.attribute("renderorder").as_string();
	if (renderorder == "right-down")
	{
		ret.renderor = map::DOWNRIGHT;
	}

	ret.width = node.attribute("width").as_int();
	ret.height = node.attribute("height").as_int();
	ret.tilewidth = node.attribute("tilewidth").as_int();
	ret.tileheight = node.attribute("tileheight").as_int();
	ret.nextobjectid = node.attribute("nextobjectid").as_int();

	pugi::xml_node tileset = node.child("tileset");

	ret.tileset.firstgid = tileset.attribute("firstgid").as_int();
	ret.tileset.name = tileset.attribute("name").as_string();
	ret.tileset.tilewidth = tileset.attribute("tilewidth").as_int();
	ret.tileset.tileheight = tileset.attribute("tileheight").as_int();
	ret.tileset.spacing = tileset.attribute("spacing").as_int();
	ret.tileset.margin = tileset.attribute("margin").as_int();

	return ret;
}

