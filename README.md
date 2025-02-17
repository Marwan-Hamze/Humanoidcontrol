In this project, I control the JVRC1 humanoid robot to move its arms, center of mass (CoM), and lift its left foot in the air, in succession. 
Every motion is represented by a set of tasks in task space. The motion is executed by pressing buttons in the GUI.

The controller is formulated using the [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/index.html) framework, which is REQUIRED TO INSTALL. mc_rtc uses a QP solver to transform the tasks to joint space.

Simulation is best run using [mc_mujoco](https://github.com/rohanpsingh/mc_mujoco). It's highly recommended to download mc_mujoco first.

To install the controller:

$ git clone https://github.com/Marwan-Hamze/Humanoidcontrol.git
$ cd Humanoidcontrol
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make install

To load the controller, the global mc_rtc configuration file (mc_rtc.yaml) should have:

MainRobot: JVRC1
Enabled: Humanoidcontroller

Finally, run the simulation interface with:

$ mc_mujoco
