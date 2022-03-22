#include <EigenLinearSolvers/config.h>

#include <sofa/core/ObjectFactory.h>
using sofa::core::ObjectFactory;

extern "C" {
    SOFA_EIGENLINEARSOLVERS_API void initExternalModule();
    SOFA_EIGENLINEARSOLVERS_API const char* getModuleName();
    SOFA_EIGENLINEARSOLVERS_API const char* getModuleVersion();
    SOFA_EIGENLINEARSOLVERS_API const char* getModuleLicense();
    SOFA_EIGENLINEARSOLVERS_API const char* getModuleDescription();
    SOFA_EIGENLINEARSOLVERS_API const char* getModuleComponentList();
}

void initExternalModule()
{
    static bool first = true;
    if (first)
    {
        first = false;
    }
}

const char* getModuleName()
{
    return sofa_tostring(SOFA_TARGET);
}

const char* getModuleVersion()
{
    return sofa_tostring(EIGENLINEARSOLVERS_VERSION);
}

const char* getModuleLicense()
{
    return "MIT";
}

const char* getModuleDescription()
{
    return "SOFA plugin wrapping the Eigen linear solvers into SOFA components";
}

const char* getModuleComponentList()
{
    /// string containing the names of the classes provided by the plugin
    static std::string classes = ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
    return classes.c_str();
}
