# Gestion de fichiers


Les différences entre ```stat```, ```fstat``` et ```lstat```:

C'est [ici](http://man7.org/linux/man-pages/man2/stat.2.html).

## liste d'include important pour les fichiers
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
```

## Opérations sur les fichiers

### Ouverture
La fonction ```open``` permet d'obtenir un descripteur de fichier à partir du nom du fichier.

```C
int open(const char *pathname, int flags, mode_t mode);
```

* ```pathname``` est le chemin vers le fichier.
* ```flags``` indique le mode d'accès au fichier (voir ce [lien](http://man7.org/linux/man-pages/man2/open.2.html) pour une liste de tous les flags disponibles).
* ```mode``` permet de fixer les permissions lors de la création du fichier.

```open``` renvoie:
* Le descripteur de fichier si l'opération est un succès.
* -1 (avec mise à jour de ```errno``` pour correspondre à l'erreur encourue).

### Fermeture

Il est important de fermer le fichier (avec le descripteur de fichier) en utilisant la fonction ```close``` (définit dans ```unistd.h```)
```C
int close (int FileDescriptor);
```
### Lecture

Pour lire un fichier, on utilise ```read``` (définit dans ```unistd.h``` aussi).
```C
ssize_t read(int FileDescriptor, void *buf, size_t count)
```

* ```buf``` 