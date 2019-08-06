#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint64_t x;
    uint64_t y;
    char op;
    uint64_t mod;
} HeadPos;


HeadPos genHead() {
    HeadPos h = {0, 0, '\0', 0};
    return h;
}


int main() {
    HeadPos r_head_pos = genHead();
    HeadPos w_head_pos = genHead();

    FILE* file = fopen("hw.scaf", "r+");
    fclose(file);
}

