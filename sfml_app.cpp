#include <SFML/Graphics.hpp>

int main()
{
	int resX{ 1920 }, resY{ 1080 };
	float x, y;
	;

	sf::RenderWindow window(sf::VideoMode(resX, resY, 32), "SFML Wykresy", sf::Style::Fullscreen);		// Utworzenie okna programu
		window.setMouseCursorVisible(false);															// Wylaczenie kursora
		window.setFramerateLimit(60);																	// Czestotliwosc odswiezania
		window.setVerticalSyncEnabled(true);															// Vertical Sync On

	sf::VertexArray osX(sf::Lines, 2);																	// Linia osi X
		osX[0].position = sf::Vector2f(20.f, float(0.5) * resY);										// 
		osX[1].position = sf::Vector2f(float(resX) - 20.0f, float(0.5 * resY));							// 

	sf::VertexArray grotX(sf::Triangles, 3);															// Grot osi X
		grotX[0].position = sf::Vector2f(float(resX) - 20.f, float(0.5 * resY));						// 
		grotX[1].position = sf::Vector2f(float(resX) - 40.f, float(0.5 * resY) - 4.f);					// 
		grotX[2].position = sf::Vector2f(float(resX) - 40.f, float(0.5 * resY) + 4.f);					// 

	sf::VertexArray osY(sf::Lines, 2);																	// Linia osi Y
		osY[0].position = sf::Vector2f(float(0.5) * resX, 20.f);										// 
		osY[1].position = sf::Vector2f(float(0.5 * resX), float(resY) - 20.0f);							// 

	sf::VertexArray grotY(sf::Triangles, 3);															// Grot osi Y
		grotY[0].position = sf::Vector2f(float(0.5) * resX, 20.f);										// 
		grotY[1].position = sf::Vector2f(float(0.5) * resX - 4.f, 40.f);								// 
		grotY[2].position = sf::Vector2f(float(0.5) * resX + 4.f, 40.f);								// 

	sf::Vertex wykres[1920];

	sf::Vertex punkt(sf::Vector2f(200,300), sf::Color::Red);





	////////////////////////////////////////////////////////////////////////////////////////
	////////////// GLOWNA PETLA ANIMACJI ///////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		// Sprawdzanie i wykonywanie zdarzen //////////////////////////////////////////////

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
		}

		// Rysowanie aktualnej klatki ///////////////////////////////////////////////////

		window.clear(sf::Color::Black);
		window.draw(osX); window.draw(osY);
		window.draw(grotX); window.draw(grotY);


		window.display();
	}

	return 0;
}