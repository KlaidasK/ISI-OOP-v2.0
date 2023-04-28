#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <random>
#include <chrono>
#include <iterator>
#include <sstream>


using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::string;
using std::copy;
using std::numeric_limits;
using std::vector;
using std::istringstream;
using std::istringstream;
using std::runtime_error;

class studentas {

private:

    string vardas, pavarde;
    vector<int> paz;
    int egz;
    float vid, med;

public:
    //Default konst'ius
    studentas() { 
        this->vardas = "";
        this->pavarde = "";
        this->paz = {0};
        this->egz = 0;
        this->vid = 0;
        this->med = 0;
    }

    studentas(string v, string p, vector<int> g, int e) {
        this->vardas = v;
        this->pavarde = p;
        this->paz = g;
        this->egz = e;
        vid = vidurk();
        med = median();
    }
    //Egzamino pazymys
    inline int getegz() const { return egz; }
    inline void setegz(int _value) { this->egz = _value; }
    //Vidurkis
    inline float getvid() const { return vid; }
    inline void setvid(float _value) { this->vid = _value; }
    //Mediana
    inline float getmed() const { return med; }
    inline void setmed(float _value) { this->med = _value; }

    inline std::string getvardas() const { return vardas; }    // get'eriai, inline
    inline void setvardas(string _value) { this->vardas = _value; }

    inline std::string getpavarde() const { return pavarde; }  // get'eriai, inline
    inline void setpavarde(string _value) { this->pavarde = _value; }

    inline std::vector<int> getpaz() const { return paz; }  // get'eriai, inline
    inline void setpaz(int pazymys) { paz.push_back(pazymys); }
    inline void pazresize(int sz) { paz.resize(sz); }

    void pild();
    float vidurk();
    float median();
    void generate(int nd_kiek, int i);
    void read(std::ifstream &open_f, vector<studentas> &grupe);  // set'eriai
    void spausd(char pas2, char pas3, std::ofstream &out_f);
    void failai(int nd_kiekis, int i, std::ofstream& out_f);
    void isrinkimas1(vector<studentas> grupe, vector<studentas> &Nel, vector<studentas> &Kiet);
    void isrinkimas2(vector<studentas>& grupe, vector<studentas>& Nel);
    void clearpaz() { paz.clear(); }

    ~studentas() { clearpaz(); }
};
bool compare(const studentas&, const studentas&);