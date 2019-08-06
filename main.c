#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint64_t x;
    uint64_t y;
    char op;
    uint64_t mod;
} HeadPos;


HeadPos heGaveMeGoodHeadPeepinOutWhileTheWindowsTinted() {
    HeadPos h;
    h.x = 0;
    h.y = 0;
    h.op = '\0';
    h.mod = 0;
    return h;
}


int main() {
    HeadPos r_head_pos = heGaveMeGoodHeadPeepinOutWhileTheWindowsTinted();
    HeadPos w_head_pos = heGaveMeGoodHeadPeepinOutWhileTheWindowsTinted();

    FILE* file = fopen("hw.scaf", "r+");
    fclose(file);
}

