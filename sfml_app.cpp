#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

int main()
{
	const int resX{ 1920 }, resY{ 1080 };																// Deklaracja rozdzielczosci

	const float M_PI = (float)acos(-1);																	// Definicja stalej PI
	float x, y;																							// Zmienne do obliczania wykresu
	int scaleY{ 400 }, scaleX{ 1 };																		// Zmienne do skalowania
	int sX{ 6 }, sY{ 6 };																				// Liczba podzialek na osi X

	bool pokaz_kolko{ false };																			// Przelacznik widocznosci kolka



	sf::RenderWindow window(sf::VideoMode(resX, resY, 32), "SFML Wykresy", sf::Style::Fullscreen);		// Utworzenie okna programu
		window.setMouseCursorVisible(false);															// Wylaczenie kursora
		window.setFramerateLimit(25);																	// Czestotliwosc odswiezania
		window.setVerticalSyncEnabled(true);															// Vertical Sync On

	sf::VertexArray osX(sf::Lines, 2);																	// Linia osi X
		osX[0].position = sf::Vector2f(20.f, float(0.5) * resY);										// 
		osX[1].position = sf::Vector2f(float(resX) - 20.0f, float(0.5 * resY));							// 

	sf::VertexArray osY(sf::Lines, 2);																	// Linia osi Y
		osY[0].position = sf::Vector2f(20.f, 20.f);														// 
		osY[1].position = sf::Vector2f(20.f, float(resY) - 20.0f);										// 

	sf::VertexArray grotX(sf::Triangles, 3);															// Grot osi X
		grotX[0].position = sf::Vector2f(float(resX) - 20.f, float(0.5 * resY));						// 
		grotX[1].position = sf::Vector2f(float(resX) - 40.f, float(0.5 * resY) - 4.f);					// 
		grotX[2].position = sf::Vector2f(float(resX) - 40.f, float(0.5 * resY) + 4.f);					// 

	sf::VertexArray grotY(sf::Triangles, 3);															// Grot osi Y
		grotY[0].position = sf::Vector2f(20.f, 20.f);													// 
		grotY[1].position = sf::Vector2f(20.f - 4.f, 40.f);												// 
		grotY[2].position = sf::Vector2f(20.f + 4.f, 40.f);												// 

	sf::CircleShape kolko(10); 
	kolko.setPosition(1890, 0);
	kolko.setFillColor(sf::Color::Green);

	sf::CircleShape* punkty = new sf::CircleShape[resX]; 
	sf::CircleShape* xy = punkty;




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
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Space)) window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) pokaz_kolko = !pokaz_kolko; std::cout << pokaz_kolko;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) scaleY++;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) scaleY--;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Multiply) scaleX++;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Divide) scaleX--;

																												//???????????????????????????????

		}

		// Rysowanie aktualnej klatki ///////////////////////////////////////////////////

		window.clear(sf::Color::Black);
		window.draw(osX); window.draw(osY);
		window.draw(grotX); window.draw(grotY);

		sf::VertexArray* podzX = new sf::VertexArray[sX+1];

		for (int i = 0; i < sX; i++)
		{
			(podzX + i)->setPrimitiveType(sf::Lines); 
			(podzX + i)->append(sf::Vector2f(20.0f + (float)i * ((float)resX - 40.0f + (float)scaleX) / (float)sX, 0.5f * (float)resY));
			(podzX + i)->append(sf::Vector2f(20.0f + (float)i * ((float)resX - 40.0f + (float)scaleX) / (float)sX, 0.5f * (float)resY + 10.0f));
			window.draw(*(podzX + i));
		}

		sf::VertexArray* podzY = new sf::VertexArray[2 * sY];


			for (int i = 0; i < sY; i++)
			{
				(podzY + i)->setPrimitiveType(sf::Lines);
				(podzY + i)->append(sf::Vector2f(20.0f, 0.5f * (float)resY - (float)i * (float)scaleY));
				(podzY + i)->append(sf::Vector2f(30.0f, 0.5f * (float)resY - (float)i * (float)scaleY));
				window.draw(*(podzY + i));

				(podzY + i + 1)->setPrimitiveType(sf::Lines);
				(podzY + i + 1)->append(sf::Vector2f(20.0f, 0.5f * (float)resY + (float(i + 1) * (float)scaleY)));
				(podzY + i + 1)->append(sf::Vector2f(30.0f, 0.5f * (float)resY + (float(i + 1) * (float)scaleY)));
				window.draw(*(podzY + i + 1));

			}

		if (pokaz_kolko) window.draw(kolko);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) kolko.move(20, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) kolko.move(-20, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) kolko.move(0, -20);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) kolko.move(0, 20);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))												//???????????????????????????????
		{																										//???????????????????????????????
			window.draw(kolko);																					//???????????????????????????????
			scaleX = event.mouseMove.x;																			//???????????????????????????????
			scaleY = event.mouseMove.y;
		}

		for (int i = 0; i < resX; i++)																			// Rysowanie wykresu punkt po punkcie
		{
			(xy + i) -> setRadius(1);
			(xy + i) -> setFillColor(sf::Color::Red);

			x = 2.f * M_PI * (float(i) - 20.f) / ((float(resX) - 40.f) + (float)scaleX);
			y = sin(x*sin(2*x));																				// Formula do wyswietlenia

			(xy + i) -> setPosition(sf::Vector2f((float)i, -(float)scaleY * y + 0.5f * (float)resY));
			window.draw(*(xy + i));
		}

		window.display();

		delete[] podzX;
		delete[] podzY;
	}

	return 0;
}