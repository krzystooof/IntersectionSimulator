#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "vehicles.hpp"
#include "lanes.hpp"
#include "Main.hpp"




const std::string ACTIVITY_TITLE = "Intersection Simulator";
const int WINDOW_SIZE = 800;

void WindowResized(const sf::RenderWindow &window, sf::View &view){
	float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
	view.setSize(WINDOW_SIZE*aspectRatio,WINDOW_SIZE);
}

int main()
{
	srand(time(NULL));


	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), ACTIVITY_TITLE, sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(WINDOW_SIZE,WINDOW_SIZE));
	std::vector<Car> cars;
	window.setFramerateLimit(180);
	Lane lane(0.0f,0.0f,30,0,LaneType::asphalt);
	lane.addVehicle(Direction::up,CarCategory::car,10);


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
				WindowResized(window,view);
				std::cout << "New window size: " << event.size.height << " x " << event.size.width << std::endl;
				break;
			}
		}
		lane.go(Direction::up);
		lane.draw(window);
		window.setView(view);
		window.display();
		window.clear();
	}
	return 0;
}