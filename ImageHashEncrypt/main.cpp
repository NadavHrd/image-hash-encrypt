#include "UserInterface.h"

constexpr int PROGRAM_SUCCESS = 0;
constexpr int PROGRAM_FAILURE = 1;

constexpr int USER_CHOICE_MIN_VALUE = 1;
constexpr int USER_CHOICE_MAX_VALUE = 3;

enum UserChoice
{
	ENCRYPT = 1,
	DECRYPT,
	EXIT
};

/*
This program lets the user encrypt and decrypt images.
Input: none.
Output: int - success / failure.
Runtime complexity: O(n^2).
*/
int main()
{
	int userInput = EXIT + 1;

	while (userInput != EXIT)
	{
		// Print menu
		UserInterface::clearScreen();
		UserInterface::printMainMenu();

		userInput = UserInterface::intInput(USER_CHOICE_MIN_VALUE, USER_CHOICE_MAX_VALUE); // Get the user's choice

		// Work according to the user's choice
		switch (userInput)
		{
			case ENCRYPT:
				UserInterface::userEncrypt();
				break;
			case DECRYPT:
				UserInterface::userDecrypt();
				break;
		}
	}

	return PROGRAM_SUCCESS;
}
