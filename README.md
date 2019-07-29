# Robot-planning
&nbsp;The implementation for a deposit of boxes with robots which move the boxes between them. The robots take commands from a person<br>
  &nbsp;The deposit is defined by a configuration of map[LIN][COL], there are N robots which are responsible for moving the boxes. map[x][y] represents the number of boxes from the cell of coordinates x, y in deposit. The commands given by that person are:<br>
    &nbsp;ADD_GET_BOX RobotId x y NrBoxes Priority<br>
    &nbsp;ADD_DROP_BOX RobotId x y NrBoxes Priority<br>
    &nbsp;EXECUTE RobotId<br>
    &nbsp;PRINT_COMMANDS RobotId<br>
    &nbsp;LAST_EXECUTED_COMMAND<br>
   &nbsp;UNDO<br>
    &nbsp;HOW_MUCH_TIME<br>
    &nbsp;HOW_MANY_BOXES RobotId<br>
  &nbsp;The commands of the type "GET" and "DROP" are kept by the robot in a queue and execute the first of them from the queue when they receive the command "EXECUTE". The commands of the type "GET" and "DROP" have priorities and because of them the robots can put a command at the beginning of the queue or at the end of it.<br>
  &nbsp;The command ADD_GET_BOX take the "NrBoxes" boxes from the cell of coords (x, y) (the robot puts the boxes in his hands)<br>
  &nbsp;The command ADD_DROP_BOX take the "NrBoxes" boxes from his hands and put them in the cell of coords (x, y) (the robot take the boxes from his hands)<br>
  &nbsp;The command PRINT_COMMANDS print the commands from the queue of the "RobotId"<br>
  &nbsp;The command LAST_EXECUTED_COMMAND print the RobotId which executed the last command, also print the command and the number of executed boxes (ex: if in the cell was 5 boxes, and the command had 10 boxes to get, the robot will get 5)
  &nbsp;The command UNDO delet the effect of the last executed command<br>
  &nbsp;The command HOW_MUCH_TIME print an integer which represent how many commands did LAST_EXECUTED_COMMAND wait until execution<br>
  &nbsp;The command HOW_MANY_BOXES print how many boxes has the robot in hands in that moment
  
  
