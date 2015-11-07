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
#include "../include/Projectile.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Random.hpp"

Projectile::Projectile(void)
: Projectile(0.f,0.f,nullptr,sf::Vector2f())
{}

Projectile::Projectile(float speed, float damage, Creep* target, sf::Vector2f position)
: m_speed(speed)
, m_damage(damage)
, m_target(target)
, m_position(position)
, m_state(0)
, m_life_time(0.f)
{
    this->m_target_sign = sf::Vector2i();

    if(this->m_target!=nullptr) {
        sf::Vector2f target_pos = this->m_target->getPosition();
        sf::Vector2f v = sf::Vector2f(position.x - target_pos.x,position.y - target_pos.y);
        if(v.x<0)
        {
            this->m_target_sign.x = -1;
        }
        else
        {
            this->m_target_sign.x = 1;
        }
        if(v.y<0)
        {
            this->m_target_sign.y = -1;
        }
        else
        {
            this->m_target_sign.y = 1;
        }
    }

	this->m_sprite = new sf::Sprite(*(ResourceManager::Instance()->getTexture("Static Water Projectile")));
	this->m_sprite->setRotation(Random::NextFloat(0.0f, 360.f));
	this->m_sprite->setOrigin(32.0f, 32.0f);

	this->m_sprite_splash = new sf::Sprite(*(ResourceManager::Instance()->getTexture("Animation Water Splash")));
	this->m_sprite_splash->setOrigin(32.0f, 32.0f);
    this->m_animation_splash = new Animation(2, "", this->m_sprite_splash, sf::IntRect(0, 0, 64, 64), 10, 100);
}

Projectile::~Projectile(void)
{
	delete this->m_sprite;
	delete this->m_animation_splash;
	delete this->m_sprite_splash;
}

sf::Vector2f Projectile::getPosition(void)
{
    return this->m_position;
}

int Projectile::getState(void)
{
    return this->m_state;
}

Creep* Projectile::getTarget(void)
{
    return this->m_target;
}

void Projectile::update(float dt)
{
    this->m_life_time += dt;
    sf::Vector2f target_pos = this->m_target->getPosition();

    if(this->m_state==0) {
        float distance_x = target_pos.x - this->m_position.x;
        float distance_y = target_pos.y - this->m_position.y;
        float distance = sqrt(pow(distance_x,2) + pow(distance_y,2));

        if((distance_x==0.f && distance_y==0.f) || distance<10.f ||
            (((distance_x<0.f && this->m_target_sign.x==-1) || (distance_x>0.f && this->m_target_sign.x==1)) &&
                ((distance_y<0.f && this->m_target_sign.y==-1) || (distance_y>0.f && this->m_target_sign.y==1))))
        {
            this->m_position = target_pos;
            if(this->m_state==0)
            {
                this->m_target->takeDamage(this->m_damage);
            }
            this->m_state = 1;
            this->m_life_time = 0.f;
            //return;
        }

        // Movement
        float coef = this->m_speed*dt / distance;
        sf::Vector2f vec_speed = sf::Vector2f(distance_x*coef, distance_y*coef);
        this->m_position += vec_speed;
    }


    if(this->m_state==1)
    {
        this->m_position = target_pos;
        if(this->m_life_time<1.f)
        {
            this->m_animation_splash->update(dt);
        }
        else
        {
            this->m_state = 2;
        }
    }
}

void Projectile::render(sf::RenderWindow& window)
{
    /*sf::CircleShape shape(5);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(this->m_position);
    shape.setOrigin(5,5);
    window.draw(shape);*/

    float factor;
    switch(this->m_state)
    {
        case 0: //Projectile
            factor = PROJECTILE_MIN_SCALE + ((PROJECTILE_MAX_SCALE - PROJECTILE_MIN_SCALE) * (m_life_time / PROJECTILE_FULL_SCALE_TIME));
            this->m_sprite->setScale(factor, factor);
            this->m_sprite->setPosition(this->m_position);
            window.draw(*(this->m_sprite));
            break;

        case 1: //Splash
            this->m_sprite_splash->setPosition(this->m_position);
            window.draw(*(this->m_sprite_splash));
            break;

        default:
            break;
    }
}

