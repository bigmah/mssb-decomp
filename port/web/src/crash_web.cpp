// Crash handling for web builds: a trap or abort surfaces in the page (see
// index.html), which shows the error and stops the game; there's no window to
// get stuck, so there's no watchdog.
#include "port/os.h"

extern "C" {
void port_crash_init(const char* userPath) { (void)userPath; }
void port_crash_heartbeat(void) {}
}
