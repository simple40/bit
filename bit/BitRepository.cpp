#include "BitRepository.h"

void BitRepository::init()
{
	if (std::filesystem::exists(repositoryPath)) {
		std::cerr << "Error: Repository already exists." << std::endl;
	}
	else {
		if (std::filesystem::create_directory(repositoryPath)) {
			std::cout << "bit initialized successfully" << std::endl;
		}
		else {
			std::cerr << "Error: Failed to initialze bit" << std::endl; 
		}
	}
}

void BitRepository::add(std::vector <std::string> filePaths)
{
	/*std::string repoPath = "D:/bit_test_eg/";
	for (const auto& entry : filePaths) {
		
		
		if (!std::filesystem::exists(repoPath + entry)) {
			if (entry == ".")
				continue;
			std::cerr << "Error the file " << entry << "doesn't exists" << std::endl;
			return;
		}
	}*/
	Tree tree;
	tree.status();
	tree.stageFile(filePaths);
}


void BitRepository::commit(const std::string& message)
{
	if (!checkBitRepository()) {
		std::cerr << "Bit repository not initialized " << std::endl << "Initialze bit repository with \"bit init\"" << std::endl;
		return ;
	}
	Commit commit;
	commit.makeCommit(message);
}

void BitRepository::checkout(const std::string& commitSHA)
{
	if (!checkBitRepository()) {
		std::cerr << "Bit repository not initialized " << std::endl << "Initialze bit repository with \"bit init\"" << std::endl;
		return ;
	}
	std::filesystem::path unBlobPath = "D:/bit_test_eg_unblob";
	Commit commit;
	std::cout << "inside checkout" << std::endl;
	commit.checkout(commitSHA, currentDir);
}


bool BitRepository::status()
{
	if (!checkBitRepository()) {
		std::cerr << "Bit repository not initialized " << std::endl << "Initialze bit repository with \"bit init\"" << std::endl;
		return false;
	}
	Tree tree;
	tree.status();
	tree.displayStatus();
	return false;
}

bool BitRepository::checkBitRepository()
{
	if (std::filesystem::exists(repositoryPath)) {
		return true;
	}
	return false;
}

void BitRepository::logCommits()
{
	
	Commit commit;
	commit.logCommits();
}

void BitRepository::ls()
{
	std::filesystem::path indexPath = repositoryPath + "/INDEX";
	nlohmann::json indexData = Tree::traverseTree(indexPath);
	for (const auto& entry : indexData) {
		std::string fileName = entry["fileName"];
		std::cout << fileName << std::endl;
	}
}
