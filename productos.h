#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include "tipos.h"

void cargarProductosIniciales(struct Producto lista[], int *cantidad);
void mostrarProductos(struct Producto lista[], int cantidad);
struct Producto* buscarProductoPorId(struct Producto lista[], int cantidad, int id);
void agregarProducto(struct Producto lista[], int *cantidad);
void editarProducto(struct Producto lista[], int cantidad);
void eliminarProducto(struct Producto lista[], int *cantidad);
void guardarProductos(struct Producto lista[], int cantidad);
void cargarProductos(struct Producto lista[], int *cantidad);
void menuProductos(struct Producto lista[], int *cantidad);

#endif
