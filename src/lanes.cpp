#include "lanes.hpp"
void Lane::addVehicle(CarCategory category)
{
    float x, y, speedMultiplier;
    if (this->lane.getRotation() == 0)
    {
        x = this->lane.getPosition().x;
        y = 399;
    }
    else if (this->lane.getRotation() == 180)
    {
        x = this->lane.getPosition().x;
        y = -399;
    }
    else if (this->lane.getRotation() == 90)
    {
        y = this->lane.getPosition().y;
        x = -399;
    }
    else if (this->lane.getRotation() == 270)
    {
        y = this->lane.getPosition().y;
        x = 399;
    }

    if (category == CarCategory::car)
        speedMultiplier = ((rand() % 21) + 100) / 100.0;
    else if (category == CarCategory::longCar)
        speedMultiplier = ((rand() % 21) + 79) / 100.0;
    else if (category == CarCategory::tram)
        speedMultiplier = ((rand() % 21) + 60) / 100.0;
    else if (category == CarCategory::pedestrian)
        speedMultiplier = ((rand() % 21) + 20) / 100.0;

    cars.push_back(new Car(this->width, x, y, category, speedMultiplier));
}
void Lane::addVehicle(CarCategory category, int amount)
{
    for (int i = 0; i < amount; i++)
        this->addVehicle(category);
}
void Lane::go(Direction direction)
{
    if (cars.empty())
        ;
    else
    {
        switch (direction)
        {
        case Direction::up:
            cars[0]->goUp(this->lane.getPosition(), this->light);
            for (int i = 1; i < cars.size(); i++)
            {
                cars[i]->goUp(*cars[i - 1], this->lane.getPosition(), this->light);
            }
            break;
        case Direction::down:
            cars[0]->goDown(this->lane.getPosition(), this->light);
            for (int i = 1; i < cars.size(); i++)
            {
                cars[i]->goDown(*cars[i - 1], this->lane.getPosition(), this->light);
            }
            break;
        case Direction::left:
            cars[0]->goLeft(this->lane.getPosition(), this->light);
            for (int i = 1; i < cars.size(); i++)
            {
                cars[i]->goLeft(*cars[i - 1], this->lane.getPosition(), this->light);
            }
            break;
        case Direction::right:
            cars[0]->goRight(this->lane.getPosition(), this->light);
            for (int i = 1; i < cars.size(); i++)
            {
                cars[i]->goRight(*cars[i - 1], this->lane.getPosition(), this->light);
            }
            break;
        }
    }
}
void Lane::go(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition)
{
    if (cars.empty())
        ;
    else
    {
        cars[0]->turn(firstDirection, secondDirection, turningPosition, this->lane.getPosition(), this->light, width);
        for (int i = 1; i < cars.size(); i++)
        {
            cars[i]->turn(firstDirection, secondDirection, turningPosition, *cars[i - 1], this->lane.getPosition(), this->light, width);
        }
    }
}
void Lane::draw(sf::RenderWindow &window)
{
    if (!light)
        this->lightShape.setTexture(&this->lightGreenTexture);
    else
        this->lightShape.setTexture(&this->lightRedTexture);
    window.draw(this->lane);
    if (!cars.empty())
    {
        for (auto it = cars.begin(); it != cars.end();)
        {
            if (std::abs((*it)->getPosition().x) > 600 || std::abs((*it)->getPosition().y) > 600)
            {
                delete *it;
                it = cars.erase(it);
            }
            else
            {
                (*it)->draw(window);
                it++;
            }
        }
    }
    window.draw(this->lightShape);
}
float Lane::getRotation() const
{
    return this->lane.getRotation();
}
sf::Vector2f Lane::getPosition() const
{
    return this->lane.getPosition();
}
LaneType Lane::getType() const
{
    return this->type;
}
void Lane::changeLight()
{
    light = !light;
}
bool Lane::getLight() const
{
    return light;
}
sf::Vector2f Lane::getPosition()
{
    return this->lane.getPosition();
}
void Lane::showLight()
{
    this->lightShape = sf::RectangleShape(sf::Vector2f(this->width/1.5 , this->width/1.5));
    this->lightShape.setPosition(this->lane.getPosition().x, this->lane.getPosition().y);
    this->lightShape.setRotation(this->lane.getRotation());
}
void Lane::changeLaneType(LaneType type)
{
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
}