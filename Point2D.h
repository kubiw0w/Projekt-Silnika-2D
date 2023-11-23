#pragma once
#include <SFML/Graphics.hpp>
#include "PrimitiveRenderer.h"
#include <iostream>

using namespace std;
using namespace sf;

class Point2D
{
public:
	Point2D(float x, float y);
	Vector2f pobierzPozycje() const;
	void ustawPozycje(float x, float y);
	void rysujPunkt(PrimitiveRenderer& renderer, const Color& kolor);
private:
	Vector2f pozycja;
};

