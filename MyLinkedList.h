#include <iostream>
template <class T>
class Node
{
    public:
        T value;
        Node<T> * next;
        Node(const T & value, Node<T> * next)
        {
            this->value = value;
            this->next = next;
        }
};

template <class T>
class MyLinkedList 
{
    public:
    
        MyLinkedList() 
        {
            head = tail = nullptr;
        }

        ~MyLinkedList() 
        {
            while (head->next != nullptr) 
            {
                Node<T> * temp = head;
                head = head->next;
                delete temp;
            }
            delete head;
            cout << "MY LINK LIST DECONSTRUCTED\n";
        }

        void push_back(const T & value)
        {
            if(head == nullptr && tail == nullptr)
                head = tail = new Node<T>(value, nullptr);
            else if(length == 1)
                head->next = tail = new Node<T>(value, nullptr);
            else
                tail = tail->next = new Node<T>(value, nullptr);
            length++;
           
            
        }

        void remove(int index)
        {
            Node<T> * temp = head;
            if(index > 0)
            {
                for(int i = 0; i < index - 1; i++)
                {
                    head = head->next;
                }
                Node<T> * del = head->next; 
                head->next = head->next->next;
                head = temp;
                delete del;
            }
            else if(length == 0)
            {
                length += 1;
                head = tail = nullptr;
            }
            else
            {
                head = head->next;
            }
            length--;

        }

        int size()
        {
            return length;
        }

        void sort()
        {
            mySort(*this);
        }

        void sort(int index)
        {
            for(auto i = begin(); i != end(); i++)
            {
                (*i).setIndex(index);
            }
            mySort(*this);
        }

            void mySort(MyLinkedList<T> & temp)
        {
            MyLinkedList<T> * newHead = new MyLinkedList<T>;
            T * max;
            while(temp.size() > 0)
            {
                int i = 0;
                int indexToDelete = 0;
                max = new T();
                for(auto itr = temp.begin();itr != temp.end();itr++)
                {
                    if(*max < *itr)
                    {
                        indexToDelete = i;
                        *max = *itr;
                    }
                    i++;
                }
                newHead->push_back(*max);
                temp.remove(indexToDelete);
            }
            temp = *newHead;
        }

        struct CustomIterableContainer 
        {
            friend class MyLinkedList;
            public:
                CustomIterableContainer() 
                {
                    cur = head;
                }

                bool operator!=(const CustomIterableContainer & itr) const
                { 
                    return itr.cur != nullptr && cur != nullptr;
                } 

                T & operator*() const 
                {
                    return cur->value;
                }

                CustomIterableContainer operator++(int) 
                {
                    CustomIterableContainer temp = *this;
                    cur = cur->next;
                    return temp;
                }
                CustomIterableContainer operator+(int i)
                {
                    CustomIterableContainer temp = *this;
                    for(int j = 0; j < i; j++)
                    {
                        cur = cur->next;
                    }
                    return temp;
                }
            private:
                Node<T> * cur;
                CustomIterableContainer(Node<T> * cur) 
                {
                    this->cur =cur;
                }
        }; 
    
        CustomIterableContainer begin() const 
        {
          return CustomIterableContainer(head);
        }

        CustomIterableContainer end() const 
        {
          return CustomIterableContainer(tail);
        }
    
    private:
        Node<T> * head;
        Node<T> * tail;
        int length = 0;
};