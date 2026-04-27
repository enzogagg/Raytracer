
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
    cl_int err = clGetPlatformIDs(1, &_platform, &num_platforms);
    if (err != CL_SUCCESS) return false;

    err = clGetDeviceIDs(_platform, CL_DEVICE_TYPE_ALL, 1, &_device, NULL);
    if (err != CL_SUCCESS) return false;

    char deviceName[128];
    clGetDeviceInfo(_device, CL_DEVICE_NAME, 128, deviceName, NULL);
    std::cout << "[GPU] Using device: " << deviceName << std::endl;

    _context = clCreateContext(NULL, 1, &_device, NULL, NULL, &err);
    if (err != CL_SUCCESS) return false;
    
    #ifdef __APPLE__
    _queue = clCreateCommandQueue(_context, _device, 0, &err);
    #else
    _queue = clCreateCommandQueueWithProperties(_context, _device, NULL, &err);
    #endif
    if (err != CL_SUCCESS) return false;

    std::string source = loadKernelSource("src/core/kernels/raytracer.cl");
    const char *src_ptr = source.c_str();
    size_t src_len = source.length();
    _program = clCreateProgramWithSource(_context, 1, &src_ptr, &src_len, &err);
    
    err = clBuildProgram(_program, 1, &_device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char log[4096];
        clGetProgramBuildInfo(_program, _device, CL_PROGRAM_BUILD_LOG, 4096, log, NULL);
        std::cerr << "[GPU] Kernel Build Error: " << log << std::endl;
        return false;
    }

    _kernel = clCreateKernel(_program, "render_scene", &err);
    return err == CL_SUCCESS;
}

void GPURender::render(Scene &scene, std::vector<Color> &pixels) {
    std::vector<GPUSphere> gpuSpheres;
    
    for (const auto &primitive : scene.getPrimitives()) {
        if (primitive->getType() == "sphere") {
            GPUSphere s;
            auto bbox = primitive->getBoundingBox();
            s.x = (bbox.min().getX() + bbox.max().getX()) / 2.0f;
            s.y = (bbox.min().getY() + bbox.max().getY()) / 2.0f;
            s.z = (bbox.min().getZ() + bbox.max().getZ()) / 2.0f;
            s.radius = (bbox.max().getX() - bbox.min().getX()) / 2.0f;
            s.r = primitive->getColor().getR();
            s.g = primitive->getColor().getG();
            s.b = primitive->getColor().getB();
            gpuSpheres.push_back(s);
        }
    }

    if (gpuSpheres.empty()) {
        std::fill(pixels.begin(), pixels.end(), Color(0, 0, 1)); // Blue if no spheres
        return;
    }

    if (gpuSpheres.size() > 0) {
        static bool logged = false;
        if (!logged) {
            std::cout << "[GPU] First Sphere: pos(" << gpuSpheres[0].x << "," << gpuSpheres[0].y << "," << gpuSpheres[0].z << ") r=" << gpuSpheres[0].radius << std::endl;
            logged = true;
        }
    }

    cl_int err;
    cl_mem spheres_buf = clCreateBuffer(_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                                        sizeof(GPUSphere) * gpuSpheres.size(), gpuSpheres.data(), &err);
    cl_mem pixels_buf = clCreateBuffer(_context, CL_MEM_WRITE_ONLY, 
                                       sizeof(float) * _width * _height * 3, NULL, &err);

    float camPosX = (float)scene.getCamera().getPosition().getX();
    float camPosY = (float)scene.getCamera().getPosition().getY();
    float camPosZ = (float)scene.getCamera().getPosition().getZ();
    
    float camDirX = 0.0f;
    float camDirY = 0.0f;
    float camDirZ = 1.0f; 

    int numSpheres = gpuSpheres.size();
    clSetKernelArg(_kernel, 0, sizeof(int), &_width);
    clSetKernelArg(_kernel, 1, sizeof(int), &_height);
    clSetKernelArg(_kernel, 2, sizeof(float), &camPosX);
    clSetKernelArg(_kernel, 3, sizeof(float), &camPosY);
    clSetKernelArg(_kernel, 4, sizeof(float), &camPosZ);
    clSetKernelArg(_kernel, 5, sizeof(float), &camDirX);
    clSetKernelArg(_kernel, 6, sizeof(float), &camDirY);
    clSetKernelArg(_kernel, 7, sizeof(float), &camDirZ);
    clSetKernelArg(_kernel, 8, sizeof(cl_mem), &spheres_buf);
    clSetKernelArg(_kernel, 9, sizeof(int), &numSpheres);
    clSetKernelArg(_kernel, 10, sizeof(cl_mem), &pixels_buf);

    size_t global_size[2] = { (size_t)_width, (size_t)_height };
    err = clEnqueueNDRangeKernel(_queue, _kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        std::cerr << "[GPU] Execution Error: " << err << std::endl;
    }

    clFinish(_queue);
    
    std::vector<float> host_pixels(_width * _height * 3);
    clEnqueueReadBuffer(_queue, pixels_buf, CL_TRUE, 0, sizeof(float) * host_pixels.size(), host_pixels.data(), 0, NULL, NULL);

    for (int i = 0; i < _width * _height; i++) {
        pixels[i] = Color(host_pixels[i*3], host_pixels[i*3+1], host_pixels[i*3+2]);
    }

    clReleaseMemObject(spheres_buf);
    clReleaseMemObject(pixels_buf);
}
