/*
 * decoderbspq3.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "decoderbspq3.h"

#include "osfile.h"
#include "vec3.h"
#include "material.h"
#include "mesh.h"

namespace base
{

DecoderBSPQ3::DecoderBSPQ3()
{
}

DecoderBSPQ3::~DecoderBSPQ3()
{
}

sptr(Resource) DecoderBSPQ3::decode(const OsPath &path)
{
    BinaryFile file(path);

    header = reinterpret_cast<BSPHeader *>(file.getBytes(0));
    if (!(header->ID == (*(int *)"IBSP") && header->version == 0x2E))   // 0x50534249
    {
        *syslog << "Bad BSP header" << logerr;

        return sptr(Resource)();
    }

    file.copy(sizeof(BSPHeader), lumps, MAX_LUMP);

    // load vertices
    numVertices = lumps[LUMP_VERTICES].length / sizeof(BSPVertex);
    vertices = new BSPVertex[numVertices];
    file.copy(lumps[LUMP_VERTICES].offset, vertices, numVertices);

    // load faces
    numFaces = lumps[LUMP_FACES].length / sizeof(BSPFace);
    faces = new BSPFace[numFaces];
    file.copy(lumps[LUMP_FACES].offset, faces, numFaces);

    // load mesh verts
    numMeshVerts = lumps[LUMP_MESH_VERTS].length / sizeof(int);
    meshVerts = new int[numMeshVerts];
    file.copy(lumps[LUMP_MESH_VERTS].offset, meshVerts, numMeshVerts);

    vector<math::vertex> vertexList;
    math::vertex v;

    for (int i = 0; i < numFaces; i++)
    {
        switch(faces[i].type)
        {
        // polygon
        case 1:
        {
            int numVerts = faces[i].n_meshverts;
            int *index = meshVerts + faces[i].meshvert;

            for (int j = 0; j < numVerts; j++)
            {
                v.p.x = vertices[faces[i].vertex + index[j]].position[0];
                v.p.y = vertices[faces[i].vertex + index[j]].position[2];
                v.p.z = vertices[faces[i].vertex + index[j]].position[1];

                v.n.x = vertices[faces[i].vertex + index[j]].normal[0];
                v.n.y = vertices[faces[i].vertex + index[j]].normal[2];
                v.n.z = vertices[faces[i].vertex + index[j]].normal[1];

                v.t.x = vertices[faces[i].vertex + index[j]].textureCoord[0];
                v.t.y = vertices[faces[i].vertex + index[j]].textureCoord[1];

                vertexList.push_back(v);
            }
        }
            break;

        // patch
        case 2:

            break;

        // mesh
        case 3:

            break;

        // billboard
        case 4:

            break;

        default:
            *syslog << "Bad face type in q3 file" << path.filePath() << logwarn;
            break;
        }
    }

    sptr(rend::Mesh) newMesh(new rend::Mesh(vertexList,
                                            rend::Mesh::MT_MESH_TRIANGLELIST));
    newMesh->setName(path.filePath());

    delete [] vertices;
    delete [] faces;
    delete [] meshVerts;

    *syslog << "Decoded q3-bsp model \"" << newMesh->name() << "\". Number of vertices:" << newMesh->numVertices() << logmess;

    return newMesh;
}

string DecoderBSPQ3::extention() const
{
    return "bsp";
}

}
