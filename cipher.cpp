#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

std::string cipher(const std::string &str, const bool &toEncrypt) {
	int num;
	if(toEncrypt) {
		do {
			num = rand() % ('Z' - 'A');
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
		out += (c + num) % (128 - ' ') + ' ';
	}
	return out;
}

bool isTesting(const int &argc) {
	return argc != 1;
}

int main(int argc, char ** argv) {
	srand(time(NULL));
	std::ifstream passwordFile;
	std::string application;
	if(!isTesting(argc)) {
		std::cout << "Input the application the password is for." << std::endl;
		std::cin >> application;
	} else {
		application = argv[0];
	}
	passwordFile.open(application + ".txt");
	char encrypt;
	if(!isTesting(argc)) {
		std::cout << "Do you want to encrypt the password in the file? (Y/N)" << std::endl;
		std::cin >> encrypt;
		toEncrypt = tolower(encrypt) == 'y';
	} else {
		encrypt = argv[1];
	}
	bool toEncrypt = tolower(encrypt) == 'y';
	std::string password;
	if(toEncrypt) {
		if(!isTesting(argc)) {
			std::cout << "Pass in the password for the application." << std::endl;
			std::cin >> password;
		} else {
			password = argv[2];
		}
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
	return 0;
}
