TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    renderer \

win32 {
SUBDIRS += client-win
}

unix {
SUBDIRS += client-unix
}

client-win.depends = renderer
client-unix.depends = renderer
