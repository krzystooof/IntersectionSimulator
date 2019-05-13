#pragma once
enum class LaneType
{
    inAsphalt,
    outAsphalt,
    asphalt,
    tram
};
enum class LaneDirection
{
    left,
    right,
    straight
};

class Lane
{
private:
    sf::RectangleShape lane;
    float height = 400.0f;
    float width;
    sf::Texture laneTexture;

public:
    Lane()
    {
        //texture
        this->laneTexture.loadFromFile("graphics/laneAsphalt.png");

        //dismensions
        float ratio = float(this->laneTexture.getSize().x) / float(this->laneTexture.getSize().y);
        this->width = this->height * ratio;
        this->lane = sf::RectangleShape(sf::Vector2f(width, height));
        this->lane.setTexture(&this->laneTexture);

        //cout
        std::cout << "Lane created at default position\n";
    }
    Lane(float positionX, float positionY, float width, LaneType type)
    {
        //texture
        if (type == LaneType::inAsphalt)
            this->laneTexture.loadFromFile("graphics/laneIn.png");
        else if (type == LaneType::outAsphalt)
            this->laneTexture.loadFromFile("graphics/laneOut.png");
        else if (type == LaneType::asphalt)
            this->laneTexture.loadFromFile("graphics/laneAsphalt.png");
        else if (type == LaneType::tram)
            this->laneTexture.loadFromFile("graphics/laneTram.png");

        //dismensions
        this->width = width;
        float ratio = float(this->laneTexture.getSize().y) / float(this->laneTexture.getSize().x);
        this->height = this->width * ratio;
        this->lane = sf::RectangleShape(sf::Vector2f(width, height));
        this->lane.setTexture(&this->laneTexture);

        //cout
        std::cout << "Lane created at: " << positionX << " x " << positionY << std::endl;
    }

    ~Lane()
    {
        std::cout << "Lane deleted\n";
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(this->lane);
    }
    float getRotation() const
    {
        return this->lane.getRotation();
    }
    sf::Vector2f getPosition() const
    {
        return this->lane.getPosition();
    }
};
