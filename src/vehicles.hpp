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
//TODO delete objects when out of view, turning in sine function
class Car
{
private:
    sf::RectangleShape car;
    float height = 40.0f;
    float width = 30.0f;
    float speed = .6f;
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
            textureNumber = rand() % 1;
            this->carTexture.loadFromFile(directory + "tram" + std::to_string(textureNumber) + ".png");
            out = "Tram";
        }
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
        std::cout<<"Car deleted\n";
    }
    void turn(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition)
    {
        bool second = false;
        bool middle = false;
        switch (firstDirection)
        {
        case Direction::left:
            if (this->car.getPosition().x < turningPosition.x + (this->height/2))
                middle = true;
            if (this->car.getPosition().x < turningPosition.x)
                second = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x - (this->height/2))
                middle = true;
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y + (this->height/2))
                middle = true;
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y - (this->height/2))
                middle = true;
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            break;
        }
        if (second)
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
        else if (middle)
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
            float rotateSpeed = this->speed * 4;
            switch (secondDirection)
            {
            case Direction::left:
                goLeft(false);
                if (this->getRotation() > 270.5 || this->getRotation() < 269.5 || this->getRotation() == 0 || this->getRotation() == 180)
                {
                    if (firstDirection == Direction::down)
                        this->car.rotate(this->speed * rotateSpeed);
                    else
                        this->car.rotate(-this->speed * rotateSpeed);
                }
                break;
            case Direction::right:
                goRight(false);
                if (this->getRotation() < 89.5 || this->getRotation() > 90.5 || this->getRotation() == 0 || this->getRotation() == 180)
                {
                    if (firstDirection == Direction::down)
                        this->car.rotate(-this->speed * rotateSpeed);
                    else
                        this->car.rotate(this->speed * rotateSpeed);
                }
                break;
            case Direction::up:
                goUp(false);
                if (this->getRotation() > 0.5 || this->getRotation() < 359.5 || this->getRotation() == 90 || this->getRotation() == 270)
                {
                    if (firstDirection == Direction::left)
                        this->car.rotate(this->speed * rotateSpeed);
                    else
                        this->car.rotate(-this->speed * rotateSpeed);
                }
                break;
            case Direction::down:
                goDown(false);
                if (this->getRotation() < 179.5 || this->getRotation() > 180.5 || this->getRotation() == 90 || this->getRotation() == 270)
                {
                    if (firstDirection == Direction::left)
                        this->car.rotate(-this->speed * rotateSpeed);
                    else
                        this->car.rotate(this->speed * rotateSpeed);
                }
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
        bool middle = false;
        switch (firstDirection)
        {
        case Direction::left:
            if (this->car.getPosition().x < turningPosition.x + (this->height/2))
                middle = true;
            if (this->car.getPosition().x < turningPosition.x)
                second = true;
            break;
        case Direction::right:
            if (this->car.getPosition().x > turningPosition.x - (this->height/2))
                middle = true;
            if (this->car.getPosition().x > turningPosition.x)
                second = true;
            break;
        case Direction::up:
            if (this->car.getPosition().y < turningPosition.y + (this->height/2))
                middle = true;
            if (this->car.getPosition().y < turningPosition.y)
                second = true;
            break;
        case Direction::down:
            if (this->car.getPosition().y > turningPosition.y - (this->height/2))
                middle = true;
            if (this->car.getPosition().y > turningPosition.y)
                second = true;
            break;
        }
        if (second)
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
        else if (middle)
        {
            bool going = false;
            float rotateSpeed = this->speed * 4;
            switch (secondDirection)
            {
            case Direction::left:
                if (goLeft(previousCar, false))
                {
                    going = true;
                    if (this->getRotation() > 270.5 || this->getRotation() < 269.5 || this->getRotation() == 0 || this->getRotation() == 180)
                    {
                        if (firstDirection == Direction::down)
                            this->car.rotate(this->speed * rotateSpeed);
                        else
                            this->car.rotate(-this->speed * rotateSpeed);
                    }
                }
                break;
            case Direction::right:
                if (goRight(previousCar, false))
                {
                    going = true;
                    if (this->getRotation() < 89.5 || this->getRotation() > 90.5 || this->getRotation() == 0 || this->getRotation() == 180)
                    {
                        if (firstDirection == Direction::down)
                            this->car.rotate(-this->speed * rotateSpeed);
                        else
                            this->car.rotate(this->speed * rotateSpeed);
                    }
                }
                break;
            case Direction::up:
                if (goUp(previousCar, false))
                {
                    going = true;
                    if (this->getRotation() > 0.5 || this->getRotation() < 359.5 || this->getRotation() == 90 || this->getRotation() == 270)
                    {
                        if (firstDirection == Direction::left)
                            this->car.rotate(this->speed * rotateSpeed);
                        else
                            this->car.rotate(-this->speed * rotateSpeed);
                    }
                }
                break;
            case Direction::down:
                if (goDown(previousCar, false))
                {
                    going = true;
                    if (this->getRotation() < 179.5 || this->getRotation() > 180.5 || this->getRotation() == 90 || this->getRotation() == 270)
                    {
                        if (firstDirection == Direction::left)
                            this->car.rotate(-this->speed * rotateSpeed);
                        else
                            this->car.rotate(this->speed * rotateSpeed);
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
                    goLeft(previousCar);
                else
                    goLeft();
                break;
            case Direction::right:
                if (previousCar.getRotation() == 90.0f)
                    goRight(previousCar);
                else
                    goRight();
                break;
            case Direction::up:
                if (previousCar.getRotation() == 0.0f)
                    goUp(previousCar);
                else
                    goUp();
                break;
            case Direction::down:
                if (previousCar.getRotation() == 180.0f)
                    goDown(previousCar);
                else
                    goDown();
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
    bool goUp(Car &previousCar, bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(0.0f);
        if (previousCar.getPosition().y + previousCar.height + margin >= this->car.getPosition().y)
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
    bool goDown(Car &previousCar, bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(180.0f);
        if (previousCar.getPosition().y - previousCar.height - margin <= this->car.getPosition().y)
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
    bool goLeft(Car &previousCar, bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(-90.0f);
        if (previousCar.getPosition().x + previousCar.height + margin >= this->car.getPosition().x)
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
    bool goRight(Car &previousCar, bool changeRotation)
    {
        if (changeRotation)
            this->car.setRotation(90.0f);
        if (previousCar.getPosition().x - previousCar.height - margin <= this->car.getPosition().x)
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