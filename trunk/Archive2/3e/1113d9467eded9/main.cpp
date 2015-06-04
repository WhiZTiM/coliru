#include <stdio.h>
#include <stdlib.h>
#define Taille_MAX (100000000)

char* lire_fichier(char* chemins)
{
     FILE* fichier=fopen(chemins,"r");
     if(fichier==NULL)
          {
               return NULL;
          }
     fseek(fichier,0,SEEK_END);
     char* texte_en_memoire=(char*)malloc(ftell(fichier)*sizeof(char)+1);
     rewind(fichier);
     int i;
     for(i=0;;i++)
     {
          texte_en_memoire[i]=fgetc(fichier);
          if(texte_en_memoire[i]==EOF)
          {
               texte_en_memoire[i]='\0';
               fclose(fichier);
               return texte_en_memoire;
          }
     }
}

int rechercher(char* texte,char* recherche,int avancement)
{
     int i,j;
     for(i=avancement;texte[i]!='\0';i++)
     {
          for(j=0;recherche[j]!='\0';j++)
          {
               if(recherche[j]!=texte[i+j])
               {
                    break;
               }
          }
          if(recherche[j]=='\0')
          {
               return i;
          }
     }
     return -1;
}

int copier(char* texte,char* destination,char* a_partir,int* avancement_texte,int* avancement_destination)
{
     (*avancement_texte)=rechercher(texte,a_partir,*avancement_texte);
     if((*avancement_texte)==-1)
     {
          return -1;
     }
     while(texte[(*avancement_texte)]!='>')
     {
          (*avancement_texte)++;
     }
     (*avancement_texte)++;

     destination[*avancement_destination]='"';
     (*avancement_destination)++;
     for(;texte[(*avancement_texte)]!='<';(*avancement_texte)++)
     {
          if(texte[(*avancement_texte)]!='\n' && texte[(*avancement_texte)]!=',' && (int)texte[(*avancement_texte)]!=0 && !(texte[(*avancement_texte)]==' ' && destination[(*avancement_destination)-1]==' '))
          {
               destination[*avancement_destination]=texte[(*avancement_texte)];
               (*avancement_destination)++;
          }
     }
     destination[*avancement_destination]='"';
     (*avancement_destination)++;
     destination[*avancement_destination]=';';
     (*avancement_destination)++;
     return 0;
}

char* extraire(char* texte)
{
     char* destination=(char*)malloc(sizeof(char)*Taille_MAX);
     int avancement_texte=6200;
     int avancement_destination=0;
     int limite =rechercher(texte,"</DIV></BODY>",0);
     while(avancement_texte<(limite-1000))
     {
          if(copier(texte,destination,"    value=",&avancement_texte,&avancement_destination)==-1)
          {
               break;
          }
          copier(texte,destination,"dossiersTraitesUi_dateContact",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_dateEmmenagement1",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_dateEmmenagement2",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_dateDossierPrisUi",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_agentUi",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_departement",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_commune",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_adresse",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_mandataire",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_moa",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_42cNum",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_42cEtat",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_oeie_",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_oeieEtat",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_bdcNum_",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_devisTactEtat",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_dossierErdf",&avancement_texte,&avancement_destination);
          copier(texte,destination,"dossiersTraitesUi_oetpNum",&avancement_texte,&avancement_destination);
          destination[avancement_destination]='\n';
          avancement_destination++;
     }
     return destination;
}

void enregistrer(char* texte)
{
     FILE* fichier=fopen("./Extraction.csv","w+");
     fprintf(fichier,"%s","N° de permis;Date de contact;1er Date Emmenagement;2ème Date Emmenagement;Date prise en cpt UI;Agent prise en cpt UI;Departement;Commune;Adresse;Mandataire;MOA;N°Dem 42C;Etat 42C;Code Oeie;Etat Oeie;Bdc Tact;Etat Tact;Erdf;N°Erdf\n");
     fputs(texte,fichier);
     fclose(fichier);
}

int main()
{
     char* texte = lire_fichier("C:\Users\spfk9109\Desktop\2 extraction.htm");
     char* extraction = extraire(texte);
     enregistrer(extraction);
     free(texte);
     free(extraction);
     return 0;
}
