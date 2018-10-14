#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer
// ----------------------------------------------------
struct MapLayer
{
	p2SString			name;
	uint				width;
	uint				height;
	uint*				data;
	
	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}
	
	inline uint Get(int x, int y) const;
	/*~MapLayer()
	{
		if (data != nullptr) delete data;
	}*/
};

	// TODO 6: Short function to get the value of x,y
struct ImageLayer
{
	SDL_Rect GetParalaxRect() const;

	p2SString	name;
	int			width;
	int			height;
	SDL_Texture* texture;

	ImageLayer() {}

	~ImageLayer() {}

};

uint MapLayer::Get(int x, int y) const {
	return (y * width) + x;
}

// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<ImageLayer*> parallax;
	// TODO 2: Add a list/array of layers to the map!
	p2List<MapLayer*> layers;
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

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single laye
	bool LoadLayer(const pugi::xml_node& node, MapLayer* layer);
	bool Colliders_on_map(const char * filename);
	bool LoadParallax(pugi::xml_node& node, ImageLayer* image);
	TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData data;
	pugi::xml_document	map_file;

private:

	
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__