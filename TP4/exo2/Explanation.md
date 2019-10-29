Le processus fils ne peut pas choisir un chiffre aléatoire plus grand que 255 car ce dernier est un entier signé codé sur 8 bits.

$2^8 =256$ (8 étant le nombre de bits). Si on considère que le nombre $0$ peut également être sélectionné,  on réduit ce nombre de 1 et on obtient donc $255$.