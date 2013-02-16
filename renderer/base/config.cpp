/*
 * config.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "config.h"

#include <jsoncpp-0.5.0/json.h>
#include "viewport.h"

namespace base
{

const char * const DEFAULT_RENDERER_CONFIG = "renderer.json";
const char * const DEFAULT_SCENE_CONFIG = "scene.json";

void getVec3(const Json::Value &root, math::vec3 &out, math::vec3 &default = math::vec3())
{
    if (root.empty())
    {
        out = default;
        return;
    }
    out.x = root[0].asFloat();
    out.y = root[1].asFloat();
    out.z = root[2].asFloat();
}

void getColor(const Json::Value &root, rend::Color3 &out, rend::Color3 &default = rend::Color3())
{
    if (root.empty())
    {
        out = default;
        return;
    }
    out[rend::RED] = root[0].asUInt();
    out[rend::GREEN] = root[1].asUInt();
    out[rend::BLUE] = root[2].asUInt();
}

void RendererConfig::makeDefaults()
{
    camPosition = math::vec3(0, 0, 0);
    width = rend::DEFAULT_WIDTH;
    height = rend::DEFAULT_HEIGHT;
    pathToTheAssets = fs::system_complete(fs::current_path<fs::path>()).string();   // executable directory
    rendererMode = "software";
}

void Config::parseRendererConfig()
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(m_rendererConfigData, root))
    {
        syslog << "Failed to parse renderer configuration: " << reader.getFormatedErrorMessages() << logerr;
        return;
    }

    m_rendererConfig.width = root.get("width", m_rendererConfig.width ).asInt();
    m_rendererConfig.height = root.get("height", m_rendererConfig.height ).asInt();
    m_rendererConfig.pathToTheAssets = root.get("assets", m_rendererConfig.pathToTheAssets).asString();
    getVec3(root["campos"], m_rendererConfig.camPosition);

    // check resources path
    fs::path p(m_rendererConfig.pathToTheAssets);

    // if this path exists, then save it
    if (fs::exists(p) && fs::is_directory(p))
        m_rendererConfig.pathToTheAssets = fs::system_complete(p).string();
    // otherwise save current path (at the time of entry to main())
    else
    {
        auto currPath = fs::current_path<fs::path>();
        m_rendererConfig.pathToTheAssets = fs::system_complete(currPath).string();
    }
}

void Config::parseSceneConfig()
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(m_sceneConfigData, root))
    {
        syslog << "Failed to parse scene configuration: " << reader.getFormatedErrorMessages() << logerr;
        return;
    }

    parseObjects(root["Objects"]);
    parseLights(root["Lights"]);
}

void Config::parseObjects(const Json::Value &root)
{
    for (Json::Value::ArrayIndex objIdx = 0; objIdx < root.size(); ++objIdx)
    {
        const Json::Value objJson = root[objIdx];
        SceneConfig::ObjInfo objInfo;

        objInfo.pathToTheModel = objJson.get("model", "").asString();
        getVec3(objJson["position"], objInfo.position);
        getVec3(objJson["scale"], objInfo.scale, math::vec3(1.f, 1.f, 1.f));

        m_sceneConfig.objects.push_back(objInfo);
    }
}

void Config::parseLights(const Json::Value &root)
{
    // get ambient light
    const Json::Value jsonAmbient = root["Ambient"];
    if (!jsonAmbient.empty())
        getColor(jsonAmbient["intensity"], m_sceneConfig.ambIntensity, rend::Color3(255, 255, 255));

    // get directional lights
    const Json::Value jsonDirectional = root["Directional"];
    for (Json::Value::ArrayIndex idx = 0; idx < jsonDirectional.size(); ++idx)
    {
        SceneConfig::DirLightInfo light;
        getVec3(jsonDirectional[idx]["direction"], light.direction);
        getColor(jsonDirectional[idx]["intensity"], light.intensity);

        m_sceneConfig.dirLights.push_back(light);
    }

    // get point lights
    const Json::Value jsonPoint = root["Point"];
    if (!jsonPoint.empty())
    {
        SceneConfig::PointLightInfo light;
        getVec3(jsonPoint["position"], light.position);
        getColor(jsonPoint["intensity"], light.intensity);
        light.kc = jsonPoint.get("kc", 0.f).asFloat();
        light.kl = jsonPoint.get("kl", 0.f).asFloat();
        light.kq = jsonPoint.get("kq", 0.f).asFloat();

        m_sceneConfig.pointLights.push_back(light);
    }
}

Config::Config(const std::string &cfgDir)
{
    m_rendererConfig.makeDefaults();

    fs::path mainDir;

    cfgDir.empty() ? mainDir = DEFAULT_RENDERER_CONFIG : mainDir = cfgDir;
    m_rendererConfig.pathToTheAssets = mainDir.string();

    if (fs::exists(mainDir))
    {
        if (fs::is_regular_file(mainDir))
        {
            if (mainDir.extension() != ".json")
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

    std::string loadPath = fs::system_complete(mainDir).string();

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
