/*Registry database C++ interface.
	Created By Sai Venu Kiran Bolla
*/
#include "registry.h"


// static members
registry registry::classes_root    (HKEY_CLASSES_ROOT);
registry registry::current_user    (HKEY_CURRENT_USER);
registry registry::local_machine   (HKEY_LOCAL_MACHINE);
registry registry::users           (HKEY_USERS);
registry registry::performance_data(HKEY_PERFORMANCE_DATA);

#if (WINVER >= 0x0400)
registry registry::current_config  (HKEY_CURRENT_CONFIG);
registry registry::dyn_data        (HKEY_DYN_DATA);
#endif // WINVER >= 0x0400


// registry class implementation
registry::registry(
	const registry &     parent,
	const std::wstring & subkey,
	unsigned long        perms /*=KEY_READ*/)
{
	if (RegOpenKeyEx(parent.__key, subkey.c_str(), 0, perms, &__key) != ERROR_SUCCESS)
		__key = (HKEY)0;
}

registry::registry(HKEY parent)
{
	__key = parent;
}

registry::~registry()
{
	if (__key)
		RegCloseKey(__key);
}

bool registry::get(const std::wstring & subkey, std::wstring & value)
{
	bool          ret = false;
	unsigned long type;
	wchar_t       buffer[1024];
	unsigned long size = sizeof(buffer);

	if (__key
			&& RegQueryValueEx(
					__key,
					subkey.c_str(),
					NULL,
					&type,
					(LPBYTE)buffer,
					&size) == ERROR_SUCCESS
			&& type == REG_SZ) {
		value = buffer;
		ret = true;
	}

	return ret;
}

bool registry::get(const std::wstring & subkey, unsigned long & value)
{
	bool          ret = false;
	unsigned long type;
	unsigned long buffer;
	unsigned long size = sizeof(value);

	if (__key
			&& RegQueryValueEx(
					__key,
					subkey.c_str(),
					NULL,
					&type,
					(LPBYTE)&buffer,
					&size)==ERROR_SUCCESS
			&& type == REG_DWORD) {
		value = buffer;
		ret = true;
	}

	return ret;
}

bool registry::put(const std::wstring & subkey, const std::wstring & value)
{
	return (__key
		&& RegSetValueEx(
			__key,
			subkey.c_str(),
			NULL,
			REG_SZ,
			(CONST BYTE *)value.c_str(),
			(1+value.length())*sizeof(wchar_t))==ERROR_SUCCESS);
}

bool registry::put(const std::wstring & subkey, unsigned long value)
{
	return (__key
		&& RegSetValueEx(
			__key,
			subkey.c_str(),
			NULL,
			REG_DWORD,
			(CONST BYTE *)&value,
			sizeof(value))==ERROR_SUCCESS);
}

bool registry::erase(const std::wstring & subkey)
{
	return (__key
		&& (RegDeleteKey(__key, subkey.c_str()) == ERROR_SUCCESS
			|| RegDeleteValue(__key, subkey.c_str()) == ERROR_SUCCESS));
} 


//*****************************************************************************
//                                 END OF FILE
//*****************************************************************************
