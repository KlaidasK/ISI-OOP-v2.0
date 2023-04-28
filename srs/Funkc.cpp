﻿# include "mylibv.h"

void studentas::pild(){ // Duomenų įvedimo funkcija

	int nd_kiekis = 0;
	int p;
	cout << "Iveskite varda ir pavarde: "; cin >> vardas >> pavarde;

	cout << "Iveskite pazymius beige rasyti iveskite, bet koki simboli" << endl;

	do {
		cin >> p;
		if (!cin) break;
		paz.push_back(p); // Vedami nd pažymiai
		nd_kiekis++;
		paz.resize(nd_kiekis);
	} while (cin);
	nd_kiekis = 0;
	cin.clear();
	std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	do {
		cout << "Iveskite egzamino paz. (Turi buti skaitmuo)" << endl;
		if (cin >> egz) break;
		cin.clear();
		std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	while (true);

	cout << "Duomenys irasyti" << endl;
}

void studentas::generate(int nd_kiekis, int i) { // Atsitiktinio generavimo funkcija

	using hrClock = std::chrono::high_resolution_clock;
	std::mt19937_64 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
	vardas=("Vardas" + std::to_string(i + 1));
	pavarde=("Pavarde" + std::to_string(i + 1));
	std::uniform_int_distribution<int>dist2(0, 10); // Pažymiams
	paz.resize(nd_kiekis);
	for (int j = 0; j < nd_kiekis; j++)
	{
		paz.push_back((dist2(mt)));
	}// Generuojami pažymiai
	egz=(dist2(mt)); // Generuojami egzamino pažymys

}

void studentas::read(std::ifstream &open_f, vector<studentas> &grupe) {

	std::vector<std::string> splited;
	std::string word, line;
	int max = 0;
	double sk = 0.0; // Iš viso žodžių faile
	int stul = 0; //stulpelių sk.
	studentas temp;
	auto start2 = std::chrono::high_resolution_clock::now(); auto st2 = start2;
	if (!open_f.fail()) {

		getline(open_f, line);
		splited.push_back(line);
		while (getline(open_f, line)) {
			++max;
			int a;
			std::stringstream ss(line);
			ss>>temp.vardas>>temp.pavarde;
			while (ss >> a) {
				temp.paz.push_back(a);
			}
			temp.egz=(temp.paz.back());
			temp.paz.pop_back();
			temp.vid=(temp.vidurk());
			grupe.push_back(temp);
			temp.paz.resize(0);
		}
	}
	open_f.close();
	splited.resize(0);

	auto end2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff2 = end2 - start2; // Skirtumas (s)
	std::cout << "Failo is " << max << " iraso nuskaitymo laikas: " << diff2.count() << " s\n";
}

void studentas::spausd(char pas2, char pas3, std::ofstream &out_f) // Rezultatų atspausdinimas
{
	if (pas3 == 'n') { // Jei norima spausdinti į terminalą
		cout << left << setw(20) << vardas;
		cout << left << setw(25) << pavarde;
		if (pas2 == '1') { cout << left << setw(30) << std::fixed << setprecision(2) << vidurk() << endl; }
		else if (pas2 == '2') { cout << left << setw(30) << std::fixed << setprecision(2) << median() << endl; }
		else if (pas2 == '3') { cout << left << setw(30) << std::fixed << setprecision(2) << vidurk() << setw(35) << std::fixed << setprecision(2) << median() << endl; }
	}
	else if (pas3 == 'y') { //Jei norima spausdinti į failą
		out_f << setw(20) << left << vardas;
		out_f << setw(25) << left << pavarde;
		if (pas2 == '1') { out_f << std::fixed << setprecision(2) << setw(30) << left << vidurk() << '\n'; }
		else if (pas2 == '2') { out_f << setw(30) << std::fixed << setprecision(2) << left << median() << endl; }
		else if (pas2 == '3') { out_f << setw(30) << std::fixed << setprecision(2) << left << vidurk() << setw(30) << std::fixed << setprecision(2) << left << median() << endl; }
	}
}

float studentas::vidurk() // Vidurkio skaičiavimas
{
	float nam_vid = 0, sum = 0;
	for (const auto& i : getpaz()) { sum = sum + i; }
	if (getpaz().size() == 0) pazresize(1);
	nam_vid = sum / getpaz().size();
	float vid = float(nam_vid * 0.4 + getegz() * 0.6);
	return vid;
}

float studentas::median() //Medianos skaičiavimas
{
	vector<int> vectkopija;
	typedef vector<int>::size_type vec_sz;
	vectkopija = getpaz();
	vectkopija.push_back(getegz());
	vec_sz size = vectkopija.size();
	sort(vectkopija.begin(), vectkopija.end());
	vec_sz mid = size / 2;
	return size % 2 == 0 ? float(vectkopija[mid] + vectkopija[mid - 1]) / 2 : vectkopija[mid];
}

void studentas::failai(int nd_kiekis, int i, std::ofstream& out_f) { // Atspausdinimi studentų failai be rezultatų

	using hrClock = std::chrono::high_resolution_clock;
	std::mt19937_64 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int>dist(0, 10); // Pažymiams
	out_f << setw(20) << left << "Vardas" + std::to_string(i + 1);
	out_f << setw(25) << left << "Pavarde" + std::to_string(i + 1);
	for (int i = 0; i < nd_kiekis; i++) {
		out_f << setw(5) << dist(mt) << setw(5);
	}
	out_f << dist(mt) << "\n";
}

void studentas::isrinkimas1(vector<studentas> grupe, vector<studentas> &Nel, vector<studentas> &Kiet) {

	auto starts1 = std::chrono::high_resolution_clock::now(); auto sts1 = starts1; //Pradedamas dalijimas į dvi grupes
	size_t laikui = grupe.size();

	Nel.resize(grupe.size());
	Kiet.resize(grupe.size());
	auto it = std::copy_if(grupe.begin(), grupe.end(), Nel.begin(), [](const auto& s) {return (s.vid < 5.00); });
	Nel.resize(std::distance(Nel.begin(), it));
	auto it2 = std::copy_if(grupe.begin(), grupe.end(), Kiet.begin(), [](const auto& s) {return (s.vid >= 5.00); });
	Kiet.resize(std::distance(Kiet.begin(), it2));

	auto ends1 = std::chrono::high_resolution_clock::now();						// Baigiamas dalijimas į dvi grupes
	std::chrono::duration<double> diffs1 = ends1 - starts1;						// Skirtumas (s)
	std::cout << laikui << " iraso dalijamo i dvi grupes laikas: " << diffs1.count() << " s\n";
}

void studentas::isrinkimas2(vector<studentas>& grupe, vector<studentas>& Nel) {

	auto starts2 = std::chrono::high_resolution_clock::now(); auto sts2 = starts2; //Pradedamas dalijimas į dvi grupes
	size_t laikui = grupe.size();

	Nel.resize(grupe.size());
	auto it = std::copy_if(grupe.begin(), grupe.end(), Nel.begin(), [](const auto& s) {return (s.vid < 5.00); });
	Nel.resize(std::distance(Nel.begin(), it));
	auto endit = remove_if(grupe.begin(), grupe.end(), [](const auto& s) {return (s.vid < 5.00); });
	grupe.erase(endit, grupe.end());

	auto ends2 = std::chrono::high_resolution_clock::now();						// Baigiamas dalijimas į dvi grupes
	std::chrono::duration<double> diffs2 = ends2 - starts2;						// Skirtumas (s)
	std::cout << laikui << " iraso dalijamo i dvi grupes laikas: " << diffs2.count() << " s\n";
}

bool compare(const studentas& a, const studentas& b) { return a.getvid() < b.getvid(); }