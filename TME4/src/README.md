

# Question 2

Oui. Si jamais plusieurs threads sont en concurrence et qu'une commutation arrive entre deux transferts, i vers j et k vers l, plusieurs cas sont possibles.
- j = l : Dans ce cas là, lorsqu'on crédite j, on a un mutex qui nous permet d'assurer la synchronisation entre les transferts de i et de k.
- i = k : idem pour débiter
- i != k et/ou j != l : Aucun problème ne se pose pour débiter ou créditer la même personne avec un crédit ou un débit qui pourrait être perdu.

# Question 4

On vérouille le débité et le crédité avant d'effectuer les opérations. 
On effectue les opérations.
On dévérouille le débité et le crédité.

# Question 5

La fonction transfert ayant déjà vérouillé les mutex, les autres fonctions (débiter et créditer) se bloquent.

# Question 6

On remplace le mutex présent par un récursive mutex en appliquant la même stratégie.

# Question 7

Les synchronisations actuelles seront satisfaites si un thread comptable tourne en concurrence avec les threads de transfert. En effet, d'une part la fonction getSolde est protégée par un mutex et d'autre part, une lecture (fonction getSolde) ne peut se dérouler ne parallèle des fonctions d'écriture (créditer et débiter).

