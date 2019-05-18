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
    std::vector<Lane *> lanes2;
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
                laneX = (this->centerSize / 2);
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
                laneY = -(this->centerSize / 2);
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
                laneY = (this->centerSize / 2);
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
                this->lanes.push_back(new Lane(laneX, laneY, laneWidth, angle, LaneType::tram));
            laneX=firstAsphaltLaneX;
            laneY=firstAsphaltLaneY;
            this->lanes.push_back(new Lane(laneX, laneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
            for (int j = start; j < lanes[i].size(); j++)
            {
                float smallLaneMarginX = .0f, smallLaneMarginY = .0f;
                if (i == 3)
                {
                    laneX = j*(laneWidth + smallLaneWidth);
                    smallLaneMarginX = this->laneWidth;
                }
                else if (i == 2)
                {
                    laneX = -j*(laneWidth + smallLaneWidth);
                    smallLaneMarginX = -this->laneWidth;
                }
                else if (i == 0)
                {
                    laneY = j*(laneWidth + smallLaneWidth);
                    smallLaneMarginY = this->laneWidth;
                }
                else if (i == 1)
                {
                    laneY = -j*(laneWidth + smallLaneWidth);
                    smallLaneMarginY = -this->laneWidth;
                }
                this->lanes.push_back(new Lane(laneX, laneY, this->laneWidth, angle, lanes[i][j]));
                if (j < lanes[i].size() - 1)
                    this->lanes.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::inAsphalt));
                else
                    this->lanes.push_back(new Lane(laneX + smallLaneMarginX, laneY + smallLaneMarginY, smallLaneWidth, angle, LaneType::outAsphalt));
                if (i == 0)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX, firstAsphaltLaneY+smallLaneWidth, this->laneWidth * .16f, -angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX, laneY+this->laneWidth, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY)+smallLaneWidth, smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY)+smallLaneWidth, smallLaneWidth, -angle, LaneType::outAsphalt));
                }
                else if (i == 1)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX, firstAsphaltLaneY-smallLaneWidth, this->laneWidth * .16f, -angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX, laneY-this->laneWidth, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY)-smallLaneWidth, smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX), (laneY + smallLaneMarginY)-smallLaneWidth, smallLaneWidth, -angle, LaneType::outAsphalt));
                }
                else if (i == 2)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX+smallLaneWidth, firstAsphaltLaneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX + this->laneWidth, laneY, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) + smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) + smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::outAsphalt));
                }
                else if (i == 3)
                {
                    this->lanes2.push_back(new Lane(-firstAsphaltLaneX-smallLaneWidth, firstAsphaltLaneY, this->laneWidth * .16f, angle, LaneType::outAsphalt));
                    this->lanes2.push_back(new Lane(-laneX - this->laneWidth, laneY, this->laneWidth, -angle, lanes[i][j]));
                    if (j < lanes[i].size() - 1)
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) - smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::inAsphalt));
                    else
                        this->lanes2.push_back(new Lane(-(laneX + smallLaneMarginX) - smallLaneWidth, (laneY + smallLaneMarginY), smallLaneWidth, -angle, LaneType::outAsphalt));
                }
            }
        }

        //cout
        std::cout << "Intersection created. Center size: " << this->centerSize << " Max Lanes: " << max << "\n";
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(this->center);
        if (!lanes2.empty())
            for (auto it : lanes2)
                it->draw(window);
        if (!lanes.empty())
            for (auto it : lanes)
                it->draw(window);
    }
};