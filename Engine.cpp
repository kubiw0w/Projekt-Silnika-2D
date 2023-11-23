#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include "BitmapHandler.h"
#include "Collisions.h"
#include "Transformations2D.h"

Vector2f rozmiarKwadratu(50.0f, 50.0f);
Vector2f pozycjaKola(1400.0f, 600.0f);
Color kolorKwadratu = Color::Green;
vector<Vector2f> pozycjeKwadratow;
vector<Point2D> punkty;

IntRect pozycja(0, 0, 83, 100);
IntRect animacjaBiegania[] = {
    IntRect(0, 0, 83, 100),
    IntRect(100, 0, 90, 100),
    IntRect(213, 0, 79, 100),
    IntRect(314, 0, 83, 100),
    IntRect(408, 0, 86, 100)
};

// ZMIENNE DO KWADRATU BORDERFILL
Color kolorObramowania = Color::Black;
Color kolorWypelnienia = Color::Yellow;
float gruboscObramowania = 2.0f;
Vector2f pozycjaKwadratu(1500.0f, 0.0f);
float dlugoscBoku = 100.0f;

Engine::Engine() {
    window.create(VideoMode(1600, 900), "Silnik 2D");
    window.setFramerateLimit(240);
}

/** Zlicza ilosc klatek na sekunde (FPS) i aktualizuje tekst na ekranie z wynikiem.
 */
void Engine::obliczFPS() {
    klatki++;
    if (zegarFPS.getElapsedTime().asSeconds() >= 1.0f) {
        float fps = static_cast<float>(klatki) / zegarFPS.restart().asSeconds();
        tekstFPS.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        klatki = 0;
    }
}

/** Wczytuje czcionke, ustawia jej w³asciwosci i pozycje tekstu na ekranie.
 */
void Engine::wczytajCzcionke() {
    czcionka.loadFromFile("Fonts/ALGER.TTF");
    tekstFPS.setFont(czcionka);
    tekstFPS.setCharacterSize(30);
    tekstFPS.setFillColor(Color::Black);
    tekstFPS.setPosition(10, 10);
    tekstPunkty.setFont(czcionka);
    tekstPunkty.setCharacterSize(100);
    tekstPunkty.setFillColor(Color::Black);
    tekstPunkty.setPosition(700, 30);
    tekstPunkty.setString(to_string(0));
}

/** Mierzy czas dzialania silnika i wyswietla go na konsoli.
 * @param timer Zegar mierzacy czas dzialania silnika.
 */
void Engine::pomiarCzasuDzialania(Clock& timer) {
    Time elapsed = timer.getElapsedTime();
    float czas = elapsed.asSeconds();
    cout << "Czas dzialania silnika: " << czas << " sekund" << endl;
}

/** Generuje losowo pozycje dla 10 kwadratow, sprawdzajac jednoczesnie ich odleg³osc od siebie.
 *  Unika kolizji kwadratow, utrzymujac minimalna odleg³osc.
 */
void Engine::spawnowanieKwadratow()
{
    for (int i = 0; i < 10; ++i)
    {
        float losowyX = static_cast<float>(rand() % 15000 + 1600);
        bool odleglosc = true;
        for (const auto& pos : pozycjeKwadratow)
        {
            if (abs(pos.x - losowyX) < 600.0f)
            {
                odleglosc = false;
                break;
            }
        }

        for (const auto& punkt : punkty)
        {
            if (abs(punkt.pobierzPozycje().x - losowyX) < 500.0f)
            {
                odleglosc = false;
                break;
            }
        }

        if (odleglosc)
        {
            pozycjeKwadratow.push_back(Vector2f(losowyX, 650.0f));
        }
        else
        {
            --i;
        }
    }
}

/** Generuje losowo pozycje dla 10 punktow, sprawdzajac jednoczeœnie ich odleg³osc od siebie i od kwadratow.
 *  Unika kolizji punktow i kwadratow, utrzymujac minimalna odleg³osc.
 */
void Engine::spawnowaniePunktow()
{
    const float minimalnaOdleglosc = 500.0f;
    const float minimalnaOdlegloscKwadrat = minimalnaOdleglosc * minimalnaOdleglosc;
    const float minimalnaOdlegloscKwadratPunkt = 400.0f * 400.0f;

    for (int i = 0; i <= 10; ++i)
    {
        float losowyX = static_cast<float>(rand() % 15000 + 1600);
        bool odleglosc = true;

        for (const auto& punkt : punkty)
        {
            float odlegloscX = punkt.pobierzPozycje().x - losowyX;
            float odlegloscY = punkt.pobierzPozycje().y - 625.0f;

            if ((odlegloscX * odlegloscX + odlegloscY * odlegloscY) < minimalnaOdlegloscKwadratPunkt)
            {
                odleglosc = false;
                break;
            }
        }

        for (const auto& pos : pozycjeKwadratow)
        {
            if (abs(pos.x - losowyX) < 500.0f)
            {
                odleglosc = false;
                break;
            }
        }

        if (odleglosc)
        {
            Point2D nowyPunkt(losowyX, 625.0f);
            punkty.push_back(nowyPunkt);
        }
        else
        {
            --i;
        }
    }
}

/** Funkcja obslugujaca petle glowna gry.
 *
 * Inicjalizuje niezbedne obiekty, takie jak czcionki, generator pseudolosowy,
 * obsluge bitmap, renderowanie prymitywow i transformacje 2D. Dodatkowo wczytuje
 * tekstury dla gracza, tla i sciezki, a takze inicjalizuje obiekty Sprite dla
 * kazdej z tekstur.
 *
 * W petli while monitoruje zdarzenia okna, takie jak zamkniecie, nacisniecie przycisku myszy,
 * czy klawisza klawiatury. W zaleznosci od zdarzen, odpowiednio aktualizuje stan gry, np.
 * rozpoczyna skok lub kucan, oraz rysuje obiekty na ekranie, takie jak tlo, sciezka, gracz,
 * kwadraty i punkty. Ponadto monitoruje kolizje miedzy graczem, kwadratami i punktami.
 *
 * Funkcja zawiera rowniez kod zwiazany z animacja skoku, biegu, kucan oraz aktualizacje
 * pozycji obiektow na planszy. Liczy rowniez punkty za przebyta droge i wyswietla je na ekranie.
 *
 * Po zakonczeniu petli gry zamyka okno i dokonuje pomiaru czasu dzialania gry.
 */

void Engine::PetlaGlowna() {
    wczytajCzcionke();
    srand(time(NULL));

    BitmapHandler handler;
    PrimitiveRenderer renderer(window);
    Transformations2D przeksztalcenie;

    Texture gracz = handler.wczytajTeksture("Textures/piesio.bmp");
    Texture tlo = handler.wczytajTeksture("Textures/tlo.png");
    Texture sciezka = handler.wczytajTeksture("Textures/sciezka.png");

    Sprite graczSprite(gracz);
    Sprite tloSprite(tlo);
    Sprite sciezkaSprite(sciezka);

    graczSprite.setPosition(50, 620);
    graczSprite.setTextureRect(pozycja);

    sciezkaSprite.setPosition(0, 700);

    Color borderColor = Color::Black;
    Color fillColor = Color::Blue;
    float outlineThickness = 2.0f;
    Vector2f position(600.0f, 300.0f);
    float sideLength = 200.0f;

    spawnowanieKwadratow();
    spawnowaniePunktow();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "Przycisk zostal wcisniety." << endl;
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if ((event.key.code == Keyboard::Space || event.key.code == Keyboard::Up) && moznaSkakac)
                {
                    if (!czySkacze)
                    {
                        if (czyKuca)
                        {
                            czyKuca = false;
                        }
                        czySkacze = true;
                        skok.restart();
                        kucanie.restart();
                    }
                }
                else if (event.key.code == Keyboard::Down && moznaKucac)
                {
                    if (!czyKuca)
                    {
                        if (czySkacze)
                        {
                            czySkacze = false;
                        }
                        czyKuca = true;
                        kucanie.restart();
                        skok.restart();
                    }
                }
            }
        }

        obliczFPS();

        if (czyKuca)
        {
            graczSprite.setTextureRect(IntRect(113, 138, 108, 89));
            graczSprite.setPosition(50, 650);
            czySkacze = false;
            if (kucanie.getElapsedTime().asSeconds() > 1.0f)
            {
                czyKuca = false;
                czyBiegnie = true;
                ruchTekstur = true;
                liczPunkty = true;
                graczSprite.setPosition(50, 620);
                klatkaAnimacjiBiegania = 0;
                kucanie.restart();
            }
        }

        if (czySkacze)
        {
            czyKuca = false;
            graczSprite.setTextureRect(IntRect(0, 134, 93, 100));
            float czasSkoku = skok.getElapsedTime().asSeconds();
            float skokY = sin(czasSkoku * 5) * 100.0f;
            graczSprite.setPosition(50, 520 - skokY);
            if (skok.getElapsedTime().asSeconds() > 1.0f)
            {
                czySkacze = false;
                czyBiegnie = true;
                ruchTekstur = true;
                liczPunkty = true;
                klatkaAnimacjiBiegania = 0;
                graczSprite.setTextureRect(animacjaBiegania[klatkaAnimacjiBiegania]);
                skok.restart();
            }
        }
        else if (czyBiegnie && skok.getElapsedTime().asMilliseconds() > 100)
        {
            klatkaAnimacjiBiegania = (klatkaAnimacjiBiegania + 1) % (sizeof(animacjaBiegania) / sizeof(animacjaBiegania[0]));
            graczSprite.setTextureRect(animacjaBiegania[klatkaAnimacjiBiegania]);
            skok.restart();
        }

        if (ruchTekstur)
        {
            tloSprite.move(-predkoscTla, 0);
            sciezkaSprite.move(-predkoscSciezki, 0);
            przeksztalcenie.aktualizujObiekty(pozycjeKwadratow, punkty, predkoscObiektow, pozycjaKola);
        }
        else
        {
            tloSprite.move(0, 0);
            sciezkaSprite.move(0, 0);
        }

        if (liczPunkty)
        {
            liczbaPunktow++;
            tekstPunkty.setString(to_string(liczbaPunktow));

        }

        Vector2f aktualnaPozycjaGracza = graczSprite.getPosition();

        for (const auto& pos : pozycjeKwadratow)
        {
            if (Collisions::czyKolizja(graczSprite, aktualnaPozycjaGracza, pos, rozmiarKwadratu))
            {
                ruchTekstur = false;
                liczPunkty = false;
                czyBiegnie = false;
                moznaSkakac = false;
                moznaKucac = false;
                graczSprite.setTextureRect(IntRect(303, 125, 87, 102));
            }
        }

        for (auto& punkt : punkty)
        {
            if (Collisions::czyKolizjaPunktow(graczSprite, punkty, 20.0f))
            {
                ruchTekstur = false;
                liczPunkty = false;
                czyBiegnie = false;
                moznaSkakac = false;
                moznaKucac = false;
                graczSprite.setTextureRect(IntRect(303, 125, 87, 102));
            }
        }

        window.clear();

        window.draw(tloSprite);
        window.draw(sciezkaSprite);

        window.draw(tekstFPS);
        window.draw(tekstPunkty);
        window.draw(graczSprite);

        for (const auto& pos : pozycjeKwadratow) {
            renderer.rysujKwadrat(pos, rozmiarKwadratu, kolorKwadratu);
        }

        for (const auto& punkt : punkty) {
            renderer.rysujPunkt(punkt.pobierzPozycje(), Color::Red);
        }

        renderer.rysowanieKwadratuBorderFill(window, pozycjaKwadratu, dlugoscBoku, kolorObramowania, kolorWypelnienia, gruboscObramowania);

        window.display();

    }

    window.close();
    pomiarCzasuDzialania(timer);
}