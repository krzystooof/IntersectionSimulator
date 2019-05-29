#pragma once
#include "lanes.hpp"
#include "vehicles.hpp"
#include <algorithm>

//TODO add mirror lanes, vehicle runing
class Intersection
{
private:
    sf::RectangleShape center;
    sf::Texture centerTexture;
    float centerWidth, centerHeight;
    std::vector<Lane *> lanes;
    std::vector<Lane *> lanes2;
    float laneWidth = 0;

public:
    ~Intersection(){
        for(auto i:lanes) delete(i);
        for(auto i:lanes2) delete(i);
        std::cout<<"Intersection deleted\n";
    }
    Intersection()
    {
        //texture
        this->centerTexture.loadFromFile("graphics/intersectionCenter.png");
        this->centerTexture.setSmooth(true);

        //dismensions
        this->center = sf::RectangleShape(sf::Vector2f(centerWidth, centerHeight));
        this->center.setPosition(sf::Vector2f(-centerWidth / 2, -centerHeight / 2));
        this->center.setTexture(&this->centerTexture);

        //cout
        std::cout << "Intersection created\n";
    }
    Intersection(std::vector<std::vector<LaneType>> lanes) //left right up down
    {
        //texture
        this->centerTexture.loadFromFile("graphics/intersectionCenter.png");
        this->centerTexture.setSmooth(true);

        //dismensions
        this->centerWidth = 50 * (lanes[2].size() + lanes[3].size());
        this->centerHeight = 50 * (lanes[0].size() + lanes[1].size());
        this->center = sf::RectangleShape(sf::Vector2f(centerWidth, centerHeight));
        this->center.setPosition(sf::Vector2f(-centerWidth / 2, -centerHeight / 2));
        this->center.setTexture(&this->centerTexture);
        this->laneWidth = this->centerWidth / (lanes[2].size() + lanes[3].size()) * .863f;

        for (int i = 0; i < lanes.size(); i++)
        {
            float smallLaneWidth = this->laneWidth * 0.16f;
            float start = 0;
            float laneY;
            float laneX;
            float angle;
            float firstAsphaltLaneY = .0f;
            float firstAsphaltLaneX = .0f;
            if (i == 0)
            {
                laneX = -(this->centerWidth / 2);
                laneY = .0f;
                angle = 90.f;
                firstAsphaltLaneX = laneX;
                if (lanes[i][0] == LaneType::tram)
                {
                    firstAsphaltLaneY = laneWidth;
                    start = 1;
                }
                else
                    firstAsphaltLaneY = 0;
            }
            if (i == 1)
            {
                laneX = (this->centerWidth / 2);
                laneY = .0f;
                angle = -90.f;
                firstAsphaltLaneX = laneX;
                if (lanes[i][0] == LaneType::tram)
                {
                    firstAsphaltLaneY = -laneWidth;
                    start = 1;
                }
                else
                    firstAsphaltLaneY = 0;
            }
            if (i == 2)
            {
                laneY = -(this->centerHeight / 2);
                laneX = .0f;
                angle = 180.f;
                firstAsphaltLaneY = laneY;
                if (lanes[i][0] == LaneType::tram)
                {
                    firstAsphaltLaneX = -laneWidth;
                    start = 1;
                }
                else
                    firstAsphaltLaneX = 0;
            }
            if (i == 3)
            {
                laneY = (this->centerHeight / 2);
                laneX = .0f;
                angle = 0.f;
                firstAsphaltLaneY = laneY;
                if (lanes[i][0] == LaneType::tram)
                {
                    firstAsphaltLaneX = laneWidth;
                    start = 1;
                }
                else
                    firstAsphaltLaneX = 0;
            }
            if (lanes[i][0] == LaneType::tram)
            {
                this->lanes.push_back(new Lane(laneX, laneY, laneWidth, angle, LaneType::tram));
                if (i == 0)
                    this->lanes2.push_back(new Lane(-laneX, laneY + laneWidth, laneWidth, -angle, LaneType::tram));
                else if (i == 1)
                    this->lanes2.push_back(new Lane(-laneX, laneY - laneWidth, laneWidth, -angle, LaneType::tram));
                else if (i == 2)
                    this->lanes2.push_back(new Lane(laneX - laneWidth, -laneY, laneWidth, 0, LaneType::tram));
                else if (i == 3)
                    this->lanes2.push_back(new Lane(laneX + laneWidth, -laneY, laneWidth, 180, LaneType::tram));
            }
            laneX = firstAsphaltLaneX;
            laneY = firstAsphaltLaneY;
            this->lanes.push_back(new Lane(laneX, laneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
            for (int j = start; j < lanes[i].size(); j++)
            {
                float smallLaneMarginX = .0f, smallLaneMarginY = .0f;
                if (i == 3)
                {
                    laneX = j * (laneWidth + smallLaneWidth);
                    smallLaneMarginX = this->laneWidth;
                }
                else if (i == 2)
                {
                    laneX = -j * (laneWidth + smallLaneWidth);
                    smallLaneMarginX = -this->laneWidth;
                }
                else if (i == 0)
                {
                    laneY = j * (laneWidth + smallLaneWidth);
                    smallLaneMarginY = this->laneWidth;
                }
                else if (i == 1)
                {
                    laneY = -j * (laneWidth + smallLaneWidth);
                    smallLaneMarginY = -this->laneWidth;
                }
                this->lanes.push_back(new Lane(laneX, laneY, this->laneWidth, angle, lanes[i][j]));
                if (j < lanes[i].size() - 1)
                    this->lanes2.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::inAsphalt));
                else
                    this->lanes2.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::outAsphalt));

                if (i == 0)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX, firstAsphaltLaneY + smallLaneWidth, this->laneWidth * .16f, -angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX, laneY + this->laneWidth, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY) + smallLaneWidth, smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY) + smallLaneWidth, smallLaneWidth, -angle, LaneType::outAsphalt));
                }
                else if (i == 1)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX, firstAsphaltLaneY - smallLaneWidth, this->laneWidth * .16f, -angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX, laneY - this->laneWidth, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY) - smallLaneWidth, smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY) - smallLaneWidth, smallLaneWidth, -angle, LaneType::outAsphalt));
                }
                else if (i == 2)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX + smallLaneWidth, firstAsphaltLaneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX + this->laneWidth, laneY, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) + smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) + smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::outAsphalt));
                }
                else if (i == 3)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX - smallLaneWidth, firstAsphaltLaneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX - this->laneWidth, laneY, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) - smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) - smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::outAsphalt));
                }
            }
        }

        //cout
        std::cout << "Intersection created. Center size: " << this->centerWidth << "x" << this->centerHeight << "\n";
    }

    void draw(sf::RenderWindow &window)
    {
        for(auto i:lanes){
            if(i->getType()==LaneType::asphalt||i->getType()==LaneType::asphaltLeft||i->getType()==LaneType::asphaltRight||i->getType()==LaneType::tram){
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
    void addVehicles(int amount)
    {
        for (auto i : this->lanes)
            if (i->getType() == LaneType::asphalt || i->getType() == LaneType::asphaltRight || i->getType() == LaneType::asphaltLeft )
                i->addVehicle(CarCategory::car, amount);
            else if (i->getType() == LaneType::tram) i->addVehicle(CarCategory::tram, amount);
    }
    void go()
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
    void changeLight(){
        for (auto i:lanes)
            i->changeLight();
    }
};