/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** CalculateRender
*/

/**
 * @file CalculateRender.cpp
 * @brief Render class implementation file.
 * @details This file contains the implementation of the methods
 *     used to calculate the render of the scene in the raytracer project.
 */
#include "Render.hpp"


bool Render::isInShadowOfShape(Math::Point &hit_point,
    std::shared_ptr<IPrimitive> closest_object, Math::Vector &lightSource)
{
    Math::Point shadow_origin = hit_point + lightSource * 1e-4;

    Ray shadow_ray(shadow_origin, lightSource);

    for (const auto& primitive : _scene.getPrimitives()) {
        if (!primitive) continue;
        if (primitive == closest_object)
            continue;
        if (primitive->intersect(shadow_ray)) {
            Math::Point shadow_hit = primitive->getIntersection(shadow_ray);
            Math::Point pointFromShadow = shadow_hit - lightSource;
            Math::Point pointFromHit = hit_point - lightSource;
            double distFromShadowToLight = sqrt(
                pointFromShadow.getX() * pointFromShadow.getX() +
                pointFromShadow.getY() * pointFromShadow.getY() +
                pointFromShadow.getZ() * pointFromShadow.getZ()
            );
            double distFromHitToLight = sqrt(
                pointFromHit.getX() * pointFromHit.getX() +
                pointFromHit.getY() * pointFromHit.getY() +
                pointFromHit.getZ() * pointFromHit.getZ()
            );
            if (distFromShadowToLight > distFromHitToLight)
                return false;
            return true;
        }
    }
    return false;
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

Math::Vector Render::reflect(Math::Vector incident, Math::Vector normal)
{
    return incident - 2.0 * incident.dot(normal) * normal;
}

Color Render::ComputeSpecularLight(Math::Vector &lightSource,
    Math::Vector normal, const Camera &cam, const std::shared_ptr<ILight> &light,
    float specularIntensity)
{
    Color lightColor = Color(
        light.get()->getColor().getR() / 255,
        light.get()->getColor().getG() / 255,
        light.get()->getColor().getB() / 255
    );
    Math::Vector cameraSource = cam.getRay().getDirection();
    Math::Vector viewSource = cameraSource.normalize();
    Math::Vector reflectSource = reflect(lightSource, normal).normalize();
    specularIntensity = std::fmax(0.0, viewSource.dot(reflectSource));
    specularIntensity = std::pow(specularIntensity, 32.0);
    return lightColor * specularIntensity;
}

Color Render::ComputeDiffuseLights(const std::shared_ptr<ILight> &light,
    float diffuseStrength)
{
    Color lightColor = Color(
        light.get()->getColor().getR() / 255,
        light.get()->getColor().getG() / 255,
        light.get()->getColor().getB() / 255
    );
    return lightColor * diffuseStrength;
}

Color Render::ComputePixelColor(std::shared_ptr<IPrimitive> closest_object, const Camera& cam, const Ray& ray, int ao)
{
    Color ambient;
    Color diffuse;
    Color specular;
    Math::Vector lightSource;
    Math::Point hit_point = closest_object->getIntersection(ray);
    Math::Vector normal = closest_object->normal_at(hit_point);
    float ambientIntensity = 1.f;
    float diffuseIntensity = 1.f;
    float specularIntensity = 1.f;

    for (const auto &light: _scene.getLights()) {
        if (!light) continue;
        if (light->getType() == "ambient") {
            ambient = light.get()->getColor() * (1 - ao);
            ambientIntensity = light.get()->getIntensity();
        } else {
            if (light->getType() == "directional") {
                lightSource = light.get()->getDirection();
            } else if (light->getType() == "point") {
                Math::Point lightPos = light.get()->getPosition();
                lightSource = (lightPos - hit_point).normalize();
            }
            diffuseIntensity = light.get()->getIntensity();
            if (isInShadowOfShape(hit_point, closest_object, lightSource)) {
                diffuseIntensity *= 0.2;
                specularIntensity = 0.f;
            }
            float diffuseStrength = std::fmax(0.0f, lightSource.dot(normal));
            diffuse = ComputeDiffuseLights(light, diffuseStrength);
            specular = ComputeSpecularLight(lightSource, normal, cam, light, specularIntensity);
        }
    }
    Color modelColor = Color(255, 255, 255);
    Color lighting = ambient * ambientIntensity + diffuse * 0.6 * diffuseIntensity + specular * specularIntensity;
    if (closest_object.get()->getMaterial().get()->getName() != "default") {
       modelColor = closest_object.get()->getMaterial().get()->getColorAt(hit_point) / 255;
    } else {
        modelColor.setColor(closest_object->getColor().getR() / 255,
            closest_object->getColor().getG() / 255, closest_object->getColor().getB() / 255);
    }
    return modelColor * lighting;
}

Color Render::renderReflection(std::shared_ptr<IPrimitive> closest_object,
    const Ray &ray, Camera &cam, int depthReflection)
{
    if (depthReflection <= 0 || !closest_object)
        return Color(0, 0, 0);
    Math::Point hit_point = closest_object->getIntersection(ray);
    Math::Vector viewDir = ray.getDirection() * -1;
    Math::Vector normal = closest_object.get()->normal_at(hit_point);

    if (normal.dot(viewDir) < 0)
        normal = -1 * normal;
    Math::Vector newRayDir = ray.getDirection() - normal * 2.0 * ray.getDirection().dot(normal);
    Ray newRay(hit_point + normal * 1e-2, newRayDir);
    Color newPixel(0, 0, 0);
    sendRay(newRay, newPixel, cam, depthReflection - 1, closest_object);
    return newPixel;
}

Color Render::renderRefraction(std::shared_ptr<IPrimitive> closest_object,
    const Ray &ray, Camera &cam, int depthRefraction)
{
    Math::Point hit_point = closest_object->getIntersection(ray);
    Math::Vector viewDir = ray.getDirection() * -1;
    Math::Vector normal = closest_object.get()->normal_at(hit_point);

    if (normal.dot(viewDir) < 0)
        normal = -1 * normal;
    double n1 = 1.0;
    double n2 = closest_object.get()->getMaterial().get()->getRefractionIndex();
    double eta = n1 / n2;
    double cosThetaI = -normal.dot(viewDir);
    double sinThetaT2 = eta * eta * (1.0 - cosThetaI * cosThetaI);
    if (sinThetaT2 > 1.0)
        return Color(0, 0, 0);
    double cosThetaT = std::sqrt(1.0 - sinThetaT2);
    Math::Vector newRayDir = (eta * viewDir) + (eta * cosThetaI - cosThetaT) * normal;
    Ray newRay(hit_point + normal * 1e-2, newRayDir);
    Color newPixel(0, 0, 0);
    sendRay(newRay, newPixel, cam, depthRefraction - 1, closest_object);
    return newPixel;
}

inline Math::Vector orthogonalVector(const Math::Vector& normal)
{
    if (std::abs(normal.getX()) > std::abs(normal.getZ())) {
        return Math::Vector(-normal.getY(), normal.getX(), 0.0f);
    } else {
        return Math::Vector(0.0f, -normal.getZ(), normal.getY());
    }
}

Math::Vector Render::randomHemisphereDirection(const Math::Vector& normal)
{
    float r = sqrt(random_double());
    float theta = 2.0f * M_PI * random_double();

    float x = r * cos(theta);
    float y = r * sin(theta);
    float z = sqrt(1.0f - x * x - y * y);

    Math::Vector tangent = orthogonalVector(normal).normalize();
    Math::Vector bitangent = normal.crossProduct(tangent);
    Math::Vector direction = x * tangent + y * bitangent + z * normal;
    return direction.normalize();
}

float Render::AmbiantOcclusion(std::shared_ptr<IPrimitive> closest_object,
    Ray &ray)
{
    int occluded = 0;
    for (int i = 0; i < OCCLUSION_SAMPLE_PX; i++) {
        Math::Point hit_point = closest_object->getIntersection(ray);
        Math::Vector normal = closest_object->normal_at(hit_point);
        Math::Point rayOrigin = hit_point + normal * 1e-4;
        Math::Vector rayDirection = randomHemisphereDirection(normal);
        Ray aoRay(rayOrigin, rayDirection);
        for (const auto &primitive : _scene.getPrimitives()) {
            if (primitive == closest_object)
                continue;
            if (primitive->intersect(aoRay) && (primitive->getIntersection(ray) - aoRay.getOrigin()).length() < 2.0) {
                occluded++;
                break;
            }
        }
    }
    return (float(occluded) / float(OCCLUSION_SAMPLE_PX));
}

void Render::sendRay(Ray &ray, Color &pixel,
    Camera &cam, int depthReflexion, std::shared_ptr<IPrimitive> closest_object)
{
    if (depthReflexion == 0)
        return;
    double closest_t = std::numeric_limits<double>::max();

    for (const auto &primitive : _scene.getPrimitives()) {
        if (primitive == closest_object)
            continue;
        if (primitive->intersect(ray)) {
            Math::Point hit_point = primitive->getIntersection(ray);
            double t = (hit_point - ray.getOrigin()).length();
            if (t > 1e-6 && t < closest_t) {
                closest_t = t;
                closest_object = primitive;
            }
        }
    }
    if (closest_object) {
        float ao = AmbiantOcclusion(closest_object, ray); // --> Comment to make the program faster
        if (closest_object.get()->getMaterial().get()->getName() == "metal") {
            pixel = renderReflection(closest_object, ray, cam, depthReflexion);
        } else if (closest_object->getMaterial()->getName() == "Transparent") {
            pixel = renderRefraction(closest_object, ray, cam, depthReflexion);
        } else {
            pixel += ComputePixelColor(closest_object, cam, ray, ao);
        }
        pixel /= 2;
    } else {
        pixel += BACKGROUNDCOLOR;
    }
    return;
}

static bool colorsAreSimilar(const Color& c1, const Color& c2, const Color& c3, const Color& c4)
{
    double dr = std::abs(c1.getR() - c2.getR()) + std::abs(c1.getR() - c3.getR()) + std::abs(c1.getR() - c4.getR());
    double dg = std::abs(c1.getG() - c2.getG()) + std::abs(c1.getG() - c3.getG()) + std::abs(c1.getG() - c4.getG());
    double db = std::abs(c1.getB() - c2.getB()) + std::abs(c1.getB() - c3.getB()) + std::abs(c1.getB() - c4.getB());
    return (dr + dg + db) < COLOR_THRESHOLD;
}

Color Render::adaptiveSample(double x0, double y0, double x1, double y1, int maxWidth, int maxHeight, int depth)
{
    auto sample = [&](double px, double py) -> Color
    {
        double u = px / (maxWidth - 1);
        double v = py / (maxHeight - 1);
        int depthReflexion = 5;
        Camera cam = _scene.getCamera();
        cam.setRay(u, v);
        Ray ray = cam.getRay();
        std::shared_ptr<IPrimitive> closest_object = nullptr;
        Color result = BACKGROUNDCOLOR;

        sendRay(ray, result, cam, depthReflexion, closest_object);
        result.setColor(
            std::clamp(result.getR(), 0.0, 1.0),
            std::clamp(result.getG(), 0.0, 1.0),
            std::clamp(result.getB(), 0.0, 1.0)
        );
        return result;
    };
    Color c00 = sample(x0, y0);
    Color c10 = sample(x1, y0);
    Color c01 = sample(x0, y1);
    Color c11 = sample(x1, y1);
    Color cCenter = sample((x0 + x1) / 2, (y0 + y1) / 2);
    if (depth >= MAX_DEPTH || colorsAreSimilar(c00, c10, c01, c11)) {
        return (((((((c00 + c10) / 2) + c01) / 2) + c11) / 2) + cCenter) / 2;
    } else {
        double mx = (x0 + x1) / 2;
        double my = (y0 + y1) / 2;
        return (
            (((((adaptiveSample(x0, y0, mx, my, maxWidth, maxHeight, depth + 1) +
            adaptiveSample(mx, y0, x1, my, maxWidth, maxHeight, depth + 1)) / 2) +
            adaptiveSample(x0, my, mx, y1, maxWidth, maxHeight, depth + 1)) / 2) +
            adaptiveSample(mx, my, x1, y1, maxWidth, maxHeight, depth + 1)) / 2
        );
    }
}

Color Render::renderPixel(int x, int y, int maxWidth, int maxHeight)
{
    return adaptiveSample(x, y, x + 1, y + 1, maxWidth, maxHeight, 0);
}
