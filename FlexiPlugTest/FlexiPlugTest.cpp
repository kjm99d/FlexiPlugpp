#include <FlexiPlugCore_API.h>
#if _WIN64
#pragma comment(lib, "FlexiPlugCorex64.lib")
#else
#pragma comment(lib, "FlexiPlugCore.lib")
#endif

int main(int argc, const char* argv[])
{
	MessageBox(NULL, L"Program Starting ...", NULL, MB_OK);
	FlexiPlugCore_API::Load();
	FlexiPlugCore_API::Link(1);

	while (TRUE)
	{
		Sleep(1000);
	}

	return 0;
}
