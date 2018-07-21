#pragma once
// The abstract factory pattern provides an interface for creating families
// of related or dependent objects without specifying their concrete classes.

// Factory method: Constructs a single object, abstract factory constructs 
// multiple objects.
#include <iostream>
#include <memory>

enum class OS_TYPE
{
    NONE = 0,
    WINDOWS = 1,
    MAC = 2
};

class IDialogBox
{
public:
    IDialogBox(int numButtons) : m_numButtons(numButtons) {}
    virtual void printContents() = 0;

protected:
    int m_numButtons{ 0 };
};

class IMenu
{
public:
    IMenu(int numMenuOptions) : m_numMenuOptions(numMenuOptions) {}
    virtual void printContents() = 0;

protected:
    int m_numMenuOptions{ 0 };
};

class WindowsDialogBox : public IDialogBox
{
public:
    WindowsDialogBox(int numButtons) : IDialogBox(numButtons) {}
    void printContents() override
    {
        std::cout << "Windows dialog box with " << m_numButtons << " buttons.";
    }
};

class MacOSDialogBox : public IDialogBox
{
public:
    MacOSDialogBox(int numButtons) : IDialogBox(numButtons) {}
    void printContents() override
    {
        std::cout << "MacOS dialog box with " << m_numButtons << " buttons.";
    }
};

class WindowsMenu : public IMenu
{
public:
    WindowsMenu(int numButtons) : IMenu(numButtons) {}
    void printContents() override
    {
        std::cout << "Windows menu with " << m_numMenuOptions << " options.";
    }
};

class MacOSMenu : public IMenu
{
public:
    MacOSMenu(int numButtons) : IMenu(numButtons) {}
    void printContents() override
    {
        std::cout << "MacOS menu with " << m_numMenuOptions << " options.";
    }
};

class DialogBoxFactory
{
public:
    std::unique_ptr<IDialogBox> createDialogBox(OS_TYPE osType, int numButtons)
    {
        if (osType == OS_TYPE::WINDOWS)
            return std::make_unique<WindowsDialogBox>(numButtons);
        else if (osType == OS_TYPE::MAC)
            return std::make_unique<MacOSDialogBox>(numButtons);
    }
};

class MenuFactory
{
public:
    std::unique_ptr<IMenu> createMenu(OS_TYPE osType, int numOptions)
    {
        if (osType == OS_TYPE::WINDOWS)
            return std::make_unique<WindowsMenu>(numOptions);
        else if (osType == OS_TYPE::MAC)
            return std::make_unique<MacOSMenu>(numOptions);
    }
};

class UserInterfaceFactory
{
public:
    UserInterfaceFactory(OS_TYPE osType) : m_osType(osType){}
    std::unique_ptr<IDialogBox> createDialogbox(int numButtons)
    {
        return dbf.createDialogBox(m_osType, numButtons);
    }

    std::unique_ptr<IMenu> createMenu(int numOptions)
    {
        return mf.createMenu(m_osType, numOptions);
    }

    void setOSType(OS_TYPE osType)
    {
        m_osType = osType;
    }

private:
    OS_TYPE m_osType;
    MenuFactory mf;
    DialogBoxFactory dbf;
};

inline void AbstractFactoryDemo()
{
    int temp = 0;
    UserInterfaceFactory uif(OS_TYPE::NONE);
    std::unique_ptr<IDialogBox> db;
    std::unique_ptr<IMenu> menu;
    do 
    {
        std::cout << "Enter 0 for Windows UI, 1 for MacOS UI. -1 to exit."
            << std::endl;
        std::cin >> temp;

        if (temp == 0 || temp == 1)
        {
            if (temp == 0)
                uif.setOSType(OS_TYPE::WINDOWS);
            else if (temp == 1)
                uif.setOSType(OS_TYPE::MAC);

            std::cout << "Enter a number." << std::endl;
            std::cin >> temp;
            db = uif.createDialogbox(temp);
            std::cout << "Enter another number." << std::endl;
            std::cin >> temp;
            menu = uif.createMenu(temp);

            std::cout << "The following UI elements have been created: "
                << std::endl;
            db->printContents();
            std::cout << std::endl;
            menu->printContents();
            std::cout << std::endl << std::endl;
        }
        else
            std::cout << "Invalid input." << std::endl << std::endl;

    } while (temp != -1);
}