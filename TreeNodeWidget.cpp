#include <iostream>
#include "TreeNodeWidget.hpp"

TreeNodeWidget::TreeNodeWidget() {
    initFont();
}

TreeNodeWidget::TreeNodeWidget(Tree * node, sf::Vector2f position) : m_position(position), m_node(node), m_circleColor(sf::Color::White), m_fontSize(15) {
    initFont();
    initText();
    setTextFromNode();
    m_circle.setFillColor(m_circleColor);
    m_circle.setPosition(position);
}

TreeNodeWidget::TreeNodeWidget(const TreeNodeWidget &other) : m_position(other.m_position),
    m_node(other.m_node),
    m_circleColor(other.m_circleColor),
    m_circle(other.m_circle),
    m_text(other.m_text),
    m_font(other.m_font),
    m_fontSize(other.m_fontSize),
    m_radius(other.m_radius) {
    initText();
    setTextFromNode();
}

void TreeNodeWidget::setPosition(const sf::Vector2f &position) {
    m_position = position;
    m_circle.setPosition(m_position);
}

void TreeNodeWidget::setCircleColor(sf::Color color) {
    m_circleColor = color;
    m_circle.setFillColor(m_circleColor);
}

void TreeNodeWidget::setPositionByOrigin(const sf::Vector2f &position) {
    m_position = sf::Vector2f (position.x - m_radius, position.y - m_radius );
    m_circle.setPosition(m_position);
}

void TreeNodeWidget::setRadius(float radius) {
    m_radius = radius;
    m_circle.setRadius(m_radius);
}

void TreeNodeWidget::initFont(std::string path) {
    if (!m_font.loadFromFile(path))
    {
        std::cerr << "[ERROR] Failed to load font: " << path << std::endl;
        exit(1);
    }
}

void TreeNodeWidget::setTextFromNode() {
    if (!m_node)
        return;
    std::string str = std::to_string(m_node->value);
    setText(str);
}

void TreeNodeWidget::initText() {
    m_text.setFont(m_font);
    m_text.setCharacterSize(m_fontSize);
    auto pos = m_position;

    auto bounds = m_text.getLocalBounds();

    pos.x += m_radius - bounds.width / 2.f;
    pos.y += m_radius - bounds.height / 2.f;

    m_text.setPosition(pos);
    m_text.setFillColor(sf::Color::Red);
}

void TreeNodeWidget::setText(const std::string & text) {
    m_text.setString(text);
}

void TreeNodeWidget::setNode(Tree *node) {
    m_node = node;
}

void TreeNodeWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_circle);
    target.draw(m_text);
}

void TreeNodeWidget::translate(const sf::Vector2f &position) {
    m_position += position;
    m_circle.setPosition(m_position);
    auto pos = m_position;

    auto bounds = m_text.getLocalBounds();

    pos.x += m_radius - bounds.width / 2.f;
    pos.y += m_radius - bounds.height / 2.f;

    m_text.setPosition(pos);
}

const sf::Vector2f &TreeNodeWidget::getPosition() const {
    return m_position;
}

Tree *TreeNodeWidget::getNode() const {
    return m_node;
}

TreeNodeWidget *TreeNodeWidget::getLeft() const {
    return m_left;
}

void TreeNodeWidget::setLeft(TreeNodeWidget *mLeft) {
    m_left = mLeft;
}

TreeNodeWidget *TreeNodeWidget::getRight() const {
    return m_right;
}

void TreeNodeWidget::setRight(TreeNodeWidget *mRight) {
    m_right = mRight;
}
