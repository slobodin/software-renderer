#include "controller.h"

#include <yaml-cpp/yaml.h>

namespace base
{

Controller::Controller(const string &conf)
{
    std::fstream inconf(conf);
    if (!inconf)
    {
        *syslog << "Can't open configuration file" << logerr;
        return;
    }

    try
    {
        YAML::Parser parser(inconf);
        YAML::Node doc;

        parser.GetNextDocument(doc);
        doc["model"] >> m_modelName;
    }
    catch(YAML::Exception &e)
    {
        *syslog << "Error while parsing config file"
                << e.what() << logerr;
    }

    m_rendmgr.reset(new rend::RenderMgr(640, 480));
    m_rendmgr->addRenderable(m_modelName);
}

}
