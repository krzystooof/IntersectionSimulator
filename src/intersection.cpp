#include "intersection.hpp"
void Intersection::draw(sf::RenderWindow &window)
{
    for (auto i : lanes)
    {
        if (i->getType() == LaneType::asphalt || i->getType() == LaneType::asphaltLeft || i->getType() == LaneType::asphaltRight || i->getType() == LaneType::tram)
        {
            i->showLight();
        }
    }
    window.draw(this->center);
    if (!lanes2.empty())
        for (auto it : lanes2)
            it->draw(window);
    if (!lanes.empty())
        for (auto it : lanes)
            it->draw(window);
}
void Intersection::addVehicles(int amount)
{
    for (auto i : this->lanes)
        if (i->getType() == LaneType::asphalt || i->getType() == LaneType::asphaltRight || i->getType() == LaneType::asphaltLeft)
            i->addVehicle(CarCategory::car, amount);
        else if (i->getType() == LaneType::tram)
            i->addVehicle(CarCategory::tram, amount);
}
void Intersection::go()
{
    for (auto i : this->lanes)
    {
        if (i->getType() == LaneType::asphalt || i->getType() == LaneType::asphaltRight || i->getType() == LaneType::asphaltLeft || i->getType() == LaneType::tram)
        {
            if (i->getRotation() == 0)
            {
                if (i->getType() == LaneType::asphaltRight)
                {
                    i->go(Direction::up, Direction::right, sf::Vector2f(i->getPosition().x, i->getPosition().y - (laneWidth * 1.16f)));
                }
                else
                    i->go(Direction::up);
            }
            if (i->getRotation() == 180)
            {
                if (i->getType() == LaneType::asphaltRight)
                {
                    i->go(Direction::down, Direction::left, sf::Vector2f(i->getPosition().x, i->getPosition().y + (laneWidth * 1.16f)));
                }
                else
                    i->go(Direction::down);
            }
            if (i->getRotation() == 90)
            {
                if (i->getType() == LaneType::asphaltRight)
                {
                    i->go(Direction::right, Direction::down, sf::Vector2f(i->getPosition().x + (laneWidth * 1.16f), i->getPosition().y));
                }
                else
                    i->go(Direction::right);
            }
            if (i->getRotation() == 270)
            {
                if (i->getType() == LaneType::asphaltRight)
                {
                    i->go(Direction::left, Direction::up, sf::Vector2f(i->getPosition().x - (laneWidth * 1.16f), i->getPosition().y + (laneWidth * 1.16f)));
                }
                else
                    i->go(Direction::left);
            }
        }
    }
}
void Intersection::changeLight()
{
    for (auto i : lanes)
        i->changeLight();
}
