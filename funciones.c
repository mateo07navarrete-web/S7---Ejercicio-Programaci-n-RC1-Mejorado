#include <stdio.h>
#include <string.h>
#include "funciones.h"

float validarFloatRango(float a, float b){
    float num; int val; char extra;
    do{
        val = scanf("%f%c", &num, &extra);
        if (val != 2 || extra != '\n') while(getchar() != '\n');
        if (val != 2 || extra != '\n' || num < a || num > b)
            printf("Error: el valor ingresado es incorrecto\n");
    }while(val != 2 || extra != '\n' || num < a || num > b);
    return num;
}

void leercadena(char *cadena, int n){
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n') cadena[len] = '\0';
}

int contieneTexto(char *texto, char *buscado){
    int lenT = strlen(texto), lenB = strlen(buscado);
    if (lenB == 0 || lenB > lenT) return 0;
    for (int i = 0; i <= lenT - lenB; i++){
        int ok = 1;
        for (int j = 0; j < lenB && ok; j++){
            char c1 = texto[i + j] | 32, c2 = buscado[j] | 32;
            if (c1 != c2) ok = 0;
        }
        if (ok) return 1;
    }
    return 0;
}

int buscarIndiceStock(char *buscado, char nombresStock[][30], char nombresUso[][30], int totalStock){
    int hits = 0, idx = -1;
    for (int i = 0; i < totalStock; i++){
        if (strcasecmp(buscado, nombresStock[i]) == 0 || strcasecmp(buscado, nombresUso[i]) == 0) return i;
        if (contieneTexto(nombresStock[i], buscado) || contieneTexto(nombresUso[i], buscado)){
            hits++; idx = i;
        }
    }
    if (hits <= 1) return idx;
    for (int i = 0; i < totalStock; i++)
        if (contieneTexto(nombresStock[i], buscado) || contieneTexto(nombresUso[i], buscado))
            printf("  %d. %s (%s)\n", i + 1, nombresStock[i], nombresUso[i]);
    printf("Ingrese el numero exacto del recurso (1 - %d): ", totalStock);
    int sel = (int)validarFloatRango(1, totalStock) - 1;
    return (contieneTexto(nombresStock[sel], buscado) || contieneTexto(nombresUso[sel], buscado)) ? sel : -1;
}

void gestionarReceta(int pos, float recetas[][27], char nombres[][50], char nombresStock[][30],
                     char nombresUso[][30], char unidadStock[][15], int totalStock){
    int seguir;
    do{
        printf("\n--- RECURSOS DE %s ---\n", nombres[pos]);
        for (int j = 0; j < totalStock; j++)
            if (recetas[pos][j] > 0)
                printf(unidadStock[j][0] == 'g' ? " - %-22s %8.1f gramos\n" : " - %-22s %8.0f unidades\n",
                       nombresUso[j], recetas[pos][j]);

        printf("Ingrese el nombre (o parte) del recurso (0 para quitar al editar): ");
        char recBuscado[30];
        leercadena(recBuscado, 30);
        int posRec = buscarIndiceStock(recBuscado, nombresStock, nombresUso, totalStock);
        if (posRec != -1){
            int modo = 1;
            if (recetas[pos][posRec] > 0){
                printf("Recurso existente. 1.Reemplazar / 2.Sumar: ");
                modo = validarFloatRango(1, 2);
            }
            printf("Cantidad de %s (%s) por unidad: ", nombresUso[posRec], unidadStock[posRec]);
            float cant = validarFloatRango(0, 5000);
            if (unidadStock[posRec][0] != 'g') cant = (int)cant;
            recetas[pos][posRec] = (modo == 1) ? cant : recetas[pos][posRec] + cant;
        }else{
            printf("Error: Recurso no encontrado en el stock\n");
        }
        printf("Desea ingresar/modificar otro recurso 1.Si/2.No: ");
        seguir = validarFloatRango(1, 2);
    }while(seguir == 1);
}

void ingresarLimitesJornada(float *tiempoDisp){
    printf("Ingrese los limites de jornada laboral disponible (horas): ");
    *tiempoDisp = validarFloatRango(0.5, 24);
    printf("Jornada laboral actualizada correctamente\n");
}

void ingresarStock(char nombresStock[][30], int *cantUnidades, float *cantGramos, 
                   char unidadStock[][15], int totalStock){
    int seguir;
    do{
        printf("\n--- INVENTARIO DE STOCK DISPONIBLE ---\n");
        for (int i = 0; i < totalStock; i++)
            printf(unidadStock[i][0] == 'g' ? "%2d. %-20s %9.1f %s\n" : "%2d. %-20s %9.0f %s\n",
                   i + 1, nombresStock[i], unidadStock[i][0] == 'g' ? cantGramos[i] : (float)cantUnidades[i], unidadStock[i]);

        printf("\nIngrese el nombre (o parte) del recurso a modificar: ");
        char buscado[30];
        leercadena(buscado, 30);
        int pos = buscarIndiceStock(buscado, nombresStock, nombresStock, totalStock);
        if (pos != -1){
            printf("Nueva cantidad disponible para %s (%s): ", nombresStock[pos], unidadStock[pos]);
            if (unidadStock[pos][0] == 'g') cantGramos[pos] = validarFloatRango(0, 500000);
            else cantUnidades[pos] = validarFloatRango(0, 500000);
            printf("Stock actualizado correctamente\n");
        }else{
            printf("Error: Recurso no encontrado\n");
        }
        printf("Desea modificar otro recurso del stock 1.Si/2.No: ");
        seguir = validarFloatRango(1, 2);
    }while(seguir == 1);
}

int mostrarProductos(int *id, char nombres[][50], int *demanda, 
                     float *tiempo, int *estado, int n, int contP){
    int activos = 0;
    printf("\n%-4s %-30s %8s %10s\n", "ID", "Producto", "Solic.", "Min/Unid");
    for (int i = n; i < contP; i++){
        if (estado[i] != 3){
            activos++;
            printf("%-4d %-30s %8d %10.1f\n", id[i], nombres[i], demanda[i], tiempo[i]);
        }
    }
    if (activos == 0) printf("Error: No hay productos activos\n");
    return activos;
}

void ingresarDemanda(int *id, char nombres[][50], int *demanda, 
                     float *tiempo, int *estado, int contP){
    printf("Seleccione: 1.Ingresar demanda por producto / 2.Reiniciar demanda a 0 (Nuevo dia): ");
    if ((int)validarFloatRango(1, 2) == 2){
        for (int i = 0; i < contP; i++) demanda[i] = 0;
        printf("Demanda reiniciada a 0 correctamente\n");
        return;
    }
    int seguir;
    do{
        if (mostrarProductos(id, nombres, demanda, tiempo, estado, 0, contP) == 0) return;
        int pos = buscarProducto(id, nombres, demanda, tiempo, estado, contP);
        if (pos != -1){
            printf("Nueva cantidad demandada para %s: ", nombres[pos]);
            demanda[pos] = validarFloatRango(0, 1000);
        }
        printf("Desea modificar otro producto 1.Si/2.No: ");
        seguir = validarFloatRango(1, 2);
    }while(seguir == 1);
}

int buscarProducto(int *id, char nombres[][50], int *demanda, 
                   float *tiempo, int *estado, int contP){
    printf("Ingrese el nombre (o parte) del producto: ");
    char nombre[50];
    leercadena(nombre, 50);

    int hits = 0, idx = -1;
    for (int i = 0; i < contP; i++){
        if (estado[i] != 3 && strcasecmp(nombre, nombres[i]) == 0){
            mostrarProductos(id, nombres, demanda, tiempo, estado, i, i + 1);
            return i;
        }
        if (estado[i] != 3 && contieneTexto(nombres[i], nombre)){ hits++; idx = i; }
    }
    if (hits == 1){
        mostrarProductos(id, nombres, demanda, tiempo, estado, idx, idx + 1);
        return idx;
    }
    if (hits > 1){
        printf("\nCoincidencias encontradas:\n");
        for (int i = 0; i < contP; i++)
            if (estado[i] != 3 && contieneTexto(nombres[i], nombre))
                printf("  ID %d: %s\n", id[i], nombres[i]);
        printf("Ingrese el ID exacto del producto (0 - %d): ", contP - 1);
        int sel = validarFloatRango(0, contP - 1);
        if (estado[sel] != 3 && contieneTexto(nombres[sel], nombre)){
            mostrarProductos(id, nombres, demanda, tiempo, estado, sel, sel + 1);
            return sel;
        }
    }
    printf("Error: Producto no encontrado\n");
    return -1;
}

void editarProducto(int *id, char nombres[][50], int *demanda, 
                    float *tiempo, int *estado, float recetas[][27], int *contP,
                    char nombresStock[][30], char nombresUso[][30], 
                    char unidadStock[][15], int totalStock){
    printf("Seleccione: 1.Modificar producto / 2.Agregar producto / 3.Activar inactivo: ");
    int accion = validarFloatRango(1, 3);

    if (accion == 1){
        int pos = buscarProducto(id, nombres, demanda, tiempo, estado, *contP);
        if (pos == -1) return;
        printf("Editar: 1.Nombre / 2.Solicitados / 3.Minutos / 4.Recursos / 5.Todo: ");
        int opc = validarFloatRango(1, 5);
        if (opc == 1 || opc == 5){ printf("Nuevo nombre: "); leercadena(nombres[pos], 50); }
        if (opc == 2 || opc == 5){ printf("Nueva cantidad solicitada: "); demanda[pos] = validarFloatRango(0, 1000); }
        if (opc == 3 || opc == 5){ printf("Nuevos minutos/unidad: "); tiempo[pos] = validarFloatRango(1, 120); }
        if (opc == 4 || opc == 5) gestionarReceta(pos, recetas, nombres, nombresStock, nombresUso, unidadStock, totalStock);
        printf("Producto actualizado correctamente\n");
    }else if (accion == 2){
        if (*contP >= 25){ printf("Error: Capacidad maxima alcanzada\n"); return; }
        id[*contP] = *contP; estado[*contP] = 0;
        for (int j = 0; j < totalStock; j++) recetas[*contP][j] = 0;
        printf("Nombre: "); leercadena(nombres[*contP], 50);
        printf("Cantidad solicitada: "); demanda[*contP] = validarFloatRango(0, 1000);
        printf("Minutos/unidad: "); tiempo[*contP] = validarFloatRango(1, 120);
        gestionarReceta(*contP, recetas, nombres, nombresStock, nombresUso, unidadStock, totalStock);
        (*contP)++;
        printf("Producto agregado correctamente\n");
    }else{
        int inactivos = 0;
        for (int i = 0; i < *contP; i++)
            if (estado[i] == 3){ inactivos++; printf("  ID %d: %s\n", id[i], nombres[i]); }
        if (inactivos == 0){ printf("No hay productos inactivos\n"); return; }
        printf("Ingrese el ID del producto a activar (0 - %d): ", *contP - 1);
        int sel = validarFloatRango(0, *contP - 1);
        if (estado[sel] == 3){ estado[sel] = 0; printf("Producto %s activado\n", nombres[sel]); }
        else printf("Error: El ID no corresponde a un producto inactivo\n");
    }
}

void eliminarProducto(int *id, char nombres[][50], int *demanda, 
                      float *tiempo, int *estado, int contP){
    int pos = buscarProducto(id, nombres, demanda, tiempo, estado, contP);
    if (pos == -1) return;
    printf("Desea borrar el producto 1.Si/2.No: ");
    if ((int)validarFloatRango(1, 2) == 1){
        estado[pos] = 3;
        demanda[pos] = 0;
        printf("El producto con el id: %d esta inactivo\n", id[pos]);
    }
}

void calcularProduccion(int *id, char nombres[][50], int *demanda, 
                        float *tiempo, int *estado, float recetas[][27], int contP, 
                        float tiempoDisp, char nombresStock[][30], 
                        char nombresUso[][30], char unidadStock[][15], int *cantUnidades, 
                        float *cantGramos, int *factorConversion, int totalStock){
    int dispU[27], reqU[27] = {0}, hayPedidos = 0, faltanRec = 0, hayCompras = 0;
    float dispG[27], reqG[27] = {0}, minTotal = 0;
    char tTxt[25];

    for (int j = 0; j < totalStock; j++){
        dispU[j] = cantUnidades[j] * factorConversion[j];
        dispG[j] = cantGramos[j];
    }

    printf("\n--- RESUMEN DE PRODUCCION SOLICITADA ---\n");
    printf("%-4s %-30s %8s %9s %15s\n", "ID", "Producto", "Solic.", "Max.Fab", "Tiempo Req.");
    for (int i = 0; i < contP; i++){
        if (estado[i] != 3 && demanda[i] > 0){
            hayPedidos = 1;
            int maxFab = 999999;
            for (int j = 0; j < totalStock; j++){
                if (recetas[i][j] > 0){
                    int posib = (unidadStock[j][0] == 'g') ? (int)(cantGramos[j] / recetas[i][j])
                                                           : (cantUnidades[j] * factorConversion[j]) / (int)recetas[i][j];
                    if (posib < maxFab) maxFab = posib;
                    if (unidadStock[j][0] == 'g'){ reqG[j] += demanda[i] * recetas[i][j]; dispG[j] -= demanda[i] * recetas[i][j]; }
                    else{ reqU[j] += demanda[i] * (int)recetas[i][j]; dispU[j] -= demanda[i] * (int)recetas[i][j]; }
                }
            }
            float minProd = demanda[i] * tiempo[i];
            minTotal += minProd;
            int hP = minProd / 60; float mP = minProd - hP * 60;
            sprintf(tTxt, (mP - (int)mP < 0.01) ? "%d h %.0f min" : "%d h %.1f min", hP, mP);
            printf("%-4d %-30s %8d %9d %15s\n", id[i], nombres[i], demanda[i], maxFab == 999999 ? 0 : maxFab, tTxt);
        }
    }
    if (!hayPedidos){ printf("No hay productos solicitados (todas las cantidades estan en 0).\n"); return; }

    printf("\n--- DESGLOSE DE CONSUMO Y FALTANTES DE RECURSOS ---\n");
    printf("%-22s  %11s  %11s  %11s  %11s\n", "Recurso", "Stock Disp.", "Requerido", "Restante", "Faltante");
    for (int j = 0; j < totalStock; j++){
        if (reqU[j] > 0 || reqG[j] > 0){
            if (unidadStock[j][0] == 'g'){
                float rest = dispG[j] >= 0 ? dispG[j] : 0, falt = dispG[j] < 0 ? -dispG[j] : 0;
                if (falt > 0) faltanRec = 1;
                printf("%-22s  %9.1f g  %9.1f g  %9.1f g  %9.1f g\n", nombresUso[j], cantGramos[j], reqG[j], rest, falt);
            }else{
                int ini = cantUnidades[j] * factorConversion[j], rest = dispU[j] >= 0 ? dispU[j] : 0, falt = dispU[j] < 0 ? -dispU[j] : 0;
                if (falt > 0){ faltanRec = 1; if (factorConversion[j] > 1) hayCompras = 1; }
                printf("%-22s  %9d u  %9d u  %9d u  %9d u\n", nombresUso[j], ini, reqU[j], rest, falt);
            }
        }
    }

    if (hayCompras){
        printf("\n--- LISTA DE COMPRAS SUGERIDA (UNIDADES DE MERCADO) ---\n");
        for (int j = 0; j < totalStock; j++)
            if (unidadStock[j][0] != 'g' && factorConversion[j] > 1 && dispU[j] < 0)
                printf(" -> %-20s Faltan %d porciones => Comprar %d %s entero(s)\n",
                       nombresUso[j], -dispU[j], (-dispU[j] + factorConversion[j] - 1) / factorConversion[j], nombresStock[j]);
    }

    float minDisp = tiempoDisp * 60.0;
    int hReq = minTotal / 60, hDisp = minDisp / 60;
    printf("\nJornada requerida: %d h %.0f min / %d h %.0f min disponibles\n",
           hReq, minTotal - hReq * 60, hDisp, minDisp - hDisp * 60);
    if (minTotal <= minDisp && !faltanRec) printf("Resultado: SI es viable cumplir la produccion diaria\n");
    else{
        printf("Resultado: NO es viable cumplir la produccion diaria\n");
        if (minTotal > minDisp) printf(" -> Faltan %d h %.0f min de jornada\n", (int)((minTotal - minDisp)/60), (minTotal - minDisp) - (int)((minTotal - minDisp)/60)*60);
        if (faltanRec) printf(" -> Revise la columna Faltante para reponer stock\n");
    }
}
