#include "render/io/scene_reader.h"
#include "utils.h"
#include <tuple>

/* -------------------------------------------------------------------------- */
/* --------------------------- Main functions ------------------------------- */
/* -------------------------------------------------------------------------- */

void SceneReader::read(const std::string path, Scene& scene, Camera*& cam,
        Shader*& shader, OutputSettings& os, int& samples, int& nrays) {
    // Open scene file
    std::ifstream file(path.c_str());
    // Check if the file exists
    if (!file) {
        // ERROR
        throw "Error: The file is not exists!";
    } else
        // Check if the file is open
        if (!file.is_open()) {
            // ERROR
            throw "Error: The file could not be opened!";
        } else {
            // Get file lines
            std::list<std::string> lines;
            get_formatted_lines(lines, file);
            // Close file
            file.close();
            // Interprets file
            os = *(interpret_output_settings(lines));
            interpret_rt_settings(lines, samples, nrays);
            cam = interpret_camera(lines);
            shader = interpret_shader(lines);
            // Check shader
            if (typeid(*shader) == typeid(BackgroundShader) ||
                typeid(*shader) == typeid(Normals2RGBShader) ||
                typeid(*shader) == typeid(DepthMapShader)) {
                scene  = *(interpret_scene(lines, false));
            } else if (typeid(*shader) == typeid(BlinnPhongShader) ||
                       typeid(*shader) == typeid(ToonShader) ||
                       typeid(*shader) == typeid(LambertianShader)) {
                scene  = *(interpret_scene(lines, true));
            } else {
                throw "ERROR";
            }
        }
}

void SceneReader::get_formatted_lines(std::list<std::string>& lines,
        std::ifstream& file) {
    // Read all lines of file and removes useless chars
    lines.clear();
    std::string line;
    while (getline(file, line)) {
        // Remove indentation
        while (line.find(" ") == 0) {
            line = line.replace(line.find(" "), 1, "");
        }
        // Remove comments
        unsigned int i = line.find("#");
        if (i < line.length()) {
            std::string aux;
            // Check if the entire line is a comment
            if (i == 0) {
                aux = line.replace(i, line.length(), "");
            } else {
                aux = line.replace(i, line.length() - 1, "");
            }
            // Check if the line is not empty
            if (aux.length() > 0) {
                line = aux;
            } else {
                continue;
            }
        }
        // Adds in list
        lines.push_back(line);
    }
}

Vec3 SceneReader::get_vec3(std::string str) {
    // Auxiliary vector
    std::vector<std::string> v = split(str, ' ');
    for (std::string& str : v) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    }
    // Generate Vec3
    Vec3 vec = Vec3(atof(v[0].c_str()), atof(v[1].c_str()), atof(v[2].c_str()));
    return vec;
}

std::vector<std::string>* SceneReader::get_content(std::vector<std::string> format,
        std::list<std::string>& lines) {
    // Init
    std::vector<std::string>* v = new std::vector<std::string>();
    std::list<std::string>::iterator itr = lines.begin();
    std::list<std::string>::iterator begin = lines.begin();
    // Read contents
    for (std::string str : format) {
        // Check format
        if ((*itr).find(str) == 0) {
            // Get content
            std::string aux = *(itr++);
            v->push_back(aux.replace(0, str.length(), ""));
        } else {
            throw "Invalid file format.";
        }
    }
    // Remove interpreted lines
    lines.erase(begin, itr);
    return v;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------- Settings -------------------------------- */
/* -------------------------------------------------------------------------- */

OutputSettings* SceneReader::interpret_output_settings(std::list<std::string>& lines) {
    // Output settings format
    std::string vformat[] = {"NAME:", "TYPE:", "CODIFICATION:",
                             "WIDTH:", "HEIGHT:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the output settings and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    for (std::string& str : v) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    }
    return (new OutputSettings(v[0], OutputSettings::get_image_file_format(v[1]),
        OutputSettings::get_codification(v[2]), std::stoi(v[3]), std::stoi(v[4])));
}

void SceneReader::interpret_rt_settings(std::list<std::string>& lines,
        int& samples, int& nrays) {
    // Camara format
    std::string vformat[] = {"SAMPLES:", "RAYS:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Get contents
    std::vector<std::string>& v = *(get_content(format, lines));
    samples = atoi(v[0].c_str());
    nrays = atoi(v[1].c_str());
}

/* -------------------------------------------------------------------------- */
/* --------------------------------- Camera --------------------------------- */
/* -------------------------------------------------------------------------- */

Camera* SceneReader::interpret_camera(std::list<std::string>& lines) {
    // Look for other scene components
    if (!lines.empty() && (*(lines.begin())).find("CAMERA:") == 0) {
        lines.pop_front();
        if (!lines.empty() && (*(lines.begin())).find("PERSPECTIVE") == 0) {
            lines.pop_front();
            // Camera format
            std::string vformat[] = {"LOOK_FROM:", "LOOK_AT:", "VUP:",
                                     "VFOV:", "ASPECT_RATIO:", "APERTURE:",
                                     "FOCAL_DISTANCE:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the camera and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            return (new PerspectiveCamera(get_vec3(v[0]), get_vec3(v[1]),
                get_vec3(v[2]), atof(v[3].c_str()), atof(v[4].c_str()),
                atof(v[5].c_str()), atof(v[6].c_str())));
        } else if (!lines.empty() && (*(lines.begin())).find("PARALLEL") == 0) {
            lines.pop_front();
            // Camera format
            std::string vformat[] = {"LOOK_FROM:", "LOOK_AT:", "VUP:",
                                     "TOP:", "LEFT:", "RIGHT:", "BOTTOM:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the camera and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            return (new ParallelCamera(get_vec3(v[0]), get_vec3(v[1]),
                get_vec3(v[2]), atof(v[3].c_str()), atof(v[4].c_str()),
                atof(v[5].c_str()), atof(v[6].c_str())));
        } else {
            // ERROR
            throw "Invalid file format! Needs the camera description.";
        }
    } else {
        // ERROR
        throw "Invalid file format! Needs the camera description.";
    }
}

/* -------------------------------------------------------------------------- */
/* -------------------------------- Shader ---------------------------------- */
/* -------------------------------------------------------------------------- */

Shader* SceneReader::interpret_shader(std::list<std::string>& lines) {
    // Look for other scene components
    if (!lines.empty() && (*(lines.begin())).find("SHADER:") == 0) {
        // Remove interpreted lines
        lines.pop_front();
        std::string aux = *(lines.begin());
        lines.pop_front();
        if (aux.find("BACKGROUND") == 0) {
            return (new BackgroundShader());
        } else
            if (aux.find("NORMALS2RGB") == 0) {
                return (new Normals2RGBShader());
        } else
            if (aux.find("DEPTHMAP") == 0) {
                return get_depth_map_shader(lines);
        } else
            if (aux.find("BLINNPHONG") == 0) {
                return get_blinn_phong_shader(lines);
        } else
            if (aux.find("TOON") == 0) {
                return get_toon_shader(lines);
        } else
            if (aux.find("LAMBERTIAN") == 0) {
                return (new LambertianShader());
        } else {
            throw "Invalid shader!";
        }
    } else {
        // ERROR
        throw "Invalid file format! Needs the shader description.";
    }
}

DepthMapShader* SceneReader::get_depth_map_shader(std::list<std::string>& lines) {
    // Depth map shader format
    std::string vformat[] = {"DEPTH:", "FOREGROUND:", "BACKGROUND:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the shader and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new DepthMapShader(atof(v[0].c_str()), get_vec3(v[1]),
        get_vec3(v[2])));
}

BlinnPhongShader* SceneReader::get_blinn_phong_shader(std::list<std::string>& lines) {
    // Blinn-Phong shader format
    std::string vformat[] = {"AMBIENT_LIGHT:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the shader and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new BlinnPhongShader(get_vec3(v[0])));
}

ToonShader* SceneReader::get_toon_shader(std::list<std::string>& lines) {
    // Blinn-Phong shader format
    std::string vformat[] = {"BORDER_COLOR:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the shader and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new ToonShader(get_vec3(v[0])));
}

/* -------------------------------------------------------------------------- */
/* -------------------------------- Scene ----------------------------------- */
/* -------------------------------------------------------------------------- */

Scene* SceneReader::interpret_scene(std::list<std::string>& lines, bool md) {
    // Check if scene description is empty
    if (lines.empty()) {
        return new Scene();
    }
    // Interpret scene attributes
    std::list<std::string>::iterator itr = lines.begin();
    // Scene background
    Background* background = new Background();
    if ((*itr).find("BACKGROUND:") == 0) {
        lines.erase(itr);
        background = get_background(lines);
    }
    Scene* scene = new Scene(*background);
    // Check if scene description is empty
    if (lines.empty()) {
        return scene;
    }
    // Components
    itr = lines.begin();
    // Look for other scene components
    if (!lines.empty() && (*(itr)).find("COMPONENTS:") == 0) {
        // Erase
        lines.erase(itr);
        // Find components
        for (itr = lines.begin(); !lines.empty(); ) {
            // Check all components
            if ((*(itr)).find("DIRECTIONAL_LIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = get_directional_light(lines);
                scene->add_light(l);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("POINT_LIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = get_point_light(lines);
                scene->add_light(l);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("SPOTLIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = get_spotlight(lines);
                scene->add_light(l);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("SPHERE:") == 0) {
                // Erase
                lines.erase(itr);
                // Add sphere
                Sphere* s = get_sphere(lines, md);
                scene->add_shape(s);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("TRIANGLE:") == 0) {
                // Erase
                lines.erase(itr);
                // Add triangle
                Triangle* t = get_triangle(lines, md);
                scene->add_shape(t);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("BOX:") == 0) {
                // Erase
                lines.erase(itr);
                // Add box
                Box* t = get_box(lines, md);
                scene->add_shape(t);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("MESH:") == 0) {
                // Erase
                lines.erase(itr);
                // Add box
                Mesh* m = get_mesh(lines, md);
                scene->add_shape(m);
                // Next component
                itr = lines.begin();
            }
        }
    }
    return scene;
}

Background* SceneReader::get_background(std::list<std::string>& lines) {
    // Background formats
    std::string f1[] = {"UPPER_LEFT:", "LOWER_LEFT:", "UPPER_RIGHT:", "LOWER_RIGHT:"};
    std::string f2[] = {"TOP:", "BOTTOM:"};
    std::string f3[] = {"LEFT:", "RIGHT:"};
    std::string f4[] = {"COLOR:"};
    // Check description type
    std::string aux = *(lines.begin());
    // Corners
    if (aux.find(f1[0]) == 0) {
        std::vector<std::string> format(f1, end(f1));
        // Create the background and return it
        std::vector<std::string>& v = *(get_content(format, lines));
        return (new Background(get_vec3(v[0]), get_vec3(v[1]), get_vec3(v[2]),
            get_vec3(v[3])));
    } else
        // Top-Bottom
        if (aux.find(f2[0]) == 0) {
            std::vector<std::string> format(f2, end(f2));
            // Create the background and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            return (new Background(get_vec3(v[0]), get_vec3(v[1]), true));
    } else
        // Left-Right
        if (aux.find(f3[0]) == 0) {
            std::vector<std::string> format(f3, end(f3));
            // Create the background and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            return (new Background(get_vec3(v[0]), get_vec3(v[1]), false));
    } else
        // One color
        if (aux.find(f4[0]) == 0) {
            std::vector<std::string> format(f4, end(f4));
            // Create the background and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            return (new Background(get_vec3(v[0])));
    }
    throw "Invalid background description.";
}

/* ------------------------------- Lights ----------------------------------- */

DirectionalLight* SceneReader::get_directional_light(std::list<std::string>& lines) {
    // Directional light format
    std::string vformat[] = {"DIRECTION:", "INTENSITY:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the directional light and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new DirectionalLight(get_vec3(v[0]), get_vec3(v[1].c_str())));
}

PointLight* SceneReader::get_point_light(std::list<std::string>& lines) {
    // Spot light format
    std::string vformat[] = {"ORIGIN:", "INTENSITY:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the spot light and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new PointLight(get_vec3(v[0].c_str()), get_vec3(v[1].c_str())));
}

Spotlight* SceneReader::get_spotlight(std::list<std::string>& lines) {
    // Spot light format
    std::string vformat[] = {"ORIGIN:", "DIRECTION:", "INTENSITY:", "ANGLE:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the spot light and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new Spotlight(get_vec3(v[0].c_str()), get_vec3(v[1].c_str()),
            get_vec3(v[2].c_str()), atof(v[3].c_str())));
}

/* ------------------------------- Shapes ----------------------------------- */

Sphere* SceneReader::get_sphere(std::list<std::string>& lines, bool md) {
    // Sphere format
    std::string vformat[] = {"ORIGIN:", "RADIUS:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the sphere and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    Sphere* s;
    if (md) {
        s = new Sphere(get_vec3(v[0]), atof(v[1].c_str()), get_material(lines));
    } else {
        s = new Sphere(get_vec3(v[0]), atof(v[1].c_str()));
    }
    // Transformations
    std::list<std::tuple<Transformation, Vec3>> ts = *(get_transformations(lines));
    if (!ts.empty()) {
        s->transform(ts);
    }
    return s;
}

Triangle* SceneReader::get_triangle(std::list<std::string>& lines, bool md) {
    // Triangle format
    std::string vformat[] = {"V0:", "V1:", "V2:", "BACK_FACING_CULL:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the triangle and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    Triangle* t;
    if (md) {
        t = new Triangle(get_vec3(v[0]), get_vec3(v[1]), get_vec3(v[2]),
            to_bool(v[3]), get_material(lines));
    } else {
        t = new Triangle(get_vec3(v[0]), get_vec3(v[1]), get_vec3(v[2]),
            to_bool(v[3]));
    }
    // Transformations
    std::list<std::tuple<Transformation, Vec3>> ts = *(get_transformations(lines));
    if (!ts.empty()) {
        t->transform(ts);
    }
    return t;
}

Box* SceneReader::get_box(std::list<std::string>& lines, bool md) {
    // Box format
    std::string vformat[] = {"ORIGIN:", "SIZE:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the box and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    Box* b;
    if (md) {
        b = new Box(get_vec3(v[0]), get_vec3(v[1]), get_material(lines));
    } else {
        b = new Box(get_vec3(v[0]), get_vec3(v[1]));
    }
    // Transformations
    std::list<std::tuple<Transformation, Vec3>> ts = *(get_transformations(lines));
    if (!ts.empty()) {
        b->transform(ts);
    }
    return b;
}

std::tuple<std::vector<Point3*>, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*>>* SceneReader::get_mesh_content(std::string mfile) {
    // Open scene file
    std::ifstream file(mfile.c_str());
    // Check if the file exists
    if (!file) {
        // ERROR
        throw "Error: The mesh file is not exists!";
    } else
        // Check if the file is open
        if (!file.is_open()) {
            // ERROR
            throw "Error: The mesh file could not be opened!";
        } else {
            std::vector<Point3*> vs;
            std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*> fs;
            // Get mesh content
            std::string line;
            while (getline(file, line)) {
                if (line.find("v") == 0) {
                    line.replace(0, 1, "");
                    Vec3 v = get_vec3(line);
                    Point3* p = new Point3(v[0], v[1], v[2]);
                    vs.push_back(p);
                }
                if (line.find("f") == 0) {
                    line.replace(0, 1, "");
                    Vec3 v = get_vec3(line);
                    std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>* t = new std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>(v[0], v[1], v[2]);
                    fs.push_back(t);
                }
            }
            return (new std::tuple<std::vector<Point3*>, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*>>(vs, fs));
        }
}

Mesh* SceneReader::get_mesh(std::list<std::string>& lines, bool md) {
    // Mesh format
    std::string vformat[] = {"FILE: "};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the mesh and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    Mesh* m;
    // Get mesh content
    std::vector<Point3*> vs;
    std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*> fs;
    std::tie(vs, fs) = *(get_mesh_content(v[0]));
    if (md) {
        m = new Mesh(vs, fs, get_material(lines));
    } else {
        m = new Mesh(vs, fs);
    }
    // Check if scene description is empty
    if (!lines.empty()) {
        // Transformations
        std::list<std::tuple<Transformation, Vec3>> ts = *(get_transformations(lines));
        if (!ts.empty()) {
            m->transform(ts);
        }
    }
    return m;
}

std::list<std::tuple<Transformation, Vec3>>* SceneReader::get_transformations(std::list<std::string>& lines) {
    // Interpret scene attributes
    std::list<std::string>::iterator itr = lines.begin();
    std::list<std::tuple<Transformation, Vec3>>* transformations = new std::list<std::tuple<Transformation, Vec3>>();
    // Get transformations
    for (itr = lines.begin(); !lines.empty(); ) {
        // Check all components
        if ((*(itr)).find("TRANSLATE:") == 0) {
            // Erase
            lines.erase(itr);
            // Add transformation
            std::string vformat[] = {"VALUE:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the sphere and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            transformations->push_back(std::make_tuple(TRANSLATE, get_vec3(v[0])));
            // Next component
            itr = lines.begin();
        } else if ((*(itr)).find("ROTATE:") == 0) {
            // Erase
            lines.erase(itr);
            // Add transformation
            std::string vformat[] = {"VALUE:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the sphere and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            transformations->push_back(std::make_tuple(ROTATE, get_vec3(v[0])));
            // Next component
            itr = lines.begin();
        } else if ((*(itr)).find("SCALE:") == 0) {
            // Erase
            lines.erase(itr);
            // Add transformation
            std::string vformat[] = {"VALUE:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the sphere and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            transformations->push_back(std::make_tuple(SCALE, get_vec3(v[0])));
            // Next component
            itr = lines.begin();
        } else {
            break;
        }
    }
    return transformations;
}

/* ----------------------------- Materials ---------------------------------- */

Material* SceneReader::get_material(std::list<std::string>& lines) {
    // Interpret file
    std::string aux = *(lines.begin());
    lines.pop_front();
    if (aux.find("BLINN_PHONG_MATERIAL:") == 0) {
        return get_bp_material(lines);
    } else
        if (aux.find("TOON_MATERIAL:") == 0) {
            return get_toon_material(lines);
    } else
        if (aux.find("LAMBERTIAN:") == 0) {
            return get_lambertian_material(lines);
    } else
        if (aux.find("METAL:") == 0) {
            return get_metal_material(lines);
    } else
        if (aux.find("DIELECTRIC:") == 0) {
            return get_dielectric_material(lines);
    } else
        if (aux.find("DIFFUSE_LIGHT:") == 0) {
            return get_diffuse_light_material(lines);
    } else {
        throw "Invalid material!";
    }
}

BlinnPhongMaterial* SceneReader::get_bp_material(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"KA:", "KD:", "KS:", "P:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Blinn-Phong material and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new BlinnPhongMaterial(get_vec3(v[0]), get_vec3(v[1]), get_vec3(v[2]),
        atof(v[3].c_str())));
}

ToonMaterial* SceneReader::get_toon_material(std::list<std::string>& lines) {
    std::vector<RGB> colors = *get_colors_toon_material(lines);
    std::vector<Vec3::RealType> angles;
    for (auto& value : *get_angles_toon_material(lines)) {
        angles.push_back(value);
    }
    return (new ToonMaterial(colors, angles));
}

std::vector<RGB>* SceneReader::get_colors_toon_material(std::list<std::string>& lines) {
    // Get number of colors
    std::string vformat[] = {"COLORS:"};
    std::vector<std::string> format(vformat, end(vformat));
    std::vector<std::string>& v = *(get_content(format, lines));
    int size = atoi(v[0].c_str());
    // Get colors
    std::vector<RGB>* colors = new std::vector<RGB>();
    std::list<std::string>::iterator itr = lines.begin();
    std::list<std::string>::iterator begin = lines.begin();
    for (int i = 0; i < size; i++) {
        colors->push_back(get_vec3(*itr));
        itr++;
    }
    // Remove interpreted lines
    lines.erase(begin, itr);
    return colors;
}

std::vector<Vec3::RealType>* SceneReader::get_angles_toon_material(std::list<std::string>& lines) {
    // Get number of angles
    std::string vformat[] = {"ANGLES:"};
    std::vector<std::string> format(vformat, end(vformat));
    std::vector<std::string>& v = *(get_content(format, lines));
    int size = atoi(v[0].c_str());
    // Get colors
    std::vector<Vec3::RealType>* angles = new std::vector<Vec3::RealType>();
    std::list<std::string>::iterator itr = lines.begin();
    std::list<std::string>::iterator begin = lines.begin();
    for (int i = 0; i < size; i++) {
        angles->push_back(std::cos((atof((*itr++).c_str()) * M_PI) / 180.f));
    }
    // Remove interpreted lines
    lines.erase(begin, itr);
    return angles;
}

LambertianMaterial* SceneReader::get_lambertian_material(std::list<std::string>& lines) {
    return (new LambertianMaterial(get_texture(lines)));
}

MetalMaterial* SceneReader::get_metal_material(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"ALBEDO:", "FUZZ:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Metal material and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new MetalMaterial(get_vec3(v[0]), atof(v[1].c_str())));
}

DielectricMaterial* SceneReader::get_dielectric_material(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"RI:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Dielectric material and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new DielectricMaterial(atof(v[0].c_str())));
}

DiffuseLightMaterial* SceneReader::get_diffuse_light_material(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"EMIT:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Dielectric material and return it
    std::vector<std::string>& v = *(get_content(format, lines));
    return (new DiffuseLightMaterial(get_vec3(v[0])));
}

Texture* SceneReader::get_texture(std::list<std::string>& lines) {
    // Interpret scene attributes
    std::list<std::string>::iterator itr = lines.begin();
    Texture* texture = new ConstantTexture();
    // Get transformations
    for (itr = lines.begin(); !lines.empty(); ) {
        // Check all components
        if ((*(itr)).find("ALBEDO:") == 0) {
            // Material format
            std::string vformat[] = {"ALBEDO:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the Metal material and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            texture = new ConstantTexture(get_vec3(v[0]));
            // Next component
            itr = lines.begin();
        } else if ((*(itr)).find("CONSTANT_TEXTURE:") == 0) {
            // Erase
            lines.erase(itr);
            // Add transformation
            std::string vformat[] = {"VALUE:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the texture and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            texture = new ConstantTexture(get_vec3(v[0]));
            // Next component
            itr = lines.begin();
        } else if ((*(itr)).find("CHECKER_TEXTURE:") == 0) {
            // Erase
            lines.erase(itr);
            // Add transformation
            std::string vformat[] = {"ODD:", "EVEN:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the texture and return it
            std::vector<std::string>& v = *(get_content(format, lines));
            texture = new CheckerTexture((new ConstantTexture(get_vec3(v[0]))), (new ConstantTexture(get_vec3(v[1]))));
            // Next component
            itr = lines.begin();
        } else {
            break;
        }
    }
    return texture;
}
