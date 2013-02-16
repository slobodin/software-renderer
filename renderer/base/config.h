/*
 * config.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "math/vec3.h"
#include "rend/color.h"

namespace Json
{

class Value;

}

namespace base
{

class Controller;
class ResourceMgr;

//! Renderer configuration.
struct RendererConfig
{
    math::vec3      camPosition;
    int             width;
    int             height;
    std::string     pathToTheAssets;
    std::string     rendererMode;           // "software" or "opengl"

    void makeDefaults();
};

//! What will scene contain.
struct SceneConfig
{
    //! Particular object.
    struct ObjInfo
    {
        math::vec3      position;
        math::vec3      scale;
        std::string     pathToTheModel;
        ObjInfo() : scale(1.0, 1.0, 1.0) { }
    };

    // scene objects
    std::vector<ObjInfo> objects;

    // ambient light intensity
    rend::Color3 ambIntensity;
    // directional light config
    struct DirLightInfo
    {
        math::vec3 direction;
        rend::Color3 intensity;
    };
    // point light config
    struct PointLightInfo
    {
        math::vec3 position;
        rend::Color3 intensity;
        float kc, kl, kq;
    };

    // directional lights
    std::vector<DirLightInfo> dirLights;
    // point lights
    std::vector<PointLightInfo> pointLights;

    SceneConfig() { ambIntensity.reset(); }
};

class Config
{
    RendererConfig m_rendererConfig;
    std::stringstream m_rendererConfigData;
    void parseRendererConfig();

    SceneConfig m_sceneConfig;
    std::stringstream m_sceneConfigData;
    void parseSceneConfig();
    void parseObjects(const Json::Value &root);
    void parseLights(const Json::Value &root);

public:
    Config(const std::string &cfgDir = "");

    const RendererConfig &getRendererConfig() const;
    const SceneConfig &getSceneConfig() const;

    NONCOPYABLE(Config)
};

}

#endif // CONFIG_H
