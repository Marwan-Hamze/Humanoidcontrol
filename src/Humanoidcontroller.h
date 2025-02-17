#pragma once

#include <mc_control/mc_controller.h>
#include <mc_control/fsm/Controller.h>
#include <mc_tasks/CoMTask.h>
#include <mc_tasks/PositionTask.h>
#include <mc_tasks/OrientationTask.h>
#include <mc_tasks/AdmittanceTask.h>
#include <mc_tasks/CoPTask.h>

#include "api.h"

struct Humanoidcontroller_DLLAPI Humanoidcontroller : public mc_control::fsm::Controller
{
  Humanoidcontroller(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

  bool run() override;

  void reset(const mc_control::ControllerResetData & reset_data) override;

  private:

  // To use buttons in the GUI for adding tasks in the solver, I define these booleans:

  bool click = false;
  bool click_2 = false;
  bool CoM = false;
  bool Foot = false;
  bool Hands = false;

  // Tasks needed for the robot motion:

  std::shared_ptr<mc_tasks::CoMTask> comTask_;
  std::shared_ptr<mc_tasks::OrientationTask> baseTask_;
  std::shared_ptr<mc_tasks::OrientationTask> chestTask_;

  std::shared_ptr<mc_tasks::force::CoPTask> rightFoot_CoPTask_;
  
  std::shared_ptr<mc_tasks::PositionTask> leftFoot_PosTask_;

  std::shared_ptr<mc_tasks::PositionTask> rightHand_PosTask_;
  std::shared_ptr<mc_tasks::PositionTask> leftHand_PosTask_;

  // To select which joints to use for specidic tasks, I define these strings:

  std::vector<std::string> Activedof_;
  std::vector<std::string> Activedof_Arms_;

};