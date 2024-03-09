// Implementatie van standaard functies.

#include <iostream>
#include <cstdlib> // voor rand
#include "standaard.h"
using namespace std;

//*************************************************************************

bool integerInBereik(const char *variabele, int waarde, int minWaarde, int maxWaarde)
{
    if (waarde >= minWaarde && waarde <= maxWaarde)
        return true;
    else
    {
        cout << variabele << "=" << waarde << ", maar moet in [" << minWaarde
             << "," << maxWaarde << "] liggen." << endl;
        return false;
    }

} // integerInBereik

//*************************************************************************

bool integerInBereik(int waarde, int minWaarde, int maxWaarde)
{
    return (waarde >= minWaarde && waarde <= maxWaarde);
} // integerInBereik

//*************************************************************************

int randomGetal(int min, int max)
{
    return ((rand()) % (max - min + 1)) + min;
} // randomGetal

int min(int one, int two) {
    return (one < two) ? one : two;
}
