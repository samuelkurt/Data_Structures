#ifndef TEMPERATUR_H
#define TEMPERATUR_H

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#define ANZAHL_SCHRITTE 360
#define CSV_KOPF "Regler;Zeit_s;Soll_C;Ist_C;Heizung_an;Stell"

typedef struct TEMPERATUR_t {
    const char *regler;
    double zeit;
    double soll;
    double ist;
    uint8_t an;
    double stell;
    struct TEMPERATUR_t *next;
} TEMPERATUR_t;

typedef struct SPEICHER_t {
    pthread_mutex_t sperre;
    pthread_cond_t aenderung;
    TEMPERATUR_t messwert;
    uint8_t voll;
    uint8_t fertig;
    uint8_t liste;
    uint32_t anzahl;
    TEMPERATUR_t feld[ANZAHL_SCHRITTE];
    TEMPERATUR_t *kopf;
    TEMPERATUR_t *ende;
} SPEICHER_t;

void temperatur_init(SPEICHER_t *speicher, uint8_t liste);
void temperatur_senden(SPEICHER_t *speicher, TEMPERATUR_t messwert);
void temperatur_schliessen(SPEICHER_t *speicher);
void *temperatur_thread(void *arg);
void temperatur_ausgabe(const SPEICHER_t *speicher, FILE *datei);
void temperatur_frei(SPEICHER_t *speicher);

#endif
