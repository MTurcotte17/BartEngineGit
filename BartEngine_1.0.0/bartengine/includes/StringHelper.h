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

        static void GetColorComponents(const std::string& aColor, int* aR, int* aG, int* aB, int* aA)
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

                std::stringstream tStringStream;

                if (tColorLen == 8)
                {
                    tStringStream << std::hex << tColor.substr(tIdx, 2);
                    tStringStream >> *aA;
                    tStringStream.clear();

                    tIdx += 2;
                }

                tStringStream << std::hex << tColor.substr(tIdx, 2);
                tStringStream >> *aR;
                tStringStream.clear();

                tIdx += 2;

                tStringStream << std::hex << tColor.substr(tIdx, 2);
                tStringStream >> *aG;
                tStringStream.clear();

                tIdx += 2;

                tStringStream << std::hex << tColor.substr(tIdx, 2);
                tStringStream >> *aB;
                tStringStream.clear();
            }
        }
    };
}

#endif
