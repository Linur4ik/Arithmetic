#include "Header.h"

int main()
{
    ifstream In("Text.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
        return 0;
    }
	Arithmetic a;
    a.CreateMap(In);



	return 0;
}