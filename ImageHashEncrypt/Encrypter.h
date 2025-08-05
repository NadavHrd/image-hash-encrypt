#pragma once

#include <iostream>
#include <fstream>
#include "picosha2.h"

constexpr int RGB_CHANNELS_VALUE = 3;

constexpr int FORMAT_HASH_BUFFER_SIZE = 128;

constexpr int RGB_VALUES_AMOUNT_IN_PIXEL = 3;

constexpr int KEY_MIN_LENGTH = 4;
constexpr int KEY_MAX_LENGTH = 32;

constexpr const char* TEXT_FILE_EXTENSION = ".txt";

enum KeyValidationResult
{
	VALID,
	TOO_SHORT,
	TOO_LONG,
	INVALID_CHARS
};

enum ImageEncryptionResult
{
	SUCCESS,
	IMAGE_PATH_INVALID,
	DST_IMAGE_PATH_ALREADY_EXISTS,
	DST_IMAGE_PATH_NOT_TEXT_FILE,
	ERROR_CREATING_ENCRYPTED_IMAGE,
	ERROR_HASHING_IMAGE_VALUES,
	KEY_INVALID
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

	/*
	This function gets an image path, a destination encrypted image path (.txt) and a key, and encrypts the given image.
	Input: const std::string& imagePath - the image the function will encrypt, const std::string& encryptedImagePath - the destination file to keep the encrypted image (.txt that doesn't exist), const std::string& key - the encryption key.
	Output: int - the result of the encryption.
	Runtime complexity: O(n).
	*/
	static int EncryptImage(const std::string& imagePath, const std::string& encryptedImagePath, const std::string& key);

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
