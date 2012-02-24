#include "controller.h"

#include <yaml-cpp/yaml.h>
#include <third-party/cpptk-1.0.2/cpptk.h>
#include "vec3.h"

namespace base
{

struct ModelData
{
    string modelpath;
    math::vec3 pos;
    rend::Color3 color;
    bool wireframe;
};

void operator>> (const YAML::Node &node, math::vec3 &v)
{
    node[0] >> v.x;
    node[1] >> v.y;
    node[2] >> v.z;
}

void operator>> (const YAML::Node &node, rend::Color3 &c)
{
    node[0] >> c.red();
    node[1] >> c.green();
    node[2] >> c.blue();
}

void operator>> (const YAML::Node &node, ModelData &data)
{
    node["model"] >> data.modelpath;
    node["position"] >> data.pos;
    node["wireframe"] >> data.wireframe;
}

using namespace Tk;

void Controller::update()
{
    m_instance->m_rendmgr->update();

    Tk::after(30, m_instance->m_updateCallback);
}

Controller::Controller(char *argv[], const string &conf)
    : m_resourceMgr(new ResourceMgr)
{
    std::fstream inconf(conf);
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
        for(unsigned i = 0;i < doc.size(); i++)
        {
            ModelData currdata;
            doc[i] >> currdata;
            modelData.push_back(currdata);
        }
    }
    catch(YAML::Exception &e)
    {
        *syslog << "Error while parsing config file"
                << e.what() << logerr;
    }

    m_mainCam = SPTR(rend::Camera)(new rend::Camera(math::vec3(), 640, 480));
    m_rendmgr.reset(new rend::RenderMgr(m_mainCam));

    for (unsigned i = 0; i < modelData.size(); i++)
    {
        string modelpath = modelData[i].modelpath;
        if (modelpath.empty())
        {
            *syslog << "Empty model name" << logwarn;
            continue;
        }

        // load resource
        SPTR(base::Resource) gettedResource = m_resourceMgr->getResource(modelpath);
        if (!gettedResource)
            continue;

        // check: is it rendering item?
        SPTR(rend::Mesh) renderItem = dynamic_pointer_cast<rend::Mesh>(gettedResource);
        if (!renderItem)
        {
            *syslog << "Can't render" << modelpath << logerr;
            continue;
        }

        // save it
        renderItem->setPosition(modelData[i].pos);
        renderItem->wireframe() = modelData[i].wireframe;
        m_rendmgr->addMesh(renderItem);
    }

    Tk::init(argv[0]);

    Tk::wm(Tk::title, ".", "Result");

    // create rendering canvas
    Tk::images(Tk::create, Tk::photo, "canvas_photo")
            -Tk::width(640)
            -Tk::height(480);
    Tk::canvas(".c") -Tk::highlightthickness(0)
            -Tk::width(640)
            -Tk::height(480);
    Tk::pack(".c") -Tk::fill(Tk::both) -Tk::expand(true);
    (".c" << Tk::create(Tk::image, 0, 0)) -Tk::image("canvas_photo") -Tk::anchor(nw);
    m_rendmgr->renderTo("canvas_photo");

    // setup update event
    m_updateCallback = Tk::callback(&Controller::update);
    Tk::after(500, m_updateCallback);
}

Controller::~Controller()
{
}

SPTR(rend::Camera) Controller::camera()
{
    return m_mainCam;
}

void Controller::run()
{
    Tk::runEventLoop();
}

}
