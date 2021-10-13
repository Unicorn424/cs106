#include "cantor.h"

void cantorSet(GWindow& window, int x, int y, int length, int levels) {
    if (levels == 1) {
        window.drawLine(x, y, x + length, y);
    }
    else {
        window.drawLine(x, y, x + length, y);
        cantorSet(window, x, y + 20, length/3, levels - 1);
        cantorSet(window, x + 2*length/3, y + 20, length/3, levels - 1);
    }
}


int main_cantor() {
    // cantor set:
    GWindow window(800, 600);
    window.setWindowTitle("cantorSet");

    cantorSet(window, 50, 50, 700, 7);

    return 0;
}
