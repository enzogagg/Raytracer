
#pragma once

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "Scene.hpp"
#include "Color.hpp"
#include <vector>
#include <string>

class GPURender {
public:
    GPURender(int width, int height);
    ~GPURender();

    bool init();
    void render(Scene &scene, std::vector<Color> &pixels);

private:
    int _width;
    int _height;
    cl_platform_id _platform;
    cl_device_id _device;
    cl_context _context;
    cl_command_queue _queue;
    cl_program _program;
    cl_kernel _kernel;

    std::string loadKernelSource(const std::string &filename);
};
