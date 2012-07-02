/*
 * config.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "vec3.h"

namespace base
{

class Controller;
class ResourceMgr;

struct RendererConfig
{
    math::vec3  camPosition;
    int         width;
    int         height;
    string      pathToTheAssets;

    void makeDefaults();
};

struct SceneConfig
{
    struct ObjInfo
    {
        math::vec3 position;
        string pathToTheModel;
    };

    vector<ObjInfo> objects;
};

class Config
{
    RendererConfig m_rendererConfig;
    std::stringstream m_rendererConfigData;
    void parseRendererConfig();

    SceneConfig m_sceneConfig;
    std::stringstream m_sceneConfigData;

public:
    Config(const string &cfgDir = "");

    RendererConfig getRendererConfig() const;
    SceneConfig getSceneConfig() const;

    void configure(Controller *controller);
};

}

#endif // CONFIG_H
