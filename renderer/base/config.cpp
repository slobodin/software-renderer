/*
 * config.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "config.h"

#include <yaml-cpp/yaml.h>
#include "viewport.h"

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
}

static void operator>> (const YAML::Node &node, math::vec3 &v)
{
    node[0] >> v.x;
    node[1] >> v.y;
    node[2] >> v.z;
}

static void operator>> (const YAML::Node &node, rend::Color3 &col)
{
    node[0] >> col[rend::RED];
    node[1] >> col[rend::GREEN];
    node[2] >> col[rend::BLUE];
}

static void operator>> (const YAML::Node &node, SceneConfig::ObjInfo &objInfo)
{
    node["model"] >> objInfo.pathToTheModel;
    node["position"] >> objInfo.position;
}

static void operator>> (const YAML::Node &node, SceneConfig::DirLightInfo &dirLightInfo)
{
    node["direction"] >> dirLightInfo.direction;
    node["intensity"] >> dirLightInfo.intensity;
}

//! Finds value by the key and stores it in `value'.
/** If can't find value - sets it to default. */
template<typename T>
bool FindValue(const YAML::Node &doc, T &value, string key, const T defaultValue)
{
    if(const YAML::Node *pName = doc.FindValue(key))
    {
        *pName >> value;

        return true;
    }
    else
    {
        syslog << "Can't find" << key << ". Setting to default value" << defaultValue << logwarn;
        value = defaultValue;

        return false;
    }
}

void Config::parseRendererConfig() try
{
    YAML::Parser cfg(m_rendererConfigData);

    YAML::Node doc;
    cfg.GetNextDocument(doc);

    FindValue(doc, m_rendererConfig.width, "width", rend::DEFAULT_WIDTH);
    FindValue(doc, m_rendererConfig.height, "height", rend::DEFAULT_HEIGHT);
    FindValue(doc, m_rendererConfig.camPosition, "campos", math::vec3(0, 0, 0));
    FindValue(doc, m_rendererConfig.pathToTheAssets, "assets", string(""));

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
    YAML::Parser cfg(m_sceneConfigData);

    YAML::Node doc;
    cfg.GetNextDocument(doc);

    // getting scene objects
    const YAML::Node &objects = doc["Objects"];
    for (size_t i = 0; i < objects.size(); i++)
    {
        SceneConfig::ObjInfo objInfo;
        objects[i] >> objInfo;

        m_sceneConfig.objects.push_back(objInfo);
    }

    // getting scene lights
    parseLights(doc);
}
catch (YAML::Exception &e)
{
    syslog << "Error while parsing scene config file.\nError:"
           << e.what() << logerr;

    m_rendererConfig.makeDefaults();
}

void Config::parseLights(const YAML::Node &doc) try
{
    const YAML::Node &lights = doc["Lights"];
    const YAML::Node &ambLight = lights["Ambient"];

    for (size_t i = 0; i < ambLight.size(); i++)
        ambLight[i]["intensity"] >> m_sceneConfig.ambIntensity;

    if (ambLight.size() > 1)
        syslog << "Number of ambient light sources more than one. Using the last." << logwarn;

    const YAML::Node &dirLight = lights["Directional"];
    for (size_t i = 0; i < dirLight.size(); i++)
    {
        SceneConfig::DirLightInfo light;
        dirLight[i] >> light;

        m_sceneConfig.dirLights.push_back(light);
    }
}
catch (YAML::Exception &e)
{
    // nothing
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
