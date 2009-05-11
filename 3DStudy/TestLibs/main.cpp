#include "boost/test/minimal.hpp"
#include "Vertex.h"
#include "myd3d.h"

struct __Vertex
{
	float x,y,z;
	float nx,ny,nz;
	DWORD color;
	FLOAT tu,tv;
};

int test_main(int argc, char *argv[])
{
	BOOST_REQUIRE( sizeof(__Vertex) == sizeof(Vertex) );
	return 0;
}