#include <stdio.h>
#include <windows.h>
#include <time.h>

#define MAX_FILES 10
#define MAX_THREADS 5

DWORD WINAPI CopyFileThread(LPVOID lpParam);  // Déclaration de la fonction CopyFileThread qui sera exécutée par les threads

typedef struct {
    LPTSTR sourceFile; // Chemin d'accès du fichier source à copier
    LPTSTR destFile; // Chemin d'accès du fichier de destination pour la copie
} CopyFileParams;

int main(int argc, LPTSTR argv[])
{
    if (argc < 3 ) {
        printf("Utilisation : programme.exe source1 dest1 source2 dest2 ... sourceN destN\n");
        return 1;
    }

    int file_num = (argc - 1) / 2;
    HANDLE threads[MAX_THREADS]; // Tableau pour stocker les handles des threads
    CopyFileParams params[MAX_FILES]; // Tableau pour stocker les paramètres de copie de fichiers
    clock_t start = clock(); // Temps de départ pour mesurer le temps d'exécution

    // Boucle pour créer les paramètres de copie de fichiers et les threads correspondants
    for (int i = 0; i < file_num; i++) {
        params[i].sourceFile = argv[i * 2 + 1];// Récupère le nom du fichier source
        params[i].destFile = argv[i * 2 + 2]; // Récupère le nom du fichier de destination
        threads[i % MAX_THREADS] = CreateThread(NULL, 0, CopyFileThread, &params[i], 0, NULL); // Crée un thread pour copier le fichier
        if (threads[i % MAX_THREADS] == NULL) {
            printf("Erreur lors de la création du thread.\n");
            return 2;
        }
    }

    // Attendre la fin de tous les threads
    WaitForMultipleObjects(file_num < MAX_THREADS ? file_num : MAX_THREADS, threads, TRUE, INFINITE);

    clock_t end = clock();
    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Copie des fichiers terminée avec succès.\n");
    printf("Temps total : %.2f secondes\n", elapsedTime);

    return 0;
}

DWORD WINAPI CopyFileThread(LPVOID lpParam)
{
    CopyFileParams* params = (CopyFileParams*)lpParam;
    if (!CopyFile(params->sourceFile, params->destFile, FALSE)) { // Copie le fichier source vers la destination
        printf("Erreur lors de la copie du fichier %s. Code d'erreur : %x\n", params->sourceFile, GetLastError()); // Affiche une erreur en cas d'échec de la copie
        return 1;
    }
    printf("Copie du fichier %s terminée.\n", params->sourceFile); // Affiche un message de réussite de la copie
    return 0;
}
