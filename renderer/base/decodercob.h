/*
 * decodercob.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODERCOB_H
#define DECODERCOB_H

#include "comm_pch.h"

#include "resourcedecoder.h"
#include "vertex.h"
#include "color.h"

namespace base
{

DECLARE_EXCEPTION(COBFileFormatExcetion)

class DecoderCOB : public ResourceDecoder
{
    string m_name;
    int currVertex;

    // vertices
    vector<math::vertex> vertexList;

    struct FaceInfo
    {
        int indices[3];
        int materialIndex;
        int uvIndices[3];

        FaceInfo() : materialIndex(-1) { memset(indices, 0, 3 * sizeof(int)); memset(uvIndices, 0, 3 * sizeof(int)); }

        // we need to sort all polygon data and create particular vertex buffers (with same material)
        // all vertex buffers will form the mesh
        bool operator< (const FaceInfo &other) const
        {
            return materialIndex < other.materialIndex;
        }
        bool operator== (const FaceInfo &other) const
        {
            return materialIndex == other.materialIndex;
        }
    };

    // polys
    vector<FaceInfo> faces;
    int currFace;

    struct MaterialInfo
    {
        int matIndex;
        rend::Color3 color;
        // TODO:
        // shading mode

        MaterialInfo(int ind = -1) : matIndex(ind) { }

        bool operator== (const MaterialInfo &other) const
        {
            return matIndex == other.matIndex;
        }
    };

    // materials
    vector<MaterialInfo> materials;
    int currMaterial;

    // texture coords
    vector<math::vec2> uv;

    void parseHeader(string &line);
    void parseTransform(string &line);
    void parseVertices(string &line);
    void parseUV(string &line);
    void parseFaces(string &line);
    void parseMaterials(string &line);

    void clear();

public:
    DecoderCOB() { }
    ~DecoderCOB() { }

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODERCOB_H
