#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>

#include "openssl/sha.h"
#include "zlib.h"
#include "json.hpp" 
#include "Blob.h"
#include "SHA1Generator.h"
#include "Tree.h"


class Commit {
public:
	Commit();
	std::string commitSHA;
	void checkout(const std::string& commitSHA, std::filesystem::path destPath);
	std::string makeCommit(const std::string& message);
	std::string status();
	void logCommits();
	

private:
	
	std::string makeRootTree();
	void updateHead(std::string commitSHAHash);
	std::string readHead();
	nlohmann::json readCommit(const std::string& commitHash);
	void updateIndex(); //updates the repo sha in the index
};
