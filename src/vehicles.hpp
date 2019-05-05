#pragma once
enum class Direction
{
    left,
    right,
    up,
    down
};
//TODO delete objects when out of view
class Car
{
private:
    sf::RectangleShape car;
    const float height = 40.0f;
    const float width = 30.0f;
    float speed = 0.01f;
    float margin = 10;

public:
    Car()
    {
        car = sf::RectangleShape(sf::Vector2f(width, height));
        std::cout << "Car created at default position\n";
    }
    Car(float positionX, float positionY)
    {
        car = sf::RectangleShape(sf::Vector2f(30.0f, 40.0f));
        car.setPosition(sf::Vector2f(positionX, positionY));
        std::cout << "Car created at: " << positionX << " x " << positionY << std::endl;
    }
    Car(float positionX, float positionY, float speed)
    {
        this->speed = speed;
        car = sf::RectangleShape(sf::Vector2f(30.0f, 40.0f));
        car.setPosition(sf::Vector2f(positionX, positionY));
        std::cout << "Car created at: " << positionX << " x " << positionY << std::endl;
    }
    ~Car()
    {
        std::cout << "Car deleted\n";
    }
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition)
    {
        bool second = false;
        switch (firstDirection)
        {
        case Direction::left:
            if (this->car.getPosition().x < turningPosition.x)
                second = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            break;
        }
        if (second == true)
        {
            switch (secondDirection)
            {
            case Direction::left:
                goLeft();
                break;
            case Direction::right:
                goRight();
                break;
            case Direction::up:
                goUp();
                break;
            case Direction::down:
                goDown();
                break;
            }
        }
        else
        {
            switch (firstDirection)
            {
            case Direction::left:
                goLeft();
                break;
            case Direction::right:
                goRight();
                break;
            case Direction::up:
                goUp();
                break;
            case Direction::down:
                goDown();
                break;
            }
        }
    }
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, Car &previousCar)
    {
        bool second = false;
        bool turned = false;
        switch (firstDirection)
        {
        case Direction::left:
            if (this->car.getPosition().x < turningPosition.x)
                second = true;
            if (previousCar.getRotation()==180||previousCar.getRotation()==0)
                turned = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            if (previousCar.getRotation()==180||previousCar.getRotation()==0)
                turned = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            if (previousCar.getRotation()==90||previousCar.getRotation()==270)
                turned = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            if (previousCar.getRotation()==90||previousCar.getRotation()==270)
                turned = true;
            break;
        }
        if (second == true)
        {
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
        else
        {
            if (turned == false)
            {
                switch (firstDirection)
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
            else
            {
                switch (firstDirection)
                {
                case Direction::left:
                    goLeft();
                    break;
                case Direction::right:
                    goRight();
                    break;
                case Direction::up:
                    goUp();
                    break;
                case Direction::down:
                    goDown();
                    break;
                }
            }
        }
        std::cout << second << " " << turned << " " << previousCar.getRotation() << std::endl;
    }
    void goUp(Car &previousCar)
    {
        this->car.setRotation(0.0f);
        if (previousCar.getPosition().y + height + margin >= this->car.getPosition().y)
            ; //car stopped
        else
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
        if (previousCar.getPosition().y - height - margin <= this->car.getPosition().y)
            ; //car stopped
        else
            this->car.move(0.0f, speed);
    }
    void goDown()
    {
        this->car.setRotation(180.0f);
        this->car.move(0.0f, speed);
    }
    void goLeft(Car &previousCar)
    {
        this->car.setRotation(90.0f);
        if (previousCar.getPosition().x + height + margin >= this->car.getPosition().x)
            ; //car stopped
        else
            this->car.move(-speed, 0.0f);
    }
    void goLeft()
    {
        this->car.setRotation(90.0f);
        this->car.move(-speed, 0.0f);
    }
    void goRight(Car &previousCar)
    {
        this->car.setRotation(-90.0f);
        if (previousCar.getPosition().x - height - margin <= this->car.getPosition().x)
            ; //car stopped
        else
            this->car.move(speed, 0.0f);
    }
    void goRight()
    {
        this->car.setRotation(-90.0f);
        this->car.move(speed, 0.0f);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(this->car);
    }
    float getRotation() const{
        return this->car.getRotation();
    }
    sf::Vector2f getPosition() const
    {
        return this->car.getPosition();
    }
};