/*
 * decoderplg.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "decoderplg.h"

#include "resource.h"
#include "ospath.h"
#include "osfile.h"
#include "mesh.h"
#include "material.h"

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

sptr(Resource) DecoderPLG::decode(const OsPath &path)
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
    istringstream token(line);
    token >> temp >> numVertices >> numPolys;

    string resourceName(temp);

    vector<math::vertex> vertexList(numVertices);
    for (unsigned vertex = 0; vertex < numVertices; )
    {
        token.str("");
        temp = plgFile.getLine();
        if (temp.empty())
            continue;

        if (temp.at(0) == '#')
            continue;

        token.str(temp);

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

        PlgPolyData newData;

        token >> std::hex >> newData.descriptor >> std::dec >> newData.numVertices;

        // always three vertices
        if (newData.numVertices != 3)
        {
            *syslog << "Can't decode PLG file" << path.filePath() << ". Number of vertices =/= 3." << logerr;
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
        *syslog << "Can't decode PLG file" << path.filePath() << ". Empty polygons data." << logerr;
        return sptr(Resource)();
    }

    std::sort(polysData.begin(), polysData.end());

    auto newMesh = make_shared<rend::Mesh>();
    auto bounds = std::equal_range(polysData.begin(), polysData.end(), polysData.front());
    do
    {
        rend::VertexBuffer vb;
        vector<int> indices;

        std::for_each(bounds.first, bounds.second, [&indices](PlgPolyData data) {
                            std::copy(data.indices, data.indices + 3, std::back_inserter(indices));
                         });

        vb.appendVertices(vertexList, indices);

        auto material = make_shared<rend::Material>();
        // FIXME:
        material->ambientColor = rend::Color3(bounds.first->descriptor & 0x00FFFFFF);

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
            *syslog << "Bad shade mode in plg-file" << path.filePath() << ". Setting to defaults." << logwarn;
            shadeMode = rend::Material::SM_WIRE;
        }

        material->shadeMode = shadeMode;

        vb.setMaterial(material);
        vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
        newMesh->appendSubmesh(vb);

        if (bounds.second != polysData.end())
            bounds = std::equal_range(bounds.second, polysData.end(), *bounds.second);
        else
            break;
    } while (true);

    /*
        math::Triangle::SideType sideType;
        int sides = polyDescriptor & 0xF0000000;
        switch (sides)
        {
        case PLX_1SIDED_FLAG:
            sideType = math::Triangle::ST_1_SIDED;
            break;

        case PLX_2SIDED_FLAG:
            sideType = math::Triangle::ST_2_SIDED;
            break;

        default:
            *syslog << "Bad side flag in plg-file" << path.filePath() << ". Setting to defaults." << logwarn;
            sideType = math::Triangle::ST_2_SIDED;
        }

    */

    newMesh->setName(resourceName);

    *syslog << "Decoded plg-model \"" << newMesh->name()
            << "\". Number of vertices:" << newMesh->numVertices() << logmess;
    
    return newMesh;
}

string DecoderPLG::extention() const
{
    return "plg";
}

}
