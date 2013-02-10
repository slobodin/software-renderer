/*
 * osfile.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef OSFILE_H
#define OSFILE_H

namespace base
{

// If something wrong...
DECLARE_EXCEPTION(FileException)

//! File abstraction.
/*!
  *
  */
class OsFile
{
protected:
    enum FileType
    {
        FT_TEXT,
        FT_BINARY
    };

    //! File itself.
    std::ifstream m_file;

public:
    //! Base ctor.
    OsFile(const std::string &path, FileType ft);
    //! Dtor.
    virtual ~OsFile();
};

//! Text file.
/*!
  *
  */
class TextFile : public OsFile
{
    std::stringstream m_fileData;

public:
    //! Ctor with path.
    TextFile(const std::string &path);

    //! Returns next line from the file.
    /*!
      * If file ends, returns "END_OF_FILE"-std::string.
      * \param delim Lines deliminator.
      */
    std::string getLine(const char delim = '\n');

    void resetPtr();
};

//! Binary file.
/**
  *
  */
class BinaryFile : public OsFile
{
    //! Binary data.
    std::vector<uint8_t> m_fileData;

public:
    //! Ctor with path.
    BinaryFile(const std::string &path);

    //! Returns pointer to the file data with given offset.
    void *getBytes(size_t offset);

    //! Gets elements with T type from the file.
    /*!
      * \param offset Offset from the file beginning.
      * \param dest Array for collecting file data.
      * \param numElements How many elements we're getting.
      */
    template <typename T>
    void copy(size_t offset, T *dest, size_t numElemets);
};

template <typename T>
void BinaryFile::copy(size_t offset, T *dest, size_t numElemets)
{
    size_t i = offset / sizeof(uint8_t);
    memcpy(dest, &m_fileData[i], numElemets * sizeof(T));
}

}

#endif // OSFILE_H
