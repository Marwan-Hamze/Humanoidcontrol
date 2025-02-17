#include "Humanoidcontroller.h"

Humanoidcontroller::Humanoidcontroller(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::fsm::Controller(rm, dt, config)
{

  mc_rtc::log::success("Humanoidcontroller init done ");
}

bool Humanoidcontroller::run()
{
  return mc_control::fsm::Controller::run();
}

void Humanoidcontroller::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::fsm::Controller::reset(reset_data);
}


