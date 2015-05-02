#include <iostream>

template <class T> struct AbstractMatrix {};
template <class T> struct SymMatrix : AbstractMatrix<T> {};
template <class T> struct Vector {};

struct GaussElim
{
    template <class T>
    Vector<T> operator()(const AbstractMatrix<T>& mx, const Vector<T> vect)
    {
        std::cout << "GaussElim::operator()";
        return Vector<T>();
    }
};

struct DirichletSolver
{
    template <class T, class Solver>
    Vector<T> solve(const AbstractMatrix<T>& mx, const Vector<T> vect, Solver matrixAlgo);
};

template <class T, class Solver>
Vector<T> DirichletSolver::solve(const AbstractMatrix<T>& mx, const Vector<T> vect, Solver matrixAlgo)
{
    return matrixAlgo(mx, vect);
}

int main()
{
    GaussElim gauss;
    DirichletSolver dir;
    SymMatrix<double> mx;
    Vector<double> vect;
    
    dir.solve(mx, vect, gauss);
}
