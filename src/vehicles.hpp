#pragma once
#include <math.h>

enum class Direction
{
    left,
    right,
    up,
    down
};
enum class CarCategory
{
    car,
    longCar,
    tram
};
//TODO delete objects when out of view, turning in sine function
class Car
{
private:
    sf::RectangleShape car;
    float height = 40.0f;
    float width = 30.0f;
    float speed = 1.f;
    float margin = 10;
    sf::Texture carTexture;

public:
    Car(float width, float positionX, float positionY, CarCategory type, float speedMulitplier)
    {
        std::string out;
        int textureNumber;
        //texture
        std::string directory = "content/";
        if (type == CarCategory::car)
        {
            textureNumber = rand() % 4;
            this->carTexture.loadFromFile(directory + "car" + std::to_string(textureNumber) + ".png");
            out = "Car";
        }
        else if (type == CarCategory::longCar)
        {
            textureNumber = rand() % 1;
            this->carTexture.loadFromFile(directory + "longCar" + std::to_string(textureNumber) + ".png");
            out = "Long car";
        }
        else if (type == CarCategory::tram)
        {
            textureNumber = rand() % 2;
            this->carTexture.loadFromFile(directory + "tramCar" + std::to_string(textureNumber) + ".png");
            out = "Tram";
        }
        this->carTexture.setSmooth(true);
        //dismensions
        this->width = width;
        float ratio = float(this->carTexture.getSize().y) / float(this->carTexture.getSize().x);
        this->height = this->width * ratio;
        car = sf::RectangleShape(sf::Vector2f(width, height));
        this->car.setTexture(&this->carTexture);

        //position
        car.setPosition(sf::Vector2f(positionX, positionY));

        //speed
        this->speed *= speedMulitplier;

        //cout
        std::cout << out << " created at: " << positionX << " x " << positionY << " Speed multiplier: " << speedMulitplier << " Texture number: " << textureNumber << std::endl;
    }
    ~Car()
    {
        std::cout << "Car deleted\n";
    }
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, Car &previousCar, sf::Vector2f lightPosition, bool light, float laneWidth);
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, sf::Vector2f lightPosition, bool light, float laneWidth);
    void goUp(Car &previousCar);
    void goUp(sf::Vector2f lightPosition, bool light);
    void goUp(Car &previousCar, sf::Vector2f lightPosition, bool light);
    bool goUp(bool changeRotation, sf::Vector2f lightPosition, bool light);
    bool goUp(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light);
    void goUp(bool changeRotation);
    void goUp();
    void goDown(Car &previousCar);
    void goDown(sf::Vector2f lightPosition, bool light);
    void goDown(Car &previousCar, sf::Vector2f lightPosition, bool light);
    bool goDown(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light);
    bool goDown(bool changeRotation, sf::Vector2f lightPosition, bool light);
    void goDown(bool changeRotation);
    void goDown();
    void goLeft(Car &previousCar);
    void goLeft(sf::Vector2f lightPosition, bool light);
    void goLeft(Car &previousCar, sf::Vector2f lightPosition, bool light);
    bool goLeft(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light);
    bool goLeft(bool changeRotation, sf::Vector2f lightPosition, bool light);
    void goLeft(bool changeRotation);
    void goLeft();
    void goRight(Car &previousCar);
    void goRight(sf::Vector2f lightPosition, bool light);
    void goRight(Car &previousCar, sf::Vector2f lightPosition, bool light);
    bool goRight(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light);
    bool goRight(bool changeRotation, sf::Vector2f lightPosition, bool light);
    void goRight(bool changeRotation);
    void goRight();
    void draw(sf::RenderWindow &window);
    float getRotation() const;
    sf::Vector2f getPosition() const;
    void setRotation(float &rotation);
    void setSpeed(float &speed);
    float getSpeed() const;
};