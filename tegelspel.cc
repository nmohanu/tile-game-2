// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen ()
{
  // TODO: implementeer deze memberfunctie
  return 0;

}  // getSchalen

//*************************************************************************

string TegelSpel::getPot ()
{ string retString;

  // TODO: implementeer deze memberfunctie
  return retString;

}  // getPot

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudSchalen ()
{ vector< pair <int,int> > inhoudSchalen;

  // TODO: implementeer deze memberfunctie

  return inhoudSchalen;

}  // getInhoudSchalen

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudRijen (int speler)
{ vector< pair <int,int> > inhoudRijen;

  // TODO: implementeer deze memberfunctie

  return inhoudRijen;

}  // getInhoudRijen

//*************************************************************************

// Lees het spel bestand in.
bool TegelSpel::leesInSpel (const char* invoernaam)
{
  std::ifstream inputFile(invoernaam); // Open bestand.
  if(!inputFile.is_open())
  {
    std::cout << "Kon bestand niet openen" << std::endl;
    return false; // Niet gelukt.
  }
  else
  {
    bouwSpel(inputFile); // Bouw spel op.
    inputFile.close(); // Sluit bestand.
    return true; // Wel gelukt.
  }
  
}  // leesInSpel

//*************************************************************************

// Bouw het spel, regel voor regel, op.
void TegelSpel::bouwSpel(std::ifstream& inputFile)
{
    std::string line;
    std::getline(inputFile, line);            // line 1: pot
    vulPot(line);
    std::getline(inputFile, line);            // line 2: $ schalen, # tegels op op een schaal
    this->aantalSchalen = line[0] - '0';      // # <= 5 dus is altijd 1 char.
    this->maxTegelsOpSchaal = line[2] - '0';  // ^
    std::getline(inputFile, line);            // line 2: # rijen en # vakjes per rij
    this->aantalRijen = line[0] - '0';        // # rijen
    if(line[1] == ' ')                        // Check of # < 10, # kan 10 zijn.
      this->vakjesPerRij = line[2] -'0';      // # vakjes per rij
    else
    {
      this->aantalRijen = 10;                 // aantalRijen = 10;
      this->vakjesPerRij = line[3] -'0';      // vakjesPerRij staat 1 char verder.
    }
    int counter = 0; 
    while(counter < this->aantalRijen)              // Scan k regels.
      speler1Bord.emplace_back(line[0], line[2]);   // Sla regel op voor s1.
    counter = 0;
    while(counter < this->aantalRijen)
      speler1Bord.emplace_back(line[0], line[2]);   // Sla regel op voor s2.
    std::getline(inputFile, line);                  // Speler aan de beurt.
    this->spelerAanBeurt = line[0] - '0';
}

//*************************************************************************

// Vul de pot op met tegels.
void TegelSpel::vulPot(string line)
{
  for(char c : line)
  {
    if(c == 'g' || c == 'b') // We kijken alleen naar de correcte kleuren.
      this->pot += c;
  }
}

//*************************************************************************

bool TegelSpel::eindstand ()
{
  // TODO: implementeer deze memberfunctie

  return false;

} // eindstand

//*************************************************************************

void TegelSpel::drukAf ()
{
  // TODO: implementeer deze memberfunctie

}  // drukAf

//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten ()
{ vector< pair<int,char> > zetten;

  // TODO: implementeer deze memberfunctie

  return zetten;

}  // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet ()
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // unDoeZet

//*************************************************************************

int TegelSpel::besteScore (pair<int,char> &besteZet,
                             long long &aantalStanden)
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // besteScore

//*************************************************************************

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties)
{ pair<int,char> goedeZet;

  // TODO: implementeer deze memberfunctie

  return goedeZet;

}  // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore ()
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore

//*************************************************************************

void TegelSpel::doeExperiment ()
{
  // TODO: implementeer deze memberfunctie

}  // doeExperiment

