#ifndef PARAMETERSWIDGET_HPP
#define PARAMETERSWIDGET_HPP

#include "ParameterWidget.hpp"

class ParametersWidget : public sf::Drawable {
public:
    ParametersWidget();

    ParametersWidget(const ParametersWidget &other);

    ParametersWidget(const sf::Vector2f &position, const sf::Vector2f &size);

    ~ParametersWidget();

    void appendParameter(const std::string & parameter, const std::string & value);
    void resizeWithUpdatePosition(const sf::Vector2f &newSize);
    void setPosition(const sf::Vector2f & position);
    void resizeNodes(const sf::Vector2f &size);
    void translate(const sf::Vector2f & offset);
    void removeParameters();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<ParameterWidget> widgets;
    sf::Vector2f m_nodeSize;
    sf::Vector2f m_basePosition;
};


#endif
