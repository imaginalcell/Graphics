#include "procgen.h"
#include "crenderutils.h"
#include "Vertex.h"
#include "GLM\gtc\noise.hpp"

Geometry genGrid(unsigned sqr, float dim)
{
	unsigned vsize = sqr*sqr;
	unsigned tsize = (sqr-1)*(sqr-1)*6;
	Vertex *verts = new Vertex[vsize];
	unsigned *tris = new unsigned[tsize];

	for(int r =0; r< sqr; ++r)
		for(int c =0; c< sqr; ++c)
		{
			verts[r*sqr+c].position = glm::vec4((c/(sqr -1.f) -.5f)* dim,0,
				(r / (sqr - 1.f) -.5f)*dim, 1);
												
			verts[r*sqr+c].texcoord = glm::vec2(c/(sqr-1.f), r/(sqr-1.f));
			verts[r*sqr + c].normal = glm::vec4(0, 1, 0, 0);
		} 

	unsigned index = 0;
	for (int r = 0; r< sqr; ++r)
		for (int c = 0; c< sqr; ++c)
		{
			tris[index++]= r * sqr +c;//bottom L corner
			tris[index++]= (r+1) * sqr +c;//bottom R corner
			tris[index++]= (r+1) * sqr +(c+1);//top R

			tris[index++]= r*sqr + c;//B L
			tris[index++]=(r+1) * sqr +c;//B R
			tris[index++]=(r+1) * sqr +(c+1);//T R
		}
	Geometry retval = MakeGeometry(verts,vsize,tris,tsize);

	delete[] verts;
	delete[] tris;
	return retval;
}

Texture NoiseMarine(unsigned sqr, unsigned octaves)
{
	float *noise = new float[sqr*sqr];
	float scale = 1.0f / sqr * 3.f;
	
	for (int x = 0; x < sqr; ++x)
		for (int y = 0; y < sqr; ++y)
		{
			noise[y*sqr + x] = glm::perlin(glm::vec2(x,y)*scale) * 0.5f + 0.5f;
		}

	Texture retval = makeTextureF(sqr, noise);
	delete[] noise;
	return retval;
}
