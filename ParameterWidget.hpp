//
// Created by ukio on 12/4/21.
//

#ifndef PARAMETERWIDGET_HPP
#define PARAMETERWIDGET_HPP


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>

class ParameterWidget : public sf::Drawable {
public:
    ParameterWidget();

    ParameterWidget(const ParameterWidget &other);

    ParameterWidget(const sf::Vector2f &position);

    ParameterWidget(const sf::Vector2f &position, const sf::Vector2f &size);

    ParameterWidget(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &parameter,
                    const std::string &value);

    ~ParameterWidget();

    sf::Vector2f getPosition() const;
    sf::Vector2f getPosition();
    void setSize(const sf::Vector2f &size);
    void initFont(const std::string & fontName);
    void setContent(const std::string & parameter, const std::string & value);
    void translate(const sf::Vector2f& offset);

    void setPosition(const sf::Vector2f &position);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2f                    m_position;
    sf::Vector2f                    m_size;
    std::pair<sf::Text, sf::Text>   m_content;
    sf::Font                        m_font;
    sf::RectangleShape              m_bound;
    void initText();

    void initBound();

};


#endif
