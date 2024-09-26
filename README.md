# Arcade

**Arcade** est une plateforme de jeu permettant à l'utilisateur de choisir parmi plusieurs jeux, tout en enregistrant les scores des joueurs. Cette plateforme inclut des jeux comme **Snake** et **Nibbler**, jouables dans différents styles graphiques. Avec **Arcade**, l'utilisateur peut choisir entre trois interfaces graphiques : **NCurses**, **SDL2**, et **SFML**.

## 🎮 Jeux disponibles

### 🐍 Snake

Dans **Snake**, le joueur contrôle un serpent qui grandit à mesure qu'il mange des éléments dispersés dans l'environnement. Le but est de grandir le plus possible sans entrer en collision avec les murs ou avec soi-même.

### 🐍 Nibbler

**Nibbler** est similaire à **Snake**, mais avec des mécaniques supplémentaires, comme la gestion de plusieurs obstacles et la nécessité de naviguer dans des labyrinthes complexes tout en grandissant.

## 🖥️ Interfaces graphiques

Avec **Arcade**, vous pouvez jouer à ces jeux avec l'un des trois styles graphiques suivants :

- **NCurses** : Pour une expérience en ligne de commande, avec un rendu textuel simple et efficace.
- **SDL2** : Pour une interface graphique plus moderne et intuitive, avec des graphismes 2D.
- **SFML** : Une alternative puissante et flexible, également en 2D, mais avec des effets et des animations plus avancés.

Chaque interface propose une expérience de jeu différente, tout en restant fidèle aux mécanismes de base des jeux.

## 📈 Système de score

Chaque partie enregistrera le score du joueur, et **Arcade** tient un registre des meilleurs scores pour chaque jeu et chaque style graphique. Vous pouvez ainsi comparer vos performances avec celles des autres joueurs et tenter de battre les records existants.

## 🕹️ Utilisation

Lorsque vous démarrez Arcade, le programme vous propose une interface simple pour choisir :

- Le jeu que vous souhaitez jouer (par exemple, Snake ou Nibbler).
- Le style graphique dans lequel vous souhaitez jouer (choisissez entre NCurses, SDL2, ou SFML).
- Vos scores seront automatiquement enregistrés et vous pourrez consulter les meilleurs scores après chaque partie.

### Commandes du jeu

Les commandes peuvent varier légèrement selon le style graphique choisi. Voici les commandes par défaut :

- Déplacement : Utilisez les touches fléchées pour déplacer votre personnage dans Snake ou Nibbler.
- Pause : Appuyez sur la touche P pour mettre le jeu en pause.
- Quitter : Appuyez sur Q pour quitter le jeu à tout moment.

## 🚧 Fonctionnalités à venir

- [ ] Ajout de nouveaux jeux à la plateforme.
- [ ] Support pour d'autres bibliothèques graphiques.
- [ ] Amélioration du système de score avec des classements en ligne.

## 🖼️ Captures d'écran

![Menu du jeu en SFML](https://github.com/TTG-Phyros/repositoriesPhotos/blob/main/Arcade/Arcade_sfml_menu.png)
![Menu du jeu en SDL2](https://github.com/TTG-Phyros/repositoriesPhotos/blob/main/Arcade/Arcade_sdl2_menu.png)
![Menu du jeu en NCurse](https://github.com/TTG-Phyros/repositoriesPhotos/blob/main/Arcade/Arcade_ncurse_menu.png)
![Snake en SFML](https://github.com/TTG-Phyros/repositoriesPhotos/blob/main/Arcade/Arcade_sfml_snake.png)
![Nibbler en SFML](https://github.com/TTG-Phyros/repositoriesPhotos/blob/main/Arcade/Arcade_sfml_nibbler.png)

## 🚀 Installation
### Prérequis

    [MakeFile, SFML, SDL2, SDL2-TTF, NCurse G++]

## Instructions

### Clone le dépôt :

    git clone https://github.com/ton-compte/Arcade.git

### Accède au dossier du projet :

    cd Arcade

### Compile le projet :

    make

### Lance le jeu :

    ./arcade [Path relatif de la lib graphique de base]

### Pour Nettoyer les fichiers :

    make fclean

## Auteur

| [<img src="https://github.com/Anagon1803.png?size=85" width=85><br><sub>Anaëlle Urbon</sub>](https://github.com/Anagon1803) | [<img src="https://github.com/BaptisteMERY.png?size=85" width=85><br><sub>Baptiste Mery</sub>](https://github.com/BaptisteMERY) | [<img src="https://github.com/TTG-Phyros.png?size=85" width=85><br><sub>Nicolas Audibert</sub>](https://github.com/TTG-Phyros)
| :---: | :---: | :---: |
