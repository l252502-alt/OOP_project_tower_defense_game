#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
const int map_cols = 20;
const int map_rows = 15;
const int tile_size = 49;
const int path_length = 46;    //number of checkpoints on the path
class Map 
{
private:
    int grid[map_rows][map_cols];
    float pathX[path_length];
    float pathY[path_length];
    int path_count;
    sf::Color grassColor;
    sf::Color pathColor;
    void buildPath();
public:
    Map();
    ~Map();
    bool is_path(int row, int col) const;
    bool is_placeable(int row, int col) const;
    void setOccupied(int row, int col);
    int get_PathCount() const;
    float get_PathX(int index) const;
    float get_PathY(int index) const;
    int pixelToRow(float py) const;
    int pixelToCol(float px) const;
    float tileCenterX(int col) const;
    float tileCenterY(int row) const;
    void render(sf::RenderWindow& window);
};
#endif