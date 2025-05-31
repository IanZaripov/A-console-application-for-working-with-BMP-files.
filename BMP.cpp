#include "BMP.h"

using namespace std;

BMP::BMP(const string& file_path) : file_name(file_path) {

}


bool BMP::hasOnlyBlackAndWhiteColors() const {
    for (int i = 0; i < pixels.size(); i += picture_info.bytes_per_pixel) {
        uint8_t r = pixels[i];
        uint8_t g = pixels[i + 1];
        uint8_t b = pixels[i + 2];
        bool white = (r == 255 && g == 255 && b == 255);
        bool black = (r == 0 && g == 0 && b == 0);
        if (!black && !white) {
            return false;
        }
    }
    return true;
}

void BMP::fillPixels(ifstream& input) {
    picture_info.bytes_per_pixel = picture_info.bit_count / 8;
    pixels.resize(picture_info.width * picture_info.height * picture_info.bytes_per_pixel);
    auto row_padding = (4 - (picture_info.width * picture_info.bytes_per_pixel) % 4) % 4;
    input.seekg(file_info.offset_data, ios::beg);
    for (int y = picture_info.height - 1; y >= 0; y--) {
        for (int x = 0; x < picture_info.width; x++) {
            size_t idx = (y * picture_info.width + x) * picture_info.bytes_per_pixel;
            input.read(reinterpret_cast<char*>(&pixels[idx]), picture_info.bytes_per_pixel);
            swap(pixels[idx], pixels[idx + 2]);
        }
        input.seekg(row_padding, ios::cur);
    }
}

void BMP::LoadFile() {
    ifstream input(file_name,ios::binary);
    if (!input) {
        throw runtime_error("Error: coldnt upload file: " + file_name);
    }
    input.read(reinterpret_cast<char*>(&file_info), sizeof(file_info));
    input.read(reinterpret_cast<char*>(&picture_info), sizeof(picture_info));
    if (file_info.file_type != 0x4D42) {
        throw runtime_error("Error: not a BMP file");
    }
    if (picture_info.bit_count != 24 && picture_info.bit_count != 32) {
        throw runtime_error("Error: 24 or 32-bit Bmp file was expected, but " 
            + std::to_string(picture_info.bit_count) + " file was received");
    }
    fillPixels(input);
    if (!hasOnlyBlackAndWhiteColors()) {
        throw runtime_error("Error: Image contains more colors than black and white");
    }
    input.close();
}


void BMP::DrawImage() const {
    for (int y = picture_info.height - 1; y >= 0; y--) {
        for (int x = 0; x < picture_info.width; x++) {
            size_t idx = (y * picture_info.width + x) * picture_info.bytes_per_pixel;
            uint8_t r = pixels[idx];
            uint8_t g = pixels[idx + 1];
            uint8_t b = pixels[idx + 2];
            cout << ((r == 255 && g == 255 && b == 255) ? '.' : '#');
        }
        cout << "\n";
    }
}

void BMP::SetPixel(int x, int y) {
    if (x < 0 || x >= picture_info.width || y < 0 || y >= picture_info.height) {
        return;
    }
    size_t idx = (y * picture_info.width + x) * picture_info.bytes_per_pixel;
    pixels[idx] = 0;
    pixels[idx + 1] = 0;
    pixels[idx + 2] = 0;
}

void BMP::DrawLine(int x0, int y0, int x1, int y1) { //алгоритм Брезенхема
    const int delta_x = std::abs(x1 - x0);
    const int delta_y = std::abs(y1 - y0);
    const int sign_x = x0 < x1 ? 1 : -1;
    const int sign_y = y0 < y1 ? 1 : -1;
    int error = delta_x - delta_y;
    SetPixel(x1, y1);
    while (x0 != x1 || y0 != y1) {
        SetPixel(x0, y0);
        int error2 = error * 2;
        if (error2 > -delta_y) {
            error -= delta_y;
            x0 += sign_x;
        }
        if (error2 < delta_x) {
            error += delta_x;
            y0 += sign_y;
        }
    }
}

void BMP::MakeCross() {
    DrawLine(0, 0, picture_info.width - 1, picture_info.height - 1);
    DrawLine(0, picture_info.height - 1, picture_info.width - 1, 0);
}


void BMP::Save(const std::string& output_file) {
    ofstream output(output_file, ios::binary);
    if (!output) {
        throw runtime_error("Error: couldn't create output file: " + output_file);
    }

    output.write(reinterpret_cast<const char*>(&file_info), sizeof(file_info));
    output.write(reinterpret_cast<const char*>(&picture_info), sizeof(picture_info));
    
    const auto row_padding = (4 - ((picture_info.width * picture_info.bytes_per_pixel) % 4)) % 4;
    const uint8_t padding[4] = { 0,0,0,0 };

    if (file_info.offset_data > sizeof(BMPFileInfo) + sizeof(BMPPictureInfo)) {
        vector<uint8_t> zeros(file_info.offset_data - sizeof(BMPFileInfo) - sizeof(BMPPictureInfo), 0);
        output.write(reinterpret_cast<const char*>(zeros.data()), zeros.size());
    }
    for (int y = picture_info.height - 1; y >= 0; --y) {
        for (int x = 0; x < picture_info.width; ++x) {
            size_t idx = (y * picture_info.width + x) * picture_info.bytes_per_pixel;
            vector<uint8_t> pixel(pixels.begin() + idx, pixels.begin() + idx + picture_info.bytes_per_pixel);
            std::swap(pixel[0], pixel[2]);
            output.write(reinterpret_cast<const char*>(pixel.data()), pixel.size());
        }
        output.write(reinterpret_cast<const char*>(padding), row_padding);
    }
    output.close();
}