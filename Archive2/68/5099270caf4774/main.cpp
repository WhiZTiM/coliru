/***********************************************/
/*    Exemple de résolution de l'examen       */
/*********************************************/
 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>   
using namespace std;
 
/******************************************************/
/*  PROTOTYPES DES FONCTIONS ET STRUCTURES            */
/******************************************************/
 
struct s_enregistrement{
    char pseudo[34];
    int jour, mois, annee;
};
 
void programmePrincipal();
int afficherMenu(void);
void affichierFichier(char nomFichier[]);
s_enregistrement* copieFichierDansTableau(char nomFichier[], s_enregistrement *tabStruct, int *tailleTab);
void affichageTab(s_enregistrement *tabStruct, int taille);
s_enregistrement *remplacercontenuTab(s_enregistrement *tabStruct, int *taille, char nomFichier[]);
 
/******************************************************/
/*  PROGRAMME PRINCIPALE                              */
/******************************************************/
int main(){
 
    // 1. Ecran d'accueil
    system("cls");
    cout << "Examen du 16 juin 2015" << endl << endl;
    system("pause");
 
    // 2. Gestion du menu et des fonctionnalités du programme      
    programmePrincipal();
 
    // 3. Fin du programme
    system("cls");
    cout << "Fin du programme" << endl << endl;
    return 0;
}
 
 
/******************************************************/
/*  DEFINITION DES PRINCIPALES FONCTIONS              */
/******************************************************/
 
void programmePrincipal(){
    // 0. Déclaration des variables
    int choix;
    s_enregistrement *tab = NULL;
    int taille = 0;
 
 
    do{
        // 1. Affichage du menu + saisie du choix de l'utilisateur
        choix = afficherMenu();
 
        // 2. On réalise le choix de l'utilisateur
        switch (choix){
        case 1: affichierFichier("fichier1.gwe");
            break;
        case 2: affichierFichier("fichier2.gwe");
            break;
        case 3: tab = copieFichierDansTableau("fichier1.gwe", tab, &taille);
            break;
        case 4:  tab = copieFichierDansTableau("fichier2.gwe", tab, &taille);
            break;
        case 5:  tab = remplacercontenuTab(tab, &taille, "fichier1.gwe");
            break;
        case 6:  tab = remplacercontenuTab(tab, &taille, "fichier2.gwe");
            break;
        case 7:  affichageTab(tab, taille);
            break;
        }
    } while (choix != 8);
}
 
// fonction afficher menu
int afficherMenu(void){
    // 0. Déclaration des variables
    int choix;
 
    // 1. Affichage du menu
    system("cls");
    cout << "Voulez-vous : " << endl << endl;
    cout << "[1] Afficher le contenu du 1er fichier" << endl;
    cout << "[2] Afficher le contenu du 2eme fichier" << endl;
    cout << "[3] Copier le contenu du 1er fichier dans le tableau" << endl;
    cout << "[4] Copier le contenu du 2eme fichier dans le tableau" << endl;
    cout << "[5] Remplacer le tableau par le contenu du 1er fichier" << endl;
    cout << "[6] Remplacer le tableau par le contenu du 2eme fichier" << endl;
    cout << "[7] Afficher le contenu du tableau" << endl;
    cout << "[8] Quitter le programme" << endl << endl;
    cout << "Votre choix : ";
 
    // 2. Saisie du choix de l'utilisateur + validation automatique
    cin >> choix;
    while (choix<1 || choix>8){
        cout << "Erreur. Saisissez une autre valeur : ";
        cin >> choix;
    }
 
    // 3. Le choix est renvoyé au programme appelant
    return choix;
}
 
/////////////////////////////////////////////////////////
//fonction qui affiche le fichier demande
void affichierFichier(char nomFichier[]){
    FILE *fichier;
    s_enregistrement etudiant;
 
    system("cls");
    // ouverture et verrification de l'existance du fichier
    fichier = fopen(nomFichier, "rb");
    if (fichier == NULL){
        cout << "le fichier n existe pas " << endl;
        system("pause");
        return;
    }
 
    //lecture du fichier 
    while (fread(&etudiant, sizeof(s_enregistrement), 1, fichier) != 0){
        cout << "Pseudo  :" << etudiant.pseudo << endl;
        cout << "Jour    :" << etudiant.jour << endl;
        cout << "Mois    :" << etudiant.mois << endl;
        cout << "Annee   :" << etudiant.annee << endl;
        cout << "-------------------------------------------" << endl << endl;
    }
 
    if (!feof(fichier)){
        cout << "impossible d ouvrir le fichier" << endl;
    }
 
    fclose(fichier);
    system("pause");
}
/////////////////////////////////////////////////////////////////////////////////////////////
 
//copie fichier dans tableau
s_enregistrement* copieFichierDansTableau(char nomFichier[], s_enregistrement *tabStruct, int *tailleTab){
    FILE *fichier;
    s_enregistrement etudiantFichier;
 
    system("cls");
    // ouverture et verrification de l'existance du fichier
    fichier = fopen(nomFichier, "rb");
    if (fichier == NULL){
        cout << "le fichier n existe pas " << endl;
        system("pause");
        return 0;
    }
 
    // lecture du fichier et copie dans le tableau de structure
    while (fread(&etudiantFichier, sizeof(s_enregistrement), 1, fichier) != 0){
        if (*tailleTab == 0){ // si la taille est = 0 nous faisons un malloc 
            tabStruct = (s_enregistrement*)malloc(*tailleTab*sizeof(s_enregistrement));
        }
        else{
            tabStruct = (s_enregistrement*)realloc(tabStruct, (*tailleTab + 1)*sizeof(s_enregistrement));
        }
        //copie des différents élements du ficier dans le tableau(l'erreur se trouve dans ces 4 lignes ci-dessous)
        strcpy((*tabStruct).pseudo, etudiantFichier.pseudo);// copie d'une chaine de caractère
        (*tabStruct).jour = etudiantFichier.jour;
        (*tabStruct).mois = etudiantFichier.mois;
        (*tabStruct).annee = etudiantFichier.annee; // copie des entiers 
 
        *tailleTab = *tailleTab + 1;
 
        //tout marche bien mais le problème j'arrive pas avoir ou placer mon tailleTab - 1; car il le faut pour que l'affichage
        // apparait bien dans le fonction 7. mais tout es bon 
        //je vais reflechir encore voir comment trouvé ma faute
 
    }
    cout << "votre copie a ete effectuee" << endl;
    system("pause");
 
    return tabStruct;
}
 
// fonction afficher tableau
void affichageTab(s_enregistrement *tabStruct, int taille){
    s_enregistrement  *pt;
 
    system("cls");
    for (pt = tabStruct; pt < tabStruct + taille; pt++){
        cout << "Pseudo  :" << pt->pseudo << endl;
        cout << "Jour    :" << pt->jour << endl;
        cout << "Mois    :" << pt->mois << endl;
        cout << "Annee   :" << pt->annee << endl;
        cout << "-------------------------------------------" << endl << endl;
    }
 
 
    system("pause");
}
 
// remplacer le tableau par le contenu du fichier
s_enregistrement *remplacercontenuTab(s_enregistrement *tabStruct, int *taille, char nomFichier[]){
    // vidons le tableau
    tabStruct = NULL;
    *taille = 0;
 
    system("cls");
    // appel à la fonction de copieFichierDansTableau
    tabStruct = copieFichierDansTableau(nomFichier, tabStruct, taille);
 
    cout << "le tableau a bien ete vide" << endl;
    cout << "Remplacement du contenu par le fichier" << endl;
 
    system("pause");
    return tabStruct;
}