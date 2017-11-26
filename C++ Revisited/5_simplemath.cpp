#include <iostream>

#define SUM(n1, n2) (n1 + n2)
#define SUB(n1, n2) (n1 - n2)
#define MUL(n1, n2) (n1 * n2)
#define DIV(n1, n2) (n1 / n2)

using std::cin;
using std::cout;

bool isnum (int);
void getinput (int&);

int main () {
    int n1, n2;
    
    getinput(n1);
    getinput(n2);        
     
    cout << "\n" << n1 << " + " << n2 << " " << SUM(n1, n2) << " " << std::endl;
    cout << "\n" << n1 << " + " << n2 << " " << SUB(n1, n2) << " " << std::endl;
    cout << "\n" << n1 << " + " << n2 << " " << MUL(n1, n2) << " " << std::endl;
    cout << "\n" << n1 << " + " << n2 << " " << DIV(n1, n2) << " " << std::endl;
}

void getinput (int& n1) {
    while (1) {
        cout << "What is the first number? ";
        cin >> n1;
        if (!isnum(n1)) {
            cout << "Enter a number" << std::endl;                        
            // this is a major bug 
            // not doing this would lead to an infinite loop 
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (n1 < 0) {
            cout << "Enter a positive integer." <<std::endl;
            continue;
        }
        break;
    }
}
bool isnum (int n) {
    // if fail bit is set 
    if (!cin) return false;    
    return true;
}