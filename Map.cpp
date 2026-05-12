#include "Map.h"
Map::Map() : path_count(0), grassColor(sf::Color(34, 139, 34)), pathColor(sf::Color(180, 150, 90))
{
    for (int r = 0; r < map_rows; r++)     //initializing all tiles with grass (0)
    {
        for (int c = 0; c < map_cols; c++)
        {
            grid[r][c] = 0;
        }
    }
    buildPath();
}
Map::~Map()
{
}
void Map::buildPath()
{
    //S-shaped path definition: list of (row, col) pairs
    //top row right, turn down, left, down, right to exit
    int pathTiles[][2] = {
        //row 1: col 0->9 (going right)
        {1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},
        //col 9: row 1->6 (going down)
        {2,9},{3,9},{4,9},{5,9},{6,9},
        //row 6: col 9->1 (going left)
        {6,8},{6,7},{6,6},{6,5},{6,4},{6,3},{6,2},
        //col 1: row 6->11 (going down)
        {7,2},{8,2},{9,2},{10,2},{11,2},
        //row 11: col 1->18 (going right towards exit)
        {11,2},{11,3},{11,4},{11,5},{11,6},{11,7},{11,8},{11,9},{11,10},{11,11},{11,12},{11,13},{11,14},{11,15},
        {11,16},{11,17},{11,18},{11,19}
    };
    int count = sizeof(pathTiles) / sizeof(pathTiles[0]);      //gives number of tiles
    path_count = count;
    for (int i = 0; i < count; i++)
    {
        int r = pathTiles[i][0];
        int c = pathTiles[i][1];
        grid[r][c] = 1;
        pathX[i] = c * tile_size + tile_size / 2.0f;
        pathY[i] = r * tile_size + tile_size / 2.0f;
    }
}
bool Map::is_path(int row, int col) const 
{
    if (row < 0 || row >= map_rows || col < 0 || col >= map_cols)
    {
        return false;
    }
    return grid[row][col] == 1;
}
bool Map::is_placeable(int row, int col) const 
{
    if (row < 0 || row >= map_rows || col < 0 || col >= map_cols)
    {
        return false;
    }
    return grid[row][col] == 0;
}
void Map::setOccupied(int row, int col)
{
    if (row >= 0 && row < map_rows && col >= 0 && col < map_cols)
    {
        grid[row][col] = 2;
    }
}
int Map::get_PathCount() const
{
    return path_count; 
}
float Map::get_PathX(int index) const
{
    return pathX[index]; 
}
float Map::get_PathY(int index) const
{
    return pathY[index]; 
}
int Map::pixelToRow(float py) const
{
    return (int)(py / tile_size); 
}
int Map::pixelToCol(float px) const 
{
    return (int)(px / tile_size); 
}
float Map::tileCenterX(int col) const 
{
    return col * tile_size + tile_size / 2.0f; 
}
float Map::tileCenterY(int row) const 
{
    return row * tile_size + tile_size / 2.0f; 
}
void Map::render(sf::RenderWindow& window) 
{
    sf::RectangleShape tile(sf::Vector2f(tile_size - 0.5, tile_size - 0.5));
    for (int r = 0; r < map_rows; r++)
    {
        for (int c = 0; c < map_cols; c++) 
        {
            tile.setPosition(c * tile_size, r * tile_size);
            if (grid[r][c] == 1)
            {
                tile.setFillColor(pathColor);
            }
            else
            {
                tile.setFillColor(grassColor);
            }
            window.draw(tile);
        }
    }
    sf::RectangleShape line(sf::Vector2f(5.f, 49.f));
    line.setPosition(0, 49);
    line.setFillColor(sf::Color::Yellow);
    window.draw(line);

    sf::RectangleShape line2(sf::Vector2f(5.f, 49.f)); 
    line2.setPosition(974, 539);
    line2.setFillColor(sf::Color::Red);
    window.draw(line2);
}