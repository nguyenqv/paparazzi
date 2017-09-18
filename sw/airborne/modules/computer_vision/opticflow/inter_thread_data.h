/*
 * Copyright (C) 2015 The Paparazzi Community
 *
 * This file is part of Paparazzi.
 *
 * Paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file modules/computer_vision/opticflow/inter_thread_data.h
 * @brief Inter-thread data structures.
 *
 * Data structures used to for inter-thread communication via Unix Domain sockets.
 */


#ifndef _INTER_THREAD_DATA_H
#define _INTER_THREAD_DATA_H

#include "math/pprz_algebra_float.h"
#include "math/pprz_algebra_int.h"


/* The result calculated from the opticflow */
struct opticflow_result_t {
  float fps;              ///< Frames per second of the optical flow calculation
  uint16_t corner_cnt;    ///< The amount of coners found by FAST9
  uint16_t tracked_cnt;   ///< The amount of tracked corners

  int16_t flow_x;         ///< Flow in x direction from the camera (in subpixels)
  int16_t flow_y;         ///< Flow in y direction from the camera (in subpixels)
  int16_t flow_der_x;     ///< The derotated flow calculation in the x direction (in subpixels)
  int16_t flow_der_y;     ///< The derotated flow calculation in the y direction (in subpixels)

  float vel_x;            ///< The velocity in the x direction (image coordinates)
  float vel_y;            ///< The velocity in the y direction (image coordinates)

  float vel_body_x;     ///< The velocity in the x direction (body fixed coordinates)
  float vel_body_y;     ///< The velocity in the y direction (body fixed coordinates)

  float div_size;         ///< Divergence as determined with the size_divergence script

  float surface_roughness; ///< Surface roughness as determined with a linear optical flow fit
  float divergence;       ///< Divergence as determined with a linear flow fit

  float noise_measurement;  ///< noise of measurement, for state filter
};

/* The state of the drone when it took an image */
struct opticflow_state_t {
  struct FloatRates rates;   ///< Body rates
  struct FloatEulers euler;   ///< Body euler angles
  float agl;                 ///< height above ground [m]
  struct FloatQuat imu_to_body_quat;   ///< imu to body quaternion
  struct Int32Vect3 accel_imu_meas;    ///< imu acceleration in imu's coordinates
};

#endif


