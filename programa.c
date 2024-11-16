#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTICULOS 15
#define MAX_TICKETS 4
#define ARCHIVO_TICKETS "tickets.txt"

// Estructura para un artículo
typedef struct {
    char nombre[30];
    float precio;
} Articulo;

// Estructura para el detalle de un artículo en un ticket
typedef struct {
    Articulo articulo;
    int cantidad;
} DetalleArticulo;

// Estructura para el ticket
typedef struct {
    int numeroTicket;
    DetalleArticulo articulos[MAX_ARTICULOS];
    int totalArticulos;
    float totalCompra;
} Ticket;

// Lista de artículos disponibles
Articulo listaArticulos[MAX_ARTICULOS] = {
    {"Pantalon", 20}, {"Camisa", 10}, {"Playera", 7}, {"Calcetines", 3},
    {"Ropa interior", 4}, {"Tenis", 50}, {"Zapatos", 55}, {"Pants", 15},
    {"Lentes", 17}, {"Gorra", 25}, {"Sudadera", 30}, {"Chamarra", 38},
    {"Short", 19}, {"Vestido", 35}, {"Bufanda", 7}
};

// Declaración de funciones
void inicializarTicket(Ticket *ticket, int numeroTicket);
void agregarProducto(Ticket *ticket, int indiceArticulo, int cantidad);
void quitarProducto(Ticket *ticket, int indiceArticulo, int cantidad);
void mostrarTicket(const Ticket *ticket);
void guardarTicketArchivo(const Ticket *ticket);
void buscarTicketPorNumero(int numeroTicket);

int main() {
    Ticket tickets[MAX_TICKETS];
    int opcion, numeroTicket, indiceArticulo, cantidad;
    
    // Inicialización de tickets
    for (int i = 0; i < MAX_TICKETS; i++) {
        inicializarTicket(&tickets[i], i + 1);
    }
    
    // Menú principal
    do {
        printf("\nSistema Generador de Tickets de Compras\n");
        printf("1. Agregar producto a un ticket\n");
        printf("2. Quitar producto de un ticket\n");
        printf("3. Mostrar ticket\n");
        printf("4. Buscar ticket por número\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese el número de ticket (1 a %d): ", MAX_TICKETS);
                scanf("%d", &numeroTicket);
                if (numeroTicket >= 1 && numeroTicket <= MAX_TICKETS) {
                    printf("Seleccione el artículo (0 a %d): ", MAX_ARTICULOS - 1);
                    for (int i = 0; i < MAX_ARTICULOS; i++) {
                        printf("%d. %s - $%.2f\n", i, listaArticulos[i].nombre, listaArticulos[i].precio);
                    }
                    scanf("%d", &indiceArticulo);
                    printf("Ingrese la cantidad: ");
                    scanf("%d", &cantidad);
                    agregarProducto(&tickets[numeroTicket - 1], indiceArticulo, cantidad);
                } else {
                    printf("Número de ticket inválido.\n");
                }
                break;
                
            case 2:
                printf("Ingrese el número de ticket (1 a %d): ", MAX_TICKETS);
                scanf("%d", &numeroTicket);
                if (numeroTicket >= 1 && numeroTicket <= MAX_TICKETS) {
                    printf("Seleccione el artículo (0 a %d): ", MAX_ARTICULOS - 1);
                    for (int i = 0; i < MAX_ARTICULOS; i++) {
                        printf("%d. %s - $%.2f\n", i, listaArticulos[i].nombre, listaArticulos[i].precio);
                    }
                    scanf("%d", &indiceArticulo);
                    printf("Ingrese la cantidad a quitar: ");
                    scanf("%d", &cantidad);
                    quitarProducto(&tickets[numeroTicket - 1], indiceArticulo, cantidad);
                } else {
                    printf("Número de ticket inválido.\n");
                }
                break;
                
            case 3:
                printf("Ingrese el número de ticket (1 a %d): ", MAX_TICKETS);
                scanf("%d", &numeroTicket);
                if (numeroTicket >= 1 && numeroTicket <= MAX_TICKETS) {
                    mostrarTicket(&tickets[numeroTicket - 1]);
                } else {
                    printf("Número de ticket inválido.\n");
                }
                break;
                
            case 4:
                printf("Ingrese el número de ticket a buscar: ");
                scanf("%d", &numeroTicket);
                buscarTicketPorNumero(numeroTicket);
                break;
                
            case 5:
                printf("Saliendo del sistema...\n");
                break;
                
            default:
                printf("Opción inválida.\n");
                break;
        }
        
    } while (opcion != 5);
    
    return 0;
}

// Inicializa un ticket
void inicializarTicket(Ticket *ticket, int numeroTicket) {
    ticket->numeroTicket = numeroTicket;
    ticket->totalArticulos = 0;
    ticket->totalCompra = 0.0;
    for (int i = 0; i < MAX_ARTICULOS; i++) {
        ticket->articulos[i].cantidad = 0;
    }
}

// Agrega un producto a un ticket
void agregarProducto(Ticket *ticket, int indiceArticulo, int cantidad) {
    if (indiceArticulo >= 0 && indiceArticulo < MAX_ARTICULOS && cantidad > 0) {
        ticket->articulos[indiceArticulo].articulo = listaArticulos[indiceArticulo];
        ticket->articulos[indiceArticulo].cantidad += cantidad;
        ticket->totalCompra += listaArticulos[indiceArticulo].precio * cantidad;
        ticket->totalArticulos += cantidad;
        printf("Producto agregado correctamente.\n");
    } else {
        printf("Datos incorrectos para agregar producto.\n");
    }
}

// Quita un producto de un ticket
void quitarProducto(Ticket *ticket, int indiceArticulo, int cantidad) {
    if (indiceArticulo >= 0 && indiceArticulo < MAX_ARTICULOS && cantidad > 0 &&
        ticket->articulos[indiceArticulo].cantidad >= cantidad) {
        ticket->articulos[indiceArticulo].cantidad -= cantidad;
        ticket->totalCompra -= listaArticulos[indiceArticulo].precio * cantidad;
        ticket->totalArticulos -= cantidad;
        printf("Producto quitado correctamente.\n");
    } else {
        printf("Datos incorrectos para quitar producto.\n");
    }
}

// Muestra un ticket
void mostrarTicket(const Ticket *ticket) {
    printf("\nTicket #%d\n", ticket->numeroTicket);
    printf("Artículos comprados:\n");
    for (int i = 0; i < MAX_ARTICULOS; i++) {
        if (ticket->articulos[i].cantidad > 0) {
            printf("%s - Cantidad: %d - Total: $%.2f\n", 
                   ticket->articulos[i].articulo.nombre, 
                   ticket->articulos[i].cantidad, 
                   ticket->articulos[i].articulo.precio * ticket->articulos[i].cantidad);
        }
    }
    printf("Total de artículos comprados: %d\n", ticket->totalArticulos);
    printf("Total de compra: $%.2f\n", ticket->totalCompra);
}

// Guarda un ticket en el archivo
void guardarTicketArchivo(const Ticket *ticket) {
    FILE *archivo = fopen(ARCHIVO_TICKETS, "a");
    if (archivo != NULL) {
        fprintf(archivo, "Ticket #%d\n", ticket->numeroTicket);
        fprintf(archivo, "Artículos comprados:\n");
        for (int i = 0; i < MAX_ARTICULOS; i++) {
            if (ticket->articulos[i].cantidad > 0) {
                fprintf(archivo, "%s - Cantidad: %d - Total: $%.2f\n",
                        ticket->articulos[i].articulo.nombre,
                        ticket->articulos[i].cantidad,
                        ticket->articulos[i].articulo.precio * ticket->articulos[i].cantidad);
            }
        }
        fprintf(archivo, "Total de artículos comprados: %d\n", ticket->totalArticulos);
        fprintf(archivo, "Total de compra: $%.2f\n\n", ticket->totalCompra);
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

// Busca un ticket por su número en el archivo
void buscarTicketPorNumero(int numeroTicket) {
    FILE *archivo = fopen(ARCHIVO_TICKETS, "r");
    char linea[100];
    int encontrado = 0;
    
    if (archivo != NULL) {
        while (fgets(linea, sizeof(linea), archivo)) {
            if (strstr(linea, "Ticket") && atoi(&linea[8]) == numeroTicket) {
                encontrado = 1;
                do {
                    printf("%s", linea);
                } while (fgets(linea, sizeof(linea), archivo) && !strstr(linea, "Ticket"));
                break;
            }
        }
        fclose(archivo);
        
        if (!encontrado) {
            printf("Ticket #%d no encontrado.\n", numeroTicket);
        }
    } else {
        printf("Error al abrir el archivo.\n");
    }
}
