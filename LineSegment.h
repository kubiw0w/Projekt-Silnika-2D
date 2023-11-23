#pragma once
#include <SFML/Graphics.hpp>
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include <iostream>

using namespace std;
using namespace sf;

class LineSegment
{
public:
	LineSegment(const Point2D& poczatek, const Point2D& koniec);
	Point2D pobierzPoczatek() const;
	Point2D pobierzKoniec() const;
	void ustawPoczatek(const Point2D& poczatek);
	void ustawKoniec(const Point2D& end);
	void rysowanieLinii(PrimitiveRenderer& renderer, const Color& kolor);
private:
	Point2D punktPoczatkowy;
	Point2D punktKoncowy;
};

