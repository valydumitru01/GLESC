#pragma once

#include "Component.h"
#include "glm.hpp"

class CameraComponent : Component {
public:
	glm::vec3 position;
	glm::quat rotation;
	float fov;
	Entity target;
	
	static glm::mat4
	MakeProjectionTransform(float fov, float nearClip, float farClip, unsigned int viewWidth,
							unsigned int viewHeight) {
		float zClipBias0 = (farClip + nearClip) / (farClip - nearClip);
		
		float zClipBias1 = (2.0f * farClip * nearClip) / (farClip - nearClip);
		
		float zoomX = 1.0f / tanf((fov / 2.0f) * (M_PI / 180.0f));
		float zoomY = (zoomX * static_cast<float>(viewWidth)) / static_cast<float>(viewHeight);
		
		glm::mat4 transform;
		transform[0][0] = zoomX;
		transform[1][1] = zoomY;
		transform[2][2] = -zClipBias0;
		transform[3][2] = -1;
		transform[2][3] = -zClipBias1;
		
		return transform;
	}
};

