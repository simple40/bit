#include "Commit.h"

Commit::Commit()
{
    /*commitSHA = makeCommit(message);
    updateHead(commitSHA);*/
}

void Commit::checkout(const std::string& commitSHA, std::filesystem::path destPath)
{
    nlohmann::json commitJsonData = readCommit(commitSHA);
    std::string rootTreeSHA = commitJsonData["rootTree"];
    std::cout << "inside commit chekout" << std::endl;
    Tree tree;
    tree.makeRepository(rootTreeSHA, destPath);
}

std::string Commit::makeCommit(const std::string& message)
{
    std::filesystem::path indexPath = ".bit/INDEX";
    nlohmann::json indexData = Tree::traverseTree(indexPath);
    if (indexData.empty()) {
        std::cout << "nothing to commit, staging area is empty" << std::endl;
        return "";
    }
    Tree tree;
    std::string rootSHA = tree.makeTrees(indexData);
    std::cout << "after Make trees" << std::endl;
    if (rootSHA.size() == 0) {
        std::cerr << "Error: Failed to save root file" << std::endl;
        return "";
    }
    //make a json for commit than hash it and store it 
    auto now = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = {};
    localtime_s(&localTime, &currentTime);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%d/%m/%y");
    std::string formattedDate = oss.str();

    nlohmann::json commit;
    commit["message"] = message;
    commit["type"] = "commit";
    commit["date"] = formattedDate;
    commit["rootTree"] = rootSHA;
    if (std::filesystem::exists(".bit/HEAD")) {
        std::ifstream headFile(".bit/HEAD");
        if (!headFile.is_open()) {
            std::cerr << "Error: Failed to open HEAD" << std::endl;
            return "";
        }
        std::string parentSHA;
        headFile >> parentSHA;
        commit["parent"] = parentSHA;
    }

    std::string commitDataString = commit.dump(4);
    std::vector<char> commitDataVector(commitDataString.c_str(), commitDataString.c_str() + commitDataString.size() + 1);
    std::string commitSHA = SHA1Generator(commitDataVector);

    std::filesystem::path objectPath = ".bit/objects/";
    std::ofstream commitFile(objectPath.string() + commitSHA, std::ios::binary);
    if (!commitFile.is_open()) {
        std::cerr << "Error: Failed to save commit" << std::endl;
        return "";
    }
    commitFile << commit.dump(4);
    commitFile.close();
    std::cout << "commit successfull: " << commitSHA << std::endl;
    updateHead(commitSHA);
    updateIndex();
    return commitSHA;
}

std::string Commit::status()
{
    return std::string();
}

void Commit::logCommits()
{
    std::string commitSHA = readHead();
    while (commitSHA.size() > 0) {
        nlohmann::json commitData = readCommit(commitSHA);
        
        std::string commitMessage = commitData["message"];
        std::string commitDate = commitData["date"];
        std::cout << "commit:  " << commitSHA << std::endl;
        std::cout << "message: " << commitMessage << std::endl;
        std::cout << "date:    " << commitDate << std::endl << std::endl;
        if (!commitData.contains("parent")) {
            break;
        }
        commitSHA = commitData["parent"];
    }
}

std::string Commit::makeRootTree()
{
    std::filesystem::path indexPath = ".bit/INDEX";
    std::ifstream indexFile(indexPath.string());
    if (!indexFile.is_open()) {
        std::cerr << "Error: Failed to open the index file " << std::endl;
        return "";
    }

    std::string jsonString;
    nlohmann::json indexData;
    try {
        indexData = nlohmann::json::parse(indexFile);
        jsonString = indexData.dump();
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing json: " << e.what() << std::endl;
        return "";
    }
    indexFile.close();
    std::vector<char> indexVector(jsonString.c_str(), jsonString.c_str() + jsonString.size() + 1);
    std::string indexSHA = SHA1Generator(indexVector);

    std::filesystem::path objectPath = ".bit/objects/";
    std::ofstream rootTree(objectPath.string() + indexSHA, std::ios::binary);
    if (!rootTree.is_open()) {
        std::cerr << "Error: Failed to save root tree" << std::endl;
        return "";
    }
    rootTree << indexData.dump(4);
    std::cout << "root tree saved to: " << objectPath << std::endl;
    rootTree.close();
    return indexSHA;
}

void Commit::updateHead(std::string commitSHAHash)
{
    std::ofstream headFile(".bit/HEAD");
    if (!headFile.is_open()) {
        std::cout << "Error: Failed to create HEAD" << std::endl;
        return;
    }
    //std::cout << commitSHAHash << "update head" << std::endl;
    headFile << commitSHAHash;
    headFile.close();
}

std::string Commit::readHead()
{
    std::filesystem::path headPath = ".bit/HEAD";
    std::ifstream headFile(headPath.string());
    if (!headFile.is_open()) {
        std::cerr << "Error: Failed to open HEAD" << std::endl;
        return "";
    }
    std::string headCommitSHA;
    headFile >> headCommitSHA;

    return headCommitSHA;
}

nlohmann::json Commit::readCommit(const std::string& commitHash)
{
    std::filesystem::path objectPath = ".bit/objects/";
    std::ifstream commitFile(objectPath.string() + commitHash);
    if (!commitFile.is_open()) {
        std::cerr << "Error: Failed to open the commit" << std::endl;
        return nlohmann::json();
    }
    nlohmann::json commitJson;
    try {
        commitJson = nlohmann::json::parse(commitFile);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing json" << e.what() << std::endl;
        return nlohmann::json();
    }

    return commitJson;
}

void Commit::updateIndex()
{
    std::cout << "updating index"<<std::endl;
    std::filesystem::path indexPath = ".bit/INDEX";
    nlohmann::json indexData = Tree::traverseTree(indexPath);
    nlohmann::json newIndexData;
    for (auto& entry : indexData) {
        if (entry["stageSHA"] != "") {
            nlohmann::json fileData;
            std::string stageSHA = entry["stageSHA"];
            std::string fileName = entry["fileName"];
            std::string action = entry["action"];
            
            fileData["stageSHA"] = stageSHA;
            fileData["repSHA"] = stageSHA;
            fileData["fileName"] = fileName;
            fileData["action"] = "committed";
            newIndexData.push_back(fileData);
        }
        
    }
    std::cout << newIndexData.dump(4);
    std::ofstream indexFile(indexPath.string(), std::ios::binary);
    if (!indexFile.is_open()) {
        std::cout<<"Error: Failed to update index" << std::endl;
        return;
    }
    try {
        indexFile << newIndexData.dump(4);
        std::cout << "written" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error: Failed to update and write index" << std::endl;
    }
    indexFile.close();
}
