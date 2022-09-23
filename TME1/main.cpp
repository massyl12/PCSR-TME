#include <iostream>

using namespace std;
int main(int argc, const char** argv){
    cout <<  "helloworld" << endl;

    size_t tab[10] = {0,1,2,3,4,5,6,7,8,9};
    for(size_t i = 0; i<10; i++)
        cout << tab[i];
    cout << endl;
}



/* debug g++ -g -o0

gbd mon debug
br main.cpp:16
ddd  ?data display debugger
n next 
s step
c continue
l lister le code
bt backtreace
f 3 frame
p var print
p *r print
q quit
*/