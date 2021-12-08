#ifndef _BRUSH_HPP_INCLUDED
#define _BRUSH_HPP_INCLUDED

#include "../../plugins/plugin.hpp"
#include "../paint_gui_components/preferences_panel.hpp"
#include "../api/api_widgets.hpp"
#include <cassert>

typedef plugin::ITexture ITexture;
typedef plugin::IPreferencesPanel IPreferencesPanel;
typedef plugin::Buffer Buffer;

class Brush : public plugin::ITool
{
public:
    Brush();
    virtual ~Brush();
    virtual void ActionBegin(ITexture* canvas, int x, int y) override;
    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy) override;
    virtual void ActionEnd  (ITexture* canvas, int x, int y) override;

    virtual const char* GetIconFileName() const override;
    virtual IPreferencesPanel* GetPreferencesPanel() const override;

private:
    Color color_;

    APIPreferencesPanel* panel_;
};

#endif /* _BRUSH_HPP_INCLUDED */
