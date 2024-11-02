// Film

#include <iostream>
#include <cctype>
#include <iomanip>
#include <string>

using namespace std;

// Dichiarazione costanti
const int e=100;

// Dichiarazione tipi variabili
struct film{
    string titolo;
    string autore;
    float incasso;
    string nazionalita;
    bool straniero=false;
};

// Prototipi
int menu();
bool carica(film tab[], int &n);
void format(string &dato);
bool controllo(float dato);
void stampa(film tab[],int n);
int max_string(film tab[],int n);
void media(film tab[],int n);
void ricerca(film tab[],int n);
void straniero(film tab[],int n);


int main(){

    // Dichiarazione variabili
    int s,n=0;
    film tab[e];
    bool c;
    float m=0.00;

    c=false;

    do{
        s=menu();

        switch(s){

            case 1:{
                c=carica(tab,n);
                break;
            }

            case 2:{
                if(c){
                    stampa(tab,n);
                }
                else{
                    cout<<"ERRORE! carica prima i film"<<endl;
                }

                break;
            }

            case 3:{
                if(c){
                    media(tab,n);
                }
                else{
                    cout<<"ERRORE! carica prima i film"<<endl;
                }

                break;
            }

            case 4:{
                if(c){
                    ricerca(tab,n);
                }
                else{
                    cout<<"ERRORE! carica prima i film"<<endl;
                }
                break;
            }

            case 5:{
                if(c){
                    straniero(tab,n);
                }
                else{
                    cout<<"ERRORE! carica prima i film"<<endl;
                }

                break;
            }

            case 0:{
                cout<<"Arrivederci"<<endl;
                break;
            }

            default:{
                cout<<"ERRORE! Scelta non valida"<<endl;
                break;
            }
        }

    }while(s!=0);

    return 0;
}


int menu(){
    int s;

    cout<<"\t-----MENU-----"<<endl;
    cout<<"1) Inserisci i film"<<endl;
    cout<<"2) Stampa tutti i film"<<endl;
    cout<<"3) Incasso medio di un autore"<<endl;
    cout<<"4) Cerca film"<<endl;
    cout<<"5) Film straniero di maggior sucesso"<<endl;
    cout<<"0) Esci"<<endl;

    cout<<"\nInserisci scelta: ";
    cin>>s;

    cout<<endl;

    return s;
}

bool carica(film tab[],int &n){

    char ris;

    do{
        cin.ignore();

        cout<<"Inserisci il titolo del ["<<n+1<<"] film: ";
        getline(cin,tab[n].titolo);
        format(tab[n].titolo);

        cout<<"Inserisci l'autore del ["<<n+1<<"] film: ";
        getline(cin,tab[n].autore);
        format(tab[n].autore);

        cout<<"Inserisci la nazionalita del ["<<n+1<<"] film: ";
        getline(cin,tab[n].nazionalita);
        format(tab[n].nazionalita);

        if(tab[n].nazionalita!="Italia"){
            tab[n].straniero=true;
        }

        do{
            cout<<"Inserisci l'incasso del ["<<n+1<<"] film: ";
            cin>>tab[n].incasso;
        }while(!controllo(tab[n].incasso));

        cout<<"\nVuoi continuare?([S]i/[N]o): ";
        cin>>ris;

        ris=toupper(ris);

        n++;

        cout<<endl;

    }while(ris=='S');


    return true;
}

void format(string &dato){

    dato[0]=toupper(dato[0]);

    for(int i=1; i<dato.length();i++){
        if(dato[i]==' '){
            dato[i+1]=toupper(dato[i+1]);
            i++;
            continue;
        }

        dato[i]=tolower(dato[i]);
    }

    dato+=" ";
}

bool controllo(float dato){
    if(dato<=0){
        cout<<"ERRORE! Inserisci un numero maggiore di 0"<<endl;
        return false;
    }
    else{
        return true;
    }
}

void stampa(film tab[], int n){
    
    int space=max_string(tab,n)+5;

    cout<<left<<setw(space)<<"Autore"
        <<setw(space)<<"Titolo"
        <<setw(space)<<"Incasso"
        <<setw(space)<<"Nazionalita'"
    <<endl;

    for(int i=0;i<n;i++){
        cout<<left<<setw(space)<<tab[i].autore
            <<setw(space)<<tab[i].titolo
            <<setw(space)<<fixed<<setprecision(3)<<tab[i].incasso
            <<setw(space)<<tab[i].nazionalita
        <<endl;
    }
}


int max_string(film tab[],int n){

    int max_len=0,temp [3];

    for(int i=0;i<n;i++){
        temp[0]=tab[i].autore.length();
        temp[1]=tab[i].titolo.length();
        temp[2]=tab[i].nazionalita.length();

        for(int j=0;j<3;j++){
            if(temp[j]>max_len){
                max_len=temp[j];
            }
        }
    }

    return max_len;
}

void media(film tab[],int n){

    string autore;
    int y=0;
    float x=0.00; 
    bool c=false;

    cin.ignore();
    cout<<"Inserisci l'autore: ";
    getline(cin,autore);
    format(autore);

    for(int i=0;i<n;i++){
        if(tab[i].autore==autore){
            x+=tab[i].incasso;
            y++;
            c=true;
        }
    }

    if(c){
        cout<<"La media degl'incassi di "<<autore<<" e' "<<fixed<<setprecision(3)<<x/y<<endl;
    }
    else{
        cout<<"L'autore non esiste"<<endl;
    }
}

void ricerca(film tab[],int n){

    bool c=false;
    int i=0;
    string titolo;

    cin.ignore();
    cout<<"Inserisci il film da cercare: ";
    getline(cin,titolo);

    format(titolo);

    while(i<n && c==false){
        if(tab[i].titolo==titolo){
            c=true;
        }
        else{
            i++;
        }
    }

    if(c){
        cout<<"\nFILM TROVATO!"<<endl;
        cout<<"Titolo: "<<tab[i].titolo<<endl;
        cout<<"Autore: "<<tab[i].autore<<endl;
        cout<<"Incasso: "<<fixed<<setprecision(3)<<tab[i].incasso<<endl;
        cout<<"Nazionalita': "<<tab[i].nazionalita;
    }
    else{
        cout<<"Il film non esiste"<<endl;
    }
}

void straniero(film tab[],int n){

    bool c=false;
    film temp;

    temp.incasso=-1;

    for(int i=0;i<n;i++){
        if(tab[i].straniero==true && tab[i].incasso>temp.incasso){
            temp=tab[i];
            c=true;
        }
    }

    if(c){
        cout<<"\nFILM STRANIERO DI MAGGIOR SUCCESSO: "<<endl;
        cout<<"Titolo: "<<temp.titolo<<endl;
        cout<<"Autore: "<<temp.autore<<endl;
        cout<<"Incasso: "<<fixed<<setprecision(3)<<temp.incasso<<endl;
        cout<<"Nazionalita': "<<temp.nazionalita<<endl;
    }
    else{
        cout<<"Non ci sono film stranieri"<<endl;
    }
}