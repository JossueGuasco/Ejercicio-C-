#include "ventas.h"
#include "productos.h"
#include "utilidades.h"
#include <stdio.h>
#include <string.h>

void registrarVenta(struct Producto menuLista[], int menuCantidad,
                    struct Venta ventasLista[], int *ventasCantidad) {

    struct Venta *nuevaVenta;
    struct Producto *productoElegido;
    struct ItemVenta *nuevoItem;
    struct ItemVenta *it;
    struct ItemVenta *finIt;
    int opcion;
    int cantidad;
    int i;
    int yaEsta;
    double subtotal;
    char cliente[MAX_NOMBRE];

    if (menuCantidad == 0) {
        printf("\n  No hay productos en el menu. Agrega productos primero.\n");
        return;
    }

    if (*ventasCantidad >= MAX_VENTAS) {
        printf("\n  Se alcanzo el limite de ventas por sesion.\n");
        return;
    }

    nuevaVenta = &ventasLista[*ventasCantidad];
    nuevaVenta->numItems = 0;

    printf("\n  Nombre del cliente (Enter para 'Cliente general'): ");
    fgets(cliente, MAX_NOMBRE, stdin);

    int len = strlen(cliente);
    if (len > 0 && cliente[len - 1] == '\n') {
        cliente[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        strcpy(nuevaVenta->cliente, "Cliente general");
    } else {
        strcpy(nuevaVenta->cliente, cliente);
    }

    do {
        limpiarPantalla();
        printf("\n  == NUEVA VENTA - Cliente: %s ==\n", nuevaVenta->cliente);
        mostrarProductos(menuLista, menuCantidad);

        if (nuevaVenta->numItems > 0) {
            printf("\n  ORDEN ACTUAL:\n");
            imprimirLinea();
            for (i = 0; i < nuevaVenta->numItems; i++) {
                it = &nuevaVenta->items[i];
                printf("  %-28s x%d  $%.2f\n",
                       it->producto.nombre,
                       it->cantidad,
                       it->producto.precio * it->cantidad);
            }
            imprimirLinea();
        }

        printf("\n  [0] Terminar y cobrar\n");
        opcion = pedirEntero("  ID del producto (0 para cobrar): ", 0, 99999);
        if (opcion == 0) break;

        productoElegido = buscarProductoPorId(menuLista, menuCantidad, opcion);

        if (productoElegido == NULL) {
            printf("\n  No existe ese ID en el menu.\n");
            pausar();
            continue;
        }

        if (nuevaVenta->numItems >= MAX_ITEMS) {
            printf("\n  La orden tiene el maximo de productos distintos.\n");
            pausar();
            continue;
        }

        cantidad = pedirEntero("  Cantidad: ", 1, 99);

        yaEsta = 0;
        for (i = 0; i < nuevaVenta->numItems; i++) {
            if (nuevaVenta->items[i].producto.id == opcion) {
                nuevaVenta->items[i].cantidad += cantidad;
                yaEsta = 1;
                break;
            }
        }

        if (!yaEsta) {
            nuevoItem           = &nuevaVenta->items[nuevaVenta->numItems];
            nuevoItem->producto = *productoElegido;
            nuevoItem->cantidad = cantidad;
            nuevaVenta->numItems++;
        }

    } while (1);

    if (nuevaVenta->numItems == 0) {
        printf("\n  La orden esta vacia. Venta cancelada.\n");
        return;
    }

    subtotal = 0;
    it    = nuevaVenta->items;
    finIt = nuevaVenta->items + nuevaVenta->numItems;

    while (it < finIt) {
        subtotal += it->producto.precio * it->cantidad;
        it++;
    }

    nuevaVenta->subtotal = subtotal;
    nuevaVenta->iva      = subtotal * IVA;
    nuevaVenta->total    = subtotal + nuevaVenta->iva;
    nuevaVenta->id       = (*ventasCantidad) + 1;

    obtenerFecha(nuevaVenta->fecha);
    obtenerHora(nuevaVenta->hora);

    (*ventasCantidad)++;

    guardarVentaEnArchivo(nuevaVenta);
    imprimirFactura(nuevaVenta);
}

void imprimirFactura(const struct Venta *v) {
    const struct ItemVenta *it;
    const struct ItemVenta *fin;

    limpiarPantalla();
    printf("\n");
    imprimirLinea();
    printf("              CAFETERIA\n");
    imprimirLinea();
    printf("  Factura #: %04d\n", v->id);
    printf("  Fecha    : %s\n",   v->fecha);
    printf("  Hora     : %s\n",   v->hora);
    printf("  Cliente  : %s\n",   v->cliente);
    imprimirLinea();
    printf("  %-28s %-6s %10s\n", "Producto", "Cant.", "Subtotal");
    imprimirLinea();

    it  = v->items;
    fin = v->items + v->numItems;

    while (it < fin) {
        printf("  %-28s %-6d $%8.2f\n",
               it->producto.nombre,
               it->cantidad,
               it->producto.precio * it->cantidad);
        it++;
    }

    imprimirLinea();
    printf("  %40s $%.2f\n", "Subtotal:", v->subtotal);
    printf("  %40s $%.2f\n", "IVA 12%: ", v->iva);
    imprimirLinea();
    printf("  %40s $%.2f\n", "TOTAL:   ", v->total);
    imprimirLinea();
    printf("           Gracias por su visita!\n");
    imprimirLinea();
}

const struct Venta* ventaMayorTotal(struct Venta ventasLista[], int ventasCantidad) {
    const struct Venta *mayor;
    int i;

    if (ventasCantidad == 0) return NULL;

    mayor = &ventasLista[0];

    for (i = 1; i < ventasCantidad; i++) {
        if (ventasLista[i].total > mayor->total) {
            mayor = &ventasLista[i];
        }
    }

    return mayor;
}

void verHistorial(struct Venta ventasLista[], int ventasCantidad) {
    struct Venta *ptr;
    struct Venta *fin;
    const struct Venta *mayor;

    if (ventasCantidad == 0) {
        printf("\n  No hay ventas registradas en esta sesion.\n");
        return;
    }

    printf("\n");
    imprimirLinea();
    printf("  %-6s %-12s %-10s %-18s %8s\n", "#", "Fecha", "Hora", "Cliente", "Total");
    imprimirLinea();

    ptr = ventasLista;
    fin = ventasLista + ventasCantidad;

    while (ptr < fin) {
        printf("  %-6d %-12s %-10s %-18.16s $%7.2f\n",
               ptr->id,
               ptr->fecha,
               ptr->hora,
               ptr->cliente,
               ptr->total);
        ptr++;
    }

    imprimirLinea();
    printf("  Total de ventas en sesion: %d\n", ventasCantidad);

    mayor = ventaMayorTotal(ventasLista, ventasCantidad);
    if (mayor != NULL) {
        printf("  Venta mas alta: #%d - %s - $%.2f\n",
               mayor->id, mayor->cliente, mayor->total);
    }
}

void verResumenDia(struct Venta ventasLista[], int ventasCantidad) {
    char hoy[MAX_FECHA];
    int totalVentas;
    double totalIngresos;
    struct Venta *ptr;
    struct Venta *fin;
    struct ItemVenta *it;
    struct ItemVenta *finIt;

    char   nombres[MAX_PRODUCTOS * 2][MAX_NOMBRE];
    int    cantidades[MAX_PRODUCTOS * 2];
    int    numProductos;
    int    encontrado;
    int    i, j, k;
    int    tmpCant;
    char   tmpNom[MAX_NOMBRE];

    obtenerFecha(hoy);

    totalVentas   = 0;
    totalIngresos = 0.0;
    numProductos  = 0;

    ptr = ventasLista;
    fin = ventasLista + ventasCantidad;

    while (ptr < fin) {
        if (strcmp(ptr->fecha, hoy) == 0) {
            totalVentas++;
            totalIngresos += ptr->total;
        }
        ptr++;
    }

    printf("\n");
    imprimirLinea();
    printf("  RESUMEN DEL DIA: %s\n", hoy);
    imprimirLinea();

    if (totalVentas == 0) {
        printf("  No hay ventas registradas hoy.\n");
        return;
    }

    printf("  Ventas realizadas : %d\n", totalVentas);
    printf("  Ingresos totales  : $%.2f\n", totalIngresos);
    printf("  Ticket promedio   : $%.2f\n", totalIngresos / totalVentas);

    ptr = ventasLista;
    while (ptr < fin) {
        if (strcmp(ptr->fecha, hoy) == 0) {
            it    = ptr->items;
            finIt = ptr->items + ptr->numItems;

            while (it < finIt) {
                encontrado = 0;
                for (k = 0; k < numProductos; k++) {
                    if (strcmp(nombres[k], it->producto.nombre) == 0) {
                        cantidades[k] += it->cantidad;
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    strcpy(nombres[numProductos], it->producto.nombre);
                    cantidades[numProductos] = it->cantidad;
                    numProductos++;
                }
                it++;
            }
        }
        ptr++;
    }

    for (i = 0; i < numProductos - 1; i++) {
        for (j = 0; j < numProductos - i - 1; j++) {
            if (cantidades[j] < cantidades[j + 1]) {
                tmpCant        = cantidades[j];
                cantidades[j]  = cantidades[j + 1];
                cantidades[j + 1] = tmpCant;

                strcpy(tmpNom,      nombres[j]);
                strcpy(nombres[j],  nombres[j + 1]);
                strcpy(nombres[j + 1], tmpNom);
            }
        }
    }

    printf("\n  PRODUCTOS MAS VENDIDOS:\n");
    imprimirLinea();
    printf("  %-30s %10s\n", "Producto", "Unidades");
    imprimirLinea();

    for (i = 0; i < numProductos; i++) {
        printf("  %-30s %8d\n", nombres[i], cantidades[i]);
    }
    imprimirLinea();
}

void guardarVentaEnArchivo(const struct Venta *v) {
    FILE *archivo;
    const struct ItemVenta *it;
    const struct ItemVenta *fin;

    archivo = fopen("ventas.txt", "a");

    if (archivo == NULL) {
        printf("  Advertencia: no se pudo guardar la venta.\n");
        return;
    }

    fprintf(archivo, "---\n");
    fprintf(archivo, "Factura #%d | %s %s | %s\n",
            v->id, v->fecha, v->hora, v->cliente);

    it  = v->items;
    fin = v->items + v->numItems;

    while (it < fin) {
        fprintf(archivo, "  %s x%d = $%.2f\n",
                it->producto.nombre,
                it->cantidad,
                it->producto.precio * it->cantidad);
        it++;
    }

    fprintf(archivo, "Subtotal: $%.2f | IVA: $%.2f | Total: $%.2f\n",
            v->subtotal, v->iva, v->total);

    fclose(archivo);
}
