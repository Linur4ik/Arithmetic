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
    int k;
public:
    Arithmetic();
    Arithmetic(int);
    void PrintMap();
    void CreateMap(ifstream&);
    void Encoded(ifstream&, ofstream&);
    void Decoded(ifstream&, ofstream&);
    void WriteCap(ofstream&);
    void ReadCap(ifstream&);
    char FindChar(double);
};

Arithmetic::Arithmetic()
{
    N = 10;
    k = 0;
}


Arithmetic::Arithmetic(int n)
{
    if (n < 1 || n > 32) n = 10;
    N = n;
    k = 0;
}


void Arithmetic::PrintMap()
{
    for (auto it = CharMap.begin(); it != CharMap.end(); it++)
    {
        cout << it->first << " - ";
        show_array(it->second);
    }
    cout << endl;
}

void Arithmetic::WriteCap(ofstream& Out) //&
{
    int d = CharMap.size();
  //  Out.write((char*)&N, sizeof(N));
   // Out.write((char*)&k, sizeof(k));
   // Out.write((char*)&d, sizeof(d));
    Out << N;
    Out << k;
    Out << d;


  //  Out.put((char)N); 
  //  Out.put((char)k); // кол-во всех
   // Out.put((char)d); // кол-во символов Map
    cout << N << endl << k << endl << d << endl;
 //   unsigned char u = k;
   // cout << N << endl << u << endl;
    for (auto it = CharMap.begin(); it != CharMap.end(); it++) // Записываем Map
    {
        Out.write((char*)&it->first, sizeof(it->first)); // Символ
        for(int i=0; i < 3 ; i++)   Out.write(reinterpret_cast<const char*>(&(it->second)[i]), sizeof((it->second)[i]));
    }
}


void Arithmetic::ReadCap(ifstream& In)
{
    int MapLong;
    char s;
    double Tr;
   // In.get(s);
   // N = s;
   // In.get(s);
   // k = s;  
   // In.get(s);
   // MapLong = s;
    In >> N;
    In >> k;
    In >> MapLong;
   // In.read((char*)&N, sizeof(N));
   // In.read((char*)&k, sizeof(k));
   // In.read((char*)&MapLong, sizeof(MapLong)); 
    cout << N << endl << k << endl<< MapLong << endl;
    for (int i = 0; i < MapLong; i++)
    {
        cout << 1 << endl;
        In.read((char*)&s, sizeof(s));
        for (int j = 0; j < 3; j++)
        {
            In.read((char*)&Tr, sizeof(Tr));
            
            CharMap[s][j] = Tr;
        }
    }
}


void Arithmetic:: CreateMap(ifstream& In)
{
    double tr=0;
    char s;
    k=0;
    for (In.get(s); !In.eof(); In.get(s))
    {
        array<double, 3>Ptr = CharMap[s];
        Ptr[0]++;
        CharMap[s]=Ptr;
        k++;
    }
    // Считаем границы
    for (auto it = CharMap.begin(); it != CharMap.end(); it++)
    {
        array<double, 3>Ptr = it -> second;
        Ptr[0] = Ptr[0] / k;
        Ptr[1] = tr;
        Ptr[2] = tr + Ptr[0];
        tr = Ptr[2];
        it->second = Ptr;
    }
    In.clear();
    In.seekg(0, ios_base::beg);
}


void Arithmetic::  Encoded(ifstream &In,ofstream &Out)
{
    char s;
    double l1, l2, h1, h2;
    while (In.get(s)) // Запись кода
    {
        l2 = 0;
        h2 = 1;
        for (int i = 0; i < N; i++)
        {
            l1 = l2 + CharMap[s][1] * (h2 - l2);
            h1 = l2 + CharMap[s][2] * (h2 - l2);
            l2 = h1;
            l2 = l1;
        }
        Out.put(l2);
    }
}

void Arithmetic::Decoded(ifstream& In, ofstream& Out)
{
    char s;
    double l1, l2, h1, h2;
    double x=0;
    while (k>0) // Запись кода
    {
        In.get(s);
        x = (double)s;
        for (int i = 0; i < N; i++)
        {
            s = FindChar(x);
            Out.put(s);
            k--;
            x = (x - CharMap[s][1]) / (CharMap[s][2] - CharMap[s][1]);
        }  
    }
}

char Arithmetic::FindChar(double x)
{
    double a, b;
    for (auto it = CharMap.begin(); it != CharMap.end(); it++) 
    {
        a = it->second[1];
        b = it->second[2];
        if (a <= x && x < b) return it->first;
    }
    return 1;
}
