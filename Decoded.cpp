#include "Header.h"

int main()
{
    ifstream In("Encoded.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
        return 0;
    }
    ofstream Out("Decoded.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
    }
    Arithmetic a(10);
    a.ReadCap(In);
    a.PrintMap();
    return 0;
}