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
            else
                face.normalIndices.push_back(common::fromString<int>(*tokIter));
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

void DecoderOBJ::appendNormal(string &line)
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
        vector<math::vertex> polyVerts;
        vector<int> polyInds;

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
        vector<int> polyIndsTriangulated;
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
            appendNormal(line);

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
    vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
    vb.appendVertices(vertexList, resultTrianglesIndices, !normalsList.empty());

    auto material = make_shared<rend::Material>();

    material->plainColor = rend::Color4(255, 255, 255);
    material->ambientColor = rend::Color4(255, 255, 255);
    material->diffuseColor = rend::Color4(255, 255, 255);

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
