#include "SHA1Generator.h"

std::string SHA1Generator(std::vector<char> contentBytes) {
	try {
		unsigned char hash[SHA_DIGEST_LENGTH];
		SHA1(reinterpret_cast<unsigned char*>(contentBytes.data()), contentBytes.size(), hash);//ERROR HERE
		std::ostringstream hashStream;
		for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
			hashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
		}
		std::string sha1_hash = hashStream.str();
		std::cout << sha1_hash << std::endl;
		return sha1_hash;
	}
	catch (...) {
		std::cerr << "Exveption" << std::endl;
		return "-1";
	}
}
