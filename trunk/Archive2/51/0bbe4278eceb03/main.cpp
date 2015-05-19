#include <iostream>
#include <chrono>

// Third party libraries zijn het niet altijd eens, stel dat deze uit verschillende libraries komen
// ... of uit dezelfde, wat in legacy code vaak genoeg gebeurt: twee classes die min of meer hetzelfde doen
struct Human { int age_in_years; };
struct Person { int gregorian_birthyear; };

auto get_current_year(){
    auto const now = std::time(nullptr);
    return std::localtime(&now)->tm_year + 1900;
}

auto get_age_in_years(Human x){ return x.age_in_years; }
auto get_age_in_years(Person x){ return get_current_year() - x.gregorian_birthyear; }

int main(){
    // Stel dat deze objecten uit een database komen oid.
    Human nick{24};
    Person anne{1991};
    
    std::cout <<
        "Nick is " << get_age_in_years(nick) << " jaar oud\n" <<
        "Anne is ongeveer " << get_age_in_years(anne) << " jaar oud" << 
        std::endl;
}