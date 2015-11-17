/*

	RusTD - A rusted Tower Defense game
    Copyright (C) 2015  Beuzmoker, Enferium, Farijo, Vizepi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "../include/Creep.hpp"
#include "../include/Projectile.hpp"
#include "../include/ProjectileList.hpp"
#include "../include/tools.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Random.hpp"

#define HEALTH_BAR_LENGTH 30

Creep::Creep(void)
: Creep(nullptr)
{}

Creep::Creep(TCreep* tc)
: m_position(sf::Vector2f())
, m_path_point_index(0)
, m_hover_indicator(false)
{
	this->m_tcreep = tc;
    if(tc!=nullptr)
    {
        this->m_current_health = this->m_tcreep->getStats().health;
    }
    this->m_state = CreepState::Normal;
    this->m_aProjectile = new ProjectileList();
	this->m_sprite = new sf::Sprite(*(ResourceManager::Instance()->getTexture("Animation Basic Robot")));
	this->m_sprite->setOrigin(32, 32);
	// TODO get the animation from index and doodad, replace by following two lines
	// this->m_animation = TDoodad::getAnimation(0);
	// this->m_animation->setSprite(m_sprite);
	this->m_animation = new Animation(0, "", m_sprite, sf::IntRect(0, 0, 64, 64), 10, 100);
	this->m_rand_dead = Random::NextFloat(0, 360);
}

Creep::~Creep(void)
{
	// TODO suppress delete animation
	delete this->m_animation;
	delete this->m_sprite;
	delete this->m_aProjectile;
}

TCreep* Creep::getTCreep(void)
{
    return this->m_tcreep;
}

sf::Vector2f Creep::getPosition(void)
{
    return this->m_position;
}

CreepState Creep::getState(void)
{
    return this->m_state;
}

float Creep::getCurrentHealth(void)
{
    return this->m_current_health;
}

void Creep::setPath(std::vector<sf::Vector2i>& path)
{
    this->m_path = path;
    this->m_next_point = getConvertedPosition(path[0]);
    this->m_next_point.x += Random::NextFloat(16.f, 48.f);
    this->m_position = m_next_point;
    this->m_path_point_index = 0;
}

void Creep::setState(CreepState state)
{
    this->m_state = state;
}

void Creep::setHoverIndicatorEnabled(bool e)
{
    this->m_hover_indicator = e;
}

void Creep::addProjectile(Projectile* proj)
{
    this->m_aProjectile->addProjectile(proj);
}

void Creep::removeProjectile(Projectile* proj)
{
    this->m_aProjectile->removeProjectile(proj);
}

bool Creep::isChasedByProjectile(void)
{
    return !(this->m_aProjectile->isEmpty());
}

void Creep::takeDamage(float damage)
{
    this->m_current_health = MAX(0.f,this->m_current_health-damage);
}

bool Creep::collide(sf::Vector2f position)
{
    float distance_x = position.x - this->m_position.x;
    float distance_y = position.y - this->m_position.y;

    return distance_x*distance_x + distance_y*distance_y < CREEP_SELECTION_RADIUS*CREEP_SELECTION_RADIUS;
}

void Creep::update(float dt)
{
    if(this->m_state==CreepState::Normal && this->m_current_health<=0.f)
    {
        this->m_state = CreepState::Dead;
    }

    if(this->m_state!=CreepState::Normal)
    {
        return;
    }

    if(this->m_path_point_index < this->m_path.size())
    {
        if(getDistanceBetweenPoints(this->m_next_point, this->m_position) < 1.f)
        {
        	this->m_position = m_next_point;
            this->m_path_point_index++;
            this->m_next_point = getConvertedPosition(this->m_path[this->m_path_point_index]);
            this->m_next_point.x += Random::NextFloat(16.f, 48.f);
            this->m_next_point.y += Random::NextFloat(16.f, 48.f);
        }

        float distance_x = m_next_point.x - this->m_position.x;
        float distance_y = m_next_point.y - this->m_position.y;
        float distance = sqrt(pow(distance_x,2) + pow(distance_y,2));
        if(distance!=0.f)
        {
            float coef = this->m_tcreep->getMovement().speed*dt / distance;
            sf::Vector2f vec_speed = sf::Vector2f(distance_x*coef, distance_y*coef);
            this->m_position += vec_speed;
			this->m_sprite->setPosition(this->m_position);
			this->m_sprite->setRotation(RAD_TO_DEG(getLookingAngle(vec_speed)) - 90.f);
        }
    }
	this->m_animation->update(dt);
	float coef = this->m_current_health / this->m_tcreep->getStats().health;
	this->m_sprite->setColor(sf::Color(200 + 55 * coef, 100 + 155 * coef, 255 * coef));
}

void Creep::renderCreep(sf::RenderWindow& window)
{
    if(this->m_state==CreepState::Dead)
    {
    	sf::Sprite dead(*(ResourceManager::Instance()->getTexture("Static Dead Basic Robot")));
    	dead.setOrigin(32, 32);
    	dead.setPosition(this->m_position);
    	dead.setRotation(m_rand_dead);
        window.draw(dead);
    }
    else
    {
    	sf::Sprite shadow(*(ResourceManager::Instance()->getTexture("Static Shadow")));
    	shadow.setOrigin(32, 32);
    	shadow.setPosition(this->m_position);
    	window.draw(shadow);
		window.draw(*m_sprite);
    }
}

void Creep::renderDialog(sf::RenderWindow& window)
{
	sf::RectangleShape health_bar_back(sf::Vector2f(HEALTH_BAR_LENGTH, 3));
	health_bar_back.setFillColor(sf::Color::Red);
	health_bar_back.setOrigin(HEALTH_BAR_LENGTH/2,2);
	health_bar_back.setPosition(sf::Vector2f(this->m_position.x,this->m_position.y-15));

	float pour_cd = MAX(0.f,this->m_current_health/this->m_tcreep->getStats().health);
	sf::RectangleShape health_bar(sf::Vector2f(pour_cd*HEALTH_BAR_LENGTH, 3));
	health_bar.setFillColor(sf::Color::Green);
	health_bar.setOrigin(HEALTH_BAR_LENGTH/2,2);
	health_bar.setPosition(sf::Vector2f(this->m_position.x,this->m_position.y-15));

    if(this->m_hover_indicator)
    {
        sf::CircleShape hover_indicator;
        hover_indicator.setRadius(CREEP_SELECTION_RADIUS);
        hover_indicator.setOrigin(sf::Vector2f(CREEP_SELECTION_RADIUS,CREEP_SELECTION_RADIUS));
        hover_indicator.setOutlineThickness(3.f);
        hover_indicator.setFillColor(sf::Color(0,0,0,0));
        hover_indicator.setOutlineColor(sf::Color(255,100,100,150));
        hover_indicator.setPosition(this->m_position);
        window.draw(hover_indicator);
    }

	window.draw(health_bar_back);
	window.draw(health_bar);
}

