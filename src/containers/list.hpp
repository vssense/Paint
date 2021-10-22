#ifndef _LIST_HPP_INCLUDED
#define _LIST_HPP_INCLUDED

template <typename T>
class List
{
public:
    List() : head_(nullptr), tail_(nullptr)
    {
        size_ = 0;
    }

    ~List()
    {
        for (auto it = Begin(); it != End();)
        {
            auto old_it = it;
            ++it;
            Erase(old_it);
        }

        size_ = 0;
    }

private:
    struct Node
    {
        Node(const T& key, Node* new_next = nullptr) : key(key), next(new_next)
        {
            prev = nullptr;
        }
        ~Node() {}

        T key;
        Node* prev;
        Node* next;
    };

public:
    class Iterator
    {
    public:
        Iterator(Node* node) : node_(node) {}
        ~Iterator() {}
        
        Iterator& operator ++ ()
        {
            if (node_ == nullptr)
            {
                return *this;
            }

            node_ = node_->next;
            return *this;
        }

        T& operator * ()
        {
            return node_->key;
        }
        
        friend bool operator != (const Iterator& lhs, const Iterator& rhs)
        {
            if (lhs.node_ != nullptr && rhs.node_ != nullptr)
            {
                return lhs.node_ != rhs.node_;
            }

            if (lhs.node_ == nullptr && rhs.node_ == nullptr)
            {
                return false;
            }

            return true;
        }

        friend void List<T>::InsertAfter(const Iterator& it, const T& key); 
        friend void List<T>::Erase(Iterator& it); 
    
    private:
        Node* node_;
    };

    void PushBack(const T& key);
    void InsertAfter(const Iterator& it, const T& key);
    void Erase(Iterator& it);
    size_t Size() { return size_; }

    Iterator Begin()
    {
        return Iterator(head_);
    }

    Iterator End()
    {
        return Iterator(nullptr);
    }

private:
    Node* head_;
    Node* tail_;
    size_t size_;
};

template <typename T>
void List<T>::PushBack(const T& key)
{
    ++size_;

    if (tail_ == nullptr)
    {
        head_ = tail_ = new Node(key);
        return;
    }

    tail_->next = new Node(key);
    tail_->next->prev = tail_;
    tail_ = tail_->next;
}

template <typename T>
void List<T>::InsertAfter(const Iterator& it, const T& key)
{
    assert(it.node_);
    ++size_;

    it.node_->next = new Node(key, it.node_->next);
    it.node_->next->prev = it.node_;
    
    if (it.node_->next->next != nullptr)
    {
        it.node_->next->next->prev = it.node_->next;
    }

    if (it.node_ == tail_)
    {
        tail_ = it.node_->next;
    }
}

template <typename T>
void List<T>::Erase(Iterator& it)
{
    assert(it.node_);
    --size_;

    Node* node = it.node_;
    if (node == head_)
    {
        head_ = node->next;
        if (head_ != nullptr)
        {
            head_->prev = nullptr;
        }
        else
        {
            tail_ = nullptr;
        }
    }
    else if (node == tail_)
    {
        node->prev->next = nullptr;
        tail_ = node->prev;
    }
    else
    {
        assert(node->prev);
        assert(node->next);
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    delete node;
    it.node_ = nullptr;
}


#endif /* _LIST_HPP_INCLUDED */