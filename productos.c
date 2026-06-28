#include "productos.h"
#include "utilidades.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cargarProductosIniciales(struct Producto lista[], int *cantidad) {
    cargarProductos(lista, cantidad);

    if (*cantidad == 0) {
        lista[0].id = 1; strcpy(lista[0].nombre, "Cafe americano");    lista[0].precio = 2.50;
        lista[1].id = 2; strcpy(lista[1].nombre, "Cappuccino");         lista[1].precio = 3.20;
        lista[2].id = 3; strcpy(lista[2].nombre, "Latte");              lista[2].precio = 3.50;
        lista[3].id = 4; strcpy(lista[3].nombre, "Chocolate caliente"); lista[3].precio = 3.00;
        lista[4].id = 5; strcpy(lista[4].nombre, "Jugo de naranja");    lista[4].precio = 2.80;
        lista[5].id = 6; strcpy(lista[5].nombre, "Agua");               lista[5].precio = 1.00;
        lista[6].id = 7; strcpy(lista[6].nombre, "Sandwich");           lista[6].precio = 4.50;
        lista[7].id = 8; strcpy(lista[7].nombre, "Croissant");          lista[7].precio = 2.20;
        lista[8].id = 9; strcpy(lista[8].nombre, "Muffin");             lista[8].precio = 2.00;
        *cantidad = 9;
    }
}

void mostrarProductos(struct Producto lista[], int cantidad) {
    int i;

    if (cantidad == 0) {
        printf("\n  El menu esta vacio. Agrega productos primero.\n");
        return;
    }

    printf("\n");
    imprimirLinea();
    printf("  %-5s %-28s %10s\n", "ID", "Producto", "Precio");
    imprimirLinea();

    for (i = 0; i < cantidad; i++) {
        printf("  %-5d %-28s %9.2f\n",
               lista[i].id,
               lista[i].nombre,
               lista[i].precio);
    }
    imprimirLinea();
}

struct Producto* buscarProductoPorId(struct Producto lista[], int cantidad, int id) {
    int i;
    for (i = 0; i < cantidad; i++) {
        if (lista[i].id == id) {
            return &lista[i];
        }
    }
    return NULL;
}

void agregarProducto(struct Producto lista[], int *cantidad) {
    struct Producto *nuevo;
    int nuevoId;
    int i;

    if (*cantidad >= MAX_PRODUCTOS) {
        printf("\n  No puedes agregar mas productos (limite: %d).\n", MAX_PRODUCTOS);
        return;
    }

    printf("\n  -- AGREGAR PRODUCTO --\n");

    nuevoId = 1;
    for (i = 0; i < *cantidad; i++) {
        if (lista[i].id >= nuevoId) {
            nuevoId = lista[i].id + 1;
        }
    }

    nuevo = &lista[*cantidad];
    nuevo->id = nuevoId;

    pedirTexto("  Nombre del producto: ", nuevo->nombre, MAX_NOMBRE);
    nuevo->precio = pedirDecimal("  Precio: $", 0.01, 9999.99);

    (*cantidad)++;

    guardarProductos(lista, *cantidad);
    printf("\n  Producto \"%s\" agregado con ID %d.\n", nuevo->nombre, nuevoId);
}

void editarProducto(struct Producto lista[], int cantidad) {
    struct Producto *p;
    int id;
    char nuevoNombre[MAX_NOMBRE];
    double nuevoPrecio;

    if (cantidad == 0) {
        printf("\n  No hay productos para editar.\n");
        return;
    }

    mostrarProductos(lista, cantidad);

    id = pedirEntero("  ID del producto a editar: ", 1, 99999);
    p  = buscarProductoPorId(lista, cantidad, id);

    if (p == NULL) {
        printf("\n  No existe un producto con ID %d.\n", id);
        return;
    }

    printf("\n  Editando: %s - $%.2f\n", p->nombre, p->precio);
    printf("  (Presiona Enter sin escribir nada para no cambiar el nombre)\n\n");

    printf("  Nuevo nombre (%s): ", p->nombre);
    fgets(nuevoNombre, MAX_NOMBRE, stdin);

    int len = strlen(nuevoNombre);
    if (len > 0 && nuevoNombre[len - 1] == '\n') {
        nuevoNombre[len - 1] = '\0';
        len--;
    }

    if (len > 0) {
        strcpy(p->nombre, nuevoNombre);
    }

    nuevoPrecio = pedirDecimal("  Nuevo precio: $", 0.01, 9999.99);
    p->precio = nuevoPrecio;

    guardarProductos(lista, cantidad);
    printf("\n  Producto actualizado.\n");
}

void eliminarProducto(struct Producto lista[], int *cantidad) {
    struct Producto *p;
    int id;
    int pos;
    int i;

    if (*cantidad == 0) {
        printf("\n  No hay productos para eliminar.\n");
        return;
    }

    mostrarProductos(lista, *cantidad);

    id = pedirEntero("  ID del producto a eliminar: ", 1, 99999);
    p  = buscarProductoPorId(lista, *cantidad, id);

    if (p == NULL) {
        printf("\n  No existe un producto con ID %d.\n", id);
        return;
    }

    printf("\n  Producto: %s - $%.2f\n", p->nombre, p->precio);

    if (!pedirSiNo("  Seguro que deseas eliminarlo?")) {
        printf("  Eliminacion cancelada.\n");
        return;
    }

    pos = p - lista;

    for (i = pos; i < *cantidad - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*cantidad)--;

    guardarProductos(lista, *cantidad);
    printf("\n  Producto eliminado.\n");
}

void guardarProductos(struct Producto lista[], int cantidad) {
    FILE *archivo;
    struct Producto *ptr;
    struct Producto *fin;

    archivo = fopen("menu.txt", "w");

    if (archivo == NULL) {
        printf("  Advertencia: no se pudo guardar el menu.\n");
        return;
    }

    ptr = lista;
    fin = lista + cantidad;

    while (ptr < fin) {
        fprintf(archivo, "%d|%s|%.2f\n", ptr->id, ptr->nombre, ptr->precio);
        ptr++;
    }

    fclose(archivo);
}

void cargarProductos(struct Producto lista[], int *cantidad) {
    FILE *archivo;
    struct Producto *p;
    char linea[100];
    char *tok;

    archivo = fopen("menu.txt", "r");
    *cantidad = 0;

    if (archivo == NULL) {
        return;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL && *cantidad < MAX_PRODUCTOS) {
        int len = strlen(linea);
        if (len > 0 && linea[len - 1] == '\n') linea[len - 1] = '\0';

        p = &lista[*cantidad];

        tok = strtok(linea, "|");
        if (tok == NULL) continue;
        p->id = atoi(tok);

        tok = strtok(NULL, "|");
        if (tok == NULL) continue;
        strcpy(p->nombre, tok);

        tok = strtok(NULL, "|");
        if (tok == NULL) continue;
        p->precio = atof(tok);

        (*cantidad)++;
    }

    fclose(archivo);
}

void menuProductos(struct Producto lista[], int *cantidad) {
    int opcion;

    do {
        limpiarPantalla();
        printf("\n  ============================================\n");
        printf("              ADMINISTRAR MENU\n");
        printf("  ============================================\n");
        printf("  1. Ver productos\n");
        printf("  2. Agregar producto\n");
        printf("  3. Editar producto\n");
        printf("  4. Eliminar producto\n");
        printf("  0. Volver al menu principal\n\n");

        opcion = pedirEntero("  Opcion: ", 0, 4);

        switch (opcion) {
            case 1:
                mostrarProductos(lista, *cantidad);
                pausar();
                break;
            case 2:
                agregarProducto(lista, cantidad);
                pausar();
                break;
            case 3:
                editarProducto(lista, *cantidad);
                pausar();
                break;
            case 4:
                eliminarProducto(lista, cantidad);
                pausar();
                break;
        }
    } while (opcion != 0);
}
