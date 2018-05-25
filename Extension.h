//Multiple Inclusion Protection
#ifndef EXTENSION_H
#define EXTENSION_H

#include <string>

#include "Object.h"
class Extension : public Object {
public:
	Extension();
	~Extension();

	void SetExtension(std::string const & ext);
	std::string GetExtension(bool includePeriod);

private:
	std::string ext;
};

#endif//EXTENSION_H