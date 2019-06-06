#include "vehicles.hpp"

void Car::turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, Car &previousCar, sf::Vector2f lightPosition, bool light, float laneWidth)
{
    if (this->speed > 1.0f)
        this->speed = 1.0f;
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
            if (go(firstDirection,secondDirection,previousCar, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection,secondDirection,previousCar, lightPosition, light);
                going = true;
                if (this->getRotation() > 271 || this->getRotation() < 269 || this->getRotation() == 0 || this->getRotation() == 180)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (turningPosition.y - this->car.getPosition().y)) * this->speed * 15 + .5f);
                    if (firstDirection == Direction::down)
                        this->car.rotate(rotateSpeed);
                    else
                        this->car.rotate(-rotateSpeed);
                }
            }
            break;
        case Direction::right:
            if (go(firstDirection,secondDirection,previousCar, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection,secondDirection,previousCar, lightPosition, light);
                going = true;
                if (this->getRotation() < 89 || this->getRotation() > 91 || this->getRotation() == 0 || this->getRotation() == 180)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (this->car.getPosition().y - turningPosition.y)) * this->speed * 15 + .5f);
                    if (firstDirection == Direction::down)
                        this->car.rotate(-rotateSpeed);
                    else
                        this->car.rotate(rotateSpeed);
                }
            }
            break;
        case Direction::up:
            if (go(firstDirection,secondDirection,previousCar, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection,secondDirection,previousCar, lightPosition, light);
                going = true;
                if (this->getRotation() > 1 || this->getRotation() < 359 || this->getRotation() == 90 || this->getRotation() == 270)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (this->car.getPosition().x - turningPosition.x)) * this->speed * 15 + .5f);
                    if (firstDirection == Direction::left)
                        this->car.rotate(rotateSpeed);
                    else
                        this->car.rotate(-rotateSpeed);
                }
            }
            break;
        case Direction::down:
            if (go(firstDirection,secondDirection,previousCar, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection,secondDirection,previousCar, lightPosition, light);
                going = true;
                if (this->getRotation() < 179 || this->getRotation() > 181 || this->getRotation() == 90 || this->getRotation() == 270)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (turningPosition.x - this->car.getPosition().x)) * this->speed * 15 + .5f);
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
void Car::turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, sf::Vector2f lightPosition, bool light, float laneWidth)
{
    if (this->speed > 1.0f)
        this->speed = 1.0f;
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
            if (go(firstDirection, secondDirection, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection, secondDirection, lightPosition, light);
                going = true;
                if (this->getRotation() > 271 || this->getRotation() < 269 || this->getRotation() == 0 || this->getRotation() == 180)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (turningPosition.y - this->car.getPosition().y)) * this->speed * 15 + .5f);
                    if (firstDirection == Direction::down)
                    {
                        this->car.rotate(rotateSpeed);
                    }
                    else
                        this->car.rotate(-rotateSpeed);
                }
            }
            break;
        case Direction::right:
            if (go(firstDirection, secondDirection, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection, secondDirection, lightPosition, light);
                going = true;
                if (this->getRotation() < 89 || this->getRotation() > 91 || this->getRotation() == 0 || this->getRotation() == 180)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (this->car.getPosition().y - turningPosition.y)) * this->speed * 15 + .5f);
                    if (firstDirection == Direction::down)
                        this->car.rotate(-rotateSpeed);
                    else
                        this->car.rotate(rotateSpeed);
                }
            }
            break;
        case Direction::up:
            if (go(firstDirection, secondDirection, lightPosition, light))
            {
                this->speed /= slowingSpeed;
               go(firstDirection, secondDirection, lightPosition, light);
                going = true;
                if (this->getRotation() > 1 || this->getRotation() < 359 || this->getRotation() == 90 || this->getRotation() == 270)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (this->car.getPosition().x - turningPosition.x)) * this->speed * 15 + .5f);
                    if (firstDirection == Direction::left)
                        this->car.rotate(rotateSpeed);
                    else
                        this->car.rotate(-rotateSpeed);
                }
            }
            break;
        case Direction::down:
            if (go(firstDirection,secondDirection, lightPosition, light))
            {
                this->speed /= slowingSpeed;
                go(firstDirection,secondDirection, lightPosition, light);
                going = true;
                if (this->getRotation() < 179 || this->getRotation() > 181 || this->getRotation() == 90 || this->getRotation() == 270)
                {
                    float rotateSpeed = std::sqrt(std::abs(1 / (turningPosition.x - this->car.getPosition().x)) * this->speed * 15 + .5f);
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
bool Car::go(Direction firstDirection, Direction secondDirection, Car &previousCar, sf::Vector2f lightPosition, bool light)
{
    bool condition = true;
    if (firstDirection == Direction::up)
    {
        if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
            condition = false;
    }
    else if (firstDirection == Direction::down)
    {
        if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
            condition = false;
    }
    else if (firstDirection == Direction::left)
    {
        if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
            condition = false;
    }
    else if (firstDirection == Direction::right)
    {
        if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
            condition = false;
    }
    if (condition)
    {
        if (secondDirection == Direction::up)
        {
            goUp(previousCar, false);
        }
        else if (secondDirection == Direction::down)
        {
            goDown(previousCar, false);
        }
        else if (secondDirection == Direction::left)
        {
            goLeft(previousCar, false);
        }
        else if (secondDirection == Direction::right)
        {
            goRight(previousCar, false);
        }
        return true;
    }
    else
        return false;
}
bool Car::go(Direction firstDirection, Direction secondDirection, sf::Vector2f lightPosition, bool light)
{
    bool condition = true;
    if (firstDirection == Direction::up)
    {
        if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
            condition = false;
    }
    else if (firstDirection == Direction::down)
    {
        if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
            condition = false;
    }
    else if (firstDirection == Direction::left)
    {
        if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
            condition = false;
    }
    else if (firstDirection == Direction::right)
    {
        if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
            condition = false;
    }
    if (condition)
    {
        if (secondDirection == Direction::up)
        {
            goUp(false);
        }
        else if (secondDirection == Direction::down)
        {
            goDown(false);
        }
        else if (secondDirection == Direction::left)
        {
            goLeft(false);
        }
        else if (secondDirection == Direction::right)
        {
            goRight(false);
        }
        return true;
    }
    else
        return false;
}
void Car::goUp(Car &previousCar)
{
    this->car.setRotation(0.0f);
    if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
        ;
    else
        this->car.move(0.0f, -speed);
}
void Car::goUp(sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(0.0f);
    if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
        ;
    else
        this->car.move(0.0f, -speed);
}
void Car::goUp(Car &previousCar, sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(0.0f);
    if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
        ;
    else if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
        ;
    else
        this->car.move(0.0f, -speed);
}
bool Car::goUp(bool changeRotation, sf::Vector2f lightPosition, bool light)
{
    if (changeRotation)
        this->car.setRotation(0.0f);
    if (lightPosition.y + margin >= this->car.getPosition().y && lightPosition.y <= this->car.getPosition().y && light)
    {
        return false;
    }
    else
    {
        this->car.move(0.0f, -speed);
        return true;
    }
}
bool Car::goUp(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
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
void Car::goUp(bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(0.0f);
    this->car.move(0.0f, -speed);
}
void Car::goUp(Car &previousCar, bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(0.0f);
    if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
        ;
    else
        this->car.move(0.0f, -speed);
}
void Car::goUp()
{
    this->car.setRotation(0.0f);
    this->car.move(0.0f, -speed);
}
void Car::goDown(Car &previousCar)
{
    this->car.setRotation(180.0f);
    if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
        ;
    else
        this->car.move(0.0f, speed);
}
void Car::goDown(sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(180.0f);
    if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
        ;
    else
        this->car.move(0.0f, speed);
}
void Car::goDown(Car &previousCar, sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(180.0f);
    if (lightPosition.y - margin <= this->car.getPosition().y && lightPosition.y >= this->car.getPosition().y && light)
        ;
    else if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
        ;
    else
        this->car.move(0.0f, speed);
}
bool Car::goDown(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
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
bool Car::goDown(bool changeRotation, sf::Vector2f lightPosition, bool light)
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
void Car::goDown(bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(180.0f);
    this->car.move(0.0f, speed);
}
void Car::goDown(Car &previousCar, bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(180.0f);
    if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
        ;
    else
        this->car.move(0.0f, speed);
}
void Car::goDown()
{
    this->car.setRotation(180.0f);
    this->car.move(0.0f, speed);
}
void Car::goLeft(Car &previousCar)
{
    this->car.setRotation(-90.0f);
    if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
        ;
    else
        this->car.move(-speed, 0.0f);
}
void Car::goLeft(sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(-90.0f);
    if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
        ;
    else
        this->car.move(-speed, 0.0f);
}
void Car::goLeft(Car &previousCar, sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(-90.0f);
    if (lightPosition.x + margin >= this->car.getPosition().x && lightPosition.x <= this->car.getPosition().x && light)
        ;
    else if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
        ;
    else
        this->car.move(-speed, 0.0f);
}
bool Car::goLeft(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
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
bool Car::goLeft(bool changeRotation, sf::Vector2f lightPosition, bool light)
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
void Car::goLeft(bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(-90.0f);
    this->car.move(-speed, 0.0f);
}
void Car::goLeft(Car &previousCar, bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(-90.0f);
    if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
        ;
    else
        this->car.move(-speed, 0.0f);
}
void Car::goLeft()
{
    this->car.setRotation(-90.0f);
    this->car.move(-speed, 0.0f);
}
void Car::goRight(Car &previousCar)
{
    this->car.setRotation(90.0f);
    if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
        ;
    else
        this->car.move(speed, 0.0f);
}
void Car::goRight(sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(90.0f);
    if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
        ;
    else
        this->car.move(speed, 0.0f);
}
void Car::goRight(Car &previousCar, sf::Vector2f lightPosition, bool light)
{
    this->car.setRotation(90.0f);
    if (lightPosition.x - margin <= this->car.getPosition().x && lightPosition.x >= this->car.getPosition().x && light)
        ;
    else if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
        ;
    else
        this->car.move(speed, 0.0f);
}
bool Car::goRight(Car &previousCar, bool changeRotation, sf::Vector2f lightPosition, bool light)
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
bool Car::goRight(bool changeRotation, sf::Vector2f lightPosition, bool light)
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
void Car::goRight(bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(90.0f);
    this->car.move(speed, 0.0f);
}
void Car::goRight(Car &previousCar, bool changeRotation)
{
    if (changeRotation)
        this->car.setRotation(90.0f);
    if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
        ;
    else
        this->car.move(speed, 0.0f);
}
void Car::goRight()
{
    this->car.setRotation(90.0f);
    this->car.move(speed, 0.0f);
}

void Car::draw(sf::RenderWindow &window)
{
    window.draw(this->car);
}
float Car::getRotation() const
{
    return this->car.getRotation();
}
sf::Vector2f Car::getPosition() const
{
    return this->car.getPosition();
}
void Car::setRotation(float &rotation)
{
    this->car.setRotation(rotation);
}
void Car::setSpeed(float &speed)
{
    this->speed = speed;
}
float Car::getSpeed() const
{
    return this->speed;
}