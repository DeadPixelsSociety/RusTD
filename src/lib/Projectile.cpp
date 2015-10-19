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

Projectile::Projectile(void)
{
	this->m_speed = 0.f;
	this->m_damage = 0.f;
	this->m_target = nullptr;
	this->m_position = sf::Vector2f();
	this->m_target_sign = sf::Vector2i();
	this->m_state = 0.f;
}

Projectile::Projectile(float speed, float damage, Creep* target, sf::Vector2f position)
{
	this->m_speed = speed;
	this->m_damage = damage;
	this->m_target = target;
	this->m_position = position;
	this->m_state = 0;

	sf::Vector2f target_pos = this->m_target->getPosition();
	sf::Vector2f v = sf::Vector2f(position.x - target_pos.x,position.y - target_pos.y);
	this->m_target_sign = sf::Vector2i();
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

Projectile::~Projectile(void)
{}

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
    sf::Vector2f target_pos = this->m_target->getPosition();
    float distance_x = target_pos.x - this->m_position.x;
    float distance_y = target_pos.y - this->m_position.y;
    float distance = sqrt(pow(distance_x,2) + pow(distance_y,2));

    if((distance_x==0.f && distance_y==0.f) ||
        distance<10.f ||
        (((distance_x<0.f && this->m_target_sign.x==-1) || (distance_x>0.f && this->m_target_sign.x==1)) &&
            ((distance_y<0.f && this->m_target_sign.y==-1) || (distance_y>0.f && this->m_target_sign.y==1))))
    {
        this->m_position = target_pos;
        if(this->m_state==0)
        {
            this->m_target->takeDamage(this->m_damage);
        }
        this->m_state = 1;
        return;
    }

    float coef = this->m_speed*dt / distance;
    sf::Vector2f vec_speed = sf::Vector2f(distance_x*coef, distance_y*coef);

    this->m_position += vec_speed;
}

void Projectile::render(sf::RenderWindow& window)
{
    sf::CircleShape shape(5);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(this->m_position);
    shape.setOrigin(5,5);
    window.draw(shape);
}

