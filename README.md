# Bit Version Control System

Bit is a simple version control system implemented in C++ as a personal project to understand the principles of version control systems like Git.

## Features

- **Commit:**  Create commits with a commit message.
- **Staging:**  Stage changes before committing.
- **Checkout:**  Switch between different commits.
- **Branch:**  Branches will be added later.

## Getting Started

To get started with Bit, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/simple40/bit.git
   cd bit

2. **Build the project**
    - Open Visual Studio:
      - Choose "Open a project or solution."
      - Navigate to the Bit project directory and open the solution file (Bit.sln).
        
    - Configure Build:
      - Select the build configuration (e.g., Debug or Release) from the toolbar.
      - Right-click on the project in the Solution Explorer and select "Properties."
      - Verify and configure project settings if needed.
      - Build the Project:
    
    - Build the project:
      - by selecting "Build" > "Build Solution" from the menu.
      - Alternatively, you can use the shortcut Ctrl + Shift + B.
        
    This will compile the source code and generate the bit.exe executable.

    - Verify Build:
       - Open the Developer Command Prompt for Visual Studio.
       - Navigate to the Bit project directory.
       - Run the following command to verify the build:
         ```bash
         .x64\Debug\bit --version
         or
         .x64\Release\bit --version
         ```
    This should display the version information, confirming that the build was successful.


## Basic Commands

1. Add Changes to Staging Area

  ```bash
  bit add <file1> <file2> ...   # Add specific files
  bit add .                     # Add all changes
  ```
2. Commit Changes

  ```bash
  bit commit "Your commit message here"
  ```

3. Check Repository Status
   
```bash
bit status
```

4. View Commit History

```bash
bit log
```

5. Checkout to Previous Commit

```bash
bit checkout <commit_sha_hash>
```
6. List Files in Index

```bash
bit ls
```


Example Usage
Here's an example workflow:

```bash
# Add changes
bit add file1.txt file2.txt

# Commit changes
bit commit "Added new features"

# Check repository status
bit status

# View commit history
bit log
```

Now you're ready to start using Bit for your version control needs!

## Licensing

- Licensed under MIT [License](https://github.com/simple40/bit/blob/master/LICENSE)

             
