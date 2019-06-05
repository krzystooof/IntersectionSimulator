#pragma once
#include "vehicles.hpp"
enum class LaneType
{
    inAsphalt,
    outAsphalt,
    asphalt,
    asphaltLeft,
    asphaltRight,
    tram,
    tramNoBackground,
    pedestrian,
    pedestrianNoBackground
};

class Lane
{
private:
    sf::RectangleShape lane, lightShape;
    float height = 400.0f;
    float width;
    bool light;
    sf::Texture laneTexture, lightGreenTexture, lightRedTexture;
    std::vector<Car *> cars;
    LaneType type;
    int carsNearEnd,group;

public:
    Lane(float positionX, float positionY, float width, float rotation, LaneType type)
    {
        //texture
        this->type = type;
        if (type == LaneType::inAsphalt)
            this->laneTexture.loadFromFile("content/laneIn.png");
        else if (type == LaneType::outAsphalt)
            this->laneTexture.loadFromFile("content/laneOut.png");
        else if (type == LaneType::asphalt)
            this->laneTexture.loadFromFile("content/laneAsphalt.png");
        else if (type == LaneType::asphaltLeft)
            this->laneTexture.loadFromFile("content/laneAsphaltLeftTurn.png");
        else if (type == LaneType::asphaltRight)
            this->laneTexture.loadFromFile("content/laneAsphaltRightTurn.png");
        else if (type == LaneType::tram)
            this->laneTexture.loadFromFile("content/laneTram.png");
        else if (type == LaneType::tramNoBackground)
            this->laneTexture.loadFromFile("content/laneTramNobackground.png");
        else if (type == LaneType::pedestrian)
            this->laneTexture.loadFromFile("content/lanePevement.png");
        else if (type == LaneType::pedestrianNoBackground)
            this->laneTexture.loadFromFile("content/lanePavementNoBackground.png");
        this->lightGreenTexture.loadFromFile("content/greenLight.png");
        this->lightRedTexture.loadFromFile("content/redLight.png");
        this->lightRedTexture.setSmooth(true);
        this->lightGreenTexture.setSmooth(true);
        this->laneTexture.setSmooth(true);

        //dismensions
        this->width = width;
        float ratio = float(this->laneTexture.getSize().y) / float(this->laneTexture.getSize().x);
        this->height = this->width * ratio;
        this->lane = sf::RectangleShape(sf::Vector2f(width, height));
        this->lane.setRotation(rotation);
        this->lane.setTexture(&this->laneTexture);
        this->lane.setPosition(sf::Vector2f(positionX, positionY));
        light = false;

        //cout
        std::cout << "Lane created at: " << positionX << " x " << positionY << std::endl;
    }

    ~Lane()
    {
        std::cout << "Lane deleted\n";
    }
    void addVehicle(CarCategory category);
    void addVehicle(CarCategory category, int amount);
    void go(Direction direction);
    void go(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition);
    void draw(sf::RenderWindow &window);
    float getRotation() const;
    sf::Vector2f getPosition() const;
    LaneType getType() const;
    void changeLight(bool green);
    bool getLight() const;
    sf::Vector2f getPosition();
    void showLight();
    void changeLaneType(LaneType type);
    void setGroup(int group);
    int getGroup() const;
    int getCarsNearEnd() const;
};
