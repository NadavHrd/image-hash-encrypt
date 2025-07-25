#include "Encrypter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*
This function gets an image path and returns a struct which includes the image data.
Input: const std::string& imagePath - the path to the image that will be read.
Output: ImageData - the data of the given image.
Runtime complexity: O(n).
*/
ImageData Encrypter::readImage(const std::string& imagePath)
{
	ImageData image;
	int channels = 0;
	
	image.pixels = stbi_load(imagePath.c_str(), &image.width, &image.height, &channels, RGB_CHANNELS_VALUE); // Load the given image

	return image; // In case the image path is invalid, image.pixels will be nullptr
}

/*
This function gets the info about an RGB value inside an image, and returns an std::string of the formetted pre-hash string presenting an RGB value.
Input: int rgbValue - value of the RGB, std::string key - the key of the image, int x - where the RGB value sits (X-axis - width), int y - where the RGB value sits (Y-axis - height).
Output: std::string - the final formatted pre-hash string presenting the given RGB value.
Runtime complexity: O(1).
*/
std::string Encrypter::formatHashInput(const int rgbValue, const std::string& key, const int x, const int y)
{
	char hashInputBuffer[FORMAT_HASH_BUFFER_SIZE];

	// Formatting the result according to the const format - RGB_VALUE_HASH_FORMAT
	snprintf(hashInputBuffer, sizeof(hashInputBuffer), Encrypter::RGB_VALUE_HASH_FORMAT, rgbValue, key.c_str(), y, x);

	return (std::string)hashInputBuffer;
}

/*
This function checks whether the given key is valid or not.
Input: const std::string& key - the key the function checks.
Output: int - a code presenting the key's validation result.
Runtime complexity: O(n).
*/
int Encrypter::isKeyValid(const std::string& key)
{
	if (key.length() > KEY_MAX_LENGTH) // Exceeds maximum allowed length
		return TOO_LONG;

	if (key.length() < KEY_MIN_LENGTH) // Below minimum required length
		return TOO_SHORT;

	for (auto charIt = key.begin(); charIt != key.end(); charIt++) // Going over every char inside the key
	{
		if (isspace(static_cast<unsigned char>(*charIt))) // ' ', '\n', '\t' - all white spaces are invalid
			return INVALID_CHARS;
	}

	return VALID;
}

/*
This function returns the final string presenting the given image (encrypted).
Input: ImageData image - the image the function will encrypt and return the string of, const std::string& key - the encryption key the function uses.
Output: std::string - the given image, as an encrypted string - ready to go into a .txt file. Empty in case of an error.
Runtime complexity: O(n).
*/
std::string Encrypter::getEncryptedImageStr(ImageData image, const std::string& key)
{
	int heightIndex = 0, widthIndex = 0, currRgbIndex = 0, rgbLoop = 0;
	std::string encryptedImage = "";

	if (!image.pixels) // If the given image is empty
		return "";

	if (Encrypter::isKeyValid(key) != VALID) // If the given key is invalid
		return "";

	for (heightIndex = 0; heightIndex < image.height; heightIndex++) // Going over each row of the image
	{
		for (widthIndex = 0; widthIndex < image.width; widthIndex++) // Going over every pixel of each row
		{
			// currRgbIndex -> R
			// (currRgbIndex + 1) -> G
			// (currRgbIndex + 2) -> B
			currRgbIndex = (((heightIndex * image.width) + widthIndex) * RGB_VALUES_AMOUNT_IN_PIXEL); // Calculating the current rgb value index
			
			for (rgbLoop = 0; rgbLoop < RGB_VALUES_AMOUNT_IN_PIXEL; rgbLoop++) // Going over every rgb value in the current pixel
			{
				try
				{
					// Adding the current rgb value hash to the final image string
					encryptedImage += picosha2::hash256_hex_string(Encrypter::formatHashInput(image.pixels[currRgbIndex + rgbLoop], key, widthIndex, heightIndex));
				}
				catch (...) // Access violation - image.pixels doesn't match image.width & image.height -> invalid image was given
				{
					return "";
				}
			}
		}
	}

	return encryptedImage;
}
