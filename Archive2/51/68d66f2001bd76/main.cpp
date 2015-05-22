#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> v = { 1, 2, 3, 4 };
    
    for (unsigned i = 0; i != v.size(); ++i)
        cout << v[i] << " ";
        
    cout << endl;
    
    int vv[] = { 5, 6, 7, 8 };
    
    for (int* w = vv; w != (vv + sizeof(vv) / sizeof(int)); ++w)
        cout << *w << " ";
        
    cout << endl;
    
    // [v.begin(), v.end)
    for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
        cout << *i << " ";
        
    cout << endl;
    
    for (auto i = v.begin(); i != v.end(); ++i)
        cout << *i << " ";

    cout << endl;
    
    for (auto i = v.rbegin(); i != v.rend(); ++i)
        cout << *i << " ";
        
    cout << endl;
    
    for (auto i = v.rend() - 1; i >= v.rbegin(); --i)
        cout << *i << " ";
    cout << endl;
    
    for (auto i = v.end() - 1; i >= v.begin(); --i)
        cout << *i << " ";
    cout << endl; 
    
    for (auto i = v.begin(); i != v.end(); ++i)
        ++*i;
    
    for (auto i : v) // tipo de i == int
        cout << i << " ";
    cout << endl;
        
        
    for (auto& i : v) // tipo de i == int&
        ++i;
    
    for (auto& i : v) cout << i << " "; cout << endl;
        
    for (auto it = v.begin(); it != v.end(); ++it) {
        auto& i = *it;
        ++i;
    }
    
    // tipo i = int&
    for (auto& i : v) cout << i << " "; cout << endl;
    
    /*
    *
    *   Iteradores (para los contenderos que los tengas, "los de verda'"):
    *
    *      Contener<T>:
    *          iterator begin();
    *          const_iterator begin() const;
    *          const_iterator cbegin() const;
    *          // Y sus 3 equivalentes para `end()`.
    *
    *          reverse_iterator rbegin();
    *          const_reverse_iterator rbegin() const;
    *          const_reverse_iterator crbegin() const;
    *          // Y sus 3 equivalentes para `rend()`.
    *
    */
    
    
    
    /*
     *     
     *     MORE ITERATORS!!!!
     *
     */
    // Ahora mismo el vector es = { 4, 5, 6, 7 };
    v.insert(v.begin() + 2, 11); // = { 4, 5, 11, 6, 7 };
    v.insert(v.begin(), 7); // = { 7, 4, 5, 11, 6, 7 };
    v.insert(v.end() - 1, 9); // = {7, 4, 5, 11, 6, 9, 7 };
    v.insert(v.end(), 4); // = {7, 4, 5, 11, 6, 9, 7, 4 };
    v.erase(v.begin()); // = {4, 5, 11, 6, 9, 7, 4};
    // v.erase(v.end()); Cuidadín.
    v.erase(v.end() - 1); // = {4, 5, 11, 6, 9, 7};
    
    for (auto i = v.begin(); i != v.end(); ++i)
        if (distance(v.begin(), i) % 2 == 0)
            v.erase(i);

    cout << endl;
    
    for (auto i : v) cout << i << " "; cout << endl;
     
    return 0;
}
