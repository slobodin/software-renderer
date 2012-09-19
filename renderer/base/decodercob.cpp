/*
 * decodercob.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decodercob.h"

#include "osfile.h"
#include "string_utils.h"
#include "vertexbuffer.h"
#include "mesh.h"
#include "material.h"
#include "sceneobject.h"

namespace base
{

void DecoderCOB::parseHeader(string &line)
{
    if (line.find("Name") == string::npos)
        return;

    m_name = line.substr(line.find(' ') + 1);
}

void DecoderCOB::parseTransform(string &line)
{
    if (line.find("World Vertices") == string::npos)
        return;

    string sizestr = line.substr(line.find_last_of(' ') + 1);
    int sz = common::fromString<int>(sizestr);

    vertexList.resize(sz);
}

void DecoderCOB::parseVertices(string &line)
{
    if (line.find("Texture Vertices") != string::npos)
        return;

    std::istringstream is(line);

    math::vertex v;
    is >> v.p.x >> v.p.y >> v.p.z;

    vertexList.at(currVertex++) = v;
}

void DecoderCOB::parseUV(string &/*line*/)
{
    // nothing
}

void DecoderCOB::parseFaces(string &line)
{
    if (line.find("DrawFlags") != string::npos)
        return;

    string temp;

    temp = "Face verts";
    if (line.find(temp) != string::npos)
    {
        string vertCountStr(line.begin() + temp.length() + 1, line.end());

        vertCountStr = string(vertCountStr.begin(), vertCountStr.begin() + vertCountStr.find(' '));

        int vertCount = common::fromString<int>(vertCountStr);
        if (vertCount != 3)
        {
            syslog << "Invalid face in cob file" << logwarn;
            return;
        }

        return;
    }

    if (line.at(0) == '<')
    {
        for (int i = 0; i < 3; i++)
        {
            line.erase(line.begin(), line.begin() + line.find('<') + 1);

            string indStr = string(line.begin(), line.begin() + line.find(','));
            int ind = common::fromString<int>(indStr);

            indices.push_back(ind);
        }

        return;
    }
}

void DecoderCOB::clear()
{
    m_name = "";
    currVertex = 0;

    vertexList.clear();
    indices.clear();
}

DecoderCOB::DecoderCOB()
{
}

DecoderCOB::~DecoderCOB()
{
}

sptr(Resource) DecoderCOB::decode(const string &path)
{
    clear();

    TextFile cobFile(path);

    string line = cobFile.getLine();
    if (line.find("Caligari V00.01ALH") == string::npos)
    {
        syslog << "Unsupported cob file" << logwarn;
        return sptr(Resource)();
    }

    parseWhile(&DecoderCOB::parseHeader, "Transform", cobFile);
    parseWhile(&DecoderCOB::parseTransform, "World Vertices", cobFile);

    if (vertexList.size() <= 0)
    {
        syslog << "Can't parse cob file. Invalid vertices array size." << logwarn;
        return sptr(Resource)();
    }

    parseWhile(&DecoderCOB::parseVertices, "Texture Vertices", cobFile);
    parseWhile(&DecoderCOB::parseUV, "Faces", cobFile);
    parseWhile(&DecoderCOB::parseFaces, "DrawFlags", cobFile);

    auto newMesh = make_shared<rend::Mesh>();

    rend::VertexBuffer vb;

    vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
    vb.appendVertices(vertexList, indices);

    auto material = make_shared<rend::Material>();
    material->plainColor = rend::Color3(255, 255, 255);
    material->ambientColor = rend::Color3(255, 255, 255);
    material->diffuseColor = rend::Color3(255, 255, 255);
    material->shadeMode = rend::Material::SM_FLAT;
    material->sideType = rend::Material::TWO_SIDE;

    vb.setMaterial(material);

    newMesh->appendSubmesh(vb);

    // create scene object
    auto newObject = make_shared<rend::SceneObject>(newMesh);

    if (!m_name.empty())
        newObject->setName(m_name);

    syslog << "Decoded cob-model \"" << newObject->getName()
            << "\". Number of vertices:" << newMesh->numVertices() << logmess;
//            << ". Number of faces:" << faces.size() << logmess;

    return newObject;
}

string DecoderCOB::extension() const
{
    return "cob";
}

}
