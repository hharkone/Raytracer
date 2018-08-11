#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "Vector3.hpp"

class TgaWriter
{
public:

    typedef unsigned char byte;
    typedef struct
    {
        byte red, green, blue;
    }
    RGB_t;

    static bool WriteTGA(const std::string& filename, std::vector<Vector3>& data, unsigned width, unsigned height);
};

