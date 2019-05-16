#pragma once
#include "lanes.hpp"
#include "vehicles.hpp"
class Intersection
{
private:
    sf::RectangleShape center;
    sf::Texture centerTexture;
    float centerSize = 100;
    std::vector<Lane *> left;
    std::vector<Lane *> right;
    std::vector<Lane *> up;
    std::vector<Lane *> down;

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
    void addLaneLeft(bool tramLaneExists, int numberOfLanes, bool leftTurnLaneExists, bool rightTurnLaneExists)
    {
        //TODO add right and left turn lane
        float laneWidth;
        float firstAsphaltLanePosition;
        if (tramLaneExists)
        {
            laneWidth = this->centerSize / 2 / (numberOfLanes + 1);
            left.push_back(new Lane(-this->center.getPosition().x / 2, -this->center.getPosition().y / 2, laneWidth * 0.8f, 90, LaneType::tram));
            right.push_back(new Lane(this->center.getPosition().x / 2, this->center.getPosition().y / 2, laneWidth * 0.8f, -90, LaneType::tram));
            firstAsphaltLanePosition = (this->center.getPosition().x / 2) + laneWidth * 0.8;
        }
        else
        {
            firstAsphaltLanePosition = this->center.getPosition().x / 2;
            laneWidth = this->centerSize / 2 / numberOfLanes;
        }
        left.push_back(new Lane(-firstAsphaltLanePosition, -firstAsphaltLanePosition, laneWidth * 0.16f, 90, LaneType::outAsphalt));
        left.push_back(new Lane(firstAsphaltLanePosition, firstAsphaltLanePosition, laneWidth * 0.16f, -90, LaneType::outAsphalt));
        for (int i = 0; i < numberOfLanes; i++)
        {
            left.push_back(new Lane(-(firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i))), -(firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i))), laneWidth, 90, LaneType::asphalt));
            right.push_back(new Lane(firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i)), firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i)), laneWidth, -90, LaneType::asphalt));
            left.push_back(new Lane(-(firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i))), -(firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i))), laneWidth*.16f, 90, LaneType::inAsphalt));
            right.push_back(new Lane(firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i)), firstAsphaltLanePosition + (laneWidth * 0.16f * (i + 1) + (laneWidth * i)), laneWidth*.16f, -90, LaneType::inAsphalt));
        }
        left.push_back(new Lane(-(firstAsphaltLanePosition + (laneWidth * 0.16f * (numberOfLanes + 1) + (laneWidth * numberOfLanes))), -(firstAsphaltLanePosition + (laneWidth * 0.16f * (numberOfLanes + 1) + (laneWidth * numberOfLanes))), laneWidth, 90, LaneType::asphalt));
        right.push_back(new Lane(firstAsphaltLanePosition + (laneWidth * 0.16f * (numberOfLanes + 1) + (laneWidth * numberOfLanes)), firstAsphaltLanePosition + (laneWidth * 0.16f * (numberOfLanes + 1) + (laneWidth * numberOfLanes)), laneWidth, -90, LaneType::asphalt));
    }
};