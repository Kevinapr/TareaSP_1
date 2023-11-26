#include <stdio.h>
#include "funciones.h"
#include <string.h>
int main() {
    int opcion;
    int totalVentas = 0;

    
    #define MAX_VENTAS 100 
    RegistroVenta ventas[MAX_VENTAS];
    Usuario* usuarioActual = NULL;  // Define usuarioActual
    Producto productos[100];

    // Se inicializan las estructuras desde archivos
    void cargarUsuarios();
    void cargarProductos();
    void cargarVentas(*ventas, totalVentas);

    // Mostrar menú
    do {
        printf("------------- Menú principal -----------\n");
        printf("1. Registrar usuario\n");
        printf("2. Registrar producto\n");
        printf("3. Vender producto\n");
        printf("4. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (usuarioActual && usuarioActual->tipo == ADMINISTRADOR) {
                    void crearActualizarUsuario();
                } else {
                    printf("Permiso denegado. Solo el administrador puede realizar esta acción.\n");
                }
                break;
            case 2:
                if (usuarioActual && usuarioActual->tipo == BODEGUERO) {
                    void crearActualizarProducto();
                } else {
                    printf("Permiso denegado. Solo el bodeguero puede realizar esta acción.\n");
                }
                break;
            case 3:
                if (usuarioActual && usuarioActual->tipo == VENDEDOR) {
                    venderProducto(productos, ventas, &totalVentas);
                } else {
                    printf("Permiso denegado. Solo el vendedor puede realizar esta acción.\n");
                }
                break;
            case 4:
                // Guardar datos en archivos antes de salir
                guardarUsuarios();
                guardarProductos();
                guardarVentas(ventas, totalVentas);
                // Salir del programa
                printf("¡Hasta luego!\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}
