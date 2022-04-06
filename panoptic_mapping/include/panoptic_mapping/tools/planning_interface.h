#ifndef PANOPTIC_MAPPING_TOOLS_PLANNING_INTERFACE_H_
#define PANOPTIC_MAPPING_TOOLS_PLANNING_INTERFACE_H_

#include <memory>

#include "panoptic_mapping/map/submap.h"
#include "panoptic_mapping/map/submap_collection.h"

namespace panoptic_mapping {

/**
 * @brief This class implements a high level interfaces for lookups on the
 * submap collection.
 */
class PlanningInterface {
 public:
  explicit PlanningInterface(std::shared_ptr<const SubmapCollection> submaps);

  enum class VoxelState {
    kUnknown = 0,
    kKnownFree,
    kKnownOccupied,
    kPersistentOccupied,
    kExpectedFree,
    kExpectedOccupied,
  };

  // Access.
  const SubmapCollection& getSubmapCollection() const { return *submaps_; }

  // Lookups.
  bool isObserved(const Point& position,
                  bool include_inactive_maps = true) const;
  VoxelState getVoxelState(const Point& position) const;
  bool getDistance(const Point& position, float* distance,
                   bool consider_change_state = true,
                   bool include_free_space = true) const;

 private:
  std::shared_ptr<const SubmapCollection> submaps_;
  static constexpr float kObservedMinWeight_ = 1e-6;
};

}  // namespace panoptic_mapping

#endif  // PANOPTIC_MAPPING_TOOLS_PLANNING_INTERFACE_H_
