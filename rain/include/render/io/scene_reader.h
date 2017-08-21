#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include "utils/vec3.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "output_settings.h"
#include "scene/components/shape/shape.h"
#include "scene/components/shape/sphere.h"

/*!
 * This class is responsible for reading the scene.
 */
class SceneReader {

    public:
        /*!
         * Read a scene.
         *
         * @param path Scene file path
         * @param scene Scene to be readed
         * @param camera Camera
         * @param os Output settings
         *
         * @return Readed scene
         */
        static void read(const std::string path, Scene& scene, Camera& cam,
            OutputSettings& os);

    private:
        /*!
         * Interpret output settings of the scene file.
         *
         * @param lines File lines
         *
         * @return Output settings
         */
        static OutputSettings* interpretOutputSettings(std::list<std::string>& lines);

        /*!
         * Interpret camera of the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted camera
         */
        static Camera* interpretCamera(std::list<std::string>& lines);

        /*!
         * Split a string and return the Vec3 corresponding to this string.
         *
         * @param str String to be splited
         *
         * @return A Vec3 value
         */
        static Vec3 getVec3(std::string str);

        /*!
         * Interpret the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted scene
         */
        static Scene* interpretScene(std::list<std::string>& lines);

        /*!
         * Split a string and return the RGB corresponding to this string.
         *
         * @param str String to be splited
         *
         * @return A RGB value
         */
        static RGB getRGB(std::string str);



       static Sphere* getSphere(std::list<std::string>& lines);
};

#endif
