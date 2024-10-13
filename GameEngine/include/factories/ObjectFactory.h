#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "IObjectFactory.h"
#include "GuiHandler.h" // for RenderObject. Consider about placing all this enums and structs in separate file

class ObjectFactory {
public:
	// if there will be some error take look at unique_ptr
	static std::unique_ptr<IObjectFactory> GetFactory(RenderObject object, Solid& solid);
};

#endif