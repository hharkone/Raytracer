#pragma once
#include <fstream>
#include <string>


class TgaWriter
{
public:

    typedef unsigned char byte;
    typedef struct
    {
        byte red, green, blue;
    }
    RGB_t;

    static bool WriteTGA(const std::string& filename, std::vector<RGB_t>* data, unsigned width, unsigned height);
};

