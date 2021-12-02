#include "axe.h"
#include "selector.h"

Axe getCurrentAxe()
{
  if ((digitalRead(PIN_AXE_X) == LOW)) { return Axe_x; }
  if ((digitalRead(PIN_AXE_Y) == LOW)) { return Axe_y; }
  if ((digitalRead(PIN_AXE_Z) == LOW)) { return Axe_z; }
  if ((digitalRead(PIN_AXE_A) == LOW)) { return Axe_a; }
}
