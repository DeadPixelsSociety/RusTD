#include "../include/Creep.hpp"
#include "../include/Projectile.hpp"
#include "../include/ProjectileList.hpp"
#include "../include/tools.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Random.hpp"

Creep::Creep(void)
{
	this->m_tcreep = nullptr;
	this->m_current_health = 1.f;
	this->m_position = sf::Vector2f();
	this->m_state = 0;
	this->m_path_point_index = 0;
	this->m_aProjectile = new ProjectileList();
	this->m_sprite = new sf::Sprite(*(ResourceManager::Instance()->getTexture("Animation Basic Robot")));
	this->m_sprite->setOrigin(32, 32);
	this->m_animation = new Animation(m_sprite, sf::IntRect(0, 0, 64, 64), 10, 100);
	this->m_rand_dead = Random::NextFloat(0, 360);
}

Creep::Creep(TCreep* tc)
{
	this->m_tcreep = tc;
    if(tc!=nullptr)
    {
        this->m_current_health = this->m_tcreep->getStats().health;
    }
    this->m_position = sf::Vector2f();
    this->m_state = 0;
    this->m_path_point_index = 0;
	this->m_aProjectile = new ProjectileList();
	this->m_sprite = new sf::Sprite(*(ResourceManager::Instance()->getTexture("Animation Basic Robot")));
	this->m_sprite->setOrigin(32, 32);
	this->m_animation = new Animation(m_sprite, sf::IntRect(0, 0, 64, 64), 10, 100);
	this->m_rand_dead = Random::NextFloat(0, 360);
}

Creep::~Creep(void)
{
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

int Creep::getState(void)
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

void Creep::update(float dt)
{
    if(this->m_state==0 && this->m_current_health<=0.f)
    {
        this->m_state = 1;
    }

    if(this->m_state>0)
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
}

void Creep::render(sf::RenderWindow& window)
{
    if(this->m_state>0)
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

        sf::RectangleShape health_bar_back(sf::Vector2f(20, 3));
        health_bar_back.setFillColor(sf::Color::Red);
        health_bar_back.setOrigin(10,2);
        health_bar_back.setPosition(sf::Vector2f(this->m_position.x,this->m_position.y-15));
        window.draw(health_bar_back);

        float pour_cd = MAX(0.f,this->m_current_health / this->m_tcreep->getStats().health);
        sf::RectangleShape health_bar(sf::Vector2f(pour_cd*20, 3));
        health_bar.setFillColor(sf::Color::Green);
        health_bar.setOrigin(10,2);
        health_bar.setPosition(sf::Vector2f(this->m_position.x,this->m_position.y-15));
        window.draw(health_bar);
    }
}
