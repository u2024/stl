#pragma once
#include <vector>
#include <utility>
#include <array>
#include <cstdint>
#include <cstddef>

constexpr size_t width = 32;
constexpr size_t height = 32;
std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> &vec);
std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& array);
