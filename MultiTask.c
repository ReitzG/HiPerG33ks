/*
http://www.robotc.net/support/nxt/MindstormsWebHelp/index.htm#page=nxt_functions/Task_Control/Task%20Control.htm
http://www.robotc.net/wiki/Multitasking_tips

From RobotC.net:

"Up to ten tasks can execute concurrently within a NXT user program. The ‘main’ or ‘primary’ task is automatically started when a user
program is run. Execution of other tasks can be started and stopped with the ‘StartTask’ and ‘StopTask’ functions. The NXT will share CPU
execution time among various tasks by giving each task a “time slice” where it will execute a group of instructions.
Each task can be assigned a priority from 0 to 255. The NXT scheduler gives execution time to the highest priority task that is waiting
to run. A round robin scheduling scheme is used when there are multiple tasks ready to run all with the highest priority.
Lower priority tasks will not execute until there are no tasks of higher priority that are ready to run.

A task that is waiting for a time period to expire is not ready to run.
Once the time period has expired it will again become ready to run. Waiting tasks do not consume any CPU cycles."

*/
//Testing a change

#include "JoystickDriver.c"

bool flinging = false;

task fling(){

  nMotorEncoder[motorA] = 0;

  while(nMotorEncoder[motorA] < 720){
    motor[motorA] = 50;
  }

  wait1Msec(2500);
}


task beep(){
  while(true){
     if(joy1Btn(8) == 1){
       PlaySound(soundBeepBeep);
       wait1Msec(500);
    }
    endTimeSlice(); //makes way for other tasks to run; ends its allotted "time slice"
  }
}

task main()
{
  int threshold = 20;             /* Int 'threshold' will allow us to ignore low       */
  StartTask(beep);                /* readings that keep our robot in perpetual motion. */

  while(true)                            // Infinite loop:
  {

    if(joy1Btn(5) == 1 && !flinging){

    if(!flinging){
         flinging=true;
         StartTask(fling);
      }


    }

    if(joy1Btn(6) == 1){
      StopAllTasks();
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    getJoystickSettings(joystick);
    if(abs(joystick.joy1_y2) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[motorB] = joystick.joy1_y2;         // Motor B is assigned a power level equal to the right analog stick's Y-axis reading.
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[motorB] = 0;                        // Motor B is stopped with a power level of 0.
    }


    if(abs(joystick.joy1_y1) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[motorC] = joystick.joy1_y1;         // Motor C is assigned a power level equal to the left analog stick's Y-axis reading.
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[motorC] = 0;                        // Motor C is stopped with a power level of 0.
    }
  }
}
