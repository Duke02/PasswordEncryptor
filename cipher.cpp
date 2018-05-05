#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>

#define DEBUG 1

void debug(const std::string &message) {
	if(DEBUG == 1) {
		std::cout << "DEBUG: " << message << std::endl;
	}
}

int getNumber(const std::string &str) {
	int digits = str[0] - '0';
	int out = 0;
	for ( int i = 1; i < digits + 1; i++ ) {
		out += std::pow(10, digits - i) * (str[i] - '0');
	}
	return out;
}

std::string cipher(const std::string &str) {
	int maxRange;
	do {
		maxRange = 'z' - ' ';
	} while(std::log10(maxRange) > 9);
	// We can only add one digit to output string.
	// So the number of digits of maxRange needs to
	// be only one digit.
	int num = rand() % maxRange + 1;
	int digits = std::log10(num) + 1;
	std::string out = std::to_string(digits) + std::to_string(num);
	std::string strCopy = str;
	for ( auto c : strCopy ) {
		out += c + num;
	}
	return out;
}

std::string decipher(const std::string& cipheredPassword) {
	int num = getNumber(cipheredPassword);
	std::string strCopy = cipheredPassword.substr(std::log10(num)+1 + 1);
	// The first + 1 is for the log10 to get the actual number of digits.
	// The second + 1 is for the digits in cipheredPassword.
	std::string out;
	for ( auto c : strCopy ) {
		out += c - num;
	}
	return out;
}

int main(int argc, char ** argv) {
	srand(time(NULL));
	std::ifstream passwordFile;
	std::string application;
	std::cout << "Input the application the password is for." << std::endl;
	std::cin >> application;
	passwordFile.open(application + ".txt");
	char encrypt;
	std::cout << "Do you want to encrypt the password in the file? (Y/N)" << std::endl;
	std::cin >> encrypt;
	bool toEncrypt = tolower(encrypt) == 'y';
	std::string password;
	std::string cipheredPassword;
	if(toEncrypt) {
		std::cout << "Pass in the password for the application." << std::endl;
		std::cin >> password;
		cipheredPassword = cipher(password);
	} else {
		passwordFile >> password;
		cipheredPassword = decipher(password);
	}

	passwordFile.close();
	if(toEncrypt) {
		std::ofstream passwordFileO;
		passwordFileO.open(application + ".txt");
		passwordFileO << cipheredPassword;
		passwordFileO.close();
	} else {
		std::cout << "Your password is: " << cipheredPassword << std::endl;
	}
	return 0;
}
