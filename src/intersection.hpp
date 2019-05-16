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
    float centerSize;
    std::vector<Lane *> lanes;
    std::vector<Lane *> middle;
    float laneWidth = 0;

public:
    Intersection()
    {
        //texture
        this->centerTexture.loadFromFile("graphics/intersectionCenter.png");
        this->centerTexture.setSmooth(true);

        //dismensions
        this->center = sf::RectangleShape(sf::Vector2f(centerSize, centerSize));
        this->center.setPosition(sf::Vector2f(-centerSize / 2, -centerSize / 2));
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
        float max = 0;
        for (auto i : lanes)
            if (i.size() > max)
                max = i.size();
        this->centerSize = 50 * max;
        if (this->centerSize < 100)
            this->centerSize = 100;
        this->center = sf::RectangleShape(sf::Vector2f(centerSize, centerSize));
        this->center.setPosition(sf::Vector2f(-centerSize / 2, -centerSize / 2));
        this->center.setTexture(&this->centerTexture);
        this->laneWidth = this->centerSize / 2 / (max + (max * 0.16f));

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
                laneX = -(this->centerSize / 2);
                laneY = .0f;
                angle = 90.f;
                firstAsphaltLaneX = laneX;
                if (lanes[0][0] == LaneType::tram)
                {
                    firstAsphaltLaneY = laneWidth;
                    this->lanes.push_back(new Lane(laneX, laneY, laneWidth, angle, LaneType::tram));
                    start = 1;
                }
                else
                    firstAsphaltLaneY = 0;
            }
            if (i == 1)
            {
                laneX = (this->centerSize / 2);
                laneY = .0f;
                angle = -90.f;
                firstAsphaltLaneX = laneX;
                if (lanes[0][0] == LaneType::tram)
                {
                    firstAsphaltLaneY = -laneWidth;
                    this->lanes.push_back(new Lane(laneX, laneY, laneWidth, angle, LaneType::tram));
                    start = 1;
                }
                else
                    firstAsphaltLaneY = 0;
            }
            if (i == 2)
            {
                laneY = -(this->centerSize / 2);
                laneX = .0f;
                angle = 180.f;
                firstAsphaltLaneY = laneY;
                if (lanes[0][0] == LaneType::tram)
                {
                    firstAsphaltLaneX = -laneWidth;
                    this->lanes.push_back(new Lane(laneX, laneY, laneWidth, angle, LaneType::tram));
                    start = 1;
                }
                else
                    firstAsphaltLaneX = 0;
            }
            if (i == 3)
            {
                laneY = (this->centerSize / 2);
                laneX = .0f;
                angle = 0.f;
                firstAsphaltLaneY = laneY;
                if (lanes[0][0] == LaneType::tram)
                {
                    firstAsphaltLaneX = laneWidth;
                    this->lanes.push_back(new Lane(laneX, laneY, laneWidth, angle, LaneType::tram));
                    start = 1;
                }
                else
                    firstAsphaltLaneX = 0;
            }
            this->lanes.push_back(new Lane(firstAsphaltLaneX, firstAsphaltLaneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
            for (int j = start; j < lanes[i].size(); j++)
            {
                float smallLaneMarginX = .0f, smallLaneMarginY = .0f;
                if (i == 3)
                {
                    laneX += laneWidth + smallLaneWidth;
                    smallLaneMarginX = this->laneWidth;
                }
                else if (i == 2)
                {
                    laneX -= laneWidth + smallLaneWidth;
                    smallLaneMarginX = -this->laneWidth;
                }
                else if (i == 0)
                {
                    laneY += laneWidth + smallLaneWidth;
                    smallLaneMarginY = this->laneWidth;
                }
                else if (i == 1)
                {
                    laneY -= laneWidth + smallLaneWidth;
                    smallLaneMarginY = -this->laneWidth;
                }
                this->lanes.push_back(new Lane(laneX, laneY, this->laneWidth, angle, lanes[i][j]));
                if (j < lanes[i].size() - 1)
                    this->lanes.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::inAsphalt));
                else
                    this->lanes.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::outAsphalt));


            }
        }

        //cout
        std::cout << "Intersection created. Center size: " << this->centerSize << " Max Lanes: " << max << "\n";
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(this->center);
        if (!middle.empty())
            for (auto it : middle)
                it->draw(window);
        if (!lanes.empty())
            for (auto it : lanes)
                it->draw(window);
    }
};