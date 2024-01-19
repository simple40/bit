#include "Tree.h"

Tree::Tree()
{
    //makeTree(path, isRootDir);
	//stageFile(path);
}

nlohmann::json Tree::traverseTree(const std::string& treeHash)
{
	std::filesystem::path objectPath = ".bit/objects/tree/";
	std::ifstream treeFile(objectPath.string() + treeHash);
	if (!treeFile.is_open()) {
		std::cerr << "Error: Failed to open the tree"<< treeHash << std::endl;
		return nlohmann::json();
	}
	nlohmann::json treeJson;
	try{
		treeJson = nlohmann::json::parse(treeFile);
	}
	catch(const std::exception& e) {
		std::cerr << "Error parsing json" << e.what() << std::endl;
		return nlohmann::json();
	}
	
	return treeJson;
}

nlohmann::json Tree::traverseTree(const std::filesystem::path treePath)
{
	std::ifstream treeFile(treePath.string());
	if (!treeFile.is_open()) {
		std::cerr << "Error: Failed to open the tree" << std::endl;
		return nlohmann::json();
	}
	nlohmann::json treeJson;
	try {
		treeJson = nlohmann::json::parse(treeFile);
	}
	catch (const std::exception& e) {
		std::cerr << "Error parsing json" << e.what() << std::endl;
		return nlohmann::json();
	}
	treeFile.close();
	return treeJson;
}



//std::string Tree::makeTree(const std::string& path, const bool& isRootDir)
//{
//	nlohmann::json indexData;
//	
//	if (!std::filesystem::exists(path)) {
//		std::cerr << "Error: Directory doesn't exists" << std::endl;
//	}
//	for (const auto& entry : std::filesystem::directory_iterator(path)) {
//		if (std::filesystem::is_regular_file(entry)) {
//			Blob blob(entry.path().string());
//			blob.makeBlob();
//			nlohmann::json blobData;
//			blobData["type"] = "blob";
//			blobData["shaHash"] = blob.sha1_hash;
//			blobData["fileName"] = entry.path().filename().string();
//			indexData.push_back(blobData);
//		}
//		else {
//			std::string treeHash = makeTree(entry.path().string(), false);
//			nlohmann::json treeData;
//			treeData["type"] = "tree";
//			treeData["shaHash"] = treeHash;
//			treeData["fileName"] = entry.path().filename().string();
//			indexData.push_back(treeData);
//		}
//		
//	}
//	
//	if (isRootDir) {
//		std::filesystem::path indexPath = ".bit/";
//		std::filesystem::create_directory(indexPath);
//		std::ofstream indexFile(indexPath.string() + "INDEX", std::ios::out);
//		if (!indexFile.is_open()) {
//			std::cerr << "Error: Failed to save index" << std::endl;
//		}
//		indexFile <<  indexData.dump(4);
//		std::string shaHash = indexData.dump();
//		std::vector <char> shaVector(shaHash.c_str(), shaHash.c_str() + shaHash.size() + 1);
//		std::string sha1_hash = SHA1Generator(shaVector);
//		indexFile.close();
//		return sha1_hash;
//	}
//	else {
//		std::filesystem::path objectPath = ".bit/objects/";
//		//std::cout << objectPath << std::endl;
//		std::filesystem::create_directory(objectPath);
//		std::string shaHash = indexData.dump();
//		std::vector <char> shaVector(shaHash.c_str(), shaHash.c_str() + shaHash.size() + 1);
//		std::string sha1_hash = SHA1Generator(shaVector);
//		std::ofstream objectFile(objectPath.string() + sha1_hash, std::ios::binary);
//		if (objectFile.is_open()) {
//			objectFile << indexData.dump(4);
//			std::cout << "tree saved to: " << objectPath << std::endl;
//		}
//		else {
//			std::cerr << "Error: Failed to save blob" << std::endl;
//		}
//		return sha1_hash;
//	}
//    
//}


//void Tree::stageFile(std::vector <std::string> filePaths)
//{
//	std::filesystem::path indexPath = ".bit/INDEX";
//	nlohmann::json oldIndexData = traverseTree(indexPath);
//	//std::cout << oldIndexData.dump(4);
//	std::ofstream indexFile(indexPath.string(), std::ios::binary);
//	if (!indexFile.is_open()) {
//		std::cerr << "Error: Failed to open INDEX file" << std::endl;
//		return;
//	}
//	nlohmann::json newIndexData;
//
//	std::string repoPath = "D:/bit_test_eg/";
//
//	auto it = std::find(filePaths.begin(), filePaths.end(), ".");
//	if (it != filePaths.end()) {
//		//all the files will be staged
//		for (const auto& entry : std::filesystem::recursive_directory_iterator(repoPath)) {
//			if (std::filesystem::is_directory(entry)) {
//				continue;
//			}
//			std::filesystem::path relativePath = std::filesystem::relative(entry.path(), repoPath);
//			//std::cout << entry.path().string() << std::endl; //here instead of entry relative path will be here, configure it when the cli is been setup such that it will take the relative path from the working repository where bit is working
//			//std::cout << relativePath.parent_path().string() << std::endl;
//			Blob blob(entry.path().string());
//			blob.makeBlob();
//			nlohmann::json blobData;
//			blobData["fileName"] = relativePath.string();
//			blobData["stageSHA"] = blob.sha1_hash;
//
//			auto it = std::find_if(oldIndexData.begin(), oldIndexData.end(),
//				[&](const nlohmann::json& entry) {
//					return entry["fileName"] == relativePath.string();
//				});
//			if (it != oldIndexData.end()) {
//				// Found the target entry
//				if ((*it).contains("repSHA")) {
//					std::string repSHA = (*it)["repSHA"];
//					blobData["repSHA"] = repSHA;
//					std::cout << "REP SHA ADDED" << std::endl << std::endl;
//				}	 
//			}
//	
//			newIndexData.push_back(blobData);
//		}
//	}
//	else {
//		for (const auto& entry : filePaths) {
//			//only given files will be staged   update this as this overrites and only the file given are in index
//			Blob blob(repoPath + entry);
//			blob.makeBlob();
//			nlohmann::json blobData;
//			blobData["fileName"] = entry;
//			blobData["stageSHA"] = blob.sha1_hash;
//
//			auto it = std::find_if(oldIndexData.begin(), oldIndexData.end(),
//				[&](const nlohmann::json& node) {
//					return node["fileName"] == entry;
//				});
//			if (it != oldIndexData.end()) {
//				// Found the target entry
//				std::cout << "updating stageSHA" << std::endl;
//				(*it)["stageSHA"] = blob.sha1_hash;
//			}
//			else {
//				nlohmann::json blobData;
//				blobData["fileName"] = entry;
//				blobData["stageSHA"] = blob.sha1_hash;
//				oldIndexData.push_back(blobData);
//			}
//			//newIndexData.push_back(blobData);
//		}
//		newIndexData = oldIndexData;
//	}
//
//	
//	try {
//		indexFile << newIndexData.dump(4);
//	}
//	catch (std::exception& e) {
//		std::cerr << "Error: Failed to write INDEX- " << e.what() << std::endl;
//	}
//}

void Tree::stageFile(std::vector <std::string> filePaths) {
	nlohmann::json IndexData = traverseTree(indexPath);
	//std::cout << oldIndexData.dump(4);
	std::ofstream indexFile(indexPath.string(), std::ios::binary);
	if (!indexFile.is_open()) {
		std::cerr << "Error: Failed to open INDEX file" << std::endl;
		return;
	}
	nlohmann::json newIndexData;

	std::string repoPath = currentDir.string() + "\\";

	auto it = std::find(filePaths.begin(), filePaths.end(), ".");
	if (it != filePaths.end()) {

		for (auto& entry : modifiedFiles) {
			Blob blob(repoPath + entry.first);
			blob.makeBlob();

			auto it = std::find_if(IndexData.begin(), IndexData.end(),
				[&](const nlohmann::json& node) {
					return node["fileName"] == entry.first;
				});
			if (it != IndexData.end()) {
				// Found the target entry
				std::cout << "updating stageSHA" << std::endl;
				(*it)["stageSHA"] = blob.sha1_hash;
				(*it)["action"] = "modified";
			}
		}

		for (auto& entry : newFiles) {
			Blob blob(repoPath + entry.first);
			blob.makeBlob();

			nlohmann::json blobData;
			blobData["fileName"] = entry.first;
			blobData["stageSHA"] = blob.sha1_hash;
			blobData["action"] = "new file";
			IndexData.push_back(blobData);
		}

		for (auto& entry : deletedFiles) {
			auto it = std::find_if(IndexData.begin(), IndexData.end(),
				[&](const nlohmann::json& node) {
					return node["fileName"] == entry.first;
				});
			if (it != IndexData.end()) {
				// Found the target entry
				std::cout << "deleting stageSHA" << std::endl;
				(*it)["stageSHA"] = "";
				(*it)["action"] = "deleted";
			}
		}

	}
	else {
		for (auto& entry  : filePaths) {
			std::string path = convert_slashes(entry);
			std::cout << "inside else of stage function "<< entry << std::endl;
			for (auto& entryn : modifiedFiles) {
				std::cout << entryn.first << std::endl;
			}
			if(modifiedFiles.count(path) > 0) {
				std::cout << "modified" << std::endl;
				Blob blob(repoPath + path);
				blob.makeBlob();

				auto it = std::find_if(IndexData.begin(), IndexData.end(),
					[&](const nlohmann::json& node) {
						return node["fileName"] == path;
					});
				if (it != IndexData.end()) {
					// Found the target entry
					std::cout << "updating stageSHA" << std::endl;
					(*it)["stageSHA"] = blob.sha1_hash;
					(*it)["action"] = "modified";
				}
			}

			else if (newFiles.count(path) > 0) {
				std::cout << "new files" << std::endl;
				Blob blob(repoPath + path);
				blob.makeBlob();

				nlohmann::json blobData;
				blobData["fileName"] = path;
				blobData["stageSHA"] = blob.sha1_hash;
				blobData["action"] = "new file";
				IndexData.push_back(blobData);
			}

			else if (deletedFiles.count(path) > 0) {
				std::cout << "deleted" << std::endl;
				auto it = std::find_if(IndexData.begin(), IndexData.end(),
					[&](const nlohmann::json& node) {
						return node["fileName"] == path;
					});
				if (it != IndexData.end()) {
					// Found the target entry
					std::cout << "deleting stageSHA" << std::endl;
					(*it)["stageSHA"] = "";
					(*it)["action"] = "deleted";
				}
			}

			else {
				std::cerr << "Error: The file" << path << "isn't changes or doesn't exist" << std::endl;
			}
		}
	}
	try {
		indexFile << IndexData.dump(4);
	}
	catch (std::exception& e){
		std::cerr << "Error: Failed to stage data in INDEX: " << e.what() << std::endl;
	}
}


void Tree::makeRepository(std::string& treeSHA, std::filesystem::path destPath)
{
	nlohmann::json treeData = traverseTree(treeSHA);
	for (const auto& entry : treeData) {
		if (entry["type"] == "blob") {
			std::string blobSHA = entry["shaHash"];
			std::string fileName = entry["fileName"];
			Blob blob(objectsPath.string()+"/" + blobSHA);
			blob.unBlob(destPath.string()+ "/" + fileName);
		}
		else {
			std::string folderName = entry["fileName"];
			std::string treeSHA = entry["shaHash"];
			std::filesystem::path newDestPath = destPath.string() + "/" + folderName;
			std::filesystem::create_directory(newDestPath);
			makeRepository(treeSHA, newDestPath);
		}
	}
}

bool Tree::status()
{
	nlohmann::json indexData = traverseTree(indexPath);
	if (indexData.empty()) {
		std::cout << "INDEX file is either empty or doesn't exists"
			<< std::endl << "this mean you haven't added any file to staging area" << std::endl;
	}

	//std::string repoPath = "D:/bit_test_eg/";
	std::unordered_map<std::string, std::string> newRepoMap; //maps the filePath to SHA

	for (const auto& entry : std::filesystem::recursive_directory_iterator(currentDir)) {
		if (std::filesystem::is_directory(entry) ) {
			continue;
		}
		if (entry.path().string().find(".bit") != std::string::npos) {
			continue; //skips the bit repository
		}
		std::filesystem::path relativePath = std::filesystem::relative(entry.path(), currentDir);
		Blob blob(entry.path().string());
		blob.generateCompressedSHA();
		newRepoMap[relativePath.string()] = blob.sha1_hash;
	}
	
	for (const auto& originalEntry : indexData) {
		const std::string& fileName = originalEntry["fileName"];
		const std::string& SHAhash = originalEntry["stageSHA"];
		
		if (!originalEntry.contains("repSHA")) {
			stagedNotCommited[fileName] = originalEntry["action"]; //as error will come for new staged files if I used repSHA
		}
		else if (originalEntry["stageSHA"] != originalEntry["repSHA"]) {
			//file made to staging area but not commited.
			stagedNotCommited[fileName] = originalEntry["action"];
		}

		auto newEntryIt = newRepoMap.find(fileName);
		if (newEntryIt != newRepoMap.end()) {
			if (SHAhash != newEntryIt->second) {
				//file modified.
				modifiedFiles[fileName] = SHAhash;
				notStagedFiles[fileName] = "modified";
			}
			newRepoMap.erase(newEntryIt); //mark as processed
		}
		else {
			//file removed
			deletedFiles[fileName] = "";
			notStagedFiles[fileName] = "deleted";
		}
	}

	newFiles = newRepoMap;//remaining file are new

	if (!stagedNotCommited.size() > 0)
		return true;
	return false;
}

void Tree::displayStatus()
{
	if (stagedNotCommited.size() != 0) {
		std::cout << "Changes to be committed" << std::endl;
		for (auto entry : stagedNotCommited) {
			std::cout << entry.second << "    " << entry.first << std::endl;
		}
	}
	if (modifiedFiles.size() != 0 || deletedFiles.size() != 0 || newFiles.size() != 0)
	{
		std::cout << std::endl << "Changes not staged" << std::endl;
		if (modifiedFiles.size() != 0) {
			std::cout << "modified:" << std::endl;
			for (auto entry : modifiedFiles) {
				std::cout << "  " << entry.first << std::endl;
			}
		}
		if (deletedFiles.size() != 0) {
			std::cout << "deleted:" << std::endl;
			for (auto entry : deletedFiles) {
				std::cout << "  " << entry.first << std::endl;
			}
		}
		if (newFiles.size() != 0) {
			std::cout << "new files:" << std::endl;
			for (auto entry : newFiles) {
				std::cout << "  " << entry.first << std::endl;
			}
		}
	}
	std::cout << std::endl;
}



std::string Tree::getRootFolder(const std::string& path)
{
	size_t pos = path.find('\\');
	if (pos == std::string::npos) {
		return path; // No folders found
	}
	return path.substr(0, pos);
}

std::string Tree::makeTrees(nlohmann::json indexData)
{
	std::unordered_map<std::string, nlohmann::json> subfolders;
	nlohmann::json treeData;
	for (const auto& entry : indexData) {
		std::string filePath_s = entry["fileName"];
		std::filesystem::path filePath = filePath_s;
		if (!filePath.has_parent_path())
		{
			std::string fileName = entry["fileName"];
			std::string shaHash = entry["stageSHA"];
			if (shaHash == "") {
				continue;
				//the file is deleted as stageSHA is empty.
			}
			std::string type = "blob";
			nlohmann::json blobData;
			blobData["fileName"] = fileName;
			blobData["shaHash"]  = shaHash;
			blobData["type"] = type;

			treeData.push_back(blobData);
			std::cout << fileName << std::endl;
		}
		else {
			//all the files present in a sub folder
			std::string subFolderName = getRootFolder(filePath.string());
			std::cout << subFolderName << std::endl;
			nlohmann::json subFolderFiles;		//contains the sub folder's files data and also the files inside the sub sub folder
			std::filesystem::path relativePath = filePath.lexically_relative(subFolderName);
			subFolderFiles["fileName"] = relativePath.string();
			subFolderFiles["stageSHA"] = entry["stageSHA"];
			/*if (subFolderFiles.find(subFolderName) == subFolderFiles.end()) {
				subFolderFiles[subFolderName] = nlohmann::json::array();
			}*/
			subfolders[subFolderName].push_back(subFolderFiles);  // maps the subfolderName to the json array
																  //with details of files it contains 
		}
		
	}
	// folderData will contains the data for the sub tree just like indexData but it contains only the files present 
	//in the subfolder with the removed root folder name i.e. the folderName. And recursively make the sub trees.
	for (const auto& [folderName, folderData] : subfolders) {
		nlohmann::json subTreeData;
		subTreeData["fileName"] = folderName;
		std::cout << folderName << std::endl;
		subTreeData["shaHash"] = makeTrees(folderData); 
		
		subTreeData["type"] = "tree";
		treeData.push_back(subTreeData);
		//std::cout << folderName << std::endl;
	}

	std::cout << "size = " << subfolders.size() << std::endl;
	std::filesystem::path treeObjectPath = ".bit/objects/tree/";
	std::filesystem::create_directory(treeObjectPath);
	std::string treeDataString = treeData.dump();
	//std::cout << treeDataString << std::endl;
	std::vector<char> treeVector(treeDataString.c_str(), treeDataString.c_str() + treeDataString.size() + 1);
	std::string treeSHA = SHA1Generator(treeVector);
	std::ofstream treeFile(treeObjectPath.string() + treeSHA, std::ios::binary);
	if (!treeFile) {
		std::cerr << "Error: Failed to save tree" << std::endl;
		return "";
	}

	try {
		treeFile << treeData.dump(4);
	}
	catch (std::exception& e) {
		std::cerr << "Error: Failed to write tree object- " << e.what() << std::endl;
		return "";
	}
	treeFile.close();

	return treeSHA;
}

std::string Tree::convert_slashes(const std::string& path)
{
	std::string convertedPath = path;
	std::replace(convertedPath.begin(), convertedPath.end(), '/', '\\');
	return convertedPath;
}
