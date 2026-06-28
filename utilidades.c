#include "utilidades.h"
#include "tipos.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

int pedirEntero(const char *mensaje, int min, int max) {
    int valor;
    int leido;
    char basura[100];

    while (1) {
        printf("%s", mensaje);
        leido = scanf("%d", &valor);

        if (leido == 1 && valor >= min && valor <= max) {
            while (getchar() != '\n');
            return valor;
        }

        while (getchar() != '\n');

        if (leido != 1) {
            printf("  Error: escribe solo numeros.\n");
        } else {
            printf("  Error: ingresa un numero entre %d y %d.\n", min, max);
        }
        (void)basura;
    }
}

double pedirDecimal(const char *mensaje, double min, double max) {
    double valor;
    int leido;

    while (1) {
        printf("%s", mensaje);
        leido = scanf("%lf", &valor);

        if (leido == 1 && valor >= min && valor <= max) {
            while (getchar() != '\n');
            return valor;
        }

        while (getchar() != '\n');

        if (leido != 1) {
            printf("  Error: escribe un numero (usa punto para decimales).\n");
        } else {
            printf("  Error: el valor debe estar entre %.2f y %.2f.\n", min, max);
        }
    }
}

void pedirTexto(const char *mensaje, char *destino, int maxLen) {
    while (1) {
        printf("%s", mensaje);
        fgets(destino, maxLen, stdin);

        int len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
            len--;
        }

        int soloEspacios = 1;
        int i;
        for (i = 0; i < len; i++) {
            if (destino[i] != ' ') {
                soloEspacios = 0;
                break;
            }
        }

        if (len > 0 && !soloEspacios) {
            return;
        }

        printf("  Error: no puedes dejar esto vacio.\n");
    }
}

int pedirSiNo(const char *mensaje) {
    char respuesta;

    while (1) {
        printf("%s (s/n): ", mensaje);
        scanf(" %c", &respuesta);
        while (getchar() != '\n');

        respuesta = tolower(respuesta);
        if (respuesta == 's') return 1;
        if (respuesta == 'n') return 0;

        printf("  Error: escribe 's' para si o 'n' para no.\n");
    }
}

void imprimirLinea(void) {
    printf("  ------------------------------------------------\n");
}

void limpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(void) {
    printf("\n  Presiona Enter para continuar...");
    while (getchar() != '\n');
}

void obtenerFecha(char *destino) {
    time_t ahora = time(NULL);
    strftime(destino, MAX_FECHA, "%d/%m/%Y", localtime(&ahora));
}

void obtenerHora(char *destino) {
    time_t ahora = time(NULL);
    strftime(destino, MAX_HORA, "%H:%M:%S", localtime(&ahora));
}
