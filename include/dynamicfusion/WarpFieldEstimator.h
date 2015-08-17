#ifndef WARPFIELDESTIMATOR_H
#define WARPFIELDESTIMATOR_H

#include "dynamicfusion/WarpField.h"
#include "dynamicfusion/RegularisationGraph.h"
#include "dynamicfusion/TSDF.h"

#include <opencv2/core/core.hpp>

namespace dynamicfusion {
	using namespace dynamicfusion;

	class WarpFieldEstimator {
		public:
			WarpFieldEstimator();
			~WarpFieldEstimator();
			void energyFunction(
					const WarpField W_t,
					const TSDF V,
					const cv::Mat D_t,
					const RegularisationGraph epsilon);

		private:
			void energyData(
					const WarpField W_t,
					const TSDF V,
					const cv::Mat D_t);
			void energyReg(
					const WarpField W_t,
					const RegularisationGraph epsilon);
			double tukeyPenaltyFunction(
					double threshold,
					double x,
					double c);
			void huberPenaltyFunction();
	};
}

#endif
