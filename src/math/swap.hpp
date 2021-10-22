#ifndef _SWAP_HPP_INCLUDED
#define _SWAP_HPP_INCLUDED

template<typename T>
void Swap(T& lhs, T& rhs)
{
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

template<typename T>
T Max(const T& lhs, const T& rhs)
{
    if (lhs > rhs)
    {
        return lhs;
    }

    return rhs;
}

template<typename T>
T Min(const T& lhs, const T& rhs)
{
    if (lhs < rhs)
    {
        return lhs;
    }

    return rhs;
}

#endif /* _SWAP_HPP_INCLUDED */