# map.inc - useful setup for a floorplan bitmap
# Authors: Richard Vaughan
# $Id$

define floorplan model
(
  # sombre, sensible, artistic
  color "red30"

  # most maps will need a bounding box
  boundary 1

  gui_nose 1
  gui_grid 0
  gui_move 0
  gui_outline 1
  gripper_return 0
  fiducial_return 0
  ranger_return 0.5

  obstacle_return 0
)

