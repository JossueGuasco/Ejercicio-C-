#include "tipos.h"
#include "utilidades.h"
#include "productos.h"
#include "ventas.h"
#include <stdio.h>

int main(void) {

    struct Producto menuLista[MAX_PRODUCTOS];
    int             menuCantidad = 0;

    struct Venta ventasLista[MAX_VENTAS];
    int          ventasCantidad = 0;

    int opcion;

    cargarProductosIniciales(menuLista, &menuCantidad);

    do {
        limpiarPantalla();
        printf("\n  ============================================\n");
        printf("         CAFETERIA - SISTEMA DE CAJA\n");
        printf("  ============================================\n");
        printf("  1. Nueva venta\n");
        printf("  2. Resumen del dia\n");
        printf("  3. Historial de ventas\n");
        printf("  4. Administrar menu de productos\n");
        printf("  0. Salir\n");
        printf("  ============================================\n\n");

        opcion = pedirEntero("  Opcion: ", 0, 4);

        switch (opcion) {
            case 1:
                registrarVenta(menuLista, menuCantidad, ventasLista, &ventasCantidad);
                pausar();
                break;
            case 2:
                verResumenDia(ventasLista, ventasCantidad);
                pausar();
                break;
            case 3:
                verHistorial(ventasLista, ventasCantidad);
                pausar();
                break;
            case 4:
                menuProductos(menuLista, &menuCantidad);
                break;
        }

    } while (opcion != 0);

    printf("\n  Hasta luego!\n\n");
    return 0;
}
