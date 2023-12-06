cmake_minimum_required(VERSION 3.26)
project(Splendor)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/mingw_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.5.2/lib")



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
        src/pioche.cpp
        include/jeu.h
        src/IA.cpp
        src/IA.cpp
        src/humain.cpp
        src/humain.cpp
        src/jeu.cpp
        include/affichage_joueur.h
        include/plateau.h
        include/jeton.h
        affichage/affichage_carte.h
        affichage/affichage_carte.cpp
        include/affichage_joueur.h
        include/query.h
        vcpkg.json
)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(Splendor
        Qt::Core
        Qt::Gui
        Qt::Widgets
)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

#find_package(unofficial-sqlite3 CONFIG REQUIRED)
#target_link_libraries(Splendor unofficial::sqlite3::sqlite3)