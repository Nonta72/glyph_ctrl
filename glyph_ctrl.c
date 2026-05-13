// glyph_ctrl.c
// Usage:
//   glyph_ctrl on          -> turns on glyphs lights and sets brightness to 4095
//   glyph_ctrl off         -> turns off glyphs by setting their brightness to 0
//   glyph_ctrl 1234        -> sets brightness to X value (between 0 and 4095)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SYSFS_NODE "/sys/class/leds/aw210xx_led/all_white_leds_br"
#define MAX_BRIGHTNESS 4095

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: glyph_ctrl <on|off|0-%d>\n", MAX_BRIGHTNESS);
        return 1;
    }

    int value;

    if (strcmp(argv[1], "on") == 0) {
        value = MAX_BRIGHTNESS;
    } else if (strcmp(argv[1], "off") == 0) {
        value = 0;
    } else {
        char *end;
        errno = 0;
        long parsed = strtol(argv[1], &end, 10);
        if (errno != 0 || *end != '\0' || parsed < 0 || parsed > MAX_BRIGHTNESS) {
            fprintf(stderr, "Invalid value: '%s'. Must be on, off, or 0-%d.\n",
                    argv[1], MAX_BRIGHTNESS);
            return 1;
        }
        value = (int)parsed;
    }

    FILE *f = fopen(SYSFS_NODE, "w");
    if (!f) {
        perror("Failed to open sysfs node");
        return 1;
    }

    fprintf(f, "%d\n", value);
    fclose(f);
    return 0;
}
