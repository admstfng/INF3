#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

struct Route {
    std::string number;
    std::string airline;
    int ticketPrice;
    int maxCapacity;
    int flights;
    int totalPassengers;
    int revenue;
    double utilization;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << inputFileName << std::endl;
        return 1;
    }

    std::vector<Route> routes;
    std::string number, airline;
    int ticketPrice, maxCapacity, flights;

    // Read data from the file
    while (inputFile >> number >> airline >> ticketPrice >> maxCapacity >> flights) {
        Route route;
        route.number = number;
        route.airline = airline;
        route.ticketPrice = ticketPrice;
        route.maxCapacity = maxCapacity;
        route.flights = flights;

        // Generate total passengers for each flight (randomly in range <10, maxCapacity>)
        route.totalPassengers = 0;
        for (int i = 0; i < flights; ++i) {
            route.totalPassengers += 10 + rand() % (maxCapacity - 10 + 1);
        }

        // Calculate revenue and utilization
        route.revenue = route.totalPassengers * route.ticketPrice;
        route.utilization = static_cast<double>(route.totalPassengers) / (route.maxCapacity * route.flights);

        routes.push_back(route);
    }

    inputFile.close();

    // Sort routes by utilization in descending order
    std::sort(routes.begin(), routes.end(), [](const Route& a, const Route& b) {
        return a.utilization > b.utilization;
        });

    // Output results to the console
    std::cout << "Cislo linky - Letecka spolocnost [Celkovo pocet prevezenych cestujucich] Trzba - Vyzitost" << std::endl;
    for (const auto& route : routes) {
        std::cout << route.number << " - " << route.airline
            << " [" << route.totalPassengers << "] "
            << route.revenue << " - "
            << std::fixed << std::setprecision(2) << route.utilization << std::endl;
    }
    _CrtDumpMemoryLeaks();
    return 0;
}
