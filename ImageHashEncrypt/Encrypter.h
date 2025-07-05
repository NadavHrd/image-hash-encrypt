#pragma once

#include <iostream>

constexpr int RGB_CHANNELS_VALUE = 3;

typedef struct ImageData
{
	int width;
	int height;
	unsigned char* pixels;

	// Default values
	ImageData(int width = 0, int height = 0, unsigned char* pixels = nullptr) : width(width), height(height), pixels(pixels) {};
} ImageData;

class Encrypter
{
public:
	Encrypter() {}; // C'tor

	~Encrypter() {}; // D'tor

private:
	/*
	This function gets an image path and returns a struct which includes the image data.
	Input: const std::string& imagePath - the path to the image that will be read.
	Output: ImageData - the data of the given image.
	Runtime complexity: O(n).
	*/
	static ImageData readImage(const std::string& imagePath);
};
