#include <stdio.h>

class ABB
{
public:
    // ... resto de la clase
    
    operator Abin<T>() const;
    
    // ... 
    
private:
    // ...
    
    void rellenarHijosAbin(Abin<T>& abin, typename Abin<T>::nodo rAbin, nodo rABB) const;
};

template<typename T>
ABB<T>::operator Abin<T>() const
{
    Abin<T> abin;
    
    abin.crearRaizB(r->elto);
    
    rellenarHijosAbin(abin, abin.raizB(), r);
    
    return abin;
}

template<typename T>
void ABB<T>::rellenarHijosAbin(Abin<T>& abin, typename Abin<T>::nodo rAbin, nodo rABB) const
{
    nodo nABBIzqdo = rABB->hizq;
    nodo nABBDrcho = rABB->hder;
    
    if (nABBIzqdo != NODO_NULO) {
        abin.insertarHijoIzqdo(nodo, nABBIzqdo->elto);
        rellenarHijosAbin(abin, abin.hijoIzqdo(rAbin), nABBIzqdo);
    }
    
    if (nABBDrcho != NODO_NULO) {
        abin.insertarHijoDrcho(nodo, nABBDrcho->elto);
        rellenarHijosAbin(abin, abin.hijoDrcho(rAbin), nABBDrcho);
    }
}


