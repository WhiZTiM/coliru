    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>
    using namespace std;
    
    class sstring{
    private:
        string value;
    public:
        sstring(string);
        int len();
        string to_lower();
        string ss_reverse();
    };
    
    sstring::sstring(string a):value(a) { }
    
    //function
    string sstring::to_lower(){
        vector<string>current{};
        string ai;
        string val_cop = value;
        string final;
        const vector <string> lc{"q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n","m"};
        const vector <string> bc{"Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","Z","X","C","V","B","N","M"};
        for (int i = 0; i<value.length();i++){
            ai = val_cop[i];
            current.push_back(ai);
            for(int p =0;p<bc.size();p++){
                if( current[i] == bc[p]){
                    current[i] = lc[p];
                    
                }
                
            }
        }
        for (auto a:current){
            final +=a;
        }
        return final;
    }
    
    int sstring::len(){
        int count;
        for (int i =0;i<value.length();i++){
            count++;
        }
        return count++; 
    }
    
    
    string sstring::ss_reverse(){
        string val_cop = value;
        reverse(begin(val_cop),end(val_cop));
        return val_cop;
    }
    
    
    int main(){
        vector<const int> v;
        sstring ivan("IVAN");
    }