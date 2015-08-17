#ifndef DEFORMATIONNODE_H
#define DEFORMATIONNODE_h

#include "dualquaternion/point3.hpp"
#include "dualquaternion/vec3.hpp"
#include "dualquaternion/mat3.hpp"

namespace dynamicfusion {
	using namespace Tbx;

	class DeformationNode{
		public:
			DeformationNode();
			~DeformationNode();
		private:
			Point3 mdg_v;
			float mdg_w;
			Mat3 mdg_se3;
	};
}

#endif
