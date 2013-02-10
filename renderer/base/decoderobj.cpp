/*
 * decoderobj.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "decoderobj.h"

#include "vertexbuffer.h"
#include "mesh.h"
#include "sceneobject.h"
#include "color.h"
#include "material.h"
#include "poly.h"

namespace base
{

void DecoderOBJ::appendVertex(std::string &line)
{
    line = line.substr(line.find(' ') + 1);

    std::istringstream is(line);
    math::vertex v;

    is >> v.p.x >> v.p.y >> v.p.z;

    vertexList.push_back(v);
}

void DecoderOBJ::appendFace(std::string &line)
{
    line = line.substr(line.find(' ') + 1);

    std::istringstream is(line);
    FaceInfo face;

    if (line.find("//") != std::string::npos)
    {
        std::vector<std::string> tokens;
        common::tokenize(tokens, line, "// ");
        
        int i = 0;
        for (auto tokIter = tokens.begin(); tokIter != tokens.end(); ++tokIter, ++i)
        {
            if (i % 2 == 0)
                face.indices.push_back(common::fromString<int>(*tokIter));
            else
                face.normalIndices.push_back(common::fromString<int>(*tokIter));
        }
    }
    else if (line.find("/") != std::string::npos)
    {
        // Vertex/texture-coordinate format
        throw std::runtime_error("Unsupported obj file");
    }
    else
    {
        copy(std::istream_iterator<int>(is), std::istream_iterator<int>(), std::back_inserter(face.indices));
    }

    faces.push_back(face);
}

void DecoderOBJ::appendNormal(std::string &line)
{
    line = line.substr(line.find(' ') + 1);

    std::istringstream is(line);
    math::vec3 n;

    is >> n.x >> n.y >> n.z;

    normalsList.push_back(n);
}

void DecoderOBJ::triangulateModel()
{
    for (auto f : faces)
    {
        std::vector<math::vertex> polyVerts;
        std::vector<int> polyInds;

        // create polygon
        std::for_each(f.indices.begin(), f.indices.end(), [&polyVerts, &polyInds, this](int ind)
                      { polyVerts.push_back(vertexList.at(ind - 1)); polyInds.push_back(ind - 1); });        // indices starting from 1 to N [1, N]

        // store normals (if they are present)
        if (!f.normalIndices.empty())
        {
            assert(f.normalIndices.size() == f.indices.size());
            for (size_t i = 0; i < f.indices.size(); i++)
            {
                auto &n = normalsList.at(f.normalIndices[i] - 1);

                // normals might not be unit in .obj file.
//                n.normalize();
                vertexList.at(f.indices[i] - 1).n = n;
            }
        }

        // triangulate a polygon
        std::vector<int> polyIndsTriangulated;
        math::Triangulate(polyVerts, polyInds, polyIndsTriangulated);

        resultTrianglesIndices.insert(resultTrianglesIndices.end(), polyIndsTriangulated.begin(), polyIndsTriangulated.end());
    }
}

void DecoderOBJ::clear()
{
    vertexList.clear();
    faces.clear();
    resultTrianglesIndices.clear();
    normalsList.clear();
}

sptr(Resource) DecoderOBJ::decode(const std::string &path)
{
    clear();

    TextFile objFile(path);

    std::string line;
    do
    {
        line = objFile.getLine();

        if (line == "END_OF_FILE")
            break;

        if (line.find("vt") != std::string::npos)
        { }

        if (line.find("vn") != std::string::npos)
            appendNormal(line);

        if (line.find("vp") != std::string::npos)
        { }

        if (line.at(0) == 'v')
            appendVertex(line);

        if (line.at(0) == 'f')
            appendFace(line);

        line.clear();

    } while (line.empty());

    if (faces.empty() || vertexList.empty())
    {
        syslog << "Unable to parse .obj file" << path << logwarn;
        return sptr(Resource)();
    }

    auto newMesh = std::make_shared<rend::Mesh>();

    triangulateModel();

    rend::VertexBuffer vb;
    vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
    vb.appendVertices(vertexList, resultTrianglesIndices, !normalsList.empty());

    auto material = std::make_shared<rend::Material>();

    material->plainColor = rend::Color3(255, 255, 255);
    material->ambientColor = rend::Color3(255, 255, 255);
    material->diffuseColor = rend::Color3(255, 255, 255);

    material->shadeMode = rend::Material::SM_FLAT;
    material->sideType = rend::Material::ONE_SIDE;

    vb.setMaterial(material);

    newMesh->appendSubmesh(vb);

    auto newObject = std::make_shared<rend::SceneObject>(newMesh);

    std::tr2::sys::path p(path);
    newObject->setName(p.filename());

    syslog << "Decoded obj-model \"" << newObject->getName()
            << "\". Number of vertices:" << newMesh->numVertices()
            << ". Number of faces:" << faces.size() << logmess;

    return newObject;
}

std::string DecoderOBJ::extension() const
{
    return "obj";
}

}
