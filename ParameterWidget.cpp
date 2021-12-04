//
// Created by ukio on 12/4/21.
//

#include <iostream>
#include "ParameterWidget.hpp"


/* Constructors */

ParameterWidget::ParameterWidget(const sf::Vector2f &position, const sf::Vector2f &size, const std::string & parameter, const std::string & value ) :
    m_position(position),
    m_size(size) {
    setPosition(m_position);
    setSize(m_size);
    setContent(parameter, value);
    initFont("Hack-Regular.ttf");
    initText();
    initBound();
}

ParameterWidget::ParameterWidget(const sf::Vector2f &position, const sf::Vector2f &size) : m_position(position), m_size(size) {
    setPosition(m_position);
    setSize(m_size);
    initFont("Hack-Regular.ttf");
    initText();
    initBound();
}

ParameterWidget::ParameterWidget(const sf::Vector2f &position) : m_position(position) {
    setPosition(m_position);
    initFont("Hack-Regular.ttf");
    initText();
    initBound();
}

ParameterWidget::ParameterWidget() { }

ParameterWidget::ParameterWidget(const ParameterWidget &other) :
    m_position(other.m_position),
    m_size(other.m_size),
    m_content(other.m_content),
    m_font(other.m_font) {
    setPosition(m_position);
    initFont("Hack-Regular.ttf");
    initText();
    initBound();
}

/* Setters */

void ParameterWidget::setSize(const sf::Vector2f &size) {
    m_size = size;
    m_content.first.setCharacterSize(m_size.y - 2.f);
    m_content.second.setCharacterSize(m_size.y - 2.f);
}

void ParameterWidget::setPosition(const sf::Vector2f &position) {
    m_position = position;
    m_content.first.setPosition(position.x, position.y - 1.f);
    m_bound.setPosition(position);
    auto letterSize = m_size.y;

    m_content.second.setPosition(position.x + letterSize * 4, position.y - 1.f);
}

void ParameterWidget::setContent(const std::string &parameter, const std::string &value) {
    m_content.first.setString(parameter + ":");
    m_content.second.setString(value);
}

/* Getters */

sf::Vector2f ParameterWidget::getPosition() const {
    return m_position;
}

sf::Vector2f ParameterWidget::getPosition() {
    return m_position;
}

/* Initialization */

void ParameterWidget::initBound() {
    m_bound = sf::RectangleShape(m_size);
    m_bound.setPosition(m_position);
    m_bound.setFillColor(sf::Color::Black);
    m_bound.setOutlineColor(sf::Color::White);
    m_bound.setOutlineThickness(1.f);
}

void ParameterWidget::initFont(const std::string &fontName) {
    if (!m_font.loadFromFile(fontName)) {
        std::cerr << "[ERROR] Failed to load font: " << fontName << std::endl;
        exit(1);
    }
}

void ParameterWidget::initText() {
    m_content.first.setFont(m_font);
    m_content.second.setFont(m_font);

    m_content.second.setFillColor(sf::Color::White);
    m_content.first.setFillColor(sf::Color::White);
}

/* Drawing */

void ParameterWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_bound);
    target.draw(m_content.first);
    target.draw(m_content.second);
}

ParameterWidget::~ParameterWidget() { }

void ParameterWidget::translate(const sf::Vector2f &offset) {
    m_position += offset;
    setPosition(m_position);
}
