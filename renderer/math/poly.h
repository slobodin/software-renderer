/*
 * poly.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef POLY_H
#define POLY_H

#include "vertex.h"
#include "material.h"
#include "m44.h"

namespace math
{

class Triangle
{
    vertex m_verts[3];
    vec3 m_normal;

    sptr(rend::Material) m_material;

public:
    bool clipped;

public:
    Triangle();
    Triangle(const vertex *arr);

    const vertex &v(size_t ind) const { return m_verts[ind]; }
    vertex &v(size_t ind) { return m_verts[ind]; }

    //! Sets 3 vertices from an array.
    void setVertices(const vertex *arr)
    {
        m_verts[0] = arr[0];
        m_verts[1] = arr[1];
        m_verts[2] = arr[2];
    }

    //! Applies given matrix to 3 vertices of the triangle.
    void applyTransformation(const math::M44 &transform, bool translateNormals = false);

    //! Returns copy of the triangle points.
    std::vector<vec3> points() const;
    //! Returns copy of the triangle normals.
    std::vector<vec3> normals() const;
    //! Returns copy of the triangle texture coordinates.
    std::vector<vec2> uvs() const;

    sptr(rend::Material) getMaterial() const { return m_material; }
    void setMaterial(sptr(rend::Material) material) { m_material = material; }

    void computeNormal();
    vec3 normal() const { return m_normal; }

    float square() const;

    friend bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMax(const math::Triangle &t1, const math::Triangle &t2);
};

bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
bool ZCompareMax(const math::Triangle &t1, const math::Triangle &t2);

//! Arbitrary poly.
/*!
  * Only for polygons triangulation support.
  */
class Polygon
{
    std::vector<vertex> m_vertices;

public:
    Polygon();
    Polygon(const std::vector<vertex> &vertices);

    //! Set poly with new data.
    void set(const std::vector<vertex> &vertices);

    const std::vector<vertex> &vertices() const { return m_vertices; }

    //! Splits this poly into two polys.
    void split(Polygon &poly1, Polygon &poly2) const;

    //! Performs triangulation of poly into resultList.
    friend void Triangulate(const Polygon &poly, std::vector<Triangle> &resultList);
};

//! Performs triangulation of poly into resultList.
void Triangulate(const Polygon &poly, std::vector<Triangle> &resultList);
//! Performs triangulation of poly defined by index and vertex list.
void Triangulate(const std::vector<math::vertex> &vertices, const std::vector<int> &indices,
                 std::vector<int> &resultIndexList);

}

#endif // POLY_H
