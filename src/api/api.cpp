#include "api.hpp"

API::API(IWidgetFactory* widget_factory, ITextureFactory* texture_factory)
    : widget_factory_(widget_factory),
      texture_factory_(texture_factory) {}

IWidgetFactory* API::GetWidgetFactory()
{
    return widget_factory_;
}

ITextureFactory* API::GetTextureFactory()
{
    return texture_factory_;
}
