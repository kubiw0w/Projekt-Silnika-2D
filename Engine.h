#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Engine
{
public:
    Engine();
    void PetlaGlowna();
private:
    RenderWindow window;
    Clock zegarFPS;
    Font czcionka;
    Text tekstFPS;
    Text tekstPunkty;
    int liczbaPunktow = 0;
    int klatkaAnimacjiBiegania = 0;
    int klatki = 0;
    float predkoscTla = 0.09f;
    float predkoscSciezki = 2.0f;
    float predkoscObiektow = 2.0f;
    bool czyBiegnie = false;
    bool czySkacze = false;
    bool czyKuca = false;
    bool moznaSkakac = true;
    bool moznaKucac = true;
    bool ruchTekstur = false;
    bool liczPunkty = false;
    Clock timer;
    Clock skok;
    Clock kucanie;
    void wczytajCzcionke();
    void obliczFPS();
    void spawnowanieKwadratow();
    void spawnowaniePunktow();
    void pomiarCzasuDzialania(Clock& timer);
};
