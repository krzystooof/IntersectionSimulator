#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "vehicles.hpp"
#include "lanes.hpp"
#include "intersection.hpp"
#include "Main.hpp"

const std::string ACTIVITY_TITLE = "Intersection Simulator";
const int WINDOW_SIZE = 800;

void WindowResized(const sf::RenderWindow &window, sf::View &view)
{
	float x = float(window.getSize().x);
	float y = float(window.getSize().y);
	if (x > WINDOW_SIZE)
		x = WINDOW_SIZE;
	if (y > WINDOW_SIZE)
		y = WINDOW_SIZE;
	view.setSize(x, y);
}

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), ACTIVITY_TITLE, sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE));
	std::vector<Car> cars;
	window.setFramerateLimit(60);
	std::vector<LaneType> right{LaneType::tram, LaneType::asphalt, LaneType::asphaltRight};
	std::vector<LaneType> left{LaneType::asphalt, LaneType::asphalt};
	Intersection intersection(std::vector<std::vector<LaneType>>{right, right, right, right});
	intersection.addVehicles(CarCategory::car, 10);
	// std::vector<Lane> lanes;
	// Lane lane1(-5,0.0f,5,0,LaneType::inAsphalt);
	// Lane lane(0,0.0f,30,0,LaneType::asphalt);
	// lane.addVehicle(Direction::up,CarCategory::car,3);
	// lane.addVehicle(Direction::up,CarCategory::longCar,2);
	// lane.addVehicle(Direction::up,CarCategory::car,5);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				std::cout << "Window closed\n";
				break;
			case sf::Event::Resized:
				WindowResized(window, view);

				std::cout << "New window size: " << event.size.height << " x " << event.size.width << std::endl;
				break;

			case sf::Event::KeyPressed:
				if(event.key.code==sf::Keyboard::Space) intersection.changeLight();
				break;
			}
		}
		intersection.go();
		intersection.draw(window);
		// lane.go(Direction::up,Direction::right,sf::Vector2f(0.0,0.0));
		// lane1.draw(window);
		// lane.draw(window);
		window.setView(view);
		window.display();
		window.clear();
	}
	return 0;
}