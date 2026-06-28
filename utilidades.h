#ifndef UTILIDADES_H
#define UTILIDADES_H

int  pedirEntero(const char *mensaje, int min, int max);
double pedirDecimal(const char *mensaje, double min, double max);
void pedirTexto(const char *mensaje, char *destino, int maxLen);
int  pedirSiNo(const char *mensaje);
void imprimirLinea(void);
void limpiarPantalla(void);
void pausar(void);
void obtenerFecha(char *destino);
void obtenerHora(char *destino);

#endif
