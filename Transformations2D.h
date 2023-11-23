#pragma once
#include <SFML/Graphics.hpp>
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include <iostream>

using namespace std;
using namespace sf;

class Transformations2D
{
public:
	void przesuwanieKwadratow(vector<Vector2f>& pozycjeKwadratow, float predkoscObiektow);
	void przesuwaniePunktow(vector<Point2D>& punkty, float predkoscObiektow);
	void przesuwanieKola(Vector2f& pozycjaKola, float predkoscObiektow);
	void skalujKwadrat(sf::RectangleShape& obiekt, float kx, float ky);
	void skalujKolo(sf::CircleShape& obiekt, float promien);
	void aktualizujObiekty(vector<Vector2f>& pozycjeKwadratow, std::vector<Point2D>& punkty, float predkoscObiektow, Vector2f& pozycjaKola);
};

