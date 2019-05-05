#include <vector>
#include "Main.hpp"
#include "vehicles.hpp"

const std::string ACTIVITY_TITLE = "Intersection Simulator";
const int WINDOW_SIZE = 800;

void WindowResized(const sf::RenderWindow &window, sf::View &view){
	float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
	view.setSize(WINDOW_SIZE*aspectRatio,WINDOW_SIZE);
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), ACTIVITY_TITLE, sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(WINDOW_SIZE,WINDOW_SIZE));
	std::vector<Car> cars;
	Car car(0,50);
	Car car1(0,200,0.02f);
	// for (int i = 0; i<10;i++){
	// 	cars.push_back(Car(0,WINDOW_SIZE/2));
	// }


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
		// cars[0].draw(window);
		// cars[0].goUp(window,car);
		// for (int i =1;i<cars.size();i++){
		// 	cars[i].draw(window);
		// 	cars[i].goUp(window,cars[i-1]);
		// }
		car.draw(window);
		car1.draw(window);
		car.turn(Direction::up,Direction::right,sf::Vector2f(car1.getPosition().x,0));
		car1.turn(Direction::up,Direction::right,sf::Vector2f(car1.getPosition().x,0),car);
		window.setView(view);
		window.display();
		window.clear();
	}
	return 0;
}