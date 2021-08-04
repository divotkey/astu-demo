#pragma once

// AST Utilities includes
#include <AstuServices.h>

class MainService : public astu::BaseService
{
public:
    
    /** Constructor. */
    MainService();

private:

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;
};