#include "../include/ResourceLoading.hpp"
#include "../include/config.hpp"
#include "../include/ResourceManager.hpp"

void LoadResources()
{
	ResourceManager* R = ResourceManager::Initialize();
	// Registering textures
	R->registerTexture(DATA_DIR"texture/static_dead_basic_robot.png", "Static Dead Basic Robot");
	R->registerTexture(DATA_DIR"texture/anim_basic_robot.png", "Animation Basic Robot");
	R->registerTexture(DATA_DIR"texture/testBackground.png", "Menu Background");
	R->registerTexture(DATA_DIR"texture/qb_panel.png", "Question Box Panel");
	R->registerTexture(DATA_DIR"texture/static_gear.png", "Static Gear");
	R->registerTexture(DATA_DIR"texture/static_ground_textures.png", "Static Ground Textures");
	R->registerTexture(DATA_DIR"texture/static_shadow.png", "Static Shadow");
	R->registerTexture(DATA_DIR"texture/static_road.png", "Static Road");
	R->registerTexture(DATA_DIR"texture/static_option_background.png", "Static Option Background");
	// Registering fonts
	R->registerFont(DATA_DIR"font/Hanken-Book.ttf", "Global Font");
	// Registering musics

	// Registering sounds
}
