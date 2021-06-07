#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <bitset>
#include <array>
using namespace std;
void show_array(array<double, 3>& Ptr)
{
    for (int i = 0; i < 3; i++)
        cout << Ptr[i] << "  ";
    cout << endl;
}
class Arithmetic
{
    map<char, array<double,3>>CharMap;
    int N;
public:
    Arithmetic();
    Arithmetic(int);
    void PrintMap();
    void CreateMap(ifstream&);
};

Arithmetic::Arithmetic()
{
    N = 10;
}


Arithmetic::Arithmetic(int n)
{
    if (n < 1 || n > 32) n = 10;
    N = n;
}


/*void Arithmetic::PrintMap()
{
    for (auto it = CharMap.begin(); it != CharMap.end(); it++)
    {
        cout << it->first << " - " << it->second << endl;
    }
}
*/
void Arithmetic:: CreateMap(ifstream& In)
{
    double tr=0;
    char s;
    int k=0;
    for (In.get(s); !In.eof(); In.get(s))
    {
        array<double, 3>Ptr = CharMap[s];
        Ptr[0] = (Ptr[0] * k + 1) / (k + 1);
        CharMap[s]=Ptr;
        k++;
    }
    // —читаем границы
    for (auto it = CharMap.begin(); it != CharMap.end(); it++)
    {
        array<double, 3>Ptr = it -> second;
        Ptr[1] = tr;
        Ptr[2] = tr + Ptr[0];
        tr = Ptr[2];
        cout << it->first << " - ";
        show_array(it->second);
        it->second = Ptr;
    }

    In.clear();
    In.seekg(0, ios_base::beg);
}