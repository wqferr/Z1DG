/*
MIT License

Copyright (c) 2016 Mariano Trebino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef C8F4E798_AEAC_47C5_90DA_1D7B512F23BE
#define C8F4E798_AEAC_47C5_90DA_1D7B512F23BE

namespace z1dg {
    template <class T>
    class StackLinkedList {
    public:
        struct Node {
            T data;
            Node* next;
        };

        Node* head;
    public:
        StackLinkedList() = default;
        StackLinkedList(StackLinkedList &stackLinkedList) = delete;
        void push(Node * newNode);
        Node* pop();
    };

    template <class T>
    void StackLinkedList<T>::push(Node * newNode) {
        newNode->next = head;
        head = newNode;
    }

    template <class T>
    typename StackLinkedList<T>::Node* StackLinkedList<T>::pop() {
        Node * top = head;
        head = head->next;
        return top;
    }
}

#endif/* C8F4E798_AEAC_47C5_90DA_1D7B512F23BE */
