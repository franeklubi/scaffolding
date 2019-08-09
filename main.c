#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint64_t x;
    uint64_t y;
    char op;
    uint64_t mod;
} Head;


Head genHead() {
    Head h = {0, 0, '\0', 0};
    return h;
}

uint32_t getSize(FILE* file) {
    fseek(file, 0L, SEEK_END);
    return ftell(file);
}

int main() {
    Head r_head_pos = genHead();
    Head w_head_pos = genHead();

    FILE* file = fopen("hw.scaf", "r");

        int32_t file_len = getSize(file);

    fclose(file);
}
