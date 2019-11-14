#ifndef BART_STRING_HELPER_H
#define BART_STRING_HELPER_H

#include <string>
#include <sstream>

namespace bart
{
    class StringHelper
    {
    public:

        static std::string GetPath(const std::string& aFilename)
        {
            const size_t tIdx = aFilename.find_last_of("/\\");
            if (tIdx > 0)
            {
                return aFilename.substr(0, tIdx + 1);
            }

            return "";
        }

        static void GetColorComponents(const std::string& aColor,
                                       unsigned char* aR,
                                       unsigned char* aG,
                                       unsigned char* aB,
                                       unsigned char* aA)
        {
            if (aColor.empty())
            {
                *aR = 0;
                *aG = 0;
                *aB = 0;
                *aA = 255;
            }
            else
            {
                std::string tColor = aColor.substr(1);
                const size_t tColorLen = tColor.size();

                int tIdx = 0;

                int tR, tG, tB, tA;

                std::stringstream tStringStream;

                if (tColorLen == 8)
                {
                    tStringStream << std::hex << tColor.substr(tIdx, 2);
                    tStringStream >> tA;
                    tStringStream.clear();

                    tIdx += 2;
                }
                else
                {
                    tA = 255;
                }

                tStringStream << std::hex << tColor.substr(tIdx, 2);
                tStringStream >> tR;
                tStringStream.clear();

                tIdx += 2;

                tStringStream << std::hex << tColor.substr(tIdx, 2);
                tStringStream >> tG;
                tStringStream.clear();

                tIdx += 2;

                tStringStream << std::hex << tColor.substr(tIdx, 2);
                tStringStream >> tB;
                tStringStream.clear();

                *aR = static_cast<unsigned char>(tR);
                *aG = static_cast<unsigned char>(tG);
                *aB = static_cast<unsigned char>(tB);
                *aA = static_cast<unsigned char>(tA);
            }
        }
    };
}

#endif
