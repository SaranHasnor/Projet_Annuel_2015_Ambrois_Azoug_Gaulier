# Projet Annuel ESGI 4A 3DJV1 2015:
# Guillaume Ambrois
# Thomas Azoug
# Sébastien Gaulier

Ce projet est un moteur OpenGL permettant d'afficher et modifier des effets de particules.

L'interface présente à droite permet d'afficher plusieurs émetteurs de particules, de modifier leurs propriétés, les particules qu'ils émettent, etc.

Les paramètres devraient être plutôt clairs et nous avons confiance en l'ergonomie de notre interface, nous vous invitons donc à tester les possibilités par vous même :)

Les boutons de sauvegarde (Save session) et chargement (Load session) du premier menu utilisent des fichiers nommés "session_particles.txt" et "session_emitters.txt"
Les autres boutons d'import/export peuvent être configurés par l'utilisateur. 
Les fichiers générés peuvent être édités en dehors du programme jusqu'à un certain degré, puis réimportés pour voir le rendu.

/!\ Il faut importer les particules avant les émetteurs qui les contiennent.

Raccourcis :
	Echap					Quitter
	Z/S 					Déplacement avant/arrière
	Q/D 					Déplacement gauche/droite
	X/Espace 				Déplacement bas/haut

Points à améliorer:

- La projection est imparfaite
- Des fichiers modifiés en dehors du programme avec des erreurs peuvent causer l'instabilité du programme au chargement