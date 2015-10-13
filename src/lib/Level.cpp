#include "../include/Level.hpp"

Level::Level(void)
{
    this->m_cl = new CreepList();
    this->m_pl = new ProjectileList();
    this->m_tl = new TowerList();
    this->m_path.push_back(sf::Vector2i(2,-1));
    this->m_path.push_back(sf::Vector2i(2,2));
    this->m_path.push_back(sf::Vector2i(5,2));
    this->m_path.push_back(sf::Vector2i(5,5));
    this->m_path.push_back(sf::Vector2i(10,5));
    this->m_path.push_back(sf::Vector2i(10,2));
    this->m_path.push_back(sf::Vector2i(5,2));
    this->m_path.push_back(sf::Vector2i(5,12));
//
    this->t_creep_spawn_cd = 100000.f;

    Random::SetSeed(time(NULL));
}

Level::~Level(void)
{}

void Level::addCreep(Creep* cre)
{
    cre->setPath(this->m_path);
    this->m_cl->addCreep(cre);
}

void Level::addTower(Tower* tow)
{
    this->m_tl->addTower(tow);
}

void Level::update(float dt)
{
    this->m_tl->attackList(this->m_pl,this->m_cl);

//
    this->t_creep_spawn_cd += dt;
    if(this->t_creep_spawn_cd>=1.5f)
    {
        Movement move = Movement();
        move.speed = 100.f;

        int rand_creep_index = Random::NextInt(0, 1);
        move.type = UnitType::GROUND;

        if(rand_creep_index==0)
        {
            //move.type = UnitType::AIR;
        }

        Stats sta = Stats();
        sta.bounty = 3;
        sta.health = 11.f;
        sta.health_regen = 0.f;
        TCreep* tc = new TCreep(1, "Monstre", move, sta);

        Creep* new_c = new Creep(tc);
        this->addCreep(new_c);
        this->t_creep_spawn_cd = 0.f;
    }
//

    this->m_cl->update(dt);
    this->m_tl->update(dt);
    this->m_pl->update(dt);
}

void Level::render(sf::RenderWindow& window)
{
/*
    int i;
    int size = this->m_path.size()-1;
    for(i=0 ; i<size ; i++)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(this->m_path[i]),
            sf::Vertex(this->m_path[i+1])
        };
        window.draw(line, 2, sf::Lines);
    }
*/
    this->m_cl->render(window);
    this->m_tl->render(window);
    this->m_pl->render(window);
}
