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

void DecoderCOB::parseUV(string &line)
{
    if (line.find("Faces") != string::npos)
        return;

    std::istringstream is(line);

    math::vec2 u_v;
    is >> u_v.x >> u_v.y;

    uv.push_back(u_v);
}

void DecoderCOB::parseFaces(string &line)
{
    if (line.find("DrawFlags") != string::npos)
        return;

    string temp;

    temp = "Face verts";
    if (line.find(temp) != string::npos)
    {
        currFace++;
        faces.push_back(FaceInfo());

        string vertCountStr(line.begin() + temp.length() + 1, line.end());

        vertCountStr = string(vertCountStr.begin(), vertCountStr.begin() + vertCountStr.find(' '));

        int vertCount = common::fromString<int>(vertCountStr);
        if (vertCount != 3)
            /*return*/throw COBFileFormatExcetion("Invalid face in cob file.");       // nahui

        string matIndStr(line.begin() + line.find("mat") + 4, line.end());
        faces.at(currFace).materialIndex = common::fromString<int>(matIndStr);

        return;
    }

    if (line.at(0) == '<')
    {
        for (int i = 0; i < 3; i++)
        {
            line.erase(line.begin(), line.begin() + line.find('<') + 1);

            string indStr = string(line.begin(), line.begin() + line.find(','));
            int ind = common::fromString<int>(indStr);

            faces.at(currFace).indices[i] = ind;

            string uvStr = string(line.begin() + line.find(',') + 1, line.begin() + line.find('>'));
            int uvInd = common::fromString<int>(uvStr);

            faces.at(currFace).uvIndices[i] = uvInd;
        }

        return;
    }
}

void DecoderCOB::parseMaterials(string &line)
{
    // check for material index
    if (line.find("mat#") != string::npos)
    {
        currMaterial++;
        materials.push_back(MaterialInfo());

        string matInd = string(line.begin() + line.find(' ') + 1, line.end());
        materials.at(currMaterial).matIndex = common::fromString<int>(matInd);

        return;
    }

    // check for material color
    if (line.find("rgb") != string::npos)
    {
        string col = string(line.begin() + line.find(' ') + 1, line.end());
        std::istringstream is(col);

        double r, g, b;
        is >> r; is.ignore(1, ',');
        is >> g; is.ignore(1, ',');
        is >> b; is.ignore(1, ',');

        rend::Color3 matColor;
        matColor[rend::RED] = r * 255.0;
        matColor[rend::GREEN] = g * 255.0;;
        matColor[rend::BLUE] = b * 255.0;;

        materials.at(currMaterial).color = matColor;

        return;
    }

    if (line.find("Shader class: color") != string::npos)
    {

        return;
    }
}

void DecoderCOB::clear()
{
    m_name = "";
    currVertex = 0;

    vertexList.clear();

    materials.clear();
    currMaterial = -1;

    faces.clear();
    currFace = -1;

    uv.clear();
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
    parseWhile(&DecoderCOB::parseMaterials, "END", cobFile);

    for (auto f : faces)
    {
        vertexList.at(f.indices[0]).t = uv.at(f.uvIndices[0]);
        vertexList.at(f.indices[1]).t = uv.at(f.uvIndices[1]);
        vertexList.at(f.indices[2]).t = uv.at(f.uvIndices[2]);
    }

    std::sort(faces.begin(), faces.end());

    auto newMesh = make_shared<rend::Mesh>();
    auto bounds = std::equal_range(faces.begin(), faces.end(), faces.front());
    do
    {
        rend::VertexBuffer vb;
        vector<int> indices;

        std::for_each(bounds.first, bounds.second, [&indices](const FaceInfo &data)
                      { std::copy(data.indices, data.indices + 3, std::back_inserter(indices)); });

        vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
        vb.appendVertices(vertexList, indices);

        auto material = make_shared<rend::Material>();
        int materialIndex = bounds.first->materialIndex;

        auto mt = std::find(materials.begin(), materials.end(), MaterialInfo(materialIndex));

        material->plainColor = materials.at(mt->matIndex).color;
        material->ambientColor = materials.at(mt->matIndex).color;
        material->diffuseColor = materials.at(mt->matIndex).color;

        // setting shade mode
        rend::Material::ShadeMode shadeMode;
        shadeMode = rend::Material::SM_PLAIN_COLOR;

        material->shadeMode = shadeMode;

        // setting "sideness"
        rend::Material::SideType sideType;
        sideType = rend::Material::TWO_SIDE;

        material->sideType = sideType;

        vb.setMaterial(material);
        newMesh->appendSubmesh(vb);

        if (bounds.second != faces.end())
            bounds = std::equal_range(bounds.second, faces.end(), *bounds.second);
        else
            break;

    } while (true);

    auto newObject = make_shared<rend::SceneObject>(newMesh);

    if (!m_name.empty())
        newObject->setName(m_name);

    syslog << "Decoded cob-model \"" << newObject->getName()
            << "\". Number of vertices:" << newMesh->numVertices()
            << ". Number of faces:" << faces.size() << logmess;

    return newObject;
}

string DecoderCOB::extension() const
{
    return "cob";
}

}
