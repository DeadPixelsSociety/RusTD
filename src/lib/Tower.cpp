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
#include <cmath>

#include <cstdio>

#include "../include/Random.hpp"
#include "../include/Tower.hpp"
#include "../include/tools.hpp"

Tower::Tower(void)
: Tower(nullptr,sf::Vector2i())
{}

Tower::Tower(TTower* tt, sf::Vector2i position)
: m_attack_cooldown(0.f)
, m_proj_speed(500.f)
, m_last_target(nullptr)
, m_show_range(false)
{
	this->m_ttower = tt;
	this->m_position = position;
}

Tower::~Tower(void)
{}

bool Tower::inRange(Creep* c)
{
    if(c==nullptr)
    {
        return false;
    }

    Attack att = this->m_ttower->getAttack();

    sf::Vector2f last_target_pos = c->getPosition();
    sf::Vector2f tower_pos = getConvertedPosition(this->m_position);
    float distance = getDistanceBetweenPoints(tower_pos,last_target_pos);

    return (distance>=att.range.minimal && distance<=att.range.maximal);
}

bool Tower::canAttack(Creep* c)
{
    TCreep* tc = c->getTCreep();
    Attack att = this->m_ttower->getAttack();
    return (att.availableTarget[tc->getMovement().type] && this->inRange(c));
}

bool Tower::isPlacementAvailable(sf::Vector2i placement)
{
    return !(this->m_position.x == placement.x && this->m_position.y == placement.y);
}

Projectile* Tower::attackList(CreepList* ac)
{
    // Can attack ?
    if(this->m_attack_cooldown>0.f)
    {
        return nullptr;
    }

    Creep* new_target = nullptr;

    if(this->m_last_target!=nullptr && this->m_last_target->getState()==CreepState::Normal)
    {
        if(this->inRange(this->m_last_target))
        {
            new_target = this->m_last_target;
        }
    }
    else
    {
        int i;
        int size = ac->getSize();
        std::vector<Creep*> aCreep;
        for(i=0 ; i<size ; i++)
        {
            Creep* cc = ac->getCreep(i);
            if(cc==this->m_last_target)
            {
                continue;
            }

            if(this->canAttack(cc) && cc->getState()==CreepState::Normal)
            {
                aCreep.push_back(cc);
            }
        }
        size = aCreep.size();
        if(size>0)
        {
            int rand_creep_index = Random::NextInt(0,size-1);
            new_target = aCreep[rand_creep_index];
        }
    }

    return this->attack(new_target);
}

Projectile* Tower::attack(Creep* c)
{
    this->m_last_target = c;
    if(c==nullptr)
    {
        return nullptr;
    }

    Attack att = this->m_ttower->getAttack();

    // Lancement du cooldown de l'attaque
    this->m_attack_cooldown = this->m_ttower->getAttack().speed;

    //
    float offset = GRID_UNIT/2.f;
    sf::Vector2f tower_pos = getConvertedPosition(this->m_position)+sf::Vector2f(offset,offset);
    Projectile* p = new Projectile(this->m_proj_speed, att.damage, c, tower_pos);
    c->addProjectile(p);
    return p;
}

void Tower::update(float dt)
{
    this->m_attack_cooldown -= dt;
}

void Tower::render(sf::RenderWindow& window)
{
    sf::Vector2f tower_pos = getConvertedPosition(this->m_position);
    sf::Vector2f cooldown_bar_pos = tower_pos+COOLDOWN_BAR_OFFSET;

    sf::RectangleShape shape(sf::Vector2f(GRID_UNIT,GRID_UNIT));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(tower_pos);

    sf::RectangleShape cooldown_bar_back(COOLDOWN_BAR_RECTANGLE);
    cooldown_bar_back.setFillColor(sf::Color::Yellow);
    cooldown_bar_back.setPosition(cooldown_bar_pos);

    float pour_cd = MAX(0.f,this->m_attack_cooldown / this->m_ttower->getAttack().speed);
    sf::RectangleShape cooldown_bar(sf::Vector2f(pour_cd*COOLDOWN_BAR_RECTANGLE.x,COOLDOWN_BAR_RECTANGLE.y));
    cooldown_bar.setFillColor(sf::Color::Red);
    cooldown_bar.setPosition(cooldown_bar_pos);


    if(this->m_show_range)
    {
        Attack att = this->m_ttower->getAttack();

        sf::CircleShape range;
        if(att.range.minimal==0)
        {
            range.setRadius(att.range.maximal);
            range.setOrigin(sf::Vector2f(att.range.maximal-GRID_UNIT/2,att.range.maximal-GRID_UNIT/2));
            range.setOutlineThickness(1.f);
        }
        else
        {
            range.setRadius(att.range.minimal);
            range.setOrigin(sf::Vector2f(att.range.minimal-GRID_UNIT/2,att.range.minimal-GRID_UNIT/2));
            range.setOutlineThickness(att.range.maximal-att.range.minimal);
        }

        range.setFillColor(sf::Color(255, 255, 255, 0));
        range.setOutlineColor(sf::Color(255, 255, 255, 150));
        range.setPosition(tower_pos);
        window.draw(range);
    }


    window.draw(shape);
    window.draw(cooldown_bar_back);
    window.draw(cooldown_bar);
}

