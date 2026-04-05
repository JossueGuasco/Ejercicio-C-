#include <stdio.h>
#include <string.h>


void registrarProducto(int *id, char nombre[], int *stock, float *precio) {
    printf("=== REGISTRO DEL PRODUCTO ===\n");

    printf("Ingrese ID: ");
    scanf("%d", id);

    printf("Ingrese nombre del producto: ");
    scanf(" %[^\n]", nombre);

    printf("Ingrese cantidad en stock: ");
    scanf("%d", stock);

    printf("Ingrese precio unitario: ");
    scanf("%f", precio);
}


void venderProducto(int *stock, float precio, float *ganancias) {
    int cantidad;
    printf("Ingrese cantidad a vender: ");
    scanf("%d", &cantidad);

    if (cantidad <= *stock) {
        *stock -= cantidad;
        *ganancias += cantidad * precio;
        printf("Venta realizada con exito.\n");
    } else {
        printf("No hay suficiente stock.\n");
    }
}


void reabastecer(int *stock) {
    int agregar;
    printf("Ingrese cantidad a agregar: ");
    scanf("%d", &agregar);
    *stock += agregar;
    printf("Stock actualizado.\n");
}


void mostrar(int id, int stock, float precio, char nombre[]) {
    printf("\nProducto: %s\n", nombre);
    printf("ID: %d\n", id);
    printf("Stock: %d\n", stock);
    printf("Precio: %.2f\n", precio);
}

int main() {
    int id, stock, op;
    float precio, ganancia = 0;
    char nombre[100];

    registrarProducto(&id, nombre, &stock, &precio);

    do {
        printf("\n1. Vender\n2. Reabastecer\n3. Mostrar\n4. Ganancia\n5. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                venderProducto(&stock, precio, &ganancia);
                break;
            case 2:
                reabastecer(&stock);
                break;
            case 3:
                mostrar(id, stock, precio, nombre);
                break;
            case 4:
                printf("Ganancia: %.2f\n", ganancia);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }

    } while(op != 5);

    return 0;
}