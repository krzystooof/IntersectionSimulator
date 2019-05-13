#pragma once
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
//TODO delete objects when out of view
class Car
{
private:
    sf::RectangleShape car;
    float height = 40.0f;
    const float width = 30.0f;
    float speed = .2f;
    float margin = 10;
    sf::Texture carTexture;

public:
    Car()
    {
        //texture
        this->carTexture.loadFromFile("graphics/car" + std::to_string(rand() % 6) + ".png");

        //dismensions
        float ratio = float(this->carTexture.getSize().y) / float(this->carTexture.getSize().x);
        this->height = this->width * ratio;
        car = sf::RectangleShape(sf::Vector2f(width, height));
        this->car.setTexture(&this->carTexture);

        //cout
        std::cout << "Car created at default position\n";
    }
    Car(float positionX, float positionY, CarCategory type, float speedMulitplier)
    {
        //texture
        std::string directory = "graphics/";
        if (type == CarCategory::car)
            this->carTexture.loadFromFile(directory + "car" + std::to_string(rand() % 6) + ".png");
        else if (type == CarCategory::longCar)
            this->carTexture.loadFromFile(directory + "longCar" + std::to_string(rand() % 1) + ".png");
        else if (type == CarCategory::tram)
            this->carTexture.loadFromFile(directory + "tram" + std::to_string(rand() % 1) + ".png");

        //dismensions
        float ratio = float(this->carTexture.getSize().y) / float(this->carTexture.getSize().x);
        this->height = this->width * ratio;
        car = sf::RectangleShape(sf::Vector2f(width, height));
        this->car.setTexture(&this->carTexture);

        //position
        car.setPosition(sf::Vector2f(positionX, positionY));

        //speed
        this->speed *= speedMulitplier;

        //cout
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
            if ((previousCar.getRotation() == 180 || previousCar.getRotation() == 0) && std::abs(previousCar.getPosition().y)>previousCar.height+margin)
                turned = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            if ((previousCar.getRotation() == 180 || previousCar.getRotation() == 0) && std::abs(previousCar.getPosition().y)>previousCar.height+margin)
                turned = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            if ((previousCar.getRotation() == 90 || previousCar.getRotation() == 270) && std::abs(previousCar.getPosition().x)>previousCar.height+margin)
                turned = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            if ((previousCar.getRotation() == 90 || previousCar.getRotation() == 270) && std::abs(previousCar.getPosition().x)>previousCar.height+margin)
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
        if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
            this->car.move(0.0f, -speed/10);
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
        if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
            this->car.move(0.0f, speed/10);
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
        this->car.setRotation(-90.0f);
        if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
            this->car.move(-speed/10, 0.0f);
        else
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
            this->car.move(speed/10, 0.0f);
        else
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
    void setSpeed(float &speed)
    {
        this->speed = speed;
    }
    float getSpeed() const
    {
        return this->speed;
    }
};