#include "ParametersWidget.hpp"

ParametersWidget::ParametersWidget() {}

ParametersWidget::ParametersWidget(const sf::Vector2f & position, const sf::Vector2f & size) : m_basePosition(position), m_nodeSize(size) {}

ParametersWidget::ParametersWidget(const ParametersWidget &other) {}

ParametersWidget::~ParametersWidget() {

}

void ParametersWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &item: widgets) {
        target.draw(item);
    }
}

void ParametersWidget::setPosition(const sf::Vector2f &position) {
    float y_offset = m_nodeSize.y;
    m_basePosition = position;
    int i = 0;
    for (auto &item: widgets) {
        item.setPosition({position.x, position.y + y_offset * i});
        i++;
    }
}

void ParametersWidget::resizeWithUpdatePosition(const sf::Vector2f &newSize) {
    m_nodeSize = newSize;
    float y_offset = m_nodeSize.y;
    int i = 0;
    for (auto &item: widgets) {
        item.setSize(newSize);
        item.setPosition({m_basePosition.x, m_basePosition.y + y_offset * i});
        i++;
    }
}

void ParametersWidget::resizeNodes(const sf::Vector2f &size) {
    m_nodeSize = size;
    for (auto &item: widgets) {
        item.setSize(size);
    }
}

void ParametersWidget::translate(const sf::Vector2f &offset) {
    for (auto &item: widgets) {
        item.translate(offset);
    }
}

void ParametersWidget::appendParameter(const std::string &parameter, const std::string & value) {
    sf::Vector2f position = {m_basePosition.x, m_basePosition.y + m_nodeSize.y * widgets.size()};
    ParameterWidget widget(position, m_nodeSize, parameter, value);
    widgets.push_back(widget);
}
