#pragma once
enum class LaneType
{
    inAsphalt,
    outAsphalt,
    asphalt,
    asphaltLeft,
    asphaltRight,
    tram,
    tramNoBackground
};

class Lane
{
private:
    sf::RectangleShape lane;
    float height = 400.0f;
    float width;
    bool light;
    sf::Texture laneTexture;
    std::vector<Car *> cars;
    LaneType type;

public:
    Lane()
    {
        //texture
        this->laneTexture.loadFromFile("graphics/laneAsphalt.png");
        this->laneTexture.setSmooth(true);

        //dismensions
        float ratio = float(this->laneTexture.getSize().x) / float(this->laneTexture.getSize().y);
        this->width = this->height * ratio;
        this->lane = sf::RectangleShape(sf::Vector2f(width, height));
        this->lane.setTexture(&this->laneTexture);

        //cout
        std::cout << "Lane created at default position\n";
    }
    Lane(float positionX, float positionY, float width, float rotation, LaneType type)
    {
        //texture
        this->type=type;
        if (type == LaneType::inAsphalt)
            this->laneTexture.loadFromFile("graphics/laneIn.png");
        else if (type == LaneType::outAsphalt)
            this->laneTexture.loadFromFile("graphics/laneOut.png");
        else if (type == LaneType::asphalt)
            this->laneTexture.loadFromFile("graphics/laneAsphalt.png");
        else if (type == LaneType::asphaltLeft)
            this->laneTexture.loadFromFile("graphics/laneAsphalt.png");//left lane
        else if (type == LaneType::asphaltRight)
            this->laneTexture.loadFromFile("graphics/laneAsphalt.png");//right lane
        else if (type == LaneType::tram)
            this->laneTexture.loadFromFile("graphics/laneTram.png");
        else if (type == LaneType::tramNoBackground)
            this->laneTexture.loadFromFile("graphics/laneTramNobackground.png");
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
    void addVehicle(CarCategory category)
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
        else if (category == CarCategory::car)
            speedMultiplier = ((rand() % 21) + 40) / 100.0;

        cars.push_back(new Car(this->width, x, y, category, speedMultiplier));
    }
    void addVehicle(CarCategory category, int amount)
    {
        for (int i = 0; i < amount; i++)
            this->addVehicle(category);
    }
    void go(Direction direction, Lane &lane)
    {
        if (cars.empty())
            ;
        else
        {
            switch (direction)
            {
            case Direction::up:
                cars[0]->goUp(lane);
                for (int i = 1; i < cars.size(); i++)
                {
                    cars[i]->goUp(*cars[i - 1],lane);
                }
                break;
            case Direction::down:
                cars[0]->goDown(lane);
                for (int i = 1; i < cars.size(); i++)
                {
                    cars[i]->goDown(*cars[i - 1],lane);
                }
                break;
            case Direction::left:
                cars[0]->goLeft(lane);
                for (int i = 1; i < cars.size(); i++)
                {
                    cars[i]->goLeft(*cars[i - 1],lane);
                }
                break;
            case Direction::right:
                cars[0]->goRight(lane);
                for (int i = 1; i < cars.size(); i++)
                {
                    cars[i]->goRight(*cars[i - 1],lane);
                }
                break;
            }
        }
    }
    void go(Direction firstDirection, Direction secondDirection, sf::Vector2f turningPosition, Lane &lane)
    {
        if (cars.empty())
            ;
        else
        {
            cars[0]->turn(firstDirection, secondDirection, turningPosition,lane);
            for (int i = 1; i < cars.size(); i++)
            {
                cars[i]->turn(firstDirection, secondDirection, turningPosition, *cars[i - 1],lane);
            }
        }
    }
    void draw(sf::RenderWindow &window)
    {

        window.draw(this->lane);
        if (!cars.empty())
        {
            for (auto it = cars.begin(); it != cars.end();)
            {
                if (std::abs((*it)->getPosition().x) > 500 || std::abs((*it)->getPosition().y) > 500)
                {
                    delete *it;
                    it = cars.erase(it);
                }
                else {
                    (*it)->draw(window);
                    it++;
                }
            }
        }
    }
    float getRotation() const
    {
        return this->lane.getRotation();
    }
    sf::Vector2f getPosition() const
    {
        return this->lane.getPosition();
    }
    LaneType getType() const{
        return this->type;
    }
    void changeLight(){
        light=!light;
    }
    bool getLight() const{
        return light;
    }
    sf::Vector2f getPosition() const{
        return this->lane.getPosition();
    }
};
