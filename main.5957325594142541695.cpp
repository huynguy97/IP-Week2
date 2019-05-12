#include "Robot.h"
#include <vector>
#include <algorithm>
#include <stdio.h>
/*
	                                                          
	                                                      
	                                                                                  
	                                                                   
*/

//                                                                          

//                                                                                         

//                                                                                                      
void steps ( int no_of_steps )
{
    while (no_of_steps > 0)
    {
        step () ;
        no_of_steps-- ;
    }
}

//                                                             
void safe_put_ball ()
{
    if (!on_ball())
        put_ball () ;
}

//                                                                                                                           
void balls (int no_of_balls)
{
    while (no_of_balls > 0)
    {
        safe_put_ball () ;
        no_of_balls-- ;
        if (no_of_balls > 0)
            step () ;
    }
}

//                                                                         
void make_grandstand ()
{
    const int FIELD_WIDTH  = 5 + rand () % (WORLDWIDTH / 5) ;
    const int NO_OF_STAIRS = 1 + rand () % (WORLDHEIGHT / 4) ;
    place_walls (1, WORLDHEIGHT / 2, FIELD_WIDTH, true) ;
    for (int stair = 0 ; stair < NO_OF_STAIRS ; stair++)
    {
        place_walls (1+FIELD_WIDTH+stair, WORLDHEIGHT / 2 + stair, 1, false) ;
        place_walls (1+FIELD_WIDTH+stair, WORLDHEIGHT / 2 + stair+1,1,true) ;
    }
    place_walls (1+FIELD_WIDTH+NO_OF_STAIRS, WORLDHEIGHT / 2 + NO_OF_STAIRS,1,true) ;
}

//                                                                               
void make_path_with_balls ()
{
    //              
    std::vector<int> columns(4);
    std::vector<int> rows(4);
    //                                                                                               
    //                               
    bool valid = false;
    while (not valid){ //                                                
        //                        
        for (int i = 0;i<4;i++){
            columns[i] = 1+rand() % (WORLDWIDTH-2);
        }

        //                                             
        valid = true;
        for (int i = 0;i<4;i++){
            for (int j = i+1;j<4;j++){
                if (columns[j] >= columns[i]-1 and columns[j] <= columns[i]+1){
                    valid = false;
                }
            }
        }
    }
    valid = false;
    while (not valid){ //                                                
        //                     
        for (int i = 0;i<4;i++){
            rows[i] = 1+rand() % (WORLDHEIGHT-2);
        }
        //                                          
        valid = true;
        for (int i = 0;i<4;i++){
            for (int j = i+1;j<4;j++){
                if (rows[j] >= rows[i]-1 and rows[j] <= rows[i]+1){
                    valid = false;
                }
            }
        }
    }
    //                                             
    sort(columns.begin(),columns.end());
    sort(rows.begin(),rows.end());

    //                   
    place_balls(1,WORLDHEIGHT-2,columns[0]-1,true);
    place_balls(columns[0],rows[1],(WORLDHEIGHT-2)-rows[1],false);
    place_balls(columns[0],rows[1],columns[3]-columns[0],true);
    place_balls(columns[3],rows[1],rows[3]-rows[1],false);
    place_balls(columns[2],rows[3],columns[3]-columns[2],true);
    place_balls(columns[2],rows[0],rows[3]-rows[0],false);
    place_balls(columns[1],rows[0],columns[2]-columns[1],true);
    place_balls(columns[1],rows[0],rows[2]-rows[0],false);
}

void make_cave_wall (bool at_north_edge)
{
    const int MARGIN    = WORLDHEIGHT / 3 ;
    const int MAX_WIDTH = WORLDWIDTH / 10 ;

    for (int ix = 2; ix <= WORLDWIDTH-3; )
    {
        const int WIDTH = rand() % (std::min (MAX_WIDTH, WORLDWIDTH - ix - 2)) + 1 ;
        const int DY = rand() % MARGIN + 2 ;
        int y ;
        if (at_north_edge)
            y = DY ;
        else
            y = WORLDHEIGHT - DY - 1 ;
        place_walls (ix,y,WIDTH-1,true) ;
        ix += WIDTH ;
    }
}

void make_cave ()
{
    make_cave_wall (true) ;
    make_cave_wall (false) ;
}

int shamrock_length (int dimension, int margin)
{
    return (dimension / 4) - margin ;//                               
}

//                                                                                                                 
//                                                                           
void make_shamrock ()
{
    const int NO_OF_LEAVES = rand () % 4 + 1 ;
    const int MARGIN  = 4 ;
    const int MW = WORLDWIDTH / 2 ;
    const int MH = WORLDHEIGHT / 2 ;
    const int NW = shamrock_length (WORLDWIDTH, MARGIN) ;
    const int SW = shamrock_length (WORLDWIDTH, MARGIN) ;
    const int WW = shamrock_length (WORLDWIDTH, MARGIN) ;
    const int EW = shamrock_length (WORLDWIDTH, MARGIN) ;
    const int NH = shamrock_length (WORLDHEIGHT, MARGIN) ;
    const int SH = shamrock_length (WORLDHEIGHT, MARGIN) ;
    const int WH = shamrock_length (WORLDHEIGHT, MARGIN) ;
    const int EH = shamrock_length (WORLDHEIGHT, MARGIN) ;
    if (NO_OF_LEAVES != 2)
    {
        place_rectangle (MW-NW/2,MH+std::max(WH,EH)/2+MARGIN,NW,NH) ;
        place_walls (MW,MH,std::max(WH,EH)/2+MARGIN,false) ;
    }
    if (NO_OF_LEAVES != 1)
    {
        place_rectangle (MW-std::max(NW,SW)/2-MARGIN-WW,MH-WH/2,WW,WH) ;
        place_rectangle (MW+std::max(NW,SW)/2+MARGIN,   MH-EH/2,EW,EH) ;
    }
    if (NO_OF_LEAVES == 4)
        place_rectangle (MW-SW/2,MH-std::max(WH,EH)/2-MARGIN-SH,SW,SH) ;
    if (NO_OF_LEAVES != 1)
        place_walls (MW-std::max(NW,SW)/2-MARGIN,MH,std::max(NW,SW)+2*MARGIN,true) ;
    place_walls (MW,MH-std::max(WH,EH)/2-MARGIN,std::max(WH,EH)/2+MARGIN,false) ;
    if (NO_OF_LEAVES == 1)
        create_ball (MW-NW/2+rand () % NW,WORLDHEIGHT-2) ;
    else
        create_ball (MW-std::max(NW,SW)/2-MARGIN-WW+rand () % (WW+std::max(NW,SW)+EW+2*MARGIN),WORLDHEIGHT-2) ;
}

//                                                                          

//                                                                  
void turn_around ()
{
    turn_left() ;
    turn_left() ;
}

//                                                                           
void walk_to_wall ()
{
    while (!in_front_of_wall())
        step () ;
}

//                               

//                                              
//                                                                                                      
//                                           
void climb_one_step ()
{
    turn_left () ;
    step () ;
    turn_right () ;
    step () ;
}

//                                                
//                                                                                                      
//                                              
void climb_all_steps ()
{
   while (in_front_of_wall ())
      climb_one_step () ;
}

//                                                                    
//                                                      
//                                                                    
void have_a_seat ()
{
    step () ;
    step () ;
    turn_left () ;
    turn_left () ;
}

//                                                                                                       
//                                                                                                                                      
//                                                             
void charles_goes_to_his_seat ()
{
    walk_to_wall () ;
    climb_all_steps () ;
    have_a_seat () ;
}

//                                                                             
void walk_to_field ()
{
    turn_right () ;
    walk_to_wall () ;
    turn_left () ;
}

//                                                        
void rectangle ( int width, int height )
{
    balls ( width ) ;
    turn_right ( ) ;
    balls ( height ) ;
    turn_right ( ) ;
    balls ( width ) ;
    turn_right ( ) ;
    balls ( height ) ;
    turn_right ( ) ;
}

void art ()
{
    rectangle ( 3, 2 ) ;
    rectangle ( 5, 4 ) ;
    rectangle ( 7, 6 ) ;
}

//                                                                          

//                                                           

//                                                
//                                                    

//                                          

//                                                                       
void followBalls(){
    //                                            
    while (not in_front_of_wall() and on_ball()){
        step();
    }
    //                                
    if (not on_ball()){
        turn_around();
        step();
        turn_around();
    }
}

void findNextDir(int maxTurns){
    //                                                       
    while (not on_ball() and maxTurns>0){
        //                                            
        if (not in_front_of_wall()){
            //                                                                                
            step();
            if (on_ball()){
                turn_around();//               
                step();
                turn_around();
                put_ball();
            }
            else{
                turn_around();
                step();
                turn_around();
            }
        }
        maxTurns--;
        if (not on_ball()){
            turn_around();
        }
    }
}

void hansl_and_gretl ()
{
    //                                                                         
    //                                     
    while (on_ball()){
        followBalls();
        turn_right();
        get_ball();//                      
        findNextDir(2);
    }
    put_ball();//                                              
    while (not north()){
        turn_right();
    }
    turn_right();
    //                             
}

void make_stalactite_or_stalagmite(){
    turn_right();
    while(!in_front_of_wall()){
        //                                                                                  
        put_ball();
        step(); //            
    }
    put_ball(); //                                                   

    //                                                                               
    turn_around();
    walk_to_wall(); //               
    turn_right();

}

//                                                                       
//                                                                                                                  
void fill_cave_with_balls ()
{
    step();
    while(!in_front_of_wall()){
        //                                               
        make_stalactite_or_stalagmite();
        step();
    }
    //                                                                                                
    turn_right();
    walk_to_wall();
    turn_right();
}

//                                                                       
void cave ()
{
	//                                                                                                  
	fill_cave_with_balls () ;
	fill_cave_with_balls () ;
}

//                                                                       
void shamrock ()
{
    //                             
}

//                                                  
//                                                                          

void quick  () { rest(FAST_STEP_TIME); };
void normal () { rest(INITIAL_STEP_TIME); };
void slow   () { rest(SLOW_STEP_TIME); };
void very_slow () { rest(VERY_SLOW_STEP_TIME); };

void start_step ()
{
    store_world () ;
    try {step (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_turn_left ()
{
    store_world () ;
    try {turn_left (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_turn_right ()
{
    store_world () ;
    try {turn_right (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_put_ball ()
{
    store_world () ;
    try {put_ball (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_get_ball ()
{
    store_world () ;
    try {get_ball (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_watch_match ()
{
    reset () ;
    make_grandstand () ;                          //                      
    store_world () ;
    try {
        walk_to_field () ;
        charles_goes_to_his_seat(); }             //                                      
    catch (...) {}                                //                         
    retrieve_world () ;
    start_replay_for_timer () ;                   //                                                              
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_art ()
{
    reset () ;
    store_world () ;
    try {
        art(); }                                  //                        
    catch (...) {}                                //                         
    retrieve_world () ;
    start_replay_for_timer () ;                   //                                                              
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_hansl_and_gretl ()
{
    reset () ;
    make_path_with_balls () ;
    store_world () ;
    try {hansl_and_gretl ();}
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_cave ()
{
    reset () ;
    make_cave () ;
    store_world () ;
    try {cave ();}
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_shamrock ()
{
    reset () ;
    make_shamrock () ;
    store_world () ;
    try {shamrock (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer (FAST_STEP_TIME) ;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    Menu charles_menu ((char*)"Charles") ;
    charles_menu.add ((char*)"Reset", reset)
                .add ((char*)"Stop",  stop) ;

	Menu ch_menu ((char*)"Basic Charles Actions") ;
	ch_menu.add ((char*)"step ()", start_step)
	       .add ((char*)"turn_left ()", start_turn_left)
	       .add ((char*)"turn_right ()", start_turn_right)
	       .add ((char*)"put_ball ()", start_put_ball)
	       .add ((char*)"get_ball ()", start_get_ball);

	Menu l2_menu ((char*)"Examples Lecture 2");
	l2_menu.add ((char*)"Watch match", start_watch_match)
	       .add ((char*)"Art",start_art);

	Menu a2_menu ((char*)"Assignment 2");
	a2_menu.add ((char*)"Hansl and Gretl", start_hansl_and_gretl )
		   .add ((char*)"Cave", start_cave )
		   .add ((char*)"Bonus: follow shamrock...", start_shamrock );

	Menu sn_menu ((char*)"Velocity");
	sn_menu.add ((char*)"Quick", quick)
		   .add ((char*)"Normal",normal)
		   .add ((char*)"Slow",slow)
		   .add ((char*)"Very slow",very_slow);

	try
	{
		charles_world().Run (charles_menu,WINARGS(hInstance, hPrevInstance, szCmdLine, iCmdShow));
	}
	catch (IllegalAction thisIllegalAction )
	{
		thisIllegalAction.report ();
	}
	catch (...)
	{
		makeAlert ("Something went terribly wrong!");
	}

	return 0;
}

