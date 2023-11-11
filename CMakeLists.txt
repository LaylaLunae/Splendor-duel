cmake_minimum_required(VERSION 3.26)
project(Splendor)

set(CMAKE_CXX_STANDARD 17)

add_executable(Splendor main.cpp
        include/couleur.h
        include/carteJoaillerie.h
        src/carteJoaillerie.cpp
        include/carteNoble.h
        src/carteNoble.cpp
        include/privilege.h
        include/joueur.h
        src/joueur.cpp
        include/carte.h
        include/pouvoir.h
        src/carte.cpp
        src/jeton.cpp
        src/privilege.cpp
        include/obligatoire.h
        src/obligatoire.cpp
        include/optionnelle.h
        src/optionnelle.cpp
        src/plateau.cpp
        include/pioche.h
        src/pioche.cpp)
