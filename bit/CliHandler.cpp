#include "CliHandler.h"

CliHandler::CliHandler(int argc, char** argv)
	:argc(argc), argv(argv)
{
	parseAndExecute();
}

int CliHandler::parseAndExecute()
{
    app.add_flag_function("-v, --version", [this](std::int64_t) { showVersion(); }, "show the version of bit");
    
    //handling the init command
    CLI::App* init = app.add_subcommand("init", "Initializes the bit repository");
    init->callback([this]() {
        handleInit();
        });
    
    //handling the add command
    CLI::App* add = app.add_subcommand("add", "Stages the changes to staging area");
    std::vector<std::string> filePaths;
    add->add_option("filePaths", filePaths, "the file paths which are to be staged")->required();
    add->callback([this,&filePaths]() {                          //pass reference not the copy of variables.
        handleAdd(filePaths);
        });

    //handling the commit command
    CLI::App* commit = app.add_subcommand("commit", "commit the changes in the staging area");
    std::string message;
    commit->add_option("message", message, "the message for the commit")->required();
    commit->callback([this, &message]() {
        handleCommit(message);
        });

    //handling the checkout command
    CLI::App* checkout = app.add_subcommand("checkout", "chekout to a given commit");
    std::string commitSHA;
    checkout->add_option("commitSHA", commitSHA, "the SHA1 hash of that commit where you want to checkout")->required();
    checkout->callback([this, &commitSHA]() {
        handleCheckout(commitSHA);  
        });

    //handling the status command
    CLI::App* status = app.add_subcommand("status", "gives the staus of the working directory wrt repository");
    status->callback([this]() {
        handleStatus();
        });

    //handling the log command
    CLI::App* log = app.add_subcommand("log", "gives the log data of commit");
    log->callback([this]() {
        handleLog();
        });

    //handling the ls command
    CLI::App* ls = app.add_subcommand("ls", "shows all the files in the bit repository");
    ls->callback([this]() {
        handleLs();
        });


    try {
        CLI11_PARSE(app, argc, argv);
    }
    catch (const CLI::Error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return app.exit(e);
        std::cout << "error in cli";
    }
    return 0;
}

void CliHandler::showVersion()
{  
     std::cout << "bit version 1.0.0" << std::endl;
     std::exit(0);	
}

void CliHandler::handleAdd(std::vector<std::string> filePaths)
{
    /*for (auto& entry : filePaths) {
        std::cout << entry << std::endl;
    }*/   
    bitRepository.add(filePaths);
}

void CliHandler::handleCommit(std::string message)
{
    bitRepository.commit(message);
}

void CliHandler::handleCheckout(std::string commitSHA)
{
    bitRepository.checkout(commitSHA);
}

void CliHandler::handleStatus()
{
    bitRepository.status();
}

void CliHandler::handleInit()
{
    bitRepository.init();
}

void CliHandler::handleLog()
{
    bitRepository.logCommits();
}

void CliHandler::handleLs()
{
    bitRepository.ls();
}
