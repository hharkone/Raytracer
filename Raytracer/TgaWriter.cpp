#include "TgaWriter.hpp"

unsigned char doubleToByte(double v)
{
    return std::min(std::max(int(v * 255), 0), 255);
}

double tonemap(double v)
{
    return std::pow(v, 0.45454);
}

void tonemap(Vector3& v)
{
    v.x = tonemap(v.x);
    v.y = tonemap(v.y);
    v.z = tonemap(v.z);
}

Vector3 tonemap(Vector3 v)
{
    return Vector3(tonemap(v.x), tonemap(v.y), tonemap(v.z));
}

// It is presumed that the image is stored in memory as 
// RGB_t data[ height ][ width ]
// where lines are top to bottom and columns are left to right
// (the same way you view the image on the display)
bool TgaWriter::WriteTGA(const std::string& filename, std::vector<Vector3>& data, unsigned width, unsigned height)
{
    // The routine makes all the appropriate adjustments to match the TGA format specification.
    std::ofstream tgafile(filename.c_str(), std::ios::binary);
    std::ios::sync_with_stdio(false);
    if (!tgafile) return false;

    // The image header
    byte header[18] = { 0 };
    header[2] = 2;  // truecolor THIS MUST BE 2 NOT 1 LIKE THE INTERNETS SAYS FUUUCK!
    header[12] = width & 0xFF;
    header[13] = (width >> 8) & 0xFF;
    header[14] = height & 0xFF;
    header[15] = (height >> 8) & 0xFF;
    header[16] = 24;  // bits per pixel

    tgafile.write((const char*)header, 18);

    for (const Vector3& i : data)
    {
        tgafile.put(doubleToByte(tonemap(i.x)));
        tgafile.put(doubleToByte(tonemap(i.y)));
        tgafile.put(doubleToByte(tonemap(i.z)));
    }

    // The file footer. This part is totally optional.
    static const char footer[26] =
        "\0\0\0\0"              // no extension area
        "\0\0\0\0"              // no developer directory
        "TRUEVISION-XFILE"      // yep, this is a TGA file
        ".";

    tgafile.write(footer, 26);
    tgafile.close();

    return true;
}
