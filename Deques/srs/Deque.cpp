﻿# include "mylibd.h"


int main()
{
	char uzkl;
	int stud_kiek = 0, max = 0;
	char pas, pas2, pas3; // Pasirinkimas tarp pazymiu ivedimo ir atsitiktinio generavimo, pasirinkimas tarp vidurkio ir medianos
	std::deque<studentas> grupe;
	studentas laikinas;
	do {
		cout << "Norint paciam ivesti studento pazymius spauskite 1, jei norit generuoti duomenis atsitiktinai spauskite 2, o  jei norite duomenis paimti is failo spauskite 3, o failu generavimas 4 :" << endl; cin >> pas;
		cin.clear();
		std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	} while (pas != '1' && pas != '2' && pas != '3' && pas != '4');

	if (pas == '1') { // Įvedami duomenys
		do {
			cout << "Iveskite studento duomenis: \n";
			//laikinas.paz.reserve(max);
			pild(laikinas, max);
			grupe.push_back(laikinas);
			laikinas.paz.clear();
			cout << "Pabaigai spauskite n, kitaip veskite kito studento duomenis po bet kokio klaviso nuspaudimo" << endl;
			cin >> uzkl;
		} while (uzkl != 'n' && uzkl != 'N');
	}

	else if (pas == '2') { // Generuojami duomenys

		cout << "Iveskite studentu skaiciu: " << endl; cin >> stud_kiek;
		try {
			if (stud_kiek == 0) throw("Klaida. Sarasas tuscias!");
		}
		catch (const char* msg) {
			cerr << msg << endl;
			return EXIT_FAILURE;
		}

		do {
			cout << "Iveskite namu pazymiu skaiciu: " << endl;
			if (cin >> max) break;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		} while (true); // Vedamas egzamino pažymys

		for (int i = 0; i < stud_kiek; i++)
		{
			//laikinas.paz.reserve(stud_kiek);
			try {
				generate(laikinas, max, i);
			}
			catch (const char* msg) {
				cerr << msg << endl;
				return EXIT_FAILURE;
			}
			grupe.push_back(laikinas);
			laikinas.paz.clear();
		}
	}
	else if (pas == '3') { // Duomenys paimami iš failo
		try {
			system("dir /b | findstr \\.txt$");
			string name_vardas;
			cout << "Iveskite failo varda: " << endl; cin >> name_vardas;
			skaitymas(name_vardas, grupe, max); // Kreipimasis į skaitymo funkcija
		}
		catch (const char* msg) {
			cerr << msg << endl;
			return EXIT_FAILURE;
		}
	}
	/// ////////////////////////////////////////////////////////////////////////////////
	else if (pas == '4') {																// Failu generavimas
		pas3 = 'y', pas2 = '1';
		int i = 0; char pab = 0, rink = 0, strat = 0;
		string rez;
		do {
			do {
				cout << "Jei norite generuoti faila atsitiktinai irasykite 1, jei norite turima faila perskaityti - 2:" << endl;
				cin >> rink;
				cin.clear();
				std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			} while (rink != '1' && rink != '2');

			do {
				cout << "Pasirinkite dalijimo strategija 1 ar 2:" << endl;
				cin >> strat;
				cin.clear();
				std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			} while (strat != '1' && strat != '2');

			if (rink == '1') { //Jei failas dar tik kuriamas
				cout << "Iveskite studentu skaiciu: " << endl; cin >> stud_kiek;
				try {
					if (stud_kiek == 0) throw("Klaida. Sarasas tuscias!");
				}
				catch (const char* msg) {
					cerr << msg << endl;
					return EXIT_FAILURE;
				}

				do {
					cout << "Iveskite namu pazymiu skaiciu: " << endl;
					if (cin >> max) break;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				} while (true); // Vedamas egzamino pažymys

			};
			auto start6 = std::chrono::high_resolution_clock::now(); auto st6 = start6;		// Pradedamas visas sugaištas laikas
			if (rink == '1') {

				auto start = std::chrono::high_resolution_clock::now(); auto st = start;	//Pradedamas failo generavimo ir kurimo laikas
				//grupe.reserve(stud_kiek);
				for (int i = 0; i < stud_kiek; i++)
				{
					//laikinas.paz.reserve(stud_kiek);
					try {
						generate(laikinas, max, i);
					}
					catch (const char* msg) {
						cerr << msg << endl;
						terminate();
					}
					grupe.push_back(laikinas);
					laikinas.paz.clear();
				}



				rez = "Rezultatai" + std::to_string(i + 1) + ".txt";
				std::ofstream out_f(rez);												//Failo kurimas
				out_f << left << setw(20) << "Vardas" << left << setw(25) << "Pavarde"; //Antraštė
				for (int i = 1; i <= max; i++) {										//Antraštė
					out_f << setw(5) << "ND" + std::to_string(i) << setw(5);			//Antraštė
				}																		//Antraštė
				out_f << "Egz" << endl;													//Antraštė
				for (auto& i : grupe) failai(i, max, out_f);							//Atspausdina duomenis į failą
				grupe.clear();															// Atlaisvinama vieta
				out_f.close();															// Uždaromas failas
				auto end = std::chrono::high_resolution_clock::now();					//Baigiamas failo kurimo laikas
				std::chrono::duration<double> diff = end - start;						// Skirtumas (s)

				cout << "Failas uzdaritas" << endl;										//Uždaromas failas
				std::cout << stud_kiek << " irasu failo kurimas uztruko  " << diff.count() << " s\n"; // Atspausdinama failo kurimo laikas
			}

			else if (rink == '2') {														// Jei failas jau egzistuoja ir norima jį tik perskaityti
				system("dir /b | findstr \\.txt$");
				cout << "Iveskite failo varda: " << endl; cin >> rez;

			}
			auto start7 = std::chrono::high_resolution_clock::now(); auto st7 = start7;
			skaitymas(rez, grupe, max); // Kreipimasis į skaitymo funkcija
			auto startskait = std::chrono::high_resolution_clock::now(); auto stskait = startskait;
			sort(grupe.begin(), grupe.end(), student); // Rikiavimas pagal vidurki
			auto endskait = std::chrono::high_resolution_clock::now();					//Baigiamas failo kurimo laikas
			std::chrono::duration<double> diffskait = endskait - startskait;
			cout << max << " irasu failo sortinimas uztruko  " << diffskait.count() << " s\n";

			string nel = "Nelaimingi";
			nel = nel + std::to_string(i + 1) + ".txt";
			std::ofstream out_n(nel);
			string ket = "Kietekai";
			ket = ket + std::to_string(i + 1) + ".txt";
			std::ofstream out_k(ket);
			out_n << left << setw(20) << "Vardas" << left << setw(25) << "Pavarde";
			out_n << setw(30) << "Gal. Vidurkis" << endl;
			out_n << "-------------------------------------------------------------------------------------------" << endl;
			out_k << left << setw(20) << "Vardas" << left << setw(25) << "Pavarde";
			out_k << setw(30) << "Gal. Vidurkis" << endl;
			out_k << "-------------------------------------------------------------------------------------------" << endl;

			std::deque<studentas> Nel;
			std::deque<studentas> Kiet;

			isrinkimas(grupe, Nel, Kiet, strat);
			grupe.clear();


			auto start4 = std::chrono::high_resolution_clock::now(); auto st4 = start4; //Pradedama nelaimeliu spausdinimo laikas
			for (auto& i : Nel) spausd(i, pas2, pas3, out_n); // Atspausdinama nelaimeliai
			auto end4 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff4 = end4 - start4; // Skirtumas (s)
			std::cout << max << " iraso nelaimeliu i faila irasymo laikas: " << diff4.count() << " s\n";

			auto start5 = std::chrono::high_resolution_clock::now(); auto st5 = start5; //Pradedama Kieteku spausdinimo laikas
			for (auto& i : Kiet) spausd(i, pas2, pas3, out_k); //Atspausdinama kietekai
			auto end5 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff5 = end5 - start5; // Skirtumas (s)
			std::cout << max << " iraso kieteku i faila irasymo laikas: " << diff5.count() << " s\n";

			Nel.clear();	//
			Kiet.clear();	// Atlaisvinama vieta
			out_n.close();	//
			out_k.close();	// Uždaromi failai

			auto end6 = std::chrono::high_resolution_clock::now(); // Viso sugaišto laiko pabaiga
			auto end7 = std::chrono::high_resolution_clock::now(); // Viso sugaišto laiko pabaiga
			if (rink == '1') {
				std::chrono::duration<double> diff6 = end6 - start6; // Skirtumas (s)
				cout << endl;
				std::cout << max << " iraso testo laikas: " << diff6.count() << " s\n";
			}

			if (rink == '2') {
				std::chrono::duration<double> diff7 = end7 - start7; // Skirtumas (s)
				cout << endl;
				std::cout << max << " iraso testo laikas: " << diff7.count() << " s\n";
			}
			cout << "Ar norite uzbaigti failu generavima? (Irasykite y)" << endl;
			cin >> pab;
			i++; //Failu vardu generavimui
		} while (pab != 'y' && pab != 'Y');
		return EXIT_SUCCESS;
	};																					// Failu generavimas paigiasi
	/// ////////////////////////////////////////////////////////////////////////////////
	if (pas != '4') {
		do {
			cout << "Pasirinkite 1 jei norite matyti vidurki, jei norite matyti mediana paspauskite 2, o jei norite matyti abu spauskite 3 : " << endl;
			cin >> pas2;
		} while (pas2 != '1' && pas2 != '2' && pas2 != '3'); // Pasirinkimas tarp vidurkio ar medianos, arba abiejų

		std::ofstream out_f("Rezultatai.txt");
		do {
			cout << "Ar norite isvesti rezultatus i faila (y/n) : " << endl;
			cin >> pas3;
		} while (pas3 != 'y' && pas3 != 'n'); // Pasirinkimas tarp išvedimo

		sort(grupe.begin(), grupe.end(), student); // Rikiavimas pagal vardą

		if (pas3 == 'n') { // Spausdinama į terminalą
			cout << left << setw(20) << "Vardas" << left << setw(25) << "Pavarde";
			if (pas2 == '1') { cout << setw(30) << "Gal. Vidurkis" << endl; }
			else if (pas2 == '2') { cout << setw(30) << "Gal. Mediana" << endl; }
			else if (pas2 == '3') { cout << setw(30) << "Gal. Vidurkis" << setw(35) << "Gal. Mediana" << endl; };
			cout << "--------------------------------------------------------------------------------------------" << endl;
			for (auto& i : grupe) spausd(i, pas2, pas3, out_f);
		}
		else if (pas3 == 'y') { // Spausdinama į failą
			out_f << left << setw(20) << "Vardas" << left << setw(25) << "Pavarde";
			if (pas2 == '1') { out_f << setw(30) << "Gal. Vidurkis" << endl; }
			else if (pas2 == '2') { out_f << setw(30) << "Gal. Mediana" << endl; }
			else if (pas2 == '3') { out_f << setw(30) << "Gal. Vidurkis" << setw(35) << "Gal. Mediana" << endl; };
			out_f << "-------------------------------------------------------------------------------------------" << endl;
			for (auto& i : grupe) spausd(i, pas2, pas3, out_f);
		};
		grupe.clear();
	}
	return EXIT_SUCCESS;
}
