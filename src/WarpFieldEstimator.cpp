#include "dynamicfusion/WarpFieldEstimator.h"

namespace dynamicfusion {
	using namespace dynamicfusion;

	WarpFieldEstimator::WarpFieldEstimator() {
	}

	WarpFieldEstimator::~WarpFieldEstimator() {
	}

	/*
	 * E(W_t, V, D_t, epsilon) = Data(W_t, V, D_t) + lambda * Reg(W_t, epsilon)
	 */
	void WarpFieldEstimator::energyFunction(
			const WarpField W_t,
			const TSDF V,
			const cv::Mat D_t,
			const RegularisationGraph epsilon) {
	}

	void WarpFieldEstimator::energyData(
			const WarpField W_t,
			const TSDF V,
			const cv::Mat D_t) {
	}

	void WarpFieldEstimator::energyReg(
			const WarpField W_t,
			const RegularisationGraph epsilon) {
	}

	double WarpFieldEstimator::tukeyPenaltyFunction(
			double threshold,
			double x,
			double c) {
		double x_abs;

		if (x_abs > threshold) {
			return x * (1 - (x * x) / (c * c)) * (1 - (x * x) / (c * c));
		} else
			return 0.0;
	}

	void WarpFieldEstimator::huberPenaltyFunction() {
	}
}
