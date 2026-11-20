#include <stdio.h>
#include <string.h>
#include "funciones.h"

float validarFloatRango(float a, float b){
    float num;
    int val;
    do{
        val = scanf("%f",&num);
        while((getchar())!='\n');
        if (num < a || num > b || val != 1){
            printf("Error: El valor ingresado es incorrecto\n");
        }
    }while(num < a || num > b || val != 1);
    return num;
}

void leercadena(char *cadena, int n){
    fgets(cadena,n,stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n') cadena[len] = '\0';
}

int buscarIndiceStock(char *buscado, char nombresStock[][30], char nombresUso[][30], int totalStock){
    for (int i = 0; i < totalStock; i++){
        if (strcasecmp(buscado, nombresStock[i]) == 0 || strcasecmp(buscado, nombresUso[i]) == 0){
            return i;
        }
    }
    return -1;
}

void ingresarLimitesJornada(float *tiempoDisp){
    printf("Ingrese los limites de jornada laboral disponible (horas): ");
    *tiempoDisp = validarFloatRango(0.5,24);
    printf("Jornada laboral actualizada correctamente\n");
}

void ingresarStock(char nombresStock[][30], int *cantUnidades, float *cantGramos, 
                   char unidadStock[][15], int totalStock){
    int seguir;
    do{
        printf("\n--- INVENTARIO DE STOCK DISPONIBLE ---\n");
        for (int i = 0; i < totalStock; i++){
            if (strcasecmp(unidadStock[i], "gramos") == 0){
                printf("%2d. %-20s %9.1f %s\n", i + 1, nombresStock[i], cantGramos[i], unidadStock[i]);
            }else{
                printf("%2d. %-20s %9d %s\n", i + 1, nombresStock[i], cantUnidades[i], unidadStock[i]);
            }
        }
        printf("\nIngrese el nombre del producto el cual desea modificar: ");
        char buscado[30];
        leercadena(buscado,30);

        int pos = buscarIndiceStock(buscado, nombresStock, nombresStock, totalStock);
        if (pos != -1){
            printf("Ingrese la nueva cantidad disponible para %s (%s): ", nombresStock[pos], unidadStock[pos]);
            if (strcasecmp(unidadStock[pos], "gramos") == 0){
                cantGramos[pos] = validarFloatRango(0,500000);
            }else{
                cantUnidades[pos] = validarFloatRango(0,500000);
            }
            printf("Stock de %s actualizado correctamente\n", nombresStock[pos]);
        }else{
            printf("Error: Producto no encontrado en la lista de stock\n");
        }

        printf("Desea modificar otro producto del stock 1.Si/2.No: ");
        seguir = validarFloatRango(1,2);
    }while(seguir == 1);
}

void mostrarProductos(int *id, char nombres[][50], int *demanda, 
                      float *tiempo, int *estado, int n, int contP){
    printf("\n%-4s %-30s %8s %10s\n", "ID", "Producto", "Solic.", "Min/Unid");
    for (int i = n; i < contP; i++){
        if (estado[i] != 3){
            printf("%-4d %-30s %8d %10.1f\n", id[i], nombres[i], demanda[i], tiempo[i]);
        }
    }
}

void ingresarDemanda(int *id, char nombres[][50], int *demanda, 
                     float *tiempo, int *estado, int contP){
    int seguir;
    do{
        mostrarProductos(id,nombres,demanda,tiempo,estado,0,contP);
        printf("\nIngrese el nombre del producto que desea modificar la cantidad demandada: ");
        char buscado[50];
        leercadena(buscado,50);

        int pos = -1;
        for (int i = 0; i < contP; i++){
            if (estado[i] != 3 && strcasecmp(buscado, nombres[i]) == 0){
                pos = i;
                break;
            }
        }

        if (pos != -1){
            printf("Ingrese la nueva cantidad demandada para %s: ", nombres[pos]);
            demanda[pos] = validarFloatRango(0,1000);
            printf("Cantidad demandada de %s actualizada correctamente\n", nombres[pos]);
        }else{
            printf("Error: Producto no encontrado\n");
        }

        printf("Desea modificar la cantidad demandada de otro producto 1.Si/2.No: ");
        seguir = validarFloatRango(1,2);
    }while(seguir == 1);
}

int buscarProducto(int *id, char nombres[][50], int *demanda, 
                   float *tiempo, int *estado, int contP){
    printf("Ingrese el nombre del producto: ");
    char nombre[50];
    leercadena(nombre,50);
    for (int i = 0; i < contP; i++){
        if (estado[i] != 3 && strcasecmp(nombre,nombres[i]) == 0){
            mostrarProductos(id,nombres,demanda,tiempo,estado,i,i+1);
            return i;
        }
    }
    printf("Error: Producto no encontrado\n");
    return -1;
}

void editarProducto(int *id, char nombres[][50], int *demanda, 
                    float *tiempo, int *estado, float recetas[][27], int *contP,
                    char nombresStock[][30], char nombresUso[][30], 
                    char unidadStock[][15], int totalStock){
    printf("Seleccione: 1.Modificar producto / 2.Agregar producto / 3.Activar producto inactivo: ");
    int accion = validarFloatRango(1,3);

    if (accion == 1){
        int posicion = buscarProducto(id,nombres,demanda,tiempo,estado,*contP);
        if (posicion == -1) return;

        printf("Editar: 1.Nombre / 2.Cant. Solicitada / 3.Minutos / 4.Recursos / 5.Todo: ");
        int opc = validarFloatRango(1,5);
        if (opc == 1 || opc == 5){
            printf("Nuevo nombre: ");
            leercadena(nombres[posicion],50);
        }
        if (opc == 2 || opc == 5){
            printf("Nueva cantidad de productos solicitado: ");
            demanda[posicion] = validarFloatRango(0,1000);
        }
        if (opc == 3 || opc == 5){
            printf("Nuevo tiempo por unidad (minutos): ");
            tiempo[posicion] = validarFloatRango(1,120);
        }
        if (opc == 4 || opc == 5){
            int seguir;
            do{
                printf("\n--- RECURSOS DE %s ---\n", nombres[posicion]);
                for (int j = 0; j < totalStock; j++){
                    if (recetas[posicion][j] > 0){
                        if (strcasecmp(unidadStock[j], "gramos") == 0){
                            printf(" - %-22s %8.1f gramos\n", nombresUso[j], recetas[posicion][j]);
                        }else{
                            printf(" - %-22s %8d unidades\n", nombresUso[j], (int)recetas[posicion][j]);
                        }
                    }
                }
                printf("Ingrese el nombre del recurso a modificar/agregar: ");
                char recBuscado[30];
                leercadena(recBuscado,30);
                int posRec = buscarIndiceStock(recBuscado, nombresStock, nombresUso, totalStock);
                if (posRec != -1){
                    printf("Nueva cantidad de %s (%s) por unidad (0 para quitar): ",
                           nombresUso[posRec], unidadStock[posRec]);
                    recetas[posicion][posRec] = validarFloatRango(0,5000);
                }else{
                    printf("Error: Recurso no encontrado en el stock\n");
                }
                printf("Ingrese (1) si necesita modificar otro recurso sino ingrese (2): ");
                seguir = validarFloatRango(1,2);
            }while(seguir == 1);
        }
        printf("Producto actualizado correctamente\n");
    }else if (accion == 2){
        if (*contP >= 25){
            printf("Error: Capacidad maxima de productos alcanzada\n");
            return;
        }
        id[*contP] = *contP;
        estado[*contP] = 0;
        for (int j = 0; j < totalStock; j++) recetas[*contP][j] = 0;

        printf("Nombre del nuevo producto: ");
        leercadena(nombres[*contP],50);
        printf("Cantidad de productos solicitado: ");
        demanda[*contP] = validarFloatRango(0,1000);
        printf("Tiempo de preparacion por unidad (minutos): ");
        tiempo[*contP] = validarFloatRango(1,120);

        int otro;
        do{
            printf("Ingrese el nombre del recurso que necesita para la preparacion: ");
            char recBuscado[30];
            leercadena(recBuscado,30);
            int posRec = buscarIndiceStock(recBuscado, nombresStock, nombresUso, totalStock);
            if (posRec != -1){
                printf("Cantidad de %s (%s) por unidad: ", nombresUso[posRec], unidadStock[posRec]);
                recetas[*contP][posRec] += validarFloatRango(0.1,5000);
            }else{
                printf("Error: Recurso no encontrado en el stock\n");
            }
            printf("Ingrese (1) si necesita otro ingrediente sino ingrese (2): ");
            otro = validarFloatRango(1,2);
        }while(otro == 1);

        (*contP)++;
        printf("Producto agregado correctamente\n");
    }else if (accion == 3){
        int hayInactivos = 0;
        printf("\n--- PRODUCTOS INACTIVOS ---\n");
        printf("%-4s %-30s %10s\n", "ID", "Producto", "Min/Unid");
        for (int i = 0; i < *contP; i++){
            if (estado[i] == 3){
                hayInactivos = 1;
                printf("%-4d %-30s %10.1f\n", id[i], nombres[i], tiempo[i]);
            }
        }
        if (hayInactivos == 0){
            printf("No hay productos inactivos para activar\n");
            return;
        }
        printf("\nIngrese el nombre del producto inactivo que desea activar: ");
        char buscado[50];
        leercadena(buscado,50);
        for (int i = 0; i < *contP; i++){
            if (estado[i] == 3 && strcasecmp(buscado, nombres[i]) == 0){
                estado[i] = 0;
                printf("Producto %s activado correctamente\n", nombres[i]);
                return;
            }
        }
        printf("Error: Producto inactivo no encontrado\n");
    }
}

void eliminarProducto(int *id, char nombres[][50], int *demanda, 
                      float *tiempo, int *estado, int contP){
    int posicion = buscarProducto(id,nombres,demanda,tiempo,estado,contP);
    if (posicion == -1) return;

    printf("Desea borrar el producto 1.Si/2.No: ");
    int opc = validarFloatRango(1,2);
    if (opc == 1){
        estado[posicion] = 3;
        demanda[posicion] = 0;
        printf("El producto con el id: %d esta inactivo\n", id[posicion]);
    }
}

void calcularProduccion(int *id, char nombres[][50], int *demanda, 
                        float *tiempo, int *estado, float recetas[][27], int contP, 
                        float tiempoDisp, char nombresUso[][30], 
                        char unidadStock[][15], int *cantUnidades, 
                        float *cantGramos, int *factorConversion, int totalStock){
    int dispU[27], reqU[27] = {0};
    float dispG[27], reqG[27] = {0};
    for (int j = 0; j < totalStock; j++){
        dispU[j] = cantUnidades[j] * factorConversion[j];
        dispG[j] = cantGramos[j];
    }

    float minTotal = 0;
    int hayPedidos = 0;
    char tiempoTxt[25];

    printf("\n--- RESUMEN DE PRODUCCION SOLICITADA ---\n");
    printf("%-4s %-30s %8s %15s\n", "ID", "Producto", "Solic.", "Tiempo Req.");
    for (int i = 0; i < contP; i++){
        if (estado[i] != 3 && demanda[i] > 0){
            hayPedidos = 1;
            float minProd = demanda[i] * tiempo[i];
            minTotal += minProd;

            int hProd = minProd / 60;
            float mProd = minProd - (hProd * 60);
            if (mProd - (int)mProd < 0.01){
                sprintf(tiempoTxt, "%d h %d min", hProd, (int)(mProd + 0.01));
            }else{
                sprintf(tiempoTxt, "%d h %.1f min", hProd, mProd);
            }
            printf("%-4d %-30s %8d %15s\n", id[i], nombres[i], demanda[i], tiempoTxt);

            for (int j = 0; j < totalStock; j++){
                if (recetas[i][j] > 0){
                    if (strcasecmp(unidadStock[j], "gramos") == 0){
                        float gNecesarios = demanda[i] * recetas[i][j];
                        reqG[j] += gNecesarios;
                        dispG[j] -= gNecesarios;
                    }else{
                        int uNecesarias = demanda[i] * (int)recetas[i][j];
                        reqU[j] += uNecesarias;
                        dispU[j] -= uNecesarias;
                    }
                }
            }
        }
    }

    if (hayPedidos == 0){
        printf("No hay productos solicitados (todas las cantidades estan en 0).\n");
        return;
    }

    int faltanRecursos = 0;
    printf("\n--- DESGLOSE DE CONSUMO Y FALTANTES DE RECURSOS ---\n");
    printf("%-22s  %11s  %11s  %11s  %11s\n",
           "Recurso", "Stock Disp.", "Requerido", "Restante", "Faltante");
    for (int j = 0; j < totalStock; j++){
        if (reqU[j] > 0 || reqG[j] > 0){
            if (strcasecmp(unidadStock[j], "gramos") == 0){
                float rest = dispG[j] >= 0 ? dispG[j] : 0;
                float falt = dispG[j] < 0 ? -dispG[j] : 0;
                if (falt > 0) faltanRecursos = 1;
                printf("%-22s  %9.1f g  %9.1f g  %9.1f g  %9.1f g\n",
                       nombresUso[j], cantGramos[j], reqG[j], rest, falt);
            }else{
                int stockInicialU = cantUnidades[j] * factorConversion[j];
                int rest = dispU[j] >= 0 ? dispU[j] : 0;
                int falt = dispU[j] < 0 ? -dispU[j] : 0;
                if (falt > 0) faltanRecursos = 1;
                printf("%-22s  %9d u  %9d u  %9d u  %9d u\n",
                       nombresUso[j], stockInicialU, reqU[j], rest, falt);
            }
        }
    }

    float minDisp = tiempoDisp * 60.0;
    int hReq = minTotal / 60, hDisp = minDisp / 60;
    float mReq = minTotal - (hReq * 60), mDisp = minDisp - (hDisp * 60);

    printf("\nJornada requerida: %d h %.0f min / %d h %.0f min disponibles\n",
           hReq, mReq, hDisp, mDisp);
    if (minTotal <= minDisp && faltanRecursos == 0){
        printf("Resultado: SI es viable cumplir la produccion diaria\n");
    }else{
        printf("Resultado: NO es viable cumplir la produccion diaria\n");
        if (minTotal > minDisp){
            float minFalt = minTotal - minDisp;
            int hFalt = minFalt / 60;
            printf(" -> Faltan %d h %.0f min de jornada\n", hFalt, minFalt - (hFalt * 60));
        }
        if (faltanRecursos == 1){
            printf(" -> Revise la columna Faltante en la tabla superior para reponer stock\n");
        }
    }
}