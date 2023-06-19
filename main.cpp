#include "header.hpp"

int main() {
    // Administrator
    auto* admin = new Administrator();
    // System Rezerwacji
    ReservationSystem rs{};
    DateTime date = {2023,12,12};
    Application app{"John Doe","1234", &rs, admin, date};
    // metoda commands testuje podstawową funkcjonalność tego projektu
    app.commands();
}
