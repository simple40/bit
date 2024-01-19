#include "Blob.h"

Blob::Blob(const std::string& filePath)
	:filePath(filePath)
{
	//if (readBytes()) {
	//	compressContent();
	//	generateHash();
	//	//decompressContent();
	//	//makeBlob();
	//}
	
}

bool Blob::readBytes()
{
	std::filesystem::path filepath = filePath;
	if (!std::filesystem::exists(filepath)) {
		std::cerr << "Error: " << filepath << " doesn't exists" << std::endl;
		return false;
	}
		
	fileName = filepath.filename().string();
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return false;
	}

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	contentBytes.resize(fileSize);
	if (file.read(contentBytes.data(), fileSize)) {
		file.close();
		return true;
	}
	else {
		std::cerr << "Error while reading the file "<< filePath << std::endl;
		file.close();
		return false;
	}
}

void Blob::compressContent() {
	z_stream strm = {};
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	deflateInit(&strm, Z_DEFAULT_COMPRESSION);  // Adjust compression level if needed

	strm.avail_in = contentBytes.size();
	strm.next_in = reinterpret_cast<Bytef*>(contentBytes.data());

	std::vector<char> compressedData;
	do {
		compressedData.resize(compressedData.size() + 1024);  // Adjust buffer size as needed
		strm.avail_out = 1024;
		strm.next_out = reinterpret_cast<Bytef*>(compressedData.data() + compressedData.size() - 1024);

		int ret = deflate(&strm, Z_FINISH);
		if (ret == Z_STREAM_END) {
			break;
		}
		else if (ret != Z_OK) {
			std::cerr << "Error: Compression Failed" << std::endl;
			deflateEnd(&strm);
			return;
		}
	} while (true);

	compressedData.resize(compressedData.size() - strm.avail_out);
	contentBytes = std::move(compressedData);

	deflateEnd(&strm);
}

void Blob::decompressContent()
{
	z_stream strm = {};
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	inflateInit(&strm);

	strm.avail_in = contentBytes.size();
	strm.next_in = reinterpret_cast<Bytef*>(contentBytes.data());

	std::vector<char> decompressedData;
	do {
		decompressedData.resize(decompressedData.size() + 1024); // Adjust buffer size as needed
		strm.avail_out = 1024;
		strm.next_out = reinterpret_cast<Bytef*>(decompressedData.data() + decompressedData.size() - 1024);

		int ret = inflate(&strm, Z_NO_FLUSH);
		if (ret == Z_STREAM_END) {
			break;
		}
		else if (ret != Z_OK) {
			std::cerr << "Error: Decompression Failed" << std::endl;
			inflateEnd(&strm);
			return;
		}
	} while (true);

	decompressedData.resize(decompressedData.size() - strm.avail_out);
	contentBytes = std::move(decompressedData);

	inflateEnd(&strm);
}

void Blob::generateHash()
{
	try {
		unsigned char hash[SHA_DIGEST_LENGTH];
		SHA1(reinterpret_cast<unsigned char*>(contentBytes.data()), contentBytes.size(), hash);//ERROR HERE
		std::ostringstream hashStream;
		for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
			hashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
		}
		sha1_hash = hashStream.str();
		//std::cout << sha1_hash << std::endl;
	}
	catch(...) {
		std::cerr << "Exveption" << std::endl;
	}
	
}



void Blob::makeBlob()
{
	if (!readBytes()) {
		std::cerr << "Error: Failed to read file." << std::endl;
		return;
	}
	compressContent();
	generateHash();
	std::filesystem::path objectPath = ".bit/objects/";
	//std::cout << objectPath << std::endl;
	std::filesystem::create_directory(objectPath);
	std::ofstream objectFile(objectPath.string() + sha1_hash, std::ios::binary);
	if (objectFile.is_open()) {
		objectFile.write(contentBytes.data(), contentBytes.size());
		std::cout << "blob saved to: " << objectPath <<" " <<sha1_hash << std::endl;
	}
	else {
		std::cerr << "Error: Failed to save blob" << std::endl;
	}
}

void Blob::unBlob(const std::string& savePath)
{
	//make the unblob here 
	if (!readBytes()) {
		std::cerr << "Error: Failed to read blob" << std::endl;
		return;
	}
	decompressContent();
	//std::filesystem::path unBlobPath = "D:/bit_test_eg_unblob/";
	std::ofstream file(savePath, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: Failed to save file" << std::endl;
		file.close();
		return;
	}
	//std::filesystem::path filePath = savePath;
	file.write(contentBytes.data(), contentBytes.size());
	std::cout << "write successfull to " << savePath << std::endl;
	file.close();
}

void Blob::generateCompressedSHA()
{
	if (!readBytes()) {
		std::cerr << "Error: Failed to read blob" << std::endl;
		return;
	}
	compressContent();
	generateHash();

}
