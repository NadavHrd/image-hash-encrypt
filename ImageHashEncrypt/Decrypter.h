#pragma once

#include <iostream>
#include "picosha2.h"
#include "Encrypter.h"

constexpr int RGB_MAX_VALUE = 255;
constexpr int RGB_MIN_VALUE = 0;

constexpr int WRONG_KEY_RETURN_VALUE = -1;

enum EncryptedImageReadingResult
{
	SUCCESS_IMAGE_READ,
	GIVEN_IMAGE_NOT_TXT,
	INVALID_IMAGE_PATH,
	INVALID_KEY_GIVEN,
	WRONG_IMAGE_DIMENSIONS
};

class Decrypter
{
private:
	/*
	This function decrypts an image. It gets the path of an encrypted image, and a reference to an ImageData struct, decrypts the given image, and stores the data in the given struct.
	Input: const std::string& encryptedImagePath - the encrypted image the function will decrypt, ImageData& destImage - where the image data will be stored, const std::string& key - the key the function will try decrypting with.
	Output: int - the result code of the operation.
	Runtime complexity: O(n).
	*/
	static int readEncryptedImage(const std::string& encryptedImagePath, ImageData& destImage, const std::string& key);

	/*
	This function gets the stats of an rgb value, and its hash string, and decrypts the rgb value.
	Input: const std::string& rgbValueHash - the hash string of the rgb value, const std::string& key - the encryption key of the image, const int pixelY - the Y axis value of the pixel,
	const int pixelX - the X axis value of the pixel, const int prevRgbVal - the rgb value of the previous pixel in the image.
	Output: The rgb value of the given hash string.
	Runtime complexity: O(1).
	*/
	static int decryptRgbValue(const std::string& rgbValueHash, const std::string& key, const int pixelY, const int pixelX, const int prevRgbVal);
};
