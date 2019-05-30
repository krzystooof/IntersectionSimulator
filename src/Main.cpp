#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "vehicles.hpp"
#include "lanes.hpp"
#include "intersection.hpp"
#include "menu.hpp"
#include "Main.hpp"

const std::string ACTIVITY_TITLE = "Intersection Simulator";



int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(730.0f, 1000.0f), ACTIVITY_TITLE, sf::Style::Close);
	sf::View simulation(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));
	sf::View bottomPanel(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 250.0f));
	simulation.setViewport(sf::FloatRect(.0f, .0f, 1.f, 0.73f));
	bottomPanel.setViewport(sf::FloatRect(.0f, .75f, 1.f, .25f));
	window.setFramerateLimit(60);
	std::vector<LaneType> right{LaneType::tram, LaneType::asphalt, LaneType::asphaltRight};
	std::vector<LaneType> left{LaneType::asphalt};
	Intersection intersection(std::vector<std::vector<LaneType>>{left, left,right, right});
	intersection.addVehicles(10);
	Menu menu = Menu();

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

			case sf::Event::KeyPressed:
				if(event.key.code==sf::Keyboard::Space) intersection.changeLight();
				else if(event.key.code==sf::Keyboard::Up) menu.nextAnswer();
				else if(event.key.code==sf::Keyboard::Down) menu.previousAnswer();
				else if(event.key.code==sf::Keyboard::Left) menu.previousQuestion();
				else if(event.key.code==sf::Keyboard::Right) menu.nextQuestion();
				break;
			}
		}
		intersection.go();
		window.setView(simulation);
		intersection.draw(window);
		window.setView(bottomPanel);
		menu.draw(window);
		window.display();
		window.clear();
	}
	return 0;
}