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
// Vul de schalen met tegels, voor zo ver mogelijk.
void TegelSpel::vulSchalen()
{
    // Tel aantal per kleur.
    int aantalGeel = 0;
    int aantalBlauw = 0;

    for (int i = 0; i < this->aantalSchalen; i++) // Voor elke schaal.
    {
        // Plek over in schaal.
        int plekOver = maxTegelsOpSchaal - schalen[i].first - schalen[i].second;

        for (int j = 0; j < plekOver; j++) // Vul de plekjes over.
        {
            if (this->pot.length() == 0) // Pot is leeg.
                return;

            if (pot[0] == 'g')
                schalen[i].first++;
            else if (pot[0] == 'b')
                schalen[i].second++;

            this->pot = pot.substr(1); // Verwijder eerste tegel in pot.
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

// Kijk of bord vol is.
bool TegelSpel::bordVol(vector<pair<int, int>> bord)
{
    for(pair rij : bord)
    {
        if (rij.first != MaxPerRij && rij.second != MaxPerRij) // Niet-volle rij gevonden.
        return false; 
    }
    return true;
}

//*************************************************************************

bool TegelSpel::eindstand()
{
    return (bordVol(speler1Bord) || bordVol(speler2Bord) ||   // Vol bord gevonden.
        bepaalVerschillendeZetten().size() == 0);                   // Geen mogelijke zetten.
} // eindstand

//*************************************************************************
// Druk alles af
void TegelSpel::drukAf()
{
    drukPotAf(); // Print pot.
    drukSchalenAf(); // Print schalen.

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
    for (pair pair : bord) // Voor elke rij in bord.
    {
        for (int i = 0; i < vakjesPerRij; i++)  // Loop rij af.
        {
            if (i < pair.first) // Print gele tegels
                cout << "g";
            else if (i < pair.second) // Print blauwe tegels.
                cout << "b";
            else
                cout << "_"; // leeg.
        }
        cout << endl;
    }
}

//*************************************************************************

// Druk schalen af.
void TegelSpel::drukSchalenAf()
{
    int counter = 0;
    for (pair pair : schalen) // Voor elke schaal.
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

// Zoek voor duplicate (meerdere identieke zetten mogelijk).
int TegelSpel::vindDubbel(Zet zet, vector<pair<int, char>> zetten)
{
    // Zoek duplicate.
    for(int i = 0; i < zetten.size(); i++)
    {
        if(zet.schaal == zetten[i].first && zet.kleur == zetten[i].second)
            return i; // Dubbel gevonden, geef index terug.
    }
    return -1; // Geen duplicate gevonden.
}

//*************************************************************************

void TegelSpel::verwerkMogelijkeZet(Zet zet, vector<pair<int, char>>& zetten)
{
    int aantalInSchaal = zet.kleur == 'g' ? schalen[zet.schaal].first : schalen[zet.schaal].second;
    if(zet.rij == -1 || aantalInSchaal < zet.aantal) 
        return; // Geen rij gevonden waar zet mogelijk is. Of schaal heeft niet genoeg tegels van kleur.
    int dubbelIndex = vindDubbel(zet, zetten);
    if(dubbelIndex == -1) // Geen dubbel gevonden. 
        zetten.emplace_back(zet.schaal, zet.kleur);
    else // Dubbel gevonden, gebruik kleinste schaal getal.
        zetten[dubbelIndex].first = min(zetten[dubbelIndex].first, zet.schaal);
}

//*************************************************************************

vector<pair<int, char>> TegelSpel::bepaalVerschillendeZetten()
{
    vector<pair<int, char>> zetten;

    for(int i = 0; i < aantalSchalen; i++) // Voor elke schaal check elke mogelijke kleur.
    {
        if(schalen[i].first > 0)
            verwerkMogelijkeZet(*maakZet(i, 'g'), zetten);
        if(schalen[i].second > 0)
        verwerkMogelijkeZet(*maakZet(i, 'b'), zetten);
    }
    return zetten;
} // bepaalVerschillendeZetten

//*************************************************************************

Zet* TegelSpel::maakZet(int schaal, char kleur)
{
    // Aantal tegels op de schaal van kleur.
    int aantal = kleur == 'g'? schalen[schaal].first : schalen[schaal].second;

    Zet* zet = new Zet(); // Maak zet object.

    // Attributen.
    zet->aantal = aantal;
    zet->kleur = kleur;
    zet->speler = spelerAanBeurt;
    zet->schaal = schaal;
    zet->bord = &((spelerAanBeurt == 0) ? speler1Bord : speler2Bord);
    zet->rij = bepaalBesteRij(*zet);
    zet->tegelsUitPotGehaald = pot.substr(0, zet->aantal);

    return zet;
}

//*************************************************************************

// Verwerk zet op het bord.
void TegelSpel::verwerkZet(Zet& zet)
{
    (zet.kleur == 'g' ? (*(zet.bord))[zet.rij].first : (*(zet.bord))[zet.rij].second)  += zet.aantal;
}

//*************************************************************************
// Doe de zet.
bool TegelSpel::doeZet(int schaal, char kleur)
{
    if(schalen.size() < schaal || (kleur != 'g' && kleur != 'b')) // Kijk of schaal en kleur bestaan.
        return false;

    // Maak zet instantie.
    Zet* zet = maakZet(schaal, kleur);

    if(zet->rij != -1) // Kijk of er een mogelijke rij gevonden is.
    {
        // Update bord.
        verwerkZet(*zet);

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
// Tel volle rijen

int TegelSpel::telRijen(vector<pair<int, int>> bord)
{
    int counter = 0;
    for(pair rij : bord)
    {
        if(rij.first == vakjesPerRij || rij.second == vakjesPerRij)
            counter++;
    }
    return counter;
}

//*************************************************************************
// Bereken score en winnaar, int 1 is winnende speler, int 2 is score.

pair<int, int> TegelSpel::berekenScore()
{
    pair<int, int> score;

    int speler1score = telRijen(speler1Bord);
    int speler2score = telRijen(speler2Bord);

    // Bepaal winnaar.
    speler1score > speler2score ? score.first = 0 : score.first = 1; 
    // Bepaal score.
    speler1score > speler2score ? score.second = speler1score - speler2score : score.second = speler2score - speler1score;

    return score;
}
//*************************************************************************
// bereken recursief de score van een speler bij willekeurige zetten.
int TegelSpel::speelRandom(int speler)
{
    if(eindstand())
    {
        int score = (speler == 0) ? this->telRijen(speler1Bord) : this->telRijen(speler2Bord);
        return score;
    }
    else
    {
        vector < pair < int, char > > zetten = this->bepaalVerschillendeZetten();
        pair < int, char > randomZet = zetten[randomGetal(0, zetten.size()-1)];
        this->doeZet(randomZet.first, randomZet.second);
        return this->speelRandom(speler);
    }
}

//*************************************************************************

pair<int, char> TegelSpel::bepaalGoedeZet(int nrSimulaties)
{
    if(eindstand())
        return pair(-1, -1);

    pair<int, char> goedeZet;

    // Bepaal mogelijke zetten in huidige positie.
    vector < pair < int, char > > zetten = bepaalVerschillendeZetten(); 

    float hoogsteScore = 0;

    for(pair zet : zetten) // Voor elke mogelijke zet.
    {
        float score = 0;
        for(int i = 0; i < nrSimulaties; i++) // Speel n keer willekeurig het spel.
        {
            TegelSpel kopie = *this;
            kopie.doeZet(zet.first, zet.second);
            score += kopie.speelRandom(spelerAanBeurt);
            
        }
        score /= nrSimulaties;
            if(score > hoogsteScore)
            {
                hoogsteScore = score;
                goedeZet = zet;
            }
    }

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
