
typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 center;
    float radius;
    float r, g, b;
} Sphere;

kernel void render_scene(
    const int width,
    const int height,
    const Vector3 camPos,
    const Vector3 camDir,
    global Sphere* spheres,
    const int numSpheres,
    global float* pixels
) {
    int x = get_global_id(0);
    int y = get_global_id(1);

    if (x >= width || y >= height) return;

    // Basic ray generation (simplified for proof of concept)
    float u = (float)x / (float)width - 0.5f;
    float v = (float)y / (float)height - 0.5f;
    
    Vector3 rayDir = { camDir.x + u, camDir.y + v, camDir.z };
    float len = sqrt(rayDir.x*rayDir.x + rayDir.y*rayDir.y + rayDir.z*rayDir.z);
    rayDir.x /= len; rayDir.y /= len; rayDir.z /= len;

    float closest_t = 1e20f;
    int closest_sphere = -1;

    for (int i = 0; i < numSpheres; i++) {
        Vector3 oc = { camPos.x - spheres[i].center.x, camPos.y - spheres[i].center.y, camPos.z - spheres[i].center.z };
        float b = 2.0f * (oc.x * rayDir.x + oc.y * rayDir.y + oc.z * rayDir.z);
        float c = (oc.x*oc.x + oc.y*oc.y + oc.z*oc.z) - (spheres[i].radius * spheres[i].radius);
        float disc = b*b - 4.0f*c;

        if (disc >= 0) {
            float t = (-b - sqrt(disc)) / 2.0f;
            if (t > 0.001f && t < closest_t) {
                closest_t = t;
                closest_sphere = i;
            }
        }
    }

    int idx = (y * width + x) * 3;
    if (closest_sphere != -1) {
        pixels[idx] = spheres[closest_sphere].r;
        pixels[idx+1] = spheres[closest_sphere].g;
        pixels[idx+2] = spheres[closest_sphere].b;
    } else {
        pixels[idx] = 0.0f;
        pixels[idx+1] = 0.0f;
        pixels[idx+2] = 0.2f; // Background
    }
}
