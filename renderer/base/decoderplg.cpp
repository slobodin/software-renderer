/*
 * decoderplg.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "decoderplg.h"

#include "osfile.h"
#include "mesh.h"
#include "material.h"

namespace base
{

static const int PLX_1SIDED_FLAG           = 0x0000;   // this poly is single sided
static const int PLX_2SIDED_FLAG           = 0x1000;   // this poly is double sided
static const int PLX_SHADE_MODE_FLAT       = 0x2000;   // this poly uses flat shading
//static const int PLX_SHADE_MODE_PHONG    = 0x4000;   // this poly used phong shading
static const int PLX_SHADE_MODE_GOURAUD    = 0x4000;   // this poly uses gouraud shading
static const int PLX_SHADE_MODE_WIRE       = 0x8000;   // this poly is wireframe

DecoderPLG::DecoderPLG()
{
}

DecoderPLG::~DecoderPLG()
{
}

sptr(Resource) DecoderPLG::decode(const OsPath &path)
{
    TextFile plgFile(path);

    // skip comments and find "header"
    string line;
    string temp;

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
    string resourceName = temp;

    vector<math::vertex> vertexList(numVertices);
    for (unsigned vertex = 0; vertex < numVertices; vertex++)
    {
        token.str("");
        temp = plgFile.getLine();
        if (temp.empty())
        {
            vertex--;
            continue;
        }

        if (temp.at(0) == '#')
        {
            vertex--;    // dirty hack. vertex is unsigned
            continue;
        }

        token.str(temp);

        math::vec3 pt;
        token >> pt.x >> pt.y >> pt.z;
        vertexList[vertex].p = pt;
    }

    // now load polygons and save it into mesh
    vector<size_t> indices;
    vector<rend::Material> materials;
    for (unsigned poly = 0; poly < numPolys; poly++)
    {
        token.str("");
        temp = plgFile.getLine();
        if (temp.empty())
        {
            poly--;
            continue;
        }

        if (temp.at(0) == '#')
        {
            poly--;    // dirty hack. vertex is unsigned
            continue;
        }

        token.str(temp);

        int polyDescriptor;
        unsigned numVertsByPoly;

        token >> std::hex >> polyDescriptor >> std::dec >> numVertsByPoly;

        for (unsigned i = 0; i < numVertsByPoly; i++)
        {
            int index;
            token >> index;
            indices.push_back(index);
        }

        int red = polyDescriptor & 0x0F00;
        int green = polyDescriptor & 0x00F0;
        int blue = polyDescriptor & 0x000F;

        rend::Material::ShadeMode shadeMode;
        int sm = polyDescriptor & 0xE000;   // mask to extract shading mode
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

        math::Triangle::SideType sideType;
        int sides = polyDescriptor & 0x1000;
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

        rend::Color3 col(red, green, blue);
        materials.push_back(rend::Material(col, shadeMode/*, sideType*/));
    }

    sptr(rend::Mesh) newMesh(new rend::Mesh(vertexList,
                                            indices,
                                            materials,
                                            rend::Mesh::MT_MESH_INDEXEDTRIANGLELIST));
    newMesh->setName(resourceName);
    newMesh->computeVertexNormals();

    *syslog << "Decoded plg-model \"" << newMesh->name() << "\". Number of vertices:" << newMesh->numVertices() << logmess;
    
    return newMesh;
}

string DecoderPLG::extention() const
{
    return "plg";
}

}
