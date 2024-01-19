#ifndef TREE_H
#define TREE_H

#pragma once


#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <iostream>
#include <fstream>
#include "openssl/sha.h"
#include "zlib.h"
#include "json.hpp" 
#include "Blob.h"
#include "SHA1Generator.h"

class Tree {
public:
	Tree();
	static nlohmann::json traverseTree(const std::string& treeHash);
	static nlohmann::json traverseTree(const std::filesystem::path treePath);
	std::string makeTrees(nlohmann::json treeData);
	static std::string getRootFolder(const std::string& path);
	void stageFile(std::vector <std::string> filePaths);
	void makeRepository(std::string& treeSHA, std::filesystem::path destPath);
	bool status();
	void displayStatus();

private:
	/*std::string makeTree(const std::string& path, const bool& isRootDir);*/
	std::string sha1_hash;
	nlohmann::json indexData;

	std::string convert_slashes(const std::string& path);
	

	//const bool rootDir;
	std::filesystem::path objectsPath = ".bit/objects";
	std::filesystem::path indexPath = ".bit/INDEX";
	std::filesystem::path currentDir = std::filesystem::current_path();

	std::unordered_map<std::string, std::string> stagedNotCommited;
	std::unordered_map<std::string, std::string> notStagedFiles;
	std::unordered_map<std::string, std::string> modifiedFiles;
	std::unordered_map<std::string, std::string> deletedFiles;
	std::unordered_map<std::string, std::string> newFiles;

};

#endif // TREE_H