#include <vector>
#include <string>
#include <iostream>

std::string processName(std::string name);// Convert name into equivalent name for comparison (e.g., "Jones" -> "cmc", Johns -> "cmc")

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "Usage: " << argv[0] << " <name>" << std::endl;
        return 1;
    }

    std::vector<std::string> inputtedNames;
    std::vector<std::string> processedNames;

    std::string nameBuffer;


    while (getline(std::cin, nameBuffer))// For each line in the inputted file
    {
        if (nameBuffer.empty())
        {
            break;// If manually entering names through command line, empty line ends user input
        }

        inputtedNames.push_back(nameBuffer);// Read the name into the vector (used to print out non-processed names if match found)

        processedNames.push_back(processName(nameBuffer));// Generate list of processed names for comparisons
    }

    for (int arg = 1; arg < argc; arg++)
    {
        nameBuffer = argv[arg];

        std::cout << nameBuffer << ": ";

        nameBuffer = processName(nameBuffer);

        bool firstName = true;

        for (unsigned int i = 0; i < processedNames.size(); i++)// Compare the processed command line name with each processed name from input file
        {
            if (nameBuffer.compare(processedNames.at(i)) == 0)
            {
                if (firstName == true)
                {
                    firstName = false;
                }
                else
                {
                    std::cout << ", ";
                }
                std::cout << inputtedNames.at(i);// Print out unprocessed name for each match
            }
        }
        std::cout << std::endl;
    }
    return 1;
}

std::string processName(std::string name)
{
    std::string processedNameBuffer;

    for (unsigned int charIndex = 0; charIndex < name.size(); charIndex++)// This seems hacky.  Two loops, read then process?  That seems inefficient (although it really isn't)
    {
        char character = name.at(charIndex);

        if (character >= 'A' && character <= 'z')// Character ignored if non-alphabetical
        {
            if (character <= 'Z')
            {
                character += ('a' - 'A');// Case is not significant, so convert all chars to lower case
            }

            if (charIndex == 0 || ( character != 'a' &&
                                    character != 'e' &&
                                    character != 'i' &&
                                    character != 'h' &&
                                    character != 'o' &&
                                    character != 'u' &&
                                    character != 'w' &&
                                    character != 'y'))// Ignore these characters if not first letter
            {

                switch (character)// Convert equivalent characters to "set value" (first character of that set)
                {
                    case 'a':// Set 'a'
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        character = 'a';
                        break;
                    case 'c':// Set 'c'
                    case 'g':
                    case 'j':
                    case 'k':
                    case 'q':
                    case 's':
                    case 'x':
                    case 'y':
                    case 'z':
                        character = 'c';
                        break;
                    case 'b':// Set 'b'
                    case 'f':
                    case 'p':
                    case 'v':
                    case 'w':
                        character = 'b';
                        break;
                    case 'd':// Set 'd'
                    case 't':
                        character = 'd';
                        break;
                    case 'm':// Set 'm'
                    case 'n':
                        character = 'm';
                        break;
                    default:// For 'h', 'l' and 'r' just put the actual character in
                        break;
                }
                if ((processedNameBuffer.empty() == true) || (character != processedNameBuffer.at(processedNameBuffer.size() - 1)))// Remove repeat occurences of equivalent letters
                // Could use processedNameBuffer.back() but unsure if you are using C++11 so this is safer
                {
                    processedNameBuffer += character;
                }
            }
        }
    }
    return processedNameBuffer;
}

