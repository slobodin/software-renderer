/*
 * decoderasc.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef DECODERASC_H
#define DECODERASC_H

#include "comm_pch.h"

#include "resourcedecoder.h"
#include "vertex.h"

namespace base
{

class DecoderASC : public ResourceDecoder
{
    void parseVertices(string &line);
    void parseHeader(string &line);
    void parseFaceLine(string &line);
    void parseMaterialLine(string &line);
    void parseHeaderVerts(string &line);

    void clear();

    string objName;

    vector<math::vertex> vertexList;

    struct AscPolyData
    {
        int indices[3];
        rend::Color4 color;
        string colorString;

        // we need to sort all polygon data and create particular vertex buffers (with same material)
        // all vertex buffers will form the mesh
        bool operator< (const AscPolyData &other) const
        {
            return colorString < other.colorString;
        }
        bool operator== (const AscPolyData &other) const
        {
            return colorString == other.colorString;
        }
    };

    size_t currPolyIndex;

    vector<AscPolyData> faces;

public:
    DecoderASC();
    ~DecoderASC();

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODERASC_H
