
#include "commonstuff.h"

#ifndef ENTRADA_H_
#define ENTRADA_H_

char barrierPulseCounter = 0;
bool barrierUp;
bool barrierDown;

bool carWaiting = false;
seconds_t tPreviousCar = 0;

miliseconds_t antireb_S01 = 0;
miliseconds_t antireb_SW1 = 0;

void barrera(barrier_status_t);
void barrierMove(void);
void barrierStope(void);
void isbarrierDown(void);       // ??? necesita revisión
// void tunnelGotBusy(void);    // ??? necesita revisión
void barrierControl(status_t);  // debe terminarse

#endif /* ENTRADA_H_ */

