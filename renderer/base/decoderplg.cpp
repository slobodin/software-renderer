#include "decoderplg.h"

#include "osfile.h"
#include "mesh.h"
#include "material.h"

namespace base
{

DecoderPLG::DecoderPLG()
{
}

DecoderPLG::~DecoderPLG()
{
}

SPTR(Resource) DecoderPLG::decode(const OsPath &path)
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

    vector<math::vec3> vertexList(numVertices);
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
        vertexList[vertex] = pt;
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

        rend::Color3 col(polyDescriptor);
        materials.push_back(rend::Material(col, rend::Material::SM_FLAT));
    }

    SPTR(rend::Mesh) newMesh(new rend::Mesh(vertexList,
                                            indices,
                                            materials,
                                            rend::Mesh::MT_MESH_INDEXEDTRIANGLELIST));
    newMesh->setName(resourceName);

    *syslog << "Decoded plg-model \"" << newMesh->name() << "\". Number of vertices:" << newMesh->numVertices() << logmess;
    
    return newMesh;
}

string DecoderPLG::extention() const
{
    return string("plg");
}

}
