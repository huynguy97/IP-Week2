#include "Robot.h"
/*
	                                                          
	                                                      
	                                                                                  
	                                                                   
*/

//                                                                          

//                                                                                

//                                                                               
void put_a_ball_somewhere ()
{
    const int LANE   = 1 + rand () % (WORLDHEIGHT - 2) ;
    const int STREET = 1 + rand () % (WORLDWIDTH  - 2) ;
    create_ball (STREET, LANE) ;
}

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
void make_string_with_balls ()
{
    place_balls (1,1,WORLDHEIGHT-3,false) ;
    place_balls (WORLDWIDTH-2,1,WORLDHEIGHT-3,false) ;
    place_balls (1,1,WORLDWIDTH-3,true) ;
    place_balls (1,WORLDHEIGHT-2,WORLDWIDTH-3,true) ;
}

//                                                                                        
void make_chaos_with_balls ()
{
    const int BOTTOM_LANE = rand () % (WORLDHEIGHT / 2) + 2 ;
    for (int lane = WORLDHEIGHT-2; lane > BOTTOM_LANE; lane--)
    {
        const int NO_OF_BALLS = rand () % (WORLDWIDTH/2) + 3 ;
        place_balls (WORLDWIDTH-NO_OF_BALLS-2,lane,NO_OF_BALLS,true) ;
    }
}

//                                                                              
//                                                           
void make_block ()
{
    const int LEFT   = rand () % (WORLDWIDTH  / 3) + 5 ;
    const int BOTTOM = rand () % (WORLDHEIGHT / 4) + 5 ;
    const int WIDTH  = rand () % (WORLDWIDTH  / 2) + 5 ;
    const int HEIGHT = rand () % (WORLDHEIGHT / 2) + 2 ;
    place_rectangle (LEFT, BOTTOM, WIDTH, HEIGHT) ;
    create_ball (LEFT, WORLDHEIGHT - 2) ;
}

//                                                                          

//                                                                                       
void swap_ball ()
{
    if (on_ball ())
        get_ball () ;
    else
	    put_ball () ;
    step () ;
}

//                                    
void turn_north ()
{
    while (!north())
        turn_left();
}

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
void sweep_lane ()
{
    while (!on_ball() && !in_front_of_wall())
        step () ;
}

//                                                                                        
//                                                                              
void go_down_east_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_right() ;
        step() ;
        turn_right() ;
    }
}

//                                                                                        
//                                                                              
void go_down_west_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_left () ;
        step () ;
        turn_left () ;
    }
}

//                                                                          
//                                                             
//                                                                                                                                         
//                                             
void sweep_lanes ()
{
    while (!on_ball())
    {
        sweep_lane () ;
        go_down_east_if_not_on_ball () ;
        sweep_lane () ;
        go_down_west_if_not_on_ball () ;
    }
}

//                                                   
//                                                                                    
//                                                                                                                 
//                                              
void find_ball ()
{
    sweep_lanes () ;
}

//                                                                          

//                                                           

//                                                                                    
//                                                                                                 
//                                                                         
//                                                                                        
/*
          
           
                 
           
           
           
                
           
           
           
           
           
           
           
           
                 
           
           
           
                 
           
           
           
           
           
           
           
           
                
                                                               

*/

/*                                         
                                                                                                   
*/
void clean_line(){
    while(on_ball() && !in_front_of_wall()){
        get_ball();
        step();
    }
}
/*                                                                                         
                                                                                      
*/
void initiate(){
    while(!on_ball()){
            step();
        }
        clean_line();
        get_ball();
        turn_right();
        step();
        turn_right();
}
/*                                                      
                                                                                        
*/
void main_loop(){
     while(on_ball()){
        clean_line();
        turn_around();
        while(!in_front_of_wall()){
            step();
        }
        turn_right();
        step();
        turn_right();
    }
}
/*                                                         
                                                                                     
*/
void return_to_start(){
    while(!in_front_of_wall()){
        step();
    }
    turn_right();
    while(!in_front_of_wall()){
        step();
    }
    turn_right();
}
/*                                                           
                                                                                     
*/
void to_the_square(){
    while(!on_ball()){
        step();
    }
    turn_right();
    while(!in_front_of_wall()){
        step();
    }
}
/*                                    
                                                       
                                                                                                                   
                                                                                                    
*/
void walk_around(){
    while(!on_ball()){
        if(in_front_of_wall()){
            turn_right();
        }else{
            put_ball();
            step();
            turn_left();
        }
    }
}
/*                                                                                            
                                                    
*/
void return_from_block(){
    turn_around();
    step();
    while(!on_ball()){
        step();
    }
    turn_left();
    while(!in_front_of_wall()){
        step();
    }
    turn_around();
}

//                                                                                     
void clean_string_with_balls ()
{
    //                             
       while(on_ball()){
        clean_line();
        turn_right();
        }
}

//                                                                                                                 
void clean_chaos_with_balls ()
{
    //                             
    initiate();
    main_loop();
    return_to_start();
}

//                                                                            
void around_the_block ()
{
    //                        
    to_the_square();
    walk_around();
    return_from_block();
}

//                                                             
void test ()
{
    //                             
}

//                                                  

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

void start_swap_ball ()
{
    store_world () ;
    try {swap_ball (); }
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_search_the_ball ()
{
    reset () ;
    put_a_ball_somewhere () ;
    store_world () ;
    try {find_ball ();}
    catch (...) {}
    retrieve_world () ;
    start_replay_for_timer () ;
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_clean_string_with_balls ()
{
    reset () ;
    make_string_with_balls () ;                   //                                       
    store_world () ;
    try {clean_string_with_balls (); }            //                                                       
    catch (...) {}                                //                         
    retrieve_world () ;
    start_replay_for_timer () ;                   //                                                              
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_clean_chaos_with_balls ()
{
    reset () ;
    make_chaos_with_balls () ;                    //                                                     
    store_world () ;
    try {clean_chaos_with_balls (); }             //                                                       
    catch (...) {}                                //                         
    retrieve_world () ;
    start_replay_for_timer () ;                   //                                                              
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_around_the_block ()
{
    reset () ;
    make_block () ;                               //                                      
    store_world () ;
    try {around_the_block (); }                   //                                                       
    catch (...) {}                                //                         
    retrieve_world () ;
    start_replay_for_timer () ;                   //                                                              
    charles_world().startTimer(FAST_STEP_TIME) ;
}

void start_test ()
{
    store_world () ;
    try {test(); }                                //                                             
    catch (...) {}                                //                         
    retrieve_world () ;
    start_replay_for_timer () ;                   //                                                              
    charles_world().startTimer(FAST_STEP_TIME) ;
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

	Menu l1_menu ((char*)"Examples Lecture 1");
	l1_menu.add ((char*)"Swap ball", start_swap_ball)
	       .add ((char*)"Find ball", start_search_the_ball);

	Menu a1_menu ((char*)"Assignment 1");
	a1_menu.add ((char*)"Balls: a string...", start_clean_string_with_balls )
		   .add ((char*)"Balls: chaos...", start_clean_chaos_with_balls )
		   .add ((char*)"Bonus: around the block...", start_around_the_block )
	       .add ((char*)"Test a function", start_test);

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

