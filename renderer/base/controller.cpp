#include "controller.h"

#include <yaml-cpp/yaml.h>
#include <third-party/cpptk-1.0.2/cpptk.h>
#include <tcl/tk.h>
#include "vec3.h"

namespace base
{

struct ModelData
{
    string modelpath;
    math::vec3 pos;
    rend::Color3 color;
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
}

using namespace Tk;

void Controller::update()
{
    m_instance->m_rendmgr->update();

    Tk::after(50, m_instance->m_updateCallback);
}

void Controller::processMouse(int x, int y)
{
    *syslog << "Mouse x:" << x << "y:" << y << logmess;

    static int dx;
    static int dy;

    m_instance->m_rendmgr->rotate(dx, dy);

    dx++;
    dy++;


//    dx = m_targetWindow->currMouseState().x - m_targetWindow->prevMouseState().x;
//    dy = m_targetWindow->currMouseState().y - m_targetWindow->prevMouseState().y;

//    if (m_targetWindow->currMouseState().isLeftPressed())
//    {
//        rotate(dx, dy);
//        windowState |= RenderWindow::ET_REDRAW_RASTERIZE;
//    }
//    if (m_targetWindow->currMouseState().isRightPressed())
//    {
//        move(dx, dy);
//        windowState |= RenderWindow::ET_REDRAW_RASTERIZE;
//    }
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

    m_rendmgr.reset(new rend::RenderMgr(640, 480));

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
        m_rendmgr->addMesh(renderItem);
    }

    Tk::init(argv[0]);

    Tk::wm(Tk::title, ".", "Result");

    Tk::images(Tk::create, Tk::photo, "canvas_photo")
            -Tk::width(640)
            -Tk::height(480);
    Tk::canvas(".c") -Tk::highlightthickness(0)
            -Tk::width(640)
            -Tk::height(480);
    Tk::pack(".c") -Tk::fill(Tk::both) -Tk::expand(true);
    (".c" << Tk::create(Tk::image, 0, 0)) -Tk::image("canvas_photo") -Tk::anchor(nw);

    Tk::bind(".", "<Button-1>", &Controller::processMouse, event_x, event_y);

    m_updateCallback = Tk::callback(&Controller::update);
    Tk::after(500, m_updateCallback);

}

void Controller::run()
{
    Tk::runEventLoop();
}

}
