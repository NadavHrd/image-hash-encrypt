#include "UserInterface.h"

/*
This function waits until the user presses enter to continue.
Input: none.
Output: none.
Runtime complexity: O(1).
*/
void UserInterface::waitForContinue()
{
	std::cout << WHITE << "\nPress Enter to continue...";

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

	std::cin.get();
}

/*
This function clears the terminal of the user.
Input: none.
Output: none.
Runtime complexity: O(1).
*/
void UserInterface::clearScreen()
{
	system("cls");
}

/*
This function lets the user encrypt an image. The function will then print the encryption result to the user.
Input: none.
Output: none.
Runtime complexity: O(n).
*/
void UserInterface::userEncrypt()
{
	std::string imageToEncryptPath = "";
	std::string encryptedImagePath = "";
	std::string key = "";
	int resCode = 0;

	UserInterface::clearScreen();

	// Getting all of the fields needed for the encryption from the user

	std::cout << RESET << "Enter the path for the image you want to encrypt: ";

	std::cin >> imageToEncryptPath;

	std::cout << "\n\nEnter the path you would like to save the encrypted image at (a new .txt file): ";

	std::cin >> encryptedImagePath;

	std::cout << "\n\nEnter the encryption key: ";

	std::cin >> key;

	std::cout << "\n\n\nEncrypting image. This may take a while...\n";

	resCode = Encrypter::EncryptImage(imageToEncryptPath, encryptedImagePath, key); // Encrypting the image

	// Printing the encryption result
	
	std::cout << BOLD;
	
	switch (resCode)
	{
		case SUCCESS:
			std::cout << GREEN << "Image was encrypted successfully.\n";
			break;
		case IMAGE_PATH_INVALID:
			std::cout << RED << "ERROR: The given image path is invalid.\n";
			break;
		case DST_IMAGE_PATH_ALREADY_EXISTS:
			std::cout << RED << "ERROR: The given .txt file already exist.\n";
			break;
		case DST_IMAGE_PATH_NOT_TEXT_FILE:
			std::cout << RED << "ERROR: The given destination file is not .txt.\n";
			break;
		case ERROR_CREATING_ENCRYPTED_IMAGE:
			std::cout << RED << "ERROR: An error occurred while trying to create a .txt file.\n";
			break;
		case ERROR_HASHING_IMAGE_VALUES:
			std::cout << RED << "ERROR: The given image data is corrupted.\n";
			break;
		case KEY_INVALID:
			std::cout << RED << "ERROR: Invalid key. A valid key does not include whitespace and is 4 - 32 chars long.\n";
			break;
	}

	UserInterface::waitForContinue();
}

/*
This function lets the user decrypt an image. The function will then print the decryption result to the user.
Input: none.
Output: none.
Runtime complexity: O(n).
*/
void UserInterface::userDecrypt()
{
	std::string encryptedImagePath = "";
	std::string destImagePath = "";
	std::string key = "";
	int resCode = 0;

	UserInterface::clearScreen();

	// Get the required inputs for the decryption from the user

	std::cout << RESET << "Enter the path for the encrypted image (.txt): ";

	std::cin >> encryptedImagePath;

	std::cout << "\n\nEnter the path which you would like to save the new image at (.png): ";

	std::cin >> destImagePath;

	std::cout << "\n\nEnter the decryption key: ";

	std::cin >> key;

	std::cout << "\n\n\nDecrypting image. This may take a while...\n";

	resCode = Decrypter::decryptImage(encryptedImagePath, key, destImagePath); // Decrypting the image

	// Printing the decryption result

	std::cout << BOLD;

	switch (resCode)
	{
		case DECRYPTION_SUCCESS:
			std::cout << GREEN << "Image was decrypted successfully.\n";
			break;
		case SRC_IMAGE_NOT_TXT:
			std::cout << RED << "ERROR: The given encrypted image is not a .txt file.\n";
			break;
		case INVALID_SRC_IMAGE_PATH:
			std::cout << RED << "ERROR: The given encrypted image path is invalid.\n";
			break;
		case INVALID_KEY_GIVEN:
			std::cout << RED << "ERROR: Invalid key. A valid key does not include whitespace and is 4 - 32 chars long.\n";
			break;
		case WRONG_IMAGE_DIMENSIONS:
			std::cout << RED << "ERROR: The given encrypted image dimensions are corrupted.\n";
			break;
		case INVALID_DEST_IMAGE_PATH:
			std::cout << RED << "ERROR: The given .png path to save the image at is invalid.\n";
			break;
		case DEST_IMAGE_NOT_PNG:
			std::cout << RED << "ERROR: The destination path to save the image at is not .png.\n";
			break;
		case DEST_IMAGE_ALREADY_EXISTS:
			std::cout << RED << "ERROR: The destination path to save the image at already exists.\n";
			break;
		case ERROR_CREATING_IMAGE:
			std::cout << RED << "ERROR: An error occurred while trying to create the image (.png).\n";
			break;
	}

	UserInterface::waitForContinue();
}

/*
This function prints the main menu to the user.
Input: none.
Output: none.
Runtime complexity: O(1).
*/
void UserInterface::printMainMenu()
{
	std::cout << BRIGHT_WHITE << "What would you like to do?\n";
	std::cout << "1. " << BRIGHT_MAGENTA << "Encrypt an image.\n";
	std::cout << BRIGHT_WHITE << "2. " << CYAN << "Decrypt an image.\n\n";
}

/*
This function gets an int input from the user and makes sure it's within the given valid range.
Input: const int minVal, const int maxVal - the valid range for an input.
Output: int - the user's input.
Runtime complexity: O(n).
*/
int UserInterface::intInput(const int minVal, const int maxVal)
{
	int userInput = minVal;
	
	do
	{
		if (std::cin.fail())
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
		}
		
		std::cin >> userInput;

		// In case of bad input, notify the user
		if ((std::cin.fail()) || (userInput > maxVal) || (userInput < minVal))
		{
			std::cout << WHITE << "\nThe input must be an integer between " << minVal << " and " << maxVal << ".\n";
		}

	} while ((std::cin.fail()) || (userInput > maxVal) || (userInput < minVal)); // Go over the input loop until we get a valid input

	return userInput;
}
