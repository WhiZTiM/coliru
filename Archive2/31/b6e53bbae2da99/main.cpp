#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <sstream>

struct tuna_parse {
    std::array<std::string,9> fields;	
	friend std::istream& operator>>(std::istream& stream, tuna_parse& tp) {
		for (auto&& entry : tp.fields)
			stream >> entry;
		return stream;
	}
};

bool contains(std::string const& str, const char* literal) {     
    return str.find(literal) != std::string::npos; 
}

int main() {
    
    auto match_it = [](auto... indices) { 
                        return [indices...](auto ...literals) {
                            return [indices..., literals...](tuna_parse const& p) {
                                bool arr[]{ contains(p.fields[indices],literals)... };                      
                                return std::all_of(std::begin(arr),std::end(arr),[](bool b){ return b; });
                            };
                        };
                    };
    
    auto check = [](tuna_parse const& p, auto func) {
                    return [&](auto ...fs){
                        return func(fs(p)... );                            
                    }; 
                  };
        
    auto match_all = [](auto ...ps){ bool arr[]{ps...}; return std::all_of(std::begin(arr),std::end(arr),[](bool b){return b;}); };
    auto match_any = [](auto ...ps){ bool arr[]{ps...}; return std::any_of(std::begin(arr),std::end(arr),[](bool b){return b;}); };
    
    auto check_for_all = [&](tuna_parse const& p) { return check(p, match_all); };
    auto check_for_any = [&](tuna_parse const& p) { return check(p, match_any); };

    auto merge_tests = [&](auto...fs){ 
                            return [&](tuna_parse const& p){ 
                                return match_all(fs(p)...); 
                            }; 
                        };

    // Here are some rules/tests...
    
    auto no_dirs = match_it(8)("../");
    auto no_downloads = match_it(8,6)("wp-config.php","200");
    auto no_logins = match_it(8,6)("wp-login.php","302");
    
    auto new_test = merge_tests(no_dirs, no_downloads);

    // Let's put it all together.. 
    
    std::stringstream blort{"Jun 26 20:57:41 tuna12 http://www.wasatchlodge.org 217.12.203.125 404 2472 /wp-content/themes/mTheme-Unus/css/css.php?files=../../../../wp-config.php\n"
    						"Jun 26 20:57:41 tuna12 http://www.wasatchlodge.org 217.12.203.125 404 2472 /wp-content/themes/mTheme-Unus/css/css.php?files=../../../../wp-config.php"};
	tuna_parse p;
    
    while (blort >> p) {
        std::cout << new_test(p) << ",";
        std::cout << check_for_any(p)(new_test) << ",";
        std::cout << check_for_all(p)(no_dirs,no_downloads,no_logins) << ",";
        std::cout << check_for_any(p)(no_dirs,no_downloads,no_logins,new_test) << "\n";        
    }

}
