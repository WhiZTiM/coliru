#include <vector>     // std::vector
#include <string>     // std::string
#include <algorithm>  // std::copy, 
#include <functional> // std::unary_function
#include <iterator>   // std::ostream_iterator, std::back_inserter
#include <ostream>    // std::ostream
#include <iostream>   // std::cout
#include <cassert>    // assert
 
 
/*-------------------------------[ Ligne de la base ]------------------------*/
// Définition à la va-vite d'une ligne.
struct line_type : public std::vector<std::string> {
    template <typename IterIn>
    line_type(IterIn first, IterIn last) 
        : std::vector<std::string>(first, last) {}
 
    friend std::ostream & operator<<(
            std::ostream & os, 
            const line_type & l) 
    {
        std::copy(l.begin(),l.end(), 
                std::ostream_iterator<std::string>(os, " - "));
        return os;
    }
};
 
 
/*-------------------------------[ Clauses de recherche ]--------------------*/
// Clause Where pour sélectionner certaines lignes seulement
class Where : std::unary_function<std::vector<std::string>, bool>
{
    typedef std::vector<std::string> line_type;
    typedef line_type::size_type     field_id_type;
    typedef line_type::value_type    field_type;
    field_id_type field_nb_;
    field_type    field_;
public:
    Where(field_id_type id, const field_type & f)
        : field_nb_(id), field_(f) { std::cout << "Constructed a Where object" << std::endl; }
    bool operator() (const line_type & l) const {
        return l[field_nb_] == field_;
    }
};
 
// Pour définir des ET-logiques entre clauses Where
template <typename P1, typename P2>
class PredicateAnd : std::unary_function<std::vector<std::string>, bool>
{
    P1 p1_;
    P2 p2_;
public:
    PredicateAnd(P1 p1, P2 p2) : p1_(p1), p2_(p2) {}
    bool operator() (const line_type & l) const {
        std::cout << "Evaluating PredicateAnd &&" << std::endl;
        return p1_(l) && p2_(l);
    }
};
 
// Pour écrire plus simplement les fameux ET-logiques
template <typename P1, typename P2>
PredicateAnd<P1,P2> operator&&(P1 p1, P2 p2) {
    std::cout << "Creating PredicateAnd" << std::endl;
    return PredicateAnd<P1,P2>(p1, p2);
}
// Faire la même chose pour les OU-logique
 
 
/*-------------------------------[ Prédicat de comparaison ]-----------------*/
// Prédicat pour trier des lignes suivant un champ donné
class CmpCol { 
    unsigned int col_; 
public: 
    CmpCol(unsigned int c) : col_(c) {} 
    bool operator()( 
        const line_type & v1, 
        const line_type & v2) const 
    { 
        assert(v1.size() >= col_); 
        assert(v2.size() >= col_); 
        return v1[col_] < v2[col_]; 
    } 
}; 
 
 
/*===============================[ Prog Princ ]==============================*/
int main (int argc, char **argv)
{
    // 0- Initialise la base initiale
    const char* lig1[] = { "Toto", "maison", "C" };
    const char* lig2[] = { "Titi", "cabane", "B" };
    const char* lig3[] = { "Tutu", "tente", "A" };
    const char* lig4[] = { "Tata", "appart", "E" };
    const char* lig5[] = { "Bobo", "maison", "D" };
    const char* lig6[] = { "Baba", "maison", "D" };
 
    typedef std::vector<line_type>   base_type;
 
    base_type basePrincipale;
    basePrincipale.push_back(line_type(lig1, lig1+3));
    basePrincipale.push_back(line_type(lig2, lig2+3));
    basePrincipale.push_back(line_type(lig3, lig3+3));
    basePrincipale.push_back(line_type(lig4, lig4+3));
    basePrincipale.push_back(line_type(lig5, lig5+3));
    basePrincipale.push_back(line_type(lig6, lig6+3));
 
    // extrait une sous-base avec les derniers critères
    std::cout << "Before copy_if" << std::endl;
    base_type b3;
    std::copy_if(basePrincipale.begin(),basePrincipale.end(),
            std::back_inserter(b3), Where(1, "maison") && Where(2,"D"));
    std::cout << "After copy_if" << std::endl;
    std::cout << "\n--------\n";
    std::copy(b3.begin(),b3.end(), 
            std::ostream_iterator<line_type>(std::cout, "\n"));
 

    std::cout.flush();
    return 0;
}