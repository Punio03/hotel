#include "header.hpp"

int main() {
    // Administrator
    auto* admin = new Administrator();
    // System Rezerwacji
    ReservationSystem rs{};
    Application app{"John Doe","1234", &rs, admin};
    app.commands();
}
