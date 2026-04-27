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
                               Math::Vector &lightSource, double distToLight) {
  Math::Point shadow_origin = hit_point + lightSource * 1e-4;
  Ray shadow_ray(shadow_origin, lightSource);

  auto bvh = _scene.getBVH();
  if (!bvh)
    return false;

  double t = distToLight;
  auto hit = bvh->getClosestPrimitive(shadow_ray, t, 1e-4);

  return (hit != nullptr);
}

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator(std::random_device{}());
  return distribution(generator);
}

template <typename T>
static T clampValue(T value, T minimum, T maximum)
{
  return std::max(minimum, std::min(value, maximum));
}

Math::Vector Render::reflect(Math::Vector incident, Math::Vector normal) {
  return incident - 2.0 * incident.dot(normal) * normal;
}

Color Render::ComputePixelColor(std::shared_ptr<IPrimitive> closest_object,
                                const Camera &cam, const Ray &ray, float ao) {
  Math::Point hit_point = closest_object->getIntersection(ray);
  Math::Vector normal = closest_object->normal_at(hit_point);
  Math::Vector viewDir = (cam.getPosition() - hit_point).normalize();

  Color totalDiffuse(0, 0, 0);
  Color totalSpecular(0, 0, 0);
  Color ambientColor(0, 0, 0);

  float materialKa = clampValue(closest_object->getMaterial()->getAmbient(), 0.0f, 1.0f);
  float materialKd = clampValue(closest_object->getMaterial()->getDiffuse(), 0.0f, 1.0f);
  float materialKs = clampValue(closest_object->getMaterial()->getSpecular(), 0.0f, 1.0f);
  float shininess = closest_object->getMaterial()->getShininess();
  if (shininess <= 0) shininess = 32.0f;

  for (const auto &light : _scene.getLights()) {
    if (!light) continue;
    
    Color lightColor = light->getColor() * (1.0 / 255.0);
    float intensity = light->getIntensity();

    if (light->getType() == "ambient") {
      ambientColor = ambientColor + lightColor * (intensity * (1.0 - ao));
      continue;
    }

    Math::Vector lightDir;
    double distToLight = std::numeric_limits<double>::max();

    if (light->getType() == "directional") {
      lightDir = light->getDirection().normalize() * -1.0;
    } else if (light->getType() == "point") {
      Math::Vector toLight = light->getPosition() - hit_point;
      distToLight = toLight.length();
      lightDir = toLight.normalize();
    }

    if (!isInShadowOfShape(hit_point, lightDir, distToLight)) {
      // Diffuse
      float diff = std::max((float)normal.dot(lightDir), 0.0f);
      totalDiffuse = totalDiffuse + lightColor * (diff * intensity * materialKd);

      // Specular (Blinn-Phong)
      Math::Vector halfDir = (lightDir + viewDir).normalize();
      float spec = std::pow(std::max((float)normal.dot(halfDir), 0.0f), shininess);
      totalSpecular = totalSpecular + lightColor * (spec * intensity * materialKs);
    }
  }

  Color modelColor(closest_object->getColor().getR() / 255.0,
                   closest_object->getColor().getG() / 255.0,
                   closest_object->getColor().getB() / 255.0);

  if (closest_object->getMaterial()->getName() != "default" &&
      closest_object->getMaterial()->getName() != "Transparent" &&
      closest_object->getMaterial()->getName() != "Metal") {
    modelColor = closest_object->getMaterial()->getColorAt(hit_point) * (1.0 / 255.0);
  }

  Color result = modelColor * (ambientColor * materialKa + totalDiffuse) + totalSpecular;
  
  return Color(clampValue(result.getR(), 0.0, 1.0),
               clampValue(result.getG(), 0.0, 1.0),
               clampValue(result.getB(), 0.0, 1.0));
}

Color Render::renderReflection(std::shared_ptr<IPrimitive> closest_object,
                               const Ray &ray, Camera &cam,
                               int depthReflection) {
  if (depthReflection <= 0 || !closest_object)
    return Color(0, 0, 0);
  Math::Point hit_point = closest_object->getIntersection(ray);
  Math::Vector viewDir = ray.getDirection() * -1;
  Math::Vector normal = closest_object.get()->normal_at(hit_point);

  if (normal.dot(viewDir) < 0)
    normal = -1 * normal;
  Math::Vector newRayDir =
      ray.getDirection() - normal * 2.0 * ray.getDirection().dot(normal);
  Ray newRay(hit_point + normal * 1e-4, newRayDir);
  Color newPixel(0, 0, 0);
  sendRay(newRay, newPixel, cam, depthReflection - 1, closest_object);
  return newPixel;
}

Color Render::renderRefraction(std::shared_ptr<IPrimitive> closest_object,
                               const Ray &ray, Camera &cam,
                               int depthRefraction) {
  Math::Point hit_point = closest_object->getIntersection(ray);
  Math::Vector viewDir = ray.getDirection() * -1;
  Math::Vector normal = closest_object.get()->normal_at(hit_point);

  double n1 = 1.0;
  double n2 = closest_object.get()->getMaterial().get()->getRefractionIndex();

  // Determine if we are entering or exiting the material
  bool entering = normal.dot(viewDir) > 0;
  if (!entering) {
    std::swap(n1, n2);
    normal = -1 * normal;
  }

  double eta = n1 / n2;
  double cosThetaI =
      -normal.dot(ray.getDirection()); // Angle between normal and ray
  double sinThetaT2 = eta * eta * (1.0 - cosThetaI * cosThetaI);

  if (sinThetaT2 > 1.0) {
    // Total internal reflection
    return renderReflection(closest_object, ray, cam, depthRefraction);
  }

  double cosThetaT = std::sqrt(1.0 - sinThetaT2);
  Math::Vector newRayDir =
      (eta * ray.getDirection()) + (eta * cosThetaI - cosThetaT) * normal;

  // Nudge the ray to avoid self-intersection
  // If entering, nudge inside. If exiting, nudge outside.
  Ray newRay(hit_point - normal * 1e-4, newRayDir);

  Color newPixel(0, 0, 0);
  sendRay(newRay, newPixel, cam, depthRefraction - 1, closest_object);
  return newPixel;
}

inline Math::Vector orthogonalVector(const Math::Vector &normal) {
  if (std::abs(normal.getX()) > std::abs(normal.getZ())) {
    return Math::Vector(-normal.getY(), normal.getX(), 0.0f);
  } else {
    return Math::Vector(0.0f, -normal.getZ(), normal.getY());
  }
}

Math::Vector Render::randomHemisphereDirection(const Math::Vector &normal) {
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
                               Ray &ray) {
  int occluded = 0;
  auto bvh = _scene.getBVH();
  if (!bvh)
    return 0.0f;

  for (int i = 0; i < OCCLUSION_SAMPLE_PX; i++) {
    Math::Point hit_point = closest_object->getIntersection(ray);
    Math::Vector normal = closest_object->normal_at(hit_point);
    Math::Point rayOrigin = hit_point + normal * 1e-4;
    Math::Vector rayDirection = randomHemisphereDirection(normal);
    Ray aoRay(rayOrigin, rayDirection);

    double t = 2.0; // Max occlusion distance
    auto hit = bvh->getClosestPrimitive(aoRay, t, 1e-4);
    if (hit) {
      occluded++;
    }
  }
  return (float(occluded) / float(OCCLUSION_SAMPLE_PX));
}

void Render::sendRay(Ray &ray, Color &pixel, Camera &cam, int depthReflexion,
                     std::shared_ptr<IPrimitive> closest_object) {
  if (depthReflexion <= 0) {
    // Return background gradient even at max depth if no hit
    double t_bg = 0.5 * (ray.getDirection().getY() + 1.0);
    pixel = Color(1.0, 1.0, 1.0) * (1.0 - t_bg) + Color(0.5, 0.7, 1.0) * t_bg;
    pixel = pixel * 0.15;
    return;
  }
  double closest_t = std::numeric_limits<double>::max();

  auto bvh = _scene.getBVH();
  if (bvh) {
    auto hit = bvh->getClosestPrimitive(ray, closest_t, 1e-4);
    if (hit) {
      closest_object = hit;
    } else {
      closest_object = nullptr;
    }
  } else {
    closest_object = nullptr;
  }

  if (closest_object) {
    std::string matName = closest_object->getMaterial()->getName();
    float ao = 0.0f;
    if (depthReflexion == 5) { // Only for primary rays
      ao = AmbiantOcclusion(closest_object, ray);
    }

    if (matName == "Metal" || matName == "metal") {
      Math::Point hit_point = closest_object->getIntersection(ray);
      Math::Vector normal = closest_object->normal_at(hit_point);
      Math::Vector viewDir = (cam.getPosition() - hit_point).normalize();
      float fresnel = 0.04f + 0.96f * std::pow(1.0f - std::max(0.0f, (float)normal.dot(viewDir)), 5.0f);

      Color reflection = renderReflection(closest_object, ray, cam, depthReflexion);
      Color baseLighting = ComputePixelColor(closest_object, cam, ray, ao);
      Color baseColor(closest_object->getColor().getR() / 255.0,
                      closest_object->getColor().getG() / 255.0,
                      closest_object->getColor().getB() / 255.0);

      pixel = reflection * (0.55f + 0.45f * fresnel) + baseLighting * 0.05 + baseColor * 0.02;
    } else if (matName == "Transparent" || matName == "transparent") {
      // Fresnel / Schlick's approximation
      Math::Point hit_point = closest_object->getIntersection(ray);
      Math::Vector normal = closest_object->normal_at(hit_point);
      Math::Vector viewDir = ray.getDirection() * -1;

      double n1 = 1.0;
      double n2 = closest_object->getMaterial()->getRefractionIndex();
      double r0 = std::pow((n1 - n2) / (n1 + n2), 2);
      double cosTheta = std::fmax(0.0, normal.dot(viewDir));
      double fresnel = r0 + (1.0 - r0) * std::pow(1.0 - cosTheta, 5);

      Color reflection =
          renderReflection(closest_object, ray, cam, depthReflexion);
      Color refraction =
          renderRefraction(closest_object, ray, cam, depthReflexion);

      // Base color tint (Green from config, normalized to 0-1)
      Color baseColor(closest_object->getColor().getR() / 255.0,
                      closest_object->getColor().getG() / 255.0,
                      closest_object->getColor().getB() / 255.0);

      // Mix: reflections on edges, refraction in center, tinted by object color
      pixel = reflection * fresnel +
              (refraction * 0.8 + baseColor * 0.2) * (1.0 - fresnel);

      // Add specular highlights (subtle)
      Color lighting = ComputePixelColor(closest_object, cam, ray, ao);
      pixel = pixel + lighting * 0.3;
    } else {
      pixel = ComputePixelColor(closest_object, cam, ray, ao);
    }
  } else {
    // Subtle background gradient instead of pitch black
    double t = 0.5 * (ray.getDirection().getY() + 1.0);
    pixel = Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.5, 0.7, 1.0) * t;
    pixel = pixel * 0.15; // Keep it dark but not black
  }

  // Final clamp to 0-1 range
  pixel.setColor(clampValue(pixel.getR(), 0.0, 1.0),
                 clampValue(pixel.getG(), 0.0, 1.0),
                 clampValue(pixel.getB(), 0.0, 1.0));
}

static bool colorsAreSimilar(const Color &c1, const Color &c2, const Color &c3,
                             const Color &c4) {
  double dr = std::abs(c1.getR() - c2.getR()) +
              std::abs(c1.getR() - c3.getR()) + std::abs(c1.getR() - c4.getR());
  double dg = std::abs(c1.getG() - c2.getG()) +
              std::abs(c1.getG() - c3.getG()) + std::abs(c1.getG() - c4.getG());
  double db = std::abs(c1.getB() - c2.getB()) +
              std::abs(c1.getB() - c3.getB()) + std::abs(c1.getB() - c4.getB());
  return (dr + dg + db) < 0.15;
}

Color Render::adaptiveSample(double x0, double y0, double x1, double y1,
                             int maxWidth, int maxHeight, int depth) {
  auto sample = [&](double px, double py) -> Color {
    double u = px / (maxWidth - 1);
    double v = py / (maxHeight - 1);
    int depthReflexion = 5;
    Camera cam = _scene.getCamera();
    cam.setRay(u, v);
    Ray ray = cam.getRay();
    std::shared_ptr<IPrimitive> closest_object = nullptr;
    Color result(0, 0, 0);

    sendRay(ray, result, cam, depthReflexion, closest_object);
    return result;
  };
  Color c00 = sample(x0, y0);
  Color c10 = sample(x1, y0);
  Color c01 = sample(x0, y1);
  Color c11 = sample(x1, y1);
  Color cCenter = sample((x0 + x1) / 2, (y0 + y1) / 2);
  if (depth >= 2 || colorsAreSimilar(c00, c10, c01, c11)) {
    return (c00 + c10 + c01 + c11 + cCenter) * 0.2;
  } else {
    double mx = (x0 + x1) / 2;
    double my = (y0 + y1) / 2;
    Color q00 = adaptiveSample(x0, y0, mx, my, maxWidth, maxHeight, depth + 1);
    Color q10 = adaptiveSample(mx, y0, x1, my, maxWidth, maxHeight, depth + 1);
    Color q01 = adaptiveSample(x0, my, mx, y1, maxWidth, maxHeight, depth + 1);
    Color q11 = adaptiveSample(mx, my, x1, y1, maxWidth, maxHeight, depth + 1);
    return (q00 + q10 + q01 + q11) * 0.25;
  }
}

Color Render::renderPixel(int x, int y, int maxWidth, int maxHeight) {
  return adaptiveSample(x, y, x + 1, y + 1, maxWidth, maxHeight, 0);
}
