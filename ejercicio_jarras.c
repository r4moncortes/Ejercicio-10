#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int jarra5;
    int jarra3;
} Estado;

bool estadoVisitado(Estado visitados[], int size, Estado nuevo) {
    for (int i = 0; i < size; i++) {
        if (visitados[i].jarra5 == nuevo.jarra5 && visitados[i].jarra3 == nuevo.jarra3) {
            return true;
        }
    }
    return false;
}

void imprimirPasos(Estado pasos[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Paso %d: Jarra de 5 litros = %d, Jarra de 3 litros = %d\n", i, pasos[i].jarra5, pasos[i].jarra3);
    }
}

int main() {
	
    const int capacidadJarra5 = 5;
    const int capacidadJarra3 = 3;
    const int objetivo = 4;

    Estado visitados[1000];
    int visitadosSize = 0;

    Estado cola[1000];
    int frente = 0, atras = 0;

    Estado inicial = {0, 0};
    cola[atras++] = inicial;
    visitados[visitadosSize++] = inicial;

    Estado pasos[1000];
    int pasosSize = 0;

    while (frente < atras) {
        Estado actual = cola[frente++];
        pasos[pasosSize++] = actual;

        if (actual.jarra5 == objetivo || actual.jarra3 == objetivo) {
            imprimirPasos(pasos, pasosSize);
            return 0;
        }

        Estado posiblesEstados[6] = {
            {capacidadJarra5, actual.jarra3}, // Llenar jarra de 5 litros
            {actual.jarra5, capacidadJarra3}, // Llenar jarra de 3 litros
            {0, actual.jarra3},               // Vaciar jarra de 5 litros
            {actual.jarra5, 0},               // Vaciar jarra de 3 litros
            {actual.jarra5 - (capacidadJarra3 - actual.jarra3) >= 0 ? actual.jarra5 - (capacidadJarra3 - actual.jarra3) : 0, actual.jarra5 + actual.jarra3 <= capacidadJarra3 ? actual.jarra5 + actual.jarra3 : capacidadJarra3}, // Verter jarra de 5 litros a jarra de 3 litros
            {actual.jarra5 + actual.jarra3 <= capacidadJarra5 ? actual.jarra5 + actual.jarra3 : capacidadJarra5, actual.jarra3 - (capacidadJarra5 - actual.jarra5) >= 0 ? actual.jarra3 - (capacidadJarra5 - actual.jarra5) : 0}  // Verter jarra de 3 litros a jarra de 5 litros
        };

        for (int i = 0; i < 6; i++) {
            if (!estadoVisitado(visitados, visitadosSize, posiblesEstados[i])) {
                cola[atras++] = posiblesEstados[i];
                visitados[visitadosSize++] = posiblesEstados[i];
            }
        }
    }

    printf("No se encontro una solucion.\n");
    return 0;
}

