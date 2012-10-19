/*
 * decoderobj.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decoderobj.h"
#include "vertexbuffer.h"
#include "mesh.h"
#include "sceneobject.h"
#include "color.h"
#include "material.h"
#include "poly.h"
#include "string_utils.h"

namespace base
{

void DecoderOBJ::appendVertex(string &line)
{
    line = line.substr(line.find(' ') + 1);

    std::istringstream is(line);
    math::vertex v;

    is >> v.p.x >> v.p.y >> v.p.z;

    vertexList.push_back(v);
}

void DecoderOBJ::appendFace(string &line)
{
    line = line.substr(line.find(' ') + 1);

    std::istringstream is(line);
    FaceInfo face;

    if (line.find("//") != string::npos)
    {
        boost::char_separator<char> sep("// ");
        boost::tokenizer<boost::char_separator<char> > tokens(line, sep);
        int i = 0;

        for (auto tokIter = tokens.begin(); tokIter != tokens.end(); ++tokIter, ++i)
        {
            if (i % 2 == 0)
                face.indices.push_back(common::fromString<int>(*tokIter));
            // omit normals for now
        }
    }
    else if (line.find("/") != string::npos)
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

void DecoderOBJ::triangulateModel()
{
    for (auto f : faces)
    {
        vector<math::vertex> polyVerts;

        // create polygon
        std::for_each(f.indices.begin(), f.indices.end(), [&polyVerts, this](int ind)
                      { polyVerts.push_back(vertexList.at(ind - 1)); });        // indices starting from 1 to N [1, N]

        vector<math::Triangle> trias;
        math::Polygon poly(polyVerts);

        // triangulate polygon
        math::Triangulate(poly, trias);

        // save result verts
        for (auto t : trias)
        {
            resultTriangles.push_back(t.v(0));
            resultTriangles.push_back(t.v(1));
            resultTriangles.push_back(t.v(2));
        }
    }
}

void DecoderOBJ::clear()
{
    vertexList.clear();
    faces.clear();
    resultTriangles.clear();
}

sptr(Resource) DecoderOBJ::decode(const string &path)
{
    clear();

    TextFile objFile(path);

    string line;
    do
    {
        line = objFile.getLine();

        if (line == "END_OF_FILE")
            break;

        if (line.find("vt") != string::npos)
        { }

        if (line.find("vn") != string::npos)
        { }

        if (line.find("vp") != string::npos)
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

    auto newMesh = make_shared<rend::Mesh>();

    triangulateModel();

    rend::VertexBuffer vb;
    vb.setType(rend::VertexBuffer::TRIANGLELIST);
    vb.appendVertices(resultTriangles);

    auto material = make_shared<rend::Material>();

    material->plainColor = rend::Color3(255, 255, 255);
    material->ambientColor = rend::Color3(255, 255, 255);
    material->diffuseColor = rend::Color3(255, 255, 255);

    material->shadeMode = rend::Material::SM_FLAT;
    material->sideType = rend::Material::ONE_SIDE;

    vb.setMaterial(material);

    newMesh->appendSubmesh(vb);

    auto newObject = make_shared<rend::SceneObject>(newMesh);

    boost::filesystem::path p(path);
    newObject->setName(p.filename().string());

    syslog << "Decoded obj-model \"" << newObject->getName()
            << "\". Number of vertices:" << newMesh->numVertices()
            << ". Number of faces:" << faces.size() << logmess;

    return newObject;
}

string DecoderOBJ::extension() const
{
    return "obj";
}

}
