#pragma once
#include "lanes.hpp"
#include <algorithm>

enum class LightChangingType
{
    smart
};

class Intersection
{
private:
    sf::RectangleShape center, backgorund;
    sf::Texture centerTexture, backgroundTexture;
    float centerWidth, centerHeight;
    std::vector<Lane *> lanes, lanes2;
    float laneWidth = 0;
    int leftLanes, upLanes;

public:
    ~Intersection()
    {
        for (auto i : lanes)
            delete (i);
        for (auto i : lanes2)
            delete (i);
        std::cout << "Intersection deleted\n";
    }
    Intersection()
    {
        //texture
        this->centerTexture.loadFromFile("content/intersectionCenter.png");
        this->centerTexture.setSmooth(true);

        this->backgroundTexture.loadFromFile("content/background.png");
        this->backgroundTexture.setSmooth(true);

        //dismensions
        this->center = sf::RectangleShape(sf::Vector2f(centerWidth, centerHeight));
        this->center.setPosition(sf::Vector2f(-centerWidth / 2, -centerHeight / 2));
        this->center.setTexture(&this->centerTexture);

        this->backgorund = sf::RectangleShape(sf::Vector2f(800, 800));
        this->backgorund.setPosition(sf::Vector2f(-400, -400));
        this->backgorund.setTexture(&this->backgroundTexture);

        //cout
        std::cout << "Intersection created\n";
    }
    Intersection(std::vector<std::vector<LaneType>> lanes) //left right up down
    {
        //texture
        this->centerTexture.loadFromFile("content/intersectionCenter.png");
        this->centerTexture.setSmooth(true);

        this->backgroundTexture.loadFromFile("content/background.png");
        this->backgroundTexture.setSmooth(true);

        //dismensions
        this->backgorund = sf::RectangleShape(sf::Vector2f(800, 800));
        this->backgorund.setPosition(sf::Vector2f(-400, -400));
        this->backgorund.setTexture(&this->backgroundTexture);

        this->centerWidth = 35 * (lanes[2].size() + lanes[3].size());
        this->centerHeight = 35 * (lanes[0].size() + lanes[1].size());
        this->center = sf::RectangleShape(sf::Vector2f(centerWidth, centerHeight));
        this->center.setPosition(sf::Vector2f(-centerWidth / 2, -centerHeight / 2));
        this->center.setTexture(&this->centerTexture);
        this->laneWidth = this->centerWidth / (lanes[2].size() + lanes[3].size()) * .863f;

        this->leftLanes = lanes[0].size();
        if (lanes[0][0] == LaneType::tram)
            leftLanes++;
        this->upLanes = lanes[2].size();
        if (lanes[2][0] == LaneType::tram)
            upLanes++;

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
                {
                    this->lanes2.push_back(new Lane(laneX, laneY + laneWidth, laneWidth, -angle, LaneType::tramNoBackground));
                    this->lanes2.push_back(new Lane(-laneX, laneY + laneWidth, laneWidth, -angle, LaneType::tram));
                }
                else if (i == 1)
                {
                    this->lanes2.push_back(new Lane(laneX, laneY - laneWidth, laneWidth, -angle, LaneType::tramNoBackground));
                    this->lanes2.push_back(new Lane(-laneX, laneY - laneWidth, laneWidth, -angle, LaneType::tram));
                }
                else if (i == 2)
                {
                    this->lanes2.push_back(new Lane(laneX - laneWidth, laneY, laneWidth, 0, LaneType::tramNoBackground));
                    this->lanes2.push_back(new Lane(laneX - laneWidth, -laneY, laneWidth, 0, LaneType::tram));
                }
                else if (i == 3)
                {
                    this->lanes2.push_back(new Lane(laneX + laneWidth, laneY, laneWidth, 180, LaneType::tramNoBackground));
                    this->lanes2.push_back(new Lane(laneX + laneWidth, -laneY, laneWidth, 180, LaneType::tram));
                }
            }
            laneX = firstAsphaltLaneX;
            laneY = firstAsphaltLaneY;
            this->lanes2.push_back(new Lane(laneX, laneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
            for (int j = start; j <= lanes[i].size(); j++)
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
                if (j < lanes[i].size())
                {
                    this->lanes.push_back(new Lane(laneX, laneY, this->laneWidth, angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::inAsphalt));
                    else
                    {
                        this->lanes2.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::outAsphalt));
                    }
                    if (i == 0)
                    {
                        this->lanes2.push_back(new Lane(-firstAsphaltLaneX, firstAsphaltLaneY + smallLaneWidth, this->laneWidth * .16f, -angle, LaneType::outAsphalt));
                        this->lanes2.push_back(new Lane(-laneX, laneY + this->laneWidth, this->laneWidth, -angle, lanes[i][j]));
                        if (j < lanes[i].size() - 1)
                            this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY) + smallLaneWidth, smallLaneWidth, -angle, LaneType::inAsphalt));
                        else
                        {
                            this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY) + smallLaneWidth, smallLaneWidth, -angle, LaneType::outAsphalt));
                        }
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
                else
                {
                    this->lanes2.push_back(new Lane(laneX, laneY, this->laneWidth, angle, LaneType::pedestrian));
                    if (i == 0)
                    {
                        this->lanes2.push_back(new Lane(-laneX, laneY + this->laneWidth, this->laneWidth, -angle, LaneType::pedestrian));
                    }
                    else if (i == 1)
                    {
                        this->lanes2.push_back(new Lane(-laneX, laneY - this->laneWidth, this->laneWidth, -angle, LaneType::pedestrian));
                    }
                    else if (i == 2)
                    {
                        this->lanes2.push_back(new Lane(-laneX + this->laneWidth, laneY, this->laneWidth, -angle, LaneType::pedestrian));
                    }
                    else if (i == 3)
                    {
                        this->lanes2.push_back(new Lane(-laneX - this->laneWidth, laneY, this->laneWidth, -angle, LaneType::pedestrian));
                    }
                }
            }
        }
        for (auto i : lanes2)
        {
            if (i->getType() == LaneType::asphaltLeft || i->getType() == LaneType::asphaltRight)
            {
                i->changeLaneType(LaneType::asphalt);
            }
        }
        //cout
        std::cout << "Intersection created. Center size: " << this->centerWidth << "x" << this->centerHeight << "\n";
    }

    void draw(sf::RenderWindow &window);
    void addVehicles(int amount);
    void addVehicles(int amount, Direction direction);
    void go();
    int getGreenLightGroup() const;
    void setGroups(LightChangingType lightChangingType);
    int changeLightToRed(LightChangingType lightChangingType);
    void changeLightToGreen(int group);
    int getCarsPassed() const;
};