
#include<cpprest\details\basic_types.h>
using namespace utility;

//<< Add all the constants here >>//
namespace ServerMessages {
	const static wstring INVALID_URL = L"Invalid Uri";
	const static wstring FILE_NOT_FOUND = L"File requested not found: ";
	const static wstring INTERNAL_ERROR = L"Some Internal error occured";
	const static wstring CONFIG_ERROR = L"Unable to read the config file";
	const static wstring ACCOUNT_NOT_FOUND = L"Account not found";
	const static wstring ACCOUNT_ALREADY_EXISTS = L"Account already exists";
	const static wstring ACCOUNT_CREATION_FAILED = L"Account already exists";
}