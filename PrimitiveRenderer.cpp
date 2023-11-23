#include "PrimitiveRenderer.h"
#include "Point2D.h"

/** Konstruktor klasy PrimitiveRenderer.
 * Inicjalizuje obiekt PrimitiveRenderer dla okna przekazanego jako argument.
 * Ustawia domyslny kolor wypelnienia kwadratu i kola na bialy.
 */
PrimitiveRenderer::PrimitiveRenderer(RenderWindow& window) : window(window)
{
    kwadrat.setFillColor(Color::White);
    kolo.setFillColor(Color::White);
}

/** Rysuje kwadrat o okreslonej pozycji, rozmiarze i kolorze.
 * @param pozycja Pozycja kwadratu.
 * @param rozmiar Rozmiar kwadratu.
 * @param kolor Kolor kwadratu.
 */
void PrimitiveRenderer::rysujKwadrat(const Vector2f& pozycja, const Vector2f& rozmiar, const Color& kolor)
{
    kwadrat.setPosition(pozycja);
    kwadrat.setSize(rozmiar);
    kwadrat.setFillColor(kolor);
    window.draw(kwadrat);
}

/** Rysuje kolo o okreslonym srodku, promieniu, grubosci obramowania i kolorach.
 * @param srodek srodek kola.
 * @param promien Promien kola.
 * @param obramowka Grubosc obramowania kola.
 * @param kolorObramowki Kolor obramowania kola.
 * @param kolorWypelnienia Kolor wypelnienia kola.
 */
void PrimitiveRenderer::rysujKolo(const Vector2f& srodek, float promien, float obramowka, const Color& kolorObramowki, const Color& kolorWypelnienia)
{
    kolo.setPosition(srodek);
    kolo.setRadius(promien);
    kolo.setOutlineThickness(obramowka);
    kolo.setOutlineColor(kolorObramowki);
    kolo.setFillColor(kolorWypelnienia);
    window.draw(kolo);
}

/** Rysuje odcinek miedzy dwoma punktami o okreslonym kolorze.
 * @param punkt1 Pierwszy punkt odcinka.
 * @param punkt2 Drugi punkt odcinka.
 * @param kolor Kolor odcinka.
 */
void PrimitiveRenderer::rysujOdcinek(const Vector2f& punkt1, const Vector2f& punkt2, const Color& kolor)
{
    int x1 = static_cast<int>(punkt1.x);
    int x2 = static_cast<int>(punkt2.x);
    int y1 = static_cast<int>(punkt1.y);
    int y2 = static_cast<int>(punkt2.y);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int kierunekX;
    int kierunekY;

    if (x1 < x2) kierunekX = 1;
    else kierunekX = -1;

    if (y1 < y2) kierunekY = 1;
    else kierunekY = -1;

    int err = dx - dy;

    while (x1 != x2 || y1 != y2)
    {
        if (x1 >= 0 && x1 < window.getSize().x && y1 >= 0 && y1 < window.getSize().y)
        {
            RectangleShape punkt(Vector2f(1, 1));
            punkt.setPosition(Vector2f(x1, y1));
            punkt.setFillColor(kolor);
            window.draw(punkt);
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += kierunekX;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += kierunekY;
        }
    }
}

/** Rysuje punkt o okreslonej pozycji i kolorze.
 * @param punkt Pozycja punktu.
 * @param kolor Kolor punktu.
 */
void PrimitiveRenderer::rysujPunkt(const Vector2f& punkt, const Color& kolor)
{
    pixel.setSize(Vector2f(10, 10));
    pixel.setPosition(punkt);
    pixel.setFillColor(kolor);
    window.draw(pixel);
}

/** Rysuje linie lamana skladajaca sie z podanych punktow i okreslonego koloru.
 * @param punkty Wektor punktow tworzacych linie lamana.
 * @param kolor Kolor lini lamanej.
 */
void PrimitiveRenderer::rysujLinieLamana(const std::vector<Vector2f>& punkty, const Color& kolor)
{
    if (punkty.size() < 2)
        return;

    for (size_t i = 0; i < punkty.size() - 1; i++)
    {
        rysujOdcinek(punkty[i], punkty[i + 1], kolor);
    }
}

/** Rysuje zamknieta linie lamana skladajaca sie z podanych punktow i okreslonego koloru.
 * @param punkty Wektor punktow tworzacych zamknieta linie lamana.
 * @param kolor Kolor zamknietej linii lamanej.
 */
void PrimitiveRenderer::rysujLinieLamanaZamknieta(const std::vector<Vector2f>& punkty, const Color& kolor)
{
    if (punkty.size() < 2)
        return;

    for (size_t i = 0; i < punkty.size() - 1; i++)
    {
        rysujOdcinek(punkty[i], punkty[i + 1], kolor);
    }

    rysujOdcinek(punkty.back(), punkty.front(), kolor);
}

/** Rysuje okrag algorytmicznie na podstawie srodka, promienia i koloru.
 * @param srodek srodek okregu.
 * @param promien Promien okregu.
 * @param kolor Kolor okregu.
 */
void PrimitiveRenderer::rysujOkragAlgorytmicznie(const Vector2f& srodek, float promien, const Color& kolor)
{
    int x = static_cast<int>(srodek.x);
    int y = static_cast<int>(srodek.y);
    int r = static_cast<int>(promien);

    int x0 = 0;
    int y0 = r;
    int d = 3 - 2 * r;

    while (x0 <= y0)
    {
        rysujPunkt(Vector2f(x + x0, y + y0), kolor);
        rysujPunkt(Vector2f(x - x0, y + y0), kolor);
        rysujPunkt(Vector2f(x + x0, y - y0), kolor);
        rysujPunkt(Vector2f(x - x0, y - y0), kolor);
        rysujPunkt(Vector2f(x + y0, y + x0), kolor);
        rysujPunkt(Vector2f(x - y0, y + x0), kolor);
        rysujPunkt(Vector2f(x + y0, y - x0), kolor);
        rysujPunkt(Vector2f(x - y0, y - x0), kolor);

        if (d < 0)
        {
            d += 4 * x0 + 6;
        }
        else
        {
            d += 4 * (x0 - y0) + 10;
            y0--;
        }
        x0++;
    }
}

/** Rysuje elipse algorytmicznie na podstawie srodka, promieniaX, promieniaY i koloru.
 * @param srodek srodek elipsy.
 * @param promienX Promien w kierunku osi X.
 * @param promienY Promien w kierunku osi Y.
 * @param kolor Kolor elipsy.
 */
void PrimitiveRenderer::rysujElipseAlgorytmicznie(const sf::Vector2f& srodek, float promienX, float promienY, const sf::Color& kolor)
{
    int x = static_cast<int>(srodek.x);
    int y = static_cast<int>(srodek.y);
    int rX = static_cast<int>(promienX);
    int rY = static_cast<int>(promienY);

    float a2 = rX * rX;
    float b2 = rY * rY;

    float d = b2 + a2 * (0.25 - rY);
    float x0 = 0;
    float y0 = rY;

    while (b2 * (x0 + 1) < a2 * (y0 - 0.5))
    {
        rysujPunkt(sf::Vector2f(x + x0, y + y0), kolor);
        rysujPunkt(sf::Vector2f(x - x0, y + y0), kolor);
        rysujPunkt(sf::Vector2f(x + x0, y - y0), kolor);
        rysujPunkt(sf::Vector2f(x - x0, y - y0), kolor);

        if (d < 0)
        {
            d += b2 * (2 * x0 + 3);
        }
        else
        {
            d += b2 * (2 * x0 + 3) + a2 * (-2 * y0 + 2);
            y0--;
        }
        x0++;
    }

    d = b2 * (x0 + 0.5) * (x0 + 0.5) + a2 * (y0 - 1) * (y0 - 1) - a2 * b2;

    while (y0 >= 0)
    {
        rysujPunkt(sf::Vector2f(x + x0, y + y0), kolor);
        rysujPunkt(sf::Vector2f(x - x0, y + y0), kolor);
        rysujPunkt(sf::Vector2f(x + x0, y - y0), kolor);
        rysujPunkt(sf::Vector2f(x - x0, y - y0), kolor);

        if (d < 0)
        {
            d += b2 * (2 * x0 + 2) + a2 * (-2 * y0 + 3);
            x0++;
        }
        else
        {
            d += a2 * (-2 * y0 + 3);
        }
        y0--;
    }
}

/** Sprawdza czy dwa odcinki miedzy punktami przecinaja sie.
 * @param punkt1 Poczatkowy punkt pierwszego odcinka.
 * @param punkt2 Koncowy punkt pierwszego odcinka.
 * @param punkt3 Poczatkowy punkt drugiego odcinka.
 * @param punkt4 Koncowy punkt drugiego odcinka.
 * @return True jesli odcinki sie przecinaja, w przeciwnym razie False.
 */
bool IloczynWektorowy(const Vector2f& punkt1, const Vector2f& punkt2, const Vector2f& punkt3, const Vector2f& punkt4)
{
    float dx1 = punkt2.x - punkt1.x;
    float dy1 = punkt2.y - punkt1.y;
    float dx2 = punkt4.x - punkt3.x;
    float dy2 = punkt4.y - punkt3.y;

    float iloczyn_wektorowy = dx1 * dy2 - dx2 * dy1;

    if (iloczyn_wektorowy == 0)
    {
        return false;
    }

    // parametry ktore okreœlaj¹ punkty przeciêcia miêdzy dwoma odcinkami
    float parametr1 = ((punkt3.x - punkt1.x) * dy2 - (punkt3.y - punkt1.y) * dx2) / iloczyn_wektorowy;
    float parametr2 = ((punkt1.x - punkt3.x) * dy1 - (punkt1.y - punkt3.y) * dx1) / (-iloczyn_wektorowy);

    return (parametr1 >= 0 && parametr1 <= 1 && parametr2 >= 0 && parametr2 <= 1);
}

/** Sprawdza czy wielokat o podanych wierzcholkach ma przecinajace sie odcinki.
 * @param wielokat Wektor wierzcholkow wielokata.
 * @return True jesli odcinki sie przecinaja, w przeciwnym razie False.
 */
bool czySiePrzecinaja(const vector<Vector2f>& wielokat)
{
    size_t liczbaWierzcholkow = wielokat.size();

    for (size_t i = 0; i < liczbaWierzcholkow; ++i)
    {
        const Vector2f& p1 = wielokat[i];
        const Vector2f& p2 = wielokat[(i + 1) % liczbaWierzcholkow];

        for (size_t j = i + 2; j < liczbaWierzcholkow; ++j)
        {
            const Vector2f& q1 = wielokat[j];
            const Vector2f& q2 = wielokat[(j + 1) % liczbaWierzcholkow];

            if (i == 0 && j == liczbaWierzcholkow - 1)
            {
                continue;
            }

            if (IloczynWektorowy(p1, p2, q1, q2))
            {
                return true;
            }
        }
    }

    return false;
}

/** Rysuje wielokat o podanych wierzcholkach i kolorze.
 * @param punkty Wektor wierzcholkow wielokata.
 * @param kolor Kolor wielokata.
 */
void PrimitiveRenderer::rysujWielokat(const std::vector<sf::Vector2f>& punkty, const sf::Color& kolor)
{
    if (punkty.size() < 3)
    {
        return;
    }

    if (czySiePrzecinaja(punkty))
    {
        return;
    }

    for (size_t i = 0; i < punkty.size() - 1; i++)
    {
        rysujOdcinek(punkty[i], punkty[i + 1], kolor);
    }
    rysujOdcinek(punkty.back(), punkty.front(), kolor);
}

/** Wypelnia wewnetrzna przestrzen wielokata o podanych wierzcholkach na obrazie.
 * @param obraz Referencja do obiektu sf::Image, na ktorym ma byc wykonane wypelnienie.
 * @param x Wspolrzedna x punktu startowego wypelniania.
 * @param y Wspolrzedna y punktu startowego wypelniania.
 * @param kolorObramowania Kolor obramowania wielokata.
 * @param kolorWypelnienia Kolor wypelnienia wielokata.
 */
void PrimitiveRenderer::borderFill(Image& obraz, int x, int y, Color kolorObramowania, Color kolorWypelnienia)
{
    if (obraz.getPixel(x, y) != kolorObramowania && obraz.getPixel(x, y) != kolorWypelnienia)
    {
        obraz.setPixel(x, y, kolorWypelnienia);
        borderFill(obraz, x + 1, y, kolorObramowania, kolorWypelnienia);
        borderFill(obraz, x - 1, y, kolorObramowania, kolorWypelnienia);
        borderFill(obraz, x, y + 1, kolorObramowania, kolorWypelnienia);
        borderFill(obraz, x, y - 1, kolorObramowania, kolorWypelnienia);
    }
}

/** Rysuje kwadrat z obramowaniem i wypelnieniem na ekranie.
 * @param window Referencja do obiektu sf::RenderWindow.
 * @param pozycja Pozycja kwadratu.
 * @param dlugoscBoku Dlugosc boku kwadratu.
 * @param kolorObramowania Kolor obramowania kwadratu.
 * @param kolorWypelnienia Kolor wypelnienia kwadratu.
 * @param gruboscObramowania Grubosc obramowania kwadratu.
 */
void PrimitiveRenderer::rysowanieKwadratuBorderFill(RenderWindow& window, sf::Vector2f pozycja, float dlugoscBoku, sf::Color kolorObramowania, sf::Color kolorWypelnienia, float gruboscObramowania)
{
    // Tworzenie prostok¹ta reprezentuj¹cego kwadrat
    sf::RectangleShape kwadrat(sf::Vector2f(dlugoscBoku, dlugoscBoku));
    kwadrat.setPosition(pozycja);
    kwadrat.setFillColor(kolorWypelnienia);
    kwadrat.setOutlineColor(kolorObramowania);
    kwadrat.setOutlineThickness(gruboscObramowania); // Gruboœæ obramowania

    // Rysowanie wype³nionego kwadratu z obramowaniem
    window.draw(kwadrat);

    // Pobieranie pozycji wierzcho³ków kwadratu
    sf::Vector2f lewoGora = pozycja;
    sf::Vector2f prawoGora = pozycja + sf::Vector2f(dlugoscBoku, 0);
    sf::Vector2f prawoDol = pozycja + sf::Vector2f(dlugoscBoku, dlugoscBoku);
    sf::Vector2f lewoDol = pozycja + sf::Vector2f(0, dlugoscBoku);

    // Ustalanie obszaru wewn¹trz kwadratu do wype³nienia
    int startX = static_cast<int>(min({ lewoGora.x, prawoGora.x, prawoDol.x, lewoDol.x }));
    int endX = static_cast<int>(max({ lewoGora.x, prawoGora.x, prawoDol.x, lewoDol.x }));
    int startY = static_cast<int>(min({ lewoGora.y, prawoGora.y, prawoDol.y, lewoDol.y }));
    int endY = static_cast<int>(max({ lewoGora.y, prawoGora.y, prawoDol.y, lewoDol.y }));

    // Tworzenie obrazu tylko dla obszaru wewn¹trz kwadratu
    sf::Image image;
    image.create(endX - startX, endY - startY, kolorObramowania);

    // Wywo³anie algorytmu borderfill na ograniczonym obszarze
    borderFill(image, 0, 0, kolorObramowania, kolorWypelnienia);
}
