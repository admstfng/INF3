#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Hrac {
    std::string priezvisko = ""; // Initialize string with an empty string
    std::string meno = "";       // Initialize string with an empty string
    int zapasy = 0;              // Initialize integer with 0
    int karty = 0;               // Initialize integer with 0
    double uzitocnost = 0.0;     // Initialize double with 0.0
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Zadaj vstupný súbor.\n";
        return 1;
    }

    std::ifstream vstup(argv[1]);
    if (!vstup) {
        std::cerr << "Nepodarilo sa otvoriť súbor.\n";
        return 1;
    }

    std::vector<Hrac> hraci;
    Hrac h;
    while (vstup >> h.priezvisko >> h.meno >> h.zapasy >> h.karty) {
        h.uzitocnost = (h.zapasy > 0 && h.karty > 0) ? (h.zapasy * 90.0) / (h.zapasy * h.karty) : 0;
        hraci.push_back(h);
    }

    std::sort(hraci.begin(), hraci.end(), [](const Hrac& a, const Hrac& b) {
        return a.uzitocnost > b.uzitocnost;
        });

    std::ofstream vystup("zoradeni_hraci.txt");
    for (const auto& h : hraci) {
        std::cout << h.priezvisko << " " << h.meno << " " << std::fixed << std::setprecision(2) << h.uzitocnost << "\n";
        vystup << h.priezvisko << " " << h.meno << " " << std::fixed << std::setprecision(2) << h.uzitocnost << "\n";
    }

    return 0;
}