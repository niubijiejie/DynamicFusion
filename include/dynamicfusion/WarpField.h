#ifndef WARPFIELD_H
#define WARPFIELD_H

namespace dynamicfusion {
	class WarpField {
		public:
			WarpField();
			~WarpField();
			void init();
			bool process();
			void warpFunction();
			void dualQuartornionBlending();
			void quaternionToTransformation();

		private:
	};
}

#endif
