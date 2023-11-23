#include "BitmapHandler.h"

/** Konstruktor klasy BitmapHandler.
 * Inicjalizuje obiekt BitmapHandler.
 */
BitmapHandler::BitmapHandler() {}

/** Tworzy teksture o okreslonych wymiarach.
 * @param szerokosc Szerokosc tekstury.
 * @param wysokosc Wysokosc tekstury.
 * @return Zwraca teksture utworzona na podstawie RenderTexture.
 */
Texture BitmapHandler::stworzTeksture(int szerokosc, int wysokosc)
{
    RenderTexture renderTexture;
    renderTexture.create(szerokosc, wysokosc);
    return renderTexture.getTexture();
}

/** Zapisuje teksture do pliku.
 * @param tekstura Referencja do tekstury do zapisu.
 * @param nazwaPliku Nazwa pliku, do ktorego ma byc zapisana tekstura.
 */
void BitmapHandler::zapiszTekstureDoPliku(const Texture& tekstura, const string& nazwaPliku)
{
    Image image = tekstura.copyToImage();
    if (!image.saveToFile(nazwaPliku))
    {
        cout << "Blad zapisywania tekstury do pliku!" << endl;
    }
}

/** Laduje teksture z pliku.
 * @param filename Nazwa pliku, z ktorego ma byc wczytana tekstura.
 * @return Zwraca wczytana teksture.
 */
Texture BitmapHandler::wczytajTeksture(const string& nazwaPliku)
{
    Texture texture;
    if (!texture.loadFromFile(nazwaPliku))
    {
        cout << "Blad wczytywania tekstury z pliku!" << endl;
    }
    return texture;
}

/** Kopiuje zawartosc tekstury zrodlowej do tekstury docelowej.
 * @param teksturaDocelowa Referencja do tekstury docelowej.
 * @param teksturaZrodlowa Referencja do tekstury zrodlowej.
 */
void BitmapHandler::kopiujTeksture(Texture& teksturaDocelowa, const Texture& teksturaZrodlowa)
{
    teksturaDocelowa = teksturaZrodlowa;
}

/** Usuwa zawartosc tekstury.
 * @param texture Referencja do tekstury do usuniecia.
 */
void BitmapHandler::usunTeksture(Texture& tekstura)
{
    Image pusteZdjecie;
    tekstura.update(pusteZdjecie);
}