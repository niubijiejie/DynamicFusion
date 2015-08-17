#ifndef WARPFIELD_H
#define WARPFIELD_H

#include "dualquaternion/dual_quat_cu.hpp"
#include "dualquaternion/point3.hpp"
#include "dualquaternion/vec3.hpp"
#include "dualquaternion/mat3.hpp"

#include <vector>

namespace dynamicfusion {
	using namespace Tbx;

	class WarpField {
		public:
			WarpField();
			~WarpField();
			void init();
			bool process();
			void warpFunction();
			void dualQuartornionBlending(
					const std::vector<Point3> &in_verts,
					const std::vector<Vec3> &in_normals,
					std::vector<Vec3> &out_verts,
					std::vector<Vec3> &out_normals,
					const std::vector<Dual_quat_cu> &dual_quat,
					const std::vector<std::vector<float>> &weights,
					const std::vector<std::vector<int>> &joints_id);
			void quaternionToTransformation();

		private:
	};
}

#endif
