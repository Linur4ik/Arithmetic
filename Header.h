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
public:
    map<char, array<double,3>>CharMap;
    unsigned int N;
     int k;

    Arithmetic();
    Arithmetic(unsigned int);
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


Arithmetic::Arithmetic(unsigned int n)
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
    unsigned int d = CharMap.size();
   Out.write((char*)&N, sizeof(N));
    Out.write((char*)&k, sizeof(k));
    Out.write((char*)&d, sizeof(d));
    for (auto it = CharMap.begin(); it != CharMap.end(); it++) // Записываем Map
    {
        Out.write((char*)&it->first, sizeof(it->first)); // Символ
        for(int i=0; i < 3 ; i++)   Out.write(reinterpret_cast<const char*>(&(it->second)[i]), sizeof((it->second)[i]));
    }
}


void Arithmetic::ReadCap(ifstream& In)
{
    unsigned int MapLong;
    char s;
    double Tr;
   In.read((char*)&N, sizeof(N));
    In.read((char*)&k, sizeof(k));
    In.read((char*)&MapLong, sizeof(MapLong)); 
    for (int i = 0; i < MapLong; i++)
    {
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
    while (1) // Запись кода
    {
        l2 = 0;
        h2 = 1;
        for (int i = 0; i < N; i++)
        {
            if (!In.get(s))
            {
                Out.write((char*)&l2, sizeof(l2));
                return;
            }
            //cout << s;
            l1 = l2 + CharMap[s][1] * (h2 - l2);
            h1 = l2 + CharMap[s][2] * (h2 - l2);
            h2 = h1;
            l2 = l1;
        }
        //cout << "e " << l2 << endl;
        Out.write((char*)&l2, sizeof(l2));
       // if (!In.get(s)) return;
    }
}

void Arithmetic::Decoded(ifstream& In, ofstream& Out)
{
    int count = 0;
    char s;
    double l1, l2, h1, h2;
    double x;
    while (k>0) // Запись кода
    {
        //In.get(s);
        l2 = 0;
        h2 = 0;
        In.read((char*)&x, sizeof(x));
        //cout << x << endl;
      //  x = (double)s;
        //cout << x;
        for (int i = 0; i < N; i++)
        {
            if (k <= 0) break;
            s = FindChar(x);
           
            

            //if (s == 'n') cout << endl << x << endl;
           // cout << s;
            Out.put(s);
            k--;
            //count++;
            
           // if (fabs((x - CharMap[s][1]) - (CharMap[s][2] - CharMap[s][1])) < 0.0000000000000001) cout << "ALLERT";
            //if (count == 20) cout << endl << CharMap[s][2] << endl;
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
        if (x >= a - 0.000000001 && x<b-0.000000001)
        {
            //cout << x << endl;
             //cout << a << "<=" << x << "<" << b  << " " << it->first << endl;
            return it->first; 
        }
    }
}
