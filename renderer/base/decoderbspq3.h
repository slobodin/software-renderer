#ifndef DECODERBSPQ3_H
#define DECODERBSPQ3_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class DecoderBSPQ3 : public ResourceDecoder
{
    enum Lumps
    {
        LUMP_ENTITIES       = 0,
        LUMP_SHADERS        = 1,
        LUMP_PLANES         = 2,
        LUMP_NODES          = 3,
        LUMP_LEAFS          = 4,
        LUMP_LEAF_FACES     = 5,
        LUMP_LEAF_BRUSHES   = 6,
        LUMP_MODELS         = 7,
        LUMP_BRUSHES        = 8,
        LUMP_BRUSH_SIDES    = 9,
        LUMP_VERTICES       = 10,
        LUMP_MESH_VERTS     = 11,
        LUMP_FOGS           = 12,
        LUMP_FACES          = 13,
        LUMP_LIGHTMAPS      = 14,
        LUMP_LIGHTGRID      = 15,
        LUMP_VIS_DATA       = 16,
        LUMP_LIGHT_ARRAY    = 17,
        MAX_LUMP            = 18
    };

    struct __attribute__ ((__packed__)) BSPHeader
    {
        int ID;         // == IBSP
        int version;    // == 0x2E  - 46v
    };

    struct __attribute__ ((__packed__)) BSPLump
    {
        int offset;
        int length;
    };

    struct __attribute__ ((__packed__)) BSPVertex
    {
        float            position[3];       // x, y, z
        float            textureCoord[2];   // u, v
        float            lightmapCoord[2];  // u, v-lightmap
        float            normal[3];         // x, y, z-normal
        unsigned char    color[4];          // RGBA
    };

    struct __attribute__ ((__packed__)) BSPFace
    {
        int     texture;
        int     effect;
        int     type;           // 1 - polygon, 2 - patch, 3 - mesh, 4 - billboard
        int     vertex;         // index of first vertex
        int     n_vertexes;     // number of vertices
        int     meshvert;       // index of first meshvert
        int     n_meshverts;
        int     lm_index;       // lightmap index
        int     lm_start[2];
        int     lm_size[2];
        float   lm_origin[3];
        float   lm_vecs[2][3];
        float   normal[3];
        int     size[2];
    };

    struct __attribute__ ((__packed__)) BSPTexture
    {
        char        strName[64];
        unsigned    flags;
        unsigned    contents;
    };

    struct __attribute__ ((__packed__)) BSPLightmap
    {
        unsigned char imageBits[128][128][3];
    };

    struct __attribute__ ((__packed__)) BSPNode
    {
        int plane;
        int front;
        int back;
        int mins[3];
        int maxs[3];
    };

    struct __attribute__ ((__packed__)) BSPLeaf
    {
        int cluster;
        int area;
        int mins[3];
        int maxs[3];
        int leafface;
        int numOfLeafFaces;
        int leafBrush;
        int numOfLeafBrushes;
    };

    struct __attribute__ ((__packed__)) BSPPlane
    {
        float vNormal[3];
        float d;
    };

    struct __attribute__ ((__packed__)) BSPVisData
    {
        int numOfClusters;
        int bytesPerCluster;
        char *pBitsets;
    };

    struct __attribute__ ((__packed__)) BSPBrush
    {
        int brushSide;
        int numOfBrushSides;
        int textureID;
    };

    struct __attribute__ ((__packed__)) BSPBrushSide
    {
        int plane;
        int textureID;
    };

    struct __attribute__ ((__packed__)) BSPModel
    {
        float min[3];
        float max[3];
        int faceIndex;
        int numOfFaces;
        int brushIndex;
        int numOfBrushes;
    };

    struct __attribute__ ((__packed__)) BSPFog
    {
        char shader[64];
        int brushIndex;
        int visibleSide;
    };

    struct __attribute__ ((__packed__)) BSPLights
    {
        unsigned char ambient[3];
        unsigned char directional[3];
        unsigned char direction[2];
    };

    BSPHeader *header;
    BSPLump lumps[MAX_LUMP];

    BSPVertex *vertices;
    int numVertices;

    BSPTexture *textures;
    int numTextures;

    BSPLightmap *lightmaps;
    int numLightmaps;

    BSPFace *faces;
    int numFaces;

    int *meshVerts;
    int numMeshVerts;

public:
    DecoderBSPQ3();
    ~DecoderBSPQ3();

    SPTR(Resource) decode(const OsPath &path);
    string extention() const;
};

}

#endif // DECODERBSPQ3_H
