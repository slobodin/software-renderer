/*
 * config.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "config.h"

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
    pathToTheAssets = fs::system_complete(fs::current_path<fs::path>()).string();   // executable directory
    rendererMode = "software";
}

void Config::parseRendererConfig()
{
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
    // objects

    // getting scene lights
    parseLights();
}

void Config::parseLights()
{
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
