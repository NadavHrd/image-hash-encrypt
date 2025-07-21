#pragma once

#include <iostream>
#include "picosha2.h"

constexpr int RGB_CHANNELS_VALUE = 3;

constexpr int FORMAT_HASH_BUFFER_SIZE = 128;

constexpr int RGB_VALUES_AMOUNT_IN_PIXEL = 3;

constexpr int KEY_MIN_LENGTH = 4;
constexpr int KEY_MAX_LENGTH = 32;

enum KeyValidationResult
{
	VALID,
	TOO_SHORT,
	TOO_LONG,
	INVALID_CHARS
};

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

	/*
	This function checks whether the given key is valid or not.
	Input: const std::string& key - the key the function checks.
	Output: int - a code presenting the key's validation result.
	Runtime complexity: O(n).
	*/
	static int isKeyValid(const std::string& key);

	/*
	This function returns the final string presenting the given image (encrypted).
	Input: ImageData image - the image the function will encrypt and return the string of, const std::string& key - the encryption key the function uses.
	Output: std::string - the given image, as an encrypted string - ready to go into a .txt file. Empty in case of an error.
	Runtime complexity: O(n).
	*/
	static std::string getEncryptedImageStr(ImageData image, const std::string& key);
};
