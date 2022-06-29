#include "lipo.h"
#include "screen.h"

SFE_MAX1704X lipo(MAX1704X_MAX17043);

void initLipo()
{
  // Uncomment this line to enable helpful debug messages on Serial
  // lipo.enableDebugging();

  // Set up the MAX17044 LiPo fuel gauge:
  const int NB_LIPO_CONNEXTION_ATTEMPT = 3;
  int lipo_connexion_attempt = 0;
  while (lipo.begin(Wire) == false)
  {
    ++lipo_connexion_attempt;
    if (NB_LIPO_CONNEXTION_ATTEMPT < lipo_connexion_attempt)
    {
      screenSendMessage("NO LIPO");
      break;
    }
  }

  // Quick start restarts the MAX17044 in hopes of getting a more accurate
  // guess for the SOC.
  lipo.quickStart();
}