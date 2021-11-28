#ifndef _PLUGIN_MANAGER_HPP_INCLUDED
#define _PLUGIN_MANAGER_HPP_INCLUDED

#include "../../plugins/plugin.hpp"
#include <cassert>
#include <dlfcn.h>
#include <cstdio>
#include <vector>

typedef plugin::IPlugin IPlugin;

class Plugin
{
public:
    explicit Plugin(const char* path, plugin::IAPI* api);
    ~Plugin();
    IPlugin* GetPlugin() const;

private:
    void InitFunctions();

    plugin::CreateFunction create_;
    plugin::DestroyFunction destroy_;
    plugin::VersionFunction version_;

    IPlugin* plugin_;
    void* handle_;
};

class PluginManager
{
private:
    PluginManager();

public:
    static PluginManager* GetInstance();
    ~PluginManager();

    const std::vector<Plugin*>& GetPlugins() const;

private:
    std::vector<Plugin*> loaded_;
    plugin::IAPI* api_;

    static PluginManager* instance_;
};

#endif /* _PLUGIN_MANAGER_HPP_INCLUDED */
