#ifndef __MATHS_H__
#define __MATHS_H__

#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Maths {

public:

	inline static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
	{
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}

	inline static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale_) {
		glm::mat4 matrix(1.0);
		matrix = translate(matrix, glm::vec3(translation.x,translation.y,0.));
		matrix = scale(matrix, glm::vec3(scale_.x, scale_.y, 1.0));
		return matrix;
	}
	inline static glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scaleValue) {
		glm::mat4 matrix(1.0);
		matrix=translate(matrix, translation);
		matrix=glm:: rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));
		matrix=glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));
		matrix=glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));
		matrix=glm::scale(matrix, glm::vec3(scaleValue, scaleValue, scaleValue));
		return matrix;
	}

};









#endif
