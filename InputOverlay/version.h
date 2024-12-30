// version.h
#pragma once
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_BUILD 2

#define stringify(x) #x
#define plugin_version stringify(VERSION_MAJOR.VERSION_MINOR.VERSION_PATCH.VERSION_BUILD)
