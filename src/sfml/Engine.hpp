/** Auteur: Maxime HAVGOUDOUKIAN
 *
 *  Nom Projet: Asteroid
 *
 *  Date de création: 09/04/2021
 *  Dernière modification: 12/04/2021
 *
 *  Contient la boucle principale du jeu
 *
**/

#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <chrono>

class Engine
{
    public:
        Engine();
        ~Engine();

        void run();
        void update(sf::Time deltaTime);
        void processEvents();
        void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
        void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);
        void render(); // Partie rendu de l'application

    public: // Normalement privé
        bool MouseL=false, MouseR=false, Echap=false, MouseRPressed = false;
        bool Left=false, Right=false, Up=false, Space=false, Down=false, Z=false, Q=false, D=false, M=false, P=false;
        bool SpacePressed=false, UpPressed=false, DownPressed=false, LeftPressed=false, RightPressed=false, MPressed=false, PPressed=false;

        sf::RenderWindow m_window;
        sf::Time TimePerFrame;
};

#endif // ENGINE_HPP_INCLUDED