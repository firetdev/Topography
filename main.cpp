#include <iostream>
#include <vector>
#include <random>

int main() {
    std::vector<std::vector<float>> current_map = {};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int r = 0; r < 100; ++r) {
        std::vector<float> row;
        for (int c = 0; c < 100; ++c) {
            row.push_back(dis(gen));
        }
        current_map.push_back(row);
    }

    int iterations = 10;

    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<std::vector<float>> new_map = current_map;

        for (int r = 0; r < 100; ++r) {
            for (int c = 0; c < 100; ++c) {
                float sum = 0.0f;
                int count = 0;

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < 100 && nc >= 0 && nc < 100) {
                            sum += current_map[nr][nc];
                            count++;
                        }
                    }
                }

                new_map[r][c] = sum / count;
            }
        }

        current_map = new_map;
    }

    for (const auto& row : current_map) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}