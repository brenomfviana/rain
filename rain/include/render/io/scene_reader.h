#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <tuple>
#include <list>
#include <string>
#include <typeinfo>
#include <vector>
#include "output_settings.h"
#include "render/shader/shader.h"
#include "scene/scene.h"
#include "scene/camera/camera.h"
#include "scene/components/light/light.h"
#include "scene/components/background.h"
#include "scene/components/shape/shape.h"
#include "scene/components/shape/sphere.h"
#include "scene/components/shape/materials/material.h"
#include "scene/components/shape/materials/texture.h"
#include "vec3.h"
#include "transformation.h"

using namespace utils;

/*!
 * This class is responsible for reading the scene description.
 */
class SceneReader {

    public:
        /*!
         * Read a scene description and return the results through the
         * referenced parameters.
         *
         * @param path Scene file path
         * @param scene Scene to be readed
         * @param cam Scene camera
         * @param shader Shader
         * @param os Output settings
         * @param samples Number of samples for anti-aliasing
         * @param nrays Number of rays of the recursion
         */
        static void read(const std::string path, Scene& scene, Camera*& cam,
            Shader*& shader, OutputSettings& os, int& samples, int& nrays);

    private:
        /*!
         * Clears all useless content from the scene description file.
         *
         * @param lines Get file lines already formatted
         * @param file Readed file
         */
        static void get_formatted_lines(std::list<std::string>& lines,
            std::ifstream& file);

        /*!
         * Interpret object (like shaders, shapes, etc.) from a custom format.
         *
         * @param format Custom format object
         * @param lines File lines
         *
         * @return Content of object
         */
        static std::vector<std::string>* get_content(std::vector<std::string> format,
                std::list<std::string>& lines);

        /*!
         * Interpret a 3D vector from a string.
         *
         * @param str String that corresponds to a vector
         *
         * @return 3D vector
         */
        static Vec3 get_vec3(std::string str);

        /*!
         * Interpret output settings from a scene description file.
         *
         * @param lines File lines
         *
         * @return Output Settings
         */
        static OutputSettings* interpret_output_settings(std::list<std::string>& lines);

        /*!
         * Interpret ray tracing settings from a scene description file.
         * Get samples and nrays by reference.
         *
         * @param lines File lines
         */
        static void interpret_rt_settings(std::list<std::string>& lines,
                int& samples, int& nrays);

        /*!
         * Interpret camera from a scene description file.
         *
         * @param lines File lines
         *
         * @return Readed camera
         */
        static Camera* interpret_camera(std::list<std::string>& lines);

        /*!
         * Interpret shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Readed shader
         */
        static Shader* interpret_shader(std::list<std::string>& lines);

        /*!
         * Interpret Depth Map Shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Depth Map Shader.
         */
        static DepthMapShader* get_depth_map_shader(std::list<std::string>& lines);

        /*!
         * Interpret Blinn-Phong Shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Blinn-Phong Shader.
         */
        static BlinnPhongShader* get_blinn_phong_shader(std::list<std::string>& lines);

        /*!
         * Interpret Toon Shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Toon Shader.
         */
        static ToonShader* get_toon_shader(std::list<std::string>& lines);

        /*!
         * Interpret a scene from a scene description file.
         *
         * @param lines File lines
         * @param md If needs material description
         *
         * @return Interpreted scene
         */
        static Scene* interpret_scene(std::list<std::string>& lines, bool md);

        /*!
         * Get background description.
         *
         * @param lines File lines
         *
         * @return Background
         */
        static Background* get_background(std::list<std::string>& lines);

        /*!
         * Get directional light description.
         *
         * @param lines File lines
         *
         * @return Light
         */
        static DirectionalLight* get_directional_light(std::list<std::string>& lines);

        /*!
         * Get Point light description.
         *
         * @param lines File lines
         *
         * @return Point light
         */
        static PointLight* get_point_light(std::list<std::string>& lines);

        /*!
         * Get spot light description.
         *
         * @param lines File lines
         *
         * @return Spotlight
         */
        static Spotlight* get_spotlight(std::list<std::string>& lines);


        /*!
         * Get sphere description.
         *
         * @param lines File lines
         *
         * @return Sphere
         */
        static Sphere* get_sphere(std::list<std::string>& lines, bool md);

        /*!
         * Get triangle description.
         *
         * @param lines File lines
         *
         * @return Triangle
         */
        static Triangle* get_triangle(std::list<std::string>& lines, bool md);

        /*!
         * Get box description.
         *
         * @param lines File lines
         *
         * @return Box
         */
        static Box* get_box(std::list<std::string>& lines, bool md);

        /*!
         * Get plane description.
         *
         * @param lines File lines
         *
         * @return Plane
         */
        static Plane* get_plane(std::list<std::string>& lines, bool md);

        /*!
         * Get mesh content.
         *
         * @param mfile Mesh file
         *
         * @return Mesh content
         */
        static std::tuple<std::vector<Point3*>, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*>>* get_mesh_content(std::string mfile);

        /*!
         * Get mesh of triangles description.
         *
         * @param lines File lines
         *
         * @return Mesh of triangles
         */
        static Mesh* get_mesh(std::list<std::string>& lines, bool md);

        /*!
         * Get transformations.
         *
         * @param lines File lines
         *
         * @return List of transformations
         */
        static std::list<std::tuple<Transformation, Vec3>>* get_transformations(std::list<std::string>& lines);

        /*!
         * Get material description.
         *
         * @param lines File lines
         *
         * @return Material
         */
        static Material* get_material(std::list<std::string>& lines);

        /*!
         * Get Blinn-Phong material.
         *
         * @param lines File lines
         *
         * @return Blinn-Phong material
         */
        static BlinnPhongMaterial* get_bp_material(std::list<std::string>& lines);

        /*!
         * Get cel material.
         *
         * @param lines File lines
         *
         * @return Toon material
         */
        static ToonMaterial* get_toon_material(std::list<std::string>& lines);

        /*!
         * Get cel material colors.
         *
         * @param lines File lines
         *
         * @return Toon material colors
         */
        static std::vector<RGB>* get_colors_toon_material(std::list<std::string>& lines);

        /*!
         * Get angle ranges at which each color of the cel material appears.
         *
         * @param lines File lines
         *
         * @return Angle ranges at which each color of the cel material appears
         */
        static std::vector<Vec3::RealType>* get_angles_toon_material(std::list<std::string>& lines);

        /*!
         * Get Lambertian material.
         *
         * @param lines File lines
         *
         * @return Lambertian material
         */
        static LambertianMaterial* get_lambertian_material(std::list<std::string>& lines);

        /*!
         * Get Metal material.
         *
         * @param lines File lines
         *
         * @return Metal material
         */
        static MetalMaterial* get_metal_material(std::list<std::string>& lines);

        /*!
         * Get Dielectric material.
         *
         * @param lines File lines
         *
         * @return Dielectric material
         */
        static DielectricMaterial* get_dielectric_material(std::list<std::string>& lines);

        /*!
         * Get Diffuse Light material.
         *
         * @param lines File lines
         *
         * @return Diffuse Light material
         */
        static DiffuseLightMaterial* get_diffuse_light_material(std::list<std::string>& lines);

        /*!
         * Get texture.
         *
         * @param lines File lines
         *
         * @return texture
         */
        static Texture* get_texture(std::list<std::string>& lines);
};

#endif /* _SCENE_READER_H_ */
