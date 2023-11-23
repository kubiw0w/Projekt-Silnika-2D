#include "LineSegment.h"

/** Konstruktor klasy LineSegment.
 * Inicjalizuje obiekt klasy LineSegment punktami poczatkowym i koncowym.
 * @param poczatek Punkt poczatkowy odcinka.
 * @param koniec Punkt koncowy odcinka.
 */
LineSegment::LineSegment(const Point2D& poczatek, const Point2D& koniec) : punktPoczatkowy(poczatek), punktKoncowy(koniec) {}

/** Pobiera punkt poczatkowy odcinka.
 * @return Punkt poczatkowy odcinka.
 */
Point2D LineSegment::pobierzPoczatek() const
{
	return punktPoczatkowy;
}

/** Pobiera punkt koncowy odcinka.
 * @return Punkt koncowy odcinka.
 */
Point2D LineSegment::pobierzKoniec() const
{
	return punktKoncowy;
}

/** Ustawia nowy punkt poczatkowy odcinka.
 * @param poczatek Nowy punkt poczatkowy odcinka.
 */
void LineSegment::ustawPoczatek(const Point2D& poczatek)
{
	punktPoczatkowy = poczatek;
}

/** Ustawia nowy punkt koncowy odcinka.
 * @param koniec Nowy punkt koncowy odcinka.
 */
void LineSegment::ustawKoniec(const Point2D& koniec)
{
	punktKoncowy = koniec;
}

/** Rysuje odcinek na podstawie punktow poczatkowego i koncowego.
 * Wykorzystuje obiekt renderer do narysowania odcinka w okreslonym kolorze.
 * @param renderer Obiekt PrimitiveRenderer do rysowania.
 * @param kolor Kolor odcinka.
 */
void LineSegment::rysowanieLinii(PrimitiveRenderer& renderer, const Color& kolor)
{
	Vector2f poczatek = punktPoczatkowy.pobierzPozycje();
	Vector2f koniec = punktKoncowy.pobierzPozycje();

	renderer.rysujOdcinek(poczatek, koniec, kolor);
}