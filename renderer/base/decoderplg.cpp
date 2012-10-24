/*
 * decoderplg.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "decoderplg.h"

#include "resource.h"
#include "osfile.h"
#include "mesh.h"
#include "material.h"
#include "sceneobject.h"
#include "poly.h"

namespace base
{

static const uint32_t PLX_1SIDED_FLAG           = 0x00000000;   // this poly is single sided
static const uint32_t PLX_2SIDED_FLAG           = 0x10000000;   // this poly is double sided
static const uint32_t PLX_SHADE_MODE_FLAT       = 0x02000000;   // this poly uses flat shading
static const uint32_t PLX_SHADE_MODE_GOURAUD    = 0x04000000;   // this poly uses gouraud shading
static const uint32_t PLX_SHADE_MODE_WIRE       = 0x08000000;   // this poly is wireframe


struct PlgPolyData
{
    uint32_t descriptor;    // poly descriptor (holds info about color and other properties)
    rend::Color3 color;
    int numVertices;        // always three
    int indices[3];

    // we need to sort all polygon data and create particular vertex buffers (with same material)
    // all vertex buffers will form the mesh
    bool operator< (const PlgPolyData &other) const
    {
        return descriptor < other.descriptor;
    }
    bool operator== (const PlgPolyData &other) const
    {
        return descriptor == other.descriptor;
    }
};

sptr(Resource) DecoderPLG::decode(const string &path)
{
    TextFile plgFile(path);

    // skip comments and find "header"
    string line;
    string temp;    // temp container for holding file data

    do
    {
        line = plgFile.getLine();

        if (line.empty())
            continue;

        if (line.at(0) != '#')
            break;

        line.clear();

    } while (line.empty());

    unsigned numVertices, numPolys;

    // skip obj name and get number of vertices and polygons
    std::istringstream token(line);
    token >> temp >> numVertices >> numPolys;

    string resourceName(temp);

    vector<math::vertex> vertexList(numVertices);
    for (unsigned vertex = 0; vertex < numVertices; )
    {
        temp = plgFile.getLine();
        if (temp.empty())
            continue;

        if (temp.at(0) == '#')
            continue;

        token.str(temp);
        token.seekg(0);     // HACK:

        math::vec3 pt;
        token >> pt.x >> pt.y >> pt.z;

        vertexList[vertex++].p = pt;
    }

    // now load polygons
    vector<PlgPolyData> polysData(numPolys);
    for (unsigned poly = 0; poly < numPolys; )
    {
        token.str("");
        temp = plgFile.getLine();
        if (temp.empty())
            continue;

        if (temp.at(0) == '#')
            continue;

        token.str(temp);
        token.seekg(0);

        PlgPolyData newData;

        token >> std::hex >> newData.descriptor >> std::dec >> newData.numVertices;

        // always three vertices
        if (newData.numVertices != 3)
        {
            syslog << "Can't decode PLG file" << path << ". Number of vertices =/= 3." << logerr;
            return sptr(Resource)();
        }

        for (int i = 0; i < newData.numVertices; i++)
        {
            int index;
            token >> index;
            newData.indices[i] = index;
        }

        polysData[poly++] = newData;
    }

    if (polysData.empty())
    {
        syslog << "Can't decode PLG file" << path << ". Empty polygons data." << logerr;
        return sptr(Resource)();
    }

    std::sort(polysData.begin(), polysData.end());

    auto newMesh = make_shared<rend::Mesh>();
    auto bounds = std::equal_range(polysData.begin(), polysData.end(), polysData.front());
    do
    {
        rend::VertexBuffer vb;
        vector<int> indices;

        std::for_each(bounds.first, bounds.second, [&indices](const PlgPolyData &data)
        { std::copy(data.indices, data.indices + 3, std::back_inserter(indices)); });

        vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
        vb.appendVertices(vertexList, indices);

        auto material = make_shared<rend::Material>();
        material->plainColor = rend::Color3(bounds.first->descriptor & 0x00FFFFFF);
        material->ambientColor = rend::Color3(bounds.first->descriptor & 0x00FFFFFF);
        material->diffuseColor = rend::Color3(bounds.first->descriptor & 0x00FFFFFF);

        // setting shade mode
        rend::Material::ShadeMode shadeMode;
        int sm = bounds.first->descriptor & 0x0F000000;   // mask to extract shading mode
        switch (sm)
        {
        case PLX_SHADE_MODE_FLAT:
            shadeMode = rend::Material::SM_FLAT;
            break;

        case PLX_SHADE_MODE_GOURAUD:
            shadeMode = rend::Material::SM_GOURAUD;
            break;

        case PLX_SHADE_MODE_WIRE:
            shadeMode = rend::Material::SM_WIRE;
            break;

        default:
            syslog << "Bad shade mode in plg-file" << path << ". Setting defaults." << logwarn;
            shadeMode = rend::Material::SM_PLAIN_COLOR;
        }

        material->shadeMode = shadeMode;

        // setting "sideness"
        rend::Material::SideType sideType;
        int sides = bounds.first->descriptor & 0xF0000000;
        switch (sides)
        {
        case PLX_1SIDED_FLAG:
            sideType = rend::Material::ONE_SIDE;
            break;

        case PLX_2SIDED_FLAG:
            sideType = rend::Material::TWO_SIDE;
            break;

        default:
            syslog << "Bad side flag in plg-file" << path << ". Setting to defaults." << logwarn;
            sideType = rend::Material::ONE_SIDE;
        }

        material->sideType = sideType;

        vb.setMaterial(material);
        newMesh->appendSubmesh(vb);

        if (bounds.second != polysData.end())
            bounds = std::equal_range(bounds.second, polysData.end(), *bounds.second);
        else
            break;
    } while (true);

    auto newObject = make_shared<rend::SceneObject>(newMesh);

    newObject->setName(resourceName);

    syslog << "Decoded plg-model \"" << newObject->getName()
            << "\". Number of vertices:" << newMesh->numVertices() << logmess;
    
    return newObject;
}

string DecoderPLG::extension() const
{
    return "plg";
}

}
