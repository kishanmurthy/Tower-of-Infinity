# Tower-of-Infinity
	Tower of Infinity is a 2D (two dimensions) single player game developed using Open GL and FreeGLUT library in C++. 
The game opens with a main menu page were the player has to choose two options namely ‘Play’ and ‘Controls’.
The player can choose an option by pressing ‘Enter’ on the keyboard or ‘Button A’ on the joystick controller. 
When the player chooses ‘Controls’ option a new page is created containing two tabs namely ‘Keyboard’ and ‘Controller’.
By default, ‘Keyboard’ tab will be opened. 
The player can switch between ‘Keyboard’ and ‘Controller’ tabs by using ‘Arrow’ keys. 
These tabs contain all the actions and associated keys required to play the game.
The player can press ‘ESC’ key in keyboard or ‘B button’ in joystick controller to go back to the main menu page. 
When the player chooses ‘Play’ option the player can start playing the game. 
The player initially at the zeroth floor. 
The player has to jump floors one after the other to reach higher floors. 
The higher the floor reached by the player is directly proportional to the score achieved by him/her. 
There exists a speed at which the player has ascend the floors. 
If the player cannot ascend at the speed defined, then player will not be visible from the game window and the game is over. 
The game is also over when the player falls from multiple floors and cannot be seen in the game window. 
The speed at which player has to ascend floors is increased by 50% every time the player climbs 30 floors.
Hence the difficulty of the game increases as the player climbs floors. 
The game is designed such that floors are slippery and the player moves very fast.
The score card is displayed at the top right corner of the screen. 
The floor number is displayed for every 10 floors the player climbs. 
The floors appear to descend downwards as the player ascends floors in order to keep player in view. 
When the player gets out and the game is over, a window will pop up stating “Game Over!!!”. 
The player can press ‘ESC’ key in keyboard or ‘B button’ in joystick controller to go back to the main menu page.
The player can press ‘Q’ key in keyboard or ‘X’ button to quit the game.
