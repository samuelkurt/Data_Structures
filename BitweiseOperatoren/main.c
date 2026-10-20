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

void printA(void) {
    printf("A  Hex: %04X\n", (unsigned int)A);
    printf("   Bits: ");
    printBinary(A);
}

int main(void) {
    unsigned int hexValue;
    int temp = 0;
    int state = -1;
    int bit = 0;

    while (state != 0) {
        printf("========MENU========\n");
        printf("A:\n");
        printf("HEX: %04X\n", (unsigned int)A);
        printf("Binary: ");
        printBinary(A);
        printf("B:\n");
        printf("HEX: %04X\n", (unsigned int)B);
        printf("Binary: ");
        printBinary(B);
        printf("1)  A eingeben (Hex)\n");
        printf("2)  B eingeben (Hex)\n");
        printf("3)  A = A + B\n");
        printf("4)  A = A UND B\n");
        printf("5)  A = A ODER B\n");
        printf("6)  A = A XOR B\n");
        printf("7)  A = NICHT A\n");
        printf("8)  A um B Stellen nach links schieben\n");
        printf("9)  A um B Stellen nach rechts schieben\n");
        printf("10)  Ein Bit in A setzen\n");
        printf("11)  Ein Bit in A löschen\n");
        printf("12)  Ein Bit in A umschalten\n");
        printf("13)  Ein Bit in A prüfen\n");
        printf("0)  Programm beenden\n");
        if (scanf("%i", &state) != 1) {
            printf("Ungueltige Eingabe!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        if (state < 0 || state > 13) {
            printf("Ungueltiger Menuepunkt!\n");
            continue;
        }
        if (state == 1) {
            temp = 0;
            while (temp == 0) {
                printf("Geben sie einen gueltigen HEX Wert fuer A ein: ");
                if (scanf("%x", &hexValue) == 1 && hexValue <= 0xFFFF) {
                    A = (uint16_t)hexValue;
                    printA();
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
            printA();
        }
        if (state == 4) {
            A = A & B;
            printA();
        }
        if (state == 5) {
            A = A | B;
            printA();
        }
        if (state == 6) {
            A = A ^ B;
            printA();
        }
        if (state == 7) {
            A = (uint16_t)~A;
            printA();
        }
        if (state == 8) {
            if (B < 16) {
                A = A << B;
                printA();
            }
            else {
                printf("B zu groß\n");
            }

        }
        if (state == 9) {
            if (B < 16) {
                A = A >> B;
                printA();
            }
            else {
                printf("B zu groß\n");
            }
        }
        if (state == 10) {
            printf("Welche Bitnummer soll auf 1 gesetzt werden (0-15)? ");
            if (scanf("%d", &bit) == 1 && bit >= 0 && bit <= 15) {
                A = A | (uint16_t)(1u << bit);
                printA();
            }
            else {
                printf("Ungueltige Bitnummer!\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
            }
        }
        if (state == 11) {
            printf("Welche Bitnummer soll auf 0 gesetzt werden (0-15)? ");
            if (scanf("%d", &bit) == 1 && bit >= 0 && bit <= 15) {
                A = (uint16_t)(A & ~(1u << bit));
                printA();
            }
            else {
                printf("Ungueltige Bitnummer!\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
            }
        }
        if (state == 12) {
            printf("Welche Bitnummer soll umgeschaltet werden (0-15)? ");
            if (scanf("%d", &bit) == 1 && bit >= 0 && bit <= 15) {
                A = A ^ (uint16_t)(1u << bit);
                printA();
            }
            else {
                printf("Ungueltige Bitnummer!\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
            }
        }
        if (state == 13) {
            printf("Welche Bitnummer soll geprueft werden (0-15)? ");
            if (scanf("%d", &bit) == 1 && bit >= 0 && bit <= 15) {
                if (A & (uint16_t)(1u << bit)) {
                    printf("Bit %d ist 1.\n", bit);
                }
                else {
                    printf("Bit %d ist 0.\n", bit);
                }
            }
            else {
                printf("Ungueltige Bitnummer!\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
            }
        }
    }

    return 0;
}