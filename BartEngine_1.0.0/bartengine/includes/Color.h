#ifndef BART_COLOR_H
#define BART_COLOR_H

#include <string>

namespace bart
{
    struct Color
    {
        Color();
        Color(unsigned char aRed, unsigned char aGreen, unsigned char aBlue);
        Color(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha);
        void Set(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha);
        std::string ToString() const;

        static const Color& Red;
        static const Color& Green;
        static const Color& Blue;
        static const Color& White;
        static const Color& Black;
        static const Color& DarkRed;
        static const Color& Pink;
        static const Color& Teal;
        static const Color& DarkGreen;
        static const Color& Turquoise;
        static const Color& DarkBlue;
        static const Color& Violet;
        static const Color& Gray;
        static const Color& DarkYellow;
        static const Color& Yellow;
        static const Color& CornflowerBlue;
        static const Color& Orange;

        unsigned char R{255};
        unsigned char G{255};
        unsigned char B{255};
        unsigned char A{255};
    };
}
#endif
