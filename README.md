# CES-Device

Medical device

## Purpose

The CES Medical device is a device used to send mild forms of electrical stimulation to the brain. This is a simulation of said device in which multiple users can create, manage, and start sessions where different frequencies of electrical stimulation is sent to the brain via 2 connecting wires.

## Team

Team 55

## Authors

Danniel Kim (101193872), 
Yacin Ismail (101080508),
Duc Tran (101158742),
Ben Conabree (101150845),


# Git


## Accessing Git from VM Terminal
First we need to create a personal token:
Settings -> Dev Settings -> Personal Access Token -> Token (classisc) -> Generate New Token (classic) -> check all -> copy the token (also save somewhere)

Then, in VM's terminal, do:
git clone https://github.com/danniel02/CES-Device.git 

Then, enter github name

Then, enter token as password


## Add repo to local config
git remote add 3004-project https://github.com/danniel02/CES-Device.git

## Navigate to a branch from terminal
Please note that this is on top of my head, I didn't save the exact command:
git checkout <branch_name> 

## Show all file
git ls-tree -r <branch_name>

## Pull 
git pull 3004-project

## Push
First, ensure you are at the branch that you want

git add .

git commit

git push

## Compilation and Execution
- Download the zip file and unzip.
- Within the folder, run the .pro file with QtCreator.
- From there, the project will build and run.

## Running the Program
Once within the program:
- To turn on the device press the power button.
- To navigate the menu use the provided buttons on the interface
- To see battery level, refer top left.
- To change the battery level use the scrollwheel on the right.
- To change the intensity use the bar above the interface.
- To check/add connectivity (connection of the device to the user's ears), use the drop down menu on the right labelled connection test.
- To view individual connectivity, refer to left and right con (L_CON and R_CON).
- To view the selected mode (frequency) of the session, refer to above the interface.
- To run tests, click the button on the bottom right.

### Source Files:
- main.cpp
- mainwindow.cpp
- menu.cpp
- user.cpp
- session.cpp

### Header Files:
- mainwindow.h
- menu.h
- user.h
- session.h

### Additional Files:
- Executables:
  - GuiEX.pro 
  - GuiEX.pro.user
- UI:
  - mainwindow.ui
- Other:
  - README.md (This readme file)
  - UML (UML diagram)
  - Files in Sequence-Diagrams (Sequence diagrams corresponding to use cases)
  - Use-Cases (Use cases of the program)
  - State Diagram
  - UIConcept (a diagram of the concept of how the main interface functions)

### Notes
- 5 users are implemented in the program:
  - Default
  - Danniel
  - Yacin
  - Duc
  - Ben
- Since this is a simulation, the admin functions/items serve as the in world equivalent (ie. set battery level serves as a charger)
- The recording of a session must be done while the session is undergoing
- The viewing of recorded sessions in Review Sessions are unique per user
