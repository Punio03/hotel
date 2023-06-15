#include "header.hpp"

//room
ostream& operator << (ostream& out, const Room &room) {
    return out << "ID: " << room.roomID << endl
               << "Capacity: " << room.capacity << endl
               << "Price for night: " << room.price << "$" << endl
               << "Available: " << ((room.available) ? "true" : "false") << endl;
}

//address
ostream& operator << (ostream& out, const Address &address) {
    return out << "Country: " << address.country << endl
               << "Street name: " << address.streetName << endl
               << "Zip code: " << address.zipCode << endl
               << "City: " << address.city << endl
               << "Telephone number: " << address.phoneNumber << endl;
}

int DateTime::countLeapYears(DateTime date) {
    int years = date.year;
    if (date.month <= 2) years--;
    return years / 4 - years / 100 + years / 400;
}

int operator - (DateTime &date1, DateTime &date2) {
    long int n1 = date1.year * 365 + date1.day;
    for (int i = 0; i < date1.month - 1; i++) n1 += DateTime::monthDays[i];
    n1 += DateTime::countLeapYears(date1);
    long int n2 = date2.year * 365 + date2.day;
    for (int i = 0; i < date2.month - 1; i++) n2 += DateTime::monthDays[i];
    n2 += DateTime::countLeapYears(date2);
    return (int)(n2 - n1);
}

ostream& operator << (ostream& out, const Client &client) {
    out << "Name: " << client.name << endl
        << "Surname: " << client.surname << endl
        << "----- Reservations -----" << endl;
    for (const auto& reservation : client.reservations) out << *reservation << endl;
    return out << *client.invoice;
}

void Client::addOrder(const std::string& name, int reservationID) {
    for (auto reservation : reservations) {
        if (reservation->getID() == reservationID) {
            Hotel h{reservation->getHotel()};
            invoice->addOrder(name, &h);
            return;
        }
    }
}

void Client::addOpinion(int rating, std::string comment, int reservationID) {
    for (auto reservation : reservations) {
        if (reservation->getID() == reservationID) {
            Hotel h{reservation->getHotel()};
            h.addOpinion({rating,comment, id, reservationID});
            return;
        }
    }
}

ostream& operator << (ostream& out, const Opinion &opinion) {
    return out << "Rating: " << opinion.rating << endl
               << "Comment: " << opinion.comment << endl
               << "Client ID: " << opinion.clientID << endl
               << "Reservation ID: " << opinion.reservationID << endl;
}

double Menu::checkPrice(const std::string &name) {
    try {
        double price = prices.at(name);
        return price;
    } catch (out_of_range e) {
        return 0;
    }
}

ostream& operator << (ostream& out, const Menu &menu) {
    out << "----- Name ----- | ----- Price -----" << endl;
    for(const auto& n : menu.prices) {
        out << setw(16) << centered(n.first);
        out << " | " << setw(17) << centered(to_string(n.second));
    }
    return out;
}

Order::Order(const string& name, Hotel *hotel, bool done) : done(done), hotel(hotel) {
    Menu m = hotel->getRestaurant().getMenu();
    AdditionalServices as = hotel->getServices().getMenu();
    double price = m.checkPrice(name);
    if (price == 0) price = as.checkPrice(name);
    else {
        hotel->getRestaurant().addOrder({name, hotel});
        position = {name,price};
        return;
    }
    if (price == 0) position = {"Wrong position!", 0};
    else {
        hotel->getServices().addOrder({name, hotel});
        position = {name,price};
    }
}

ostream& operator << (ostream& out, const Order &order) {
    return out << order.position.first << " "
               << order.position.second << "$" << endl;
}

Order Restaurant::doOrder() {
    Order o = orders.top();
    orders.pop();
    o.setDone(true);
    return o;
}

int Hotel::searchForRoom(int roomID) {
    for(int i = 0; i < rooms.size(); i++) if (rooms[i].getRoomID()==roomID) return i;
    return -1;
}

ostream& operator << (ostream& out, const Hotel &hotel) {
    for(auto room : hotel.rooms) out << room << endl;
    return out;
}

void Invoice::addOrder(const string& name, Hotel* hotel) {
    Order o{name,hotel};
    wholePrice += o.getPrice();
    orders.emplace_back(o);
}

ostream& operator << (ostream& out, const Invoice &invoice) {
    out << "----- Invoice -----" << endl;
    out << "Whole price: " << invoice.wholePrice << "$" << endl;
    for(const auto& order : invoice.orders) out << order;
    return out;
}

// zmiana :D
ostream& operator << (ostream &out, const Reservation &res) {
    return out << "ID: " << res.id << endl
    << "Data zameldownia: " << res.checkInDate << endl
    << "Data wymeldowania: " << res.checkOutDate << endl
    << "--- Pokoje ---" << endl << &res.rooms << endl;
}
