#include "DC30Badge.h"
#include "images/DEFCON.h"
#include "images/skull1.h"
#include "images/skull2.h"
#include "ssd1306.h"


int main() {
    init();
    ssd1306_bmp_show_image_with_offset(&Screen, DEFCONdat, DEFCONsz, 31, 0);
    ssd1306_show(&Screen);
    int col = 0b000;
    bool rev = false;
    bool inv = false;
    bool sk = false;
    bool sk1 = true;
    int i = 0, j = 0;
    while (1) {
        if (j > 5000) {
            sk = !sk;
            j = 0;
            ssd1306_invert(&Screen, 0);
            if (!sk) {
                ssd1306_clear(&Screen);
                ssd1306_bmp_show_image_with_offset(&Screen, DEFCONdat, DEFCONsz, 31, 0);
                ssd1306_show(&Screen);
            }
        }
        if (i > 1000 && !sk) {
            i = 0; inv = !inv;
            ssd1306_invert(&Screen, inv);
        }
        if (i > 500 && sk) {
            sk1 = !sk1;
            ssd1306_clear(&Screen);
            if (sk1) { ssd1306_bmp_show_image_with_offset(&Screen, dat1, sz1, 42, 0); }
            else { ssd1306_bmp_show_image_with_offset(&Screen, dat2, sz2, 42, 0); }
            ssd1306_show(&Screen);
            i = 0;
        }
        if (rev) { col--; }
        else { col++; }
        if (col > 0b110) { col = 0b101; rev = !rev; }
        if (col < 0b001) { col = 0b010; rev = !rev; }
        LED((col >> 0) & 1, (col >> 1) & 1, (col >> 2) & 1);
        sleep_ms(100);
        i += 100;
        j += 100;
    }
    return 0;
}