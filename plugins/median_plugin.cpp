#include "plugin.hpp"

#include <cassert>

namespace plugin {

class MedianFilter : public IFilter {
public:
    MedianFilter(plugin::IAPI* api)
        : panel_{nullptr} {
        panel_ = api->GetWidgetFactory()->CreateDefaultPreferencesPanel();
    }

    ~MedianFilter() {}

    virtual void Apply(ITexture* canvas) override {
        assert(canvas != nullptr);

        int32_t width  = canvas->GetWidth();
        int32_t height = canvas->GetHieght();

        Buffer old_buffer = canvas->ReadBuffer();
        Buffer buffer     = canvas->ReadBuffer();

        int32_t window_width  = 2; 
        int32_t window_height = 2;

        int32_t edge_x = (window_width  / 2);
        int32_t edge_y = (window_height / 2);

        uint32_t array[window_width * window_height];

        for (int32_t x = edge_x; x < width - edge_x; ++x) {
            for (uint32_t y = edge_y; y < height - edge_y; ++y) {
                for (int32_t fx = 0; fx < window_width; ++fx) {
                    for (int32_t fy = 0; fy < window_height; ++fy) {                      
                      array[fx + fy * window_width] = old_buffer.pixels[x + fx - edge_x + (y + fy - edge_y) * width];
                    }
                }
                for (int32_t fx = 0; fx < window_width * window_height; ++fx) {
                    for (int32_t fy = 0; fy < window_width * window_height; ++fy) {
                        if (array[fx] < array[fy]) {
                            uint32_t temp = array[fx];
                            array[fx] = array[fy];
                            array[fy] = temp;
                        }
                    }
                }
             buffer.pixels[x + y * width] = array[edge_x + edge_y * window_width];
            }
        }

        canvas->LoadBuffer(buffer);

        canvas->ReleaseBuffer(buffer);
        canvas->ReleaseBuffer(old_buffer);
    }

    virtual const char* GetName() const override {
        return "Median";
    }

    virtual IPreferencesPanel* GetPreferencesPanel() const override {
        return panel_;
    }

private:
    IPreferencesPanel* panel_;
};

class Plugin : public IPlugin {
public:
    Plugin(IAPI* api)
        : median_filter_{nullptr} {
        median_filter_ = new MedianFilter(api);
    }

    virtual ~Plugin() override {
        delete median_filter_;
    }

    virtual std::list<IFilter*> GetFilters() const override {
        return std::list<IFilter*>{median_filter_};
    }

    virtual std::list<ITool*> GetTools() const override {
        return std::list<ITool*>{};
    }

private:
    MedianFilter* median_filter_;
};

extern "C" IPlugin* Create(IAPI* api) {
    return new Plugin(api);
}

extern "C" void Destroy(IPlugin* plugin) {
    delete plugin;
}

extern "C" uint32_t Version() {
    return kVersion;
}

} // namespace plugin