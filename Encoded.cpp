#include "Header.h"

int main()
{
    ifstream In("Text.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
        return 0;
    }
    ofstream Out("Encoded.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
        return 0;
    }
	Arithmetic a;
   a.CreateMap(In);
   a.PrintMap();
   a.WriteCap(Out);
   a.Encoded(In, Out);
	return 0;
}
