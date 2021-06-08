#include <iostream>
#include <iterator>
#include <fstream>

using namespace std;
int main()
{
    ifstream In("Text.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error1";
        return 0;
    }
    ifstream It("Decode.txt", ios::binary);
    if (!It.is_open())
    {
        cout << "error2";
        return 0;
    }
    char s1, s2;
    while (In.get(s1) && It.get(s2))
    {
        if (s1 != s2)
        {
            cout << "error3" << endl; 
            return 0;
        }
    }
    if (!(In.get(s1) || It.get(s2)))
        cout << "Super";

}