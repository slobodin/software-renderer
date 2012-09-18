TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    renderer

win32 {
SUBDIRS += client-win
}

unix {
SUBDIRS += client-unix
SUBDIRS += client-tk
}
