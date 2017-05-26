# minifB

## Overview
**minifB** is an implementation of the facebook friends **graph** data structure in C.
The following mini project successfully demonstrates the implementation of graph data structure using **struct** and **pointers** in C. It also applications of graphs in a real life scenario such as facebook.

## Install and Run
Clone repository and run main.exe

## Documentation

### PART I : Initial Boot Commands

1. SIGN UP
	- Create a new user account. No parameters taken.
	`>>> SIGN UP`

2. LOGIN AS [username]
	- Log In into an already existing account.
	- Parameter [username]
	`>>> LOGIN AS kbStudios`

3. LOGOUT
	- Log out from an existing account.
	`>>> LOGOUT`
  
### PART II : Add Commands
 
1. ADD POST|FRIEND
 
	- POST - Add a new status to the timeline.
	`>>> ADD STATUS` 
 
	- FRIEND [username] - Add a Friend to your list. 
	Accepts username of the friend as a parameter.
	`>>> ADD FRIEND kbStudios`

### PART III : Display Commands 
 
1. VIEW FRIENDLIST|TIMELINE|USERS
 
	- FRIENDLIST [Username] - View the list of all friends of a person 
	given by the username
	`>>> VIEW FRIENDLIST kbStudios`

	- TIMELINE - View the timeline of status posted by users. 
	`>>> VIEW TIMELINE`
	- USERS - View all the users signed up for miniFb
  `>>> VIEW USERS`

## PART IV : Additional Commands
1. CLS
	- clears the screen 
	`>>> CLS`

4. QUIT
	- Exit the program
	`>>> QUIT`
