#include "Transformations2D.h"

/** Przesuwa pozycje kwadratow o zadana wartosc predkozci w kierunku przeciwnym do osi X.
 * @param pozycjeKwadratow Wektor pozycji kwadratow do przesuniecia.
 * @param predkoscObiektow Wartosc predkosci przesuniecia.
 */
void Transformations2D::przesuwanieKwadratow(vector<Vector2f>& pozycjeKwadratow, float predkoscObiektow)
{
    for (auto& pos : pozycjeKwadratow)
    {
        pos.x -= predkoscObiektow;
    }
}

/** Przesuwa pozycje punktow 2D o zadana wartosc predkosci w kierunku przeciwnym do osi X.
 * @param punkty Wektor punktow 2D do przesuniecia.
 * @param predkoscObiektow Wartosc predkosci przesuniecia.
 */
void Transformations2D::przesuwaniePunktow(vector<Point2D>& punkty, float predkoscObiektow)
{
    for (auto& punkt : punkty)
    {
        float obecneX = punkt.pobierzPozycje().x;
        float obecneY = punkt.pobierzPozycje().y;
        punkt.ustawPozycje(obecneX - predkoscObiektow, obecneY);
    }
}

/** Przesuwa pozycje kola o zadana wartosc predkosci w kierunku przeciwnym do osi X.
 * @param pozycjaKola Pozycja kola do przesuniecia.
 * @param predkoscObiektow Wartosc predkosci przesuniecia.
 */
void Transformations2D::przesuwanieKola(Vector2f& pozycjaKola, float predkoscObiektow)
{
    pozycjaKola.x -= predkoscObiektow;
}

/** Skaluje rozmiar kwadratu o podane wspolczynniki kx i ky.
 * @param obiekt Referencja do obiektu sf::RectangleShape do przeskalowania.
 * @param kx Wspolczynnik skalowania w kierunku osi X.
 * @param ky Wspolczynnik skalowania w kierunku osi Y.
 */
void Transformations2D::skalujKwadrat(sf::RectangleShape& obiekt, float kx, float ky) {
    sf::Vector2f rozmiar = obiekt.getSize();
    rozmiar.x *= kx;
    rozmiar.y *= ky;
    obiekt.setSize(rozmiar);
}

/** Skaluje rozmiar kola o podany wspolczynnik k.
 * @param obiekt Referencja do obiektu sf::CircleShape do przeskalowania.
 * @param k Wspolczynnik skalowania.
 */
void Transformations2D::skalujKolo(sf::CircleShape& obiekt, float k) {
    float promien = obiekt.getRadius();
    promien *= k;
    obiekt.setRadius(promien);
}

/** Aktualizuje obiekty wykonujac operacje przesuniecia na kwadratach, punktach i kole.
 * @param pozycjeKwadratow Wektor pozycji kwadratpw do aktualizacji.
 * @param punkty Wektor punktow 2D do aktualizacji.
 * @param predkoscObiektow Wartosc predkosci przesuniecia.
 * @param pozycjaKola Pozycja kola do aktualizacji.
 */
void Transformations2D::aktualizujObiekty(vector<Vector2f>& pozycjeKwadratow, std::vector<Point2D>& punkty, float predkoscObiektow, Vector2f& pozycjaKola)
{
    przesuwanieKwadratow(pozycjeKwadratow, predkoscObiektow);
    przesuwaniePunktow(punkty, predkoscObiektow);
    przesuwanieKola(pozycjaKola, predkoscObiektow);
}
