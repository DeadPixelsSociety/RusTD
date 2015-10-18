#include "../include/ResourceLoading.hpp"
#include "../include/config.hpp"
#include "../include/ResourceManager.hpp"

void LoadResources(Data* data)
{
#if ENTITIES_LOADING_MODE == LOAD_XML
	ResourceManager* R = ResourceManager::Initialize();
	// Registering textures
	R->registerTexture(DATA_DIR"texture/static_dead_basic_robot.png", "Static Dead Basic Robot");
	R->registerTexture(DATA_DIR"texture/animation_basic_robot.png", "Animation Basic Robot");
	R->registerTexture(DATA_DIR"texture/menu_background.png", "Menu Background");
	R->registerTexture(DATA_DIR"texture/qusetion_box_panel.png", "Question Box Panel");
	R->registerTexture(DATA_DIR"texture/static_gear.png", "Static Gear");
	R->registerTexture(DATA_DIR"texture/static_ground_textures.png", "Static Ground Textures");
	R->registerTexture(DATA_DIR"texture/static_shadow.png", "Static Shadow");
	R->registerTexture(DATA_DIR"texture/static_road.png", "Static Road");
	R->registerTexture(DATA_DIR"texture/static_option_background.png", "Static Option Background");
	// Registering fonts
	R->registerFont(DATA_DIR"font/global_font.ttf", "Global Font");
	// Registering musics

	// Registering sounds

#else // ENTITIES_LOADING_MODE != LOAD_XML
	ResourceManager* R = ResourceManager::Initialize();
	if(data == nullptr)
	{
		return;
	}
	// Registering textures
	R->loadTexturesFromData(*data);
	// Registering fonts
	R->loadFontsFromData(*data);
	// Registering musics
	R->loadMusicsFromData(*data);
	// Register sounds
	R->loadSoundsFromData(*data);
#endif // ENTITIES_LOADING_MODE == LOAD_XML
}
