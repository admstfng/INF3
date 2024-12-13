#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Zamestnanec {
    std::string priezvisko;
    std::string meno;
    int pocetDni;
    double hodinovaSadzba;
    std::vector<int> odpracovaneHodiny;
    int celkoveHodiny = 0;
    double mzda = 0.0;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Zadajte meno vstupneho suboru ako parameter." << std::endl;
        return 1;
    }

    std::ifstream vstup(argv[1]);
    if (!vstup.is_open()) {
        std::cerr << "Nepodarilo sa otvorit subor." << std::endl;
        return 1;
    }

    std::vector<Zamestnanec> zamestnanci;
    std::string priezvisko, meno;
    int pocetDni;
    double hodinovaSadzba;

    while (vstup >> priezvisko >> meno >> pocetDni >> hodinovaSadzba) {
        zamestnanci.push_back({ priezvisko, meno, pocetDni, hodinovaSadzba });
    }

    vstup.close();

    double koeficient;
    std::cout << "Zadajte koeficient priplatku za nadcasove hodiny (1.5 - 2.5): ";
    std::cin >> koeficient;
    if (koeficient < 1.5 || koeficient > 2.5) {
        std::cerr << "Neplatny koeficient." << std::endl;
        return 1;
    }

    std::srand(std::time(0));

    for (auto& zamestnanec : zamestnanci) {
        for (int i = 0; i < zamestnanec.pocetDni; ++i) {
            int hodiny = 5 + std::rand() % 8; // Generuje hodiny v intervale <5,12>
            zamestnanec.odpracovaneHodiny.push_back(hodiny);
            zamestnanec.celkoveHodiny += hodiny;
        }

        int nadcasy = std::max(0, zamestnanec.celkoveHodiny - 170);
        double zakladnaMzda = zamestnanec.hodinovaSadzba * (zamestnanec.celkoveHodiny - nadcasy);
        double nadcasovaMzda = nadcasy * zamestnanec.hodinovaSadzba * koeficient;
        zamestnanec.mzda = zakladnaMzda + nadcasovaMzda;
    }

    std::sort(zamestnanci.begin(), zamestnanci.end(), [](const Zamestnanec& a, const Zamestnanec& b) {
        return a.mzda > b.mzda;
        });

    std::ofstream vystup("vystup.txt");
    if (!vystup.is_open()) {
        std::cerr << "Nepodarilo sa otvorit vystupny subor." << std::endl;
        return 1;
    }

    for (const auto& zamestnanec : zamestnanci) {
        std::cout << zamestnanec.priezvisko << " " << zamestnanec.meno << " [" << zamestnanec.celkoveHodiny << "] "
            << std::fixed << std::setprecision(2) << zamestnanec.mzda << std::endl;
        vystup << zamestnanec.priezvisko << " " << zamestnanec.meno << " [" << zamestnanec.celkoveHodiny << "] "
            << std::fixed << std::setprecision(2) << zamestnanec.mzda << std::endl;
    }

    vystup.close();
    return 0;
}