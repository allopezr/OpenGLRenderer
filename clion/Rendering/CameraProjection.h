/*   Copyright (C) 2023 Lidia Ortega Alvarado, Alfonso Lopez Ruiz
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see https://github.com/AlfonsoLRz/AG2223.
*/

#pragma once

namespace PAG
{
	class CameraProjection
	{
	protected:
		static std::vector<std::shared_ptr<CameraProjection>> _cameraProjection;

	public:
		enum Projection
		{
			PERSPECTIVE, ORTHOGRAPHIC
		};

		class CameraProperties
		{
		public:
			int								_cameraType;

			vec3							_eye, _lookAt, _up;
			float							_zNear, _zFar;
			float							_aspect;
			float							_fovY, _fovX;
			vec2							_bottomLeftCorner;
			uint16_t						_width, _height;
			vec3							_n, _u, _v;
			mat4							_viewMatrix, _projectionMatrix, _viewProjectionMatrix;

			float	computeAspect();
			void	computeAxes(vec3& n, vec3& u, vec3& v);
			vec2	computeBottomLeftCorner();
			float	computeFovY();

			void	computeProjectionMatrices(CameraProperties* camera);
			void	computeViewMatrices();
			void	computeViewMatrix();

			void	zoom(float speed);
		};

	public:
		virtual mat4 buildProjectionMatrix(CameraProperties* camera) = 0;
		virtual void zoom(CameraProperties* camera, const float speed) = 0;
	};

	class PerspectiveProjection : public CameraProjection
	{
	public:
		virtual mat4 buildProjectionMatrix(CameraProperties* camera);
		virtual void zoom(CameraProperties* camera, const float speed);
	};

	class OrthographicProjection : public CameraProjection
	{
	public:
		virtual mat4 buildProjectionMatrix(CameraProperties* camera);
		virtual void zoom(CameraProperties* camera, const float speed);
	};
}

