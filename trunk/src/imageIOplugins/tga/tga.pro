TEMPLATE = lib
TARGET  = qtga

CONFIG += plugin

SOURCES += main.cpp
SOURCES += qtgahandler.cpp
HEADERS += qtgahandler.h


target.path += $$[QT_INSTALL_PLUGINS]/imageformats
INSTALLS += target
