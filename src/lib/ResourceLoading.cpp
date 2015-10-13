#include "../include/ResourceLoading.hpp"

#include "../include/ResourceManager.hpp"

void LoadResources()
{
	ResourceManager* R = ResourceManager::Initialize();
	// Registering textures
	R->registerTexture("data/texture/static_dead_basic_robot.png", "Static Dead Basic Robot");
	R->registerTexture("data/texture/anim_basic_robot.png", "Animation Basic Robot");
	R->registerTexture("data/texture/testBackground.png", "Menu Background");
	R->registerTexture("data/texture/qb_panel.png", "Question Box Panel");
	R->registerTexture("data/texture/static_gear.png", "Static Gear");
	R->registerTexture("data/texture/static_ground_textures.png", "Static Ground Textures");
	R->registerTexture("data/texture/static_shadow.png", "Static Shadow");
	R->registerTexture("data/texture/static_road.png", "Static Road");
	// Registering fonts
	R->registerFont("data/font/Hanken-Book.ttf", "Global Font");
	// Registering musics

	// Registering sounds
}
