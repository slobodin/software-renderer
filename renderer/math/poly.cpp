/*
 * poly.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "poly.h"

namespace math
{

Triangle::Triangle()
    : clipped(false)
{
}

Triangle::Triangle(const vertex *arr)
    : clipped(false)
{
    if (!arr)
    {
        syslog << "Trying to initialize triangle with an empty array" << logdebug;
        return;
    }

    m_verts[0] = arr[0];
    m_verts[1] = arr[1];
    m_verts[2] = arr[2];

    computeNormal();
}

void Triangle::applyTransformation(const M44 &transform, bool translateNormals)
{
    // translate point
    m_verts[0].p = m_verts[0].p * transform;
    m_verts[1].p = m_verts[1].p * transform;
    m_verts[2].p = m_verts[2].p * transform;

    if (translateNormals)
    {
        // FIXME: !!
        // translate normal
        m_verts[0].n = m_verts[0].n * transform;
        m_verts[1].n = m_verts[1].n * transform;
        m_verts[2].n = m_verts[2].n * transform;

        // noo??
        m_verts[0].n.normalize();
        m_verts[1].n.normalize();
        m_verts[2].n.normalize();
    }
}

std::vector<vec3> Triangle::points() const
{
    std::vector<vec3> res(3);
    res[0] = m_verts[0].p;
    res[1] = m_verts[1].p;
    res[2] = m_verts[2].p;

    return res;
}

std::vector<vec3> Triangle::normals() const
{
    std::vector<vec3> res(3);
    res[0] = m_verts[0].n;
    res[1] = m_verts[1].n;
    res[2] = m_verts[2].n;

    return res;
}

std::vector<vec2> Triangle::uvs() const
{
    std::vector<vec2> res(3);
    res[0] = m_verts[0].t;
    res[1] = m_verts[1].t;
    res[2] = m_verts[2].t;

    return res;
}

void Triangle::computeNormal()
{
    static vec3 p1, p2;

    p1.set((m_verts[1].p - m_verts[0].p).normalize());
    p2.set((m_verts[2].p - m_verts[0].p).normalize());

    m_normal = p1.crossProduct(p2);
    m_normal.normalize();
}

float Triangle::square() const
{
    static vec3 p1, p2;

    p1.set((m_verts[1].p - m_verts[0].p).normalize());
    p2.set((m_verts[2].p - m_verts[0].p).normalize());

    vec3 n = p1.crossProduct(p2);

    return 0.5f * n.length();
}

bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2)
{
    float avgz = 0.33333f * (t1.m_verts[0].p.z + t1.m_verts[1].p.z + t1.m_verts[2].p.z);
    float avgotherz = 0.33333f * (t2.m_verts[0].p.z + t2.m_verts[1].p.z + t2.m_verts[2].p.z);

    if (avgz < avgotherz)
        return true;

    return false;
}

bool ZCompareMin(const Triangle &t1, const Triangle &t2)
{
    std::vector<vec3> points = t1.points();
    float minz1 = (*std::min_element(points.begin(), points.end(), comparez)).z;

    points = t2.points();
    float minz2 = (*std::min_element(points.begin(), points.end(), comparez)).z;

    if (minz1 < minz2)
        return true;

    return false;
}

bool ZCompareMax(const Triangle &t1, const Triangle &t2)
{
    std::vector<vec3> points = t1.points();
    float minz1 = (*std::max_element(points.begin(), points.end(), comparez)).z;

    points = t2.points();
    float minz2 = (*std::max_element(points.begin(), points.end(), comparez)).z;

    if (minz1 < minz2)
        return true;

    return false;
}

Polygon::Polygon()
{
}

Polygon::Polygon(const std::vector<vertex> &vertices)
{
    if (vertices.size() < 3)
        throw std::runtime_error("Invalid poly.");

    copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
}

void Polygon::set(const std::vector<vertex> &vertices)
{
    m_vertices.clear();
    copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
}

void Polygon::split(Polygon &poly1, Polygon &poly2) const
{
    poly1.set(std::vector<vertex>(m_vertices.begin(), m_vertices.begin() + 3));
    poly2.set(std::vector<vertex>(m_vertices.begin() + 2, m_vertices.end()));
    poly2.m_vertices.push_back(m_vertices[0]);
}

void Triangulate(const Polygon &poly, std::vector<Triangle> &resultList)
{
    if (poly.m_vertices.size() == 3)
    {
        resultList.push_back(Triangle(&poly.m_vertices[0]));
        return;
    }
    else
    {
        Polygon p1, p2;

        poly.split(p1, p2);
        Triangulate(p1, resultList);
        Triangulate(p2, resultList);
    }
}

void Triangulate(const std::vector<math::vertex> &vertices, const std::vector<int> &indices, std::vector<int> &resultIndexList)
{
    if (vertices.size() == 3)
    {
        assert(indices.size() == 3);
        resultIndexList.insert(resultIndexList.end(), indices.begin(), indices.end());
    }
    else
    {
        // split
        std::vector<vertex> newverts1(vertices.begin(), vertices.begin() + 3);
        std::vector<vertex> newverts2(vertices.begin() + 2, vertices.end());
        newverts2.push_back(vertices[0]);

        std::vector<int> newinds1(indices.begin(), indices.begin() + 3);
        std::vector<int> newinds2(indices.begin() + 2, indices.end());
        newinds2.push_back(indices[0]);

        // triangulate
        Triangulate(newverts1, newinds1, resultIndexList);
        Triangulate(newverts2, newinds2, resultIndexList);
    }
}

}
