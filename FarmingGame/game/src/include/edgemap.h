#include "raylib.h"
#include <vector>
#include "include/map.h"

class EdgeMap {
public:
    EdgeMap();
    EdgeMap(Map& map);
    void SetTile(int x, int y, int val);
    void UpdateEdge();
    void UpdateCorner();
private:
    std::vector<std::vector<int>> edgeMap;
    Map map;
};