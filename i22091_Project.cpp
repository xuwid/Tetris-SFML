/*HAMZA NAVEED
 22i-0961
 CS (A)
 FINAL PROJECT
*/
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1,obj2,obj3,obj4,obj5,obj6;
 	Text text;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/tiles.png");
    obj5.loadFromFile("img/index.png");
    obj6.loadFromFile("img/tiles.png");
    Sprite sprite(obj1),background(obj2), frame(obj3),nextblock(obj4),shadoww(obj5),bomb(obj6);
    int delta_x=0; int colorNum=1;int n=0;int color2=1;int n3;
    float timer=0, delay=0.4;
    bool rotate=0; bool pause=false; bool drop=false;bool gameover=false; 
    int sCore=0;int score=0;
    int colorArray[]={1,2,3,4,5,6,7};
    int randomarray[]={0,1,2,3,4,5,6};
    Clock clock;
    while (window.isOpen()){
    	if(delay!=0)
    	{
    		delay=0.4;
      	}
      	//---RESETTING SOME MAJOR VARIBLEST THE START OF THE LOOP---//
       	gameover=0;
    	delta_x=0;
    	rotate=0;
    	drop=0;
    	sCore=0;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        bombtimer+=time;
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                     rotate=true;	                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x =-1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;
                else if (e.key.code == Keyboard::H)     	//WHEN PRESSED H THE GAME BECOME PAUSED
                {	
                	pause=true;
                }	
                else if (e.key.code == Keyboard::P)
                {
                 	pause=false;						//WHEN PRESSED P THE GAME WILL BECOME UN PAUSED
                 	window.clear(Color::Black);
                }
                else if (e.key.code == Keyboard::Space)   //BY PRESSING SPACE THE BOOL DROP WILLL BECOME TRUE
				{
					drop=true;
				}
                                         
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.1;  					//HOW MANY UNITS THE BLOCK WILL MOVE DOWN WHEN PREESED THE DOWN KEY
            								//If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
            
        for (int i=0;i<4;i++)//When the pieces touch the upper boundary of the grid the window closes and Gameover window is popped
      	{
        	if(gameGrid[point_1[i][1]][point_1[i][0]])
        	{	
        		window.close();
        		gameover=true;	
        	}
        
		}
      
     if(pause==0)    //A CONDITION TO PAUSE THE GAME 
     {                                    
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        
        
        
        ///-----------------------///
       
       //THIS FUNCTION IS RESPONSIBLE FOR FALLING THE PIECE OR THE BLOCK
       // IN THIS FUNCTION color2,n3,colorArray,randomarray are used for suggestion block
       //While shadow array is passed here so it can copy all the values of point_1
        fallingPiece(timer,delay,colorNum,n,color2,n3,colorArray,randomarray,shadow);
       //Colornum is the color of the blocks
       //And n is the number of the block 
       ///-----------------------///
       
       
       
       
       ///-----------------------///
        
        rotation(rotate,n);		//THIS FUNCTION IS TAKING BOOL ROATATE AS INPUT ,AND THEN BY FINDING THE AXIS OF ROTATION OF THE
        						// BLOCK IT REPLACES VALUE OF X AXIS AND Y AXIS
        						// n IS PASSED IN THIS FUNCTION AS TO MAKE THE SQUARE BLOCK NOT ROTATE
        
       ///-----------------------///
       
       
       ///-----------------------///
        
        motion(delta_x);//THIS FUNCTION IS CHANING THE X-AXIS OF THE POINT_1 BY ADDING VALUE OF DELTA_X TO IT
        				// -1 OR +1 WILL BE ADDED DEPENDING ON WHICH BUTTON IS PRESSED
      
       ///-----------------------///
      
       
       
        ///-----------------------///
       							//THIS FUNCTION IS CHECKING WHETHER LINE IS COMPLETED AND HOW MANY OF THEM
   		checkline(sCore);			// ARE COMPLETED ONCE BY INPUTIING INT sCORE, IT ALSO CHANGING VALUE WHEN COMPLETED 
        							//OF THE UPPER ROW 	 WITH TH LOWER ROW
        ///-----------------------///
      
      
        
        ///-----------------------///
        dropblock(drop,delay);	//THIS FUNCTION IS TAKING THE BOOL DROP AND THE FLOAT DELAY AS INPUT,DROP IS ONLY ACTIVATED 
        						//WHEN YOU PRESS 'SPACE',HENCE THE DELAY TIMES BECOMES ZERO UNTIL THE NEXT BLOCK IS GENERATED
        ///-----------------------///
        
        
        
        ///-----------------------///
        gameOver(gameover);			//THIS FUNCTION IS TAKING THE BOOL gameover as input and it will display the gameover screen
        ///-----------------------///
        
        
        
        ///-----------------------///
        sTorescore(sCore,score);//This function will take sCOre(how many lines are completed in one time)
        						// integer and it will update the value of score in the game
        ///-----------------------///
        
        
        
        
        //THIS FUNCTION BELOW WILL CHANGE THE VALUE OF SHADOW ARRAY AS 
        ///IN THE FALLING PIECE THE VALUE OF SHADOW FUNCTION IS INTIALIZED TO BE SAME AS THE POINT_1 
        shadowfunction(shadow);		//HERE +1 will be added in the shadow shadow reaches the ground or until the anamoly is false
       ///-----------------------///
        
        
        //THIS FUNCTION WILL CHECK THE CONDITITION THAT THE BOMB DOES NOT DROP ON A BLOCK BUT RATHER ON THE COLOMN 19  
        bombcondition1();
       ///-----------------------///
       
   
   //Example: fallingPiece() function is called here
  ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
	}
		
		//Displaying Score in the Main Window
		///-----------------------///
		sf::Font myfont;
        if (!myfont.loadFromFile("Calibri.ttf"))
        {
 	         std::cerr << "error";
   		}
		std::ostringstream oss;
    	oss << score;
		sf::Text mytext;
    	mytext.setFont(myfont);
    	mytext.setString(oss.str());
    	mytext.setPosition(260, 260);
    	///--------ENDED DISPLAYING SCORE--------------///
    	
    	
    	
    	
    	
    	//-------Displaying the word score-----------//
    	///-----------------------///
    	sf::Font fontt;
        if (!fontt.loadFromFile("Calibri.ttf"))
         {
        	   std::cerr << "error";
   		  }
   	 	sf::Text textt;
   		textt.setFont(fontt);
   		text.setCharacterSize(24); // in pixels, not points!
    	textt.setString("Score");
    	textt.setPosition(240, 230);
    	///----ENDED DISPLAYING THE WORD SCORE------------------///




        window.clear(Color::Black);
        window.draw(background);
         for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }  
        ///---------DISPLAYING  SHADOW--------------///
        for (int i=0; i<4; i++){
            shadoww.setTextureRect(IntRect(colorNum*18,0,18,18));
            shadoww.setPosition(shadow[i][0]*18,shadow[i][1]*18);
            shadoww.move(28,31);
            
           	window.draw(shadoww);
          }
          ///It has the same coorindates as the point_1 or the orignal block
           ///---------ENDED DISPLAYING  SHADOW--------------///
            ///-----------------------///
            
            
            
            
         ///---------DISPLAYING  ORIGNAL BLOCK--------------///
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
           ///--------- ENDED DISPLAYING  SHADOW--------------///
        
        
		 ///---------DISPLAYING  NEXT SUGGESTION BLOCK--------------///        
         for (int i=0; i<4; i++){
            nextblock.setTextureRect(IntRect(color2*18,0,18,18));
            nextblock.setPosition(((BLOCKS[n3][i]%2)*18)+250,((BLOCKS[n3][i]/2)*18)+160);
            window.draw(nextblock);
          }
           ///-----------------------///
          
          
          	 ///---------DISPLAYING  BOMB--------------///
          	if(random==0){
            bomb.setTextureRect(IntRect(bombcolor*18,0,18,18));
            bomb.setPosition(bombpoint_1[0][0]*18,bombpoint_1[0][1]*18);
            bomb.move(28,31);
            window.draw(bomb);
          	}
         
        //---The Final on Which Everything is Drawn Over is Loaded---/
          window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---/
        window.draw(textt);
        window.draw(mytext);
        window.display();
    }
    return 0;
}
