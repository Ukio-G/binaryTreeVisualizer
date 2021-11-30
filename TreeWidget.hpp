#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Tree.hpp"
#include "TreeNodeWidget.hpp"


class TreeWidget : public sf::Drawable {
public:
    TreeWidget(Tree *root, const sf::Vector2f &position, const sf::Vector2f &size);
    enum NodePath { Left, Right };
    const sf::Vector2f &getPosition() const;
    void setPosition(const sf::Vector2f &position);

    void drawSegments(sf::RenderWindow &window);
    void translateContentUsingGrid(int x, int y);

    void setContentOnCenter();
    void rebuildTree(Tree * root);

    void initConnectionBetweenNodes();

    void highlight(int key);

private:
    Tree * root;
    float m_radius = 10.f;
    using Line = std::pair<sf::Vertex,sf::Vertex>;
    /*
     * m_size - Widget's size in pixels
     */
    sf::Vector2f m_size;

    /*
     * m_grid_segments_count - Count of segments by x and y.
     * Segment - a rectangle that splits the widget into equal parts
     */
    sf::Vector2f m_grid_segments_count;

    /*
     * m_grid_segment_size - Size in pixels of one segment
     */
    sf::Vector2f m_grid_segment_size;

    /*
     * m_inner_square_size - Size of maximum inscribed square of segment
     */
    unsigned int m_inner_square_size;

    // std::vector<sf::CircleShape> m_nodes;
    std::vector<TreeNodeWidget> m_nodes;
    std::vector<Line> gridLines;
    std::vector<Line> connectionNodesLines;

    /*
     * m_position - Widget position
     */
    sf::Vector2f m_position = {0, 0};

    /*
     * m_color - Color of circles (btree nodes visual representation)
     */
    sf::Color m_color = {0, 255, 0};
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2f getSize();

    sf::Vector2f getPositionSquareInGrid(unsigned int x, unsigned int y);

    sf::Vector2f getGridSegmentByPath(std::vector<NodePath> &path);

    void fillNodesFromRoot();

    void infixTravesal(Tree *node);

    TreeNodeWidget infixTravesalCreateNodeWidget(Tree *node);

    int emptyColumnsCount();

    void addConnectionsLines(TreeNodeWidget &nodeWidget);

    TreeNodeWidget * findWidgetByNode(Tree * node);
};


#endif
