#include "globe.h"

void setup()
{    
    common_routine_init();    
    globe_init();

    *console << CIRCUIT_NAME << F(": Init done") << endl;
}

void loop()
{
    common_routine();
    
    globe_routine();
}