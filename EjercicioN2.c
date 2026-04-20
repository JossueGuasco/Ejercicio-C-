#include <stdio.h>

int main() {

    int totalEstudiantes = 5;   
    int totalAsignaturas = 3;  
    char nombresEstudiantes[5][50];
    char nombresAsignaturas[3][50];
    float notas[5][3];
    int i, j;                   
    float suma, promedio;      
    float notaAlta, notaBaja;   
    int aprobados, reprobados; 

    printf("=== INGRESO DE ASIGNATURAS ===\n");
    for (j = 0; j < totalAsignaturas; j++) {
       
        printf("Nombre asignatura %d: ", j + 1);
        scanf(" %[^\n]", nombresAsignaturas[j]);
    }


    printf("\n=== INGRESO DE CALIFICACIONES ===\n");

    for (i = 0; i < totalEstudiantes; i++) {
        
        printf("\nNombre del estudiante %d: ", i + 1);
        scanf(" %[^\n]", nombresEstudiantes[i]);

        for (j = 0; j < totalAsignaturas; j++) {
            
            do {
                printf("  Nota en %s (0 a 10): ", nombresAsignaturas[j]);
                scanf("%f", &notas[i][j]);
                if (notas[i][j] < 0 || notas[i][j] > 10)
                printf("  ERROR: La nota debe estar entre 0 y 10.\n");

            } while (notas[i][j] < 0 || notas[i][j] > 10);
        }
    }


    printf("\n\n=== RESULTADOS POR ESTUDIANTE ===\n");
    printf("%-20s %-10s %-10s %-10s\n", "ESTUDIANTE", "PROMEDIO", "MAS ALTA", "MAS BAJA");
    printf("--------------------------------------------------\n");

    for (i = 0; i < totalEstudiantes; i++) {

        suma     = 0;
        notaAlta = notas[i][0];  
        notaBaja = notas[i][0];

        for (j = 0; j < totalAsignaturas; j++) {
            suma += notas[i][j];

            if (notas[i][j] > notaAlta) notaAlta = notas[i][j];
            if (notas[i][j] < notaBaja) notaBaja = notas[i][j];
        }

        promedio = suma / totalAsignaturas;

        printf("%-20s %-10.2f %-10.2f %-10.2f\n",
               nombresEstudiantes[i], promedio, notaAlta, notaBaja);
    }


    printf("\n\n=== RESULTADOS POR ASIGNATURA ===\n");
    printf("%-15s %-10s %-10s %-10s %-10s %-10s\n",
           "ASIGNATURA", "PROMEDIO", "MAS ALTA", "MAS BAJA", "APROBADOS", "REPROBADOS");
    printf("------------------------------------------------------------------\n");

    for (j = 0; j < totalAsignaturas; j++) {

        suma       = 0;
        notaAlta   = notas[0][j];  
        notaBaja   = notas[0][j];
        aprobados  = 0;
        reprobados = 0;

    
        for (i = 0; i < totalEstudiantes; i++) {
            suma += notas[i][j];

            if (notas[i][j] > notaAlta) notaAlta = notas[i][j];
            if (notas[i][j] < notaBaja) notaBaja = notas[i][j];
            if (notas[i][j] >= 6)
                aprobados++;
            else
                reprobados++;
        }

        promedio = suma / totalEstudiantes;

        printf("%-15s %-10.2f %-10.2f %-10.2f %-10d %-10d\n",
               nombresAsignaturas[j], promedio, notaAlta, notaBaja,
               aprobados, reprobados);
    }

    printf("==================================================================\n");

    return 0;
}