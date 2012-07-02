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
    pathToTheAssets = "";   // executable dir
}

static void operator>> (const YAML::Node &node, math::vec3 &v)
{
    node[0] >> v.x;
    node[1] >> v.y;
    node[2] >> v.z;
}

static void operator>> (const YAML::Node &node, SceneConfig::ObjInfo &objInfo)
{
    node["model"] >> objInfo.pathToTheModel;
    node["position"] >> objInfo.position;
}

//! Finds value by the key and stores it in `value'.
/** If can't find value - sets it to default. */
template<typename T>
bool FindValue(const YAML::Node &doc, T &value, string key, const T defaultValue)
{
    if(const YAML::Node *pName = doc.FindValue(key))
    {
        *pName >> value;
    }
    else
    {
        syslog << "Can't find" << key << ". Setting to default value" << defaultValue << logwarn;
        value = defaultValue;
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
}
catch (YAML::Exception &e)
{
    syslog << "Error while parsing config file. Setting to defaults.\nError:"
           << e.what() << logerr;

    m_rendererConfig.makeDefaults();
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

    string loadPath = fs::complete(mainDir).string();

    std::ifstream rendererConfigFile(loadPath);

    if (rendererConfigFile)
    {
        m_rendererConfigData << rendererConfigFile.rdbuf();
        parseRendererConfig();
    }
    else
        syslog << "Cannot open config file. Setting defaults." << logwarn;
}

RendererConfig Config::getRendererConfig() const
{
    return m_rendererConfig;
}

SceneConfig Config::getSceneConfig() const
{
    return m_sceneConfig;
}

void Config::configure(Controller *controller)
{
    /*std::fstream inconf(path.filePath());
    if (!inconf)
    {
        *syslog << "Can't open configuration file" << logerr;
        return;
    }

    vector<ModelData> modelData;
    try
    {
        YAML::Parser parser(inconf);
        YAML::Node doc;

        parser.GetNextDocument(doc);
        for (YAML::Iterator i = doc.begin(); i != doc.end(); ++i)
        {
            const YAML::Node &value = i.second();

            for(unsigned i = 0; i < value.size(); i++)
            {
                ModelData currdata;
                value[i] >> currdata;
                modelData.push_back(currdata);
            }
        }

        parser.GetNextDocument(doc);
        math::vec3 vectCam;
        int width, height;
        doc["Campos"] >> vectCam;
        controller->m_mainCam->setPosition(vectCam);

        doc["Width"] >> width;
        doc["Height"] >> height;

        controller->resize(width, height);
    }
    catch(YAML::Exception &e)
    {
        *syslog << "Error while parsing config file. Setting to defaults."
                << e.what() << logerr;
        modelData.clear();
    }

    for (unsigned i = 0; i < modelData.size(); i++)
    {
        string modelpath = modelData[i].modelpath;
        if (modelpath.empty())
        {
            *syslog << "Empty model name" << logwarn;
            continue;
        }

        // load resource
        sptr(base::Resource) gettedResource = controller->m_resourceMgr->getResource(modelpath);
        if (!gettedResource)
            continue;

        // check: is it rendering item?
        sptr(rend::Mesh) renderItem = dynamic_pointer_cast<rend::Mesh>(gettedResource);
        if (!renderItem)
        {
            *syslog << "Can't render" << modelpath << logerr;
            continue;
        }

        // save it
        renderItem->setPosition(modelData[i].pos);
        //renderItem->setWindingOrder(modelData[i].wo);
        controller->m_rendmgr->addMesh(renderItem);
    }*/
}

}
