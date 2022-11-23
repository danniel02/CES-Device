# CES-Device

Medical device


# Git


## Accessing Git from VM Terminal
First we need to create a personal token:
Settings -> Dev Settings -> Personal Access Token -> Token (classisc) -> Generate New Token (classic) -> check all -> copy the token (also save somewhere)

Then, in VM's terminal, do:
git clone https://github.com/danniel02/CES-Device <insert_token_here>


## Add repo to local config
git remote add 3004-project https://github.com/danniel02/CES-Device.git

## Navigate to a branch from terminal
Please note that this is on top of my head, I didn't save the exact command:
git checkout <branch_name> 

## Show all file
git ls-tree -r <branch_name>

## Pull 
git pull 3004-project
