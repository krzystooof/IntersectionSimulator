#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include "vehicles.hpp"
#include "lanes.hpp"
#include "intersection.hpp"
#include "menu.hpp"
#include "Main.hpp"

const std::string ACTIVITY_TITLE = "Intersection Simulator";
int timesBuild = 0, group=-1;

int main()
{
	srand(time(NULL));
	sf::Clock clock;

	sf::RenderWindow simulationWindow(sf::VideoMode(800.0f, 800.0f), ACTIVITY_TITLE, sf::Style::Close);
	simulationWindow.setVisible(false);
	sf::View simulation(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));
	sf::RenderWindow menuWindow(sf::VideoMode(800.0f, 200.0f), ACTIVITY_TITLE + " menu", sf::Style::Close);
	menuWindow.setVisible(false);
	sf::View bottomPanel(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 200.0f));
	menuWindow.setFramerateLimit(60);
	simulationWindow.setFramerateLimit(60);
	Menu menu = Menu();
	std::vector<std::vector<LaneType>> lanes{{LaneType::asphalt}, {LaneType::asphalt}, {LaneType::asphalt}, {LaneType::asphalt}};
	Intersection *intersection = new Intersection(lanes);
	std::vector<sf::Time> time{clock.getElapsedTime(), clock.getElapsedTime(), clock.getElapsedTime(), clock.getElapsedTime()};
	sf::Time lastChangeTime = sf::seconds(0);
	menuWindow.setVisible(true);

	while (menuWindow.isOpen())
	{
		sf::Event event;
		while (menuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				menuWindow.close();
				simulationWindow.close();
				std::cout << "Menu window closed\n";
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up)
					menu.nextAnswer();
				else if (event.key.code == sf::Keyboard::Down)
					menu.previousAnswer();
				else if (event.key.code == sf::Keyboard::Right)
					menu.nextQuestion();
				break;
			}
			if (menu.getBuild() && timesBuild == 0)
			{
				timesBuild++;
				lanes.clear();
				lanes.push_back(menu.getLeftRight());
				lanes.push_back(menu.getLeftRight());
				lanes.push_back(menu.getUpDown());
				lanes.push_back(menu.getUpDown());
			}
		}
		if (menu.getClose())
		{
			menuWindow.close();
		}
		menuWindow.setView(bottomPanel);
		menu.draw(menuWindow);
		menuWindow.display();
		menuWindow.clear();
	}
	while (simulationWindow.isOpen())
	{

		if (timesBuild == 1)
		{
			timesBuild++;
			intersection = new Intersection(lanes);
			intersection->setGroups(LightChangingType::smart);
		}
		if (menu.getGo())
		{
			simulationWindow.setVisible(true);
			std::vector<int> times = menu.getTimes();
			sf::Time elapsedTime = clock.getElapsedTime() - time[0];
			if (elapsedTime.asSeconds() >= times[0])
			{
				intersection->addVehicles(1, Direction::right);
				time[0] = clock.getElapsedTime();
			}
			elapsedTime = clock.getElapsedTime() - time[1];
			if (elapsedTime.asSeconds() >= times[1])
			{
				intersection->addVehicles(1, Direction::left);
				time[1] = clock.getElapsedTime();
			}
			elapsedTime = clock.getElapsedTime() - time[2];
			if (elapsedTime.asSeconds() >= times[2])
			{
				intersection->addVehicles(1, Direction::down);
				time[2] = clock.getElapsedTime();
			}
			elapsedTime = clock.getElapsedTime() - time[3];
			if (elapsedTime.asSeconds() >= times[3])
			{
				intersection->addVehicles(1, Direction::up);
				time[3] = clock.getElapsedTime();
			}
			intersection->go();
		}
		sf::Event event2;
		while (simulationWindow.pollEvent(event2))
		{
			switch (event2.type)
			{
			case sf::Event::Closed:
				simulationWindow.close();
				std::cout << "Simulation window closed\n";
				break;

			case sf::Event::KeyPressed:
				if (event2.key.code == sf::Keyboard::Space)
					break;
			}
		}
		sf::Time elapsedTime = clock.getElapsedTime() - lastChangeTime;

		if (elapsedTime.asSeconds() > 5)
		{
			group = intersection->changeLightToRed(LightChangingType::smart);
			lastChangeTime=clock.getElapsedTime();
		}
		if(clock.getElapsedTime()-lastChangeTime>sf::seconds(2.3f)) intersection->changeLightToGreen(group);
		simulationWindow.setView(simulation);
		intersection->draw(simulationWindow);
		simulationWindow.display();
		simulationWindow.clear();
	}
	return 0;
}

// int main()
// {
// 	srand(time(NULL));

// 	sf::RenderWindow window(sf::VideoMode(730.0f, 1000.0f), ACTIVITY_TITLE, sf::Style::Close);
// 	sf::View simulation(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));
// 	window.setFramerateLimit(60);
// 	Lane lane(0, 000, 30, 0, LaneType::asphaltLeft);
// 	lane.addVehicle(CarCategory::car);

// 	while (window.isOpen())
// 	{
// 		sf::Event event;
// 		while (window.pollEvent(event))
// 		{
// 			switch (event.type)
// 			{
// 			case sf::Event::Closed:
// 				window.close();
// 				std::cout << "Window closed\n";
// 				break;

// 			case sf::Event::KeyPressed:
// 				break;
// 			}
// 		}
// 		window.setView(simulation);
// 		lane.go(Direction::up, Direction::left, sf::Vector2f(0, 0));
// 		lane.draw(window);
// 		window.display();
// 		window.clear();
// 	}
// 	return 0;
// }
// int main()
// {
// 	srand(time(NULL));
// 	bool light=false;
// 	sf::RenderWindow window(sf::VideoMode(800.0f, 800.0f), ACTIVITY_TITLE, sf::Style::Close);
// 	sf::View simulation(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));
// 	window.setFramerateLimit(60);
// 	Car car(30,0,250,CarCategory::car,1);
// 	while (window.isOpen())
// 	{
// 		sf::Event event;
// 		while (window.pollEvent(event))
// 		{
// 			switch (event.type)
// 			{
// 			case sf::Event::Closed:
// 				window.close();
// 				std::cout << "Window closed\n";
// 				break;

// 			case sf::Event::KeyPressed:
// 				light=!light;
// 				break;
// 			}
// 		}

// 		window.setView(simulation);
// 		car.turn(Direction::up, Direction::left, sf::Vector2f(0, -100),sf::Vector2f(0,100),light,30);
// 		car.draw(window);
// 		window.display();
// 		window.clear();
// 	}
// 	return 0;
// }