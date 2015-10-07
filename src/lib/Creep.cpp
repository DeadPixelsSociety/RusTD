#include "../include/Creep.hpp"
#include "../include/Projectile.hpp"
#include "../include/ProjectileList.hpp"
#include "../include/tools.hpp"

Creep::Creep(void)
{
	this->m_tcreep = nullptr;
	this->m_current_health = 1.f;
	this->m_position = sf::Vector2f();
	this->m_state = 0;
	this->m_path_point_index = 0;
	this->m_aProjectile = new ProjectileList();
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
}

Creep::~Creep(void)
{}

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

void Creep::setPath(std::vector<sf::Vector2f>& path)
{
    this->m_path = path;
    this->m_position = path[0];
    this->m_path_point_index = 1;
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

    if(this->m_path_point_index<this->m_path.size())
    {
        if(getDistanceBetweenPoints(this->m_path[this->m_path_point_index],this->m_position)<0.1f)
        {
            this->m_path_point_index++;
        }
        sf::Vector2f move_point = this->m_path[this->m_path_point_index];

        float distance_x = move_point.x - this->m_position.x;
        float distance_y = move_point.y - this->m_position.y;
        float distance = sqrt(pow(distance_x,2) + pow(distance_y,2));
        if(distance!=0.f)
        {
            float coef = this->m_tcreep->getMovement().speed*dt / distance;
            sf::Vector2f vec_speed = sf::Vector2f(distance_x*coef, distance_y*coef);
            this->m_position += vec_speed;
        }
    }
}

void Creep::render(sf::RenderWindow& window)
{
    sf::CircleShape shape(10);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(this->m_position);
    shape.setOrigin(10,10);

    if(this->m_state>0)
    {
        shape.setFillColor(sf::Color::Yellow);
    }
    else
    {
        sf::RectangleShape health_bar_back(sf::Vector2f(20, 3));
        health_bar_back.setFillColor(sf::Color::Red);
        health_bar_back.setOrigin(10,2);
        health_bar_back.setPosition(sf::Vector2f(this->m_position.x,this->m_position.y-12));
        window.draw(health_bar_back);

        float pour_cd = MAX(0.f,this->m_current_health / this->m_tcreep->getStats().health);
        sf::RectangleShape health_bar(sf::Vector2f(pour_cd*20, 3));
        health_bar.setFillColor(sf::Color::Green);
        health_bar.setOrigin(10,2);
        health_bar.setPosition(sf::Vector2f(this->m_position.x,this->m_position.y-12));
        window.draw(health_bar);
    }
    window.draw(shape);
}
