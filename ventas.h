#ifndef VENTAS_H
#define VENTAS_H

#include "tipos.h"

void registrarVenta(struct Producto menuLista[], int menuCantidad,
                    struct Venta ventasLista[], int *ventasCantidad);

void imprimirFactura(const struct Venta *v);

const struct Venta* ventaMayorTotal(struct Venta ventasLista[], int ventasCantidad);

void verHistorial(struct Venta ventasLista[], int ventasCantidad);

void verResumenDia(struct Venta ventasLista[], int ventasCantidad);

void guardarVentaEnArchivo(const struct Venta *v);

#endif
