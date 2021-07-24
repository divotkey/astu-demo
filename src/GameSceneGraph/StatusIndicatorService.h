#pragma once

// AST Utilities includes
#include <Services.h>

// C++ Standard Libray includes
#include <string>

class StatusIndicatorService 
    : public astu::BaseService
    , public astu::ISignalListener<std::string>
{
public:

    /**
     * Constructor.
     * 
     * @param windowTitle   the title for the application window
     */
    StatusIndicatorService(const std::string & windowTitle = "");

    /**
     * Specifies the title for the application window.
     * 
     * @param title the title
     */
    void SetWindowTitle(const std::string & title);

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;


    // Inherited via ISignalListener<std::string>
    virtual bool OnSignal(const std::string & signal) override;

private:
    /** The title of the application window. */
    std::string title;

    /** The last received status messages. */
    std::string status;

    /**
     * Updates the title of the application window.
     */
    void UpdateTitle();
};