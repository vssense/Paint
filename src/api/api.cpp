#include "api.hpp"

API::API()
    : widget_factory_(new APIWidgetFactory),
      texture_factory_(new APITextureFactory) {}

API::~API()
{
    delete widget_factory_;
    delete texture_factory_;
}

IWidgetFactory* API::GetWidgetFactory()
{
    return widget_factory_;
}

ITextureFactory* API::GetTextureFactory()
{
    return texture_factory_;
}


