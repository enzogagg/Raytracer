
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

    // Basic Plane (y = -1)
    float t_plane = (-1.0f - camPos.y) / rayDir.y;
    if (t_plane > 0.001f && t_plane < closest_t) {
        closest_t = t_plane;
        closest_sphere = -2; // Marker for plane
    }

    int idx = (y * width + x) * 3;
    if (closest_sphere == -2) {
        // Simple checkerboard for plane
        float hit_x = camPos.x + rayDir.x * closest_t;
        float hit_z = camPos.z + rayDir.z * closest_t;
        int checkers = ((int)(floor(hit_x)) + (int)(floor(hit_z))) & 1;
        float col = checkers ? 0.3f : 0.1f;
        pixels[idx] = col; pixels[idx+1] = col; pixels[idx+2] = col;
    } else if (closest_sphere != -1) {
        // Simple diffuse lighting
        Vector3 hitPoint = { camPos.x + rayDir.x * closest_t, camPos.y + rayDir.y * closest_t, camPos.z + rayDir.z * closest_t };
        Vector3 normal = { hitPoint.x - spheres[closest_sphere].center.x, hitPoint.y - spheres[closest_sphere].center.y, hitPoint.z - spheres[closest_sphere].center.z };
        float n_len = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
        normal.x /= n_len; normal.y /= n_len; normal.z /= n_len;
        
        Vector3 lightDir = { 0.5f, 0.7f, -0.5f }; // Hardcoded light
        float diff = max(0.1f, normal.x*lightDir.x + normal.y*lightDir.y + normal.z*lightDir.z);

        // Specular
        Vector3 viewDir = { -rayDir.x, -rayDir.y, -rayDir.z };
        Vector3 halfDir = { lightDir.x + viewDir.x, lightDir.y + viewDir.y, lightDir.z + viewDir.z };
        float h_len = sqrt(halfDir.x*halfDir.x + halfDir.y*halfDir.y + halfDir.z*halfDir.z);
        halfDir.x /= h_len; halfDir.y /= h_len; halfDir.z /= h_len;
        float spec = pow(max(0.0f, normal.x*halfDir.x + normal.y*halfDir.y + normal.z*halfDir.z), 32.0f);

        pixels[idx] = spheres[closest_sphere].r * diff + spec * 0.5f;
        pixels[idx+1] = spheres[closest_sphere].g * diff + spec * 0.5f;
        pixels[idx+2] = spheres[closest_sphere].b * diff + spec * 0.5f;
    } else {
        // Gradient background (Magenta to Blue)
        float t = (rayDir.y + 1.0f) * 0.5f;
        pixels[idx] = (1.0f - t); // R
        pixels[idx+1] = 0.0f;     // G
        pixels[idx+2] = 1.0f;     // B
    }
}
