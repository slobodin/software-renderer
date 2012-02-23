#include "rasterizer.h"

#include "vec2.h"

namespace rend
{

void Rasterizer::drawBottomTriangle(int x1, int y1,
                                    int x2, int y2,
                                    int x3, int y3,
                                    const Color3 &color)
{
    if (x3 < x2)
        std::swap(x2, x3);

    double height = y3 - y1;
    double dxLeft = (x2 - x1) / height;
    double dxRight = (x3 - x1) / height;
    double xs = x1;
    double xe = x1;

    int iy1 = 0, iy3 = 0;

    if (y1 < m_fb.m_yOrigin)
    {
        xs = xs + dxLeft * (-y1 + m_fb.m_yOrigin);
        xe = xe + dxRight * (-y1 + m_fb.m_yOrigin);

        y1 = m_fb.m_yOrigin;
        iy1 = m_fb.m_yOrigin;
    }
    else
    {
        iy1 = ceil(y1);

        xs = xs + dxLeft * (iy1 - y1);
        xe = xe + dxRight * (iy1 - y1);
    }
    if (y3 > m_fb.m_height)
    {
        y3 = m_fb.m_height;
        iy3 = y3 - 1;
    }
    else
    {
        iy3 = ceil(y3) - 1;
    }

    if (x1 >= m_fb.m_xOrigin && x1 <= m_fb.m_width &&
        x2 >= m_fb.m_xOrigin && x2 <= m_fb.m_width &&
        x3 >= m_fb.m_xOrigin && x3 <= m_fb.m_width)
    {
        for (int y = y1; y < y3; y++)
        {
            m_fb.scanline(xs, xe, y, color);

            xs += dxLeft;
            xe += dxRight;
        }
    }
    else
    {
        for (int y = y1; y < y3; y++)
        {
            double left = xs, right = xe;

            xs += dxLeft;
            xe += dxRight;

            if (left < m_fb.m_xOrigin)
            {
                left = m_fb.m_xOrigin;

                if (right < m_fb.m_xOrigin)
                    continue;
            }

            if (right > m_fb.m_width)
            {
                right = m_fb.m_width;

                if (left > m_fb.m_width)
                    continue;
            }

            m_fb.scanline(left, right, y, color);
        }
    }
}

void Rasterizer::drawTopTriangle(int x1, int y1,
                                 int x2, int y2,
                                 int x3, int y3,
                                 const Color3 &color)
{
    if (x2 < x1)
    {
        std::swap(x1, x2);
    }

    double height = y3 - y1;

    double dx_left  = (x3 - x1) / height;
    double dx_right = (x3 - x2) / height;
    double xs = x1;
    double xe = x2;

    int iy1 = 0, iy3 = 0;

    if (y1 < m_fb.m_yOrigin)
    {
        xs = xs + dx_left * (-y1 + m_fb.m_yOrigin);
        xe = xe + dx_right * (-y1 + m_fb.m_yOrigin);

        y1 = m_fb.m_yOrigin;

        iy1 = y1;
    }
    else
    {
        iy1 = ceil(y1);

        xs = xs + dx_left * (iy1 - y1);
        xe = xe + dx_right * (iy1 - y1);
    }

    if (y3 > m_fb.m_height)
    {
        y3 = m_fb.m_height;

        iy3 = y3 - 1;
    }
    else
    {
        iy3 = ceil(y3) - 1;
    }

    if (x1 >= m_fb.m_xOrigin && x1 <= m_fb.m_width &&
        x2 >= m_fb.m_xOrigin && x2 <= m_fb.m_width &&
        x3 >= m_fb.m_xOrigin && x3 <= m_fb.m_width)
    {
        for (int y = iy1; y < iy3; y++)
        {

            m_fb.scanline(xs, xe, y, color);

            xs += dx_left;
            xe += dx_right;
        }

    }
    else
    {
        for (int y = iy1; y < iy3; y++)
        {
            double left = xs;
            double right = xe;

            xs += dx_left;
            xe += dx_right;

            if (left < m_fb.m_xOrigin)
            {
                left = m_fb.m_xOrigin;

                if (right < m_fb.m_xOrigin)
                    continue;
            }

            if (right > m_fb.m_width)
            {
                right = m_fb.m_width;

                if (left > m_fb.m_width)
                   continue;
            }

            m_fb.scanline(left, right, y, color);
        }
    }
}

void Rasterizer::drawTriangle(const math::vec3 &p1,
                              const math::vec3 &p2,
                              const math::vec3 &p3,
                              const Color3 &color)
{
    int x1 = p1.x, x2 = p2.x, x3 = p3.x;
    int y1 = p1.y, y2 = p2.y, y3 = p3.y;

    if ((x1 == x2 && x2 == x3) || (y1 == y2 && y2 == y3))
        return;

    // sort vertices
    if (y2 < y1)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    if (y3 < y1)
    {
        std::swap(x1, x3);
        std::swap(y1, y3);
    }

    if (y3 < y2)
    {
        std::swap(x2, x3);
        std::swap(y2, y3);
    }

    if (y3 < m_fb.m_yOrigin || y1 > m_fb.m_height
            || (x1 < m_fb.m_xOrigin && x2 < m_fb.m_xOrigin && x3 < m_fb.m_xOrigin)
            || (x1 > m_fb.m_width && x2 > m_fb.m_width && x3 > m_fb.m_width))
        return;

    if (y1 == y2)
    {
        drawTopTriangle(x1, y1, x2, y2, x3, y3, color);
    }
    else if (y2 == y3)
    {
        drawBottomTriangle(x1, y1, x2, y2, x3, y3, color);
    }
    else
    {
        double newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);

        drawBottomTriangle(x1, y1, newX, y2, x2, y2, color);
        drawTopTriangle(x2, y2, newX, y2, x3, y3, color);
    }
}

Rasterizer::Rasterizer(const int width, const int height)
    : m_fb(width, height)
{
}

void Rasterizer::draw(const SPTR(Mesh) mesh, const SPTR(Camera) cam)
{
//    const vector<math::vec3> &vertices = mesh->vertices();
//    list<math::vec3> vertList;

//    std::copy(vertices.begin(), vertices.end(), std::back_inserter(vertList));
//    cam->apply(vertList);

    vector<math::vec3> vertList;
    std::copy(mesh->vertices().begin(), mesh->vertices().end(), std::back_inserter(vertList));
    cam->apply(vertList);

    math::vec3 p1, p2, p3;
    const vector<int> &indices = mesh->indices();
    switch(mesh->type())
    {
    case Mesh::MT_MESH_INDEXEDTRIANGLELIST:
        for(size_t ind = 0; ind < indices.size(); ind += 3)
        {
            p1 = vertList[indices[ind]];
            p2 = vertList[indices[ind + 1]];
            p3 = vertList[indices[ind + 2]];

            drawTriangle(p1, p2, p3, Color3(255, 0, 0));
        }

        break;

    case Mesh::MT_MESH_TRIANGLELIST:

        break;

    case Mesh::MT_MESH_UNDEFINED:
    default:
        *syslog << "Can't draw this mesh" << logwarn;
        break;
    }
}

void Rasterizer::beginFrame()
{
    m_fb.clear();
}

void Rasterizer::endFrame()
{
    m_fb.flush_tk();
}

}
