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

            std::vector<std::string> *declaredTypes = new std::vector<std::string>();

            std::string *className = new std::string("");

            for(std::string line; std::getline(file, line);)
            {
                bool *isStatic = new bool(line.find("static") != std::string::npos);
                bool *isClassPreDefinition = new bool(line.find("class") != std::string::npos);
                bool *isCreatingInstance = new bool(false);
                bool *isUsingExtends = new bool(false);
                bool *hasAccessModifiers = new bool(false);

                // comments remover
                if(int index = line.find("//")) line = line.substr(0, index);
                if(line.find_first_not_of('\t') == std::string::npos || line.find_first_not_of(' ') == std::string::npos) continue;

                std::istringstream iterableLine(line);
                std::string *word = new std::string("");
                while(std::getline(iterableLine, *word, ' '))
                {
                    if(*isClassPreDefinition)
                    {
                        // ACCESS MODIFIERS
                        if(*word == "public")
                            continue;

                        if(*word == "protected")
                            continue;

                        if(*word == "private")
                            continue;

                        // KEYWORDS
                        if(*word == "static")
                            continue;
                        
                        if(*word == "extends")
                        {
                            continue;
                            *isUsingExtends = true;
                        }

                        if(*word == "class")
                        {
                            result += "class ";
                            continue;
                        }
                        
                        if(!*isUsingExtends)
                        {
                            const char* sc = word->c_str();
                            declaredTypes->push_back(sc);
                            className = new std::string(sc);
                        }
                    }
                    else
                    {
                        // ACCESS MODIFIERS
                        if(*word == "public")
                        {
                            *hasAccessModifiers = true;
                            continue;
                        }

                        if(*word == "protected")
                        {
                            *hasAccessModifiers = true;
                            continue;
                        }

                        if(*word == "private")
                        {
                            *hasAccessModifiers = true;
                            continue;
                        }

                        // TYPES
                        if(!*isCreatingInstance)
                        {
                            if(*word == "void")
                            {
                                if(!*isStatic && !*hasAccessModifiers) result += "let ";
                                continue;
                            }
                                
                            if(*word == "int")
                            {
                                if(!*isStatic && !*hasAccessModifiers) result += "let ";
                                continue;
                            }

                            if(*word == "String")
                            {
                                if(!*isStatic && !*hasAccessModifiers) result += "let ";
                                continue;
                            }

                            if(*word == "bool")
                            {
                                if(!*isStatic && !*hasAccessModifiers) result += "let ";
                                continue;
                            }

                            // custom types
                            bool hasRemoveType = false;
                            for(int i = 0; i < declaredTypes->size(); i++)
                            {
                                std::cout << word->find(declaredTypes->operator[](i)) << "\t" << *word << std::endl;
                                if(*word == declaredTypes->operator[](i))
                                {
                                    if(!*isStatic && !*hasAccessModifiers) result += "let ";
                                    hasRemoveType = true;
                                    break;
                                }
                            }

                            if(hasRemoveType) continue;
                        }

                        // KEYWORDS
                        if(*word == "new")
                        {
                            *isCreatingInstance = true;
                            result += "new ";
                            continue;
                        }

                        if(word->find(*className) != std::string::npos && !*isClassPreDefinition && !*isStatic)
                        {
                            result += "constructor()";
                            continue;
                        }
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