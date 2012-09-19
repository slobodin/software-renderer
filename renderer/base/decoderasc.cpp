/*
 * decoderasc.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "decoderasc.h"

#include "resource.h"
#include "osfile.h"
#include "string_utils.h"
#include "color.h"
#include "mesh.h"
#include "vertexbuffer.h"
#include "material.h"
#include "sceneobject.h"

namespace base
{

void DecoderASC::parseVertices(string &line)
{
    auto pos = line.find('X');
    if (pos == string::npos)
        return;

    string x_str(line.begin() + pos + 2, line.begin() + line.find('Y'));

    pos = line.find('Y');
    string y_str(line.begin() + pos + 2, line.begin() + line.find('Z'));

    pos = line.find('Z');
    string z_str(line.begin() + pos + 2, line.end());

    common::eraseSpaces(x_str); common::eraseSpaces(y_str); common::eraseSpaces(z_str);

    double x = boost::lexical_cast<double>(x_str);
    double y = boost::lexical_cast<double>(y_str);
    double z = boost::lexical_cast<double>(z_str);

    math::vertex v;
    v.p.x = x;
    v.p.y = y;
    v.p.z = z;

    vertexList.push_back(v);
}

void DecoderASC::parseHeader(string &line)
{
    // find the name
    const string pattern = "Named object:";

    auto pos = line.find(pattern);
    if (pos == string::npos)
        return;

    objName = string(line.begin() + pos + 2 + pattern.size(), line.end() - 1);
}

void DecoderASC::parseFaceLine(string &line)
{
    auto pos = line.find('A');
    if (pos == string::npos)
        return;

    string a_str(line.begin() + pos + 2, line.begin() + line.find('B'));

    pos = line.find('B');
    string b_str(line.begin() + pos + 2, line.begin() + line.find('C'));

    pos = line.find('C');
    string c_str(line.begin() + pos + 2, std::find_if(line.begin() + pos + 2, line.end(),
                                                      [](char ch) -> bool { return (ch == 'A') || (ch == 'B') || (ch == 'C'); }));

    common::eraseSpaces(a_str); common::eraseSpaces(b_str); common::eraseSpaces(c_str);

    AscPolyData poly;
    poly.indices[0] = boost::lexical_cast<int>(a_str);
    poly.indices[1] = boost::lexical_cast<int>(b_str);
    poly.indices[2] = boost::lexical_cast<int>(c_str);

    faces.push_back(poly);
}

void DecoderASC::parseMaterialLine(string &line)
{
    string colorStr = line.substr(line.find(':'));

    faces.at(currPolyIndex).colorString = colorStr;

    auto pos = colorStr.find('r');
    if (pos == string::npos)
        return;

    string r_str(colorStr.begin() + pos + 1, colorStr.begin() + colorStr.find('g'));

    pos = colorStr.find('g');
    string g_str(colorStr.begin() + pos + 1, colorStr.begin() + colorStr.find('b'));

    pos = colorStr.find('b');
    string b_str(colorStr.begin() + pos + 1, colorStr.begin() + colorStr.find('a'));

    common::eraseSpaces(r_str); common::eraseSpaces(g_str); common::eraseSpaces(b_str);

    faces.at(currPolyIndex).color[rend::RED] = boost::lexical_cast<uint32_t>(r_str);
    faces.at(currPolyIndex).color[rend::GREEN] = boost::lexical_cast<uint32_t>(g_str);
    faces.at(currPolyIndex).color[rend::BLUE] = boost::lexical_cast<uint32_t>(b_str);

    currPolyIndex++;
}

void DecoderASC::parseHeaderVerts(string &/*line*/)
{
    // nothing
}

void DecoderASC::clear()
{
    objName = "";
    vertexList.clear();
    currPolyIndex = 0;
    faces.clear();
}

DecoderASC::DecoderASC()
    : currPolyIndex(0)
{
}

DecoderASC::~DecoderASC()
{
}

sptr(Resource) DecoderASC::decode(const string &path)
{
    clear();

    TextFile ascFile(path);

    parseWhile(&DecoderASC::parseHeader, "Tri-mesh", ascFile);
    parseWhile(&DecoderASC::parseHeaderVerts, "Vertex list:", ascFile);
    parseWhile(&DecoderASC::parseVertices, "Face list:", ascFile);

    string line;
    currPolyIndex = 0;
    do
    {
        line = ascFile.getLine();

        if (line.empty())
            continue;

        if (line == "END_OF_FILE")
            break;

        if (line.find("Face") != string::npos)
            parseFaceLine(line);

        if (line.find("Material") != string::npos)
            parseMaterialLine(line);

        line.clear();

    } while (line.empty());

    std::sort(faces.begin(), faces.end());

    auto newMesh = make_shared<rend::Mesh>();
    auto bounds = std::equal_range(faces.begin(), faces.end(), faces.front());
    do
    {
        rend::VertexBuffer vb;
        vector<int> indices;

        std::for_each(bounds.first, bounds.second, [&indices](const AscPolyData &data)
                      { std::copy(data.indices, data.indices + 3, std::back_inserter(indices)); });

        vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
        vb.appendVertices(vertexList, indices);

        auto material = make_shared<rend::Material>();
        material->plainColor = bounds.first->color;
        material->ambientColor = bounds.first->color;
        material->diffuseColor = bounds.first->color;

        material->shadeMode = rend::Material::SM_FLAT;
        material->sideType = rend::Material::ONE_SIDE;

        vb.setMaterial(material);

        newMesh->appendSubmesh(vb);

        if (bounds.second != faces.end())
            bounds = std::equal_range(bounds.second, faces.end(), *bounds.second);
        else
            break;

    } while (true);

    auto newObject = make_shared<rend::SceneObject>(newMesh);

    if (!objName.empty())
        newObject->setName(objName);

    syslog << "Decoded asc-model \"" << newObject->getName()
            << "\". Number of vertices:" << newMesh->numVertices()
            << ". Number of faces:" << faces.size() << logmess;

    return newObject;
}

string DecoderASC::extension() const
{
    return "asc";
}

}
