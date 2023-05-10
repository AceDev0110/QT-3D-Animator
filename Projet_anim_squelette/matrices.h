#ifndef MATRICES_H
#define MATRICES_H

#include <cmath>
#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

typedef glm::mat4 Mat4;
typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;



/// matrix CREATION SHORTCUTS

inline Mat4 translate(float tx, float ty, float tz) { return glm::translate(Vec3(tx,ty,tz));}

inline Mat4 scale(float sx, float sy, float sz) { return glm::scale(Vec3(sx,sy,sz));}

inline Mat4 scale(float s) { return glm::scale(Vec3(s,s,s));}

inline Mat4 rotateX(float alpha) { return glm::rotate(float(M_PI/180*alpha), Vec3(1,0,0));}

inline Mat4 rotateY(float alpha) { return glm::rotate(float(M_PI/180*alpha), Vec3(0,1,0));}

inline Mat4 rotateZ(float alpha) { return glm::rotate(float(M_PI/180*alpha), Vec3(0,0,1));}


///for  std::cout << Mat4
inline std::ostream &operator<< (std::ostream &out, const Mat4 &m)
{
	for (int i=0;i<3;++i)
	{
		for (int j=0;j<4;++j)
			out << "|" << std::setprecision(5) << std::fixed << std::setw(10) << m[j][i] << " ";
		out << "|" << std::endl;
	}

	for (int j=0;j<4;++j)
		out << "|" << std::setprecision(5) << std::fixed << std::setw(10) << m[j][3] << " ";
	out << "|";


	return out;
}


/// for std::cout << Vec3
inline std::ostream &operator<< (std::ostream &out, const Vec3 &v)
{
	out << "( " << v[0] << " , "<< v[1] << " , "<< v[2] << " )";
	return out;
}


#endif // MATRICES_H
