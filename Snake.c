#include<cs50.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define _head 64 // 22 is the head of snake in ASKI
#define _hight 15 // The Higth of The Screen
#define _length 30 // The length of The Screen
#define _BodyHersontal 45 // The body node in ASKY when its Hersontal
#define _BodyVertecal 124 // The body node in ASKY when its Vertecal
#define _eatFormat1 4  // The First Format of The eat in ASKI
#define _eatFormat2 42 // The Socund Format of The eat in ASKI

#define _UP 87        //
#define _up 119       // The leters
#define _down 115     //
#define _DOWN 83      // for The input
#define _RIGHT 68     //
#define _right 100    //
#define _left 97      // in ASKI
#define _LEFT 65      //

#define _eazy 100
#define _normal 50
#define _hard 0


//------------------------------------------------
	// Snake Stuff
	typedef struct node
	 {
	   int x_pos;
	   int y_pos;
	   int body; // the body Format of the Snake
	   struct node* next;
 	  }node;
	node* root = NULL ;
	void create_node(node** root,int x , int y , int body);
	void DeleteSnake(node* root); // Free the memory
	bool serch(node* root,int x , int y,int* body);
	node* Temp = NULL ; // variable used in Delete The Snake
//------------------------------------------------

// **************************************************
    // Functions :
void clear();
void drow();
void bottom();//Function to set the bottom of the screen
void up();    //Function to set the up of the screen
void change_pos_head(); // Function to move the Snake in Another plase
void change_First_node(); // Function to move the Snake First Body node to Flow The head
void change_pos_body(node* root); // Function to move the Snake Body to Flow The head
void Random_palse_for_eat(); // set a Random plase to eat
void change_eat_format(); // lettel Function to change eat format
void snake_eat(); // This Function Runs if The snake eat
void snake_die(); // Function checks if The Snake die .. and Stop The Game if so
void welcom(); // Fuction do all stuff befor The Game start
void BigS();
	// Tread Functions
DWORD WINAPI moveInput(); // Take Input from The User
DWORD WINAPI moveB();     // Do all The Game Stuff
// *************************************************************
	// Variables
bool First_game = true ; // Bolean to Fix Bug That The Thread Run Twice
bool Move = false ; // boolean To check if the User Press a Key
node head ={20,12} ;
node First_node ={19,12,_BodyHersontal} ; // First node in the body After The head
node eat;
int eat_b =0 ; // intger To change The eat Format ^_^
node* Snake = NULL ;
node S_part ; // node use to help move Snake Parts to new location
bool Exit = true; // Bolean Used To Exit From The Infintef Loop of The game
int S_dirc = 1; // intger to deside direction of the snake head .. 0 is up .. 1 is right .. 2 is down .. 3 is Left
int B_dirc = 1;  // intger to deside direction of First node in the Snake .. like the past one
long score = 0; //The score of The Game ^_^
int level ;
string level_s;

//********************************************************************


int main()
{
	system("color 1f");
	BigS();



	create_node(&Snake,18,12,_BodyHersontal);
	create_node(&Snake,17,12,_BodyHersontal);
	Random_palse_for_eat();

	HANDLE thread = CreateThread(NULL, 0, moveInput , NULL, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, moveB , NULL, 0, NULL);

	moveInput();
	moveB();

	DeleteSnake(Snake);
	Sleep(200);
	clear();
	printf("I Hope That You Enjoyed .. !! ^_^ \n");
	printf("Press Any Key To Exit.\n");
	getch();

}//End of the Main Function

void drow()
{
	for(int i=0;i<_hight;i++)//the hight Loop
	   {
		   for(int j=0;j<_length;j++)//spases Loop
		      {
                int b ;
                if(eat.x_pos == j && eat.y_pos == i )
                	printf("%c",eat.body);
                else if(head.x_pos == j && head.y_pos == i )
                   printf("%c",_head);
                else if(First_node.x_pos == j && First_node.y_pos == i )
                   printf("%c",First_node.body);
                else if(serch (Snake,j,i,&b))
				   printf("%c",b);
				else
				   printf(" ");
			  }

		   printf("\n");
	   }//End of the hight Loop

}//End of the drow Function

DWORD WINAPI moveB()
{
	if(!First_game)
	  return 0;
	for(;;)
		{
			clear();
			up();
			drow();
			bottom();
			Sleep(level);
			change_pos_head();
			change_eat_format();
			if(head.x_pos == eat.x_pos && head.y_pos == eat.y_pos)
				snake_eat();
			snake_die();
			if(!Exit)
				break;
		}
	First_game = false;
	return 0;
}
void snake_die()
{
	int b; // do nothing .. Just to pass it To Function 'Serch' above
	if(serch(Snake,head.x_pos,head.y_pos,&b))
	  {
		Exit = false;
		clear();
		up();
		drow();
		bottom();
	  }

}
void snake_eat()
{
	Random_palse_for_eat();
	create_node(&Snake,S_part.x_pos,S_part.y_pos,S_part.body);
	score +=5 ;
}
void welcom()
{
	printf("\t\t Welcome To Snake Game ... ^_^ \n");
	printf("Choose a Level .. \n");
	printf("          Easy   Enter : E \n");
	printf("          Normal Enter : N \n");
	printf("          Hard   Enter : H \n");
	int n = getch();
	if(n == 'e'||n=='E')
	   {
			level = _eazy;
			level_s = "Eazy";
		}
	else if(n == 'n'||n=='N')
		{
			level = _normal;
			level_s = "Normal";
		}
	else if(n == 'h'||n=='H')
		{
			level = _hard;
			level_s = "Hard";
		}
	else
	{
		clear();
		welcom();
	}
}
void Random_palse_for_eat()
{
	int m ; // do nothing .. Just to pass it To Function 'Serch' above
	srand(time(NULL));
	eat.x_pos = rand()%_length ;
	srand (time(NULL));
	eat.y_pos = rand()%_hight ;
	if(head.x_pos == eat.x_pos && head.y_pos == eat.y_pos )
		Random_palse_for_eat();
	else if(First_node.x_pos == eat.x_pos && First_node.y_pos == eat.y_pos )
    	Random_palse_for_eat();
    else if(serch (Snake,eat.x_pos,eat.y_pos,&m))
    	Random_palse_for_eat();
}
void change_eat_format()
{
	if(level_s == "Eazy")
	   {
	    	if(eat_b == 0)
	    	   {
	    			eat.body = _eatFormat1 ;
	    			eat_b++;
				}
	    	else
	    		{
	    			eat.body = _eatFormat2 ;
	    			eat_b = 0;
				}
		}
	else if(level_s == "Normal")
	    {
	  		if(eat_b == 0)
	    	   {
	    			eat.body = _eatFormat1 ;
			   }
			else if(eat_b == 2)
	    		{
	    			eat.body = _eatFormat2 ;
	    			eat_b = -2;
				}
			eat_b++;
		}
	else
	    {
			if(eat_b == 0)
		        {
					eat.body = _eatFormat1 ;
			    }
			else if(eat_b == 4)
			    {
		   			eat.body = _eatFormat2 ;
	    			eat_b = -4;
	    		}
			eat_b++;

		}
}
void change_pos_head()
{
	int temp;
	bool temp_bool = false ;
	S_part.x_pos = head.x_pos;
	S_part.y_pos = head.y_pos;
	if(Move)
	  {
		temp = S_dirc;
		Move = false;
		temp_bool = true;
	  }
	if(S_dirc == 0)
	  {
		head.y_pos--;
		if(head.y_pos < 0)
		  head.y_pos = _hight -1;
	  }
	else if(S_dirc == 1)
	  {
		head.x_pos++;
		if(head.x_pos >= _length)
		   head.x_pos = 0;
	  }
	else if(S_dirc == 2)
	  {
		head.y_pos++;
		if(head.y_pos >= _hight)
		  head.y_pos = 0;
	  }
	else if(S_dirc == 3)
	  {
		head.x_pos--;
		if(head.x_pos < 0)
		   head.x_pos = _length-1 ;
	  }

	change_First_node();

    if(temp_bool)
    	B_dirc = temp;
}
void change_First_node()
{
	//swap
	int temp = S_part.x_pos ;
	S_part.x_pos = First_node.x_pos;
	First_node.x_pos = temp ;
	//swap
	temp = S_part.y_pos ;
	S_part.y_pos = First_node.y_pos;
	First_node.y_pos = temp;
	S_part.body = First_node.body;
	if(B_dirc == 1 ||B_dirc == 3)
		First_node.body = _BodyHersontal;
	else
		First_node.body = _BodyVertecal;

	change_pos_body(Snake);

}
void change_pos_body(node* root)
{
	if(root == NULL)
	     return ;
	//swap
	int temp = S_part.x_pos ;
	S_part.x_pos = root->x_pos;
	root->x_pos = temp;
	//swap
	temp = S_part.y_pos ;
	S_part.y_pos = root->y_pos;
	root->y_pos = temp;
	//swap
	temp = S_part.body ;
	S_part.body = root->body;
	root->body = temp;

    change_pos_body(root->next);
}

DWORD WINAPI moveInput()
{
	if(!First_game)
	  return 0;
	while(Exit)
	{
		int n = getch();
		if(( n == _up || n== _UP || n== _down|| n== _DOWN) && (S_dirc != 0 && S_dirc != 2 ))
		  {
			Move = true ;
			if( n == _UP|| n == _up)
				S_dirc = 0;
			else
				S_dirc = 2;

		  }
		else if((n == _left || n== _LEFT ||n== _RIGHT || n == _right) && (S_dirc != 3 && S_dirc != 1 ))
		  {
			Move = true ;
			if( n == _LEFT || n == _left )
				S_dirc = 3;
			else
				S_dirc = 1;
		  }
		else if(n == 48)
		  {
			Exit = false;
			First_game = false;
			Sleep(20);
			clear();

	  	  }
	}
	return 0;
}

void bottom()
{
 	for(int i=0;i<_length;++i)
 	   {
		 printf("*");
	   }
	printf("\n");
}

void up()
{
	printf("Press 0 To Exit ..\n");
	printf("Level Mode : %s ..\n",level_s);
	printf("Keys:   W : Up , S : Down , D : Right , A : Left\n");
	printf("Enjoy .. ^_^ \n");
	printf("score : %d \n",score);
	for(int i=0;i<_length;++i)
	 	{
		 printf("*");
	    }
	printf("\n");
}

void clear()
{
	system("cls");
}

// ************************************************************************************
  // Snake Stuff

void create_node(node** root,int x , int y , int body)
{
  if((*root) == NULL)
    {
     *root = malloc (sizeof(node));
     if(*root == NULL)
       {
     	   printf("Erorr .. no memory available");
     	   return;
	   }
     (*root)-> x_pos = x ;
     (*root)-> y_pos = y ;
     (*root)-> body = body;
     (*root)-> next=NULL;
    }
  else
    create_node( &((*root)->next), x ,y ,body);
}

void DeleteSnake(node* root)
{
	if(Temp != NULL)
	  {
		  free(Temp);
		  Temp = NULL ;
  	  }
	if(root == NULL)
	  {
	     return;
	  }
	if(root->next == NULL)
	  {
	       free(root);
	       return;
	  }
	else
	  {
  		 Temp = root;
  		 DeleteSnake(root->next);
  	  }
}

bool serch (node* root,int x , int y,int* body)
{
  if(root == NULL)
     return false;
  else if(root->x_pos == x && root->y_pos == y)
          {
      	    *body = root->body;
      	    return true;
	      }
    else
         return serch (root->next,x ,y, body);
}
//******************************************
  // Somting Cooool ... ^ _ ^
void BigS()
{
	int n =75;
	   printf("                                             \n");Sleep(n);
	   printf("                               *               \n");Sleep(n);
	   printf("                           * * *              \n");Sleep(n);
	   printf("                        *      *                   \n");Sleep(n);
	   printf("                      *                          \n");Sleep(n);
	   printf("                     *                           \n");Sleep(n);
	   printf("                     *                           \n");Sleep(n);
	   printf("                      *                           \n");Sleep(n);
	   printf("                         *                       \n");Sleep(n);
	   printf("                            *                  \n");Sleep(n);
	   printf("                               *              \n");Sleep(n);
	   printf("                                *             \n");Sleep(n);
	   printf("                                *           \n");Sleep(n);
	   printf("                               *            \n");Sleep(n);
	   printf("                             *              \n");Sleep(n);
	   printf("                   *      *                         \n");Sleep(n);
	   printf("                   * * *                          \n");Sleep(n);
       printf("                   *                              \n");Sleep(n);

   Sleep(320);

   clear();
   welcom();

}