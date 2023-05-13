#pragma once
#ifndef _DLL_H_
#define _DLL_H_




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
#include <windows.h>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

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



/// Klasė "zmogus" yra abstrakčioji bazinė klasė
/// 
/// Klasė "zmogus" turi viena pure virtual funkcija virtual ~zmogus()=0 , dėl to negalima tiesiogiai kurti šios klasės objektų. Ji naudojama su kita derived klase "studentas".
class zmogus {
protected:
    /// String tipo kintamasis vardas saugoja žmogaus vardą.
    string vardas;
    /// String tipo kintamasis pavarde saugoja žmogaus pavardę.
    string pavarde;
    /// Klasės konstruktorius.
    /// <param name="var"></param> vardo parametras.
    /// <param name="pav"></param> pavardės parametras.
    zmogus(string var="", string pav="") {
        vardas = var;
        pavarde = pav;
    }

    /// Pure virtual destruktorius.
    /// 
    /// Pure virtual destruktorius ištrina string vardo ir pavardės reikšmes ir vieta, taip pat užtikrina, kad klasė bus abstrakčioji.
    /// <returns></returns> 0.
    DLL_API virtual ~zmogus() = 0;
};

/// Derived klasė "studentas"
/// 
/// Derived klasė iš class<zmogus>. Pasiima kintamuosius vardas ir pavarde.
class studentas : public zmogus
{
private:
    vector<int> paz;
    int egz;
    float vid, med;

public:
    /// Default konstruktorius
    studentas() : zmogus() {
        this->paz = {};
        this->egz = 0;
        this->vid = 0;
        this->med = 0;
    }
    /// Konstruktorius
    /// <param name="v"></param> vardo parametras.
    /// <param name="p"></param> pavardės parametras.
    /// <param name="g"></param> pažymių parametras.
    /// <param name="e"></param> egzamino parametras.
    studentas(string v, string p, vector<int> g, int e) : zmogus(v, p)
    {
        this->paz = g;
        this->egz = e;
        vid = vidurk();
        med = median();
    }

    /// Kopijavimo konstruktorius
    /// <param name="other"></param>
    studentas(const studentas& other) : zmogus(other.vardas, other.pavarde)
    {
        this->paz = other.paz;
        this->egz = other.egz;
        this->vid = other.vid;
        this->med = other.med;
    }

    /// Kopijavimo paskyrimas
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

    /// Move konstruktorius
    /// <param name="other"></param>
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

    /// Move paskyrimas.
    /// <param name="other"></param>
    /// <returns></returns>
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

    /// Gražina egzamino pažymį.
    /// <returns></returns> Egzaminas
    inline int getegz() const { return egz; }
    /// Nustato egzamino pažymį.
    /// <param name="_value"></param> Egzamino reikšmė.
    inline void setegz(int _value) { this->egz = _value; }


    /// Gražina vidurkio pažymį.
    /// <returns></returns> Vidurkis
    inline float getvid() const { return vid; }
    /// Nustato vidurkio pažymį.
    /// <param name="_value"></param> Vidurkio reikšmė.
    inline void setvid(float _value) { this->vid = _value; }

    /// Gražina mediana.
    /// <returns></returns> Mediana
    inline float getmed() const { return med; }
    /// Nustato Mediana.
   /// <param name="_value"></param> Medianos reikšmė.
    inline void setmed(float _value) { this->med = _value; }

    /// Gražina vardą.
    /// <returns></returns> Vardas
    inline std::string getvardas() const { return vardas; }    // get'eriai, inline
    /// Nustato vardą.
   /// <param name="_value"></param> Vardo reikšmė.
    inline void setvardas(string _value) { this->vardas = _value; }

    /// Gražina pavardę.
    /// <returns></returns> Pavarde
    inline std::string getpavarde() const { return pavarde; }  // get'eriai, inline
    /// Nustato pavardę.
   /// <param name="_value"></param> Pavardės reikšmė.
    inline void setpavarde(string _value) { this->pavarde = _value; }

    /// Gražina ND pažymius.
    /// <returns></returns> ND pažymiai
    inline std::vector<int> getpaz() const { return paz; }  // get'eriai, inline
    /// Nustato pažymius po viena reikšmę.
    /// Tik po vieną skaičių pakeičia, įvedamas int kintamasis. Naudojama vector push_back.
    /// <param name="pazymys"></param> ND pažymys.
    inline void setpaz(int pazymys) { paz.push_back(pazymys); }
    /// Nustato pažymius.
    /// Nustato pagal visus pažymius, įvedamas vektorius.
    /// <param name="v"></param> ND pažymiai.
    inline void setpazdef(vector<int> v) { paz = v; }
    /// Pažymių vektoriaus dydžio pakeitimas.
    /// <param name="sz"></param> ND pažymių kiekis
    inline void pazresize(int sz) { paz.resize(sz); }

    /// Vidurkio funkcija.
    /// Apskaičiuoja vidurkio pažymį pagal turimas nd ir egzamino pažymius.
    /// <returns></returns> Vidurkis reikšmė
    DLL_API float vidurk();
    /// Medianos funkcija.
    /// Apskaičiuoja medianos pažymį pagal turimas nd ir egzamino pažymius.
    /// <returns></returns> Mediana reikšmė
    DLL_API float median();

    /// Operatoriaus cout perdengimas.
    /// Operatorius leidžia iškart spausdinti klasės studentas narius. Nereikia po viena narį kviesti.
    /// <param name="os"></param> Cout perdengimas.
    /// <param name="dt"></param> Studentas objektas.
    DLL_API friend std::ostream& operator<<(std::ostream& os, const studentas& dt);
    /// Operatoriaus cout perdengimas.
    /// Operatorius leidžia iškart užpildyt visus klasės studentas narius. Nereikia po viena narį kviesti.
    /// <param name="os"></param> Cin perdengimas.
    /// <param name="dt"></param> Studentas objektas.
    DLL_API friend std::istream& operator>>(std::istream& is, studentas& dt);

    /// Destruktorius
    ~studentas() {vardas.clear(), pavarde.clear(), paz.clear(); egz = 0; vid = 0; med = 0; }
};

extern "C"
/// Studentų objektų palyginimas.
/// Palygina du studentus pagal vidurkį. Grąžina mažesenį.
/// <param name=""></param> Studentas 1
/// <param name=""></param> Studentas 2
/// <returns></returns> Studentas 1 arba Studentas 2
DLL_API bool compare(const studentas&, const studentas&); //pagal vidurkius

extern "C"
/// Atsitiktinai generuoja studentą.
/// 
/// Atsitktinio generavimo metodu generuojami studento atributai.
/// <param name="nd_kiek"></param> ND pažymių kiekis
/// <param name="i"></param> Indexas
/// <param name="temp"></param> Studentas objektas
/// <returns></returns> Sugeneruotas studentas objektas
DLL_API void generate(int nd_kiek, int i, studentas& temp);

extern "C"
/// Atspausdina studento objekto vardą, pavardę ir vidurkį arba medianą.
/// <param name="pas2"></param> Pasirinkimas tarp vidurkio ir medianos
/// <param name="pas3"></param> Pasirinkimas tarp terminalo ir tekstinio failo spausdinimo
/// <param name="out_f"></param> Rezultatų tekstinis failas
/// <param name="temp"></param> Studento objektas
/// <returns></returns>
DLL_API void spausd(char pas2, char pas3, std::ofstream& out_f, studentas temp);

extern "C"
/// Perskaito tekstinį failą ir pagal duomenis sukuria studentų objektų vektorių.
/// <param name="open_f"></param> Skaitomas tekstinis failas
/// <param name="grupe"></param> Studentų objektų vektorius
DLL_API void read(std::ifstream& open_f, vector<studentas>& grupe);

extern "C"
/// Atsitiktinai sugeneruoja ir atspausdina tekstiniame faile studentų vardus, pavardes, ND ir egzamino pažymius
/// <param name="nd_kiekis"></param> ND pažymių kiekis
/// <param name="i"></param> Indexas
/// <param name="out_f"></param> Rezultatų tekstinis failas
/// <returns></returns>
DLL_API void failai(int nd_kiekis, int i, std::ofstream& out_f);

extern "C"
/// Išrinkimas tarp Nelaimėlių ir Kietekų.
/// 
/// Išrenka pagal vidurkį studentus ir paskirsto į dvi naujas grupes Nelaimėliai ir Kietekai.
/// <param name="grupe"></param> Visų studentų vektorius
/// <param name="Nel"></param> Nelaimėlių vektorius (Kurių vidurkis<5.00)
/// <param name="Kiet"></param> Kietekų vektorius (Kurių vidurkis>=5.00)
DLL_API void isrinkimas1(vector<studentas> grupe, vector<studentas>& Nel, vector<studentas>& Kiet);

extern "C"
/// Antras išrinkimo būdas tarp Nelaimėlių ir Kietekų.
/// 
/// Išrenka pagal vidurkį studentus ir paskirsto į naują grupę Nelaimėliai ir iš senos grupės juos pašalina, taip lieka senoj grupė tik Kietekai.
/// <param name="grupe"></param> Visų studentų vektorius
/// <param name="Nel"></param> Nelaimėlių vektorius (Kurių vidurkis<5.00)
DLL_API void isrinkimas2(vector<studentas>& grupe, vector<studentas>& Nel);


#endif