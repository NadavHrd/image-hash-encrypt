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
