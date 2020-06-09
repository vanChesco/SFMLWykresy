#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
	const int resX{ 1920 }, resY{ 1080 };																			// Deklaracja rozdzielczosci
	float margX{ 20 }, margY{ 20 };																					// Marginesy
	float LX = resX - 2 * margX, LY = resY - 2 * margY;																// Docelowa dlugosc osi w pikselach


	const float M_PI = (float)acos(-1);																				// Definicja stalej PI
	float x, y;																										// Zmienne do obliczania wykresu
	int iloscPodzialekX{ 0 }, iloscPodzialekY{ 0 };																	// Liczba podzialek na osi X
	float uX{ 1 * M_PI }, uY{ 1 };																					// Jednostki osi
	float x_max{ 4 * M_PI }, y_max{ 2 };																			// Wartosci max osi
	float x_min{ -1 * M_PI }, y_min{ -2 };																			// Wartosci min osi


	sf::Vector2f axisOrigin{ -x_min * LX / (x_max-x_min) + margX, y_max * LY / (y_max - y_min) + margY };							// Punkt skrzyzowania osi
	float scaleY{ 1 }, scaleX{ 1 };																					// Wspolczynniki skalowania


	bool pokaz_kolko{ false };																						// Przelacznik widocznosci kolka


	sf::Font czcionka;
		czcionka.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	sf::Color kolor_osi(150, 150, 150);
	

	sf::ContextSettings settings;																					// Ustawienie antyaliasingu
		settings.antialiasingLevel = 16;

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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) scaleY*=1.1f;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) scaleY*=0.9f;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Multiply) scaleX*=1.1f;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Divide) scaleX*=0.9f;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad2) axisOrigin.y+=10; 
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad8) axisOrigin.y-=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad6) axisOrigin.x+=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad4) axisOrigin.x-=10;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad8 && event.key.code == sf::Keyboard::LShift) axisOrigin.y += 100.f;			// ???????????????????????
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad2 && event.key.code == sf::Keyboard::LShift) axisOrigin.y -= 100.f;			// ???????????????????????
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad6 && event.key.code == sf::Keyboard::LShift) axisOrigin.x += 100.f;			// ???????????????????????
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad4 && event.key.code == sf::Keyboard::LShift) axisOrigin.x -= 100.f;			// ???????????????????????
		}

		window.clear(sf::Color::Black);

		if (pokaz_kolko) window.draw(kolko);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) kolko.move(20, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) kolko.move(-20, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) kolko.move(0, -20);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) kolko.move(0, 20);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))													//???????????????????????????????
		{																										//???????????????????????????????
			window.draw(kolko);																					//???????????????????????????????
			scaleX += 0.01f * event.mouseWheelScroll.delta;
			scaleY += 0.01f * event.mouseWheelScroll.delta;
		}

		if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			axisOrigin.x += 0.01f * event.mouseMove.x;
			axisOrigin.y += 0.01f * event.mouseMove.y;
		}



		sf::VertexArray osX(sf::Lines, 2);																		// Linia osi X
			osX[0].position = sf::Vector2f(margX, axisOrigin.y);												// 
			osX[1].position = sf::Vector2f(float(resX) - margX, axisOrigin.y);									// 
			osX[0].color = osX[1].color = kolor_osi;

		sf::VertexArray osY(sf::Lines, 2);																		// Linia osi Y
			osY[0].position = sf::Vector2f(axisOrigin.x, margY);												// 
			osY[1].position = sf::Vector2f(axisOrigin.x, float(resY) - margY);									// 
			osY[0].color = osY[1].color = kolor_osi;

		sf::VertexArray grotX(sf::Triangles, 3);																// Grot osi X
			grotX[0].position = sf::Vector2f(float(resX) - margX, axisOrigin.y);								// 
			grotX[1].position = sf::Vector2f(float(resX) - margX - 20.f, axisOrigin.y - 4.f);					// 
			grotX[2].position = sf::Vector2f(float(resX) - margX - 20.f, axisOrigin.y + 4.f);					// 
			grotX[0].color = grotX[1].color = grotX[2].color = kolor_osi;

		sf::VertexArray grotY(sf::Triangles, 3);																// Grot osi Y
			grotY[0].position = sf::Vector2f(axisOrigin.x, margY);												// 
			grotY[1].position = sf::Vector2f(axisOrigin.x - 4.f, margY + 20.f);									// 
			grotY[2].position = sf::Vector2f(axisOrigin.x + 4.f, margY + 20.f);									// 
			grotY[0].color = grotY[1].color = grotY[2].color = kolor_osi;



		// Rysowanie aktualnej klatki ///////////////////////////////////////////////////


		window.draw(osX); window.draw(osY);
		window.draw(grotX); window.draw(grotY);

		float dX = scaleX * LX / ((x_max - x_min) / uX);														// 
		float dY = scaleY * LY / ((y_max - y_min) / uY);														// Dlugosc jednej dzialki

		iloscPodzialekX = int((x_max - x_min) / uX / scaleX);
		if (dX < 100)
		{
			iloscPodzialekX /= 2;
			uX *= 4;
		}

		int count_x = -(int(axisOrigin.x / dX));

		sf::VertexArray* podzX = new sf::VertexArray[iloscPodzialekX + 1];										// Rysowanie podzialek na osi X
		sf::Text* eX = new sf::Text[iloscPodzialekX + 1];														// 

		for (int i = 0; i <= iloscPodzialekX; i++)																// 
		{																										// 
			(podzX + i)->setPrimitiveType(sf::Lines); 															// 
			(podzX + i)->append(sf::Vector2f(axisOrigin.x + count_x * dX, axisOrigin.y));						// 
			(podzX + i)->append(sf::Vector2f(axisOrigin.x + count_x * dX, axisOrigin.y + 10.0f));				// 
			podzX[i][0].color = podzX[i][1].color = kolor_osi;

			(eX + i)->setString(std::to_string(int(count_x * uX * 180 / M_PI)));								// 
			(eX + i)->setFont(czcionka);																		// 
			(eX + i)->setCharacterSize(12);																		// 
			(eX + i)->setPosition(sf::Vector2f(axisOrigin.x + count_x * dX, axisOrigin.y + 15));				// 
			(eX + i)->setFillColor(kolor_osi);

			window.draw(*(podzX + i));																			// 
			window.draw(*(eX + i));																				// 
			count_x++;
		}

		iloscPodzialekY = int(LY/dY);  std::cout << iloscPodzialekY << " | " << scaleY << '\n';
		int count_y = int(axisOrigin.y / dY);

		sf::VertexArray* podzY = new sf::VertexArray[iloscPodzialekY + 1];										// Rysowanie podzialek na osi Y
		sf::Text* eY = new sf::Text[iloscPodzialekY + 1];														// 

		for (int i = 0; i <= iloscPodzialekY; i++)																// 
		{																										// 
			(podzY + i)->setPrimitiveType(sf::Lines);															// 
			(podzY + i)->append(sf::Vector2f(axisOrigin.x, axisOrigin.y - dY * count_y));						// 
			(podzY + i)->append(sf::Vector2f(axisOrigin.x + 10.0f, axisOrigin.y - dY * count_y));				// 
			podzY[i][0].color = podzY[i][1].color = kolor_osi;

			(eY + i)->setString(std::to_string((count_y * uY)));												// 
			(eY + i)->setFont(czcionka);																		// 
			(eY + i)->setCharacterSize(12);																		// 
			(eY + i)->setPosition(sf::Vector2f(axisOrigin.x + 15, axisOrigin.y - dY * count_y));				// 
			(eY + i)->setFillColor(kolor_osi);

			window.draw(*(podzY + i));																			// 
			window.draw(*(eY + i));																				// 
			count_y--;
		}

			int fmax = 20;
		for (int i = 0; i < resX; i++)																			// Rysowanie wykresu punkt po punkcie
		{
			x = (x_max - x_min) * (float(i) - axisOrigin.x) / (scaleX * LX);
			//y = sin(x * sin(2 * x));
			
			y = y = sin((2 * M_PI / ((1 - 1 / fmax) * x + 2 * M_PI / fmax)) * x) * (2 * M_PI / ((1 - 1 / fmax) * x + 2 * M_PI / fmax)) / fmax;				// Formula do wyswietlenia

			(xy + i) -> setRadius(1);
			(xy + i) -> setFillColor(sf::Color::Red);
			(xy + i) -> setPosition(sf::Vector2f((float)i, -dY * y / uY + axisOrigin.y));
			window.draw(*(xy + i));
		}

		window.display();

		std::cout << "Przeciecie ukladu wspolrzednych" << "\t\t" << '\n';
		std::cout << "x: " << axisOrigin.x << "\ty: " << axisOrigin.y << '\n';
		std::cout << "Skala X: " << /*scaleX <<*/ ", Skala Y: " << scaleY << '\n';

		delete[] podzX;
		delete[] podzY;
		delete[] eX;
		delete[] eY;
	}

	return 0;
}