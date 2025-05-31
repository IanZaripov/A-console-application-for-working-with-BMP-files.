#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#pragma pack(push,1)

struct BMPFileInfo {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;
};

struct BMPPictureInfo {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    uint32_t bytes_per_pixel;
};


class BMP {
public:
    BMP(const std::string& file_path);
    ~BMP() = default;
    void LoadFile();
    void SetPixel(int x,int y);
    void MakeCross();
    void Save(const std::string& file_path);
    void DrawImage() const;
private:
    void DrawLine(int x0, int y0, int x1, int y1);
    void fillPixels(std::ifstream& input);
    bool hasOnlyBlackAndWhiteColors() const;
    BMPFileInfo file_info;
    BMPPictureInfo picture_info;
    std::vector<uint8_t> pixels;
    std::string file_name;
};
#pragma pack(pop)
