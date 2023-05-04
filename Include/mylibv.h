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
        this->paz = {};
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

    //copy
    studentas(const studentas& other) {
        this->vardas = other.vardas;
        this->pavarde = other.pavarde;
        this->paz = other.paz;
        this->egz = other.egz;
        this->vid = other.vid;
        this->med = other.med;
    }

    // copy assignment
    studentas& operator=(const studentas& rhs) {
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
        this->vardas = std::move(other.vardas);
        this->pavarde = std::move(other.pavarde);
        this->paz = std::move(other.paz);
        this->egz = std::move(other.egz);
        this->vid = other.vid;
        this->med = other.med;
        other.vardas.clear();
        other.pavarde.clear();
        other.paz.clear();
    }

    // move assignment
    studentas& operator=(studentas&& rhs) {
        // self-asignment check
        if (this != &rhs) {
            this->egz = rhs.egz;
            if (!this->paz.empty()) this->paz.clear();
            if (!this->vardas.empty()) this->vardas.clear();
            if (!this->pavarde.empty()) this->pavarde.clear();

            this->vardas = rhs.vardas;
            this->pavarde = rhs.pavarde;
            this->paz = std::move(rhs.paz);
            this->vid = rhs.vid;
            this->med = rhs.med;
            rhs.vardas.clear();
            rhs.pavarde.clear();
            rhs.paz.clear();
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

   ~studentas() { vardas.clear(); pavarde.clear(); paz.clear();}
};

bool compare(const studentas&, const studentas&); //pagal vidurkius
void generate(int nd_kiek, int i, studentas &temp);
void spausd(char pas2, char pas3, std::ofstream& out_f, studentas temp);
void read(std::ifstream& open_f, vector<studentas>& grupe);
void failai(int nd_kiekis, int i, std::ofstream& out_f);
void isrinkimas1(vector<studentas> grupe, vector<studentas>& Nel, vector<studentas>& Kiet);
void isrinkimas2(vector<studentas>& grupe, vector<studentas>& Nel);
