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
    Car()
    {
        //texture
        this->carTexture.loadFromFile("graphics/car1.png");
        this->carTexture.setSmooth(true);

        //dismensions
        float ratio = float(this->carTexture.getSize().y) / float(this->carTexture.getSize().x);
        this->height = this->width * ratio;
        car = sf::RectangleShape(sf::Vector2f(width, height));
        this->car.setTexture(&this->carTexture);

        //cout
        std::cout << "Car created at default position\n";
    }
    Car(float width, float positionX, float positionY, CarCategory type, float speedMulitplier)
    {
        std::string out;
        int textureNumber;
        //texture
        std::string directory = "graphics/";
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
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, Car &previousCar, sf::Vector2f lightPosition, bool light, float laneWidth)
    {
        if (this->speed > 1.5f)
            this->speed = 1.3f;
        bool second = false;
        bool middle = false;
        switch (firstDirection)
        {
        case Direction::left:
            if (this->car.getPosition().x < turningPosition.x + laneWidth)
                middle = true;
            if (this->car.getPosition().x < turningPosition.x)
                second = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x - laneWidth)
                middle = true;
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y + laneWidth)
                middle = true;
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y - laneWidth)
                middle = true;
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            break;
        }
        if (second)
        {
            this->speed *= 1.05f;
            switch (secondDirection)
            {
            case Direction::left:
                goLeft(previousCar);
                break;
            case Direction::right:
                goRight(previousCar);
                break;
            case Direction::up:
                goUp(previousCar);
                break;
            case Direction::down:
                goDown(previousCar);
                break;
            }
        }
        else if (middle)
        {
            float slowingSpeed = 1.015f;
            bool going = false;
            switch (secondDirection)
            {
            case Direction::left:
                if (goLeft(previousCar, false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goLeft(previousCar, false, lightPosition, light);
                    going = true;
                    if (this->getRotation() > 271 || this->getRotation() < 269 || this->getRotation() == 0 || this->getRotation() == 180)
                    {
                        float rotateSpeed = std::sqrt(1 / (turningPosition.y - this->car.getPosition().y)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::down)
                            this->car.rotate(rotateSpeed);
                        else
                            this->car.rotate(-rotateSpeed);
                    }
                }
                break;
            case Direction::right:
                if (goRight(previousCar, false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goRight(previousCar, false, lightPosition, light);
                    going = true;
                    if (this->getRotation() < 89 || this->getRotation() > 91 || this->getRotation() == 0 || this->getRotation() == 180)
                    {
                        float rotateSpeed = std::sqrt(1 / (this->car.getPosition().y - turningPosition.y)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::down)
                            this->car.rotate(-rotateSpeed);
                        else
                            this->car.rotate(rotateSpeed);
                    }
                }
                break;
            case Direction::up:
                if (goUp(previousCar, false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goUp(previousCar, false, lightPosition, light);
                    going = true;
                    if (this->getRotation() > 1 || this->getRotation() < 359 || this->getRotation() == 90 || this->getRotation() == 270)
                    {
                        float rotateSpeed = std::sqrt(1 / (this->car.getPosition().x - turningPosition.x)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::left)
                            this->car.rotate(rotateSpeed);
                        else
                            this->car.rotate(-rotateSpeed);
                    }
                }
                break;
            case Direction::down:
                if (goDown(previousCar, false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goDown(previousCar, false, lightPosition, light);
                    going = true;
                    if (this->getRotation() < 179 || this->getRotation() > 181 || this->getRotation() == 90 || this->getRotation() == 270)
                    {
                        float rotateSpeed = std::sqrt(1 / (turningPosition.x - this->car.getPosition().x)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::left)
                            this->car.rotate(-rotateSpeed);
                        else
                            this->car.rotate(rotateSpeed);
                    }
                }
                break;
            }
            if (going)
            {
                switch (firstDirection)
                {
                case Direction::left:
                    goLeft(false);
                    break;
                case Direction::right:
                    goRight(false);
                    break;
                case Direction::up:
                    goUp(false);
                    break;
                case Direction::down:
                    goDown(false);
                    break;
                }
            }
        }
        else
        {
            switch (firstDirection)
            {
            case Direction::left:
                if (previousCar.getRotation() == 270.0f)
                    goLeft(previousCar, lightPosition, light);
                else
                    goLeft(lightPosition, light);
                break;
            case Direction::right:
                if (previousCar.getRotation() == 90.0f)
                    goRight(previousCar, lightPosition, light);
                else
                    goRight(lightPosition, light);
                break;
            case Direction::up:
                if (previousCar.getRotation() == 0.0f)
                    goUp(previousCar, lightPosition, light);
                else
                    goUp(lightPosition, light);
                break;
            case Direction::down:
                if (previousCar.getRotation() == 180.0f)
                    goDown(previousCar, lightPosition, light);
                else
                    goDown(lightPosition, light);
                break;
            }
        }
    }
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, sf::Vector2f lightPosition, bool light, float laneWidth)
    {
        if (this->speed > 1.5f)
            this->speed = 1.3f;
        bool second = false;
        bool middle = false;
        switch (firstDirection)
        {
        case Direction::left:
            if (this->car.getPosition().x < turningPosition.x + laneWidth)
                middle = true;
            if (this->car.getPosition().x < turningPosition.x)
                second = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x - laneWidth)
                middle = true;
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y + laneWidth)
                middle = true;
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y - laneWidth)
                middle = true;
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            break;
        }
        if (second)
        {
            this->speed *= 1.05f;
            switch (secondDirection)
            {
            case Direction::left:
                goLeft(lightPosition, light);
                break;
            case Direction::right:
                goRight(lightPosition, light);
                break;
            case Direction::up:
                goUp(lightPosition, light);
                break;
            case Direction::down:
                goDown(lightPosition, light);
                break;
            }
        }
        else if (middle)
        {
            float slowingSpeed = 1.02f;
            bool going = false;
            float rotateSpeed = this->speed * 4;
            switch (secondDirection)
            {
            case Direction::left:
                if (goLeft(false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goLeft(false, lightPosition, light);
                    going = true;
                    if (this->getRotation() > 271 || this->getRotation() < 269 || this->getRotation() == 0 || this->getRotation() == 180)
                    {
                        float rotateSpeed = std::sqrt(1 / (turningPosition.y - this->car.getPosition().y)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::down)
                            this->car.rotate(rotateSpeed);
                        else
                            this->car.rotate(-rotateSpeed);
                    }
                }
                break;
            case Direction::right:
                if (goRight(false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goRight(false, lightPosition, light);
                    going = true;
                    if (this->getRotation() < 89 || this->getRotation() > 91 || this->getRotation() == 0 || this->getRotation() == 180)
                    {
                        float rotateSpeed = std::sqrt(1 / (this->car.getPosition().y - turningPosition.y)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::down)
                            this->car.rotate(-rotateSpeed);
                        else
                            this->car.rotate(rotateSpeed);
                    }
                }
                break;
            case Direction::up:
                if (goUp( false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goUp( false, lightPosition, light);
                    going = true;
                    if (this->getRotation() > 1 || this->getRotation() < 359 || this->getRotation() == 90 || this->getRotation() == 270)
                    {
                        float rotateSpeed = std::sqrt(1 / (this->car.getPosition().x - turningPosition.x)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::left)
                            this->car.rotate(rotateSpeed);
                        else
                            this->car.rotate(-rotateSpeed);
                    }
                }
                break;
            case Direction::down:
                if (goDown( false, lightPosition, light))
                {
                    this->speed /= slowingSpeed;
                    goDown( false, lightPosition, light);
                    going = true;
                    if (this->getRotation() < 179 || this->getRotation() > 181 || this->getRotation() == 90 || this->getRotation() == 270)
                    {
                        float rotateSpeed = std::sqrt(1 / (turningPosition.x - this->car.getPosition().x)) * this->speed * 5 + .5f;
                        if (firstDirection == Direction::left)
                            this->car.rotate(-rotateSpeed);
                        else
                            this->car.rotate(rotateSpeed);
                    }
                }
                break;
            }
            if (going)
            {
                switch (firstDirection)
                {
                case Direction::left:
                    goLeft(false);
                    break;
                case Direction::right:
                    goRight(false);
                    break;
                case Direction::up:
                    goUp(false);
                    break;
                case Direction::down:
                    goDown(false);
                    break;
                }
            }
        }
        else
        {
            switch (firstDirection)
            {
            case Direction::left:
                goLeft(lightPosition, light);
                break;
            case Direction::right:
                goRight(lightPosition, light);
                break;
            case Direction::up:
                goUp(lightPosition, light);
                break;
            case Direction::down:
                goDown(lightPosition, light);
                break;
            }
        }
    }
    void goUp(Car &previousCar)
    {
        this->car.setRotation(0.0f);
        if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
            ;
        else
            this->car.move(0.0f, -speed);
    }
    void goUp(sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(0.0f);
        if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
            ;
        else
            this->car.move(0.0f, -speed);
    }
    void goUp(Car &previousCar, sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(0.0f);
        if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
            ;
        else if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
            ;
        else
            this->car.move(0.0f, -speed);
    }
    bool goUp(bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(0.0f);
        if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
            return false;
        else
        {
            this->car.move(0.0f, -speed);
            return true;
        }
    }
    bool goUp(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(0.0f);
        if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
            return false;
        else if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
            return false;
        else
        {
            this->car.move(0.0f, -speed);
            return true;
        }
    }
    void goUp(bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(0.0f);
        this->car.move(0.0f, -speed);
    }
    void goUp()
    {
        this->car.setRotation(0.0f);
        this->car.move(0.0f, -speed);
    }
    void goDown(Car &previousCar)
    {
        this->car.setRotation(180.0f);
        if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
            ;
        else
            this->car.move(0.0f, speed);
    }
    void goDown(sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(180.0f);
        if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
            ;
        else
            this->car.move(0.0f, speed);
    }
    void goDown(Car &previousCar, sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(180.0f);
        if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
            ;
        else if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
            ;
        else
            this->car.move(0.0f, speed);
    }
    bool goDown(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(180.0f);
        if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
            return false;
        else if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
            return false;
        else
        {
            this->car.move(0.0f, speed);
            return true;
        }
    }
    bool goDown(bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(180.0f);
        if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
            return false;
        else
        {
            this->car.move(0.0f, speed);
            return true;
        }
    }
    void goDown(bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(180.0f);
        this->car.move(0.0f, speed);
    }
    void goDown()
    {
        this->car.setRotation(180.0f);
        this->car.move(0.0f, speed);
    }
    void goLeft(Car &previousCar)
    {
        this->car.setRotation(-90.0f);
        if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
            ;
        else
            this->car.move(-speed, 0.0f);
    }
    void goLeft(sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(-90.0f);
        if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
            ;
        else
            this->car.move(-speed, 0.0f);
    }
    void goLeft(Car &previousCar, sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(-90.0f);
        if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
            ;
        else if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
            ;
        else
            this->car.move(-speed, 0.0f);
    }
    bool goLeft(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(-90.0f);
        if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
            return false;
        else if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
            return false;
        else
        {
            this->car.move(-speed, 0.0f);
            return true;
        }
    }
    bool goLeft(bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(-90.0f);
        if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
            return false;
        else
        {
            this->car.move(-speed, 0.0f);
            return true;
        }
    }
    void goLeft(bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(-90.0f);
        this->car.move(-speed, 0.0f);
    }
    void goLeft()
    {
        this->car.setRotation(-90.0f);
        this->car.move(-speed, 0.0f);
    }
    void goRight(Car &previousCar)
    {
        this->car.setRotation(90.0f);
        if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
            ;
        else
            this->car.move(speed, 0.0f);
    }
    void goRight(sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(90.0f);
        if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
            ;
        else
            this->car.move(speed, 0.0f);
    }
    void goRight(Car &previousCar, sf::Vector2f lightPosition, bool light)
    {
        this->car.setRotation(90.0f);
        if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
            ;
        else if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
            ;
        else
            this->car.move(speed, 0.0f);
    }
    bool goRight(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(90.0f);
        if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
            return false;
        else if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
            return false;
        else
        {
            this->car.move(speed, 0.0f);
            return true;
        }
    }
    bool goRight(bool changeRotation, sf::Vector2f lightPosition, bool light)
    {
        if (changeRotation)
            this->car.setRotation(90.0f);
        if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
            return false;
        else
        {
            this->car.move(speed, 0.0f);
            return true;
        }
    }
    void goRight(bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(90.0f);
        this->car.move(speed, 0.0f);
    }
    void goRight()
    {
        this->car.setRotation(90.0f);
        this->car.move(speed, 0.0f);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(this->car);
    }
    float getRotation() const
    {
        return this->car.getRotation();
    }
    sf::Vector2f getPosition() const
    {
        return this->car.getPosition();
    }
    void setRotation(float &rotation)
    {
        this->car.setRotation(rotation);
    }
    void setSpeed(float &speed)
    {
        this->speed = speed;
    }
    float getSpeed() const
    {
        return this->speed;
    }
};