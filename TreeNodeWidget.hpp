#ifndef TREENODEWIDGET_HPP
#define TREENODEWIDGET_HPP


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Tree.hpp"
#include "ParametersWidget.hpp"

class TreeNodeWidget : public sf::Drawable {
public:
    TreeNodeWidget();
    TreeNodeWidget(const TreeNodeWidget & other);
    TreeNodeWidget(Tree *node, sf::Vector2f position);

    void setPositionByOrigin(const sf::Vector2f &position);
    void setPosition(const sf::Vector2f &position);
    void translate(const sf::Vector2f &offset);
    void setRadius(float radius);
    void setNode(Tree * node);
    void setCircleColor(sf::Color color);
    void setTextFromNode();
    void setText(const std::string &text);
    const sf::Vector2f &getPosition() const;
    Tree *getNode() const;
    TreeNodeWidget *getLeft() const;
    void setLeft(TreeNodeWidget *mLeft);
    TreeNodeWidget *getRight() const;
    void setRight(TreeNodeWidget *mRight);
    void initParametersWidget();
    void updateParametersWidgetGeometry();
    void updateParametersWidgetContent();

private:
    ParametersWidget parametersWidget;
    sf::CircleShape m_circle;
    sf::Font m_font;
    sf::Text m_text;
    Tree * m_node;
    float m_radius;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    unsigned int m_fontSize;
    sf::Color m_circleColor;
    TreeNodeWidget * m_left;
    TreeNodeWidget * m_right;
    void initFont(std::string path = "Hack-Regular.ttf");
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void initText();
};


#endif
