/*Registry database C++ interface.
	Created By Sai Venu Kiran Bolla
*/

#ifndef __REGISTRY_H_49349
#define __REGISTRY_H_49349

#include <windows.h>
#include <regstr.h>
#include <string>

// registry class interface
class registry
{
public:
	registry(const registry & parent, const std::wstring & subkey, unsigned long perms =KEY_READ);
	virtual ~registry();

	bool get(const std::wstring & subkey, std::wstring       & value);
	bool get(const std::wstring & subkey, unsigned long      & value);
	bool put(const std::wstring & subkey, const std::wstring & value);
	bool put(const std::wstring & subkey, unsigned long        value);
	bool erase(const std::wstring & subkey);

	static registry classes_root;
	static registry current_user;
	static registry local_machine;
	static registry users;
	static registry performance_data;
#if (WINVER >= 0x0400)
	static registry current_config;
	static registry dyn_data;
#endif // WINVER >= 0x0400

protected:
	registry(HKEY parent);

private:
	HKEY __key;
};

#endif	// __REGISTRY_H_49349


//*****************************************************************************
//                                 END OF FILE
//*****************************************************************************
