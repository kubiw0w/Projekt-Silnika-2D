#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class BitmapHandler
{
public:
    BitmapHandler();
    Texture stworzTeksture(int szerokosc, int wysokosc);
    void zapiszTekstureDoPliku(const Texture& tekstura, const string& nazwaPliku);
    Texture wczytajTeksture(const string& nazwaPliku);
    void kopiujTeksture(Texture& teksturaDocelowa, const Texture& teksturaZrodlowa);
    void usunTeksture(Texture& tekstura);
};

