#pragma once
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <codecvt>
#include <locale>

std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

template <typename T>
class LinkedList 
{
private:
    class Node 
    {
    public:
        T data;
        Node* next;

        Node(T data) 
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    Node* head;
    int size;

public:
    LinkedList() 
    {
        head = nullptr;
        size = 0;
    }

    ~LinkedList() 
    {
        clear();
    }

    void pushFront(T data) 
    {
        Node* new_node = new Node(data);
        new_node->next = head;
        head = new_node;
        size++;
    }

    void pushBack(T data) 
    {
        Node* new_node = new Node(data);
        if (head == nullptr) 
        {
            head = new_node;
        }
        else 
        {
            Node* current = head;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            current->next = new_node;
        }
        size++;
    }

    void clear() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
        size = 0;
    }

    int getSize() const 
    {
        return size;
    }

    T& operator[](int index) const 
    {
        Node* current = head;
        for (int i = 0; i < index; i++) 
        {
            current = current->next;
        }
        return current->data;
    }
};