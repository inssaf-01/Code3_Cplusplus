# Le code utilise l'héritage en C++ pour modéliser un système de gestion de comptes bancaires. 
- La classe de base, CompteBancaire, représente un compte bancaire général avec des attributs et méthodes pour gérer le solde. 
- Les classes dérivées CompteCourant et CompteEpargne héritent de CompteBancaire et ajoutent des fonctionnalités spécifiques comme le découvert autorisé et le taux d'intérêt respectivement.
- Une classe composite, CompteCourantEpargne, combine les caractéristiques des deux classes dérivées.
-  La classe Banque gère plusieurs comptes en utilisant un tableau de pointeurs vers des objets de type CompteBancaire et fournit des méthodes pour ajouter, supprimer, afficher les comptes, et calculer le total des soldes.
