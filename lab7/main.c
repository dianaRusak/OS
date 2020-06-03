#include <stdio.h>

short isLetter(const char *str) {
    if (((int) str >= 65 && (int) str <= 90)||((int) str >= 97 && (int) str <= 122)) {
        return 1;
    }
    return 0;
}

void changeCase(char *str, size_t n) {
    for (int i = 0; i < n; i++) {
        if (isLetter((const char *) *(str + i))) {
            //делаем сдвиг на символ. После смещаем на 6 бит и делаем XOR
            *(str + i) ^= 1 << 5;
        }
    }
}

int main() {
    char string[] = "chvgBJHJGFGDcvbnjkNBVHGFfcVBNKjhCGbjYFVbnkliHGvbjkg IUYFvug";
    printf("test: %s\n", string);
    changeCase(string, sizeof(string));
    printf("answer: %s\n", string);
}
