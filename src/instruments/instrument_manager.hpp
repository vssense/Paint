#ifndef _TOOL_MANAGER_HPP_INCLUDED
#define _TOOL_MANAGER_HPP_INCLUDED

#include "tool.hpp"
#include <vector>

template <class Instrument>
class Manager
{
private:
    Manager();
    ~Manager();

public:
    static Manager* GetInstance();
    static void Destruct();

    void Add(Instrument* tool);
    void SetActive(Instrument* tool);
    Instrument* GetActive() const;

private:
    Instrument* active_;
    
    std::vector<Instrument*> instruments_;
    static Manager* instance_;
};

template <class Instrument>
Manager<Instrument>* Manager<Instrument>::instance_ = nullptr;

template <class Instrument>
Manager<Instrument>::Manager() :
    active_(nullptr) {}

template <class Instrument>
Manager<Instrument>* Manager<Instrument>::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new Manager;
        assert(instance_);
    }

    return instance_;
}

template <class Instrument>
void Manager<Instrument>::Destruct()
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

template <class Instrument>
void Manager<Instrument>::Add(Instrument* instrument)
{
    assert(instrument);

    instruments_.push_back(instrument);
    active_ = instrument;
}

template <class Instrument>
void Manager<Instrument>::SetActive(Instrument* instrument)
{
    assert(instrument);

    active_ = instrument;
}

template <class Instrument>
Instrument* Manager<Instrument>::GetActive() const
{
    return active_;
}

template <class Instrument>
Manager<Instrument>::~Manager()
{
    active_ = nullptr;

    for (Instrument* instrument : instruments_)
    {
        delete instrument;
    }
}

#endif /* _TOOL_MANAGER_HPP_INCLUDED */
