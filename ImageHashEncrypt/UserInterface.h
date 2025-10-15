#pragma once

#include <iostream>
#include <cstdlib>
#include "Encrypter.h"
#include "Decrypter.h"

class UserInterface
{
public:
	/*
	This function lets the user encrypt an image. The function will then print the encryption result to the user.
	Input: none.
	Output: none.
	Runtime complexity: O(n).
	*/
	void userEncrypt();

private:
	/*
	This function waits until the user presses enter to continue.
	Input: none.
	Output: none.
	Runtime complexity: O(1).
	*/
	void waitForContinue();

	/*
	This function clears the terminal of the user.
	Input: none.
	Output: none.
	Runtime complexity: O(1).
	*/
	void clearScreen();
};
