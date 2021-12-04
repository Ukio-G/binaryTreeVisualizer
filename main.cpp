#include <GL/glew.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window.hpp>
#include <imgui.h>
#include <iostream>
#include "imgui-SFML.h"
#include "Tree.hpp"
#include "TreeWidget.hpp"
#include "rotations.hpp"

Tree* sampleTree() {
    Tree *t = new Tree(50);
    t->insert(25);
    t->insert(100);
    t->insert(0);
    t->insert(37);
    return t;
}

void treeControlMenu(Tree *& root, TreeWidget & widget);

int main() {
    sf::ContextSettings settings;

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(false);
    ImGui::SFML::Init(window);
    window.setActive(true);
    sf::Clock deltaClock;
    sf::Clock globalClock;
    globalClock.restart();

    Tree * t = sampleTree();

    TreeWidget tw(t, {50, 50}, {1400,850});

    tw.setContentOnCenter();
    tw.initConnectionBetweenNodes();
    glewInit();

    // run the main loop
    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                running = false;
            else if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            }
        }


        /* Start ImGUI drawing */
        ImGui::SFML::Update(window, deltaClock.restart());
        treeControlMenu(t, tw);
        /* ImGui::Begin("Disassembly"); */

            /***************************/
            /* ImGui menu content here */
            /***************************/

        /* ImGui::End(); */
        /* End ImGUI drawing */

        window.clear();

        // Render shapes


        tw.drawSegments(window);
        window.draw(tw);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}

int newValue = 0;
int nodeKeyManipulation = 0;
void treeControlMenu(Tree *& root, TreeWidget & widget) {
    ImGui::Begin("Tree manipulations");
    /***************************/
    /* ImGui menu content here */
    /***************************/

    ImGui::InputInt("New node value", &newValue);
    ImGui::InputInt("Modify node value", &nodeKeyManipulation);
    bool rebuildTreeWidget = false;

    if (ImGui::Button("Append")) {
        std::cout << newValue << std::endl;
        root->insert(newValue);
        rebuildTreeWidget = true;
    }

    if (ImGui::Button("Small left rotate")) {
        smallLeftRotate(root, nodeKeyManipulation);
        rebuildTreeWidget = true;
    }

    if (ImGui::Button("Small right rotate")) {
        smallRightRotate(root, nodeKeyManipulation);
        rebuildTreeWidget = true;
    }

    if (ImGui::Button("Big left rotate")) {
        bigLeftRotate(root, nodeKeyManipulation);
        rebuildTreeWidget = true;
    }

    if (ImGui::Button("Big right rotate")) {
        bigRightRotate(root, nodeKeyManipulation);
        rebuildTreeWidget = true;
    }

    if (ImGui::Button("Highlight")) {
        widget.highlight(nodeKeyManipulation);
    }

    if (ImGui::Button("Rebuild")) {
        rebuildTreeWidget = true;
    }

    if (rebuildTreeWidget) {
        widget.rebuildTree(root);
        widget.setContentOnCenter();
        widget.initConnectionBetweenNodes();
    }

    ImGui::End();
}