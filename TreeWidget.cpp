#include "TreeWidget.hpp"
#include "rotations.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

const sf::Vector2f &TreeWidget::getPosition() const {
    return m_position;
}

void TreeWidget::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

void TreeWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    target.draw((sf::Vertex*)(connectionNodesLines.data()), connectionNodesLines.size() * 2, sf::Lines);

    for (auto &node: m_nodes)
        target.draw(node);
}

sf::Vector2f TreeWidget::getSize() {
    unsigned int height = root->calculateMaxHeight();
    unsigned int  width = std::pow(2, height) - 1;
    return sf::Vector2f(width, height);
}

void TreeWidget::drawSegments(sf::RenderWindow & window)
{
    std::vector<Line> Llines;

    for (int x = 0; x < m_grid_segments_count.x + 1; ++x) {
        float top_y = static_cast<float>(m_position.y);
        float bottom_y = static_cast<float>(m_position.y + m_size.y);
        sf::Vertex begin_line(sf::Vector2f(static_cast<float>(x * m_grid_segment_size.x + m_position.x), top_y));
        sf::Vertex end_line(sf::Vector2f(static_cast<float>(x * m_grid_segment_size.x + m_position.x), bottom_y));

        Line line = std::make_pair(begin_line, end_line);
        Llines.push_back(line);
    }

    for (int y = 0; y < m_grid_segments_count.y + 1; ++y) {
        float left_x = static_cast<float>(m_position.x);
        float right_x = static_cast<float>(m_position.x + m_size.x);
        sf::Vertex begin_line(sf::Vector2f(left_x, static_cast<float>(y * m_grid_segment_size.y + m_position.y)));
        sf::Vertex end_line(sf::Vector2f(right_x, static_cast<float>(y * m_grid_segment_size.y + m_position.y)));

        Line line = std::make_pair(begin_line, end_line);
        Llines.push_back(line);
    }

    window.draw((sf::Vertex*)(Llines.data()), Llines.size() * 2, sf::Lines);
}

/*
 * Get position (x,y) in window, based on segment coordinated (segment - widget part, rectangle)
 * start value for x|y : 0
 * max x: m_grid_segments_count.x - 1
 * max y: m_grid_segments_count.y - 1
 */
sf::Vector2f TreeWidget::getPositionSquareInGrid(unsigned int x, unsigned int y) {
    auto dx = m_grid_segment_size.x - m_inner_square_size;
    auto dy = m_grid_segment_size.y - m_inner_square_size;

    auto x_result = x * m_grid_segment_size.x + dx;
    auto y_result = y * m_grid_segment_size.y + dy;

    return {x_result, y_result};
}


/*
 * Return grid's segment x and y indexes, based on passed path
 */
sf::Vector2f TreeWidget::getGridSegmentByPath(std::vector<NodePath> & path) {
    auto mid_x_idx = m_grid_segments_count.x / 2;
    for (const auto &item: path) {
        if (item == Left)
            mid_x_idx--;
        else
            mid_x_idx++;
    }
    return sf::Vector2f(mid_x_idx, static_cast<float>(path.size()));
}

std::vector<TreeWidget::NodePath> nodePath(Tree * node)
{
    std::vector<TreeWidget::NodePath> result;
    Tree * parent = node->parent;
    Tree * current = node;

    while (parent) {
        if (current == parent->left)
            result.emplace_back(TreeWidget::NodePath::Left);
        else
            result.emplace_back(TreeWidget::NodePath::Right);
        current = parent;
        parent = parent->parent;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

TreeNodeWidget TreeWidget::infixTravesalCreateNodeWidget(Tree *node) {
    int grid_x = m_nodes.size();
    auto screen_position = getPositionSquareInGrid(grid_x, node->height - 1);
    auto pos = sf::Vector2f(screen_position.x + m_position.x, screen_position.y + m_position.y);
    TreeNodeWidget nodeWidget(node, pos);
    nodeWidget.setRadius(m_radius);
    return nodeWidget;
}


/*
 * Translate all TreeNodeWidget on x * m_grid_segment_size.x on x axis
 * on y * m_grid_segment_size.y on y axis
 */
void TreeWidget::translateContentUsingGrid(int x, int y)
{
    auto offset_in_screen_coordinates = sf::Vector2f(x * m_grid_segment_size.x, y * m_grid_segment_size.y);
    for (auto &item: m_nodes) {
        item.translate(offset_in_screen_coordinates);
    }

    for (auto &item: connectionNodesLines) {
        item.first.position += offset_in_screen_coordinates;
        item.second.position += offset_in_screen_coordinates;
    }
}


void TreeWidget::addConnectionsLines(TreeNodeWidget & nodeWidget) {
    auto current_node_position = nodeWidget.getPosition() + sf::Vector2f{m_radius, m_radius};
    sf::Vertex begin_line(current_node_position);
    auto node = nodeWidget.getNode();
    if (node->left) {
        auto left_widget = findWidgetByNode(node->left);
        sf::Vertex end_line(left_widget->getPosition() + sf::Vector2f{m_radius, m_radius});
        Line line = std::make_pair(begin_line, end_line);
        connectionNodesLines.push_back(line);
    }

    if (node->right) {
        auto right_widget = findWidgetByNode(node->right);
        sf::Vertex end_line(right_widget->getPosition() + sf::Vector2f{m_radius, m_radius});
        Line line = std::make_pair(begin_line, end_line);
        connectionNodesLines.push_back(line);
    }
}


void TreeWidget::infixTravesal(Tree * node)
{
    if (node == nullptr)
        return;

    infixTravesal(node->left);

    m_nodes.push_back(infixTravesalCreateNodeWidget(node));

    infixTravesal(node->right);
}


void TreeWidget::fillNodesFromRoot() {
    m_nodes.clear();
    infixTravesal(root);
}

TreeWidget::TreeWidget(Tree * root, const sf::Vector2f &position, const sf::Vector2f & size) : root(root), m_position(position), m_size(size) {
    m_grid_segments_count = getSize();

    auto grid_width  = size.x / m_grid_segments_count.x;
    auto grid_height = size.y / m_grid_segments_count.y;

    m_grid_segment_size = {grid_width, grid_height};

    m_inner_square_size = std::min(grid_height, grid_width);
    m_radius = static_cast<float>(m_inner_square_size) / 2.f;
    fillNodesFromRoot();
}

void TreeWidget::setContentOnCenter() {
    auto offset = emptyColumnsCount() / 2;
    translateContentUsingGrid(offset, 0);
}

int TreeWidget::emptyColumnsCount() {
    int width = getSize().x;
    int used = m_nodes.size();

    return (width - used);
}

void TreeWidget::initConnectionBetweenNodes()
{
    for (auto &nodeWidget: m_nodes) {
        addConnectionsLines(nodeWidget);
    }
}

void TreeWidget::rebuildTree(Tree *new_root) {
    root = new_root;
    m_grid_segments_count = getSize();

    auto grid_width  = m_size.x / m_grid_segments_count.x;
    auto grid_height = m_size.y / m_grid_segments_count.y;

    m_grid_segment_size = {grid_width, grid_height};

    m_inner_square_size = std::min(grid_height, grid_width);
    m_radius = static_cast<float>(m_inner_square_size) / 2.f;
    connectionNodesLines.clear();
    fillNodesFromRoot();
}

TreeNodeWidget *TreeWidget::findWidgetByNode(Tree *node) {
    if (node == nullptr)
        return nullptr;
    for (auto &item: m_nodes) {
        if (item.getNode() == node)
            return &item;
    }
    return nullptr;
}

void TreeWidget::highlight(int key) {
    if (auto node = findNodeByKey(root, key)) {
        if (auto widget = findWidgetByNode(node)) {
            widget->setCircleColor(sf::Color::Cyan);
        }
    }
}

