#ifndef BITREPOSITORY_H
#define BITREPOSITORY_H
#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "Blob.h"
#include "Tree.h"
#include "Commit.h"

class BitRepository {
private:
	 const std::string repositoryPath = ".bit";
	 std::filesystem::path currentDir = std::filesystem::current_path();

public:
	 void init();
	 void add(std::vector <std::string> filePaths);
	 void commit(const std::string& message);
	 void checkout(const std::string& commitSHA);
	 bool status(); //check the staus of the repo and return whether it has changes or not
	 bool checkBitRepository();
	 void logCommits();
	 void ls();

	 
};
#endif // BITREPOSITORY_H