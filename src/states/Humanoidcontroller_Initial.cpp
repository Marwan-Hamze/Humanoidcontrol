#include "Humanoidcontroller_Initial.h"

#include "../Humanoidcontroller.h"

void Humanoidcontroller_Initial::configure(const mc_rtc::Configuration & config)
{
}

void Humanoidcontroller_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<Humanoidcontroller &>(ctl_);
}

bool Humanoidcontroller_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<Humanoidcontroller &>(ctl_);
  output("OK");
  return true;
}

void Humanoidcontroller_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<Humanoidcontroller &>(ctl_);
}

EXPORT_SINGLE_STATE("Humanoidcontroller_Initial", Humanoidcontroller_Initial)
