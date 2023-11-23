#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Point2D.h"

using namespace std;
using namespace sf;

class Collisions
{
public:
	static bool czyKolizja(const Sprite& graczSprite, const Vector2f& rozmiar1, const Vector2f& pozycjaKwadratu, const Vector2f& rozmiar2);
	static bool czyKolizjaPunktow(const Sprite& graczSprite, const vector<Point2D>& punkty, float odlegloscKolizji);
};

