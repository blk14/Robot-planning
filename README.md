# Robot-planning
The implementation for a deposit of boxes with robots which move the boxes between them. The robots take commands from a person
  The deposit is defined by a configuration of map[LIN][COL], there are N robots which are responsible for moving the boxes. map[x][y] represents the number of boxes from the cell of coordinates x, y in deposit. The commands given by that person are:
    ADD_GET_BOX RobotId x y NrBoxes Priority
    ADD_DROP_BOX RobotId x y NrBoxes Priority
    EXECUTE RobotId
    PRINT_COMMANDS RobotId
    LAST_EXECUTED_COMMAND
    UNDO
    HOW_MUCH_TIME
    HOW_MANY_BOXES RobotId
  The commands of the type "GET" and "DROP" are kept by the robot in a queue and execute the first of them from the queue when they receive the command "EXECUTE". The commands of the type "GET" and "DROP" have priorities and because of them the robots can put a command at the beginning of the queue or at the end of it.
  The command ADD_GET_BOX take the "NrBoxes" boxes from the cell of coords (x, y) (the robot puts the boxes in his hands)
  The command ADD_DROP_BOX take the "NrBoxes" boxes from his hands and put them in the cell of coords (x, y) (the robot take the boxes from his hands)
  The command PRINT_COMMANDS print the commands from the queue of the "RobotId"
  The command LAST_EXECUTED_COMMAND print the RobotId which executed the last command, also print the command and the number of executed boxes (ex: if in the cell was 5 boxes, and the command had 10 boxes to get, the robot will get 5)
  The command UNDO delet the effect of the last executed command
  The command HOW_MUCH_TIME print an integer which represent how many commands did LAST_EXECUTED_COMMAND wait until execution
  The command HOW_MANY_BOXES print how many boxes has the robot in hands in that moment
  
  
  
  &nbsp; The implementation for a deposit <br> of boxes with robots which move the boxes between them. The robots take commands from a person.
                        &nbsp;The deposit is defined by a configuration of map[LIN][COL], there are N robots which are responsible for moving the boxes. Map[x][y] represents the number of boxes from the cell of coordinates x, y in deposit. They have to memorise all the commands until there is given an "EXECUTE" command and they have to execute the first command from the queue. The robots are able to recognise and answer to commands of dropping and getting (boxes), last executed command or how much a command have stayed in the queue
