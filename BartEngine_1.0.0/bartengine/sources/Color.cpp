#include <Color.h>
#include <string>

const bart::Color& bart::Color::Red = Color(255, 0, 0);
const bart::Color& bart::Color::Green = Color(0, 255, 0);
const bart::Color& bart::Color::Blue = Color(0, 0, 255);
const bart::Color& bart::Color::Black = Color(0, 0, 0);
const bart::Color& bart::Color::White = Color(255, 255, 255);
const bart::Color& bart::Color::DarkRed = Color(128, 0, 0);
const bart::Color& bart::Color::Pink = Color(255, 0, 255);
const bart::Color& bart::Color::Teal = Color(0, 128, 128);
const bart::Color& bart::Color::DarkGreen = Color(0, 128, 0);
const bart::Color& bart::Color::Turquoise = Color(0, 255, 255);
const bart::Color& bart::Color::DarkBlue = Color(0, 0, 128);
const bart::Color& bart::Color::Violet = Color(128, 0, 128);
const bart::Color& bart::Color::Gray = Color(128, 128, 128);
const bart::Color& bart::Color::DarkYellow = Color(128, 128, 0);
const bart::Color& bart::Color::Yellow = Color(255, 255, 0);
const bart::Color& bart::Color::CornflowerBlue = Color(115, 130, 250);
const bart::Color& bart::Color::Orange = Color(255, 128, 0);

bart::Color::Color()
{
    R = G = B = A = 255;
}

bart::Color::Color(const int aRed, const int aGreen, const int aBlue)
{
    R = aRed;
    G = aGreen;
    B = aBlue;
    A = 255;
}

bart::Color::Color(const int aRed, const int aGreen, const int aBlue, const int aAlpha)
{
    R = aRed;
    G = aGreen;
    B = aBlue;
    A = aAlpha;
}

void bart::Color::Set(const int aRed, const int aGreen, const int aBlue, const int aAlpha)
{
    R = aRed;
    G = aGreen;
    B = aBlue;
    A = aAlpha;
}

std::string bart::Color::ToString() const
{
    return std::to_string(R) + ", " + std::to_string(G) + ", " + std::to_string(B) + ", " + std::to_string(A);
}
