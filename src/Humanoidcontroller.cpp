#include "Humanoidcontroller.h"

Humanoidcontroller::Humanoidcontroller(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::fsm::Controller(rm, dt, config)
{

  // Loading the configuration of the controller from the YAML file
  config_.load(config);

  Activedof_ = {"Root", "R_HIP_Y", "R_HIP_R","R_HIP_P", "R_KNEE","R_ANKLE_P", "R_ANKLE_R",
                "L_HIP_Y",  "L_HIP_R", "L_HIP_P","L_KNEE","L_ANKLE_P","L_ANKLE_R"};

  Activedof_Arms_ = {"R_SHOULDER_P", "R_SHOULDER_R", "R_SHOULDER_Y", "R_ELBOW_P",    "R_ELBOW_Y", "R_WRIST_R", "R_WRIST_Y",
                     "L_SHOULDER_P", "L_SHOULDER_R", "L_SHOULDER_Y", "L_ELBOW_P", "L_ELBOW_Y", "L_WRIST_R","L_WRIST_Y"};


  comTask_ = std::make_shared<mc_tasks::CoMTask>(robots(), robots().robot().robotIndex(), 2, 1e7);
  baseTask_ = std::make_shared<mc_tasks::OrientationTask>("WAIST_R_S", robots(), robots().robot().robotIndex(), 2, 1e7);

  rightFoot_CoPTask_ = std::make_shared<mc_tasks::force::CoPTask>("RightFoot", robots(), robots().robot().robotIndex(), 5, 1e7);
  leftFoot_PosTask_ = std::make_shared<mc_tasks::PositionTask>("L_ANKLE_P_S", robots(), robots().robot().robotIndex(), 2, 1e9);

  rightHand_PosTask_ = std::make_shared<mc_tasks::PositionTask>("R_WRIST_Y_S", robots(), robots().robot().robotIndex(), 2, 1e7);
  leftHand_PosTask_ = std::make_shared<mc_tasks::PositionTask>("L_WRIST_Y_S", robots(), robots().robot().robotIndex(), 2, 1e7);


  logger().addLogEntry("JVRC_CoM", [this]() { return realRobots().robot().com(); });

  mc_rtc::log::success("Humanoidcontroller init done ");
}

bool Humanoidcontroller::run()
{
  // Moving the CoM
  if(!CoM && Hands && !click) 

  {
  
  click = true;

    gui()->removeElement({"Controller"}, "MoveHands");

    gui()->addElement({"Controller"}, mc_rtc::gui::Button("MoveCoM", [this]() {

    solver().addTask(rightHand_PosTask_);
    solver().addTask(leftHand_PosTask_);

    comTask_->com(comTask_->com() - Eigen::Vector3d{0, 0.1, 0});

    CoM = true;

    mc_rtc::log::info("Moved the CoM to be above the Right Foot\n");

    }));

  }
  // Lifting the left foot
  if(CoM && !Foot && !click_2)
  
  {

    click_2 = true;

    gui()->removeElement({"Controller"}, "MoveCoM");

    gui()->addElement({"Controller"}, mc_rtc::gui::Button("LiftFoot", [this]() {

      solver().addTask(rightFoot_CoPTask_);
      solver().addTask(leftFoot_PosTask_);

  
      removeContact({robot().name(), "ground", "LeftFoot", "AllGround"});
      leftFoot_PosTask_->position(Eigen::Vector3d{0, 0.1, 0.2});
  
      mc_rtc::log::info("Left Foot is in the Air!\n");
  
      Foot = true;
  
      }));

  }
  // Removing the last button from the GUI
  if(Foot)

  {

    gui()->removeElement({"Controller"}, "LiftFoot");

  }


  return mc_control::fsm::Controller::run();
}

void Humanoidcontroller::reset(const mc_control::ControllerResetData & reset_data)
{
  // Resetting all tasks
  comTask_->reset();
  baseTask_->reset();

  rightFoot_CoPTask_->reset();
  leftFoot_PosTask_->reset();

  rightHand_PosTask_->reset();
  leftHand_PosTask_->reset();

  // Make the CoM and the root tasks use the joints of the legs only
  comTask_->selectActiveJoints(Activedof_);
  baseTask_->selectActiveJoints(Activedof_);

  solver().addTask(comTask_);
  solver().addTask(baseTask_);

  // Moving the Arms:
  if (!Hands) {
    gui()->addElement({"Controller"}, mc_rtc::gui::Button("MoveHands", [this]() {

      rightHand_PosTask_->selectActiveJoints(Activedof_Arms_);
      leftHand_PosTask_->selectActiveJoints(Activedof_Arms_);
      solver().addTask(rightHand_PosTask_);
      solver().addTask(leftHand_PosTask_);

      rightHand_PosTask_->position(Eigen::Vector3d{0.025, -0.6, 0.85});
      leftHand_PosTask_->position(Eigen::Vector3d{0.025, 0.6, 0.85});

      Hands = true;

      mc_rtc::log::info("Arms Spread!\n");

   }));
  }

  mc_control::fsm::Controller::reset(reset_data);
}


