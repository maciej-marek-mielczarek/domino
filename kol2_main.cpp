#include <iostream>
#include<stdexcept>
#include<ctime>
#include<cstdlib>

using namespace std;

#define MAX_LICZBA_GRACZY 5
#define LICZBY_NA_KLOCKACH 6


struct lista_klockow {
    struct klocek
        {
        short prawa_liczba;
        short lewa_liczba;
        klocek* nastepny;
        klocek* poprzedni;
	klocek()
	    {
        prawa_liczba = -1;
        lewa_liczba = -1;
        nastepny = NULL;
        poprzedni = NULL;
	    }
	~klocek()
	    {
	    }
	  
        };
    klocek* pierwszy;
    klocek* przedostatni;
public:
    lista_klockow()//konstruktor listy klockow
        {
        pierwszy = NULL;
        przedostatni = NULL;
        }
    short lewy_koniec()//zwraca lewy koniec listy
        {
        if(pierwszy == NULL)
            return -1;//pusta lista
        return pierwszy->lewa_liczba;
        }
    short prawy_koniec()//zwraca prawy koniec listy
        {
        if(pierwszy == NULL)
            return -1;//pusta lista
        if(przedostatni == NULL)
            return pierwszy->prawa_liczba;//jeden klocek na liscie
        return przedostatni->nastepny->prawa_liczba;
        }
    void wyswietl()//wyswietla liste klockow
        {
        if(pierwszy == NULL)
            {
            cout << "\n";
            return;
            }
        cout << "[" << pierwszy->lewa_liczba << "|" << pierwszy->prawa_liczba << "] ";
        if(przedostatni == NULL)
            {
            cout << "\n";
            return;
            }
        klocek* wyswietlany = pierwszy->nastepny;
        while(wyswietlany)
            {
            cout << "[" << wyswietlany->lewa_liczba << "|" << wyswietlany->prawa_liczba << "] ";
            wyswietlany = wyswietlany->nastepny;
            }
        cout << "\n";
        return;
        }
    void dodaj_pierwszy (short lewa_liczba, short prawa_liczba)//dodaje klocek na poczatek
        {
        if(pierwszy == NULL)
            {
            pierwszy = new klocek;
            pierwszy->lewa_liczba = lewa_liczba;
            pierwszy->prawa_liczba = prawa_liczba;
            pierwszy->nastepny = NULL;
            pierwszy->poprzedni = NULL;
            return;
            }
        if(przedostatni == NULL)
            {
            przedostatni = new klocek;
            przedostatni->lewa_liczba = lewa_liczba;
            przedostatni->prawa_liczba = prawa_liczba;
            przedostatni->nastepny = pierwszy;
            przedostatni->poprzedni = NULL;
            pierwszy->poprzedni = przedostatni;
            pierwszy = przedostatni;
            return;
            }
        klocek* drugi = pierwszy;
        pierwszy = new klocek;
        pierwszy->lewa_liczba = lewa_liczba;
        pierwszy->prawa_liczba = prawa_liczba;
        pierwszy->nastepny = drugi;
        drugi->poprzedni = pierwszy;
        return;
        }
    void dodaj_ostatni (short lewa_liczba, short prawa_liczba)//dodaje klocek na koniec
        {
        if(pierwszy == NULL)
            {
            dodaj_pierwszy (lewa_liczba, prawa_liczba);
            return;
            }
        if (przedostatni == NULL)
            {
            przedostatni = new klocek;
            pierwszy->nastepny = przedostatni;
            przedostatni->poprzedni = pierwszy;
            przedostatni->nastepny = NULL;
            przedostatni->lewa_liczba = lewa_liczba;
            przedostatni->prawa_liczba = prawa_liczba;
            przedostatni = pierwszy;
            return;
            }
        przedostatni = przedostatni->nastepny;
        klocek* ostatni = new klocek;
        przedostatni->nastepny = ostatni;
        ostatni->poprzedni = przedostatni;
        ostatni->nastepny = NULL;
        ostatni->lewa_liczba = lewa_liczba;
        ostatni->prawa_liczba = prawa_liczba;
        return;
        }
    bool usun_klocek(short liczba_1, short liczba_2)//usuwa podany klocek z listy
        {//zwraca true, jesli sie to udalo, a false jesli nie znaleziono podanego klocka na liscie
        klocek* sprawdzany = pierwszy;
        klocek* sprawdzony = pierwszy;
        while(sprawdzany)
            {
            if(((liczba_1 == sprawdzany->lewa_liczba) && (liczba_2 == sprawdzany->prawa_liczba)) || ((liczba_2 == sprawdzany->lewa_liczba) && (liczba_1 == sprawdzany->prawa_liczba)))
                {
                //Przed skasowaniem klocka kaze sasiednim klockom wskazywac na siebie nawzajem.
                if(sprawdzany->poprzedni != NULL)
                    {
                    //To nie jest pierwszy klocek na liscie.
                    sprawdzany->poprzedni->nastepny = sprawdzany->nastepny;
                    }
                else
                    {
                    pierwszy = sprawdzany->nastepny;
                    }
                if(sprawdzany->nastepny != NULL)
                    {
                    //To nie jest ostatni klocek na liscie.
                    sprawdzany->nastepny->poprzedni = sprawdzany->poprzedni;
                    if(sprawdzany->nastepny->nastepny == NULL)
                        {
                        //Przedostatni klocek na liscie
                        przedostatni = przedostatni->poprzedni;
                        }
                    }
                else
                    {
                    //Ostatni klocek na liscie.
                    if(pierwszy != NULL)
                        {//Nie jest to jedyny klocek na liscie.
                        przedostatni = przedostatni->poprzedni;
                        }
                    }
                delete sprawdzany;
                return true;
                }
            else
                {
	            sprawdzony = sprawdzany;
                sprawdzany = sprawdzany->nastepny;
                }
            //sprawdzony = sprawdzony->nastepny;
            }
        return false;
        }
    void dostepne_liczby(bool liczby[LICZBY_NA_KLOCKACH])//zwraca przez referencje zbior liczb wystepujacych na liscie
        {
        for(short i=0; i<LICZBY_NA_KLOCKACH; ++i)
            {
            liczby[i] = false;
            }
        klocek* sprawdzany = pierwszy;
        while(sprawdzany)
            {
            liczby[sprawdzany->lewa_liczba] = true;
            liczby[sprawdzany->prawa_liczba] = true;
            sprawdzany = sprawdzany->nastepny;
            }
        return;
        }
    ~lista_klockow()//destruktor listy klockow
        {
        while(przedostatni)
            {
            delete przedostatni->nastepny;
            przedostatni = przedostatni->poprzedni;
            }
        if(pierwszy)
            {
            delete pierwszy;
            }
        }
      };
struct worek: public lista_klockow
    {
    public:
    short pusty_worek;
    void mieszaj_worek()
        {
        //wylosuj 2 liczby od 0 do LICZBY_NA_KLOCKACH i rzuc moneta czy przelozyc klocek z tymi liczbami na poczatek czy na koniec
        //powtorz duzo razy, powiedzmy 100*LICZBY_NA_KLOCKACH^2
        for(int i=0; i<=(LICZBY_NA_KLOCKACH+1)*(LICZBY_NA_KLOCKACH+1); ++i)
            {
            short a, b;
            a=rand()%(LICZBY_NA_KLOCKACH+1);
            b=rand()%(LICZBY_NA_KLOCKACH+1);
            usun_klocek(a,b);
            if(rand()%2)
                {
                dodaj_pierwszy(a,b);
                }
            else
                {
                dodaj_ostatni(a,b);
                }
            }
        }
    worek():lista_klockow()//konstruktor tworzy niepotasowana liste klockow
        {
        this->pusty_worek = MAX_LICZBA_GRACZY;
        for(short i=0; i<=LICZBY_NA_KLOCKACH; ++i)
            {
            for(short j=i; j<=LICZBY_NA_KLOCKACH; ++j)
                {
                lista_klockow::dodaj_ostatni(i,j);
                }
            }
        }
    ~worek()
        {
        }
    };
worek worek;
enum typ_gracza {cpu_latwy, cpu_trudny, czlowiek};
struct gracz
    :public lista_klockow
    //dziedzicz po lista_klockow
    {
    typ_gracza kto_steruje;
    //wybierz akcje do wykonania
    gracz* nastepny_gracz;
    gracz* poprzedni_gracz;
    static gracz* poczatek_listy_graczy;
    static gracz* koniec_listy_graczy;
    static short liczba_graczy;
    short id;
    static short przyblokowani;
    gracz(typ_gracza kto_ma_sterowac = czlowiek):lista_klockow()
    //Konstruktor nadaje graczowi numer, dodaje go do listy graczy i okresla jego typ.
    //Domyslnie tworzony jest gracz czlowiek.
        {
        //Dodaj gracza do listy graczy.
        if(liczba_graczy == 0)
            {
            poczatek_listy_graczy = this;
            koniec_listy_graczy = this;
            nastepny_gracz = this;
            poprzedni_gracz = this;
            }
        if(liczba_graczy >= 1)
            {
            koniec_listy_graczy->nastepny_gracz = this;//Nie mozna tego zrobic jesli lista graczy jest pusta, stad poprzedni if.
            poprzedni_gracz = koniec_listy_graczy;
            koniec_listy_graczy = this;
            nastepny_gracz = poczatek_listy_graczy;
            poczatek_listy_graczy->poprzedni_gracz = this;//Jak wyzej.
            }
        id = ++liczba_graczy;//nadaj graczowi numer
        kto_steruje = kto_ma_sterowac;//okresl typ gracza
        }
    bool dobierz_klocek()//bierze klocek z worka i dodaje go na koniec swojej listy. False jesli worek byl pusty.
        {
        if(worek.pierwszy)
            {
            //najpierw dodaj pierwszy klocek z worka na koniec swojej listy
            dodaj_ostatni(worek.pierwszy->lewa_liczba, worek.pierwszy->prawa_liczba);
            //potem usun pierwszy klocek z worka
            worek.usun_klocek(worek.pierwszy->lewa_liczba, worek.pierwszy->prawa_liczba);
            return true;
            }
        return false;
        }
    
    bool mozliwosc_ruchu(short lewy_koniec_stolu,short prawy_koniec_stolu)
        {
        if(lewy_koniec_stolu == -1 || prawy_koniec_stolu == -1)
            return true;
        klocek* sprawdzany = pierwszy;
        while(sprawdzany)
            {
            if((sprawdzany->lewa_liczba == lewy_koniec_stolu) || (sprawdzany->lewa_liczba == prawy_koniec_stolu))
                return true;
            if((sprawdzany->prawa_liczba == lewy_koniec_stolu) || (sprawdzany->prawa_liczba == prawy_koniec_stolu))
                return true;
            sprawdzany = sprawdzany->nastepny;
            }
        return false;
        }
    bool wez_klocek(short liczba_na_klocku_a, short liczba_na_klocku_b)
        {
        if(pierwszy == NULL)
            return false;
        if((
                (pierwszy->lewa_liczba == liczba_na_klocku_a)
                &&
                (pierwszy->prawa_liczba == liczba_na_klocku_b))
            ||
                ((pierwszy->lewa_liczba == liczba_na_klocku_b)
                &&
                (pierwszy->prawa_liczba == liczba_na_klocku_a)
            ))
            {
            //bierzemy pierwszy klocek z listy
            if(pierwszy->nastepny != NULL)
                pierwszy->nastepny->poprzedni = NULL;
            delete pierwszy;
            return true;
            }
        if(przedostatni == NULL)
            return false;//na liscie jest tylko 1 klocek i zostal on juz sprawdzony
        if((
                (przedostatni->nastepny->lewa_liczba == liczba_na_klocku_a)
                &&
                (przedostatni->nastepny->prawa_liczba == liczba_na_klocku_b))
            ||
                ((przedostatni->nastepny->lewa_liczba == liczba_na_klocku_b)
                &&
                (przedostatni->nastepny->prawa_liczba == liczba_na_klocku_a)
            ))
            {
            //bierzemy ostatni klocek z listy
            delete przedostatni->nastepny;
            przedostatni->nastepny = NULL;
            return true;
            }
        //jesli program doszedl tutaj, to znaczy ze na liscie sa conajmniej 3 klocki
        klocek* sprawdzany = pierwszy->nastepny;
        while(sprawdzany)//ostatni klocek moze zostac sprawdzony 2 razy, ale za to warunek zakonczenia petli jest prostszy
            {
            if((sprawdzany->lewa_liczba == liczba_na_klocku_a) && (sprawdzany->prawa_liczba == liczba_na_klocku_b))
                {
                sprawdzany->poprzedni->nastepny = sprawdzany->nastepny;
                sprawdzany->nastepny->poprzedni = sprawdzany->poprzedni;
                delete sprawdzany;
                return true;
                }
            if((sprawdzany->lewa_liczba == liczba_na_klocku_b) && (sprawdzany->prawa_liczba == liczba_na_klocku_a))
                {
                sprawdzany->poprzedni->nastepny = sprawdzany->nastepny;
                sprawdzany->nastepny->poprzedni = sprawdzany->poprzedni;
                delete sprawdzany;
                return true;
                }
            }
        return false;
        }
    klocek* daj_nty_klocek(short numer_klocka)
        {
        if(numer_klocka<1)
            return NULL;
        klocek* zwracany = pierwszy;
        for(short i = 1; i<numer_klocka; ++i)
            {
            if(zwracany == NULL)
                return NULL;
            zwracany = zwracany->nastepny;
            }
        return zwracany;
        }
    void rozdaj()
        {
        gracz* bioracy_klocek = nastepny_gracz;//Rozdawanie klockow zaczynamy od nastepnego gracza.
        for(short i=0; i<5; ++i)
            {
            do
                {
                bioracy_klocek->dobierz_klocek();
                bioracy_klocek = bioracy_klocek->nastepny_gracz;
                }
            while(bioracy_klocek != nastepny_gracz);
            }
        }
    void rusz_sie(lista_klockow* stol)
        {
        //Na poczatku tury wypisz klocki wszystkich graczy i klocki na stole.
        cout << "Klocki znajdujace sie na stole:\n";
        stol->wyswietl();
        gracz* pokazujacy_klocki = poczatek_listy_graczy;
        for(short numer_gracza = 1; numer_gracza <= liczba_graczy; ++numer_gracza)
            {
            cout << "Klocki gracza numer " << (pokazujacy_klocki->id) << ": ";
            pokazujacy_klocki->wyswietl();
            pokazujacy_klocki = pokazujacy_klocki->nastepny_gracz;
            }
        if(kto_steruje == czlowiek)
            {
            if(mozliwosc_ruchu(stol->lewy_koniec(), stol->prawy_koniec()))
                {
                bool dolozono = false;
	            klocek* do_wylozenia = NULL;
                do
                    {
                    short akcja = 0;
                    cout << "Ktory klocek chcesz wylozyc, graczu numer " << id << "?\n";
                    do
                        {
                        do
                            {
                            cout << "Numer klocka na liscie: ";
                            if(!cin)
                                {
                                cin.clear();
                                cin.ignore(1024,'\n');
                                }
                            cin >> akcja;//Wczytujemy numer klocka do wylozenia.
                            }
                        while(!cin);
                        do_wylozenia = daj_nty_klocek(akcja);
                        }
                    while(do_wylozenia == NULL);
                    //Mamy adres klocka do wylozenia. Dokladamy do stolu.
                    cout << "Czy chcesz dolozyc klocek z (l)ewej, czy z (p)rawej strony stolu?\n";
                    char strona = 'l';
                    do
                        {
                        if(!cin)
                            {
                            cin.clear();
                            cin.ignore(1024,'\n');
                            }
                        cin >> strona;//Wczytujemy strone z ktorej gracz chce dolozyc klocek.
                        }
                    while(!cin);
                        if(stol->lewy_koniec() == -1)
                            {
                            stol->dodaj_pierwszy(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                            dolozono = true;
                            }
                        else if((strona == 'l') || (strona == 'L'))
                            {
                            if((do_wylozenia->lewa_liczba) == (stol->lewy_koniec()))
                                {
                                stol->dodaj_pierwszy(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                                dolozono = true;
                                }
                            else if((do_wylozenia->prawa_liczba) == (stol->lewy_koniec()))
                                {
                                stol->dodaj_pierwszy(do_wylozenia->lewa_liczba, do_wylozenia->prawa_liczba);
                                dolozono = true;
                                }
                            }
                        else if((strona == 'p') || (strona == 'P'))
                            {
                            if((do_wylozenia->lewa_liczba) == (stol->prawy_koniec()))
                                {
                                stol->dodaj_ostatni(do_wylozenia->lewa_liczba, do_wylozenia->prawa_liczba);
                                dolozono = true;
                                }
                            else if((do_wylozenia->prawa_liczba) == (stol->prawy_koniec()))
                                {
                                stol->dodaj_ostatni(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                                dolozono = true;
                                }
                            }
                    }
                while(!dolozono);
                cout << "Gracz " << id << " doklada klocek " << "[" << do_wylozenia->lewa_liczba << "|" << do_wylozenia->prawa_liczba << "].\n";
                usun_klocek(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                przyblokowani = 0;
                }
            else
                {
                cout << "Gracz " << id << " nie moze dolozyc klocka i siega do worka.\n";
                if(!(dobierz_klocek()))
                    {
                    ++przyblokowani;
                    }
                //Obsluga remisu.
                }
            }//Czlowiek, komputer latwy i komputer trudny inaczej sie ruszaja.
        if(kto_steruje == cpu_latwy)
            {
            if(mozliwosc_ruchu(stol->lewy_koniec(), stol->prawy_koniec()))
                {
                klocek* do_wylozenia = pierwszy;
                bool dolozono = false;
                while(!dolozono)
                    {
                    if(((do_wylozenia->lewa_liczba) == (stol->lewy_koniec())) || ((stol->lewy_koniec()) == -1))
                        {
                        stol->dodaj_pierwszy(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                        dolozono = true;
                        }
                    else if((do_wylozenia->prawa_liczba) == (stol->lewy_koniec()))
                        {
                        stol->dodaj_pierwszy(do_wylozenia->lewa_liczba, do_wylozenia->prawa_liczba);
                        dolozono = true;
                        }
                    else if((do_wylozenia->lewa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(do_wylozenia->lewa_liczba, do_wylozenia->prawa_liczba);
                        dolozono = true;
                        }
                    else if((do_wylozenia->prawa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                        dolozono = true;
                        }
                    if(dolozono)
                        {
                        cout << "Gracz " << id << " doklada klocek " << "[" << do_wylozenia->lewa_liczba << "|" << do_wylozenia->prawa_liczba << "].\n";
                        usun_klocek(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                        przyblokowani = 0;
                        }
                    else
                        {
                        do_wylozenia = do_wylozenia->nastepny;
                        }
                    }
                }
            else
                {
                cout << "Gracz " << id << " nie moze dolozyc klocka i siega do worka.\n";
                if(!dobierz_klocek())
                    {
                    ++przyblokowani;
                    }
                //Obsluga remisu.
                }
            }
        if(kto_steruje == cpu_trudny)
            {
            if(mozliwosc_ruchu(stol->lewy_koniec(), stol->prawy_koniec()))
                {
                klocek* nieblokujacy = NULL;
                klocek* blokujacy = pierwszy;
                bool dolozono = false;
                while(!dolozono)
                    {
                    if(((blokujacy->lewa_liczba) == (stol->lewy_koniec())) || ((stol->lewy_koniec()) == -1))
                        {
                        if(!(nastepny_gracz->mozliwosc_ruchu(blokujacy->prawa_liczba,blokujacy->prawa_liczba)))//Sprawdzenie czy kostka pasuje nastepnemu graczowi.
                            {
                            stol->dodaj_pierwszy(blokujacy->prawa_liczba, blokujacy->lewa_liczba);
                            dolozono = true;
                            break;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                if(((blokujacy->prawa_liczba) == (stol->lewy_koniec())) || ((stol->lewy_koniec()) == -1))
                        {
                        if(!(nastepny_gracz->mozliwosc_ruchu(blokujacy->lewa_liczba,blokujacy->lewa_liczba)))
                            {
                            stol->dodaj_pierwszy(blokujacy->lewa_liczba, blokujacy->prawa_liczba);
                            dolozono = true;
                            break;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                if(((blokujacy->lewa_liczba) == (stol->prawy_koniec())) || ((stol->lewy_koniec()) == -1))
                        {
                        if(!(nastepny_gracz->mozliwosc_ruchu(blokujacy->prawa_liczba,blokujacy->prawa_liczba)))//Sprawdzenie czy kostka pasuje nastepnemu graczowi.
                            {
                            stol->dodaj_ostatni(blokujacy->lewa_liczba, blokujacy->prawa_liczba);
                            dolozono = true;
                            break;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                if(((blokujacy->prawa_liczba) == (stol->prawy_koniec())) || ((stol->lewy_koniec()) == -1))
                        {
                        if(!(nastepny_gracz->mozliwosc_ruchu(blokujacy->lewa_liczba,blokujacy->lewa_liczba)))//Sprawdzenie czy kostka pasuje nastepnemu graczowi.
                            {
                            stol->dodaj_ostatni(blokujacy->prawa_liczba, blokujacy->lewa_liczba);
                            dolozono = true;
                            break;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                if(!dolozono)
                    {
                    if(blokujacy->nastepny == NULL)
                        break;
                    blokujacy = blokujacy->nastepny;
                    }
                }
                if(dolozono)
                    {
                    cout << "Gracz " << id << " doklada klocek " << "[" << blokujacy->lewa_liczba << "|" << blokujacy->prawa_liczba << "].\n";
                    usun_klocek(blokujacy->prawa_liczba, blokujacy->lewa_liczba);
                    przyblokowani = 0;
                    }
                if(!dolozono)//Doloz klocek nieblokujacy.
                    {
                    if(((nieblokujacy->lewa_liczba) == (stol->lewy_koniec())) || ((stol->lewy_koniec()) == -1))
                        {
                        stol->dodaj_pierwszy(nieblokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                        dolozono = true;
                        }
                    else if((nieblokujacy->prawa_liczba) == (stol->lewy_koniec()))
                        {
                        stol->dodaj_pierwszy(nieblokujacy->lewa_liczba, nieblokujacy->prawa_liczba);
                        dolozono = true;
                        }
                    else if((nieblokujacy->lewa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(nieblokujacy->lewa_liczba, nieblokujacy->prawa_liczba);
                        dolozono = true;
                        }
                    else if((nieblokujacy->prawa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(nieblokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                        dolozono = true;
                        }
                    cout << "Gracz " << id << " doklada klocek " << "[" << nieblokujacy->lewa_liczba << "|" << nieblokujacy->prawa_liczba << "].\n";
                    usun_klocek(nieblokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                    przyblokowani = 0;
                    }
                }
            else
                {
                cout << "Gracz " << id << " nie moze dolozyc klocka i siega do worka.\n";
                if(!dobierz_klocek())
                    {
                    ++przyblokowani;
                    }
                }
            }
        if(przyblokowani == liczba_graczy)//Obsluga remisu.
            {
            cout << "Gra konczy sie remisem!\n";
            return;
            }
        if(pierwszy == NULL)
            {
            //Gracz wygrywa, wiec nastepny gracz juz sie nie rusza. Po wyswietleniu wiadomosci zostana wywolane destruktory.
            cout << "Gracz " << id << " wygrywa!\n";
            return;
            }
        nastepny_gracz->rusz_sie(stol);
        }
    
    ~gracz()
        {
        //Konstruktor nie przydziela pamieci, wiec destruktor nie zwalnia pamieci.
        //Usun gracza z listy i zmniejsz liczbe graczy o 1:
        if(liczba_graczy < 1)
            {
            throw logic_error("Destruktor gracza zobaczyl niedodatnia liczbe graczy.");
            }
        if(this == koniec_listy_graczy)
            {
            koniec_listy_graczy = poprzedni_gracz;
            }
        if(this == poczatek_listy_graczy)
            {
            poczatek_listy_graczy = nastepny_gracz;
            }
        if(liczba_graczy >= 2)
            {
            poprzedni_gracz->nastepny_gracz = nastepny_gracz;
            nastepny_gracz->poprzedni_gracz = poprzedni_gracz;
            }
        --liczba_graczy;
        }
    };
short gracz::liczba_graczy = 0;
gracz* gracz::poczatek_listy_graczy = NULL;
gracz* gracz::koniec_listy_graczy = NULL;
short gracz::przyblokowani = 0;
lista_klockow* stolik = new lista_klockow;
struct gra
    {
    gra()//Konstruktor gry. Po jego wywolaniu pierwszy gracz moze juz sie ruszyc.
        {
        cout << "\nRozpoczyne sie gra w domino.\n";
        short liczba_graczy;
	bool dobra_liczba_graczy = false;
	do
	    {
	    cout << "W grze moze uczestniczyc od 1 do "<< MAX_LICZBA_GRACZY <<" graczy.\n";
	    cout << "Podaj liczbe graczy: ";
	    do
	        {
                if(!cin)
                    {
                    cin.clear();
                    cin.ignore(1024,'\n');
                    }
                cin >> liczba_graczy;//Wczytujemy liczbe graczy.
                }
            while(!cin);
	    if(liczba_graczy <= MAX_LICZBA_GRACZY && liczba_graczy >= 1)
	        dobra_liczba_graczy = true;
	    }
	while(!dobra_liczba_graczy);
        //Znamy juz liczbe graczy.
        char typ_gracza = 'l';
        cout << "Okresl typy graczy. Mozliwe typy to: gracz (l)udzki, komputerowy l(a)twy, komputerowy (t)rudny.\n";
        for(short i=1; i<=liczba_graczy; ++i)
            {
            do
                {
                cout << "Okresl typ gracza numer " << i << ": ";
                if(!cin)
                    {
                    cin.clear();
                    cin.ignore(1024,'\n');
                    }
                cin >> typ_gracza;
                }
            while(!cin);
            //Wczytano typ kolejnego gracza. Teraz trzeba go skonstruowac.
            if((typ_gracza == 'l') || (typ_gracza == 'L'))
                new gracz();
            else 
                {
                if ((typ_gracza == 'a') || (typ_gracza == 'A'))
                    new gracz(cpu_latwy);
                else
                    {
                    if((typ_gracza == 't') || (typ_gracza == 'T'))
                        new gracz(cpu_trudny);
                    else
                        --i;
                    }
                }
            }//koniec fora
        worek.mieszaj_worek();
        gracz::poczatek_listy_graczy->rozdaj();
        }//Koniec konstruktora gry.
        
    void graj()
        {
        gracz::poczatek_listy_graczy->rusz_sie(stolik);
        }
    ~gra()
        {
        //Pozostale destruktory zniszcza odpowiednie obiekty.
        while(gracz::liczba_graczy)
	    {
	    delete gracz::koniec_listy_graczy;
	    }
        }
    };
int main()
    {
    srand(time(0));
    bool wystarczy_gier = false;
    do
        {
        gra nowa_gra;
        nowa_gra.graj();
        char czy_nastepna_gra = 't';
        bool gracz_odpowiedzial = false;
        cout << "Zakonczono gre. ";
        delete stolik;
        do
            {
            do
                {
                cout << "Czy rozpoczac kolejna gre? (t/n)\n";
                if(!cin)
                    {
                    cin.clear();
                    cin.ignore(1024,'\n');
                    }
                cin >> czy_nastepna_gra;
                }
            while(!cin);
            if(czy_nastepna_gra == 't' || czy_nastepna_gra == 'T')
                {
                wystarczy_gier = false;
                stolik = new lista_klockow;
                gracz_odpowiedzial = true;
                }
            if(czy_nastepna_gra == 'n' || czy_nastepna_gra == 'N')
                {
                wystarczy_gier = true;
                gracz_odpowiedzial = true;
                }
            }
        while(!gracz_odpowiedzial);
        }
    while(!wystarczy_gier);
    return 0;
    }
