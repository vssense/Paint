#ifndef _API_HPP_INCLUDED
#define _API_HPP_INCLUDED

#include "../../plugins/plugin.hpp"
#include "api_texture.hpp"
#include "api_widgets.hpp"

class API : public IAPI
{
public:
    API();
    ~API();

    virtual IWidgetFactory*  GetWidgetFactory () override;
    virtual ITextureFactory* GetTextureFactory() override;

private:
    IWidgetFactory* widget_factory_;
    ITextureFactory* texture_factory_;
};

#endif /* _API_HPP_INCLUDED */