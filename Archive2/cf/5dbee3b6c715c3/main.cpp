    #include<iostream>
    using namespace std;

    class pacient{
    protected:
        int colesterol;
        int tensiune_arteriala;
        char * nume;
        char * prenume;
        int varsta;
        char * adresa;
        char * data_analiza;
    public:
        //constructor cu toti parametrii
        pacient(){};
        pacient(int colesterol, int tensiune_art, char * nume, char *prenume,
            int varsta, char * adresa, char *data_analiza)
        {
            (*this).colesterol = colesterol;
            tensiune_arteriala = tensiune_art;
            strcpy((*this).nume, nume);
            strcpy((*this).prenume, prenume);
            (*this).varsta = varsta;
            strcpy((*this).adresa, adresa);
            strcpy((*this).data_analiza, data_analiza);
        }
        //destructor
        ~pacient(){
            colesterol = 0;
            tensiune_arteriala = 0;
            strcpy(nume, "");
            strcpy(prenume, "");
            varsta = 0;
            strcpy(adresa, "");
            strcpy(data_analiza, "");
        }
        //functie virtuala
        virtual char * get_name() { return "Este pacient"; }

        //citirea si afisarea obiectelor
        friend istream &operator>> (istream&in, pacient&ob);
        friend ostream &operator<< (ostream&out, const pacient&ob);

    };

    istream& operator>>(istream &in, pacient &ob){
        cout << "Nume: "; gets(ob.nume); cout << endl;
        cout << "Prenume: "; gets(ob.prenume); cout << endl;
        cout << "Varsta: "; cin >> ob.varsta; cout << endl;
        cout << "Adresa: "; gets(ob.adresa); cout << endl;
        cout << "Data analiza: "; gets(ob.data_analiza); cout << endl;
        cout << "Colesterol: "; cin>>ob.colesterol; cout << endl;
        cout << "Tensiune arteriala: "; cin>>ob.tensiune_arteriala; cout << endl;
        return in;
    }

    ostream &operator<< (ostream&out, const pacient&ob){
        cout << "Nume: "; puts(ob.nume); cout << endl;
        cout << "Prenume: "; puts(ob.prenume); cout << endl;
        cout << "Varsta: "; cout << ob.varsta; cout << endl;
        cout << "Adresa: "; puts(ob.adresa); cout << endl;
        cout << "Data analiza: "; puts(ob.data_analiza); cout << endl;
        cout << "Colesterol: "; cout << ob.colesterol; cout << endl;
        cout << "Tensiune arteriala: "; cout << ob.tensiune_arteriala; cout << endl;
        return out;
    }

    int main()
    {
        pacient a;
        cin >> a;
        cout << a;
    }