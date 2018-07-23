#pragma once
// The proxy pattern provides a surrogate, or placeholder for another object
// in order to control access to it.

// There are 3 styles of proxy:
// - Remote Proxy
//   - To be used when a resource that is remote needs to be accesed. e.g.
//     a different namespace, a server, a different code project.
// - Virtual Proxy
//   - A virtual proxy controls access to a resource that is expensive to 
//     create.
// - Protection Proxy
//   - It controls access to a resource based on access rights. Only users who
//     are allowed to access the resource will be granted access.

// The following code will be for a Virtual Proxy, very contrived example 
// because there are definitely better ways to implement the following; but it's
// fine for showcasing the design pattern.

#include <string>
#include <memory>
#include <iostream>

class IBookParser
{
public:
    virtual int getNumPages() = 0;
};

class BookParser : IBookParser
{
public:
    // Let's say the book string contains the contents of a whole book. In other
    // words, it's a HUGE string.
    BookParser(std::string book)
    {
        // Some very expensive process to initialize the BookParser.
        std::cout << "This is a very expensive constructor initialization."
            << std::endl;
    }

    int getNumPages() override
    {
        // Some simple operation, which relies on the constructor being 
        // initialized first.
        std::cout << "There is a cheap operation to get the number of pages."
            << std::endl;
        return 0;
    }
};

class LazyBookParserProxy : IBookParser
{
public:
    LazyBookParserProxy(std::string book) : m_book(book) {}

    int getNumPages() override
    {
        if (m_bookParser == nullptr)
            m_bookParser = std::make_unique<BookParser>(m_book);
        return m_bookParser->getNumPages();
    }

private:
    std::string m_book;
    std::unique_ptr<BookParser> m_bookParser{ nullptr };
};

void VirtualProxyDemo()
{
    LazyBookParserProxy bpp("Some large string");
    std::cout << "BookParser has not been initialized yet, because we do not "
        << "yet need to call getNumPages()." << std::endl;
    std::cout << "Enter any value to call getNumPages()" << std::endl;
    
    std::string temp = "";
    std::cin.ignore();
    std::getline(std::cin, temp);
    bpp.getNumPages();
    std::cout << "Enter any value to exit." << std::endl;
    std::getline(std::cin, temp);
}