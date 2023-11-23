#include "Point2D.h"

/** Konstruktor klasy Point2D.
 * Inicjalizuje obiekt klasy Point2D wspolrzednymi x i y.
 * @param x Wartosc wspolrzednej x.
 * @param y Wartosc wspolrzednej y.
 */
Point2D::Point2D(float x, float y) : pozycja(x, y) {}

/** Pobiera pozycje punktu.
 * @return Wektor reprezentujacy pozycje punktu.
 */
Vector2f Point2D::pobierzPozycje() const
{
	return pozycja;
}

/** Ustawia nowa pozycje punktu.
 * @param x Nowa wartosc wspolrzednej x.
 * @param y Nowa wartosc wspolrzednej y.
 */
void Point2D::ustawPozycje(float x, float y)
{
	pozycja.x = x;
	pozycja.y = y;
}

/** Rysuje punkt na ekranie w okreslonym kolorze.
 * Wykorzystuje obiekt renderer do narysowania punktu w okreslonym kolorze.
 * @param renderer Obiekt PrimitiveRenderer do rysowania.
 * @param color Kolor punktu.
 */
void Point2D::rysujPunkt(PrimitiveRenderer& renderer, const Color& kolor)
{
	renderer.rysujPunkt(pozycja, kolor);
}
