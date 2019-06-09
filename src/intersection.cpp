#include "intersection.hpp"
#include <algorithm>

void Intersection::draw(sf::RenderWindow &window)
{
    for (auto i : lanes)
    {
        if (i->getType() == LaneType::asphalt || i->getType() == LaneType::asphaltLeft || i->getType() == LaneType::asphaltRight || i->getType() == LaneType::tram)
        {
            i->showLight();
        }
    }
    window.draw(this->backgorund);
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
    // for (auto i : this->lanes2)
    //     if (i->getType() == LaneType::pedestrian)
    //         i->addVehicle(CarCategory::pedestrian, amount);
}
void Intersection::addVehicles(int amount, Direction direction)
{
    int angle;
    if (direction == Direction::up)
        angle = 0;
    else if (direction == Direction::down)
        angle = 180;
    else if (direction == Direction::right)
        angle = 90;
    else if (direction == Direction::left)
        angle = 270;
    for (auto i : this->lanes)
    {
        if (i->getRotation() == angle && (i->getType() == LaneType::asphalt || i->getType() == LaneType::asphaltRight || i->getType() == LaneType::asphaltLeft))
            i->addVehicle(CarCategory::car, amount);
        else if (i->getRotation() == angle && i->getType() == LaneType::tram)
        {
            int random = rand() % 3 - 1;
            if (random < 0)
                random = 0;
            i->addVehicle(CarCategory::tram, random);
        }
    }
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
                else if (i->getType() == LaneType::pedestrian)
                {
                    i->go(Direction::up, Direction::down, sf::Vector2f(i->getPosition().x, i->getPosition().y));
                }
                else if (i->getType() == LaneType::asphaltLeft)
                {
                    i->go(Direction::up, Direction::left, sf::Vector2f(i->getPosition().x, i->getPosition().y - (leftLanes * (laneWidth * 1.16f))));
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
                else if (i->getType() == LaneType::pedestrian)
                {
                    i->go(Direction::down, Direction::up, sf::Vector2f(i->getPosition().x, i->getPosition().y));
                }
                else if (i->getType() == LaneType::asphaltLeft)
                {
                    i->go(Direction::down, Direction::right, sf::Vector2f(i->getPosition().x, i->getPosition().y + (leftLanes * (laneWidth * 1.16f))));
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
                else if (i->getType() == LaneType::pedestrian)
                {
                    i->go(Direction::right, Direction::left, sf::Vector2f(i->getPosition().x, i->getPosition().y));
                }
                else if (i->getType() == LaneType::asphaltLeft)
                {
                    i->go(Direction::right, Direction::up, sf::Vector2f(i->getPosition().x + (upLanes * (laneWidth * 1.16f)), i->getPosition().y));
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
                else if (i->getType() == LaneType::pedestrian)
                {
                    i->go(Direction::left, Direction::right, sf::Vector2f(i->getPosition().x, i->getPosition().y));
                }
                else if (i->getType() == LaneType::asphaltLeft)
                {
                    i->go(Direction::left, Direction::down, sf::Vector2f(i->getPosition().x - (upLanes * (laneWidth * 1.16f)), i->getPosition().y + (laneWidth * 1.16f)));
                }
                else
                    i->go(Direction::left);
            }
        }
    }
}
int Intersection::getGreenLightGroup() const
{
    for (auto i : this->lanes)
    {
        if (i->getLight() == false)
            return i->getGroup();
    }
    return -1;
}
void Intersection::setGroups(LightChangingType lightChangingType)
{
    if (lightChangingType == LightChangingType::smart)
    {
        for (auto i : lanes)
        {
            if ((i->getRotation() == 0 || i->getRotation() == 180) && (i->getType() == LaneType::asphalt || i->getType() == LaneType::tram || i->getType() == LaneType::asphaltRight))
            {
                i->setGroup(0);
            }
            else if ((i->getRotation() == 0 || i->getRotation() == 180) && (i->getType() == LaneType::asphaltLeft))
            {
                i->setGroup(1);
            }
            else if ((i->getRotation() == 90 || i->getRotation() == 270) && (i->getType() == LaneType::asphalt || i->getType() == LaneType::tram|| i->getType() == LaneType::asphaltRight))
            {
                i->setGroup(2);
            }
            else if ((i->getRotation() == 90 || i->getRotation() == 270) && (i->getType() == LaneType::asphaltLeft ))
            {
                i->setGroup(3);
            }
        }
    }
}
int Intersection::changeLightToRed(LightChangingType lightChangingType)
{
    float sums[4]{0, 0, 0, 0};
    int times[4]{0, 0, 0, 0};
    for (auto i : lanes)
    {
        sums[i->getGroup()] += i->getCarsNearEnd();
        if (i->getType() != LaneType::tram)
            times[i->getGroup()]++;
    }
    for (int i = 0; i < 4; i++)
    {
        if (times[i] != 0 && times[i] > 1)
            sums[i] /= times[i];
    }
    //std::cout << "!!!" << sums[0] << " " << sums[1] << " " << sums[2] << " " << sums[3] << "\n";
    for (auto i : lanes)
    {
        if (i->getGroup() != std::distance(sums, std::max_element(sums, sums + 4)))
        {
            i->changeLight(true);
        }
    }
    return std::distance(sums, std::max_element(sums, sums + 4));
}

void Intersection::changeLightToGreen(int group)
{
    for (auto i : lanes)
    {
        if (i->getGroup() == group)
        {
            i->changeLight(false);
        }
    }
}
int Intersection::getCarsNear() const{
    int sum=0;
    for(auto i:lanes){
        sum+=i->getCarsNearEnd();
    }
}
int Intersection::getLeftLanes() const{
    return this->leftLanes;
}
int Intersection::getUpLanes() const{
    return this->upLanes;
}
