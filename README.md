# Projet Annuel ESGI 4A 3DJV1 2015:
# Guillaume Ambrois
# Thomas Azoug
# S�bastien Gaulier

Ce projet est un moteur OpenGL permettant d'afficher et modifier des effets de particules.

L'interface pr�sente � droite permet d'afficher plusieurs �metteurs de particules, de modifier leurs propri�t�s, les particules qu'ils �mettent, etc.

Les param�tres devraient �tre plut�t clairs et nous avons confiance en l'ergonomie de notre interface, nous vous invitons donc � tester les possibilit�s par vous m�me :)

Les boutons de sauvegarde (Save session) et chargement (Load session) du premier menu utilisent des fichiers nomm�s "session_particles.txt" et "session_emitters.txt"
Les autres boutons d'import/export peuvent �tre configur�s par l'utilisateur. 
Les fichiers g�n�r�s peuvent �tre �dit�s en dehors du programme jusqu'� un certain degr�, puis r�import�s pour voir le rendu.

/!\ Il faut importer les particules avant les �metteurs qui les contiennent.

Raccourcis :
	Echap					Quitter
	Z/S 					D�placement avant/arri�re
	Q/D 					D�placement gauche/droite
	X/Espace 				D�placement bas/haut

Points � am�liorer:

- La projection est imparfaite
- Des fichiers modifi�s en dehors du programme avec des erreurs peuvent causer l'instabilit� du programme au chargement