#include <iostream>
using std::cin;
using std::cout;
using std::string;

void getDetails (string&, string&, string&, string&);
void printStory (string&, string&, string&, string&);

int main () {
    string noun, verb, adjective, adverb;
    // get the details 
    getDetails (noun, verb, adjective, adverb);
    // print the details 
    printStory(noun, verb, adjective, adverb);    
    return 0;
}

void getDetails (string& noun, string& verb,
                string& adj, string& adverb) {
    cout << "Enter a noun: ";
    cin >> noun;
    cout << "\nEnter a verb: ";
    cin >> verb;
    cout << "\nEnter an adjective: ";
    cin >> adj;
    cout << "\nEnter an adverb: ";
    cin >> adverb;
}

void printStory (string& noun, string& verb,
    string& adj, string& adverb) {
    cout << "Do you " << verb << " your " << adj << " " << \
        noun << " " << adverb << "? That's hilarious!" << std::endl;       
}        