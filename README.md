# CES-Device

Medical device

## Purpose

The CES Medical device is a device used to send mild forms of electrical stimulation to the brain. This is a simulation of said device in which multiple users can create, manage, and start sessions where different frequencies of electrical stimulation is sent to the brain via 2 connecting wires.

## Authors

Danniel Kim (101193872), 
Yacin Ismail (),
Duc Tran (),
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
(not sure what is the correct order between commit and push)
First, ensure you are at the branch that you want
git add .
git commit
git push

## Contributions

Danniel Kim
- Implemented...

Yacin Ismail
- 

Duc Tran
- 

Ben Conabree
- UML
- State diagrams
- base UI
- 
- 
