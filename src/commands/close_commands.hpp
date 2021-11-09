#ifndef _CLOSE_COMMANDS_HPP_INCLUDED
#define _CLOSE_COMMANDS_HPP_INCLUDED

#include "../gui_system/gui_component_commands.hpp"
#include "../graphics/texture.hpp"

class MainCloseOnMouseEvent : public IOnMouseEventCommand
{
public:
    MainCloseOnMouseEvent(bool* is_running, const char* path = nullptr) :
                          is_running_(is_running), swap_texture_(nullptr)
    {
        assert(is_running_);
        if (path != nullptr)
        {
            swap_texture_ = new Texture(path);
            assert(swap_texture_);
        }
    }

    ~MainCloseOnMouseEvent()
    {
        delete swap_texture_;
    }

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonRelease:
            {
                *is_running_ = false;
                break;
            }
            case kMouseButtonPress:
            case kMouseButtonOldRelease:
            {
                if (swap_texture_ != nullptr)
                {
                    Texture* tmp = component_->GetTexture();
                    component_->SetTexture(swap_texture_);
                    swap_texture_ = tmp;
                }
                
                break;                
            }
            default:
            {
                break;
            }
        }

        return true;
    }

private:
    bool* is_running_;
    Texture* swap_texture_;
};

class CloseCanvasOnMouseEvent : public IOnMouseEventCommand
{
public:
    CloseCanvasOnMouseEvent(GUIComponent* canvas, const char* path = nullptr) :
        canvas_(canvas) 
    {
        assert(canvas_);

        if (path != nullptr)
        {
            swap_texture_ = new Texture(path);
            assert(swap_texture_);
        }
    }
    
    ~CloseCanvasOnMouseEvent()
    {
        if (swap_texture_ != nullptr)
        {
            delete swap_texture_; 
        }
    }

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonRelease:
            {
                canvas_->Delete();
                break;
            }
            case kMouseButtonPress:
            case kMouseButtonOldRelease:
            {
                if (swap_texture_ != nullptr)
                {
                    Texture* tmp = component_->GetTexture();
                    component_->SetTexture(swap_texture_);
                    swap_texture_ = tmp;
                }
                
                break;                
            }
            default:
            {
                break;
            }
        }

        return true;
    }

private:
    GUIComponent* canvas_;
    Texture* swap_texture_;
};

#endif /* _CLOSE_COMMANDS_HPP_INCLUDED */
