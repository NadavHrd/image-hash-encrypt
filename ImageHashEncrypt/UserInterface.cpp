#include "UserInterface.h"

/*
This function waits until the user presses enter to continue.
Input: none.
Output: none.
Runtime complexity: O(1).
*/
void UserInterface::waitForContinue()
{
	std::cout << "\nPress Enter to continue...";

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

	std::cout << "Enter the path for the image you want to encrypt: ";

	std::cin >> imageToEncryptPath;

	std::cout << "\n\nEnter the path you would like to save the encrypted image at (a new .txt file): ";

	std::cin >> encryptedImagePath;

	std::cout << "\n\nEnter the encryption key: ";

	std::cin >> key;

	std::cout << "\n\n\nEncrypting image. This may take a while...\n";

	resCode = Encrypter::EncryptImage(imageToEncryptPath, encryptedImagePath, key); // Encrypting the image

	// Printing the encryption result
	switch (resCode)
	{
		case SUCCESS:
			std::cout << "Image was encrypted successfully.\n";
			break;
		case IMAGE_PATH_INVALID:
			std::cout << "ERROR: The given image path is invalid.\n";
			break;
		case DST_IMAGE_PATH_ALREADY_EXISTS:
			std::cout << "ERROR: The given .txt file already exist.\n";
			break;
		case DST_IMAGE_PATH_NOT_TEXT_FILE:
			std::cout << "ERROR: The given destination file is not .txt.\n";
			break;
		case ERROR_CREATING_ENCRYPTED_IMAGE:
			std::cout << "ERROR: An error occurred while trying to create a .txt file.\n";
			break;
		case ERROR_HASHING_IMAGE_VALUES:
			std::cout << "ERROR: The given image data is corrupted.\n";
			break;
		case KEY_INVALID:
			std::cout << "ERROR: Invalid key. A valid key does not include whitespace and is 4 - 32 chars long.\n";
			break;
	}

	UserInterface::waitForContinue();
}
