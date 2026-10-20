#include <stdio.h>
#include <stdint.h>

uint16_t A = 0;
uint16_t B = 0;

void printBinary(uint16_t value) {
    for (int i = 15; i >= 8; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf(" ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

int main(void) {
    unsigned int hexValue;
    int temp = 0;
    int state = -1;

    while (state != 0) {
        state = 0;
        printf("========MENU========\n");
        printf("A:\n");
        printf("HEX: %X\n", A);
        printf("Binary: ");
        printBinary(A);
        printf("B:\n");
        printf("HEX: %X\n", B);
        printf("Binary: ");
        printBinary(B);
        printf("1)  A eingeben (Hex)\n");
        printf("2)  B eingeben (Hex)\n");
        printf("3)  A = A + B\n");
        printf("4)  A = A UND B\n");
        printf("5)  A = A ODER B\n");
        printf("6)  A = A XOR B\n");
        printf("7)  A = NICHT A\n");
        scanf("%i", &state);
        if (state == 1) {
            temp = 0;
            while (temp == 0) {
                printf("Geben sie einen gueltigen HEX Wert fuer A ein: ");
                if (scanf("%x", &hexValue) == 1 && hexValue <= 0xFFFF) {
                    A = (uint16_t)hexValue;
                    temp = 1;
                } else {
                    printf("Ungueltige Eingabe!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                }
            }
        }

        if (state == 2) {
            temp = 0;
            while (temp == 0) {
                printf("Geben sie einen gueltigen HEX Wert fuer B ein: ");
                if (scanf("%x", &hexValue) == 1 && hexValue <= 0xFFFF) {
                    B = (uint16_t)hexValue;
                    temp = 1;
                } else {
                    printf("Ungueltige Eingabe!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                }
            }
        }
        if (state == 3) {
            A = A + B;
        }
        if (state == 4) {
            A = A & B;
        }
        if (state == 5) {
            A = A | B;
        }
        if (state == 6) {
            A = A ^ B;
        }
        if (state == 7) {
            A = (uint16_t)~A;
        }
    }

    return 0;
}