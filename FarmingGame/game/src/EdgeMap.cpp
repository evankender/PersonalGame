#include "include/edgemap.h"

EdgeMap::EdgeMap()
{
    edgeMap.resize(EDGE_MAP_HEIGHT);
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        edgeMap[r].resize(EDGE_MAP_WIDTH);
        for (int c = 0; c < EDGE_MAP_WIDTH; c++) {
            edgeMap[r][c] = 0;
        }
    }
}

EdgeMap::EdgeMap(Map& map)
{
    this->map = map;
    edgeMap.resize(EDGE_MAP_HEIGHT);
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        edgeMap[r].resize(EDGE_MAP_WIDTH);
        for (int c = 0; c < EDGE_MAP_WIDTH; c++) {
            edgeMap[r][c] = 0;
        }
    }
}

void EdgeMap::SetTile(int x, int y, int val)
{
    this->edgeMap[(y + 1) * 2][(x + 1) * 2] = val;
}

void EdgeMap::UpdateEdge()
{
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        int c = 0;
        bool evenRow = ((r % 2) == 0);

        if (evenRow)
        {
            c = 1;
        }

        for (c; c < EDGE_MAP_WIDTH; c += 2) {
            if (((r != 0) && (c != 0)) && ((r != EDGE_MAP_HEIGHT - 1) && (c != EDGE_MAP_WIDTH - 1)))
            {
                switch (evenRow)
                {
                case false:
                    if (edgeMap[r][c - 1] == edgeMap[r][c + 1]) edgeMap[r][c] = 1;
                    break;
                case true:
                    if (edgeMap[r - 1][c] == edgeMap[r + 1][c]) edgeMap[r][c] = 1;
                    break;
                }
            }
        }
    }
}

void EdgeMap::UpdateCorner()
{
    for (int r = 0; r < EDGE_MAP_HEIGHT; r += 2) {
        for (int c = 0; c < EDGE_MAP_WIDTH; c += 2) {
            if (((r != 0) && (c != 0)) && ((r != EDGE_MAP_HEIGHT - 1) && (c != EDGE_MAP_WIDTH - 1)))
            {

                if (edgeMap[r - 1][c] == edgeMap[r + 1][c] && edgeMap[r - 1][c] == edgeMap[r][c - 1] && edgeMap[r - 1][c] == edgeMap[r][c + 1])
                {
                    edgeMap[r][c] = 1;
                }
                if (edgeMap[r - 1][c - 1] == edgeMap[r + 1][c - 1] && edgeMap[r - 1][c - 1] == edgeMap[r + 1][c + 1] && edgeMap[r - 1][c - 1] == edgeMap[r - 1][c + 1])
                {
                    edgeMap[r][c] = 1;
                }

            }
        }
    }
}