#include <iostream>
// Добавляем нужное пространство имен.
#include <vector>
using namespace std;
void main()
{
    // Объявляем вектор из целых.
    vector <int> k;
    // Добавляем элементы в конец вектора.
    k.push_back(22);
    k.push_back(11);
    k.push_back(4);
    // Показываем все элементы вектора.
    for (int i = 0; i<k.size(); i++)
    {
        cout<<k[i]<<"\n";
    }
    cout<<"***\n";
    // Удаляем элемент с конца вектора.
    k.pop_back();
    // Показываем все элементы вектора.
    for (i = 0; i<k.size(); i++)
    {
        cout<<k[i]<<"\n";
    }
    cout<<"***\n";

    // Удаляем все элементы ветораю
    k.clear();
    // Проверяем, что вектор пуст.
    if(k.empty)
    {
        cout<<"Vector is empty\n";
    }
}