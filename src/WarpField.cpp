#include "dynamicfusion/core/WarpField.h"
#include "dualquaternion/dual_quat_cu.hpp"

#include <vector>

namespace dynamicfusion {
	using namespace Tbx;

	WarpField::WarpField() {
	}

	WarpField::~WarpField() {
	}

	void WarpField::init() {
	}

	bool WarpField::process() {
	}

	void WarpField::warpFunction() {
	}

	/*
	 * Transforms point from canonical space into the live, non-rigidly deformed frame of reference.
	 *
	 * @note Originally this was CUDA code. Aside from this deformer function
	 * which uses std::vector every other classes and methods should be readily
	 * convertible to CUDA code ust by adding __host__ __device__ flags before
	 * their definitions.
	 *
	 * @param in_verts : vector of mesh vertices
	 * @param in_verts : vector of mesh vertices 
	 * @param in_normals : vector of mesh normals (same order as 'in_verts') 
	 * @param out_verts : deformed vertices with dual quaternions
	 * @param out_normals : deformed normals with dual quaternions
	 * @param dual_quat : list of dual quaternions transformations per joints
	 * @param weights : list of influence weights for each vertex
	 * @param joints_id : list of joints influence fore each vertex (same order as 'weights')
	 */
	void WarpField::DualQuartornionBlending(
			const std::vector<Point3> &in_verts,
			const std::vector<Vec3> &in_normals,
			std::vector<Vec3> &out_verts,
			std::vector<Vec3> &out_normals,
			const std::vector<Dual_quat_cu> &dual_quat,
			const std::vector<std::vector<float>> &weights,
			const std::vector<std::vector<int> &joints_id) {
		for (unsigned v = 0; v < in_verts.size(); ++v) {
			const int nb_joints = weights[v].size(); // Number of joints influencing vertex p

			//Init dual quaternion with first joint transformation
			int k0 = -1;
			float w0 = 0.0f;
			Dual_quat_cu dq_blend;
			Quat_cu q0;

			if (nb_joints != 0) {
				k0 = joints_id[v][0];
				w0 = weights[v][0];
			} else {
				dq_blend = Dual_quat_cu::identity();
			}

			if (k0 != -1)
				dq_blend = dual_quat[k0] * w0;

			int pivot = k0;

			q0 = dual_quat[pivot].rotation();
			// Look up the other joints influencing 'p' if any
			for (int j = 1; j < nb_joints; ++j) {
				const int k = joints_id[v][j];
				float w = weights[v][j];
				const Dual_quat_cu &dq = (k == -1) ? Dual_quat_cu::identity() : dual_quat[k];

				if (dq.rotation().dot(q0) < 0.0f)
					w *= -1.0f;

				dq_blend = dq_blend + dq * w;
			}

			// Compute animated position
			Vec3 vi = dq_blend.transform(in_verts[v]).to_vec3();
			out_verts[v] = vi;

			// Compute animated normal
			out_normals[v] = dq_blend.rotate(in_normals[v]);
		}
	}

	void WarpField::quaternionToTransformation() {
	}
}
