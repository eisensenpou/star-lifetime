#include "main.h"
#include "physics/star_physics.h"


int main() {
    std::cout << "=== Stellar Lifetime Simulator ===\n";
    std::cout << "1. Estimate lifetime of a star\n";
    std::cout << "2. Generate lifetime table\n";
    std::cout << "3. Compare multiple stars\n";
    std::cout << "Choose option: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        double mass;
        std::cout << "Enter stellar mass (in solar masses): ";
        std::cin >> mass;

        double lifetime = physics::stellar::lifetime(mass * M_SUN);
        std::cout << "Predicted lifetime: " << lifetime << " years\n";
    } 
    else if (choice == 2) {
        physics::stellar::generate_lifetime_table(100);
    } 
    else if (choice == 3) {
        physics::stellar::Star sun("Sun", 1.0, 1.0, 4.6e9);
        physics::stellar::Star sirius("Sirius A", 2.1, 25.0, 2.4e8);
        sun.printSummary();
        sirius.printSummary();
    } 
    else {
        std::cout << "Invalid option.\n";
    }

    return 0;
}
