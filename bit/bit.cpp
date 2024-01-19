
#include <iostream>
#include "Blob.h"
#include "BitRepository.h"
#include "CliHandler.h"



int main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    //BitRepository bitRepository;
    //bitRepository.init();
    //bitRepository.add("D:/bit_test_eg");
    //std::vector<std::string> paths = { "New folder/Second.txt"};
    //std::vector<std::string> paths = { "." };
    //bitRepository.add(paths);
    //bitRepository.commit("the new commit is here");
    //bitRepository.checkout("9e5a383ddd63091b45c367258f5123a571e2eae2");
    //bitRepository.status();

    CliHandler cliHandler(argc, argv);

    return 0;
}

//so implemented the mechanism to traverse down the tree for a particular file
//make something for the add method I mean the stage area do something for this like a separate file for staging area.

//so I will make a new file for staging area which will contain all the files which are to be committed 
//and the above logic will be used to traverse through the tree and update the tree.
//also in the add make something for a new sub folder 

//so staging area file will contains only the file present in the staging area 
//so if I type git status what will happen that 


//so what is happening in git is that when I put the add command then only the blob is added of in the object
//folder and corresponding index is updated.
//And the trees are made only after the commit in git.

 //(*)   //so I should update my add function and it should only make the blobs and update the corresponding index data.
 //(*)   //then commit should also be modified as the tree will be formed like that only but it will now use the index file 
         //as a data source 

// the add function are being currently made to work for whole repo but have to make it to work only for a file simple by passing the path in a vector form 

//parent path separate it from the fileName and then store all the sub directories in a vector


//so the making of trees is completed but now I have to implement the rollback feature which will use the tree objects 
//And also the status function still remains 
//so now complete the rollback and status funcition and it can be completed today itself.

//rollback is completed along with staging area
//but for the status a new approach is that:
    //# the INDEX will contain all the files present in the repository 
    //# now two more fields will be there which are
        //* stageSHA - the sha that is calculated when the file is added to the staging area
        //* repoSHA - the sha when the commit is been done
    //# and when status is called the widrSHA will be calculated for the working directory and will be compared with the two
// * if the stageSHA != repoSHA then the corresponding file is staged but not commited.
// * if the wdirSHA != stageSHA then the changes in that file is not staged and the file is modified.
// * if the corresponding fileName is not in index then that file is a new file.


// test the status function and also the commit and stage function should be modified and shoudl work only when there
    //is some changes
//design the cli and also the repoPath is to defined dynamically now.

//thinkking of a new approach for staging the files which will use status function : 
    //the status function will save the stageNotCommited, modified, newfiles and deletedFiles  map
    //now the stageFiles function will use only the files present in the above modified, newFiles and deletedFiles data
    //and I think I should also add the data like action ->(modified, newfile, deleted) to the staging area data

//Finished with the main logic 
//Finish this by making the cli andl also resolve the repo path so that it will point to the path in the opened in the cli

//MAKE THE parsers for the commit and chekout and status functions and also call the bitrepository func 
//take care of the path also now


//now will be implementing the branch for the bit
//and the diff function will just calculate the line diff only.
//so the fuck all about merge will be that first I will save the diffs of the two branch from the base commit 
//and then compare the two diffs and thats all 
//if the two diffs occur at same place than it will raise conflict, if not then automatic merge.




