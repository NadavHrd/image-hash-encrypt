#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <filesystem>
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
	READING_IMAGE_INVALID_KEY_GIVEN,
	READING_IMAGE_WRONG_IMAGE_DIMENSIONS
};

enum DecryptionResult
{
	DECRYPTION_SUCCESS,
	SRC_IMAGE_NOT_TXT,
	INVALID_SRC_IMAGE_PATH,
	INVALID_KEY_GIVEN,
	WRONG_IMAGE_DIMENSIONS,
	INVALID_DEST_IMAGE_PATH,
	DEST_IMAGE_NOT_PNG,
	DEST_IMAGE_ALREADY_EXISTS,
	ERROR_CREATING_IMAGE
};

class Decrypter
{
public:
	/*
	This function decrypts an encrypted image and saves it.
	Input: const std::string& encryptedImagePath - the path of the encrypted image, const std::string& key - the encryption key, const std::string& destImagePath - the path where the image will be saved at.
	Output: int - the result code (DecryptionResult).
	Runtime complexity: O(n).
	*/
	static int decryptImage(const std::string& encryptedImagePath, const std::string& key, const std::string& destImagePath);

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
