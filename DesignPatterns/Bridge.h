#pragma once
// The intent of the bridge pattern is to decouple an abstraction from its 
// implementation so the two can vary independantly.

// Problem: We have two types of resources which rely on each other,
// Resource A and Resource B. If we have 3 types of Resource A, and 3 types
// of Resource B we will need 9 total classes we have to create.
// The bridge pattern makes it so instead, we have to create 3 classes of 
// type Resource A, 3 classes of Resource B, and 1 interface and 1
// abstract class. The more total resources we have, the benefits of the bridge
// pattern shows.

#include <iostream>
#include <string>

class IResource
{
public:
    virtual std::string shortDescription() = 0;
    virtual std::string longDescription() = 0;
    virtual std::string title() = 0;
    virtual std::string image() = 0;
protected:
    ~IResource() {};
};

class SongResource : public IResource
{
public:
    std::string shortDescription() override
    {
        return "Short song description.";
    }

    std::string longDescription() override
    {
        return "Long song description.";
    }

    std::string title() override
    {
        return "Song title.";
    }

    std::string image() override
    {
        return "Song's album image.";
    }
};

class BookResource : public IResource
{
public:
    std::string shortDescription() override
    {
        return "Short book description.";
    }

    std::string longDescription() override
    {
        return "Long book description.";
    }

    std::string title() override
    {
        return "Book title.";
    }

    std::string image() override
    {
        return "Book's cover image.";
    }
};

class View
{
public:
    View(IResource &resource) : m_resource(&resource) {}
    virtual void show() = 0;

protected:
    IResource *m_resource;
};

class LongFormView : public View
{
public:
    LongFormView(IResource &resource) : View(resource) {};
    void show() override
    {
        std::cout << "Showing: " << std::endl;
        std::cout << m_resource->image() << std::endl;
        std::cout << m_resource->title() << std::endl;
        std::cout << m_resource->longDescription() << std::endl;
    }
};

class MediumFormView : public View
{
public:
    MediumFormView(IResource &resource) : View(resource) {};
    void show() override
    {
        std::cout << "Showing: " << std::endl;
        std::cout << m_resource->image() << std::endl;
        std::cout << m_resource->title() << std::endl;
        std::cout << m_resource->shortDescription() << std::endl;
    }
};

class ShortFormView : public View
{
public:
    ShortFormView(IResource &resource) : View(resource) {};
    void show() override
    {
        std::cout << "Showing: " << std::endl;
        std::cout << m_resource->title() << std::endl;
        std::cout << m_resource->shortDescription() << std::endl;
    }
};

void BridgeDemo()
{
    BookResource br;
    SongResource sr;

    ShortFormView sfvBook(br);
    ShortFormView sfvSong(sr);
    
    MediumFormView mfvBook(br);
    MediumFormView mfvSong(sr);

    LongFormView lfvBook(br);
    LongFormView lfvSong(sr);

    auto temp = 0;
    do
    {
        std::cout << "Select which view to show: " << std::endl;
        std::cout << "1. Short Form View of a Book" << std::endl;
        std::cout << "2. Short Form View of a Song" << std::endl;
        std::cout << "3. Medium Form View of a Book" << std::endl;
        std::cout << "4. Medium Form View of a Song" << std::endl;
        std::cout << "5. Long Form View of a Book" << std::endl;
        std::cout << "6. Long Form View of a Song" << std::endl;
        std::cout << "-1 to exit." << std::endl;

        std::cin.ignore();
        std::cin >> temp;
        std::cout << std::endl;

        switch (temp)
        {
            case 1:
                sfvBook.show();
                break;
            case 2:
                sfvSong.show();
                break;
            case 3:
                mfvBook.show();
                break;
            case 4:
                mfvSong.show();
                break;
            case 5:
                lfvBook.show();
                break;
            case 6:
                lfvSong.show();
                break;
        }

        std::cout << std::endl;
    } while (temp != -1);
}