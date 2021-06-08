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
    ofstream c("Encoded.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
        return 0;
    }
    ifstream d("Text.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
    }
    Arithmetic a(10);
    Arithmetic b;
    b.CreateMap(d);
    b.WriteCap(c);
    b.Encoded(d, c);
   // b.PrintMap();


    a.ReadCap(In);
    a.Decoded(In, Out);
    a.PrintMap();
    return 0;
}
