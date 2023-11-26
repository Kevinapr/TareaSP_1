  #include <stdio.h>
  #include <string.h>
  #include "funciones.h"

int cantidad_productos = 0;
Producto productos[MAX_PRODUCTOS]; 
int cantidad_usuarios = 0;
Usuario* usuarioActual = NULL;
#define MAX_USUARIOS 10
Usuario usuarios[MAX_USUARIOS];
int totalVentas = 0;
#define MAX_VENTAS 100
RegistroVenta ventas[MAX_VENTAS];
#define MAX_CARACTERES 100

  void cargarUsuarios() {
      FILE* archivoUsuarios = fopen("usuarios.txt", "r");
      if (archivoUsuarios == NULL) {
          printf("No se pudo abrir el archivo de usuarios.\n");
          return;
      }
  
      while (fscanf(archivoUsuarios, "%s %s %d\n", usuarios[cantidad_usuarios].usuario,
                    usuarios[cantidad_usuarios].clave, &usuarios[cantidad_usuarios].tipo) != EOF) {
          cantidad_usuarios++;
          if (cantidad_usuarios >= MAX_USUARIOS) {
              printf("Se alcanzó el límite máximo de usuarios.\n");
              break;
          }
      }
  
      fclose(archivoUsuarios);
  }
  
  void cargarProductos() {
      FILE* archivoProductos = fopen("productos.txt", "r");
      if (archivoProductos == NULL) {
          printf("No se pudo abrir el archivo de productos.\n");
          return;
      }
  
      while (fscanf(archivoProductos, "%s %s %s %s %f %s %d\n", productos[cantidad_productos].nombre,
                    productos[cantidad_productos].categoria, productos[cantidad_productos].marca,
                    productos[cantidad_productos].codigo, &productos[cantidad_productos].precioCompra,
                    productos[cantidad_productos].bodega, &productos[cantidad_productos].cantidad) != EOF) {
          cantidad_productos++;
          if (cantidad_productos >= MAX_PRODUCTOS) {
              printf("Se alcanzó el límite máximo de productos.\n");
              break;
          }
      }
  
      fclose(archivoProductos);
  }
  
  void cargarVentas(RegistroVenta ventas[], int *totalVentas) {
      FILE* archivoVentas = fopen("ventas.txt", "r");
      if (archivoVentas == NULL) {
          printf("No se pudo abrir el archivo de ventas.\n");
          return;
      }
  
      while (fscanf(archivoVentas, "%s %s %s %f %d\n", ventas[*totalVentas].local,
                    ventas[*totalVentas].vendedor, ventas[*totalVentas].fechaVenta,
                    &ventas[*totalVentas].precioVenta, &ventas[*totalVentas].cantidad) != EOF) {
          (*totalVentas)++;
          if (*totalVentas >= MAX_VENTAS) {
              printf("Se alcanzó el límite máximo de ventas.\n");
              break;
          }
      }
  
      fclose(archivoVentas);
  }
  
  void guardarUsuarios() {
      FILE* archivoUsuarios = fopen("usuarios.txt", "w");
      if (archivoUsuarios == NULL) {
          printf("No se pudo abrir el archivo de usuarios para escritura.\n");
          return;
      }
  
      for (int i = 0; i < cantidad_usuarios; i++) {
          fprintf(archivoUsuarios, "%s %s %d\n", usuarios[i].usuario, usuarios[i].clave, usuarios[i].tipo);
      }
  
      fclose(archivoUsuarios);
  }
  
  void guardarProductos() {
      FILE* archivoProductos = fopen("productos.txt", "w");
      if (archivoProductos == NULL) {
          printf("No se pudo abrir el archivo de productos para escritura.\n");
          return;
      }
  
      for (int i = 0; i < cantidad_productos; i++) {
          fprintf(archivoProductos, "%s %s %s %s %.2f %s %d\n", productos[i].nombre, productos[i].categoria,
                  productos[i].marca, productos[i].codigo, productos[i].precioCompra, productos[i].bodega,
                  productos[i].cantidad);
      }
  
      fclose(archivoProductos);
  }
  
  void guardarVentas(RegistroVenta ventas[], int totalVentas) {
      FILE* archivoVentas = fopen("ventas.txt", "w");
      if (archivoVentas == NULL) {
          printf("No se pudo abrir el archivo de ventas para escritura.\n");
          return;
      }
  
      for (int i = 0; i < totalVentas; i++) {
          fprintf(archivoVentas, "%s %s %s %.2f %d\n", ventas[i].local, ventas[i].vendedor, ventas[i].fechaVenta,
                  ventas[i].precioVenta, ventas[i].cantidad);
      }
  
      fclose(archivoVentas);
  }
  
  void crearActualizarUsuario() {
      char usuario[MAX_CARACTERES];
      char clave[MAX_CARACTERES];
      int tipo;
  
      printf("Ingrese el nombre de usuario: ");
      scanf("%s", usuario);
  
      // Verificar si el usuario ya existe
      for (int i = 0; i < cantidad_usuarios; i++) {
          if (strcmp(usuarios[i].usuario, usuario) == 0) {
              printf("El usuario ya existe. Ingrese una clave para actualizar el usuario: ");
              scanf("%s", usuarios[i].clave);
              printf("Ingrese el nuevo tipo de usuario (0: Administrador, 1: Bodeguero, 2: Vendedor): ");
              scanf("%d", &usuarios[i].tipo);
              printf("Usuario actualizado con éxito.\n");
              guardarUsuarios(); // Actualizar el archivo de usuarios
              return;
          }
      }
  
      // Si el usuario no existe, se crea uno nuevo
      printf("Ingrese la clave para el nuevo usuario: ");
      scanf("%s", clave);
      printf("Ingrese el tipo de usuario (0: Administrador, 1: Bodeguero, 2: Vendedor): ");
      scanf("%d", &tipo);
  
      if (cantidad_usuarios < MAX_USUARIOS) {
          // Agregar el nuevo usuario
          strcpy(usuarios[cantidad_usuarios].usuario, usuario);
          strcpy(usuarios[cantidad_usuarios].clave, clave);
          usuarios[cantidad_usuarios].tipo = tipo;
          cantidad_usuarios++;
  
          printf("Usuario creado con éxito.\n");
          guardarUsuarios(); // Actualizar el archivo de usuarios
      } else {
          printf("Se alcanzó el límite máximo de usuarios.\n");
      }
  }
  
  void crearActualizarProducto() {
      char codigo[MAX_CARACTERES];
      float precioCompra;
      int cantidad;
  
      printf("Ingrese el código del producto: ");
      scanf("%s", codigo);
  
      // Verificar si el producto ya existe
      for (int i = 0; i < cantidad_productos; i++) {
          if (strcmp(productos[i].codigo, codigo) == 0) {
              printf("Ingrese el nuevo precio de compra del producto: ");
              scanf("%f", &productos[i].precioCompra);
              printf("Ingrese la nueva cantidad del producto: ");
              scanf("%d", &productos[i].cantidad);
              printf("Producto actualizado con éxito.\n");
              guardarProductos(); // Actualizar el archivo de productos
              return;
          }
      }
  
      // Si el producto no existe, se crea uno nuevo
      printf("Ingrese el precio de compra del nuevo producto: ");
      scanf("%f", &precioCompra);
      printf("Ingrese la cantidad del nuevo producto: ");
      scanf("%d", &cantidad);
  
      if (cantidad_productos < MAX_PRODUCTOS) {
          // Agregar el nuevo producto
          strcpy(productos[cantidad_productos].codigo, codigo);
          productos[cantidad_productos].precioCompra = precioCompra;
          productos[cantidad_productos].cantidad = cantidad;
          cantidad_productos++;
  
          printf("Producto creado con éxito.\n");
          guardarProductos(); // Actualizar el archivo de productos
      } else {
          printf("Se alcanzó el límite máximo de productos.\n");
      }
  }
  
  void venderProducto(Producto productos[MAX_PRODUCTOS], RegistroVenta ventas[], int *totalVentas) {
      char codigo[MAX_CARACTERES];
      int cantidad;
  
      printf("Ingrese el código del producto a vender: ");
      scanf("%s", codigo);
  
      // Verificar si el producto existe
      for (int i = 0; i < cantidad_productos; i++) {
          if (strcmp(productos[i].codigo, codigo) == 0) {
              printf("Ingrese la cantidad del producto a vender: ");
              scanf("%d", &cantidad);
  
              // Verificamos si la cantidad ingresada es menor o igual a la cantidad en bodega
              if (cantidad <= productos[i].cantidad) {
                  // Actualizamos la cantidad en bodega
                  productos[i].cantidad -= cantidad;
  
                  // Registramos la venta
                  strcpy(ventas[*totalVentas].local, "Local");
                  strcpy(ventas[*totalVentas].vendedor, usuarioActual->usuario);
                  // Puedes obtener la fecha actual y asignarla aquí
                  strcpy(ventas[*totalVentas].fechaVenta, "Fecha");
                  ventas[*totalVentas].precioVenta = productos[i].precioCompra * cantidad;
                  ventas[*totalVentas].cantidad = cantidad;
                  (*totalVentas)++; // Incrementamos el total de ventas
  
                  printf("Venta realizada con éxito.\n");
                  guardarProductos(); // Actualizar el archivo de productos
                  guardarVentas(ventas, *totalVentas); // Actualizar el archivo de ventas
              } else {
                  printf("No hay suficiente cantidad del producto en bodega.\n");
              }
  
              return;
          }
      }
  
      printf("No se encontró el producto.\n");
  }
  