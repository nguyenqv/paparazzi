/*
 * Copyright (C) 2015 Torbjoern Cunis <t.cunis@tudelft.nl>
 *
 * This file is part of paparazzi:
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file /paparazzi/paparazzi/sw/airborne/modules/delfly_control/delfly_model.c
 * @author Torbjoern Cunis
 */

#include "delfly_model.h"

#include "state_estimation.h"

#include "delfly_algebra_int.h"


struct DelflyModel delfly_model;


void delfly_model_init (void) {

  delfly_model_init_states( &delfly_model.states );
}


void delfly_model_enter (void) {

  delfly_model_assign_states( &delfly_model.states, state_estimation.states.pos, state_estimation.states.vel, state_estimation.states.acc );
  delfly_model_assign_eulers( &delfly_model.states, state_estimation.states.att, state_estimation.states.rot );
}

extern void delfly_model_set_cmd (int32_t cmd_h_acc, int32_t cmd_v_acc) {

  delfly_model.states.acc.x = ( cmd_h_acc * pprz_itrig_cos(delfly_model.states.att.psi) )/(1<<INT32_TRIG_FRAC);
  delfly_model.states.acc.y = ( cmd_h_acc * pprz_itrig_sin(delfly_model.states.att.psi) )/(1<<INT32_TRIG_FRAC);
  delfly_model.states.acc.z =   cmd_v_acc;
}

extern void delfly_model_run (void) {

  delfly_model_predict_states( &delfly_model.states, DELFLY_MODEL_RUN_PERIOD*(1<<INT32_TIME_FRAC) );

  delfly_model_assign_eulers( &delfly_model.states, state_estimation.states.att, state_estimation.states.rot );
}
