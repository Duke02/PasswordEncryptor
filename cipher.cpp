#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

void debugStr(const std::string &str) {
	for ( auto c : str ) {
		std::cout << (int)(c);
	}
	std::cout << std::endl;
}

std::string cipher(const std::string &str, const bool &toEncrypt) {
	int num;
	int maxRange = 10;
	if(toEncrypt) {
		do {
			num = rand() % maxRange;
		} while ( num == 0 );
	}
	if ( !toEncrypt ) {
		num = -str[ 0 ];
	}
	std::string out = std::to_string( num );
	std::string strCopy;
	if(!toEncrypt) {
		strCopy = str.substr(1);
	} else {
		strCopy = str;
	}
	for ( auto c : strCopy ) {
		out += c + num;
	}
	return out;
}

bool testCipher(const std::string &password, const bool &toEncrypt) {
	std::string ciphered = cipher(password, toEncrypt);
	return password == cipher(ciphered, !toEncrypt);
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
	if(toEncrypt) {
		std::cout << "Pass in the password for the application." << std::endl;
		std::cin >> password;
	} else {
		passwordFile >> password;
	}
	std::string cipheredPassword = cipher(password, toEncrypt);
	passwordFile.close();
	if(toEncrypt) {
		std::ofstream passwordFileO;
		passwordFileO.open(application + ".txt");
		passwordFileO << cipheredPassword;
		passwordFileO.close();
	} else {
		std::cout << "Your password is: " << cipheredPassword << std::endl;
	}
	if(testCipher(password, toEncrypt)) {
		std::cout << "This password is correct!" << std::endl;
	} else {
		std::cout << "This password is wrong!" << std::endl;
	}
	return 0;
}
