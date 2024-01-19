#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <iostream>
#include <fstream>
#include "openssl/sha.h"
#include "zlib.h"



class Blob {
public:
	Blob(const std::string& filePath );
	std::string sha1_hash;
	void makeBlob();
	void unBlob(const std::string& savePath);
	void generateCompressedSHA();

private:
	std::string filePath;
	std::string fileName;
	std::vector<char> contentBytes;
	
	bool readBytes();
	void compressContent();
	void decompressContent();
	void generateHash();
	
};
