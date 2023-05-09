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

class zmogus {
protected:
    string vardas, pavarde;
    zmogus(string var, string pav) {
        vardas = var;
        pavarde = pav;
    }
    zmogus() {
        vardas = "";
        pavarde = "";
    }
    virtual ~zmogus() = 0;
};

class studentas: public zmogus
{
private:
    vector<int> paz;
    int egz;
    float vid, med;

public:
    //Default konst'ius
    studentas() : zmogus() {
        this->paz = {};
        this->egz = 0;
        this->vid = 0;
        this->med = 0;
    }

    studentas(string v, string p, vector<int> g, int e) : zmogus(v,p)
    {
        this->paz = g;
        this->egz = e;
        vid = vidurk();
        med = median();
    }

    //copy
    studentas(const studentas& other) : zmogus(other.vardas,other.pavarde)
    {
        this->paz = other.paz;
        this->egz = other.egz;
        this->vid = other.vid;
        this->med = other.med;
    }

    // copy assignment
    studentas& operator=(const studentas& rhs) 
    {
        // self-asignment check
        if (this != &rhs) {
            this->vardas = rhs.vardas;
            this->pavarde = rhs.pavarde;
            this->egz = rhs.egz;

            this->paz = rhs.paz;
            this->vid = rhs.vid;
            this->med = rhs.med;
        }

        return *this;
    }

    // move constructor
    studentas(studentas&& other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
        paz = other.paz;
        egz = other.egz;
        vid = other.vid;
        med = other.med;
        other.vardas.clear();
        other.pavarde.clear();
        other.paz.clear();
        other.egz = 0;
        other.vid = 0;
        other.med = 0;
    }

    // move assignment
    studentas& operator=(studentas&& other) {
        // self-asignment check
        if (this != &other) {
            
            if (!this->paz.empty()) paz.clear();
            if (!this->vardas.empty()) vardas.clear();
            if (!this->pavarde.empty()) pavarde.clear();

            egz = other.egz;
            vardas = other.vardas;
            pavarde = other.pavarde;
            paz = other.paz;
            vid = other.vid;
            med = other.med;
            other.vardas.clear();
            other.pavarde.clear();
            other.paz.clear();
            other.egz = 0;
            other.vid = 0;
            other.med = 0;
        }

        return *this;
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
    //vardas
    inline std::string getvardas() const { return vardas; }    // get'eriai, inline
    inline void setvardas(string _value) { this->vardas = _value; }
    //pavarde
    inline std::string getpavarde() const { return pavarde; }  // get'eriai, inline
    inline void setpavarde(string _value) { this->pavarde = _value; }
    //ND pazymiai
    inline std::vector<int> getpaz() const { return paz; }  // get'eriai, inline
    inline void setpaz(int pazymys) { paz.push_back(pazymys); }
    inline void pazresize(int sz) { paz.resize(sz); }

    //Gal balo skaiciavimas
    float vidurk();
    float median();
 
    
    //Operatoriai cout ir cin
    friend std::ostream& operator<<(std::ostream& os, const studentas& dt);
    friend std::istream& operator>>(std::istream& is, studentas& dt);

    
    ~studentas() { paz.clear(); egz = 0; vid = 0; med = 0; }
};

bool compare(const studentas&, const studentas&); //pagal vidurkius
void generate(int nd_kiek, int i, studentas &temp);
void spausd(char pas2, char pas3, std::ofstream& out_f, studentas temp);
void read(std::ifstream& open_f, vector<studentas>& grupe);
void failai(int nd_kiekis, int i, std::ofstream& out_f);
void isrinkimas1(vector<studentas> grupe, vector<studentas>& Nel, vector<studentas>& Kiet);
void isrinkimas2(vector<studentas>& grupe, vector<studentas>& Nel);
