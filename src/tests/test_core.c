#include <recomp_globals.h>
#include <printf.h>

RECOMP_CALLBACK("*", recomp_on_init) void starting_tests () {
    recomp_printf("Recomp LibC: Starting Tests...\n");

    rc_printf("PRINTF WORKS!\n");
}
