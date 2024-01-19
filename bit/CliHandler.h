#pragma once

#include <iostream>
#include <CLI11.hpp>
#include "BitRepository.h"

class CliHandler {
public:
	CliHandler(int argc, char** argv);
	int parseAndExecute();

private:
	void showVersion();
	void handleAdd(std::vector<std::string> filePaths);				//add commmand to stage the changes
	void handleCommit(std::string message);
	void handleCheckout(std::string commitSHA);
	void handleStatus();
	void handleInit();
	void handleLog();
	void handleLs();

	CLI::App app{ "bit - a git like vcs" };
	int argc;
	char** argv;
	BitRepository bitRepository;
};

