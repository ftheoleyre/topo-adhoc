/* Process model C form file: mobility_models.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char mobility_models_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 42DB7538 42DB7538 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>

#if defined (__cplusplus)
extern "C" {
#endif
FSM_EXT_DECS
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif


/* Header Block */

///////////////////////////////////////////////////////////////
// WAYPOINT MOBILITY HEADER BLOCK
//
// Declaration of every constant, type, library, global 
// variables... used by the mobility process
///////////////////////////////////////////////////////////////

//////////////////////// INCLUDE ////////////////////////////// 

#include 	<math.h>
#include	<oms_dist_support.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>



///////////////// CONSTANTS DEFINITION ////////////////////////

#define 	PI	 				3.141592654

#define		LOW_MOBILITY		1
#define		HIGH_MOBILITY		2

#define		NO_MOBILITY						0
#define		RANDOM_WAYPOINT					1
#define		RANDOM_DIRECTION				2
#define		BOUNDLESS						3
#define		CITY							4
#define		NEITHER_POSITION_NOR_MOBILITY	5

#define		XMIN				0
#define		YMIN				0
#define		PAUSE_TIME			0
#define 	MVT_STEP        	2

#define		DEBUG_POSITIONS		0

///////////////// TRANSITION CODES ////////////////////////////

#define 	MOVE_CODE        	0
#define 	START_PAUSE_CODE 	1
#define 	END_PAUSE_CODE   	2
#define 	STAT_CODE        	3


#define 	MOVE          	((op_intrpt_type () == OPC_INTRPT_SELF) && (op_intrpt_code() == MOVE_CODE))
#define 	START_PAUSE   	(PAUSE == 1)
#define 	KEEP_MOVING   	(PAUSE == 0)
#define 	END_PAUSE     	((op_intrpt_type () == OPC_INTRPT_SELF) && (op_intrpt_code() == END_PAUSE_CODE))
#define 	STATS         	((op_intrpt_type () == OPC_INTRPT_SELF) && (op_intrpt_code() == STAT_CODE))
#define 	FIX           	(MOBILE == 0) 
#define 	MOBIL        	(MOBILE == 1)
#define		ENDSIM_MOB		(op_intrpt_type() == OPC_INTRPT_ENDSIM)


///////////////// GLOBAL VARIABLES ////////////////////////////


typedef struct{
	double x;
	double y;
	}Position;



/* End of Header Block */


#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(last_line_passed) = __LINE__ - _block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(last_line_passed) = 0; _block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	Distribution *	         		direction_dist;
	Objid	                  		node_id;
	Objid	                  		process_id;
	Objid	                  		net_id;
	double	                 		XMAX;
	double	                 		YMAX;
	int	                    		DEBUG;
	int	                    		node_addr;
	double	                 		TRANSMISSION_RANGE;
	int	                    		num_nodes;
	double	                 		my_avg_speed;
	double	                 		distance_to_cover;
	double	                 		SPEED_MAX;
	double	                 		direction_angle;
	double	                 		step_range;
	double	                 		DISTANCE_LIMIT;
	Distribution *	         		uniform_double_x;
	Distribution *	         		uniform_double_y;
	int	                    		PAUSE;
	double	                 		x_target;
	double	                 		y_target;
	Distribution *	         		my_avg_speed_dist;
	FILE*	                  		mobility_file;
	int	                    		MOBILITY_MODEL;
	int	                    		my_address;
	double	                 		SPEED_MIN;
	short	                  		mobile;
	short	                  		speed_class;
	} mobility_models_state;

#define pr_state_ptr            		((mobility_models_state*) SimI_Mod_State_Ptr)
#define direction_dist          		pr_state_ptr->direction_dist
#define node_id                 		pr_state_ptr->node_id
#define process_id              		pr_state_ptr->process_id
#define net_id                  		pr_state_ptr->net_id
#define XMAX                    		pr_state_ptr->XMAX
#define YMAX                    		pr_state_ptr->YMAX
#define DEBUG                   		pr_state_ptr->DEBUG
#define node_addr               		pr_state_ptr->node_addr
#define TRANSMISSION_RANGE      		pr_state_ptr->TRANSMISSION_RANGE
#define num_nodes               		pr_state_ptr->num_nodes
#define my_avg_speed            		pr_state_ptr->my_avg_speed
#define distance_to_cover       		pr_state_ptr->distance_to_cover
#define SPEED_MAX               		pr_state_ptr->SPEED_MAX
#define direction_angle         		pr_state_ptr->direction_angle
#define step_range              		pr_state_ptr->step_range
#define DISTANCE_LIMIT          		pr_state_ptr->DISTANCE_LIMIT
#define uniform_double_x        		pr_state_ptr->uniform_double_x
#define uniform_double_y        		pr_state_ptr->uniform_double_y
#define PAUSE                   		pr_state_ptr->PAUSE
#define x_target                		pr_state_ptr->x_target
#define y_target                		pr_state_ptr->y_target
#define my_avg_speed_dist       		pr_state_ptr->my_avg_speed_dist
#define mobility_file           		pr_state_ptr->mobility_file
#define MOBILITY_MODEL          		pr_state_ptr->MOBILITY_MODEL
#define my_address              		pr_state_ptr->my_address
#define SPEED_MIN               		pr_state_ptr->SPEED_MIN
#define mobile                  		pr_state_ptr->mobile
#define speed_class             		pr_state_ptr->speed_class

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	mobility_models_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
void mobility_message(char* message)
	{
		FILE* 	fichier;
		char	str[100];
		
		if (DEBUG_POSITIONS)
			{
				if (my_address==0)
					{
						op_ima_obj_attr_get(node_id,"cluster-mcds.My_Address",&my_address);
						if (my_address!=0)
							{
								if (my_address<10)
									sprintf(str,"results/details_per_node/mobility_0%d.txt",my_address);
								if (my_address>=10)
									sprintf(str,"results/details_per_node/mobility_%d.txt",my_address);
								fichier = fopen(str,"w");
								fclose(fichier);
							}
					}
				if (my_address!=0)
					{
						if (my_address<10)
							sprintf(str,"results/details_per_node/mobility_0%d.txt",my_address);
						if (my_address>=10)
							sprintf(str,"results/details_per_node/mobility_%d.txt",my_address);
						fichier = fopen(str,"a");
						fprintf(fichier,message);
						fclose(fichier);
					}		
			}
	}

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void mobility_models (void);
	Compcode mobility_models_init (void **);
	void mobility_models_diag (void);
	void mobility_models_terminate (void);
	void mobility_models_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
mobility_models (void)
	{
	int _block_origin = 0;
	FIN (mobility_models ());
	if (1)
		{
		Objid	       	params_comp_attr_objid;
		Objid          	params_attr_objid;
		double	       	prev_angle,x,y,z,x_pos,y_pos,z_pos;
		double         	first_interval;
		char           	msg[64];
		int            	i;
		double         	pause_time;
		double 	       	avg_speed;
		double         	r,e,f,delta_dir;
		int				nb_high_speed_nodes;


		FSM_ENTER (mobility_models)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED (0, state0_enter_exec, "init", "mobility_models () [init enter execs]")
				{
				///////////////////////////////////////////////////////////////
				// WAYPOINT MOBILITY INIT STATE
				//
				// Initialize the waypoint mobility process model
				///////////////////////////////////////////////////////////////
				char	str[50];
				FILE*	fichier;
				
				
				// init Objids
				process_id = op_id_self();
				node_id = op_topo_parent (process_id);
				net_id = op_topo_parent(node_id);
				
				// Load Mobility parameters
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"X_MAX"      		, &XMAX);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"Y_MAX"      		, &YMAX);
				
				//To determine if that node is an high speed node or not (we have 2 classes of nodes)
				op_ima_obj_attr_get(op_id_self(), 		"Speed_Class"		, &speed_class);
				switch(speed_class)
					{	
						case NO_MOBILITY :
							SPEED_MAX = 0;
							SPEED_MIN = 0;
							MOBILITY_MODEL = NO_MOBILITY;
						break;
						case LOW_MOBILITY :
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"SP_LOW_MAX"			, &SPEED_MAX);
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"SP_LOW_MIN"			, &SPEED_MIN);
							op_ima_sim_attr_get(OPC_IMA_INTEGER, 	"SP_LOW_MOBILITY_MODEL"	, &MOBILITY_MODEL);
						break;
						case HIGH_MOBILITY :
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"SP_HIGH_MAX"			, &SPEED_MAX);
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"SP_HIGH_MIN"			, &SPEED_MIN);
							op_ima_sim_attr_get(OPC_IMA_INTEGER, 	"SP_HIGH_MOBILITY_MODEL", &MOBILITY_MODEL);
						break;
						default :
							printf("the definition of mobility model isn't valid ! \n");
							break;
					}
				
				
				if (MOBILITY_MODEL!=NEITHER_POSITION_NOR_MOBILITY)
					{
						// Pick a random init position
						uniform_double_x = op_dist_load ("uniform", XMIN, XMAX);
						x_pos = op_dist_outcome(uniform_double_x);
						uniform_double_y = op_dist_load ("uniform", YMIN, YMAX);
						y_pos = op_dist_outcome(uniform_double_y);
						// Set the current position of the node
						op_ima_obj_attr_set(node_id,"x position",x_pos);
						op_ima_obj_attr_set(node_id,"y position",y_pos);
					}
				
				if (MOBILITY_MODEL!=NO_MOBILITY)
					{
						/* Read the number of nodes in the network */
						num_nodes = op_topo_object_count (OPC_OBJTYPE_NDMOB);
						//if(num_nodes > N_MAX)
						//	{
						//		op_sim_end("Network contains more than N_MAX nodes","Change N_MAX value in all files and restart all over again","","");
						//	}
						
						// Compute DISTANCE_LIMIT
						DISTANCE_LIMIT = sqrt((XMAX - XMIN)*(XMAX - XMIN)+(YMAX - YMIN)*(YMAX - YMIN));
						// initialize distributions for random movement
						direction_dist = op_dist_load ("uniform", -1, 1);
				
						
						// Begin
						// If MOBILITY attribute is set to Enabled, then node is 
						// really entitled to travel through the network.
						// In this case, transit to "Init_Mvt" state.
				
						
						// Init avg speed
						my_avg_speed_dist=op_dist_load("uniform",SPEED_MIN,SPEED_MAX);
						my_avg_speed = (double)op_dist_outcome(my_avg_speed_dist);
				
						
						// Schedule the end of the initial pause time
						op_intrpt_schedule_self(op_sim_time()+1,END_PAUSE_CODE);
					}
				
				
				if ((MOBILITY_MODEL==NEITHER_POSITION_NOR_MOBILITY)||(MOBILITY_MODEL==NO_MOBILITY))
					mobile = 0;
				else
					mobile = 1;
				
				}


			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "mobility_models () [init exit execs]")
				{
				}


			/** state (init) transition processing **/
			FSM_INIT_COND (mobile)
			FSM_TEST_COND (!mobile)
			FSM_TEST_LOGIC ("init")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 3, state3_enter_exec, ;, "mobile", "", "init", "idle")
				FSM_CASE_TRANSIT (1, 4, state4_enter_exec, ;, "!mobile", "", "init", "OFF")
				}
				/*---------------------------------------------------------*/



			/** state (Init_Mvt) enter executives **/
			FSM_STATE_ENTER_FORCED (1, state1_enter_exec, "Init_Mvt", "mobility_models () [Init_Mvt enter execs]")
				{
				/* Initiate the movement.
				/* 1. Determine the avg speed of the current node.
				/* 2. Determine the length of the distance, which the node
				/*    has to cover in his next run.
				/* 3. Given these two values, plus the movement step in time,
				/*    then compute the distance to cover during each simulation 
				/*    step (state variable "step_range")
				/* 4. Determine a direction to follow.
				*/
				op_prg_odb_bkpt("Mobile_Init");
				
				// Reset the PAUSE flag
				PAUSE = 0;
				
				// init the distribution which will chose a uniformly distributed 
				// average speed between 0 and SPEED_LIMIT meters per second
				my_avg_speed_dist=op_dist_load("uniform",SPEED_MIN,SPEED_MAX);
				my_avg_speed = (double)op_dist_outcome(my_avg_speed_dist);
				
				
				switch (MOBILITY_MODEL) 
					{
				  		case RANDOM_WAYPOINT : // Random walk mobility model : Init_Mvt state
					      
							// Pick a target position
							x_target = x = op_dist_outcome(uniform_double_x);
							y_target = y = op_dist_outcome(uniform_double_y);
				
							// Read the current position
							op_ima_obj_attr_get(node_id,"x position",&x_pos);
							op_ima_obj_attr_get(node_id,"y position",&y_pos);
				
							// Compute the distance to cover for the next mvt
							distance_to_cover = sqrt((x-x_pos)*(x-x_pos) + (y-y_pos)*(y-y_pos));
				
							// Step range
							step_range      = MVT_STEP*my_avg_speed;
							// Angle
							if(x != x_pos)
								{
									direction_angle =  atan((y-y_pos)/(x-x_pos));///op_dist_outcome (one) * PI;
									if(direction_angle < 0)
										direction_angle = (direction_angle*(-1));
									if(x_target > x_pos && y_target > y_pos)
										direction_angle =  direction_angle;
									else if(x_target > x_pos && y_target < y_pos)
											direction_angle =  (direction_angle*(-1));
										else if(x_target < x_pos && y_target > y_pos)
												{
													direction_angle =  PI - direction_angle;
												}
											else if(x_target < x_pos && y_target < y_pos)
												{
													direction_angle =  direction_angle - PI;
												}
								}
						else if(y != y_pos)
							direction_angle =  (y>y_pos?0.5*PI:-0.5*PI);
						else
							direction_angle =  0;
				
				        break;
						   
				   
				   case RANDOM_DIRECTION : // Random direction mobility model : Init_Mvt state
						   
				   		   		// Pick a target position
						   		//x = op_dist_outcome(uniform_double_x);
								//y = op_dist_outcome(uniform_double_y);
								
								//pick a random direction angle betwen 0 and 2*PI
								r = op_dist_uniform(2);
						   		direction_angle = r*PI;
				
								// Step range
								step_range      = MVT_STEP*my_avg_speed;
				
								// Read the current position
								op_ima_obj_attr_get(node_id,"x position",&x_pos);
								op_ima_obj_attr_get(node_id,"y position",&y_pos);
								
						     // End of Random direction mobility model : Init_Mvt state
				
							 break ;
				
				   case BOUNDLESS : // Boundless mobility model : Init_Mvt state
						   
					   			// Read the current position
					   			op_ima_obj_attr_get(node_id,"x position",&x_pos);
								op_ima_obj_attr_get(node_id,"y position",&y_pos);
				
								// Step range
								step_range     = MVT_STEP*my_avg_speed;
				
								// Angle
								r=op_dist_uniform(2);
								direction_angle=r*PI;
				
								sprintf(msg,"direction angle = %f*PI", direction_angle);
				
							// End of Boundless mobility model : Init_Mvt state
				           
						   break ;
				
				   case CITY :	   //city mobility model : Init_Mvt state
					   
						       // Pick a target position
						   		x_target=x= op_dist_outcome(uniform_double_x);
								y_target=y= op_dist_outcome(uniform_double_y);
								
								// Step range
						   		step_range      = MVT_STEP*my_avg_speed;
				
								// Read the current position
								op_ima_obj_attr_get(node_id,"x position",&x_pos);
								op_ima_obj_attr_get(node_id,"y position",&y_pos);
						        x_pos=(int)x_pos;
						        y_pos=(int)y_pos;
						   
						        direction_dist=op_dist_load ("uniform_int", -12, 12);
						   		e = 1 + (int)op_dist_outcome (direction_dist);
						        f = 1 + (int)op_dist_outcome (direction_dist);
						        //pick a random x_target inside the simulation area
						   		x_target=x_pos+ (int) step_range*e;
						        if (x_target<0)
									x_target = x_target*(-1);
						        
						        //pick a random x_target inside the simulation area
						        y_target=y_pos+(int) step_range*f;
						       	if (y_target<0)
									y_target = y_target*(-1);
						   
						   		while (x_target>XMAX || x_target<XMIN || y_target>YMAX || y_target<YMIN)
									{					   
									    e=1+(int)op_dist_outcome (direction_dist);
										f=1+(int)op_dist_outcome (direction_dist);
										
										x_target=x_pos+ (int) step_range*e;
										if (x_target<0)
											x_target = x_target*(-1);
						   
										y_target=y_pos+(int) step_range*f;
										if (y_target<0)
											y_target = y_target*(-1);
										
									 }
						   		
						        //End of city mobility model : Init_Mvt state		   			   
				        break ;
				   }
				}


			/** state (Init_Mvt) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "Init_Mvt", "mobility_models () [Init_Mvt exit execs]")
				{
				}


			/** state (Init_Mvt) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "Init_Mvt", "Move")
				/*---------------------------------------------------------*/



			/** state (Move) enter executives **/
			FSM_STATE_ENTER_FORCED (2, state2_enter_exec, "Move", "mobility_models () [Move enter execs]")
				{
				char	msg[150];
				
				
				op_prg_odb_bkpt("Mobile_Move");
				
				/* Move a step_range ahead and decrease the lenght of distance_to_cover*/
				// Get the current position of the node
				op_ima_obj_attr_get(node_id,"x position",&x_pos);
				op_ima_obj_attr_get(node_id,"y position",&y_pos);
				
				sprintf(msg,"speed=%f, direction=%f, x=%f, y=%f\n",my_avg_speed,direction_angle,x_pos,y_pos);
				mobility_message(msg);
				
				
				
				
				switch (MOBILITY_MODEL)
				  {
				  
				   case RANDOM_WAYPOINT :     // Random walk mobility model : Mvt state
					   
				   				// Trace
				   				x_pos = (double) x_pos;
								y_pos = (double) y_pos;
								sprintf(msg,"Target  position  |X axis: %f   |Y axis: %f", x_target, y_target);
								sprintf(msg,"Current position  |X axis: %f   |Y axis: %f", x_pos, y_pos);
				
				   				// Compute the new x and y position according to the STEP_DIST and the current direction (angle)
								x= x_pos+ (double) step_range*cos(direction_angle);
								y= y_pos+ (double) step_range*sin(direction_angle);
				
								// Make sure the new position is inside the grid
								while(y<YMIN || YMAX<y || x<XMIN || XMAX<x)
									{
					
									// Compute a random new direction
									direction_angle= op_dist_outcome(direction_dist)*PI;
									//Compute the new x and y position according to the STEP_DIST and the current direction (angle)
									x= x_pos+ (double) step_range*cos(direction_angle);
									y= y_pos+ (double) step_range*sin(direction_angle);
					
									}
				
								// set the new position of the node
								op_ima_obj_attr_set(node_id, "x position",x);
								op_ima_obj_attr_set(node_id, "y position",y);
				
								// Decrease the value of the distance to cover
								distance_to_cover = distance_to_cover-step_range;
				
								// Check if target reached or not
								if(distance_to_cover < step_range)
									{
									// Set the pause flag to 1		
									PAUSE = 1;
									// Set avg speed to 0
									my_avg_speed = 0;
					
									// Schedule an interrupt for the end of the next pause state
									op_intrpt_schedule_self(op_sim_time()+PAUSE_TIME,END_PAUSE_CODE);
									sprintf(msg,"Target position reached: Enter Pause state\n\t\t- Distance to cover = %f\n\t\t- Pause time = %f",distance_to_cover,pause_time);
										}
								else
									{
									sprintf(msg,"Target position not reached yet: Keep on moving\n\t\t- Distance still to cover = %f",distance_to_cover);
									op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
									}
				
				     		// End of Random walk mobility model : Mvt state 
				           
								break;
						   
				   
				
				   case RANDOM_DIRECTION :	  // Random direction mobility model : Mvt state 
						   			
									// Trace
									x_pos = (double) x_pos;
									y_pos = (double) y_pos;
				
									sprintf(msg,"Current position  |X axis: %f   |Y axis: %f", x_pos, y_pos);
				
									// Compute the new x and y position according to the STEP_DIST and the current direction (angle)
									x= x_pos+ (double) step_range*cos(direction_angle);
									y= y_pos+ (double) step_range*sin(direction_angle);
				
									// Make sure the new position is inside the grid
									while(y<YMIN || YMAX<y || x<XMIN || XMAX<x)
										{
					
										// Compute a random new direction
										r=op_dist_uniform(2);
										direction_angle=r*PI;
						
						
										// Compute the new x and y position according to the STEP_DIST and the current direction (angle)
										x= x_pos+ (double) step_range*cos(direction_angle);
										y= y_pos+ (double) step_range*sin(direction_angle);
					  
										}
				
									// set the new position of the node
									op_ima_obj_attr_set(node_id, "x position",x);
									op_ima_obj_attr_set(node_id, "y position",y);
				
				
									// Check if target reached or not
				
									if(x==XMAX || x== XMIN || y==YMAX || y==YMIN)
					
										{
										// Set the pause flag to 1		
										PAUSE = 1;
										// Set avg speed to 0
										my_avg_speed = 0;
					
										// Schedule an interrupt for the end of the next pause state
										op_intrpt_schedule_self(op_sim_time()+PAUSE_TIME,END_PAUSE_CODE);
					
										}
				
									else
					
										op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
				
						            // End of Random direction mobility model : Mvt state 
				             
									break ;
				
				   case BOUNDLESS :         //Boundless mobility model : Mvt state
										
										
										// Trace
					                    op_ima_obj_attr_get(node_id, "x position",&x_pos);
										op_ima_obj_attr_get(node_id, "y position",&y_pos);
										
										//Chooses a new direction
										direction_dist=op_dist_load("normal",direction_angle,0.001*PI);
								   	    direction_angle = op_dist_outcome(direction_dist);
									
										//Keeps the direction_angle between 0 and 2*PI
										if (direction_angle < 0)
											direction_angle += 2*PI;
										if (direction_angle > 2*PI)
											direction_angle -= 2*PI;
				
										//Chooses a new speed
										my_avg_speed_dist = op_dist_load("normal",my_avg_speed,0.01);
										my_avg_speed = (double)op_dist_outcome(my_avg_speed_dist);
										if (my_avg_speed < SPEED_MIN)
											my_avg_speed = SPEED_MIN;
										if (my_avg_speed > SPEED_MAX)
											my_avg_speed = SPEED_MAX;
									
										// Compute the new x and y position according to the STEP_DIST and the current direction (angle)
										x= x_pos+ (double) step_range*cos(direction_angle);
										y= y_pos+ (double) step_range*sin(direction_angle);
									
										//A node out of limits reappear on the next side
										if (x < XMIN)
											x = XMAX;
										if (x > XMAX)
											x = XMIN;
										if (y < YMIN)
											y = YMAX;
										if (y > YMAX)
											y = YMIN;
				
										op_ima_obj_attr_set(node_id, "x position",x);
										op_ima_obj_attr_set(node_id, "y position",y);
										op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
									
									
									
									// Make sure the new position is inside the grid
				
				/*						while(y<YMIN || YMAX<y || x<XMIN || XMAX<x)
				
											{
											// Compute a random new direction
											//r=op_dist_uniform(2);
											//direction_angle=r*PI;
				                            one=op_dist_load("uniform_init",-PI*0.05,PI*0.05);
										    delta_dir=op_dist_outcome(one);  
								   	        direction_angle=direction_angle+delta_dir;
											
											//Keeps the direction between 0 and 2*PI
											if (direction_angle < 0)
												direction_angle += 2*PI;
											if (direction_angle > 2*PI)
												direction_angle -= 2*PI;
											
					  						// Compute the new x and y position according to the STEP_DIST and the current direction (angle)
											//x= x_pos+ (double) step_range*cos(direction_angle);
											//y= y_pos+ (double) step_range*sin(direction_angle);
					
											}
				
										if ((x-0.2)<=XMIN)    
											{ 
												x=XMAX;
																					
												// set the new position of the node
												op_ima_obj_attr_set(node_id, "x position",XMAX);
												op_ima_obj_attr_set(node_id, "y position",y);
												op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
												
											 }
										
									     
										else if ((x+0.2)>=XMAX)   
												{
												 
												x=XMIN;
													
												 // set the new position of the node
											  	op_ima_obj_attr_set(node_id, "x position",XMIN);
										   		op_ima_obj_attr_set(node_id, "y position",y);
								     			op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
													
				 								}
											 
										 else if ((y-0.2)<=YMIN)  
											    {
														
												 y=YMAX;
														
												 // set the new position of the node
												 op_ima_obj_attr_set(node_id, "x position",x);
												 op_ima_obj_attr_set(node_id, "y position",YMAX);			
												 op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
													
												}
										 
										  else if ((y+0.2)>=YMAX)
												{
												
												   y=YMIN;
															
												   //set the new position of the node
												   op_ima_obj_attr_set(node_id, "x position",x);
												   op_ima_obj_attr_set(node_id, "y position",YMIN);
												   op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
																									
												 }
										
										  else				   
				*/																							
				
				           
										//End of Boundless mobility model:  Mvt state
								   
				           break ;
				
				   case CITY :  //city mobility model : Mvt state
						    
									// Trace
									x_pos = (int) x_pos;
									y_pos = (int) y_pos;
									
									sprintf(msg,"Target  position  |X axis: %f   |Y axis: %f", x_target, y_target);
									sprintf(msg,"Current position  |X axis: %f   |Y axis: %f", x_pos, y_pos);
									
									
									if ( x_pos!= x_target)
										{
											if ( x_target>x_pos )
												x_pos= x_pos+ (int) step_range;
											else
												x_pos= x_pos- (int) step_range;
											
											// set the new position of the node
											op_ima_obj_attr_set(node_id, "x position",x_pos);
											op_ima_obj_attr_set(node_id, "y position",y_pos);
									
											op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
											
										} 
										
									 else 
									   if (y_pos!=y_target)
										   {
										   		if ( y_target<y_pos )      	  
													y_pos= y_pos-(int) step_range;
												else
													y_pos= y_pos+ (int) step_range;
											  							 
												// set the new position of the node
												op_ima_obj_attr_set(node_id, "x position",x_pos);
												op_ima_obj_attr_set(node_id, "y position",y_pos);
									
												op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
											}
									
									 	else
											{
									   		   //Set the pause flag to 1		
									   			PAUSE = 1;
									
												//Set avg speed to 0
												my_avg_speed = 0;
									
												// set the new position of the node
												op_ima_obj_attr_set(node_id, "x position",x_pos);
												op_ima_obj_attr_set(node_id, "y position",y_pos);
									
												//Schedule an interrupt for the end of the next pause state
												op_intrpt_schedule_self(op_sim_time()+PAUSE_TIME,END_PAUSE_CODE);
											 }
						//End of city mobility model : Mvt state
									   
					    break ;
				   }
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				/*
				
				// Trace
				x_pos = (double) x_pos;
				y_pos = (double) y_pos;
				
				
				if (DEBUG>1)
					{
						sprintf(msg,"Target  position  |X axis: %f   |Y axis: %f\n", x_target, y_target);
						mobility_message(msg);
						sprintf(msg,"Current position  |X axis: %f   |Y axis: %f\n", x_pos, y_pos);
						mobility_message(msg);
					}
				
				//Compute the new x and y position according to the STEP_DIST and the current direction (angle)
				x= x_pos+ (double) step_range*cos(direction_angle);
				y= y_pos+ (double) step_range*sin(direction_angle);
				
				// Make sure the new position is inside the grid
				while(y<YMIN || YMAX<y || x<XMIN || XMAX<x)
					{
						// Compute a random new direction
						direction_angle= op_dist_outcome(one)*PI;
						// Compute the new x and y position according to the STEP_DIST and the current direction (angle)
						x= x_pos+ (double) step_range*cos(direction_angle);
						y= y_pos+ (double) step_range*sin(direction_angle);
					}
				
				// set the new position of the node
				op_ima_obj_attr_set(node_id, "x position",x);
				op_ima_obj_attr_set(node_id, "y position",y);
				
				// Decrease the value of the distance to cover
				distance_to_cover = distance_to_cover-step_range;
				
				// Check if target reached or not
				if(distance_to_cover < step_range)
					{
						// Set the pause flag to 1		
						PAUSE = 1;
						// Set avg speed to 0
						my_avg_speed = 0;
					
						// Schedule an interrupt for the end of the next pause state
						op_intrpt_schedule_self(op_sim_time()+PAUSE_TIME,END_PAUSE_CODE);
				
						if (DEBUG>1)
							{
								sprintf(msg,"Target position reached: Enter Pause state\n\t\t- Distance to cover = %f\n\t\t- Pause time = %f\n",distance_to_cover,pause_time);
								mobility_message(msg);
							}
					}
				else
					{
						if (DEBUG>1)
							{
								sprintf(msg,"Target position not reached yet: Keep on moving\n\t\t- Distance still to cover = %f\n",distance_to_cover);
								mobility_message(msg);
							}
						op_intrpt_schedule_self(op_sim_time()+MVT_STEP,MOVE_CODE);
					}
				
				
				
				*/
				}


			/** state (Move) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "Move", "mobility_models () [Move exit execs]")
				{
				}


			/** state (Move) transition processing **/
			FSM_TRANSIT_FORCE (3, state3_enter_exec, ;, "default", "", "Move", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (3, state3_enter_exec, "idle", "mobility_models () [idle enter execs]")
				{
				// If there still a distance to cover (distance_to_cover > 0)
				// then schedule an interrupt for the next movement after a
				// MVT_STEP sec period of time.
				// Else, schedule an interrupt to enter the Pause state now.
				
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (7,mobility_models)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (3, "idle", "mobility_models () [idle exit execs]")
				{
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (MOVE)
			FSM_TEST_COND (END_PAUSE)
			FSM_TEST_COND (ENDSIM_MOB)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "MOVE", "", "idle", "Move")
				FSM_CASE_TRANSIT (1, 1, state1_enter_exec, ;, "END_PAUSE", "", "idle", "Init_Mvt")
				FSM_CASE_TRANSIT (2, 3, state3_enter_exec, ;, "ENDSIM_MOB", "", "idle", "idle")
				}
				/*---------------------------------------------------------*/



			/** state (OFF) enter executives **/
			FSM_STATE_ENTER_UNFORCED (4, state4_enter_exec, "OFF", "mobility_models () [OFF enter execs]")
				{
				sprintf(msg,"speed=%f, direction=%f, x=%f, y=%f\n",my_avg_speed,direction_angle,x_pos,y_pos);
				mobility_message(msg);
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (9,mobility_models)


			/** state (OFF) exit executives **/
			FSM_STATE_EXIT_UNFORCED (4, "OFF", "mobility_models () [OFF exit execs]")
				{
				}


			/** state (OFF) transition processing **/
			FSM_TRANSIT_FORCE (4, state4_enter_exec, ;, "default", "", "OFF", "OFF")
				/*---------------------------------------------------------*/



			/** state (pre_init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (5, "pre_init", "mobility_models () [pre_init enter execs]")
				{
				op_intrpt_schedule_self (op_sim_time() +  op_dist_uniform (1.0)	, 0);
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (11,mobility_models)


			/** state (pre_init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (5, "pre_init", "mobility_models () [pre_init exit execs]")
				{
				}


			/** state (pre_init) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "pre_init", "init")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (5,mobility_models)
		}
	}

#if defined (__cplusplus)
	extern "C" { 
#endif
	extern VosT_Fun_Status Vos_Catmem_Register (const char * , int , VosT_Void_Null_Proc, VosT_Address *);
	extern VosT_Address Vos_Catmem_Alloc (VosT_Address, size_t);
	extern VosT_Fun_Status Vos_Catmem_Dealloc (VosT_Address);
#if defined (__cplusplus)
	}
#endif


Compcode
mobility_models_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (mobility_models_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (mobility_models)",
			sizeof (mobility_models_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
			{
			FRET (OPC_COMPCODE_FAILURE)
			}
		}

	*gen_state_pptr = Vos_Catmem_Alloc (obtype, 1);
	if (*gen_state_pptr == OPC_NIL)
		{
		FRET (OPC_COMPCODE_FAILURE)
		}
	else
		{
		/* Initialize FSM handling */
		((mobility_models_state *)(*gen_state_pptr))->current_block = 10;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
mobility_models_diag (void)
	{
	/* No Diagnostic Block */
	}




void
mobility_models_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (mobility_models_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in mobility_models_svar function. */
#undef direction_dist
#undef node_id
#undef process_id
#undef net_id
#undef XMAX
#undef YMAX
#undef DEBUG
#undef node_addr
#undef TRANSMISSION_RANGE
#undef num_nodes
#undef my_avg_speed
#undef distance_to_cover
#undef SPEED_MAX
#undef direction_angle
#undef step_range
#undef DISTANCE_LIMIT
#undef uniform_double_x
#undef uniform_double_y
#undef PAUSE
#undef x_target
#undef y_target
#undef my_avg_speed_dist
#undef mobility_file
#undef MOBILITY_MODEL
#undef my_address
#undef SPEED_MIN
#undef mobile
#undef speed_class



void
mobility_models_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	mobility_models_state		*prs_ptr;

	FIN (mobility_models_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (mobility_models_state *)gen_ptr;

	if (strcmp ("direction_dist" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->direction_dist);
		FOUT;
		}
	if (strcmp ("node_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->node_id);
		FOUT;
		}
	if (strcmp ("process_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->process_id);
		FOUT;
		}
	if (strcmp ("net_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->net_id);
		FOUT;
		}
	if (strcmp ("XMAX" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->XMAX);
		FOUT;
		}
	if (strcmp ("YMAX" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->YMAX);
		FOUT;
		}
	if (strcmp ("DEBUG" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG);
		FOUT;
		}
	if (strcmp ("node_addr" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->node_addr);
		FOUT;
		}
	if (strcmp ("TRANSMISSION_RANGE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->TRANSMISSION_RANGE);
		FOUT;
		}
	if (strcmp ("num_nodes" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->num_nodes);
		FOUT;
		}
	if (strcmp ("my_avg_speed" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_avg_speed);
		FOUT;
		}
	if (strcmp ("distance_to_cover" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->distance_to_cover);
		FOUT;
		}
	if (strcmp ("SPEED_MAX" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->SPEED_MAX);
		FOUT;
		}
	if (strcmp ("direction_angle" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->direction_angle);
		FOUT;
		}
	if (strcmp ("step_range" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->step_range);
		FOUT;
		}
	if (strcmp ("DISTANCE_LIMIT" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DISTANCE_LIMIT);
		FOUT;
		}
	if (strcmp ("uniform_double_x" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->uniform_double_x);
		FOUT;
		}
	if (strcmp ("uniform_double_y" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->uniform_double_y);
		FOUT;
		}
	if (strcmp ("PAUSE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->PAUSE);
		FOUT;
		}
	if (strcmp ("x_target" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->x_target);
		FOUT;
		}
	if (strcmp ("y_target" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->y_target);
		FOUT;
		}
	if (strcmp ("my_avg_speed_dist" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_avg_speed_dist);
		FOUT;
		}
	if (strcmp ("mobility_file" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->mobility_file);
		FOUT;
		}
	if (strcmp ("MOBILITY_MODEL" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->MOBILITY_MODEL);
		FOUT;
		}
	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
		FOUT;
		}
	if (strcmp ("SPEED_MIN" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->SPEED_MIN);
		FOUT;
		}
	if (strcmp ("mobile" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->mobile);
		FOUT;
		}
	if (strcmp ("speed_class" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->speed_class);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

