/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Define
*/

#define FAST_RENDER_RATIO 0.15
#define THREADS_NUMBER 36
#define RENDER_COLOMNS_DIVISION_PIXEL 20
#define FONT "./ressources/BebasNeue-Regular.ttf"
#define BACKGROUNDCOLOR Color(0, 0, 0)
#define OCCLUSION_SAMPLE_PX 8

#define TRANSLATE_X "Translate X"
#define TRANSLATE_Y "Translate Y"
#define TRANSLATE_Z "Translate Z"
#define ROTATE_X "Rotate X"
#define ROTATE_Y "Rotate Y"
#define ROTATE_Z "Rotate Z"

#define MAX_DEPTH 3
#define COLOR_THRESHOLD 0.10

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <functional>
#include <filesystem>
#include <dlfcn.h>
#include <queue>
#include <random>
#include <chrono>
#include <fstream>
#include <array>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <SFML/Graphics.hpp>

#include <libconfig.h++>
