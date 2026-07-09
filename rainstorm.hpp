#pragma once

#include <vector>
#include <random>

// Simulate rain erosion
std::vector<std::vector<float>> rainstorm(std::vector<std::vector<float>> map) {
    // Choose random region for rainstorm
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> map_height_dis(0, map.size() - 1);
    std::uniform_int_distribution<int> map_width_dis(0, map[0].size() - 1);
    // Region size is between 1/10 and 2/3 of the map size
    std::uniform_int_distribution<int> area_dis(std::min(map.size(), map[0].size()) / 10, std::min(map.size(), map[0].size()) / 1.5);

    std::vector<int> region = {map_height_dis(gen), map_width_dis(gen), area_dis(gen), area_dis(gen)};
    if (region[0] + region[2] >= map.size()) {
        region[2] = map.size() - region[0] - 1;
    }
    if (region[1] + region[3] >= map[0].size()) {
        region[3] = map[0].size() - region[1] - 1;
    }

    // Create Y random rain positions within the region
    std::vector<std::vector<int>> rain_positions;
    int active_rain_cells = 500;
    
    std::uniform_int_distribution<int> x_dist(region[0], region[0] + region[2] - 1);
    std::uniform_int_distribution<int> y_dist(region[1], region[1] + region[3] - 1);

    for (int i = 0; i < active_rain_cells; ++i) {
        int x = x_dist(gen);
        int y = y_dist(gen);
        rain_positions.push_back({x, y});
    }

    while (active_rain_cells > 0) {
        for (auto& pos : rain_positions) {
            int x = pos[0];
            int y = pos[1];
            if (map[x][y] > 0.03f) {
                map[x][y] -= 0.03f;  // Erode the terrain at the rain position
            }

            // Make rain flow to lowest neighboring cell
            std::vector<int> lowest = {x, y};

            // Get positions of neighboring cells (including diagonals)
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
                        if (map[nx][ny] < map[lowest[0]][lowest[1]]) {
                            lowest = {nx, ny};
                        }
                    }
                }
            }

            // If the lowest neighbor is lower than the current cell, flow water to it
            if (map[lowest[0]][lowest[1]] < map[x][y]) {
                pos = lowest;
            } else {
                active_rain_cells--;
            }
        }
    }

    return map;
}