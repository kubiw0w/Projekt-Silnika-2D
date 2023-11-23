#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class PrimitiveRenderer
{
public:
	PrimitiveRenderer(RenderWindow& window);
	void rysujKwadrat(const Vector2f& pozycja, const Vector2f& rozmiar, const Color& kolor);
	void rysujKolo(const Vector2f& srodek, float promien, float obramowka, const Color& kolorObramowki, const Color& kolorWypelnienia);
	void rysujOdcinek(const Vector2f& punkt1, const Vector2f& punkt2, const Color& kolor);
	void rysujPunkt(const Vector2f& punkt, const Color& kolor);
	void rysujLinieLamana(const vector<Vector2f>& punkty, const Color& kolor);
	void rysujLinieLamanaZamknieta(const vector<Vector2f>& punkty, const Color& kolor);
	void rysujOkragAlgorytmicznie(const Vector2f& srodek, float promien, const Color& kolor);
	void rysujElipseAlgorytmicznie(const sf::Vector2f& srodek, float promienX, float promienY, const sf::Color& kolor);
	void rysujWielokat(const std::vector<sf::Vector2f>& punkty, const sf::Color& kolor);
	void borderFill(Image& obraz, int x, int y, Color kolorObramowania, Color kolorWypelnienia);
	void rysowanieKwadratuBorderFill(RenderWindow& window, sf::Vector2f pozycja, float dlugoscBoku, sf::Color kolorObramowania, sf::Color kolorWypelnienia, float gruboscObramowania);
private:
	RenderWindow& window;
	RectangleShape kwadrat;
	RectangleShape pixel;
	CircleShape kolo;
};

