#include <stdio.h>
#include <stdlib.h>
#include "temperatur.h"

void temperatur_init(SPEICHER_t *speicher, uint8_t liste) {
    pthread_mutex_init(&speicher->sperre, NULL);
    pthread_cond_init(&speicher->aenderung, NULL);
    speicher->voll = 0;
    speicher->fertig = 0;
    speicher->liste = liste;
    speicher->anzahl = 0;
    speicher->kopf = NULL;
    speicher->ende = NULL;
}

void temperatur_senden(SPEICHER_t *speicher, TEMPERATUR_t messwert) {
    pthread_mutex_lock(&speicher->sperre);
    while (speicher->voll) {
        pthread_cond_wait(&speicher->aenderung, &speicher->sperre);
    }
    speicher->messwert = messwert;
    speicher->voll = 1;
    pthread_cond_broadcast(&speicher->aenderung);
    pthread_mutex_unlock(&speicher->sperre);
}

void temperatur_schliessen(SPEICHER_t *speicher) {
    pthread_mutex_lock(&speicher->sperre);
    speicher->fertig = 1;
    pthread_cond_broadcast(&speicher->aenderung);
    pthread_mutex_unlock(&speicher->sperre);
}

void *temperatur_thread(void *arg) {
    SPEICHER_t *speicher = arg;
    while (1) {
        pthread_mutex_lock(&speicher->sperre);
        while (!speicher->voll && !speicher->fertig) {
            pthread_cond_wait(&speicher->aenderung, &speicher->sperre);
        }
        if (!speicher->voll) {
            pthread_mutex_unlock(&speicher->sperre);
            break;
        }
        TEMPERATUR_t messwert = speicher->messwert;
        speicher->voll = 0;
        pthread_cond_broadcast(&speicher->aenderung);
        pthread_mutex_unlock(&speicher->sperre);

        messwert.next = NULL;
        if (speicher->liste) {
            TEMPERATUR_t *neu = malloc(sizeof(TEMPERATUR_t));
            if (neu == NULL) {
                perror("malloc");
                exit(1);
            }
            *neu = messwert;
            if (speicher->ende == NULL) {
                speicher->kopf = neu;
            } else {
                speicher->ende->next = neu;
            }
            speicher->ende = neu;
        } else {
            speicher->feld[speicher->anzahl] = messwert;
        }
        speicher->anzahl++;
    }
    return NULL;
}

static void temperatur_zeile(const TEMPERATUR_t *temperatur) {
    char zeile[128];
    snprintf(zeile, sizeof(zeile), "%s;%.1f;%.2f;%.3f;%.3f",
            temperatur->regler, temperatur->zeit, temperatur->soll, temperatur->ist, temperatur->stell);
    for (char *zeichen = zeile; *zeichen != '\0'; zeichen++) {
        if (*zeichen == '.') {
            *zeichen = ',';
        }
    }
    printf("%s\n", zeile);
}

void temperatur_ausgabe(const SPEICHER_t *speicher) {
    if (speicher->liste) {
        for (const TEMPERATUR_t *aktuell = speicher->kopf; aktuell != NULL; aktuell = aktuell->next) {
            temperatur_zeile(aktuell);
        }
    } else {
        for (uint32_t i = 0; i < speicher->anzahl; i++) {
            temperatur_zeile(&speicher->feld[i]);
        }
    }
}

void temperatur_frei(SPEICHER_t *speicher) {
    TEMPERATUR_t *aktuell = speicher->kopf;
    while (aktuell != NULL) {
        TEMPERATUR_t *naechster = aktuell->next;
        free(aktuell);
        aktuell = naechster;
    }
    pthread_mutex_destroy(&speicher->sperre);
    pthread_cond_destroy(&speicher->aenderung);
}
