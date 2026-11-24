#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {
    int id[25] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    char nombres[25][50] = {
        "Chivito Uruguayo", "BBQ Cheesesteak", "Philly Cheesesteak", "Pulled Pork",
        "Philly Cheesechicken", "BBQ Cheesechicken", "Cerdo Ahumado", "Morlaco de Pernil",
        "Hamburguesa Simple", "Hamburguesa Doble", "Hamburguesa Triple", "Salchipapa",
        "Porcion de papas fritas", "Media porcion de papas fritas", "Papas All meats", "Papas Bacon Smash",
        "Agua con gas", "Agua", "Cola", "Cerveza"
    };
    int demanda[25] = {0}, estado[25] = {0}, contP = 20, opc, opc2;
    float tiempo[25] = {5,5,5,4, 5,5,5,4, 4,4.5,5,4, 3.5,3,5,4.5, 0.1,0.1,0.1,0.1}, tiempoDisp = 12.0;

    char nombresStock[27][30] = {
        "Desechables","Pan de hamburguesa","Pan de baguette","Lechuga","Carne","Lomo de res","Tomate",
        "Huevo","Queso","Papa chola","Pollo","Cerdo ahumado","Cebolla","Pepino","Champinones",
        "Salchicha","Jamon","Tocino","Mayonesa","Salsa Tomate","Bbq","Salsa to go","Aji",
        "Colas","Cerveza","Agua con gas","Agua"
    };
    char nombresUso[27][30] = {
        "Desechables","Pan de hamburguesa","Pan de baguette","Hojas de Lechuga","Carne","Lomo de res","Rodajas de Tomate",
        "Huevo","Queso","Papa chola","Pollo","Cerdo ahumado","Rodajas de Cebolla","Rodajas de Pepino","Champinones",
        "Salchicha","Jamon","Tocino","Mayonesa","Salsa Tomate","Bbq","Salsa to go","Aji",
        "Colas","Cerveza","Agua con gas","Agua"
    };
    int factorConversion[27] = {1,1,1,20,1,1,6,1,1,1,1,1,10,20,1,1,1,1,1,1,1,1,1,1,1,1,1};
    char unidadStock[27][15] = {
        "unidades","unidades","unidades","unidades","gramos","gramos","unidades","unidades","unidades",
        "unidades","gramos","gramos","unidades","unidades","unidades","unidades","unidades","unidades",
        "gramos","gramos","gramos","gramos","gramos","unidades","unidades","unidades","unidades"
    };
    int cantUnidades[27] = {175,50,40,15,0,0,30,60,50,100,0,0,25,20,50,50,50,50,0,0,0,0,0,24,12,12,12};
    float cantGramos[27] = {0,0,0,0,6000,4000,0,0,0,0,1500,1000,0,0,0,0,0,0,1000,1000,1000,1500,500,0,0,0,0};
    float recetas[25][27] = {
        {1,0,1,2,0,110,2,1,1,0,0,0,2,0,0,0,1,0,0,0,0,30,0,0,0,0,0},
        {1,0,1,0,0,110,0,0,1,0,0,0,2,0,0,0,0,0,0,0,30,0,0,0,0,0,0},
        {1,0,1,0,0,110,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,1,0,2,0,0,0,0,0,0,0,110,2,0,0,0,0,0,20,0,30,0,0,0,0,0,0},
        {1,0,1,0,0,0,0,0,1,0,110,0,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,0,1,0,0,0,0,0,1,0,110,0,2,0,0,0,0,0,0,0,30,0,0,0,0,0,0},
        {1,0,1,0,0,0,0,0,1,0,0,110,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,0,1,2,0,0,2,0,0,0,0,110,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,1,0,0,100,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,1,0,0,200,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,1,0,0,300,0,0,0,3,0,0,0,2,0,0,0,0,0,0,0,0,30,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,20,20,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,15,15,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0},
        {1,0,0,0,100,0,0,0,0,2,0,110,0,0,0,1,0,1,0,0,40,0,0,0,0,0,0},
        {1,0,0,0,100,0,0,0,1,2,0,0,0,0,0,0,0,2,0,0,0,30,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}
    };

    do{
        printf("\nSeleccione una opcion:\n1.Ingrese los limites de jornada\n2.Ingrese las cantidades de stock disponible\n3.Mostrar productos\n4.Ingresar cantidad de los productos demandados\n5.Buscar producto\n6.Editar producto\n7.Eliminar producto\n8.Calcular produccion\n>> ");
        opc = validarFloatRango(1, 8);
        switch (opc){
            case 1: ingresarLimitesJornada(&tiempoDisp); break;
            case 2: ingresarStock(nombresStock, cantUnidades, cantGramos, unidadStock, 27); break;
            case 3: mostrarProductos(id, nombres, demanda, tiempo, estado, 0, contP); break;
            case 4: ingresarDemanda(id, nombres, demanda, tiempo, estado, contP); break;
            case 5: buscarProducto(id, nombres, demanda, tiempo, estado, contP); break;
            case 6: editarProducto(id, nombres, demanda, tiempo, estado, recetas, &contP, nombresStock, nombresUso, unidadStock, 27); break;
            case 7: eliminarProducto(id, nombres, demanda, tiempo, estado, contP); break;
            case 8: calcularProduccion(id, nombres, demanda, tiempo, estado, recetas, contP, tiempoDisp, nombresStock, nombresUso, unidadStock, cantUnidades, cantGramos, factorConversion, 27); break;
        }
        printf("Desea seleccionar otra opcion 1.Si/2.No: ");
        opc2 = validarFloatRango(1, 2);
    }while(opc2 == 1);
    return 0;
}
