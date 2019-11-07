#ifndef BART_COLOR_H
#define BART_COLOR_H

#include <string>

namespace bart
{
    struct Color
    {
        Color();
        Color(int aRed, int aGreen, int aBlue);
        Color(int aRed, int aGreen, int aBlue, int aAlpha);
        void Set(int aRed, int aGreen, int aBlue, int aAlpha);
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

        unsigned R{255};
        unsigned G{255};
        unsigned B{255};
        unsigned A{255};
    };
}
#endif
