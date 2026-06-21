#include <stdio.h>
#include <string.h>

typedef struct {
    int id, disponible;
    char marca[30], modelo[30], estado[10];
    float precio;
} Vehiculo;

void registrar() {
    Vehiculo v;
    FILE *f = fopen("vehiculos.dat", "ab");
    printf("ID: "); scanf("%d", &v.id);
    printf("Marca: "); scanf("%s", v.marca);
    printf("Modelo: "); scanf("%s", v.modelo);
    printf("Estado (nuevo/usado): "); scanf("%s", v.estado);
    printf("Precio: "); scanf("%f", &v.precio);
    v.disponible = 1;
    fwrite(&v, sizeof(v), 1, f);
    fclose(f);
    printf("Vehiculo registrado.\n");
}

void listar() {
    Vehiculo v;
    FILE *f = fopen("vehiculos.dat", "rb");
    if (!f) { printf("No hay vehiculos.\n"); return; }
    printf("\n--- Disponibles ---\n");
    while (fread(&v, sizeof(v), 1, f) == 1)
        if (v.disponible)
            printf("ID:%d | %s %s (%s) | $%.2f\n", v.id, v.marca, v.modelo, v.estado, v.precio);
    fclose(f);
}

void buscar() {
    Vehiculo v;
    char marca[30], estado[10];
    float pres;
    printf("Marca: "); scanf("%s", marca);
    printf("Estado: "); scanf("%s", estado);
    printf("Presupuesto: "); scanf("%f", &pres);
    FILE *f = fopen("vehiculos.dat", "rb");
    if (!f) { printf("No hay vehiculos.\n"); return; }
    printf("\n--- Resultados ---\n");
    while (fread(&v, sizeof(v), 1, f) == 1)
        if (v.disponible && !strcmp(v.marca, marca) && !strcmp(v.estado, estado) && v.precio <= pres)
            printf("ID:%d | %s %s | $%.2f\n", v.id, v.marca, v.modelo, v.precio);
    fclose(f);
}

void vender() {
    Vehiculo v;
    int id;
    char cliente[40];
    printf("ID a vender: "); scanf("%d", &id);
    FILE *f = fopen("vehiculos.dat", "rb+");
    if (!f) { printf("No hay vehiculos.\n"); return; }
    while (fread(&v, sizeof(v), 1, f) == 1)
        if (v.id == id && v.disponible) {
            v.disponible = 0;
            fseek(f, -(long)sizeof(v), SEEK_CUR);
            fwrite(&v, sizeof(v), 1, f);
            fclose(f);
            printf("Cliente: "); scanf("%s", cliente);
            FILE *fv = fopen("ventas.dat", "ab");
            fprintf(fv, "%s compro ID:%d por $%.2f\n", cliente, v.id, v.precio);
            fclose(fv);
            printf("Venta registrada.\n");
            return;
        }
    fclose(f);
    printf("Vehiculo no disponible.\n");
}

int main() {
    int op;
    do {
        printf("\n=== Ruedas de Oro (SGIC) ===\n");
        printf("1.Registrar 2.Listar 3.Buscar 4.Vender 0.Salir\nOpcion: ");
        scanf("%d", &op);
        if (op == 1) registrar();
        else if (op == 2) listar();
        else if (op == 3) buscar();
        else if (op == 4) vender();
        else if (op != 0) printf("Opcion invalida.\n");
    } while (op != 0);
    return 0;
}
