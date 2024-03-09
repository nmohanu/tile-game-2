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

    cout << "Speler 0 bord:\n";
    drukBordAf(speler1Bord);
    cout << "Speler 1 bord:\n";
    drukBordAf(speler2Bord);

    cout << "Speler aan zet: " << spelerAanBeurt << endl;
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
    // Aantal tegels op de schaal van kleur.
    int aantal = kleur == 'g'? schalen[schaal].first : schalen[schaal].second;

    if(schalen.size() < schaal || (kleur != 'g' && kleur != 'b')) // Kijk of schaal en kleur bestaan.
        return false;

    Zet* zet = new Zet(); // Maak zet object.
    zet->aantal = aantal;
    zet->kleur = kleur;
    zet->speler = spelerAanBeurt;
    zet->schaal = schaal;
    zet->bord = &((spelerAanBeurt == 0) ? speler1Bord : speler2Bord);
    zet->rij = bepaalBesteRij(*zet);
    zet->tegelsUitPotGehaald = pot.substr(0, zet->aantal);

    if(zet->rij != -1)
    {
        // Update bord.
        (zet->kleur == 'g' ? (*(zet->bord))[zet->rij].first : (*(zet->bord))[zet->rij].second)  += zet->aantal;
        kleur == 'g'? schalen[schaal].first = 0 : schalen[schaal].second = 0; // Haal tegels van schaal af.
        vulSchalen(); // Hervul de schalen.

        // Update de zet stack.
        zet->vorige = this->laatsteZet;
        this->laatsteZet = zet;
    }
    else
    {
        return false;
        delete zet;
    }
    wisselSpelerAanBeurt();
    return true;
} // doeZet

//*************************************************************************
int TegelSpel::bepaalBesteRij(Zet& zet)
{
    // Houd beste kandidaat bij, 1 = index, 2 = aantal lege plekken over na zet.
    pair <int, int> besteKandidaat(-1, -1);
    // Voor het geval dat er meerdere even sterke kandidaten zijn, houd bij welke indexen.
    vector <int> kandidaten;
    for(int i = 0; i < zet.bord->size(); i++)
    {   // Check of andere kleur niet bestaat op de rij.
        if(((zet.kleur == 'g') ? (*(zet.bord))[i].second : (*(zet.bord))[i].first) == 0)
        { // Rij is geldig
            // Bereken hoeveel tegels er over zijn na plaatsen van tegels op schaal.
            int aantalOver = vakjesPerRij - (zet.kleur == 'g'? (*(zet.bord))[i].first : (*(zet.bord))[i].second) - zet.aantal;
            if(aantalOver >= 0 && (aantalOver <= besteKandidaat.second || besteKandidaat.first == -1))
            {   // Even goede rij gevonden, sla op.
                if(aantalOver == besteKandidaat.second)
                    kandidaten.emplace_back(i);
                else
                {   // Nieuwe beste rij gevonden.
                    besteKandidaat.first = i;
                    besteKandidaat.second = aantalOver;
                    kandidaten.clear(); // Reset de lijst van kindidaten.
                }
            }
        }
    }
    // Kijk of er een kandidaat is en verwerk de zet.
    if(besteKandidaat.first == -1 && kandidaten.size() == 0) // Geen mogelijke rij gevonden.
        return -1;
    else if(kandidaten.size() > 0) // Meerdere rijen zijn even goed, kies willekeurig.
        return randomGetal(0, kandidaten.size()-1); 
    else // Er is 1 beste rij gevonden.
        return besteKandidaat.first;
}
//*************************************************************************

bool TegelSpel::unDoeZet()
{
    Zet* verwijderZet = laatsteZet;
    if(this->laatsteZet == nullptr)
        return false;
    
    // Undo zet op bord.
    (verwijderZet->kleur == 'g' ? (*(verwijderZet->bord))[verwijderZet->rij].first : (*(verwijderZet->bord))[verwijderZet->rij].second) -= verwijderZet->aantal;

    // Haal de uit pot gehaald tegels van de schaal af.
    for(int i = 0; i < laatsteZet->tegelsUitPotGehaald.length(); i++)
    {
        if(laatsteZet->tegelsUitPotGehaald[i] == 'g')
            schalen[verwijderZet->schaal].first--;
        else
            schalen[verwijderZet->schaal].second--;
    }

    (verwijderZet->kleur == 'g' ? schalen[verwijderZet->schaal].first : schalen[verwijderZet->schaal].second) += verwijderZet->aantal;

    // Herstel de pot.
    pot = laatsteZet->tegelsUitPotGehaald + pot;
    laatsteZet = verwijderZet->vorige;
    delete verwijderZet;
    wisselSpelerAanBeurt();
    return true;

} // unDoeZet

//*************************************************************************
// Wissel tussen speler 0 en 1.
void TegelSpel::wisselSpelerAanBeurt() 
{ spelerAanBeurt = !spelerAanBeurt; }

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
