#pragma once

#include <iostream>
#include <cstdlib>
#include "Encrypter.h"
#include "Decrypter.h"

// Reset
constexpr const char* RESET = "\033[0m";

// Regular colors
constexpr const char* BLACK = "\033[30m";
constexpr const char* RED = "\033[31m";
constexpr const char* GREEN = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* CYAN = "\033[36m";
constexpr const char* WHITE = "\033[37m";

// Bright colors
constexpr const char* BRIGHT_BLACK = "\033[90m";
constexpr const char* BRIGHT_RED = "\033[91m";
constexpr const char* BRIGHT_GREEN = "\033[92m";
constexpr const char* BRIGHT_YELLOW = "\033[93m";
constexpr const char* BRIGHT_BLUE = "\033[94m";
constexpr const char* BRIGHT_MAGENTA = "\033[95m";
constexpr const char* BRIGHT_CYAN = "\033[96m";
constexpr const char* BRIGHT_WHITE = "\033[97m";

// Text styles
constexpr const char* BOLD = "\033[1m";
constexpr const char* UNDERLINE = "\033[4m";
constexpr const char* REVERSED = "\033[7m";

class UserInterface
{
public:
	/*
	This function lets the user encrypt an image. The function will then print the encryption result to the user.
	Input: none.
	Output: none.
	Runtime complexity: O(n).
	*/
	static void userEncrypt();

	/*
	This function lets the user decrypt an image. The function will then print the decryption result to the user.
	Input: none.
	Output: none.
	Runtime complexity: O(n).
	*/
	static void userDecrypt();

	/*
	This function prints the main menu to the user.
	Input: none.
	Output: none.
	Runtime complexity: O(1).
	*/
	static void printMainMenu();

	/*
	This function gets an int input from the user and makes sure it's within the given valid range.
	Input: const int minVal, const int maxVal - the valid range for an input.
	Output: int - the user's input.
	Runtime complexity: O(n).
	*/
	static int intInput(const int minVal, const int maxVal);

private:
	/*
	This function waits until the user presses enter to continue.
	Input: none.
	Output: none.
	Runtime complexity: O(1).
	*/
	static void waitForContinue();

	/*
	This function clears the terminal of the user.
	Input: none.
	Output: none.
	Runtime complexity: O(1).
	*/
	static void clearScreen();
};
