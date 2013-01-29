/*
 * config.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "config.h"

#include <yaml-cpp/yaml.h>
#include "viewport.h"
#include "string_utils.h"

namespace YAML {

template<>
struct convert<math::vec3>
{
    static bool decode(const Node &node, math::vec3 &rhs)
    {
        if(!node.IsSequence() || node.size() != 3)
            return false;

        rhs.x = node[0].as<float>();
        rhs.y = node[1].as<float>();
        rhs.z = node[2].as<float>();

        return true;
    }
};

template<>
struct convert<rend::Color3>
{
    static bool decode(const Node &node, rend::Color3 &rhs)
    {
        if(!node.IsSequence() || node.size() != 3)
            return false;

        rhs[rend::RED] = node[0].as<uint32_t>();
        rhs[rend::GREEN] = node[1].as<uint32_t>();
        rhs[rend::BLUE] = node[2].as<uint32_t>();

        return true;
    }
};

template<>
struct convert<base::SceneConfig::ObjInfo>
{
    static bool decode(const Node &node, base::SceneConfig::ObjInfo &rhs)
    {
        rhs.pathToTheModel = node["model"].as<std::string>();
        rhs.position = node["position"].as<math::vec3>();

        try { rhs.scale = node["scale"].as<math::vec3>(); } catch (YAML::Exception &e) { }

        return true;
    }
};

template<>
struct convert<base::SceneConfig::DirLightInfo>
{
    static bool decode(const Node &node, base::SceneConfig::DirLightInfo &rhs)
    {
        rhs.direction = node["direction"].as<math::vec3>();
        rhs.intensity = node["intensity"].as<rend::Color3>();

        return true;
    }
};

template<>
struct convert<base::SceneConfig::PointLightInfo>
{
    static bool decode(const Node &node, base::SceneConfig::PointLightInfo &rhs)
    {
        rhs.position = node["position"].as<math::vec3>();
        rhs.intensity = node["intensity"].as<rend::Color3>();

        rhs.kc = node["kc"].as<double>();
        rhs.kl = node["kl"].as<double>();
        rhs.kq = node["kq"].as<double>();

        return true;
    }
};

}

namespace base
{

const char * const DEFAULT_RENDERER_CONFIG = "renderer.yaml";
const char * const DEFAULT_SCENE_CONFIG = "scene.yaml";


void RendererConfig::makeDefaults()
{
    camPosition = math::vec3(0, 0, 0);
    width = rend::DEFAULT_WIDTH;
    height = rend::DEFAULT_HEIGHT;
    pathToTheAssets = fs::canonical(fs::current_path()).string();   // executable dir
    rendererMode = "software";
}

/*
static void operator>> (const YAML::Node &node,  &dirLightInfo)
{
    node[""] >> dirLightInfo.direction;
    node[""] >> dirLightInfo.intensity;
}

static void operator>> (const YAML::Node &node, SceneConfig:: &pointLightInfo)
{
    node["position"] >> pointLightInfo.position;
    node["intensity"] >> pointLightInfo.intensity;

}*/

//! Finds value by the key and stores it in `value'.
/** If can't find value - sets it to default. */
template<typename T>
bool FindValue(const YAML::Node &node, T &value, std::string key, const T &defaultValue)
{
    if (node[key])
    {
        value = node[key].as<T>();

        return true;
    }
    else
    {
        syslog << "Can't find" << key << ". Setting to default value"
               << defaultValue << logwarn;
        value = defaultValue;

        return false;
    }
}

void Config::parseRendererConfig() try
{
    YAML::Node cfg = YAML::Load(m_rendererConfigData);

    FindValue(cfg, m_rendererConfig.width, "width", rend::DEFAULT_WIDTH);
    FindValue(cfg, m_rendererConfig.height, "height", rend::DEFAULT_HEIGHT);
    FindValue(cfg, m_rendererConfig.camPosition, "campos", math::vec3(0, 0, 0));
    FindValue(cfg, m_rendererConfig.pathToTheAssets, "assets", string(""));
    FindValue(cfg, m_rendererConfig.rendererMode, "renderer", string("software"));

    common::eraseSpaces(m_rendererConfig.rendererMode);

    // check resources path
    fs::path p(m_rendererConfig.pathToTheAssets);

    // if this path exists, then save it
    if (fs::exists(p) && fs::is_directory(p))
        m_rendererConfig.pathToTheAssets = fs::canonical(p).string();
    // otherwise save current path (at the time of entry to main())
    else
        m_rendererConfig.pathToTheAssets = fs::canonical(fs::current_path()).string();
}
catch (YAML::Exception &e)
{
    syslog << "Error while parsing config file. Setting to defaults.\nError:"
           << e.what() << logerr;

    m_rendererConfig.makeDefaults();
}

void Config::parseSceneConfig() try
{
    YAML::Node cfg = YAML::Load(m_sceneConfigData);

    // getting scene objects
    const YAML::Node &objects = cfg["Objects"];
    for (size_t i = 0; i < objects.size(); i++)
    {
        auto objInfo = objects[i].as<SceneConfig::ObjInfo>();

        m_sceneConfig.objects.push_back(objInfo);
    }

    // getting scene lights
    parseLights(cfg);
}
catch (YAML::Exception &e)
{
    syslog << "Error while parsing scene config file.\nError:"
           << e.what() << logerr;

    m_rendererConfig.makeDefaults();
}

void Config::parseLights(const YAML::Node &doc)
{
    const YAML::Node &lights = doc["Lights"];

    // ambient lights
    try
    {
        const YAML::Node &ambLight = lights["Ambient"];

        for (size_t i = 0; i < ambLight.size(); i++)
            m_sceneConfig.ambIntensity = ambLight[i]["intensity"].as<rend::Color3>();

        if (ambLight.size() > 1)
            syslog << "Number of ambient light sources more than one. Using the last." << logwarn;
    }
    catch (YAML::Exception &e) { syslog << "No ambient light" << logmess; }

    // directional lights
    try
    {
        const YAML::Node &dirLight = lights["Directional"];
        for (size_t i = 0; i < dirLight.size(); i++)
        {
            auto light = dirLight[i].as<SceneConfig::DirLightInfo>();

            m_sceneConfig.dirLights.push_back(light);
        }
    }
    catch (YAML::Exception &e) { syslog << "No directional lights" << logmess; }

    // point lights
    try
    {
        const YAML::Node &pointLight = lights["Point"];
        for (size_t i = 0; i < pointLight.size(); i++)
        {
            auto light = pointLight[i].as<SceneConfig::PointLightInfo>();

            m_sceneConfig.pointLights.push_back(light);
        }
    }
    catch (YAML::Exception &e) { syslog << "No point lights" << logmess; }
}

Config::Config(const string &cfgDir)
{
    m_rendererConfig.makeDefaults();

    fs::path mainDir;

    cfgDir.empty() ? mainDir = DEFAULT_RENDERER_CONFIG : mainDir = cfgDir;

    if (fs::exists(mainDir))
    {
        if (fs::is_regular_file(mainDir))
        {
            if (mainDir.extension().string() != ".yaml")
            {
                syslog << "Invalid type of config a file" << logerr;
                return;
            }
        }
        else if (fs::is_directory(mainDir))
        {
            mainDir /= DEFAULT_RENDERER_CONFIG;
        }
        else
        {
            syslog << "Unknown error while opening a configuration file" << logerr;
            return;
        }
    }
    else
    {
        syslog << "Cannot find config file. Setting defaults." << logwarn;
        return;
    }

    string loadPath = fs::canonical(mainDir).string();

    // load renderer config
    std::ifstream rendererConfigFile(loadPath);

    if (rendererConfigFile)
    {
        m_rendererConfigData << rendererConfigFile.rdbuf();
        parseRendererConfig();
    }
    else
    {
        syslog << "Cannot open config file. Setting defaults." << logwarn;
        return;
    }

    loadPath = (mainDir.parent_path() /= DEFAULT_SCENE_CONFIG).string();

    // load scene config
    std::ifstream sceneConfigFile(loadPath);

    if (sceneConfigFile)
    {
        m_sceneConfigData << sceneConfigFile.rdbuf();
        parseSceneConfig();
    }
    else
    {
        syslog << "Cannot open scene config file." << logwarn;
        return;
    }
}

const RendererConfig &Config::getRendererConfig() const
{
    return m_rendererConfig;
}

const SceneConfig &Config::getSceneConfig() const
{
    return m_sceneConfig;
}

}
