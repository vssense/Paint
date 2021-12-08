#include "plugin_manager.hpp"
#include "../api/api.hpp"

#include <dirent.h>
#include <cstring>

const char* kPluginDir = "plugins/";
const uint32_t kMaxFilenameLen = 256;

PluginManager* PluginManager::instance_ = nullptr;

Plugin::Plugin(const char* path, plugin::IAPI* api)
    : create_(nullptr),
      destroy_(nullptr),
      version_(nullptr),
      plugin_(nullptr)
{
    assert(path);
    assert(api);

    handle_ = dlopen(path, RTLD_NOW);
    if (handle_ == nullptr)
    {
        fprintf(stderr, "Can't load dl from %s\n", path);
        fprintf(stderr, "dlerror: %s\n", dlerror());
        return;
    }

    InitFunctions();

    if (create_ != nullptr)
    {
        plugin_ = create_(api);
    }
}

Plugin::~Plugin()
{
    if (plugin_ != nullptr && destroy_ != nullptr)
    {
        destroy_(plugin_);
    }

    if (handle_ != nullptr)
    {
        dlclose(handle_);
    }
}

IPlugin* Plugin::GetPlugin() const
{
    return plugin_;
}

void Plugin::InitFunctions()
{
    version_ = (plugin::VersionFunction)dlsym(handle_, "Version");
    if (version_ == nullptr)
    {
        fprintf(stderr, "Can't find Version function\n");
        return;
    }

    uint32_t version = version_();
    if (version != plugin::kVersion)
    {
        fprintf(stderr, "Wrong version: expected %u, actual %u\n", plugin::kVersion, version);
        return;
    }

    create_ = (plugin::CreateFunction)dlsym(handle_, "Create");
    if (create_ == nullptr)
    {
        fprintf(stderr, "Can't find Create function\n");
        return;
    }

    destroy_ = (plugin::DestroyFunction)dlsym(handle_, "Destroy");
    if (destroy_ == nullptr)
    {
        fprintf(stderr, "Can't find Destroy function\n");
        return;
    }
}

PluginManager::PluginManager()
    : api_(new API)
{
    DIR* plugins_dir = opendir(kPluginDir);
    if (plugins_dir == nullptr)
    {
        fprintf(stderr, "Can't open plugins directory\n");
        return;
    }

    struct dirent* file = readdir(plugins_dir);

    while (file != NULL)
    {
        char path[kMaxFilenameLen] = "";
        strcat(path, kPluginDir);
        strcat(path, file->d_name);
        
        if (file->d_type == DT_REG)
        {
            if (strstr(path, ".so") != NULL)
            {
                loaded_.push_back(new Plugin(path, api_));
            }
        }

        file = readdir(plugins_dir);
    }

    closedir(plugins_dir);
}

PluginManager* PluginManager::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new PluginManager;
    }

    return instance_;
}

void PluginManager::Destruct()
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

PluginManager::~PluginManager()
{
    if (api_ != nullptr)
    {
        delete api_;
    }

    for (Plugin* plugin : loaded_)
    {
        delete plugin;
    }

    loaded_.clear();
}

const std::vector<Plugin*>& PluginManager::GetPlugins() const
{
    return loaded_;
}
