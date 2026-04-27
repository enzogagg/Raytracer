
#include "GPURender.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

struct GPUSphere {
    float x, y, z;
    float radius;
    float r, g, b;
};

GPURender::GPURender(int width, int height) : _width(width), _height(height) {}

GPURender::~GPURender() {
    if (_kernel) clReleaseKernel(_kernel);
    if (_program) clReleaseProgram(_program);
    if (_queue) clReleaseCommandQueue(_queue);
    if (_context) clReleaseContext(_context);
}

std::string GPURender::loadKernelSource(const std::string &filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool GPURender::init() {
    cl_uint num_platforms;
    clGetPlatformIDs(1, &_platform, &num_platforms);
    clGetDeviceIDs(_platform, CL_DEVICE_TYPE_GPU, 1, &_device, NULL);

    _context = clCreateContext(NULL, 1, &_device, NULL, NULL, NULL);
    
    #ifdef __APPLE__
    _queue = clCreateCommandQueue(_context, _device, 0, NULL);
    #else
    _queue = clCreateCommandQueueWithProperties(_context, _device, NULL, NULL);
    #endif

    std::string source = loadKernelSource("src/core/kernels/raytracer.cl");
    const char *src_ptr = source.c_str();
    size_t src_len = source.length();
    _program = clCreateProgramWithSource(_context, 1, &src_ptr, &src_len, NULL);
    
    if (clBuildProgram(_program, 1, &_device, NULL, NULL, NULL) != CL_SUCCESS) {
        char log[4096];
        clGetProgramBuildInfo(_program, _device, CL_PROGRAM_BUILD_LOG, 4096, log, NULL);
        std::cerr << "OpenCL Build Error: " << log << std::endl;
        return false;
    }

    _kernel = clCreateKernel(_program, "render_scene", NULL);
    return true;
}

void GPURender::render(Scene &scene, std::vector<Color> &pixels) {
    std::vector<GPUSphere> gpuSpheres;
    // Extract spheres from scene (simplified for now)
    // In a real project, we would iterate through primitives and check if they are spheres
    // For this proof of concept, we assume atonium scene has some spheres
    
    // Set arguments
    cl_mem spheres_buf = clCreateBuffer(_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                                        sizeof(GPUSphere) * gpuSpheres.size(), gpuSpheres.data(), NULL);
    cl_mem pixels_buf = clCreateBuffer(_context, CL_MEM_WRITE_ONLY, 
                                       sizeof(float) * _width * _height * 3, NULL, NULL);

    float camPos[3] = { (float)scene.getCamera().getPosition().getX(), (float)scene.getCamera().getPosition().getY(), (float)scene.getCamera().getPosition().getZ() };
    float camDir[3] = { 0, 0, 1 }; // Simplified

    int numSpheres = gpuSpheres.size();
    clSetKernelArg(_kernel, 0, sizeof(int), &_width);
    clSetKernelArg(_kernel, 1, sizeof(int), &_height);
    clSetKernelArg(_kernel, 2, sizeof(float) * 3, camPos);
    clSetKernelArg(_kernel, 3, sizeof(float) * 3, camDir);
    clSetKernelArg(_kernel, 4, sizeof(cl_mem), &spheres_buf);
    clSetKernelArg(_kernel, 5, sizeof(int), &numSpheres);
    clSetKernelArg(_kernel, 6, sizeof(cl_mem), &pixels_buf);

    size_t global_size[2] = { (size_t)_width, (size_t)_height };
    clEnqueueNDRangeKernel(_queue, _kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
    
    std::vector<float> host_pixels(_width * _height * 3);
    clEnqueueReadBuffer(_queue, pixels_buf, CL_TRUE, 0, sizeof(float) * host_pixels.size(), host_pixels.data(), 0, NULL, NULL);

    for (int i = 0; i < _width * _height; i++) {
        pixels[i] = Color(host_pixels[i*3], host_pixels[i*3+1], host_pixels[i*3+2]);
    }

    clReleaseMemObject(spheres_buf);
    clReleaseMemObject(pixels_buf);
}
