#include<iostream>
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
	    //cerr << "Dodano klocek.\n";
	    }
	~klocek()
	    {
	    //cerr << "Zniszczono klocek.\n";
	    }
	  
        };
    klocek* pierwszy;
    klocek* przedostatni;
public:
    lista_klockow()//konstruktor listy klock�w
        {
        pierwszy = NULL;
        przedostatni = NULL;
        }
    short lewy_koniec()//zwraca lewy koniec listy
        {
        return pierwszy->lewa_liczba;
        }
    short prawy_koniec()//zwraca prawy koniec listy
        {
        return pierwszy->prawa_liczba;
        }
    void wyswietl()//wy�wietla list� klock�w
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
    void dodaj_pierwszy (short lewa_liczba, short prawa_liczba)//dodaje klocek na pocz�tek
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
            cerr << "checkpoint 7c\n";
            dodaj_pierwszy (lewa_liczba, prawa_liczba);
            return;
            }
        if (przedostatni == NULL)
            {
            cerr << "checkpoint 7d\n";
            przedostatni = new klocek;
            pierwszy->nastepny = przedostatni;
            przedostatni->poprzedni = pierwszy;
            przedostatni->nastepny = NULL;
            przedostatni->lewa_liczba = lewa_liczba;
            przedostatni->prawa_liczba = prawa_liczba;
            przedostatni = pierwszy;
            return;
            }
        cerr << "checkpoint 7e\n";
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
        {//zwraca true, je�li si� to uda�o, a false je�li nie znaleziono podanego klocka na li�cie
        klocek* sprawdzany = pierwszy;
        klocek* sprawdzony = pierwszy;
        cerr << "checkpoint usun_klocek 1\n";
        while(sprawdzany)
            {
            if(((liczba_1 == sprawdzany->lewa_liczba) && (liczba_2 == sprawdzany->prawa_liczba)) || ((liczba_2 == sprawdzany->lewa_liczba) && (liczba_1 == sprawdzany->prawa_liczba)))
                {
                //Przed skasowaniem klocka ka�� s�siednim klockom wskazywa� na siebie nawzajem.
                if(sprawdzany->poprzedni != NULL)
                    {
                    cerr << "checkpoint usun_klocek 2\n";
                    //To nie jest pierwszy klocek na li�cie.
                    sprawdzany->poprzedni->nastepny = sprawdzany->nastepny;
                    cerr << "checkpoint usun_klocek 2a\n";
                    }
                else
                    {
                    cerr << "checkpoint usun_klocek 3\n";
                    pierwszy = sprawdzany->nastepny;
                    cerr << "checkpoint usun_klocek 3a\n";
                    }
                if(sprawdzany->nastepny != NULL)
                    {
                    //To nie jest ostatni klocek na li�cie.
                    cerr << "checkpoint usun_klocek 4\n";
                    sprawdzany->nastepny->poprzedni = sprawdzany->poprzedni;
                    cerr << "checkpoint usun_klocek 4a\n";
                    if(sprawdzany->nastepny->nastepny == NULL)
                        {
                        cerr << "checkpoint usun_klocek 5\n";
                        //Przedostatni klocek na li�cie
                        przedostatni = przedostatni->poprzedni;
                        cerr << "checkpoint usun_klocek 5a\n";
                        }
                    }
                else
                    {
                    //Ostatni klocek na li�cie.
                    if(pierwszy != NULL)
                        {//Nie jest to jedyny klocek na li�cie.
                        cerr << "checkpoint usun_klocek 6\n";
                        przedostatni = przedostatni->poprzedni;
                        cerr << "checkpoint usun_klocek 6a\n";
                        }
                    }
                cerr << "checkpoint usun_klocek 7\n";
                delete sprawdzany;
                cerr << "checkpoint usun_klocek 7a\n";
                return true;
                }
            else
                {
	            sprawdzony = sprawdzany;
                sprawdzany = sprawdzany->nastepny;
                }
            //sprawdzony = sprawdzony->nastepny;
            }
        cerr << "checkpoint usun_klocek 8\n";
        return false;
        }
    void dostepne_liczby(bool liczby[LICZBY_NA_KLOCKACH])//zwraca przez referencj� zbi�r liczb wyst�puj�cych na li�cie
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
    ~lista_klockow()//destruktor listy klock�w
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
    worek():lista_klockow()//konstruktor tworzy niepotasowan� list� klock�w
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
worek* worek;
enum typ_gracza {cpu_latwy, cpu_trudny, czlowiek};
struct gracz
    //dziedzicz po lista_klockow
    {
    typ_gracza kto_steruje;
    //wybierz akcj� do wykonania
    gracz* nastepny_gracz;
    gracz* poprzedni_gracz;
    static gracz* poczatek_listy_graczy;
    static gracz* koniec_listy_graczy;
    static short liczba_graczy;
    short id;
    static short przyblokowani;
    lista_klockow* lista_klockow_gracza;
    gracz(typ_gracza kto_ma_sterowac = czlowiek)
    //Konstruktor nadaje graczowi numer, dodaje go do listy graczy i okre�la jego typ.
    //Domy�lnie tworzony jest gracz cz�owiek.
        {
        lista_klockow_gracza = new lista_klockow;
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
            koniec_listy_graczy->nastepny_gracz = this;//Nie mo�na tego zrobi� je�li lista graczy jest pusta, st�d poprzedni if.
            poprzedni_gracz = koniec_listy_graczy;
            koniec_listy_graczy = this;
            nastepny_gracz = poczatek_listy_graczy;
            poczatek_listy_graczy->poprzedni_gracz = this;//Jak wy�ej.
            }
        id = ++liczba_graczy;//nadaj graczowi numer
        cerr << "checkpoint skonstruowano gracza numer " << id << "potwierdz:";
        int q;
        cin >> q;
        kto_steruje = kto_ma_sterowac;//okre�l typ gracza
        }
    bool dobierz_klocek()//bierze klocek z worka i dodaje go na koniec swojej listy. False je�li worek by� pusty.
        {
        if(worek->pierwszy)
            {
            //najpierw dodaj pierwszy klocek z worka na koniec swojej listy
            lista_klockow_gracza->dodaj_ostatni(worek->pierwszy->lewa_liczba, worek->pierwszy->prawa_liczba);
            //potem usu� pierwszy klocek z worka
            worek->usun_klocek(worek->pierwszy->lewa_liczba, worek->pierwszy->prawa_liczba);
            cerr << "checkpoint gracz "<< id <<" +klocek. potwierdz:";
            int q;
            cin >> q;
            return true;
            }
        cerr << "checkpoint gracz "<< id <<" widzi pusty worek. potwierdz:";
        int q;
        cin >> q;
        return false;
        }
    void mieszaj_worek()
        {
	cerr << "checkpoint 4\n";
        //wylosuj 2 liczby od 0 do LICZBY_NA_KLOCKACH i rzu� monet� czy prze�o�y� klocek z tymi liczbami na pocz�tek czy na koniec
        //powt�rz du�o razy, powiedzmy 100*LICZBY_NA_KLOCKACH^2
        for(int i=0; i<=(LICZBY_NA_KLOCKACH+1)*(LICZBY_NA_KLOCKACH+1); ++i)
            {
            short a, b;
            a=rand()%(LICZBY_NA_KLOCKACH+1);
            b=rand()%(LICZBY_NA_KLOCKACH+1);
	    cerr << "checkpoint 5, a = " << a << ", b = " << b << "\n";
            worek->usun_klocek(a,b);
            if(rand()%2)
                {
		cerr << "checkpoint 6, a = " << a << ", b = " << b << "\n";
                worek->dodaj_pierwszy(a,b);
        cerr << "checkpoint 6b, a = " << a << ", b = " << b << "\n";
                }
            else
                {
		cerr << "checkpoint 7, a = " << a << ", b = " << b << "\n";
                worek->dodaj_ostatni(a,b);
        cerr << "checkpoint 7b, a = " << a << ", b = " << b << "\n";
                }
            }
        }
    bool mozliwosc_ruchu(short lewy_koniec_stolu,short prawy_koniec_stolu)
        {
        auto sprawdzany = lista_klockow_gracza->pierwszy;
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
        if(lista_klockow_gracza->pierwszy == NULL)
            return false;
        if((
                (lista_klockow_gracza->pierwszy->lewa_liczba == liczba_na_klocku_a)
                &&
                (lista_klockow_gracza->pierwszy->prawa_liczba == liczba_na_klocku_b))
            ||
                ((lista_klockow_gracza->pierwszy->lewa_liczba == liczba_na_klocku_b)
                &&
                (lista_klockow_gracza->pierwszy->prawa_liczba == liczba_na_klocku_a)
            ))
            {
            //bierzemy pierwszy klocek z listy
            if(lista_klockow_gracza->pierwszy->nastepny != NULL)
                lista_klockow_gracza->pierwszy->nastepny->poprzedni = NULL;
            delete lista_klockow_gracza->pierwszy;
            return true;
            }
        if(lista_klockow_gracza->przedostatni == NULL)
            return false;//na li�cie jest tylko 1 klocek i zosta� on ju� sprawdzony
        if((
                (lista_klockow_gracza->przedostatni->nastepny->lewa_liczba == liczba_na_klocku_a)
                &&
                (lista_klockow_gracza->przedostatni->nastepny->prawa_liczba == liczba_na_klocku_b))
            ||
                ((lista_klockow_gracza->przedostatni->nastepny->lewa_liczba == liczba_na_klocku_b)
                &&
                (lista_klockow_gracza->przedostatni->nastepny->prawa_liczba == liczba_na_klocku_a)
            ))
            {
            //bierzemy ostatni klocek z listy
            delete lista_klockow_gracza->przedostatni->nastepny;
            lista_klockow_gracza->przedostatni->nastepny = NULL;
            return true;
            }
        //je�li program doszed� tutaj, to znaczy �e na li�cie s� conajmniej 3 klocki
        auto sprawdzany = lista_klockow_gracza->pierwszy->nastepny;
        while(sprawdzany)//ostatni klocek mo�e zosta� sprawdzony 2 razy, ale za to warunek zako�czenia p�tli jest prostszy
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
    lista_klockow::klocek* daj_nty_klocek(short numer_klocka)
        {
        auto zwracany = lista_klockow_gracza->pierwszy;
        bool przejechalismy_liste = false;
        for(short i = 0; i<numer_klocka; ++i)
            {
            if(przejechalismy_liste)
                return NULL;
            if(zwracany == lista_klockow_gracza->przedostatni)
                przejechalismy_liste = true;
            zwracany = zwracany->nastepny;
            }
        return zwracany;
        }
    void rozdaj()
        {
        gracz* bioracy_klocek = nastepny_gracz;//Rozdawanie klock�w zaczynamy od nast�pnego gracza.
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
        //Na pocz�tku tury wypisz klocki wszystkich graczy i klocki na stole.
        cout << "Klocki znajduj�ce si� na stole:\n";
        stol->wyswietl();
        gracz* pokazujacy_klocki = poczatek_listy_graczy;
        for(short numer_gracza = 1; numer_gracza <= liczba_graczy; ++numer_gracza)
            {
            cout << "Klocki gracza numer " << (pokazujacy_klocki->id) << ": ";
            pokazujacy_klocki.lista_klockow_gracza->wyswietl();
            pokazujacy_klocki = pokazujacy_klocki->nastepny_gracz;
            }
        if(this->kto_steruje == czlowiek)
            {
            if(mozliwosc_ruchu(stol->lewy_koniec(), stol->prawy_koniec()))
                {
                bool dolozono = false;
	      (lista_klockow_gracza->klocek)* do_wylozenia = NULL;
                do
                    {
                    short akcja = 0;
                    cout << "Kt�ry klocek chcesz wy�o�y�, graczu numer " << id << "?";
                    do
                        {
                        do
                            {
                            cout << "Numer klocka na li�cie: ";
                            if(!cin)
                                {
                                cin.clear();
                                cin.ignore(1024,'\n');
                                }
                            cin >> akcja;//Wczytujemy numer klocka do wy�o�enia.
                            }
                        while(!cin);
                        do_wylozenia = daj_nty_klocek(akcja);
                        }
                    while(!do_wylozenia);
                    //Mamy adres klocka do wy�o�enia. Dok�adamy do sto�u.
                    cout << "Czy chcesz do�o�y� klocek z (l)ewej, czy z (p)rawej strony sto�u?\n";
                    char strona = 'l';
                    do
                        {
                        if(!cin)
                            {
                            cin.clear();
                            cin.ignore(1024,'\n');
                            }
                        cin >> strona;//Wczytujemy stron� z kt�rej gracz chce do�o�y� klocek.
                        }
                    while(!cin);
                        if((strona == 'l') || (strona == 'L'))
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
                                stol->dodaj_ostatni(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                                dolozono = true;
                                }
                            else if((do_wylozenia->prawa_liczba) == (stol->prawy_koniec()))
                                {
                                stol->dodaj_ostatni(do_wylozenia->lewa_liczba, do_wylozenia->prawa_liczba);
                                dolozono = true;
                                }
                            }
                    }
                while(!dolozono);
                cout << "Gracz " << id << "dok�ada klocek " << "[" << do_wylozenia->lewa_liczba << "|" << do_wylozenia->prawa_liczba << "].\n";
                lista_klockow_gracza->usun_klocek(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                przyblokowani = 0;
                }
            else
                {
                cout << "Gracz " << id << " nie mo�e do�o�y� klocka i si�ga do worka.";
                if(!dobierz_klocek())
                    {
                    ++przyblokowani;
                    }
                //Obs�uga remisu.
                }
            }//Cz�owiek, komputer �atwy i komputer trudny inaczej si� ruszaj�.
        if(kto_steruje == cpu_latwy)
            {
            if(mozliwosc_ruchu(stol->lewy_koniec(), stol->prawy_koniec()))
                {
                lista_klockow_gracza->klocek* do_wylozenia = this->pierwszy;
                bool dolozono = false;
                while(!dolozono)
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
                    else if((do_wylozenia->lewa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(do_wylozenia->prawa_liczba, do_wylozenia->lewa_liczba);
                        dolozono = true;
                        }
                    else if((do_wylozenia->prawa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(do_wylozenia->lewa_liczba, do_wylozenia->prawa_liczba);
                        dolozono = true;
                        }
                    if(dolozono)
                        {
                        cout << "Gracz " << this->id << "dok�ada klocek " << "[" << do_wylozenia->lewa_liczba << "|" << do_wylozenia->prawa_liczba << "].\n";
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
                cout << "Gracz " << id << " nie mo�e do�o�y� klocka i si�ga do worka.";
                if(!dobierz_klocek())
                    {
                    ++przyblokowani;
                    }
                //Obs�uga remisu.
                }
            }
        if(kto_steruje == cpu_trudny)
            {
            if(mozliwosc_ruchu(stol->lewy_koniec(), stol->prawy_koniec()))
                {
                (lista_klockow_gracza->klocek)* nieblokujacy = NULL;
                (lista_klockow_gracza->klocek)* blokujacy = pierwszy;
                bool dolozono = false;
                while(!dolozono)
                    {
                    if((blokujacy->lewa_liczba) == (stol->lewy_koniec()))
                        {
                        if(!(nastepny_gracz->mozliwosc_ruchu(blokujacy->prawa_liczba,blokujacy->prawa_liczba)))//Sprawdzenie czy kostka pasuje nast�pnemu graczowi.
                            {
                            stol->dodaj_pierwszy(blokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                            dolozono = true;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                else if((nieblokujacy->prawa_liczba) == (stol->lewy_koniec()))
                        {
                        if(!(this->nastepny_gracz->mozliwosc_ruchu(blokujacy->lewa_liczba,blokujacy->lewa_liczba)))
                            {
                            stol->dodaj_pierwszy(nieblokujacy->lewa_liczba, blokujacy->prawa_liczba);
                            dolozono = true;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                else if((nieblokujacy->lewa_liczba) == (stol->prawy_koniec()))
                        {
                        if(!(this->nastepny_gracz->mozliwosc_ruchu(blokujacy->prawa_liczba,blokujacy->prawa_liczba)))//Sprawdzenie czy kostka pasuje nast�pnemu graczowi.
                            {
                            stol->dodaj_ostatni(blokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                            dolozono = true;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                else if((nieblokujacy->prawa_liczba) == (stol->prawy_koniec()))
                        {
                        if(!(nastepny_gracz->mozliwosc_ruchu(blokujacy->lewa_liczba,blokujacy->lewa_liczba)))//Sprawdzenie czy kostka pasuje nast�pnemu graczowi.
                            {
                            stol->dodaj_ostatni(blokujacy->lewa_liczba, nieblokujacy->prawa_liczba);
                            dolozono = true;
                            }
                        else if(!nieblokujacy)
                            {
                            nieblokujacy = blokujacy;
                            }
                        }
                if(dolozono)
                    {
                    cout << "Gracz " << id << "dok�ada klocek " << "[" << blokujacy->lewa_liczba << "|" << blokujacy->prawa_liczba << "].\n";
                    usun_klocek(blokujacy->prawa_liczba, blokujacy->lewa_liczba);
                    przyblokowani = 0;
                    }
                else
                    {
                    blokujacy = blokujacy->nastepny;
                    }
                }
                if(!dolozono)//Do�� klocek nieblokuj�cy.
                    {
                    if((nieblokujacy->lewa_liczba) == (stol->lewy_koniec()))
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
                        stol->dodaj_ostatni(nieblokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                        dolozono = true;
                        }
                    else if((nieblokujacy->prawa_liczba) == (stol->prawy_koniec()))
                        {
                        stol->dodaj_ostatni(nieblokujacy->lewa_liczba, nieblokujacy->prawa_liczba);
                        dolozono = true;
                        }
                    cout << "Gracz " << id << "dok�ada klocek " << "[" << nieblokujacy->lewa_liczba << "|" << nieblokujacy->prawa_liczba << "].\n";
                    usun_klocek(nieblokujacy->prawa_liczba, nieblokujacy->lewa_liczba);
                    przyblokowani = 0;
                    }
                }
            else
                {
                cout << "Gracz " << id << " nie mo�e do�o�y� klocka i si�ga do worka.";
                if(!dobierz_klocek())
                    {
                    ++przyblokowani;
                    }
                }
            }
        if(przyblokowani == liczba_graczy)//Obs�uga remisu.
            {
            cout << "Gra ko�czy si� remisem!\n";
            return;
            }
        if(pierwszy == NULL)
            {
            //Gracz wygrywa, wi�c nast�pny gracz ju� sie nie rusza. Po wy�wietleniu wiadomo�ci zostan� wywo�ane destruktory.
            cout << "Gracz " << id << " wygrywa!";
            return;
            }
        nastepny_gracz->rusz_sie(stol);
        }
    
    ~gracz()
        {
        //Usu� gracza z listy i zmniejsz liczb� graczy o 1:
        delete lista_klockow_gracza;
        if(liczba_graczy < 1)
            {
            //throw logic_error("Destruktor gracza zobaczy� niedodatni� liczb� graczy.");
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
    gra()//Konstruktor gry. Po jego wywo�aniu pierwszy gracz mo�e ju� si� ruszy�.
        {
        cout << "\nRozpoczyne si� gra w domino.\n";
        short liczba_graczy;
	bool dobra_liczba_graczy = false;
	do
	    {
	    cout << "W grze mo�e uczestniczy� od 1 do "<< MAX_LICZBA_GRACZY <<" graczy.\n";
	    cout << "Podaj liczb� graczy: ";
	    do
	        {
                if(!cin)
                    {
                    cin.clear();
                    cin.ignore(1024,'\n');
                    }
                cin >> liczba_graczy;//Wczytujemy liczb� graczy.
                }
            while(!cin);
	    if(liczba_graczy <= MAX_LICZBA_GRACZY && liczba_graczy >= 1)
	        dobra_liczba_graczy = true;
	    }
	while(!dobra_liczba_graczy);
        //Znamy ju� liczb� graczy.
        char typ_gracza = 'l';
        cout << "Okre�l typy graczy. Mo�liwe typy to: gracz (l)udzki, komputerowy �(a)twy, komputerowy (t)rudny.\n";
        for(short i=1; i<=liczba_graczy; ++i)
            {
            do
                {
                cout << "Okre�l typ gracza numer " << i << ": ";
                if(!cin)
                    {
                    cin.clear();
                    cin.ignore(1024,'\n');
                    }
                cin >> typ_gracza;
                }
            while(!cin);
            //Wczytano typ kolejnego gracza. Teraz trzeba go skonstruowa�.
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
	cerr << "checkpoint 1\n";
        gracz::poczatek_listy_graczy->mieszaj_worek();
	cerr << "checkpoint 2\n";
        gracz::poczatek_listy_graczy->rozdaj();
	cerr << "checkpoint 3\n";
        }//Koniec konstruktora gry.
        
    void graj()
        {
        gracz::poczatek_listy_graczy->rusz_sie(stolik);
        }
    ~gra()
        {
        //Pozosta�e destruktory zniszcz� odpowiednie obiekty.
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
	cerr << "checkpoint skonstruowano gre!\n";
        nowa_gra.graj();
        cerr << "checkpoint rozegrano gre!\n";
        char czy_nastepna_gra = 't';
        bool gracz_odpowiedzial = false;
        cout << "Zako�czono gr�. ";
        do
            {
            do
                {
                cout << "Czy rozpocz�� kolejn� gr�? (t/n)\n";
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
