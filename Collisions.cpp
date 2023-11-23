#include "Collisions.h"

/** Sprawdza, czy wystepuje kolizja miedzy prostokatem reprezentujacym gracza (Sprite) a kwadratem o okreslonych wymiarach
 *  i pozycji.
 * @param graczSprite Sprite reprezentujacy gracza.
 * @param rozmiar1 Wymiary prostokata reprezentujacego gracza.
 * @param pozycjaKwadratu Pozycja kwadratu, z ktorym sprawdzana jest kolizja.
 * @param rozmiar2 Wymiary kwadratu, z ktorym sprawdzana jest kolizja.
 * @return Zwraca true, jesli wystepuje kolizja, w przeciwnym razie false.
 */
bool Collisions::czyKolizja(const Sprite& graczSprite, const Vector2f& rozmiar1, const Vector2f& pozycjaKwadratu, const Vector2f& rozmiar2)
{
    FloatRect granice1 = graczSprite.getGlobalBounds();
    FloatRect granice2(pozycjaKwadratu.x, pozycjaKwadratu.y, rozmiar2.x, rozmiar2.y);
    return granice1.intersects(granice2);
}

/** Sprawdza, czy wystepuje kolizja miedzy prostokatem reprezentujacym gracza (Sprite) a zestawem punktow o okreslonej odleglosci.
 * @param graczSprite Sprite reprezentujacy gracza.
 * @param punkty Wektor zawierajacy punkty, z ktorymi sprawdzana jest kolizja.
 * @param odlegloscKolizji Odleglosc, w jakiej wystepuje kolizja.
 * @return Zwraca true, jesli wystepuje kolizja, w przeciwnym razie false.
 */
bool Collisions::czyKolizjaPunktow(const Sprite& graczSprite, const vector<Point2D>& punkty, float odlegloscKolizji)
{
    FloatRect graniceGracza = graczSprite.getGlobalBounds();

    for (const auto& punkt : punkty)
    {
        Vector2f pozycjaPunktu = punkt.pobierzPozycje();
        FloatRect granicePunktu(pozycjaPunktu.x, pozycjaPunktu.y, 10.0f, 10.0f);

        if (graniceGracza.intersects(granicePunktu))
        {
            return true;
        }
    }
    return false;
}
