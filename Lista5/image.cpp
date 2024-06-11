#include "image.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

void Image::load(const std::string& filename)
{
    constexpr auto MAGIC = "P6";

    this->filename = filename;

    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::invalid_argument("failed to open \"" + filename + "\"");

    in >> magic;
    if (magic != MAGIC) throw std::logic_error("unknown magic naumber " + magic);

    in >> my_width >> my_height >> color_depth;

    if (!in || my_width < 0 || my_width > 10000 || my_height < 0 || my_height > 10000 || color_depth <= 0 ||
        color_depth > 255)
        throw std::logic_error("invalid image parameter(s): " + std::to_string(my_width) + " " +
                               std::to_string(my_height) + " " + std::to_string(color_depth));
    in.ignore(1);
    pixels.resize(my_height);
    for (auto& line : pixels)
    {
        line.resize(my_width);
        in.read(reinterpret_cast<char*>(&line[0]), my_width * sizeof(RGB));
        if (!in) throw std::logic_error("failed to read binary pixel data from file " + filename);
    }
}

void Image::save_as(const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Could not open file for writing: " + filename);

    out << magic << "\n";
    out << my_width << " " << my_height << "\n";
    out << color_depth << "\n";

    for (const auto& line : pixels) {
        out.write(reinterpret_cast<const char*>(&line[0]), line.size() * sizeof(RGB));
        if (!out) throw std::runtime_error("Failed to write binary pixel data to file " + filename);
    }
}


void Image::add_watermark()
{
    for (int y = 0; y < my_height; y++) {
        for (int x = 0; x < my_width; x++) {
            if (x == y || x == my_width - y) {
                pixels[y][x].red = 255;
                pixels[y][x].green = 0;
                pixels[y][x].blue = 0;
            }
        }
    }
}

void Image::blurr()
{
    std::vector<std::vector<RGB>> new_pixels = pixels;

    for (int y = 0; y < my_height; ++y)
    {
        for (int x = 0; x < my_width; ++x)
        {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                    int ny = y + dy;
                    int nx = x + dx;

                    if (ny >= 0 && ny < my_height && nx >= 0 && nx < my_width)
                    {
                        red_sum += pixels[ny][nx].red;
                        green_sum += pixels[ny][nx].green;
                        blue_sum += pixels[ny][nx].blue;
                        count++;
                    }
                }
            }

            new_pixels[y][x].red = red_sum / count;
            new_pixels[y][x].green = green_sum / count;
            new_pixels[y][x].blue = blue_sum / count;
        }
    }

    pixels = new_pixels;

    static int iterations = 10;
    if (--iterations > 0)
    {
        blurr();
    }
}

void Image::extract_layer(ColorLayer color_layer)
{
    for (auto& row : pixels)
    {
        for (auto& pixel : row)
        {
            switch (color_layer)
            {
                case ColorLayer::Red:
                    pixel.green = 0;
                    pixel.blue = 0;
                    break;
                case ColorLayer::Green:
                    pixel.red = 0;
                    pixel.blue = 0;
                    break;
                case ColorLayer::Blue:
                    pixel.red = 0;
                    pixel.green = 0;
                    break;
            }
        }
    }
}


void Image::filter()
{
    for (int y = 0; y < my_height - 1; y++) {
        for (int x = 0; x < my_width - 1; x++) {
            int diff_red = std::abs(pixels[y][x].red - pixels[y + 1][x + 1].red);
            int diff_green = std::abs(pixels[y][x].green - pixels[y + 1][x + 1].green);
            int diff_blue = std::abs(pixels[y][x].blue - pixels[y + 1][x + 1].blue);

            pixels[y][x].red = diff_red;
            pixels[y][x].green = diff_green;
            pixels[y][x].blue = diff_blue;
        }
    }
}


void Image::flip_horizontally()
{
    for (auto& row : pixels) {
        std::reverse(row.begin(), row.end());
    }
}

void Image::flip_vertically()
{
    std::reverse(pixels.begin(), pixels.end());
}

void Image::inflate()
{
    std::vector<std::vector<RGB>> new_pixels(2 * my_height, std::vector<RGB>(2 * my_width));

    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            new_pixels[2 * y][2 * x] = pixels[y][x];
            new_pixels[2 * y + 1][2 * x] = pixels[y][x];
            new_pixels[2 * y][2 * x + 1] = pixels[y][x];
            new_pixels[2 * y + 1][2 * x + 1] = pixels[y][x];
        }
    }
    pixels = std::move(new_pixels);
    my_width *= 2;
    my_height *= 2;
}

void Image::negative()
{
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            pixel.red = 255 - pixel.red;
            pixel.green = 255 - pixel.green;
            pixel.blue = 255 - pixel.blue;
        }
    }
}

void Image::rotate_clockwise_90()
{
    std::vector<std::vector<RGB>> new_pixels(my_width, std::vector<RGB>(my_height));
    for (int y = 0; y < my_height; ++y) {
        for (int x = 0; x < my_width; ++x) {
            new_pixels[x][my_height - 1 - y] = pixels[y][x];
        }
    }
    pixels = std::move(new_pixels);
    std::swap(my_width, my_height);
}

void Image::sepia()
{
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            int red = pixel.red;
            int green = pixel.green;
            int blue = pixel.blue;
            int newRed = std::min(int(0.393 * red + 0.769 * green + 0.189 * blue), 255);
            int newGreen = std::min(int(0.349 * red + 0.686 * green + 0.168 * blue), 255);
            int newBlue = std::min(int(0.272 * red + 0.534 * green + 0.131 * blue), 255);
            pixel.red = newRed;
            pixel.green = newGreen;
            pixel.blue = newBlue;
        }
    }
}

void Image::shrink()
{
    std::vector<std::vector<RGB>> new_pixels(my_height / 2, std::vector<RGB>(my_width / 2));

    for (int y = 0; y < my_height / 2; ++y) {
        for (int x = 0; x < my_width / 2; ++x) {
            new_pixels[y][x] = pixels[2 * y][2 * x]; // Picking one of every four pixels
        }
    }
    pixels = std::move(new_pixels);
    my_width /= 2;
    my_height /= 2;
}

void Image::to_grayscale()
{
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            int gray = pixel.red * 0.299 + pixel.green * 0.587 + pixel.blue * 0.114;
            pixel.red = gray;
            pixel.green = gray;
            pixel.blue = gray;
        }
    }
}

int Image::height() const
{
    return my_height;
}

int Image::width() const
{
    return my_width;
}
