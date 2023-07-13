/**
 * @file organizer.cpp
 * @author kanol77
 * @brief Aplikacja do zarządzania kontaktami i zadaniami.
 * @version 1.0
 * @date 2022-12-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cctype>
#include <regex>

/**
 * @brief Używanie standardowej przestrzeni nazw.
 * 
 */
using namespace std;

/**
 * @brief Definicja skrótu str dla typu danych string.
 * Definicja skrótu dla wygody i czytelności.
 */
using str = string;

/**
 * @brief Na podstawie wartości tej zmiennej program kończy swoje działanie.
 * Gdy zmienna ma wartość true program kontynuuje swoje działanie, a gdy false zostaje zakończony.
 */
bool DzialanieProgramu = true;

/**
 * @brief Na podstawie tej zmiennej wyświetlane jest podsumowanie.
 * Gdy zmienna ma wartość true zostanie pokazane podsumowanie, a gdy false nie.
 */
bool show = true; 

/**
 * @brief Struktura kontaktu.
 * Struktura ta składa się z 3 ciągów znaków: imienia, nazwiska i e-maila danego kontaktu.
 * 
 */
struct kontakt
{
    str imie;
    str nazwisko;
    str email;
};

/**
 * @brief Struktura zadania.
 * Struktura ta składa się z 5 ciągów znaków: daty, godziny, typu, statusu i opisu danego zadania.
 * 
 */
struct zadanie
{
    str data;
    str godzina;
    str typ;
    str status;
    str opis;
};

/**
 * @brief Funkcja wypisująca vector kontaktów.
 * 
 * @param vec Referencja do vectora kontaktów który ma zostać wypisany.
 */
void WypiszVectorK(vector<kontakt> &vec);

/**
 * @brief Funkcja wypisująca vector zadań.
 * 
 * @param vec Referencja do vectora zadań który ma zostać wypisany.
 */
void WypiszVectorZ(vector<zadanie> &vec); 

/**
 * @brief Funkcja sortująca vector kontaktów.
 * Funkcje sortowania sortują alfabetycznie.
 * @param vec Vector kontaktów który ma zostać posortowany.
 * @param x Zmienna oznaczająca to według której właściwości kontaktów zostanie posortowany vector. Kolejno: x = 1 - sortuj według imion, x = 2 - sortuj według nazwisk, x = 3 - sortuj według E-maili. 
 * @return vector<kontakt>  Posortowany vector kontaków według wybranej właściwości kontaktów.
 */
vector<kontakt> sortujVecK(vector<kontakt> vec, int x);

/**
 * @brief Funkcja sortująca vector zadań.
 * Funkcje sortowania sortują alfabetycznie.
 * @param vec Vector zadań który ma zostać posortowany.
 * @param x Zmienna oznaczająca to według której właściwości zadań zostanie posortowany vector. Kolejno: x = 1 - sortuj według daty, x = 2 - sortuj według godziny, x = 3 - sortuj według typu, x = 4 - sortuj według statusu, x = 5 - sortuj według opisu. 
 * @return vector<zadanie> Posortowany vector zadań według wybranej właściwości zadań.
 */
vector<zadanie> sortujVecZ(vector<zadanie> vec, int x); 

/**
 * @brief Funkcja filtrująca vector kontaktów.
 * 
 * @param kontakty Vector kontaktów który ma zostać pofiltrowany.
 * @param x Zmienna oznaczająca to według której właściwości kontaktów zostanie pofiltrowany vector. Kolejno: x = 1 - filtruj według imion, x = 2 - filtruj według nazwisk, x = 3 - filtruj według E-maili.
 * @return vector<kontakt> Pofiltrowany vector kontaków według wybranej właściwości kontaktów
 */
vector<kontakt> filtrujVecK(vector<kontakt> kontakty, int x);

/**
 * @brief Funkcja filtrująca vector zadań.
 * 
 * @param zadania Vector zadań który ma zostać pofiltrowany.
 * @param x Zmienna oznaczająca to według której właściwości zadań zostanie pofiltrowany vector. Kolejno: x = 1 - filtruj według daty, x = 2 - filtruj według godziny, x = 3 - filtruj według typu, x = 4 - filtruj według statusu, x = 5 - filtruj według opisu.
 * @return vector<zadanie> Pofiltrowany vector zadań według wybranej właściwości zadań.
 */
vector<zadanie> filtrujVecZ(vector<zadanie> zadania, int x);

/**
 * @brief Funkcja dodająca kontakt do vectora kontaktów.
 * Funkcja ta przyjmuje od użytkownika wszystkie dane nowego kontaktu i zapisuje go do vectora kontaktów.
 * @param vec Referencja do vectora kontaktów do którego zostanie dodany nowy kontakt.
 */
void DodajKontakt(vector<kontakt> &vec); 

/**
 * @brief Funkcja dodająca zadanie do vectora zadań.
 * Funkcja ta przyjmuje od użytkownika wszystkie dane nowego zadania i zapisuje go do vectora zadań.
 * @param vec Referencja do vectora zadań do którego zostanie dodane nowe zadanie.
 */
void DodajZadanie(vector<zadanie> &vec); 

/**
 * @brief Funkcja usuwająca kontakt z vectora kontaktów.
 * Funkcja ta usuwa wybrany przez użytkownika kontakt z vectora kontaktów.
 * @param vec Referencja do vectora kontaktów z którego zostanie usunięty kontakt.
 */
void UsunKontakt(vector<kontakt> &vec); 

/**
 * @brief Funkcja usuwająca zadanie z vectora zadań.
 * Funkcja ta usuwa wybrane przez użytkownika zadanie z vectora zadań.
 * @param vec Referencja do vectora zadań z którego zostanie usunięte zadanie.
 */
void UsunZadanie(vector<zadanie> &vec); 

/**
 * @brief Funkcja zmieniająca status zadania.
 * Funkcja ta zmienia status zadania z wykonanego na niewykonane lub na odwrót (V -> X lub X -> V).
 * @param vec Referencja do vectora zadań który przechowuje zadanie którego status zostanie zmieniony.
 */
void ZmienStatus(vector<zadanie> &vec); 

/**
 * @brief Funkcja czytająca kontakty z pliku tekstowego.
 * Funkcja ta czyta kontakty zapisane w pliku tekstowym i zapisuje je w vectorze kontaktów.
 * @param nazwa_pliku_kontakty Nazwa pliku z którego mają zostać sczytane kontakty.
 * @return vector<kontakt> Vector kontaktów przechowujący sczytane kontakty.
 */
vector<kontakt> CzytajKontakty(str nazwa_pliku_kontakty); 

/**
 * @brief Funkcja czytająca zadania z pliku tekstowego.
 * Funkcja ta czyta zadania zapisane w pliku tekstowym i zapisuje je w vectorze zadań.
 * @param nazwa_pliku_zadania Nazwa pliku z którego mają zostać sczytane zadania.
 * @return vector<zadanie> Vector zadań przechowujący sczytane zadania.
 */
vector<zadanie> CzytajZadania(str nazwa_pliku_zadania);

/**
 * @brief Funkcja zapisująca kontakty i zadania w plikach tekstowych.
 * Funkcja ta zapisuje kontakty i zadania z odpowiadających sobie vectorów do pliku tekstowego. Funkcja używa tych samych plików tekstowych co funkcje czytające dane z plików przy starcie programu.
 * @param nazwa_pliku_kontakty Nazwa pliku do którego mają zostać zapisane kontakty.
 * @param nazwa_pliku_zadania Nazwa pliku do którego mają zostać zapisane zadania.
 * @param vecK Vector kontaktów zawierający kontakty które mają zostać zapisane w pliku tekstowym.
 * @param vecZ Vector zadań zawierający zadania które mają zostać zapisane w pliku tekstowym.
 */
void ZapiszWPlikach(str nazwa_pliku_kontakty, str nazwa_pliku_zadania, vector<kontakt> &vecK, vector<zadanie> &vecZ); 

/**
 * @brief Funkcja pytająca użytkownika o chęć kontynuacji działania z programem.
 * Funkcja ta pyta użytkownika czy chce on powrócić do menu głównego (1) czy też zakończyć działanie z programem (2).
 */
void Zapytanie(); 

/**
 * @brief Funkcja pytająca użytkownika według jakiej właściwości kontaktu posortować lub pofiltrować kontakty.
 * Funkcja ta pyta użytkownika według jakiej właściwości kontaktu chce sortować lub filtrować kontakty i zwraca jego decyzję w postaci liczby całkowitej.
 * @param flag Parametr będący stringiem który służy do tego by wyświetlić odpowiednie słowo (Posortuj lub Pofiltruj) w zależności od tego o co własnie pyta program.
 * @return int Liczba całkowita będąca odzwierciedleniem decyzji użytkownika o tym według jakiej właściwości kontaktu sortować lub filtrować kontakty. Kolejno:  1 - imie, 2 - nazwisko, 3 - e-mail.
 */
int WedlugCzegoK(string flag); 

/**
 * @brief Funkcja pytająca użytkownika według jakiej właściwości zadania posortować lub pofiltrować zadania.
 * Funkcja ta pyta użytkownika według jakiej właściwości zadania chce sortować lub filtrować zadania i zwraca jego decyzję w postaci liczby całkowitej.
 * @param flag Parametr będący stringiem który służy do tego by wyświetlić odpowiednie słowo (Posortuj lub Pofiltruj) w zależności od tego o co własnie pyta program.
 * @return int Liczba całkowita będąca odzwierciedleniem decyzji użytkownika o tym według jakiej właściwości zadania sortować lub filtrować zadania. Kolejno:  1 - data, 2 - godzina, 3 - typ, 4 - status, 5 - opis. 
 */
int WedlugCzegoZ(string flag);

/**
 * @brief Funkcja pytająca użytkownika czy sortować kontakty lub zadania.
 * Funkcja ta pyta użytkownika czy chce sortować kontakty lub zadania i zwraca prawdę lub fałsz w zależności od jego decyzji.
 * @return true Wartość zwracana gdy użytkownik chce sortować.
 * @return false Wartość zwracana gdy użytkownik nie chce sortować.
 */
bool CzySortowac(); 

/**
 * @brief Funkcja pytająca użytkownika czy filtrować kontakty lub zadania.
 * Funkcja ta pyta użytkownika czy chce filtrować kontakty lub zadania i zwraca prawdę lub fałsz w zależności od jego decyzji.
 * @return true Wartość zwracana gdy użytkownik chce filtrować.
 * @return false Wartość zwracana gdy użytkownik nie chce filtrować.
 */
bool CzyFiltrowac();

/**
 * @brief Funkcja sprawdzająca czy dany ciąg znaków zawiera tylko litery.
 * Funkcja ta przyjmuje ciąg znaków i sprawdza czy zawiera on tylko znaki alfanumeryczne za pomocą wyrażenia regularnego po czym zwraca prawdę lub fałsz w zależności od wyniku.
 * @param nazwa Sprawdzany ciąg znaków.
 * @return true Wartość zwracana gdy ciąg znaków zawiera tylko znaki alfanumeryczne.
 * @return false Wartość zwracana gdy ciąg znaków nie zawiera tylko znaków alfanumerycznych.
 */
bool TylkoLitery(string nazwa);

/**
 * @brief Funkcja sprawdzająca czy dany ciąg znaków jest adresem e-mail.
 * Funkcja ta przyjmuje ciąg znaków i sprawdza czy jest on prawidłowym e-mailem za pomocą wyrażenia regularnego po czym zwraca prawdę lub fałsz w zależności od wyniku.
 * @param email Sprawdzany ciąg znaków.
 * @return true Wartość zawracana gdy okaże się że podany ciąg znaków jest prawidłowym e-mailem.
 * @return false Wartość zawracana gdy okaże się że podany ciąg znaków nie jest prawidłowym e-mailem.
 */
bool CzyEmail(string email);

/**
 * @brief Funkcja sprawdzająca czy dany ciąg znaków jest datą w foramcie RRRR.MM.DD.
 * Funkcja ta przyjmuje ciąg znaków i sprawdza czy jest on prawidłową datą w formacie RRRR.MM.DD za pomocą wyrażenia regularnego po czym zwraca prawdę lub fałsz w zależności od wyniku.
 * @param data Sprawdzany ciąg znaków.
 * @return true Wartość zawracana gdy okaże się że podany ciąg znaków jest prawidłową datą.
 * @return false Wartość zawracana gdy okaże się że podany ciąg znaków nie jest prawidłową datą.
 */
bool CzyData(string data);

/**
 * @brief Funkcja sprawdzająca czy dany ciąg znaków jest godziną w formacie GG:MM.
 * Funkcja ta przyjmuje ciąg znaków i sprawdza czy jest on prawidłową godziną w formacie GG:MM za pomocą wyrażenia regularnego po czym zwraca prawdę lub fałsz w zależności od wyniku.
 * @param godzina Sprawdzany ciąg znaków.
 * @return true Wartość zawracana gdy okaże się że podany ciąg znaków jest prawidłową godziną.
 * @return false Wartość zawracana gdy okaże się że podany ciąg znaków nie jest prawidłową godziną.
 */
bool CzyGodzina(string godzina); 

/**
 * @brief Funkcja uruchamiająca główne menu programu i wykonująca podprogramy.
 * Funkcja ta przyjmuje vector kontaktów oraz vector zadań i za ich pomocą uruchamia odpowiedni podprogram wybrany przez użytkownika.
 * @param kontakty Referencja do vectora kontaktów przechowującego sczytane z pliku kontakty.
 * @param zadania Referencja do vectora zadań przechowującego sczytane z pliku zadania.
 */
void Start(vector<kontakt> &kontakty, vector<zadanie> &zadania); 

/**
 * @brief Funkcja main.
 * Funkcja ta jest funkcją główną. Wykonuje ona ustawienia wstępne, uruchamia funkcję Start() oraz zajmuje się wywołaniem funkcji ZapiszWPlikach().
 * @param argc Parametr określający ilość argumentów podanych w linii poleceń przy uruchamianiu programu.
 * @param args Tablica wskaźników do argumentów podanych w linii poleceń przy uruchamianiu programu.
 * @return int Liczba całkowita odzwierciedlająca to jak przebiegła praca z programem.
 */
int main(int argc, char *args[])
{
    setlocale(LC_ALL, "pl_PL");

    system("chcp 65001");
    system("cls");

    string nazwa_pliku_wejsciowego_kontakty;
    string nazwa_pliku_wejsciowego_zadania;
    try
    {
        if (string(args[1]) == "-k" && string(args[3]) == "-z")
        {
            nazwa_pliku_wejsciowego_kontakty = args[2];
            nazwa_pliku_wejsciowego_zadania = args[4];
        }
        else if (string(args[3]) == "-k" && string(args[1]) == "-z")
        {
            nazwa_pliku_wejsciowego_kontakty = args[4];
            nazwa_pliku_wejsciowego_zadania = args[2];
        }
    }
    catch (exception &e)
    {
        printf("%s", "Nieprawidłowe wejście!");
        return 1;
    }

    vector<kontakt> kontakty = CzytajKontakty(nazwa_pliku_wejsciowego_kontakty);
    vector<zadanie> zadania = CzytajZadania(nazwa_pliku_wejsciowego_zadania);

    while (DzialanieProgramu)
        Start(kontakty, zadania);

    ZapiszWPlikach(nazwa_pliku_wejsciowego_kontakty, nazwa_pliku_wejsciowego_zadania, kontakty, zadania);

    return 0;
}

void WypiszVectorK(vector<kontakt> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << endl;
        cout << i + 1 << "." << endl;
        cout << vec[i].imie << endl;
        cout << vec[i].nazwisko << endl;
        cout << vec[i].email << endl;
        cout << endl;
        cout << "--------------------------------------------------" << endl;
    }
}

void WypiszVectorZ(vector<zadanie> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << endl;
        cout << i + 1 << "." << endl;
        cout << vec[i].data << endl;
        cout << vec[i].godzina << endl;
        cout << vec[i].typ << endl;
        cout << vec[i].status << endl;
        cout << vec[i].opis << endl;
        cout << endl;
        cout << "--------------------------------------------------" << endl;
    }
}

vector<kontakt> sortujVecK(vector<kontakt> vec, int x)
{
    vector<string> PosortowaneImiona;
    vector<string> PosortowaneNazwiska;
    vector<string> PosortowaneEmaile;
    vector<kontakt> PosortowaneKontakty;

    for (auto elem : vec)
    {
        string klucz1 = elem.imie;
        string klucz2 = elem.nazwisko;
        string klucz3 = elem.email;
        if (!count(PosortowaneImiona.begin(), PosortowaneImiona.end(), klucz1))
            PosortowaneImiona.push_back(elem.imie);
        if (!count(PosortowaneNazwiska.begin(), PosortowaneNazwiska.end(), klucz2))
            PosortowaneNazwiska.push_back(elem.nazwisko);
        if (!count(PosortowaneEmaile.begin(), PosortowaneEmaile.end(), klucz3))
            PosortowaneEmaile.push_back(elem.email);
    }

    switch (x)
    {
    case 1:
        sort(PosortowaneImiona.begin(), PosortowaneImiona.end());
        for (auto elem : PosortowaneImiona)
        {
            for (auto elem1 : vec)
            {
                if (elem1.imie == elem)
                    PosortowaneKontakty.push_back(elem1);
            }
        }
        break;
    case 2:
        sort(PosortowaneNazwiska.begin(), PosortowaneNazwiska.end());
        for (auto elem : PosortowaneNazwiska)
        {
            for (auto elem1 : vec)
            {
                if (elem1.nazwisko == elem)
                    PosortowaneKontakty.push_back(elem1);
            }
        }
        break;
    case 3:
        sort(PosortowaneEmaile.begin(), PosortowaneEmaile.end());
        for (auto elem : PosortowaneEmaile)
        {
            for (auto elem1 : vec)
            {
                if (elem1.email == elem)
                    PosortowaneKontakty.push_back(elem1);
            }
        }
        break;

    default:
        break;
    }
    return PosortowaneKontakty;
}

vector<zadanie> sortujVecZ(vector<zadanie> vec, int x)
{
    vector<string> PosortowaneDaty;
    vector<string> PosortowaneGodziny;
    vector<string> PosortowaneTypy;
    vector<string> PosortowaneStatusy;
    vector<string> PosortowaneOpisy;
    vector<zadanie> PosortowaneZadania;

    for (auto elem : vec)
    {
        string klucz1 = elem.data;
        string klucz2 = elem.godzina;
        string klucz3 = elem.typ;
        string klucz4 = elem.status;
        string klucz5 = elem.opis;
        if (!count(PosortowaneDaty.begin(), PosortowaneDaty.end(), klucz1))
            PosortowaneDaty.push_back(elem.data);
        if (!count(PosortowaneGodziny.begin(), PosortowaneGodziny.end(), klucz2))
            PosortowaneGodziny.push_back(elem.godzina);
        if (!count(PosortowaneTypy.begin(), PosortowaneTypy.end(), klucz3))
            PosortowaneTypy.push_back(elem.typ);
        if (!count(PosortowaneStatusy.begin(), PosortowaneStatusy.end(), klucz4))
            PosortowaneStatusy.push_back(elem.status);
        if (!count(PosortowaneOpisy.begin(), PosortowaneOpisy.end(), klucz5))
            PosortowaneOpisy.push_back(elem.opis);
    }

    switch (x)
    {
    case 1:
        sort(PosortowaneDaty.begin(), PosortowaneDaty.end());
        for (auto elem : PosortowaneDaty)
        {
            for (auto elem1 : vec)
            {
                if (elem1.data == elem)
                    PosortowaneZadania.push_back(elem1);
            }
        }
        break;
    case 2:
        sort(PosortowaneGodziny.begin(), PosortowaneGodziny.end());
        for (auto elem : PosortowaneGodziny)
        {
            for (auto elem1 : vec)
            {
                if (elem1.godzina == elem)
                    PosortowaneZadania.push_back(elem1);
            }
        }
        break;
    case 3:
        sort(PosortowaneTypy.begin(), PosortowaneTypy.end());
        for (auto elem : PosortowaneTypy)
        {
            for (auto elem1 : vec)
            {
                if (elem1.typ == elem)
                    PosortowaneZadania.push_back(elem1);
            }
        }
        break;
    case 4:
        sort(PosortowaneStatusy.begin(), PosortowaneStatusy.end());
        for (auto elem : PosortowaneStatusy)
        {
            for (auto elem1 : vec)
            {
                if (elem1.status == elem)
                    PosortowaneZadania.push_back(elem1);
            }
        }
        break;
    case 5:
        sort(PosortowaneOpisy.begin(), PosortowaneOpisy.end());
        for (auto elem : PosortowaneOpisy)
        {
            for (auto elem1 : vec)
            {
                if (elem1.opis == elem)
                    PosortowaneZadania.push_back(elem1);
            }
        }
        break;

    default:
        break;
    }
    return PosortowaneZadania;
}

vector<kontakt> filtrujVecK(vector<kontakt> kontakty, int x)
{
    vector<kontakt> PofiltrowaneKontakty;
    switch (x)
    {
    case 1:
    {
        str imie;
        do
        {
            cout << "Podaj imie: " << endl;
            cin >> imie;
            if (!TylkoLitery(imie))
                cout << "Błędne imie. Spróbuj ponownie." << endl;
        } while (!TylkoLitery(imie));

        for (int i = 0; i < kontakty.size(); i++)
        {
            if (kontakty[i].imie == imie)
                PofiltrowaneKontakty.push_back(kontakty[i]);
        }
        break;
    }
    case 2:
    {
        str nazwisko;
        do
        {
            cout << "Podaj nazwisko: " << endl;
            cin >> nazwisko;
            if (!TylkoLitery(nazwisko))
                cout << "Błędne nazwisko. Spróbuj ponownie." << endl;
        } while (!TylkoLitery(nazwisko));

        for (int i = 0; i < kontakty.size(); i++)
        {
            if (kontakty[i].nazwisko == nazwisko)
                PofiltrowaneKontakty.push_back(kontakty[i]);
        }
        break;
    }
    case 3:
    {
        str email;
        do
        {
            cout << "Podaj E-Mail: " << endl;
            cin >> email;
            if (!CzyEmail(email))
                cout << "Błędny E-Mail. Spróbuj ponownie." << endl;
        } while (!CzyEmail(email));

        for (int i = 0; i < kontakty.size(); i++)
        {
            if (kontakty[i].email == email)
                PofiltrowaneKontakty.push_back(kontakty[i]);
        }
        break;
    }
    default:
        break;
    }
    return PofiltrowaneKontakty;
}

vector<zadanie> filtrujVecZ(vector<zadanie> zadania, int x)
{
    vector<zadanie> PofiltrowaneZadania;

    switch (x)
    {
    case 1:
    {
        str data;
        do
        {
            cout << "Podaj datę: " << endl;
            cin >> data;
            if (!CzyData(data))
                cout << "Błędna data. Spróbuj ponownie." << endl;
        } while (!CzyData(data));

        for (int i = 0; i < zadania.size(); i++)
        {
            if (zadania[i].data == data)
                PofiltrowaneZadania.push_back(zadania[i]);
        }

        break;
    }
    case 2:
    {
        str godzina;
        do
        {
            cout << "Podaj godzinę: " << endl;
            cin >> godzina;
            if (!CzyGodzina(godzina))
                cout << "Błędna godzina. Spróbuj ponownie." << endl;
        } while (!CzyGodzina(godzina));

        for (int i = 0; i < zadania.size(); i++)
        {
            if (zadania[i].godzina == godzina)
                PofiltrowaneZadania.push_back(zadania[i]);
        }

        break;
    }
    case 3:
    {
        str typ;
        do
        {
            cout << "Podaj typ: " << endl;
            cin >> typ;
            if (!TylkoLitery(typ))
                cout << "Błędny typ. Spróbuj ponownie." << endl;
        } while (!TylkoLitery(typ));

        for (int i = 0; i < zadania.size(); i++)
        {
            if (zadania[i].typ == typ)
                PofiltrowaneZadania.push_back(zadania[i]);
        }

        break;
    }
    case 4:
    {
        str status;
        do
        {
            cout << "Podaj status: (X lub V)" << endl;
            cin >> status;
            if (status.size() > 1 || status != "X" && status != "x" && status != "V" && status != "v")
                cout << "Błędny status. Spróbuj ponownie." << endl;
        } while (status.size() > 1 || status != "X" && status != "x" && status != "V" && status != "v");

        for (int i = 0; i < zadania.size(); i++)
        {
            if (zadania[i].status == status)
                PofiltrowaneZadania.push_back(zadania[i]);
        }

        break;
    }
    case 5:
    {
        str opis;
        cout << "Podaj opis: " << endl;
        getline(cin, opis);

        for (int i = 0; i < zadania.size(); i++)
        {
            if (zadania[i].opis == opis)
                PofiltrowaneZadania.push_back(zadania[i]);
        }
        break;
    }
    default:
        break;
    }

    return PofiltrowaneZadania;
}

void DodajKontakt(vector<kontakt> &vec)
{
    str imie, nazwisko, email;
    do
    {
        cout << "Podaj imię: A-anuluj" << endl;
        cin >> imie;
        if (imie == "A"){
            show = false;
            return;
        }
        if (!TylkoLitery(imie))
            cout << "Błędne imie. Spróbuj ponownie." << endl;
    } while (!TylkoLitery(imie));
    do
    {
        cout << "Podaj nazwisko: A-anuluj" << endl;
        cin >> nazwisko;
        if (nazwisko == "A"){
            show = false;
            return;
        }
        if (!TylkoLitery(nazwisko))
            cout << "Błędne nazwisko. Spróbuj ponownie." << endl;
    } while (!TylkoLitery(nazwisko));
    do
    {
        cout << "Podaj email: A-anuluj" << endl;
        cin >> email;
        if (email == "A"){
            show = false;
            return;
        }
        if (!CzyEmail(email))
            cout << "Błędny E-Mail. Spróbuj ponownie." << endl;
    } while (!CzyEmail(email));

    kontakt NowaOsoba;
    NowaOsoba.imie = imie;
    NowaOsoba.nazwisko = nazwisko;
    NowaOsoba.email = email;

    vec.push_back(NowaOsoba);
}

void UsunKontakt(vector<kontakt> &vec)
{
    str x;
    int numer = -1;
    WypiszVectorK(vec);
    do
    {
        cout << "Który kontakt usunąć? A - anuluj" << endl;
        cin >> x;
        if (x == "A"){
            show = false;
            return;
        }
        for (char znak : x)
        {
            if (!isdigit(znak))
                continue;
        }
        try
        {
            numer = stoi(x);
        }
        catch (exception &e)
        {
            cout << "Błąd konwersji. Najprawdopodobniej wejście nie jest liczbą. Spróbuj ponownie." << endl;
            numer = -1;
            continue;
        }
        numer = numer - 1;
        if (numer < 0 || numer > vec.size() - 1)
        {
            cout << "Nie ma takiego kontaktu. Spróbuj ponownie." << endl;
            continue;
        }
    } while (numer < 0 || numer > vec.size() - 1);
    vec.erase(vec.begin() + numer);
}

void DodajZadanie(vector<zadanie> &vec)
{
    str data, godzina, typ, status, opis;
    do
    {
        cout << "Podaj datę (RRRR.MM.DD): A-anuluj" << endl;
        cin >> data;
        if (data == "A"){
            show = false;
            return;
        }
        if (CzyData(data) == false)
            cout << "Błędna data. Spróbuj ponownie." << endl;
    } while (!CzyData(data));
    do
    {
        cout << "Podaj godzinę (GG:MM): A-anuluj" << endl;
        cin >> godzina;
        if (godzina == "A"){
            show = false;
            return;
        }
        if (CzyGodzina(godzina) == false)
            cout << "Błędna godzina. Spróbuj ponownie." << endl;
    } while (!CzyGodzina(godzina));
    do
    {
        cout << "Podaj typ: A-anuluj" << endl;
        cin >> typ;
        if (typ == "A"){
            show = false;
            return;
        }
        if (TylkoLitery(typ) == false)
            cout << "Błędny typ. Spróbuj ponownie." << endl;
    } while (!TylkoLitery(typ));
    do
    {
        cout << "Podaj status(X - niewykonane, V - wykonane): A-anuluj" << endl;
        cin >> status;
        if (status == "A"){
            show = false;
            return;
        }
        if (status != "X" && status != "V" && status != "x" && status != "v")
            cout << "Błędny status. Spróbuj ponownie." << endl;
    } while (status != "X" && status != "V" && status != "x" && status != "v");
    if (status == "x")
        status = "X";
    else if (status == "v")
        status = "V";
    cout << "Podaj opis: A-anuluj" << endl;
    cin.clear();
    cin.sync();
    getline(cin, opis);

    if (opis == "A"){
            show = false;
            return;
        }

    zadanie NoweZadanie;
    NoweZadanie.data = data;
    NoweZadanie.godzina = godzina;
    NoweZadanie.typ = typ;
    NoweZadanie.status = status;
    NoweZadanie.opis = opis;

    vec.push_back(NoweZadanie);
}

void UsunZadanie(vector<zadanie> &vec)
{
    str x;
    int numer = -1;
    WypiszVectorZ(vec);
    do
    {
        cout << "Które zadanie usunąć? A-anuluj" << endl;
        cin >> x;
        if (x == "A"){
            show = false;
            return;
        }
        for (char znak : x)
        {
            if (!isdigit(znak))
                continue;
        }
        try
        {
            numer = stoi(x);
        }
        catch (exception &e)
        {
            cout << "Błąd konwersji. Najprawdopodobniej wejście nie jest liczbą. Spróbuj ponownie." << endl;
            numer = -1;
            continue;
        }
        numer = numer - 1;
        if (numer < 0 || numer > vec.size() - 1)
            cout << "Nie ma takiego zadania. Spróbuj ponownie." << endl;
    } while (numer < 0 || numer > vec.size() - 1);
    vec.erase(vec.begin() + numer);
}

void ZmienStatus(vector<zadanie> &vec)
{
    str x;
    int numer = -1;
    WypiszVectorZ(vec);
    do
    {
        cout << "Status którego zadania chcesz zmienić? A-anuluj" << endl;
        cin >> x;
        if (x == "A"){
            show = false;
            return;
        }
        for (char znak : x)
        {
            if (!isdigit(znak))
                continue;
        }
        try
        {
            numer = stoi(x);
        }
        catch (exception &e)
        {
            cout << "Błąd konwersji. Najprawdopodobniej wejście nie jest liczbą. Spróbuj ponownie." << endl;
            numer = -1;
            continue;
        }
        if (numer < 1 || numer > vec.size())
            cout << "Nie ma takiego zadania. Spróbuj ponownie." << endl;
    } while (numer < 1 || numer > vec.size());

    numer = numer - 1;

    string zamiennik;

    do
    {
        cout << "Wprowadź status V(wykonane) lub X(niewykonane): " << endl;
        cin >> zamiennik;
    } while (zamiennik != "V" && zamiennik != "X" && zamiennik != "v" && zamiennik != "x");

    if (zamiennik == "v")
        zamiennik = "V";
    if (zamiennik == "x")
        zamiennik = "X";

    vec[numer].status = zamiennik;
}

vector<kontakt> CzytajKontakty(str nazwa_pliku_kontakty)
{
    fstream wejscie(nazwa_pliku_kontakty);

    vector<kontakt> kontakty;

    if (wejscie.good())
    {
        str imie, nazwisko, email;

        while (wejscie >> imie >> nazwisko >> email)
        {
            kontakt osoba;
            osoba.imie = imie;
            osoba.nazwisko = nazwisko;
            osoba.email = email;
            kontakty.push_back(osoba);
        }
    }
    wejscie.close();
    return kontakty;
}

vector<zadanie> CzytajZadania(str nazwa_pliku_zadania)
{
    fstream wejscie(nazwa_pliku_zadania);

    vector<zadanie> zadania;

    str data, godzina, typ, status, opis;

    if (wejscie.good())
    {
        while (wejscie >> data >> godzina >> typ >> status)
        {
            getline(wejscie, opis);
            opis.erase(0, 1);
            zadanie zad;
            zad.data = data;
            zad.godzina = godzina;
            zad.typ = typ;
            zad.status = status;
            zad.opis = opis;
            zadania.push_back(zad);
        }
    }

    wejscie.close();
    return zadania;
}

void ZapiszWPlikach(str nazwa_pliku_kontakty, str nazwa_pliku_zadania, vector<kontakt> &vecK, vector<zadanie> &vecZ)
{
    ofstream wyjscieKontakty(nazwa_pliku_kontakty, ios::out | ios::trunc);
    ofstream wyjscieZadania(nazwa_pliku_zadania, ios::out | ios::trunc);

    for (auto elem : vecK)
    {
        wyjscieKontakty << elem.imie << " " << elem.nazwisko << " " << elem.email << endl;
    }

    for (auto elem : vecZ)
    {
        wyjscieZadania << elem.data << " " << elem.godzina << " " << elem.typ << " " << elem.status << " " << elem.opis << endl;
    }

    wyjscieKontakty.close();
    wyjscieZadania.close();
}

void Zapytanie()
{
    int x = 0;
    do
    {
        cout << "1.Wróć do menu \n 2.Zakończ" << endl;
        cin >> x;
        if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(), '\n');
            x = 0;
            cout<<"Błąd konwersji. Wejście najprawdopodobniej nie jest liczbą. Spróbuj ponownie."<<endl;
        }
        else if (x != 1 && x != 2) cout << "Nie ma takiej opcji. Spróbuj ponownie." << endl;
    } while (x != 1 && x != 2);
    if (x == 1)
        system("cls");
    if (x == 2)
        DzialanieProgramu = false;
}

int WedlugCzegoK(string flag)
{
    int x = 0;
    do
    {
        do
        {
            cout << flag << " kontakty według: \n 1.Imienia \n 2.Nazwiska \n 3.E-Maila" << endl;
            cin >> x;
            if (cin.fail())
                cout << "Błąd konwersji. Najprawdopodobniej wejście nie jest liczbą. Spróbuj ponownie." << endl;
        } while (cin.fail());
        if (x != 1 && x != 2 && x != 3)
        {
            x = 0;
            cout << "Nie ma takiej opcji. Spróbuj ponownie." << endl;
        }
    } while (x < 1 || x > 3);
    return x;
}

int WedlugCzegoZ(string flag)
{
    int x = 0;
    do
    {
        do
        {
            cout << flag << " zadania według: \n 1.Daty \n 2.Godziny \n 3.Typu \n 4.Statusu \n 5.Opisu" << endl;
            cin >> x;
            if (cin.fail())
                cout << "Błąd konwersji. Najprawdopodobniej wejście nie jest liczbą. Spróbuj ponownie." << endl;
        } while (cin.fail());

        if (x != 1 && x != 2 && x != 3 && x != 4 && x != 5)
        {
            x = 0;
            cout << "Nie ma takiej opcji. Spróbuj ponownie." << endl;
        }
    } while (x < 1 || x > 5);
    return x;
}

bool CzySortowac()
{
    string wejscie;
    char x;
    do
    {
        do
        {
            cout << "Czy sortować? T/N" << endl;
            cin >> wejscie;
            if (cin.fail() || wejscie.size() > 1)
                cout << "Błąd konwersji. Wejście najprawdopodobniej nie jest znakiem. Spróbuj ponownie." << endl;
        } while (cin.fail() || wejscie.size() > 1);
        x = wejscie[0];
        if (x != 'T' && x != 'N' && x != 't' && x != 'n')
            cout << "Nie ma takiej opcji. Spróbuj ponownie." << endl;

    } while (x != 'T' && x != 'N' && x != 't' && x != 'n');

    if (x == 'T' || x == 't')
        return true;
    else
        return false;
}

bool CzyFiltrowac()
{
    string wejscie;
    char x;
    do
    {
        do
        {
            cout << "Czy filtrować? T/N" << endl;
            cin >> wejscie;
            if (cin.fail() || wejscie.size() > 1)
                cout << "Błąd konwersji. Wejście najprawdopodobniej nie jest znakiem. Spróbuj ponownie." << endl;
        } while (cin.fail() || wejscie.size() > 1);
        x = wejscie[0];
        if (x != 'T' && x != 'N' && x != 't' && x != 'n')
            cout << "Nie ma takiej opcji. Spróbuj ponownie." << endl;
    } while (x != 'T' && x != 'N' && x != 't' && x != 'n');

    if (x == 'T' || x == 't')
        return true;
    else
        return false;
}

void Start(vector<kontakt> &kontakty, vector<zadanie> &zadania)
{
    int x = 0;
    do
    {
        cout << "Witaj w Organizerze! Co chciał(a)byś zrobić?" << endl;
        cout << "1.Dodaj kontakt \n 2.Usuń kontakt \n 3.Dodaj zadanie \n 4.Usuń zadanie \n 5.Wyświetl kontakty \n 6.Wyświetl zadania \n 7.Zmień status zadania \n 8.Zakończ działanie programu" << endl;
        cin >> x;
        if (cin.fail())
        {
            x = 0;
            cout << "Błąd konwersji. Najprawdopodobniej wejście nie jest liczbą. Spróbuj ponownie." << endl;
            cin.clear();
            str ignore;
            cin >> ignore;
            continue;
        }
        else if (x != 1 && x != 2 && x != 3 && x != 4 && x != 5 && x != 6 && x != 7 && x != 8)
        {
            x = 0;
            cout << "Nie ma takiej opcji. Spróbuj ponownie." << endl;
        }
    } while (x < 1 || x > 8);

    switch (x)
    {
    case 1:
        DodajKontakt(kontakty);
        if(show){
            cout << endl
             << "Podsumowanie:" << endl;
            WypiszVectorK(kontakty);
        }
        show = true;
        Zapytanie();
        break;
    case 2:
        UsunKontakt(kontakty);
        if(show){
            cout << endl
             << "Podsumowanie:" << endl;
            WypiszVectorK(kontakty);
        }   
        show = true;
        Zapytanie();
        break;
    case 3:
        DodajZadanie(zadania);
        if(show){
            cout << endl
             << "Podsumowanie:" << endl;
            WypiszVectorZ(zadania);
        }
        show = true;
        Zapytanie();
        break;
    case 4:
        UsunZadanie(zadania);
        if(show){
            cout << endl
             << "Podsumowanie:" << endl;
            WypiszVectorZ(zadania);
        }
        show = true;
        Zapytanie();
        break;
    case 5:
    {
        vector<kontakt> PosortowaneKontakty;
        vector<kontakt> PofiltrowaneKontakty;

        if (CzyFiltrowac())
        {
            int kryterium = WedlugCzegoK("Pofiltrować");
            PofiltrowaneKontakty = filtrujVecK(kontakty, kryterium);
            if (CzySortowac())
            {
                int kryterium = WedlugCzegoK("Posortować");
                PosortowaneKontakty = sortujVecK(PofiltrowaneKontakty, kryterium);
                WypiszVectorK(PosortowaneKontakty);
            }
            else
            {
                WypiszVectorK(PofiltrowaneKontakty);
            }
        }
        else
        {
            if (CzySortowac())
            {
                int kryterium = WedlugCzegoK("Posortować");
                PosortowaneKontakty = sortujVecK(kontakty, kryterium);
                WypiszVectorK(PosortowaneKontakty);
            }
            else
                WypiszVectorK(kontakty);
        }
        Zapytanie();
        break;
    }
    case 6:
    {
        vector<zadanie> PosortowaneZadania;
        vector<zadanie> PofiltrowaneZadania;

        if (CzyFiltrowac())
        {
            int kryterium = WedlugCzegoZ("Pofiltrować");
            PofiltrowaneZadania = filtrujVecZ(zadania, kryterium);
            if (CzySortowac())
            {
                int kryterium = WedlugCzegoZ("Posortować");
                PosortowaneZadania = sortujVecZ(PofiltrowaneZadania, kryterium);
                WypiszVectorZ(PosortowaneZadania);
            }
            else
            {
                WypiszVectorZ(PofiltrowaneZadania);
            }
        }
        else
        {
            if (CzySortowac())
            {
                int kryterium = WedlugCzegoZ("Posortować");
                PosortowaneZadania = sortujVecZ(zadania, kryterium);
                WypiszVectorZ(PosortowaneZadania);
            }
            else
                WypiszVectorZ(zadania);
        }
        Zapytanie();
        break;
    }
    case 7:
        ZmienStatus(zadania);
        if(show){
            cout << endl
             << "Podsumowanie:" << endl;
            WypiszVectorZ(zadania);
        }
        show = true;
        Zapytanie();
        break;
    case 8:
        DzialanieProgramu = false;
        break;

    default:
        break;
    }
}

bool TylkoLitery(string nazwa)
{
    for (char znak : nazwa)
    {
        if (!isalpha(znak))
        {
            return false;
        }
    }
    return true;
}

bool CzyEmail(string email)
{
    regex wzorzec("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    if (regex_match(email, wzorzec))
        return true;
    else
        return false;
}

bool CzyData(string data)
{
    regex wzorzec("[0-9]{4}.[0-9]{2}.[0-9]{2}");
    if (regex_match(data, wzorzec))
    {
        if (data[5] == '0' && data[6] == '0')
            return false;
        if (data[8] == '0' && data[9] == '0')
            return false;
        return true;
    }
    else
        return false;
}

bool CzyGodzina(string godzina)
{
    regex wzorzec("[0-2]+[0-9]:[0-5]+[0-9]");
    if (regex_match(godzina, wzorzec))
    {
        regex wzorzec1("[4-9]");
        string s(1, godzina[1]);
        if (godzina[0] == '2' && regex_match(s, wzorzec1))
            return false;
        return true;
    }
    else
        return false;
}
