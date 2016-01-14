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
#include <iostream>

#include "../include/Random.hpp"
#include "../include/Tower.hpp"
#include "../include/tools.hpp"
#include "../include/ResourceManager.hpp"


Tower::Tower(void)
: Tower(nullptr,sf::Vector2i(),0)
{}

Tower::Tower(TTower* tt, sf::Vector2i position)
: Tower(tt,position,0)
{}

Tower::Tower(TTower* tt, sf::Vector2i position, unsigned int rank)
: m_ttower(tt)
, m_position(position)
, m_attack_cooldown(0.f)
, m_last_target(nullptr)
, m_show_range_indicator(false)
, m_proj_speed(500.f) // DEFAULT
, m_rank(rank)
{
	Attack attack = tt->getAttack();
	this->m_damage = attack.damage_base + m_rank*attack.damage_bonus;

    std::cout << "**********:" << tt->getBaseIdent();
}

Tower::~Tower(void)
{}

void Tower::enableRangeIndicator(bool e)
{
    this->m_show_range_indicator = e;
}

void Tower::setTarget(Creep* c)
{
    this->m_last_target = c;
}

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
    return (att.availableTarget[tc->getMovement().type] && this->inRange(c) && c->getState()==CreepState::Normal);
}

bool Tower::isTowerPosition(sf::Vector2i placement)
{
    return (this->m_position.x==placement.x && this->m_position.y== placement.y);
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

    //Attack att = this->m_ttower->getAttack();

    // Lancement du cooldown de l'attaque
    this->m_attack_cooldown = this->m_ttower->getAttack().speed;

    //
    float offset = GRID_UNIT/2.f;
    sf::Vector2f tower_pos = getConvertedPosition(this->m_position)+sf::Vector2f(offset,offset);
    Projectile* p = new Projectile(this->m_proj_speed, this->m_damage, c, tower_pos);
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

    //window.draw(shape);
    window.draw(cooldown_bar_back);
    window.draw(cooldown_bar);

    if(this->m_show_range_indicator)
    {
        Attack att = this->m_ttower->getAttack();
        if(att.range.maximal>0)
        {
            sf::CircleShape max_range;
            max_range.setRadius(att.range.maximal);
            max_range.setOrigin(sf::Vector2f(att.range.maximal-GRID_UNIT/2,att.range.maximal-GRID_UNIT/2));
            max_range.setOutlineThickness(3.f);
            max_range.setFillColor(sf::Color(0,0,0,0));
            max_range.setOutlineColor(RANGE_INDICATOR_LIMIT_COLOR);
            max_range.setPosition(tower_pos);
            window.draw(max_range);
        }

        if(att.range.minimal>0)
        {
            sf::CircleShape min_range;
            min_range.setRadius(att.range.minimal);
            min_range.setOrigin(sf::Vector2f(att.range.minimal-GRID_UNIT/2,att.range.minimal-GRID_UNIT/2));
            min_range.setOutlineThickness(3.f);
            min_range.setFillColor(sf::Color(0,0,0,0));
            min_range.setOutlineColor(RANGE_INDICATOR_LIMIT_COLOR);
            min_range.setPosition(tower_pos);
            window.draw(min_range);
        }

        if(att.range.minimal>=0 && att.range.maximal>0 && att.range.maximal>att.range.minimal)
        {
            sf::CircleShape range;
            if(att.range.minimal==0)
            {
                range.setRadius(att.range.maximal);
                range.setFillColor(RANGE_INDICATOR_ZONE_COLOR);
                range.setOrigin(sf::Vector2f(att.range.maximal-GRID_UNIT/2,att.range.maximal-GRID_UNIT/2));
            }
            else
            {
                range.setRadius(att.range.minimal);
                range.setOutlineThickness(att.range.maximal-att.range.minimal);
                range.setFillColor(sf::Color(0,0,0,0));
                range.setOutlineColor(RANGE_INDICATOR_ZONE_COLOR);
                range.setOrigin(sf::Vector2f(att.range.minimal-GRID_UNIT/2,att.range.minimal-GRID_UNIT/2));
            }
            range.setPosition(tower_pos);
            window.draw(range);
        }
    }

	sf::Sprite sprite;
    sprite.setTexture(*ResourceManager::Instance()->getTexture(this->m_ttower->getBaseIdent()));
	sprite.setScale(0.25, 0.25);
	sprite.setPosition(shape.getPosition());
	sf::Sprite head;
	head.setTexture(*ResourceManager::Instance()->getTexture(this->m_ttower->getHeadIdent()));
	head.setScale(0.25, 0.25);
	head.setPosition(shape.getPosition() + sf::Vector2f(32, 32));
	head.setOrigin(128, 128);
	if(m_last_target != nullptr)
	{
		sf::Vector2f diff = m_last_target->getPosition() - head.getPosition();
		float rotation = atan2(diff.x, -diff.y) + 270.f;
		head.setRotation(rotation * 180 / 3.14);
	}
    window.draw(sprite);
    window.draw(head);
    window.draw(cooldown_bar_back);
    window.draw(cooldown_bar);
}

