// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream> // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel()
{

} // default constructor

//*************************************************************************

int TegelSpel::getSchalen()
{
    return this->aantalSchalen;
} // getSchalen

//*************************************************************************

string TegelSpel::getPot()
{ return this->pot; } // getPot

//*************************************************************************

vector<pair<int, int>> TegelSpel::getInhoudSchalen()
{ return schalen; } // getInhoudSchalen

//*************************************************************************

vector<pair<int, int>> TegelSpel::getInhoudRijen(int speler)
{
    if(speler == 0)
        return speler1Bord;
    else
        return speler2Bord;
} // getInhoudRijen

//*************************************************************************

// Lees het spel bestand in.
bool TegelSpel::leesInSpel(const char *invoernaam)
{
    ifstream inputFile(invoernaam); // Open bestand.
    if (!inputFile.is_open())
    {
        cout << "Kon bestand niet openen" << endl;
        return false; // Niet gelukt.
    }
    else
    {
        bouwSpel(inputFile); // Bouw spel op.
        inputFile.close();   // Sluit bestand.
        return true;         // Wel gelukt.
    }
} // leesInSpel

//*************************************************************************

// Bouw het spel, regel voor regel, op.
void TegelSpel::bouwSpel(ifstream &inputFile)
{
    string line;
    getline(inputFile, line); // line 1: pot
    vulPot(line);

    getline(inputFile, line);                // line 2: $ schalen, # tegels op op een schaal
    this->aantalSchalen = line[0] - '0';     // # <= 5 dus is altijd 1 char.
    this->maxTegelsOpSchaal = line[2] - '0'; // ^
    schalen.resize(this->aantalSchalen);
    vulSchalen(); // Vul de schalen.

    getline(inputFile, line);                // line 2: # rijen en # vakjes per rij
    this->aantalRijen = line[0] - '0';       // # rijen
    if (line[1] == ' ')                      // Check of # < 10, # kan 10 zijn.
        this->vakjesPerRij = line[2] - '0';  // # vakjes per rij
    else
    {
        this->aantalRijen = 10;             // aantalRijen = 10;
        this->vakjesPerRij = line[3] - '0'; // vakjesPerRij staat 1 char verder.
    }
    int counter = 0;
    while (counter < this->aantalRijen) // Scan k regels.
    {
        getline(inputFile, line);
        speler1Bord.emplace_back(line[0] - '0', line[2] - '0'); // Sla regel op voor s1.
        counter++;
    }
    counter = 0;
    while (counter < this->aantalRijen)
    {
        getline(inputFile, line);
        speler2Bord.emplace_back(line[0] - '0', line[2] - '0'); // Sla regel op voor s2.
        counter++;
    }
    getline(inputFile, line); // Speler aan de beurt.
    this->spelerAanBeurt = line[0] - '0';
}

//*************************************************************************

void TegelSpel::vulSchalen()
{
    int potGrootte = this->pot.length();
    int aantalGeel = 0;
    int aantalBlauw = 0;

    for (int i = 0; i < this->aantalSchalen; i++) // Voor elke schaal.
    {
        int plekOver = maxTegelsOpSchaal - schalen[i].first - schalen[i].second;

        for (int j = 0; j < plekOver; j++)
        {
            if (this->pot.length() == 0)
                return;

            if (pot[0] == 'g')
                schalen[i].first++;
            else if (pot[0] == 'b')
                schalen[i].second++;

            this->pot = pot.substr(1);
        }
    }
}

//*************************************************************************

// Vul de pot op met tegels.
void TegelSpel::vulPot(string line)
{
    for (char c : line)
    {
        if (c == 'g' || c == 'b') // We kijken alleen naar de correcte kleuren.
            this->pot += c;
    }
}

//*************************************************************************

bool TegelSpel::eindstand()
{
    // TODO: implementeer deze memberfunctie

    return false;

} // eindstand

//*************************************************************************
// Druk alles af
void TegelSpel::drukAf()
{
    drukPotAf();
    drukSchalenAf();

    cout << "Speler 1 bord:\n";
    drukBordAf(speler1Bord);
    cout << "Speler 2 bord:\n";
    drukBordAf(speler2Bord);

    cout << "Speler aan zet: " << spelerAanBeurt + 1 << endl;
} // drukAf

//*************************************************************************
// Druk borden af.
void TegelSpel::drukBordAf(vector<pair<int, int>>& bord)
{
    for (pair pair : bord)
    {
        for (int i = 0; i < vakjesPerRij; i++) // Print gele tegels.
        {
            if (i < pair.first)
            {
                cout << "g";
            }
            else if (i < pair.second)
            {
                cout << "b";
            }
            else
            {
                cout << "_";
            }
        }
        cout << endl;
    }
}

//*************************************************************************

// Druk schalen af.
void TegelSpel::drukSchalenAf()
{
    int counter = 0;
    for (pair pair : schalen)
    {
        cout << "Schaal " << counter << endl;
        for (int i = 0; i < pair.first; i++) // Print gele tegels.
        {
            cout << "g";
        }
        for (int i = 0; i < pair.second; i++) // Print blauwe tegels.
        {
            cout << "b";
        }
        cout << endl;
        counter++;
    }
}

//*************************************************************************

// Druk de pot af.
void TegelSpel::drukPotAf()
{
    cout << "Tegels in de pot:" << endl;
    for (char c : this->pot) // Druk tegels af
    {
        cout << c;
    }
    cout << endl;
    cout << "^" << endl; // Volgende tegel in de pot indicator
}

//*************************************************************************

vector<pair<int, char>> TegelSpel::bepaalVerschillendeZetten()
{
    vector<pair<int, char>> zetten;

    // TODO: implementeer deze memberfunctie

    return zetten;

} // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet(int schaal, char kleur)
{
    // TODO: implementeer deze memberfunctie

    return true;

} // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet()
{
    // TODO: implementeer deze memberfunctie

    return true;

} // unDoeZet

//*************************************************************************

int TegelSpel::besteScore(pair<int, char> &besteZet,
                          long long &aantalStanden)
{
    // TODO: implementeer deze memberfunctie

    return 0;

} // besteScore

//*************************************************************************

pair<int, char> TegelSpel::bepaalGoedeZet(int nrSimulaties)
{
    pair<int, char> goedeZet;

    // TODO: implementeer deze memberfunctie

    return goedeZet;

} // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore()
{
    // TODO: implementeer deze memberfunctie

    return 0;

} // bepaalGoedeScore

//*************************************************************************

void TegelSpel::doeExperiment()
{
    // TODO: implementeer deze memberfunctie

} // doeExperiment
