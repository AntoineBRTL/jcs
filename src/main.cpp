#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

class Compiler
{
    private:
        std::string entryFilePath;

    public:
        Compiler(char ** argv)
        {
            this->entryFilePath = std::filesystem::current_path().string() + "\\" + argv[1];
        }

        std::string compile()
        {
            std::string result;
            std::ifstream file;
            file.open(this->entryFilePath);

            std::string *className = new std::string("");

            for(std::string line; std::getline(file, line);)
            {
                bool *isClassPreDefinition = new bool(line.find("class") != std::string::npos);
                bool *isStatic = new bool(line.find("static") != std::string::npos);

                // comments remover
                if(int index = line.find("//")) line = line.substr(0, index);
                if(line.find_first_not_of('\t') == std::string::npos || line.find_first_not_of(' ') == std::string::npos) continue;

                std::istringstream iterableLine(line);
                std::string *word = new std::string("");
                while(std::getline(iterableLine, *word, ' '))
                {

                    // ACCESS MODIFIERS
                    if(*word == "public")
                        // everything is public in js
                        continue;

                    if(*word == "protected")
                        continue;

                    if(*word == "private")
                    {
                        continue;
                    }

                    if(*word == "static" && *isClassPreDefinition)
                        continue;

                    // TYPES
                    if(*word == "void")
                        continue;
                    
                    if(*word == "int")
                        continue;

                    if(*word == "String")
                        continue;

                    if(*word == "bool")
                        continue;

                    // KEYWORDS
                    if(*word == "class")
                    {
                        result += "class ";
                        continue;
                    }

                    if(*word == "extends")
                    {
                        result += "extends ";
                        continue;
                    }

                    if(*isClassPreDefinition)
                    {
                        className = new std::string(word->c_str());
                    }

                    if(word->find(*className) != std::string::npos && !*isClassPreDefinition && !*isStatic)
                    {
                        result += "constructor()";
                        continue;
                    }

                    result += *word + " ";
                }
                result += "\n";
            }

            file.close();

            return result;
        }
};

int main(int argc, char ** argv)
{
    /**
     * Check whenever there are required arguments
     * Note that the first element of argv is the command itself
     */ 
    if(argc == 1)
    {
        std::cout << "jcs: " << "\033[31m" << "fatal error: " << "\033[0m" << "no input files" << std::endl;
        return -1;
    }

    // we can now compile the file which is supposed to be the first argument
    Compiler compiler(argv);
    std::string compiled = compiler.compile();
    // write compiled to .js file
    std::ofstream file;
    file.open(argv[2]);
    file << compiled << "Main.Main();";
    file.close();

    return 0;
}