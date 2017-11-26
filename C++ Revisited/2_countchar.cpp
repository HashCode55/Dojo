#include <iostream>

/*
    Well, turns out cin does not proceed until the user enters atleast one character 
*/

int main () {
    std::string name;
    std::cout << "What is the input string? ";    
    getline(std::cin, name);
    // keep asking until the user enters a valid string.
    while (name.size() == 0) {
        std::cout << "You cannot enter an empty string." << std::endl;
        getline(std::cin, name);        
    }
    std::cout << name << " has " << name.length() << " characters." << std::endl;
    return 0;
}