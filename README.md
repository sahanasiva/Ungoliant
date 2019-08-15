Ungoliant, Robot d’Indexation et Moteur de Recherche, est une application web implémenté en langage C. Il s'agît d'un moteur de recherche, un programme capable d’explorer récursivement le contenu d’un ensemble de pages HTML ou de sites Web, de les indexer, et de permettre à un utilisateur d’effectuer une recherche sur leur contenu.
Cette application comprend :
1. un analyseur syntaxique (parser) de pages HTML ;
2. un gestionnaire de fichier d’index qui contient les informations nécessaires pour associer un ensemble de pages à un mot-clef donné, le gestionnaire permettant d’effectuer, ajouter, supprimer ou mettre à jour de telles associations ;
3. un robot d’indexation (crawler) ou araignée, qui télécharge chaque page, analyse leur contenu à l’aide du parser, ajoute de l’information à l’index et se déplaçe de page en page en suivant les liens externes ;
4. enfin, un gestionnaire de requêtes (query engine) permettant à un utilisateur de retrouver des pages indexées à partir d’un ou plusieurs mots-clefs.

