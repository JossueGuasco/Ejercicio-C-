#include <stdio.h>
#include <string.h>
#include "inventario.h" 
 
int main() {
 
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    float precios[MAX_PRODUCTOS];
    int cantidad;
    float total, promedio;
    int indiceCaro, indiceBarato;
 
  
    printf("--- SISTEMA DE INVENTARIO DE TIENDA ---\n\n");
    cantidad = ingresarProductos(nombres, precios);
 
    mostrarInventario(nombres, precios, cantidad);
    total = calcularTotal(precios, cantidad);
    printf("\nPrecio TOTAL del inventario:   $%.2f\n", total);
 
    promedio = calcularPromedio(precios, cantidad);
    printf("Precio PROMEDIO de productos:  $%.2f\n", promedio);
 
    indiceCaro = encontrarMasCaro(precios, cantidad);
    printf("\nProducto MAS CARO:   %s ($%.2f)\n",
           nombres[indiceCaro], precios[indiceCaro]);
    indiceBarato = encontrarMasBarato(precios, cantidad);
    printf("Producto MAS BARATO: %s ($%.2f)\n",
           nombres[indiceBarato], precios[indiceBarato]);
 
    printf("\n--- BUSQUEDA DE PRODUCTO ---\n");
    char busqueda[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a buscar: ");
    fgets(busqueda, MAX_NOMBRE, stdin);
    busqueda[strcspn(busqueda, "\n")] = '\0'; // Quitar el Enter
 
    int resultado = buscarProducto(nombres, cantidad, busqueda);
 
    if (resultado != -1) {
        printf("Producto encontrado: %s -> Precio: $%.2f\n",
               nombres[resultado], precios[resultado]);
    } else {
        printf("El producto '%s' no esta en el inventario.\n", busqueda);
    }
 
    printf("\n--- FIN DEL PROGRAMA ---\n");
    return 0;
}