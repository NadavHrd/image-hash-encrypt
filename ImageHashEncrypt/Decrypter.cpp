#include "Decrypter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/*
This function decrypts an image. It gets the path of an encrypted image, and a reference to an ImageData struct, decrypts the given image, and stores the data in the given struct.
Input: const std::string& encryptedImagePath - the encrypted image the function will decrypt, ImageData& destImage - where the image data will be stored, const std::string& key - the key the function will try decrypting with.
Output: int - the result code of the operation.
Runtime complexity: O(n).
*/
int Decrypter::readEncryptedImage(const std::string& encryptedImagePath, ImageData& destImage, const std::string& key)
{
	std::ifstream encryptedImage;
	std::stringstream contentBuffer;
	std::string imageContent = "";
	std::istringstream contentStream;
	std::string currLine = "";
	std::string currHash = "";
	std::istringstream currLineStream;
	int imageHeight = 0;
	int prevPixel[RGB_VALUES_AMOUNT_IN_PIXEL] = {};
	int prevRowPixel[RGB_VALUES_AMOUNT_IN_PIXEL] = {};
	int currRgbVal = 0;
	int hashesPerLine = 0;
	bool firstLine = true;
	int imageWidth = 0;
	std::vector<unsigned char> imageRgbValues;
	bool firstPixelInLine = true;
	size_t rgbValuesAmount = 0;
	unsigned char* pixelsData = nullptr;

	// The given encrypted image must be a .txt file
	if (!Encrypter::hasExtension(encryptedImagePath, TEXT_FILE_EXTENSION))
		return GIVEN_IMAGE_NOT_TXT;

	encryptedImage.open(encryptedImagePath);

	if (!encryptedImage.is_open()) // Image failed to open - wrong path
		return INVALID_IMAGE_PATH;

	contentBuffer << encryptedImage.rdbuf(); // Reading the whole file content into contentBuffer

	encryptedImage.close();

	imageContent = contentBuffer.str(); // Get the whole file content as a string

	contentStream.str(imageContent); // Turn the string into a stream

	while (std::getline(contentStream, currLine)) // Going over each line of the stream - each 'row' of the image
	{
		// Clear & load the current line into a stream
		currLineStream.clear();
		currLineStream.str(currLine);

		hashesPerLine = 0; // Variable for counting each hash - each rgb value
		firstPixelInLine = true;

		while (currLineStream >> currHash) // Going over every hash in the line
		{
			if (firstPixelInLine) // If it's the first pixel in the line
			{
				// Decrypt the hash into the rgb value - starting from the rgb value in the top pixel to the current pixel
				currRgbVal = Decrypter::decryptRgbValue(currHash, key, imageHeight, (hashesPerLine / RGB_VALUES_AMOUNT_IN_PIXEL), prevRowPixel[hashesPerLine % RGB_VALUES_AMOUNT_IN_PIXEL]);

				prevRowPixel[hashesPerLine % RGB_VALUES_AMOUNT_IN_PIXEL] = currRgbVal; // Saving the rgb value for the next row
				prevPixel[hashesPerLine % RGB_VALUES_AMOUNT_IN_PIXEL] = currRgbVal; // Saving the rgb value for the next pixel in the line

				if (hashesPerLine == (RGB_VALUES_AMOUNT_IN_PIXEL - 1)) // If we reached the last rgb value in the first pixel
					firstPixelInLine = false; // Next pixels are not first
			}
			else // If it's not the first pixel in the line
			{
				// Decrypting the rgb value, starting from the rgb value of the previous pixel in the line
				currRgbVal = Decrypter::decryptRgbValue(currHash, key, imageHeight, (hashesPerLine / RGB_VALUES_AMOUNT_IN_PIXEL), prevPixel[hashesPerLine % RGB_VALUES_AMOUNT_IN_PIXEL]);

				prevPixel[hashesPerLine % RGB_VALUES_AMOUNT_IN_PIXEL] = currRgbVal; // Saving the rgb value for the next pixel in the line
			}

			if (currRgbVal == WRONG_KEY_RETURN_VALUE) // If we couldn't find a matching hash - no rgb value found - wrong key
				return READING_IMAGE_INVALID_KEY_GIVEN;

			imageRgbValues.push_back(currRgbVal); // Save the rgb value in the image pixels vector

			currHash = "";
			hashesPerLine++;

			if (!firstLine) // If it's not the first line
			{
				if ((hashesPerLine / RGB_VALUES_AMOUNT_IN_PIXEL) > imageWidth) // If we just decrypted an 'extra' rgb value - image width is not synced in all rows
					return READING_IMAGE_WRONG_IMAGE_DIMENSIONS;
			}
		}

		// By here we finished decrypting the current line

		if (firstLine) // If it's the first line
		{
			imageWidth = (hashesPerLine / RGB_VALUES_AMOUNT_IN_PIXEL); // Set the width of the image
			firstLine = false;
		}
		else // If its not the first line
		{
			if ((hashesPerLine / RGB_VALUES_AMOUNT_IN_PIXEL) < imageWidth) // If we have missing rgb values for the current row
				return READING_IMAGE_WRONG_IMAGE_DIMENSIONS;
		}

		imageHeight++;
	}

	rgbValuesAmount = imageRgbValues.size();

	// Allocate and put the rgb values inside an unsigned char array
	pixelsData = (unsigned char*)malloc(rgbValuesAmount);
	memcpy(pixelsData, imageRgbValues.data(), rgbValuesAmount);

	destImage.height = imageHeight;
	destImage.width = imageWidth;
	destImage.pixels = pixelsData;

	return SUCCESS_IMAGE_READ;
}

/*
This function gets the stats of an rgb value, and its hash string, and decrypts the rgb value.
Input: const std::string& rgbValueHash - the hash string of the rgb value, const std::string& key - the encryption key of the image, const int pixelY - the Y axis value of the pixel,
const int pixelX - the X axis value of the pixel, const int prevRgbVal - the rgb value of the previous pixel in the image.
Output: The rgb value of the given hash string.
Runtime complexity: O(1).
*/
int Decrypter::decryptRgbValue(const std::string& rgbValueHash, const std::string& key, const int pixelY, const int pixelX, const int prevRgbVal)
{
	// Initialize the rgb values the function will start from
	int currDownRgbVal = prevRgbVal; // This value will go down after each iteration
	int currUpRgbVal = prevRgbVal + 1; // This value will go up after each iteration
	// We are starting from the last pixel's rgb value, to save time by hashing less strings - Spatial Redundancy

	while ((currDownRgbVal >= RGB_MIN_VALUE) || (currUpRgbVal <= RGB_MAX_VALUE)) // Going until we covered every possible rgb value
	{
		if (currDownRgbVal >= RGB_MIN_VALUE) // If there are still possible rgb values under the previous pixel's value
		{
			// Hashing the current 'down' rgb value and comparing to the actual hash of the rgb value
			if (picosha2::hash256_hex_string(Encrypter::formatHashInput(currDownRgbVal, key, pixelX, pixelY)) == rgbValueHash)
				return currDownRgbVal;

			currDownRgbVal--; // Going down by 1 for the next iteration
		}

		if (currUpRgbVal <= RGB_MAX_VALUE) // If there are still possible rgb values above the previous pixel's value
		{
			// Hashing the current 'up' rgb value and comparing to the actual hash of the rgb value
			if (picosha2::hash256_hex_string(Encrypter::formatHashInput(currUpRgbVal, key, pixelX, pixelY)) == rgbValueHash)
				return currUpRgbVal;

			currUpRgbVal++; // Going up one value for the next iteration
		}
	}

	return WRONG_KEY_RETURN_VALUE; // By here we covered all possible rgb values, but found none matching
}

/*
This function decrypts an encrypted image and saves it.
Input: const std::string& encryptedImagePath - the path of the encrypted image, const std::string& key - the encryption key, const std::string& destImagePath - the path where the image will be saved at.
Output: int - the result code (DecryptionResult).
Runtime complexity: O(n).
*/
int Decrypter::decryptImage(const std::string& encryptedImagePath, const std::string& key, const std::string& destImagePath)
{
	ImageData image;
	int readEncryptedCode = 0;

	if (!Encrypter::hasExtension(destImagePath, PNG_FILE_EXTENSION)) // If the dest image is not a .png file
		return DEST_IMAGE_NOT_PNG; // The image cannot be saved

	if (std::filesystem::exists(destImagePath)) // If the dest image path already exists
		return DEST_IMAGE_ALREADY_EXISTS; // We do not want to override the existing image

	readEncryptedCode = Decrypter::readEncryptedImage(encryptedImagePath, image, key); // Decrypting the image

	switch (readEncryptedCode) // Going over the errors (if some occurred)
	{
	// Returning the error codes
		case GIVEN_IMAGE_NOT_TXT:
			return SRC_IMAGE_NOT_TXT;
		case INVALID_IMAGE_PATH:
			return INVALID_SRC_IMAGE_PATH;
		case READING_IMAGE_INVALID_KEY_GIVEN:
			return INVALID_KEY_GIVEN;
		case READING_IMAGE_WRONG_IMAGE_DIMENSIONS:
			return WRONG_IMAGE_DIMENSIONS;
	}

	// Attempting to save the decrypted image as a .png file
	if (stbi_write_png(destImagePath.c_str(), image.width, image.height, RGB_CHANNELS_VALUE, image.pixels, image.width * RGB_VALUES_AMOUNT_IN_PIXEL))
	{
		return DECRYPTION_SUCCESS;
	}
	else
	{
		return ERROR_CREATING_IMAGE;
	}
}
