#include "framebuffer.h"

#include <tcl/tk.h>
#include <tcl/tcl.h>
#include <third-party/cpptk-1.0.2/base/cpptkbase.h>

namespace rend
{

// this function fills or sets unsigned 32-bit aligned memory
// count is number of quads
static inline void Memset_QUAD(void *dest, const uint32_t data, int count)
{
    __asm__ ("mov %%edi, %0\n\t" ::"d"(dest));
    __asm__ ("mov %%ecx, %0\n\t" ::"d"(count));
    __asm__ ("mov %%eax, %0\n\t" ::"d"(data));
    __asm__ ("rep stosd");
//             "mov %ecx, count\n\t"
//             "mov %eax, data\n\t"
//             "rep stosd");
//    __asm
//    {
//        mov edi, dest   ; edi points to destination memory
//        mov ecx, count  ; number of 32-bit words to move
//        mov eax, data   ; 32-bit data
//        rep stosd       ; move data
//    }
}

FrameBuffer::FrameBuffer(const int witdh, const int height)
    : m_pixels(0),
      m_width(witdh),
      m_height(height),
      m_xOrigin(0),
      m_yOrigin(0)
{
    m_pixels = new Color3[m_width * m_height];
}

FrameBuffer::~FrameBuffer()
{
    if (m_pixels)
        delete [] m_pixels;
}

void FrameBuffer::clear()
{
    memset(m_pixels, 0x00, sizeof(Color3) * m_width * m_height);
}

void FrameBuffer::flush_tk(const string &to)
{
    Tk_PhotoHandle fbphoto;
    Tk_PhotoImageBlock block;
    Tcl_Interp *fbinterp = Tk::globalTclInterpret;

    if ((fbphoto = Tk_FindPhoto(fbinterp, to.c_str())) == NULL)
    {
        *syslog << "Image creation unsuccessful. Can't find" << to.c_str() << logerr;
        return;
    }

    block.pixelPtr = (unsigned char *)m_pixels;
    block.width = m_width;
    block.height = m_height;
    block.pitch = 3 * m_width;
    block.pixelSize = 3;
    block.offset[0] = 0;
    block.offset[1] = 1;
    block.offset[2] = 2;
    block.offset[3] = 0;

    Tk_PhotoPutBlock(fbinterp, fbphoto, &block, 0, 0, m_width, m_height, TK_PHOTO_COMPOSITE_SET);
}

void FrameBuffer::flush_win()
{
}

void FrameBuffer::flush_gl()
{
}

void FrameBuffer::wscanline(const int x1, const int x2, const int y, const Color3 &color)
{
    if (x1 > x2)
        return;

    // FIXME: quad memset
    for (int x = x1; x <= x2; x++)
    {
        wpixel(x, y, color);
    }
}

void FrameBuffer::wpixel(const int x, const int y, const Color3 &color)
{
    if (!(x >= 0 && x < m_width && y >= 0 && y < m_height))
        return;

    Color3 &currPix = m_pixels[m_width * y + x];
    currPix = color;
}

void FrameBuffer::wpixel(const int pos, const Color3 &color)
{
    if (!(pos >= 0 && pos < (m_width * m_height)))
        return;

    m_pixels[pos] = color;
}

}
