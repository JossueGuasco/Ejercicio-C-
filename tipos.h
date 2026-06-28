#ifndef TIPOS_H
#define TIPOS_H

#define MAX_PRODUCTOS 50
#define MAX_VENTAS    200
#define MAX_ITEMS     20
#define MAX_NOMBRE    50
#define MAX_FECHA     12
#define MAX_HORA      10

#define IVA 0.12

struct Producto {
    int    id;
    char   nombre[MAX_NOMBRE];
    double precio;
};

struct ItemVenta {
    struct Producto producto;
    int             cantidad;
};

struct Venta {
    int              id;
    char             cliente[MAX_NOMBRE];
    struct ItemVenta items[MAX_ITEMS];
    int              numItems;
    double           subtotal;
    double           iva;
    double           total;
    char             fecha[MAX_FECHA];
    char             hora[MAX_HORA];
};

#endif
