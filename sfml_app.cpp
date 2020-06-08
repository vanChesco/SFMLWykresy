#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

int main()
{
	const int resX{ 1920 }, resY{ 1200 };																			// Deklaracja rozdzielczosci

	sf::ContextSettings settings;																					// Ustawienie antyaliasingu
		settings.antialiasingLevel = 16;
	
	float margX{ 20 }, margY{ 20 };																					// Marginesy

	const float M_PI = (float)acos(-1);																				// Definicja stalej PI
	float x, y;																										// Zmienne do obliczania wykresu
	int scaleY{ 2 }, scaleX{ 1 };																					// Zmienne do skalowania
	int iloscPodzialekX{ 6 }, iloscPodzialekY{ 6 };																	// Liczba podzialek na osi X
	float uX{ 1.0f * M_PI }, uY{ 2 };																				// Jednostki osi
	float x_max{ 4.f * M_PI }, y_max{ 2.f };																		// Wartosci mx osi
	float x_min{ -0.1f * M_PI }, y_min{ -2.f };																		// Wartosci mx osi

	float dX = (resX - 2 * margX) / (x_max - x_min);				
	float dY = (resY - 2 * margY) / (y_max - y_min);																// Dlugosc jednej dzialki

	float xo = dX * (-x_min);
	float yo = dY * (-y_min);

	sf::Vector2f axisOrigin{ xo, yo };																				// Punkt skrzyzowania osi

	bool pokaz_kolko{ false };																						// Przelacznik widocznosci kolka




	sf::Font czcionka;
		czcionka.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	


	sf::RenderWindow window(sf::VideoMode(resX, resY, 32), "SFML Wykresy", sf::Style::Fullscreen, settings);		// Utworzenie okna programu
		window.setMouseCursorVisible(false);																		// Wylaczenie kursora
		window.setFramerateLimit(120);																				// Czestotliwosc odswiezania
		window.setVerticalSyncEnabled(true);																		// Vertical Sync On

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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) pokaz_kolko = !pokaz_kolko;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) scaleY+=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) scaleY-=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Multiply) scaleX+=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Divide) scaleX-=10;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad8) axisOrigin.y+=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad2) axisOrigin.y-=10; 
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad6) axisOrigin.x+=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad4) axisOrigin.x-=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad8 && event.key.code == sf::Keyboard::LShift) axisOrigin.y += 100.f;			// ???????????????????????
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad2 && event.key.code == sf::Keyboard::LShift) axisOrigin.y -= 100.f;			// ???????????????????????
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad6 && event.key.code == sf::Keyboard::LShift) axisOrigin.x += 100.f;			// ???????????????????????
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad4 && event.key.code == sf::Keyboard::LShift) axisOrigin.x -= 100.f;			// ???????????????????????
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) std::cout << 1;
		}

		window.clear(sf::Color::Black);

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


		sf::VertexArray osX(sf::Lines, 2);																		// Linia osi X
		osX[0].position = sf::Vector2f(margX, axisOrigin.y);													// 
		osX[1].position = sf::Vector2f(float(resX) - margX, axisOrigin.y);										// 

		sf::VertexArray osY(sf::Lines, 2);																		// Linia osi Y
		osY[0].position = sf::Vector2f(axisOrigin.x, margY);													// 
		osY[1].position = sf::Vector2f(axisOrigin.x, float(resY) - margY);										// 

		sf::VertexArray grotX(sf::Triangles, 3);																// Grot osi X
		grotX[0].position = sf::Vector2f(float(resX) - margX, axisOrigin.y);									// 
		grotX[1].position = sf::Vector2f(float(resX) - margX - 20.f, axisOrigin.y - 4.f);						// 
		grotX[2].position = sf::Vector2f(float(resX) - margX - 20.f, axisOrigin.y + 4.f);						// 

		sf::VertexArray grotY(sf::Triangles, 3);																// Grot osi Y
		grotY[0].position = sf::Vector2f(axisOrigin.x, margY);													// 
		grotY[1].position = sf::Vector2f(axisOrigin.x - 4.f, margY + 20.f);										// 
		grotY[2].position = sf::Vector2f(axisOrigin.x + 4.f, margY + 20.f);										// 


		dX = (resX - 2 * margX + scaleX) * uX / (x_max);														//todo Gdzies tu dochodzi do dzielenia przez 0
		int xpmin = int(-axisOrigin.x/dX);																		// ilosc podzialek na minusie
		int xpmax = int((resX - margX - axisOrigin.x) / dX);
		iloscPodzialekX = xpmax - xpmin;

		dY = (resY - 2 * margY + scaleY) * uY / (y_max- y_min); 
		int ypmin = -1 * int((resY - margY - axisOrigin.y )/ (int)dY);											// ilosc podzialek na minusie
		int ypmax = int((axisOrigin.y - margY) / dY);
		iloscPodzialekY = ypmax - ypmin;
	



		// Rysowanie aktualnej klatki ///////////////////////////////////////////////////


		window.draw(osX); window.draw(osY);
		window.draw(grotX); window.draw(grotY);


		sf::VertexArray* podzX = new sf::VertexArray[iloscPodzialekX + 1];
		sf::Text* eX = new sf::Text[iloscPodzialekX + 1];

		for (int i = 0; i <= iloscPodzialekX; i++)
		{
			(podzX + i)->setPrimitiveType(sf::Lines); 
			(podzX + i)->append(sf::Vector2f(axisOrigin.x + (float)xpmin * dX, axisOrigin.y));
			(podzX + i)->append(sf::Vector2f(axisOrigin.x + (float)xpmin * dX, axisOrigin.y + 10.0f));

			(eX + i)->setString(std::to_string(int(xpmin * uX * 180/M_PI)));
			(eX + i)->setFont(czcionka);
			(eX + i)->setCharacterSize(12);
			(eX + i)->setPosition(sf::Vector2f(axisOrigin.x + (float)xpmin * dX, axisOrigin.y + 15.0f));

			window.draw(*(podzX + i));
			window.draw(*(eX + i));
			xpmin++;
		}


		sf::VertexArray* podzY = new sf::VertexArray[iloscPodzialekY + 1];
		sf::Text* eY = new sf::Text[iloscPodzialekY + 1];


			for (int i = 0; i <= iloscPodzialekY; i++)
			{
				(podzY + i)->setPrimitiveType(sf::Lines);
				(podzY + i)->append(sf::Vector2f(axisOrigin.x, axisOrigin.y - ypmax * dY));
				(podzY + i)->append(sf::Vector2f(axisOrigin.x + 10.f, axisOrigin.y - ypmax * dY));
				
				(eX + i)->setString(std::to_string(ypmax));
				(eX + i)->setFont(czcionka);
				(eX + i)->setCharacterSize(12);
				(eX + i)->setPosition(sf::Vector2f(axisOrigin.x + 15, axisOrigin.y - ypmax * dY));

				window.draw(*(podzY + i));
				window.draw(*(eX + i));
				ypmax--;
			}

			int fmax = 20;
		for (int i = 0; i < resX; i++)																			// Rysowanie wykresu punkt po punkcie
		{
			x = 4.f * M_PI * (float(i) - axisOrigin.x) / ((float(resX) - 2* margX) + (float)scaleX);
			y = sin(x);
			
			//y = y = sin((2 * M_PI / ((1 - 1 / fmax) * x + 2 * M_PI / fmax)) * x) * (2 * M_PI / ((1 - 1 / fmax) * x + 2 * M_PI / fmax)) / fmax;				// Formula do wyswietlenia

			(xy + i) -> setRadius(1);
			(xy + i) -> setFillColor(sf::Color::Red);
			(xy + i) -> setPosition(sf::Vector2f((float)i, -dY * y + axisOrigin.y));
			window.draw(*(xy + i));
		}

		window.display();

		std::cout << "Przeciecie ukladu wspolrzednych" << "\t\t" << '\n';
		std::cout << "x: " << axisOrigin.x << "\ty: " << axisOrigin.y << '\n';
		std::cout << "Skala X: " << scaleX << ", Skala Y: " << scaleY << '\n';

		delete[] podzX;
		delete[] podzY;
		delete[] eX;
		delete[] eY;
	}

	return 0;
}