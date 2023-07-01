# Programme de copie de fichiers en parallèle

Ce programme permet de copier plusieurs fichiers en parallèle à l'aide de threads. Chaque fichier source est copié vers un fichier de destination spécifié.

## Utilisation

Le programme est destiné à être utilisé en ligne de commande. Voici comment l'utiliser :


- `source1`, `source2`, ..., `sourceN` : Chemins d'accès des fichiers sources à copier.
- `dest1`, `dest2`, ..., `destN` : Chemins d'accès des fichiers de destination pour les copies correspondantes.

## Fonctionnement

Le programme utilise des threads pour effectuer les copies de fichiers en parallèle. Voici comment il fonctionne :

1. Le programme vérifie que les arguments de ligne de commande sont corrects. Il doit y avoir un nombre pair d'arguments (source et destination pour chaque fichier).
2. Les paramètres de copie de fichiers sont créés à partir des arguments de ligne de commande.
3. Des threads sont créés pour chaque fichier à copier. Le nombre maximum de threads simultanés est défini à `MAX_THREADS`.
4. Chaque thread exécute la fonction `CopyFileThread` pour copier le fichier correspondant.
5. Une fois que tous les threads ont terminé, le programme affiche un message de réussite et le temps total écoulé.

## Compilation

Le programme utilise les bibliothèques standard de C (`stdio.h`, `windows.h`, `time.h`). Assurez-vous de les inclure lors de la compilation du programme. Par exemple :


## Remarque

Veuillez noter que ce programme a été conçu pour les systèmes Windows, car il utilise des fonctions spécifiques à Windows (`CreateThread`, `CopyFile`, `GetLastError`). Si vous souhaitez l'utiliser sur un autre système d'exploitation, vous devrez apporter des modifications pour utiliser des fonctions équivalentes.

