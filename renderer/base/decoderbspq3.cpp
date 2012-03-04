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

SPTR(Resource) DecoderBSPQ3::decode(const OsPath &path)
{
    BinaryFile file(path);

    header = reinterpret_cast<BSPHeader *>(file.getBytes(0));
    if (!(header->ID == (*(int *)"IBSP") && header->version == 0x2E))   // 0x50534249
    {
        *syslog << "Bad BSP header" << logerr;

        return SPTR(Resource)();
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

    vector<math::vec3> vertexList;
    math::vec3 v;

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
                v.x = vertices[faces[i].vertex + index[j]].position[0];
                v.y = vertices[faces[i].vertex + index[j]].position[2];
                v.z = vertices[faces[i].vertex + index[j]].position[1];

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

    SPTR(rend::Mesh) newMesh(new rend::Mesh(vertexList,
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
    return string("bsp");
}

}
