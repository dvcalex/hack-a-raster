#include"Globals.h"
#ifdef MY_DEBUG

#include"OBJToMyMesh.h"

int main()
{
	std::cout << "DEBUG MODE" << '\n';

	std::string cppCode = Rasterizer::ParseOBJToMyMesh(Rasterizer::cubeOBJ);
	std::cout << cppCode << std::endl;

	return 0;
}


#endif // MY_DEBUG
