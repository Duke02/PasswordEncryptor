#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

void debugString(const std::string &str) {
	for ( auto c : str ) {
		std::cout << (int)(c);
	}
	std::cout << std::endl;
}

std::string cipher(const std::string &str) {
	int maxRange = 2;
	int num = rand() % maxRange + 1;
	std::string out = std::to_string(num);
	std::string strCopy = str;
	for ( auto c : strCopy ) {
		out += c + num;
	}
	return out;
}

std::string decipher(const std::string& cipheredPassword) {
	int num = cipheredPassword[0] - '0';
	std::string strCopy = cipheredPassword.substr(1);
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
