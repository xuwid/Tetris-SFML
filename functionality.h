/*HAMZA NAVEED
 22i-0961
 CS (A)
 FINAL PROJECT
*/
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum ,int &n,int &color2,int &n3,int colorArray[7],int randomarray[7],int shadow[][2])
{
    if (timer>delay)
    {
        for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        //random=1+rand()%7;
       	//if(random==0){
        for (int i=0;i<1;i++)
        {
            bombpoint_2[i][1]=bombpoint_1[i][1];
 			bombpoint_1[i][1]+=1;          
                               //How much units downward
        }
        //}
        	
        for(int i=0;i<4;i++)					//SHADOW is storing  the values 
		{
			shadow[i][0]=point_1[i][0];
			shadow[i][1]=point_1[i][1];
			
		}
        if (!anamoly())
        {
        	for(int i=0;i<4;i++)
        	{
        		gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
        	}
        	static int counter=0;
        	colorNum=colorArray[counter];
        	color2=colorArray[counter+1];
        	bombcolor=1+rand()%7;
            n=randomarray[counter];
            n3=randomarray[counter+1];
            if(counter==6)
        	{
        		color2=1;
        			
        	}	
            if(counter>=6)
            {
            	counter=-1;
            }	
            //--- Un-Comment this Part When You Make BLOCKS array---//
 				if(delay==0)
 				delay=0.4;           
                for (int i=0;i<4;i++)
                {
                    point_1[i][0] = BLOCKS[n][i]%2;//point1 is initiallized with each of the block
                    point_1[i][1] = BLOCKS[n][i]/2;//
        
                }
                for (int i=0;i<1;i++)
                {
                	
                   bombpoint_1[i][1] = bombed;
                }
               counter++;
        }
        timer=0;					//timer becomes zero at the end ,so it keeps falling
    }
 }

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
////*****CODE For MOVING *****///////
void motion(int& delta_x)
{
	for(int i=0;i<4;i++) //First of all point1 is copied in point2 and ,then value of delta_x is added in point_1 
	{
		point_2[i][0]=point_1[i][0];
		point_2[i][1]=point_1[i][1];
		if(delta_x==1)
		point_1[i][0]=1+point_1[i][0];
		if(delta_x==-1)
		point_1[i][0]=-1+point_1[i][0];	
	}
	if(!anamoly())
	{
		
		for(int i=0;i<4;i++)
						//IF ANAMOLY BECOMES False VALUE OF POINT_1 ARE REPLACED WITH POINT_2 (WITH THE VALUES WHEN ANANOMLY 
									// WAS NOT FALSE
		{
			point_1[i][0]=point_2[i][0];
			point_1[i][1]=point_2[i][1];
		}
	}
}
////*****Code ended  here******///////
/////***FOR ROTATION***///////////////
void rotation(bool& rotate,int n)
{
	if(n!=4){						//function will not work when n=4
	switch (rotate)
	{
	case 1 :	
		for(int i=0;i<4;i++)
		{
			int xaxis=point_1[i][1]-point_1[1][1];
			int yaxis=point_1[i][0]-point_1[1][0];
			point_1[i][0]=point_1[1][0]-xaxis;
			point_1[i][1]=point_1[1][1]+yaxiss;
		}
		if(!anamoly())				//IF ANAMOLY BECOMES False VALUE OF POINT_1 ARE REPLACED WITH POINT_2 (WITH THE VALUES WHEN ANANOMLY 
									// WAS NOT FALSE)
		{								
			for(int i=0;i<4;i++)
			{
				point_1[i][1]=point_2[i][1];
				point_1[i][0]=point_2[i][0];
			}
		}
	break;
	}
	}
}
/////***Ended Rotation***//////////////////
/////****Checking lines*****/////////////////
void checkline(int &sCore)
{
	sCore=0;							//sCore here means that in one time, how many rows are completed
	int m=M-1;
	for(int i=M-1;i>0;i--)
	{
		int counter=0;	
		for(int j=0;j<N;j++)
		{
			if(gameGrid[i][j])
			{	
					counter=counter+1;
			}
			gameGrid[m][j]=gameGrid[i][j];			// The values of upper row is replaced with the values of lower row
		}

		if(counter<N)
		{
			
			m--;
		}
		else 
		{
			sCore+=1;			//sCore is being calculated
		}	
	}
}
//////***Ended Checking lines***///////////
//////****BLOCKS DROPPING****///////////
void dropblock(bool & drop,float &delay)
{
	
	if (drop){				//WHEN THIS FUNCTION IS CALLED DELAY BECOMES ZERO UNTIL THE NEXT BLOCK ARRIVES
		delay=0;	
	
	}
}

//////****BLOCKS DROPPING ENDED****///////////
/////*****GAME OVER*****//////
void gameOver(bool gameover)
{
	if(gameover)
	{
		sf:: RenderWindow window(sf::VideoMode(320, 480), title);
		sf::Texture obj2;
        sf::Sprite background(obj2);
        obj2.loadFromFile("img/background.png");       
        while (window.isOpen()){
        sf::Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == sf::Event::Closed)                   //If cross/close is clicked/pressed
               { 
               window.close();
               }
               	
        		sf::Font font;
        		
        		if (!font.loadFromFile("Calibri.ttf"))
					{
  						  // error...
						}
				sf::Text text;

				text.setFont(font);
			// set the string to display
			text.setString("\n\n\n   GameOver :(");
			// set the character size
			text.setCharacterSize(48); // in pixels, not points!
			// set the color
			text.setFillColor(sf::Color::Red);
			// set the text style
			text.setStyle(sf::Text::Bold);
			// inside the main loop, between window.clear() and window.display()
			window.clear(sf::Color::Blue);
			window.draw(background);
			window.draw(text);
			window.display();
	}
	}
	
}
}
///*** GAME OVER ***///
///*** Storing score ***///
void sTorescore(int sCore,int& score)
{
	if(sCore==1)			
	{
		score=score+10;
	}
	else if(sCore==2)					//DIFFERNET SCORES ARE GIVEN TO THE USER IF THEY COMPLETE DIFFERNT NUMBER OF ROWS AT ONCE								
	{
		score=score+30;
	}
	else if(sCore==3)
	{
		score=score+60;
	}
	else if(sCore==4)
	{
		score=score+100;
	}
	
}
///*** Storing score ended ***///
///*** SHADOW FUNCTION  ***///
void shadowfunction(int shadow[][2])
{
				
		if(shadowanamoly())
		{
	for(int i=0;i<4;i++)							//+1 is added in the y axis of the shadow array until the shadowanamoly is true
		{
			shadow[i][1]=shadow[i][1]+1;
		}
	}
	if(!shadowanamoly())
	 {	
	 	for(int i=0;i<4;i++)
	 	shadow[i][1]=shadow[i][1]-1;		 
	 }
	 
	
}
	 		
///*** SHADOW FUNCTION ended ***///

///*** SHADOW FUNCTION ended ***///
void bombcondition1()
{
	bool flag=false;
	for(int i=0;i<10;i++)
	if (bombed==gameGrid[19][i]){
		flag=true;
	}
	if(flag==true)
	{
		
	}
	else
	flag=false;
}
///*** YOUR FUNCTIONS END HERE ***///
void bombcondition2(int &colorNum)
{
	for(int i=0;i<4;i++)
	if (bombpoint_1[0][0]==gameGrid[point_2[i][1]][point_2[i][0]])
	{
		
	}
}
///*** YOUR FUNCTIONS END HERE ***///

/////////////////////////////////////

