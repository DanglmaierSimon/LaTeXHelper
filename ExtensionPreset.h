//Multiple Inclusion Protection
#ifndef EXTENSIONPRESET_H
#define EXTENSIONPRESET_H

#include <vector>

#include "Extension.h"
#include "Object.h"

class ExtensionPreset :	public Object {
public:
	ExtensionPreset(Extension const & ext);
	ExtensionPreset(Extension * ext, size_t const & cnt);
	~ExtensionPreset();

	void AddExtension(Extension const & ext);
	std::vector<Extension> GetExtensions() const;
	void PrintExtensions(bool const printWithPeriod);

private:
	std::vector<Extension> mExtentions;
};

#endif//EXTENSIONPRESET_H