#include <iostream>
using std::cout;
using std::cin;

int main () {
    // quote and author name 
    std::string quote, author;    
    cout << "What is the quote? ";
    // cin terminates at space 
    getline(cin, quote);
    cout << "\nWho said it? ";
    cin >> author;
    cout << "\n" << author << " says, \"" << quote << "\"" << std::endl;
    return 0;  
}