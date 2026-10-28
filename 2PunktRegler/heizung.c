#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include "temperatur.h"

#define WAERMEKAPAZITAET 5000.0
#define WAERMEVERLUST 8.0
#define MAX_LEISTUNG 400.0
#define AUSSENTEMPERATUR 5.0
#define SOLL 21.0
#define START 10.0
#define SCHRITTWEITE 10.0
#define HYSTERESE 0.5
#define KP 0.5
#define KI 0.002
#define KD 5.0

typedef struct HEIZUNG_t {
    SPEICHER_t *speicher;
    const char *name;
    uint8_t pid;
} HEIZUNG_t;

static void *heizung_thread(void *arg) {
    HEIZUNG_t *heizung = arg;
    double ist = START;
    double integral = 0.0;
    double letzter_fehler = 0.0;
    uint8_t an = 0;
    for (uint32_t i = 0; i < ANZAHL_SCHRITTE; i++) {
        double fehler = SOLL - ist;
        double stell;
        if (heizung->pid) {
            double differenz = 0.0;
            if (i > 0) {
                differenz = (fehler - letzter_fehler) / SCHRITTWEITE;
            }
            letzter_fehler = fehler;
            stell = KP * fehler + KI * integral + KD * differenz;
            if ((stell < 1.0 || fehler < 0) && (stell > 0.0 || fehler > 0)) {
                integral += fehler * SCHRITTWEITE;
                stell = KP * fehler + KI * integral + KD * differenz;
            }
            if (stell > 1.0) {
                stell = 1.0;
            }
            if (stell < 0.0) {
                stell = 0.0;
            }
            an = stell > 0.0;
        } else {
            if (ist < SOLL - HYSTERESE) {
                an = 1;
            } else if (ist > SOLL + HYSTERESE) {
                an = 0;
            }
            stell = an;
        }
        TEMPERATUR_t messwert = {heizung->name, i * SCHRITTWEITE, SOLL, ist, an, stell, NULL};
        temperatur_senden(heizung->speicher, messwert);
        double leistung = stell * MAX_LEISTUNG;
        double verlust = WAERMEVERLUST * (ist - AUSSENTEMPERATUR);
        ist += (leistung - verlust) / WAERMEKAPAZITAET * SCHRITTWEITE;
    }
    temperatur_schliessen(heizung->speicher);
    return NULL;
}

int main(int argc, char *argv[]) {
    const char *namen[2] = {"2-Punkt", "PID"};
    uint8_t liste = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "liste") == 0) {
            liste = 1;
        } else if (strcmp(argv[1], "feld") != 0) {
            fprintf(stderr, "Aufruf: %s [feld|liste]\n", argv[0]);
            return 1;
        }
    }
    printf("%s\n", CSV_KOPF);
    for (uint8_t pid = 0; pid < 2; pid++) {
        SPEICHER_t speicher;
        HEIZUNG_t heizung = {&speicher, namen[pid], pid};
        pthread_t heizung_id;
        pthread_t temperatur_id;
        temperatur_init(&speicher, liste);
        pthread_create(&temperatur_id, NULL, temperatur_thread, &speicher);
        pthread_create(&heizung_id, NULL, heizung_thread, &heizung);
        pthread_join(heizung_id, NULL);
        pthread_join(temperatur_id, NULL);
        temperatur_ausgabe(&speicher, stdout);
        temperatur_frei(&speicher);
    }
    if (fflush(stdout) != 0) {
        perror("stdout");
        return 1;
    }
    return 0;
}
