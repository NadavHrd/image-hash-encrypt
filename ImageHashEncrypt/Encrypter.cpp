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
