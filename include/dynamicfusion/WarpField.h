#ifndef WARPFIELD_H
#define WARPFIELD_H

namespace dynamicfusion {
	class WarpField {
		public:
			WarpField();
			~WarpField();
			void init();
			bool process();
			void WarpFunction();
			void DualQuartornionBlending();
			void QuaternionToTransformation();

		private:
	};
}

#endif
