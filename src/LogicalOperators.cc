#include "ral/LogicalOperators.h"
#include "ROOT/RVec.hxx"
#include <stdexcept>
#include <string>

namespace k4::ral {

namespace LogicalOperators {

ROOT::VecOps::RVec<bool> operator&&(const ROOT::VecOps::RVec<bool> &vec1,
                                    const ROOT::VecOps::RVec<bool> &vec2) {
  if (vec1.size() != vec2.size()) {
    auto msg = "Different vector lenghts: " + std::to_string(vec1.size()) +
               " and " + std::to_string(vec2.size()) + ".";
    throw std::length_error(msg);
  }
  ROOT::VecOps::RVec<bool> result;
  result.reserve(vec1.size());
  for (int i = 0; i < vec1.size(); i++) {
    result[i] = vec1[i] && vec2[i];
  }
  return result;
}

ROOT::VecOps::RVec<bool> operator||(const ROOT::VecOps::RVec<bool> &vec1,
                                    const ROOT::VecOps::RVec<bool> &vec2) {
  if (vec1.size() != vec2.size()) {
    auto msg = "Different vector lenghts: " + std::to_string(vec1.size()) +
               " and " + std::to_string(vec2.size()) + ".";
    throw std::length_error(msg);
  }
  ROOT::VecOps::RVec<bool> result;
  result.reserve(vec1.size());
  for (int i = 0; i < vec1.size(); i++) {
    result[i] = vec1[i] && vec2[i];
  }
  return result;
}

ROOT::VecOps::RVec<bool> operator!(const ROOT::VecOps::RVec<bool> &vec1) {
  ROOT::VecOps::RVec<bool> result;
  result.reserve(vec1.size());
  for (int i = 0; i < vec1.size(); i++) {
    result[i] = !vec1[i];
  }
  return result;
}

} // namespace LogicalOperators
} // namespace k4::ral
