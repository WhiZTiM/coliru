#include <iostream>
#include <fstream>
#include <string>
#include "dico.h"

using namespace std;

void afficheMot(int lettreTrouve[], const char motSecret[], int taille); //Fonction affichant le mot secret
char lireCaractere(); //Fonction qui permet de lire un caractere
int rechercheLettre(int lettreTrouve[], const char motSecret[], char maLettre, int taille); //Fontion de recherche caractere
int gagne(int lettreTrouve[], int taille); //Fonction qui définit si le mot a été trouvé


int main(void)
{
    string motPiocher, reponse; //Déclaration de deux chaines
	int taille = 0; //Initialisation de la taille de mot
	bool jouer = true; //variable bool pour faire une boucle sur le programme
	char maLettre = 0; //Initialisation de la variable ma lettre
	int coupsRestant = 10; //nombre de coups restant
	while(jouer){
		if(piocheMot(motPiocher, taille))
                    cout << "Erreur aucun mot trouve !" << endl;
		int *lettreTrouve = NULL;
		lettreTrouve = new int[taille];
		const char *motSecret = NULL;
		motSecret = new char[taille+1];
		motSecret = motPiocher.c_str();
		//Initialisation du tableau lettreTrouver
		for(int i = 0; i < taille; i++)
		lettreTrouve[i] = 0;
	            	cout << "Bienvenu dans le Pendu !\n\n\n" << endl;
		while(coupsRestant > 0 && gagne(lettreTrouve, taille))
		{
                    cout << "Il vous reste " << coupsRestant << " coup a jouer\n" << endl;
		           	cout << "Quel est le mot secret ? ";
			afficheMot(lettreTrouve, motSecret, taille);
		           	cout << endl;
	            	cout << "Proposez une lettre : ";
			maLettre = lireCaractere();
			         cout << endl;
			if(!rechercheLettre(lettreTrouve, motSecret, maLettre, taille))
			coupsRestant--;
		}
		if(!gagne(lettreTrouve, taille))
                     cout << "Gagne Le mot secret etait bien : " << motSecret << endl;
		else
		           	 cout << "Vous avez perdu le mot secret etait : " << motSecret << endl;
		coupsRestant = 10;
		             cout << "Rejouer (oui ou non) : ";
	               	cin >> reponse;
		while(reponse != "oui" && reponse != "non")
		{
                    cout << "Choisir entre oui et non : ";
		           	cin >> reponse;
		}
		if(reponse == "non")
		jouer = false;
	}
}

void afficheMot(int lettreTrouve[],const char motSecret[], int taille)
{
	for(int i = 0; i < taille; i++)
	{
		if(lettreTrouve[i] == 1)
		{
			cout << motSecret[i];
		}
		else
			cout << " _ ";
	}
	cout << endl;
}

char lireCaractere()
{
	char caractere = 0;
	caractere = getchar();
	caractere = toupper(caractere);
	while(getchar() != '\n');
	return caractere;
}

int rechercheLettre(int lettreTrouve[], const char motSecret[], char maLettre, int taille)
{
	int trouve = 0;
	for(int i = 0; i < taille; i++)
	{
		if(motSecret[i] == maLettre)
		{
			lettreTrouve[i] = 1;
			trouve = 1;
		}
	}
	return trouve;
}

int gagne(int lettreTrouve[], int taille)
{
	int somme = 0;
	int gain = 1;
	for(int i = 0; i < taille; i++)
	{
		somme += lettreTrouve[i];
	}
	if(somme == taille)
	gain = 0;
	return gain;
}

    
 
    std::cout << "i is " << type_names[std::type_index(typeid(i))] << '\n';
    std::cout << "d is " << type_names[std::type_index(typeid(d))] << '\n';
    std::cout << "a is " << type_names[std::type_index(typeid(a))] << '\n';
    std::cout << "b is " << type_names[std::type_index(typeid(*b))] << '\n';
    std::cout << "c is " << type_names[std::type_index(typeid(*c))] << '\n';
    std::cout << "bs is " << type_names[std::type_index(typeid(*bs))] << '\n';
}