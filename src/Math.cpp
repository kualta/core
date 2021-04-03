#include <cmath>
#include "Math.h"

namespace core {

const float Math::PI = float( 4.0 * std::atan( 1.0 ) );
const float Math::TWO_PI = float( 2.0 * PI );
const float Math::HALF_PI = float( 0.5 * PI );
const float Math::fDeg2Rad = PI / float(180.0);
const float Math::fRad2Deg = float(180.0) / PI;
const float Math::LOG2 = std::log(float(2.0));

} // namespace