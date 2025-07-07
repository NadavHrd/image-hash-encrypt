#pragma once

#include <iostream>
#include "picosha2.h"

constexpr int RGB_CHANNELS_VALUE = 3;

constexpr int FORMAT_HASH_BUFFER_SIZE = 128;

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
	//                                     Example:   "17-pa$$word-{10,82}"      "[RGB VALUE]-[KEY]-{[HEIGHT],[WIDTH]}"
	static constexpr const char* RGB_VALUE_HASH_FORMAT = "%d-%s-{%d,%d}"; // The pre-hash string presenting every RGB value

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

	/*
	This function gets the info about an RGB value inside an image, and returns an std::string of the formetted pre-hash string presenting an RGB value.
	Input: int rgbValue - value of the RGB, std::string key - the key of the image, int x - where the RGB value sits (X-axis - width), int y - where the RGB value sits (Y-axis - height).
	Output: std::string - the final formatted pre-hash string presenting the given RGB value.
	Runtime complexity: O(1).
	*/
	static std::string formatHashInput(const int rgbValue, const std::string& key, const int x, const int y);
};
