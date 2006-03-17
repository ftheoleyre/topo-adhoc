/* Process model C form file: mewlana_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char mewlana_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 43ED1905 43ED1905 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
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

// INCLUDES
#include	<oms_dist_support.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>


//----------------------------------------------------------------------
//				     		Parameters		
//----------------------------------------------------------------------

// Special attribute values.
#define		TIME_INIT_MAC					5.0		//Time to wait before initialization
#define		TIME_BEGIN_STATS				15.0
#define		TIME_BEGIN_NETWORK				60.0
#define		BROADCAST						-1

#define		PROCESS_ID_NAME					"mewlana"

//	General parameters
#define		MAX_NETWORK_RADIUS				10
#define		MAX_NB_NODES					150
#define		MAX_ADDRESS						150
#define		LOW_SPEED						1
#define		HIGH_SPEED						2
#define		PROMISCUOUS_FOR_UNICAST			0

//	Constants to define Maximum Array Dimension
#define		MAX_DATA_PK						100000
#define		MAX_AP_HELLO_PK					1000

// DATA
#define		INTERVALL_DATA_PK_AP			2
#define		INTERARRIVAL_DATA_PK			0.25
#define		NB_PK_PER_FLOW					8
#define		DATA_PK_UPLOAD_RATIO			1

#define		UPLOAD							0
#define		DOWNLOAD						1

//	For automatic attribution of Addresses
#define		ADDR_RANDOM						0
#define		ADDR_WLAN						1
#define		ADDR_CONFIGURED					2
#define		ADDR_MAC_CDCL_FROM_NAME			3
	

// Special Addresses (Multicast for APs...)
#define		ADDR_MULTICAST_AP				255
#define		ADDR_MULTICAST_BACKBONE			256
#define		LOWER_ADDR_FOR_MULTICAST		255			


// Intervalls for packets and interruptions
#define		INTERVALL_AP_HELLO				4.0
#define		INTERVALL_HELLO					4.0
#define		INTERVALL_PERIODIC_FUNCTIONS	1.0

// Hellos
#define		MAX_FIELDS_IN_HELLO				35


// Acks
#define		MAX_NB_RETRIES_UNICAST_ACKS		3
#define		ACK_FOR_AP_REG					0
#define		ACK_FOR_DATA					1


//  Timeouts
#define		TIMEOUT_AP_HELLO				2.1			//In AP-Hellos
#define		TIMEOUT_HELLO					3.1			//In Hellos
#define		TIMEOUT_UNICAST_ACK				0.2			//Acks in Unicast
#define		TIMEOUT_ADDR_PK_ID				10.1
#define		TIMEOUT_ICI						2.0

// Figures for Topology
#define		THICKNESS_PHYSIC_NEIGHBOR		2
#define		COLOR_AP_CONNECTED				6
#define		COLOR_AP_DISCONNECTED			0
#define		GRAPHIC_XMAX					9000




//----------------------------------------------------------------------
//						PACKETS			
//----------------------------------------------------------------------
//Streams
#define		STRM_FROM_WLAN					0
#define		STRM_TO_WLAN					0

#define		STRM_FROM_ETH					2
#define		STRM_TO_ETH						2

#define		STRM_FROM_HIGHER	   			1
#define		STRM_TO_HIGHER					1

//For Stats
#define		AP_HELLO						1
#define		AP_REGISTRATION					2
#define		UNICAST_ACK						3
#define		HELLO							4
#define		DATA							5


//Packets Type
#define		AP_HELLO_PK_TYPE				1
#define		AP_REGISTRATION_PK_TYPE			2
#define		UNICAST_ACK_PK_TYPE				3
#define		HELLO_PK_TYPE					4
#define		DATA_PK_TYPE					5





//----------------------------------------------------------------------
//						Interruptions			
//----------------------------------------------------------------------

// Interruption codes
#define		AP_HELLO_GENERATE_CODE			1
#define		HELLO_GENERATE_CODE				2
#define		PK_DATA_GENERATE_CODE			3

#define		PERIODIC_FUNCTIONS_CODE			10
#define		UNICAST_RETRANSMISSIONS_CODE	11
#define		WRITE_TOPOLOGY_CODE				12


// Macro definitions for state
#define		ENDSIM							(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define 	PK_FROM_ETH						(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_ETH)
#define 	PK_FROM_WLAN					(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_WLAN)
#define		PK_FROM_LOWER					(PK_FROM_ETH || PK_FROM_WLAN)
#define 	PK_DATA_GENERATE				(op_intrpt_code() == PK_DATA_GENERATE_CODE)
#define		AP_HELLO_GENERATE				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == AP_HELLO_GENERATE_CODE)
#define		HELLO_GENERATE					(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == HELLO_GENERATE_CODE)
#define		PERIODIC_FUNCTIONS				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == PERIODIC_FUNCTIONS_CODE)
#define		UNICAST_RETRANSMISSIONS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == UNICAST_RETRANSMISSIONS_CODE)
#define		WRITE_TOPOLOGY					(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == WRITE_TOPOLOGY_CODE)










//----------------------------------------------------------------------
//						Structures
//----------------------------------------------------------------------


//For Addr/Pk_id records
typedef struct {
	int			address;
	int			pk_id;
	double		timeout;
} addr_pk_id_couple;


//Routing Table
typedef struct{
	int 		dest;
	int			relay;
	short		hops;
	Boolean		ap;
	double		timeout;
	Boolean		bidirect;
} routing_entry ;

//Acks table
typedef struct{
	int			dest;
	int			pk_id;
	double 		timeout;
	short		nb_retry;
	packet*		pkptr;	
} ack_couple;


//Multiple Ici (one for each packet)
typedef struct{
	Ici*	ici_ptr;
	double	timeout;
} struct_ici;




//----------------------------------------------------------------------
//						Structures For Stats Collect
//----------------------------------------------------------------------


//DATA PK
typedef struct{
	int		source;
	int		dest;
	int		pk_size;
	short	hops;
	int		nb_retry;
	short	type;
	double	time_emission;
	double	time_reception;
	Boolean	error_from_src;
} struct_stats_data;




//----------------------------------------------------------------------
//				     		STATS
//----------------------------------------------------------------------
//Common

int			nb_nodes;
int			begin_name_stats = 0;

//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];




//----------------------------------------------------------------------
//	     		Global Variables for Control		
//----------------------------------------------------------------------

//	Common
int			begin_time 			= 0;

// Nb nodes, special nodes... 
int			nb_aps = 0;
int			nb_nodes = 0;

// Speeds
int			nb_high_speed_nodes = 0;
int			nb_low_speed_nodes 	= 0;

// Degree
int			average_degree = 0;

//Actual Number of Communicating Nodes
int			actual_nb_connections = 0;


//----------------------------------------------------------------------
//				     		Statistics		
//----------------------------------------------------------------------
//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];

//AP Hellos (Transmission & Registration)
int			stats_ap_hellos_rcvd	[MAX_AP_HELLO_PK][MAX_NB_NODES];
int			nb_nodes_registered_to_ap 				= 0;
int			nb_nodes_which_have_a_valid_ap 			= 0;
int			nb_nodes_registered_to_ap_final 		= 0;
int			nb_nodes_which_have_a_valid_ap_final 	= 0;
char		list_nodes_without_valid_ap[500];

//AP Registrations
int			stats_ap_reg 		[MAX_AP_HELLO_PK][MAX_NB_NODES][4];		//0-Source Address , 1-Destination address, 2-Nb Hops, 3-Nb retransmissions
double		stats_ap_reg_time 	[MAX_AP_HELLO_PK][MAX_NB_NODES][2];		//0-Time Emission ,1-Time Reception
int			stats_nb_ap_hello = 0;

//Topology Figures
short		stats_nb_position_written;
short		stats_positions		[MAX_NB_NODES][2];						//[1] : the x-coordinate, [2] : the y-coordinate, 
short		stats_links			[MAX_NB_NODES][MAX_NB_NODES];			//[i][j] 1 If there exists a link between nodes i and j
short		stats_ap_connection	[MAX_NB_NODES];							//[i] 1 If the node i is connected to AP




//----------------------------------------------------------------------
//			     		Packet Statistics		
//----------------------------------------------------------------------
int			nb_pk_instantaneous 								= 0;
int			nb_pk_total 										= 0;
int			nb_pk_retransmission_instantaneous 					= 0;
int			nb_pk_retransmission_total 							= 0;


int			nb_pk_ap_hello_instantaneous 						= 0;
int			nb_pk_ap_hello_total 								= 0;
int			nb_pk_ap_hello_retransmission_instantaneous 		= 0;
int			nb_pk_ap_hello_retransmission_total 				= 0;

int			nb_pk_ap_registration_instantaneous 				= 0;
int			nb_pk_ap_registration_total 						= 0;
int			nb_pk_ap_registration_retransmission_instantaneous 	= 0;
int			nb_pk_ap_registration_retransmission_total 			= 0;

int			nb_pk_unicast_ack_instantaneous 					= 0;
int			nb_pk_unicast_ack_total 							= 0;

int			nb_pk_hello_instantaneous 							= 0;
int			nb_pk_hello_total 									= 0;

int			nb_pk_data_instantaneous 							= 0;
int			nb_pk_data_total 									= 0;
int			nb_pk_data_retransmission_instantaneous 			= 0;
int			nb_pk_data_retransmission_total 					= 0;




//----------------------------------------------------------------------
//						    Data 	Packets		
//----------------------------------------------------------------------
struct_stats_data	stats_data_pk 	[MAX_DATA_PK];

int			stats_nb_data_pk 		= 0;
int			stats_nb_data_pk_down	= 0;
int			stats_nb_data_pk_up		= 0;







//----------------------------------------------------------------------
//						Functions Prototypes
//----------------------------------------------------------------------

//Packet
Boolean addr_pk_id_not_seen (int addr , int pk_id);
void 	pk_send_delayed(Packet* pkptr , double delay);
void 	pk_send(Packet* pkptr);
void 	add_address_id_couple(int addr , int pk_id);

//Debug
void 	print_routing_table();
void 	print_ack_table();
void 	mewlana_debug(char* msg);
void 	mewlana_ap_reg(char* msg);
void 	mewlana_up(char* msg);
void 	mewlana_down(char* msg);
void 	mewlana_test(char* msg);


//Routing Table
void 	add_routing_entry (int dest, int relay , short hops , double timeout , Boolean ap , Boolean bidirect , Boolean force_replace);
void 	delete_timeout_in_routing_table ();
int 	get_relay_in_routing_table (int dest);

//Acks
void	add_unicast_ack(int dest , int pk_id , Packet* pkptr);

//Hellos
void 	update_neighbors (Packet* pkptr);

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
	int	                    		my_address;
	Boolean	                		is_AP;
	short	                  		DEBUG;
	int	                    		current_id;
	int	                    		my_stat_id;
	List*	                  		addr_pk_id_list;
	List*	                  		ack_table;
	int	                    		current_ap_hello_id;
	int	                    		my_ap;
	Boolean	                		debug_ap_reg;
	Boolean	                		debug_data;
	Boolean	                		debug_load;
	int	                    		nb_connections;
	List*	                  		ici_list;
	int	                    		data_pk_size;
	List*	                  		routing_table;
	} mewlana_process_state;

#define pr_state_ptr            		((mewlana_process_state*) SimI_Mod_State_Ptr)
#define my_address              		pr_state_ptr->my_address
#define is_AP                   		pr_state_ptr->is_AP
#define DEBUG                   		pr_state_ptr->DEBUG
#define current_id              		pr_state_ptr->current_id
#define my_stat_id              		pr_state_ptr->my_stat_id
#define addr_pk_id_list         		pr_state_ptr->addr_pk_id_list
#define ack_table               		pr_state_ptr->ack_table
#define current_ap_hello_id     		pr_state_ptr->current_ap_hello_id
#define my_ap                   		pr_state_ptr->my_ap
#define debug_ap_reg            		pr_state_ptr->debug_ap_reg
#define debug_data              		pr_state_ptr->debug_data
#define debug_load              		pr_state_ptr->debug_load
#define nb_connections          		pr_state_ptr->nb_connections
#define ici_list                		pr_state_ptr->ici_list
#define data_pk_size            		pr_state_ptr->data_pk_size
#define routing_table           		pr_state_ptr->routing_table

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	mewlana_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   NEIGHBORHOOD
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


static void hello (){
	//Packet
	Packet*				pkptr;
	//Routing Table
	routing_entry*		entry;	
	//For each Neighbors in apcket
	int					field_num = 0;
	char				field_name[20];	
	//Control
	char				msg[150];
	int					i;
	
	
	pkptr = op_pk_create_fmt ("mewlana_hello");
	op_pk_nfd_set(pkptr,"SRC",			my_address);
	op_pk_nfd_set(pkptr,"DEST",			-1);
	op_pk_nfd_set(pkptr,"PK_ID",		current_id++);
	op_pk_nfd_set(pkptr,"TTL",			1);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",	HELLO_PK_TYPE);
		
		
	if (DEBUG>4) 
		{
			sprintf(msg,"I send an hello (id=%d) at %f\n",current_id,op_sim_time());
			mewlana_debug (msg);
		}		
	//We add all 1-neighbors
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (routing_entry*) op_prg_list_access (routing_table , i);
			if (entry->hops == 1)
				{
					sprintf (field_name, "NEIGHBOR_%d",field_num++);
					op_pk_nfd_set(pkptr , field_name , entry->dest);
				}
		}
	
	//"Delete" useless Fields
	sprintf (field_name, "NEIGHBOR_%d",field_num);
	for (i=field_num ;  (i<MAX_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr,field_name))  ; i++)
		{
			op_pk_nfd_strip(pkptr , field_name);
			sprintf (field_name, "NEIGHBOR_%d",i+1);
		}

	/* Send the packet */
	pk_send_delayed(pkptr , op_dist_uniform(0.05) );
	add_address_id_couple(my_address , current_id-1);
	
	//Next Hello
	op_intrpt_schedule_self (op_sim_time() + INTERVALL_HELLO + op_dist_uniform(0.05), HELLO_GENERATE_CODE);
}


void update_neighbors (Packet* pkptr) {
	//Control
	int 			addr_temp;	
	char			msg[150];
	//Info abbout source
	int				src_temp , pk_id_temp;	
	Boolean			is_link_bidirect;	
	//For list of neighbors in packet
	short			field_num;
	char			field_name[20];	
		
	
	//Get Infos
	op_pk_nfd_get(pkptr,"SRC",		&src_temp);
	op_pk_nfd_get(pkptr,"PK_ID",	&pk_id_temp);

	//Bidirection Detection
	is_link_bidirect = OPC_FALSE;
	field_num = 0; 
	addr_temp = 0;
	sprintf(field_name , "NEIGHBOR_%d", field_num);
	while ((field_num < MAX_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr,field_name)) && (!is_link_bidirect) && (addr_temp!=-1))
		{
			op_pk_nfd_get(pkptr , field_name , &addr_temp);
			if (addr_temp == my_address)
				is_link_bidirect = OPC_TRUE;
			sprintf(field_name , "NEIGHBOR_%d", ++field_num);
		}
	
	if (DEBUG>4) 
		{
			sprintf(msg,"I receive an hello from %d (id=%d) at %f -> timeout=%f , bidirect=%d \n",src_temp,pk_id_temp,op_sim_time(),INTERVALL_HELLO * TIMEOUT_HELLO,is_link_bidirect);
			mewlana_debug (msg);
		}	
	
	//Update The Routing Table
	add_routing_entry (src_temp , src_temp , 1 , INTERVALL_HELLO * TIMEOUT_HELLO , OPC_FALSE , is_link_bidirect , OPC_FALSE);
}

//Returns the number of 1-Neighbors
int	count_nb_neighbors(){
	routing_entry*		entry;	
	int					degree=0;
	int					i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(0);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (routing_entry*) op_prg_list_access (routing_table , i);
			if (entry->hops == 1)
				degree++;
		}

	//Returns the value
	return(degree);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		   TOPOLOGY REPRESENTATION (FIGURE GENERATION)
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns a text-formatted number with non significative zeros (i.e. 2 becomes 002)
void format_int_to_string(double src, char* dest, int nb_digits){
	int i;

	//We initialize dest 
	sprintf(dest,"");
	
	//We add non significative zeros (nb digits of src : round( log10(src)+1) ) 
	for(i=0 ; i < nb_digits - ((int)log10(src)+1) ;i++)
		{
			sprintf(dest,"%s%d",dest,0);
		}
	
	//We add the original string 
	sprintf(dest , "%s%f" , dest , src);	
}

//Reinitializes some stats for further writes a new figure
void stats_variable_reinitialization(){
	int 	i , j;

	//NB nodes written
	stats_nb_position_written = 0;		
		
	//Links
	for(i=0 ; i < MAX_NB_NODES ; i++)
		{
			stats_ap_connection [i] = OPC_FALSE;
			for(j=0 ; j < MAX_NB_NODES ; j++)
				stats_links[i][j] = 0;
		}
}

//Writes figures containing the current topology
void write_topology_figures (){
	FILE*			pfile;
	char			msg[500];
	short			color;
	double			x , y , x_max , y_max;		//Positions in Opnet  (floats)
	int				x1 , x2 , y1 , y2 ;			//Positions in figure (integers)
	int				i , j;
	routing_entry*	entry;
	char			filename [150];
	

	//Next Interruption
	op_intrpt_schedule_self(op_sim_time() + 10.0 , WRITE_TOPOLOGY_CODE);
	
	
	//---------------------------------------
	//			GPS Position
	//---------------------------------------	
	if (my_stat_id < MAX_NB_NODES)
		{
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"x position",&x);
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"y position",&y);
			stats_positions	[my_stat_id][0]	= x;
			stats_positions	[my_stat_id][1]	= y;
	   	}
	else
		{
			sprintf(msg,"You must increase MAX_NB_NODES (%d), my_address (%d) is too high\n",MAX_NB_NODES,my_address);
			printf(msg);
			op_sim_end(msg,"","","");
		}
	
	//Nb of nodes which already wrote their position and stats
	stats_nb_position_written++;

	//---------------------------------------
	//			    Links
	//---------------------------------------	
	if (is_AP)
		stats_ap_connection [my_stat_id] = COLOR_AP_CONNECTED;
	else
		stats_ap_connection [my_stat_id] = COLOR_AP_DISCONNECTED;
	if (op_prg_list_size(routing_table)!=0)
		{
			for (i=0; i < op_prg_list_size(routing_table) ; i++)
				{
					//Links
					entry = (routing_entry*) op_prg_list_access(routing_table , i);
					if (entry->hops == 1)				
						stats_links[my_stat_id][address_to_stat_id[entry->relay]] = THICKNESS_PHYSIC_NEIGHBOR;
					
					//Stats of Connection to AP (the nodes which received the last ap-hello
					if ((entry->dest <= nb_aps) && (entry->timeout >= op_sim_time() - TIMEOUT_AP_HELLO*INTERVALL_AP_HELLO + INTERVALL_AP_HELLO*1.2))
						stats_ap_connection [my_stat_id] = COLOR_AP_CONNECTED;
				}
		}
	
	//---------------------------------------
	//			Writes Figures
	//---------------------------------------	
		
	//Writes stats if I'm the last node
	if (stats_nb_position_written == nb_nodes)
		{
	
		//---------------------------------------
		//			Mewlana Tree
		//---------------------------------------	
		
			//Opens the associated file and 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results_mewlana/%d_mewlana_topology_tree_%s.fig" , begin_time , msg);
			
			op_ima_sim_attr_get(OPC_IMA_DOUBLE , "X_MAX" , &x_max);
			op_ima_sim_attr_get(OPC_IMA_DOUBLE , "Y_MAX" , &y_max); 
			pfile = fopen(filename,"w");
			if (pfile==NULL)
				{
					printf("Error : we cannot create the file %s\n",filename);
				}
		
			//--------
			//Headers
			//--------
			fprintf(pfile,"#FIG 3.2 \n#Snapshot of The Network Topology for Mewlana \nLandscape \nCenter \nInches \nA4 \n100.00 \nSingle \n-2 \n1200 2 \n");						
			fprintf(pfile,"1 3 0 1 0 0 50 -1 15 0.000 1 0.000 0 0 1 1 0 0 0 0\n");
			
			//---------------
			//Nodes Position
			//---------------
			fprintf(pfile,"#NODE POSITIONS AND ADDRESSES\n");
			for(i=0;i<nb_nodes;i++)
				{	
					//Circle to represent the node
					color = stats_ap_connection [i] ;
					sprintf(msg,"1 3 0 1 0 %d 50 -1 15 0.000 1 0.000 %d %d 100 100 0 0 0 0\n",color,(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),(int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX)));
					fprintf(pfile,msg);
					
					//Address associated to this node
					sprintf(msg,"4 0 0 50 -1 0 15 0.0000 4 135 135 %d %d %d\\001\n",80+(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),-20+(int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX)),stat_id_to_address[i]);
					fprintf(pfile,msg);
				}
			
			//------
			//Links
			//------
			fprintf(pfile,"#LINKS\n");
			for(i=0;i<nb_nodes;i++)
				{
					for(j=0;j<nb_nodes;j++)
						{
							if (stats_links[i][j]!=0)
								{
									//Coordinates of the source and destination of link
									x1 = (int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX));
									y1 = (int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX));
									
									x2 = (int)(stats_positions[j][0]/(x_max/GRAPHIC_XMAX));
									y2 = (int)(stats_positions[j][1]/(x_max/GRAPHIC_XMAX));
									
									color = 10;
									sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 0 0 2\n			%d %d %d %d\n			0.000 0.000\n",stats_links[i][j],x1,y1,x2,y2);
									//With an arrow
									//sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 1 0 2\n			1 1 %f 120.00 240.00\n			%d %d %d %d\n			0.000 0.000\n",stats_links[i][j],(double)stats_links[i][j]/2,x1,y1,x2,y2);
									fprintf(pfile,msg);
								}								
						}
				}
			
			//--------
			//Footers
			//--------
			fclose(pfile);
			
			
			
		//---------------------------------------
		//			END
		//---------------------------------------	
		
			stats_variable_reinitialization();
		}
	}	
	

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//							AP HELLOS / REGISTRATION
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//Genereates an ap_hello, sent in broadcast
void ap_hello(){
	Packet*		pkptr;
	char		msg[150];
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("mewlana_pk_ap_hello");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SRC" ,			my_address);
	op_pk_nfd_set (pkptr, "SRC_INIT" ,		my_address);
	op_pk_nfd_set (pkptr, "ID_AP" ,			my_address);
	op_pk_nfd_set (pkptr, "DEST" ,			BROADCAST);
	op_pk_nfd_set (pkptr, "HOPS" ,			0);
	op_pk_nfd_set (pkptr, "TTL" ,			MAX_NETWORK_RADIUS);
	op_pk_nfd_set (pkptr, "OPTION_TYPE" ,	AP_HELLO_PK_TYPE);
	op_pk_nfd_set (pkptr, "PK_ID" ,			current_ap_hello_id++);

	//Sends it
	pk_send(pkptr);
	
	//Stats
	if (stats_nb_ap_hello >= MAX_AP_HELLO_PK)
		op_sim_end("We have too many ap-hellos-flooded to treat for statistics","please increase the value of MAX_AP_HELLO_PK","in the header block of the mewlana process","");
	stats_nb_ap_hello++;
	
	//Next ap-hello
	op_intrpt_schedule_self( op_sim_time() + INTERVALL_AP_HELLO , AP_HELLO_GENERATE_CODE);
	if (DEBUG>1)
		{
			sprintf(msg,"------- %d sent an ap-hello at %f ---------\n",my_address,op_sim_time());
			mewlana_ap_reg(msg);
			sprintf(msg,"I sent an ap-hello at %f\n",op_sim_time());
			mewlana_debug(msg);
		}
}

//Sends an AP registration
void ap_registration_generate(int id_ap, int ap_hello_pk_id){
	Packet*		pkptr;
	int			next_hop;
	char		msg[200];
	double		delay;
	
	//Finds the next hop torward the AP
	next_hop = get_relay_in_routing_table(id_ap);
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("mewlana_pk_ap_hello");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SRC" ,			my_address);
	op_pk_nfd_set (pkptr, "SRC_INIT" ,		my_address);
	op_pk_nfd_set (pkptr, "ID_AP" ,			id_ap);
	op_pk_nfd_set (pkptr, "DEST" ,			next_hop);
	op_pk_nfd_set (pkptr, "HOPS" ,			0);
	op_pk_nfd_set (pkptr, "TTL" ,			MAX_NETWORK_RADIUS);
	op_pk_nfd_set (pkptr, "OPTION_TYPE" ,	AP_REGISTRATION_PK_TYPE);
	op_pk_nfd_set (pkptr, "PK_ID" ,			ap_hello_pk_id);

	//Delay
	delay = op_dist_uniform(0.3);
	
	//Stats
	stats_ap_reg		[ap_hello_pk_id][my_stat_id][0] = my_address;
	stats_ap_reg_time	[ap_hello_pk_id][my_stat_id][0] = op_sim_time() + delay;	
	
	//Sends it (after registration in the retranmission list)
	if (ACK_FOR_AP_REG)
		add_unicast_ack(next_hop , ap_hello_pk_id , pkptr);
	pk_send_delayed (pkptr , delay );
	
	if (DEBUG>1)
		{
			sprintf(msg,"INIT : %d registers itself to the AP via %d at %f (pk_id %d)\n", my_address , next_hop , op_sim_time()+delay , ap_hello_pk_id);
			mewlana_ap_reg(msg);		
		}
	if (DEBUG>5)
		{
			sprintf(msg,"AP_REGISTRATION : I register myself to the AP at %f (pk id %d)\n", op_sim_time()+delay , ap_hello_pk_id);
			mewlana_debug(msg);		
		}
}

//Returns 1 if an AP is registered in my routing table
Boolean is_my_ap_valid(){
	int				i = 0;
	routing_entry*	entry;
	
	//I am an AP
	if (is_AP)
		return (OPC_TRUE);
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (OPC_FALSE);
	
	//Search if the entry already exists
	while (i< op_prg_list_size(routing_table))
		{
			entry = (routing_entry*) op_prg_list_access (routing_table, i);
			if (entry->dest <= nb_aps)
				return (OPC_TRUE);
			i++;
		}
	
	//No entry corresponding to an AP was found	
	return (OPC_FALSE);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								PACKETS COMMON
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//Add a new Ici in the ici_list
Ici* add_in_ici_list(){
	struct_ici*		entry;
	
	//Memory allocation (to have a valid entry outside this function)
	entry = (struct_ici*) op_prg_mem_alloc ( sizeof (struct_ici));
	
	//Info
	entry->ici_ptr		= op_ici_create("mac_dest_indication");
	entry->timeout		= op_sim_time() + TIMEOUT_ICI ;
	
	//Insert it
	op_prg_list_insert(ici_list , entry , OPC_LISTPOS_TAIL);	
	
	//Return the Ici
	return(entry->ici_ptr);
}

//Delete timeouted entries
void delete_timeout_in_ici_list(){
	int				i = 0;
	struct_ici*		entry;
	
	if (ici_list == NULL)
		op_sim_end("We have an error :" , "the ici list is a null list" , "please initialize it","");

	//If the list is empty
	if (op_prg_list_size(ici_list)==0)
		return;
	
	//For each entry
	while (i< op_prg_list_size(ici_list))
		{
			entry = (struct_ici*) op_prg_list_access (ici_list, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout < op_sim_time())
				{
					op_prg_list_remove ( ici_list , i);
					free(entry);
				}
			else
				i++;
		}
}

//Returns 1 if the packet comes from a bidirectional link
Boolean is_link_bidirect (int address){
	routing_entry	*entry;
	int				i;
	
	//No declared Neighbor
	if (op_prg_list_size(routing_table)==0)
		return (OPC_FALSE);
	
	//For each entry of the routing table
	for (i=0; i < op_prg_list_size(routing_table) ; i++)
		{
			entry = (routing_entry*) op_prg_list_access (routing_table, i);
			
			if ((entry->dest == address) && (entry->hops==1) && (entry->bidirect))
				return (OPC_TRUE);
		}
	
	//Not Found
	return (OPC_FALSE);
}

//Deletes all entries that are timeouted
void delete_timeout_in_addr_pk_id_list(){
	int					i = 0;
	addr_pk_id_couple*	entry;
	char				msg[150];
	
	//If the list is empty
	if (op_prg_list_size(addr_pk_id_list)==0)
		return;
	
	//Search if the entry already exists
	while (i< op_prg_list_size(addr_pk_id_list))
		{
			entry = (addr_pk_id_couple*) op_prg_list_access (addr_pk_id_list, i);
			
			//We delete the entry
			if (entry->timeout < op_sim_time())
				{				
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ID-TABLE : deletes the address %d with pk_id %d with timeout %f at %f\n", entry->address , entry->pk_id , entry->timeout , op_sim_time());
							mewlana_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( addr_pk_id_list , i);
					free(entry);
				}
			else
				i++;
		}
}

//=1 if that packet was already seen, 0 else
Boolean addr_pk_id_not_seen (int addr , int pk_id) {
	int					i=0;
	addr_pk_id_couple*	couple;
	
	//For each entry of the list ...
	for(i=0; i< op_prg_list_size(addr_pk_id_list);i++)
		{  
			couple = (addr_pk_id_couple*) op_prg_list_access(addr_pk_id_list,i);
			//.....compare it
			if ((couple->address == addr) && (couple->pk_id == pk_id))
				return(OPC_FALSE);
		}
	return (OPC_TRUE);
}

//Adds this packet as already seen
void add_address_id_couple(int addr , int pk_id){
	addr_pk_id_couple*		couple;
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (addr_pk_id_couple*) malloc ( sizeof (addr_pk_id_couple));
	
	//Info
	couple->address 	= addr;
	couple->pk_id		= pk_id;
	couple->timeout		= op_sim_time() + TIMEOUT_ADDR_PK_ID;
	
	//Insert it
	op_prg_list_insert( addr_pk_id_list, couple, OPC_LISTPOS_TAIL);	
}


//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void stats_about_control_pk_flows(Packet* pkptr){
	char	msg[50];
	int		option_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
	
	//Total nb of packets
	nb_pk_instantaneous++;
	nb_pk_total++;
	
	//Gets the type associated to the option_type
	switch (option_type)
		{
			case AP_HELLO_PK_TYPE :
				type = AP_HELLO;
			break;
			case AP_REGISTRATION_PK_TYPE :
				type = AP_REGISTRATION;
			break;
			case UNICAST_ACK_PK_TYPE :
				type = UNICAST_ACK;
			break;
			case HELLO_PK_TYPE :
				type = HELLO;
			break;
			case DATA_PK_TYPE :
				type = DATA;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case AP_HELLO :
				nb_pk_ap_hello_instantaneous++;
				nb_pk_ap_hello_total++;
			break;
			case AP_REGISTRATION :
				nb_pk_ap_registration_instantaneous++;
				nb_pk_ap_registration_total++;
			break;
			case UNICAST_ACK :
				nb_pk_unicast_ack_instantaneous++;
				nb_pk_unicast_ack_total++;
			break;
			case HELLO :
				nb_pk_hello_instantaneous++;
		   		nb_pk_hello_total++;
			break;
			case DATA :
				nb_pk_data_instantaneous++;
				nb_pk_data_total++;
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void stats_about_control_pk_flows_retransmission(Packet* pkptr){
	char	msg[50];
	int		option_type;
	int		type;
	
	//Total nb of packets
	nb_pk_retransmission_instantaneous++;
	nb_pk_retransmission_total++;

	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
	
	//Gets the type associated to the option_type
	switch (option_type)
		{
			case AP_HELLO_PK_TYPE :
				type = AP_HELLO;
			break;
			case AP_REGISTRATION_PK_TYPE :
				type = AP_REGISTRATION;
			break;
			case DATA_PK_TYPE :
				type = DATA;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case AP_HELLO :
				nb_pk_ap_hello_retransmission_instantaneous++;
				nb_pk_ap_hello_retransmission_total++;
			break;
			case AP_REGISTRATION :
				nb_pk_ap_registration_retransmission_instantaneous++;
				nb_pk_ap_registration_retransmission_total++;
			break;
			case DATA :
				nb_pk_data_retransmission_instantaneous++;
				nb_pk_data_retransmission_total++;
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}


//Sends the packet with the specified delay
void pk_send_delayed(Packet* pkptr , double delay){
	int		dest;
	int		pk_type;
	Ici*	ici_ptr;
	char	msg[200];

	//Stats
	stats_about_control_pk_flows(pkptr);
	
	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", 			&dest);
	op_pk_nfd_get (pkptr, "OPTION_TYPE",	&pk_type);

	if (pk_type == DATA_PK_TYPE)
		{
			sprintf(msg,"data from %d to %d\n",my_address, dest);
			mewlana_test(msg);
		}
	
	//Ici Management
	if (PROMISCUOUS_FOR_UNICAST)
		dest = -1;
	
	//Ici installation
	ici_ptr = add_in_ici_list();
	op_ici_install(ici_ptr);
	op_ici_attr_set(ici_ptr,"dest_addr", dest);
	
	//Sends it
	op_pk_send_delayed(pkptr , STRM_TO_WLAN , delay);
}

//Sends the packet without delay
void pk_send (Packet* pkptr){
	pk_send_delayed(pkptr , 0);
}


//Retransmits the packet with the specified delay
void pk_retransmit_delayed(Packet* pkptr , double delay){
	int		dest;
	//int		pk_type;
	Ici*	ici_ptr;
	//char	msg[200];
	
	//Stats
	stats_about_control_pk_flows_retransmission(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", 			&dest);

	//Ici Management
	if (PROMISCUOUS_FOR_UNICAST)
		dest = -1;
	
	//Ici installation
	ici_ptr = add_in_ici_list();
	op_ici_install(ici_ptr);
	op_ici_attr_set(ici_ptr,"dest_addr", dest);
	
	//Sends it
	op_pk_send_delayed(pkptr, STRM_TO_WLAN,delay);
}

//Retransmits the packet without delay
void pk_retransmit (Packet* pkptr){
	pk_retransmit_delayed(pkptr , 0);
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								Acknowledgements
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//This packet must be further acknowledged
void add_unicast_ack(int dest , int pk_id , Packet* pkptr){
	ack_couple*		couple;
	char			msg[150];
	
	sprintf(msg, "ack insere par %d a %f\n", my_address , op_sim_time());
	mewlana_up(msg);
	print_ack_table();
	
	//If the list is empty, we must schedule the must verification of timeouts in ack_table (else it is already scheduled)
	if (op_prg_list_size (ack_table) == 0)
		op_intrpt_schedule_self (op_sim_time() + TIMEOUT_UNICAST_ACK , UNICAST_RETRANSMISSIONS_CODE);
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (ack_couple*) malloc ( sizeof (ack_couple));
	
	//Info
	couple->dest		= dest;
	couple->pk_id		= pk_id;
	couple->nb_retry	= 0;
	couple->timeout 	= op_sim_time() + TIMEOUT_UNICAST_ACK ;
	couple->pkptr		= op_pk_copy(pkptr);
	
	//Insert it
	op_prg_list_insert( ack_table , couple , OPC_LISTPOS_TAIL);	
}

//This packet must be further acknowledged
void delete_unicast_ack(int dest , int pk_id){
	ack_couple*		couple;
	char			msg[200];
	int				i;
	//Info from packet for debug purpose
	int				pk_type , dest_final;
	int				nb_entry_del = 0;
	
	print_ack_table();
	
	//If the list is empty -> I exit !
	if (op_prg_list_size(ack_table)==0)
		{
			if (DEBUG>1)
				{
					sprintf(msg, "ACKS : the entry corresponding to the id_pk %d to destination %d was not found at %f\n", pk_id , dest , op_sim_time());
					mewlana_debug (msg);
				}
			return ;
		}
	
	//For each entry
	for (i = op_prg_list_size(ack_table)-1 ; i >=0 ; i--)
		{
			//gets the entry
			couple = (ack_couple*) op_prg_list_access (ack_table, i);
			
			if ((couple->dest == dest) && (couple->pk_id == pk_id))
				{
					if (DEBUG>1)
						{
							op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
							op_pk_nfd_get(couple->pkptr, "DEST_FINAL", 	&dest_final);
							if (pk_type == DATA_PK_TYPE)
								{
									sprintf(msg, "ACKS : %d acked the packet with id_pk %d at %f\n", dest , pk_id , op_sim_time());
									if (dest_final <= nb_aps)
										mewlana_up(msg);
									else
										mewlana_down(msg);
								}
							else if (pk_type == AP_REGISTRATION_PK_TYPE)
								mewlana_ap_reg(msg);
							//Per node
							sprintf(msg, "ACKS : %d acked the packet with id_pk %d at %f\n", dest , pk_id , op_sim_time());
							mewlana_debug (msg);
						}
					op_prg_list_remove(ack_table, i);
					free(couple);
					nb_entry_del++;
				}
		}
	
	if (DEBUG>0)
		{
			sprintf(msg, "ACKS : %d entries (with id_pk %d to destination %d) were found at %f\n", nb_entry_del , pk_id , dest , op_sim_time());
			mewlana_debug (msg);
		}	
}

//Sends an unicast ack
void acknowledges_unicast_packet(int address , int pk_id){
	char		msg[150];
	Packet*		pkptr;
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("mewlana_pk_unicast_ack");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SRC" ,			my_address);
	op_pk_nfd_set (pkptr, "SRC_INIT" ,		my_address);
	op_pk_nfd_set (pkptr, "DEST" ,			address);
	op_pk_nfd_set (pkptr, "TTL" ,			1);
	op_pk_nfd_set (pkptr, "OPTION_TYPE" ,	UNICAST_ACK_PK_TYPE);
	op_pk_nfd_set (pkptr, "PK_ID" ,			pk_id);

	//Sends it
	pk_send_delayed(pkptr , op_dist_uniform(0.001));
	
	if (DEBUG>1)
		{
			sprintf(msg,"ACKS : we send an active ack to %d (for pk-id %d) at %f\n", address , pk_id , op_sim_time());
			mewlana_debug(msg);
		}
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTING
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns the number of bidirectionnal entries in the routing table
int	count_nb_bidirect_entries_in_routing_table(){
	routing_entry*		entry;	
	int					nb	= 0;
	int					i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(0);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (routing_entry*) op_prg_list_access (routing_table , i);
			if (entry->bidirect)
				nb++;
		}

	//Returns the value
	return(nb);	
}

//Delete all entries in routing table that overcome the timeout
void delete_timeout_in_routing_table (){
	int				i = 0;
	routing_entry*	entry;
	char			msg[150];
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return;
	
	//Search if the entry already exists
	while (i< op_prg_list_size(routing_table))
		{
			entry = (routing_entry*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if (entry->timeout < op_sim_time())
				{				
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ROUTING-TABLE : deletes the relay %d toward %d (hops=%d), with timeout %f at %f\n", entry->relay , entry->dest , entry->hops , entry->timeout , op_sim_time());
							mewlana_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( routing_table , i);
					free(entry);
				}
			else
				i++;
		}
}


//Returns the timeout time associated to one entry (-1 if no entry was found)
double timeout_routing_entry (int address){
	int				i ;
	routing_entry*	entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			entry = (routing_entry*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if (entry->dest == address)
				return (entry->timeout);
		}
	
	//No corresponding entry was found
	return(-1);
}


//Adds an entry in the routing table :
// ->If one exists and is farther, we update with the new information
// ->If none exists, we add it
void add_routing_entry (int dest, int relay , short hops , double timeout , Boolean ap , Boolean bidirect , Boolean force_replace){
	int				i = 0;
	routing_entry*	entry;
	char			msg[350];
	
	//Search if the entry already exists
	while ((op_prg_list_size(routing_table)!=0) && (i< op_prg_list_size(routing_table) ))
		{
			entry = (routing_entry*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if ((entry->dest == dest) && ((entry->hops >= hops) || (force_replace)))
				{
					//Updates info
					entry->relay	= relay;
					entry->hops		= hops;					
					entry->timeout 	= op_sim_time() + timeout;				
					entry->ap		= ap;
					entry->bidirect	= bidirect;
					
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ROUTING-TABLE : updates the relay %d toward %d (hops=%d), at %f\n", entry->relay , entry->dest , entry->hops , op_sim_time());
							mewlana_debug(msg);
						}				
					
					//That's all
					return;
				}
			
			//The entry is not acceptable -> too far
			if ((entry->dest == dest) && (entry->hops < hops))
				return;
			i++;
		}
	
	//The entry was not found
	//Memory allocation
	entry = (routing_entry*) malloc (sizeof(routing_entry));
			
	//Info
	entry->dest		= dest;
	entry->relay	= relay;
	entry->hops		= hops;
	entry->ap		= ap;
	entry->bidirect = bidirect;
	entry->timeout 	= op_sim_time() + timeout;		
	
	//DEBUG
	if (DEBUG>5)
		{
			sprintf(msg,"ROUTING-TABLE : adds the relay %d toward %d (hops=%d), at %f\n", entry->relay , entry->dest , entry->hops , op_sim_time());
			mewlana_debug(msg);
		}
	
	//I add it in the list
	op_prg_list_insert( routing_table, entry, OPC_LISTPOS_TAIL);	
}

//Looks for the relay toward a destination (returns -1 if none was found)
int get_relay_in_routing_table(int dest){
	int				i = 0;
	routing_entry*	entry;
	char			msg[350];
	
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(routing_table) ; i++)
		{
			entry = (routing_entry*) op_prg_list_access (routing_table, i);
			if ((entry!=NULL) && (entry->dest == dest) && (entry->bidirect))				
				{
					//DEBUG
					if (DEBUG>4)
						{
							sprintf(msg,"ROUTING : I find the relay %d toward %d (%d hops far) at %f\n", entry->relay , entry->dest , entry->hops , op_sim_time());
							mewlana_debug(msg);
						}

					return (entry->relay);
				}
	}
		
	//DEBUG
	if (DEBUG>1)
		{
			sprintf(msg,"ROUTING : I didn't find any relay toward %d at %f\n", dest , op_sim_time());
			mewlana_debug(msg);
		}		
		
	//No valid entry found	
	return(-1);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								DATA
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void schedule_data_pk(int dest_final , int code){
	Packet*		pkptr;
	char		msg[300];
	int			next_hop;

	//The next hop (in routing table)
	next_hop = get_relay_in_routing_table(dest_final);		

	//INCOMING PACKET 
	pkptr = op_pk_create_fmt ("mewlana_pk_data");
	op_pk_total_size_set ( pkptr, 8 * data_pk_size);
	op_pk_nfd_set (pkptr, "SRC_INIT", 	my_address);
	op_pk_nfd_set (pkptr, "SRC", 		my_address);
	op_pk_nfd_set (pkptr, "DEST_FINAL",	dest_final);
	op_pk_nfd_set (pkptr, "DEST",		next_hop);
	op_pk_nfd_set (pkptr, "PK_ID", 		current_id++);
	op_pk_nfd_set (pkptr, "STAT_ID", 	stats_nb_data_pk);
	op_pk_nfd_set (pkptr, "TTL", 		MAX_NETWORK_RADIUS);
	op_pk_nfd_set (pkptr, "OPTION_TYPE",DATA_PK_TYPE);

	//STATS
	stats_data_pk	[stats_nb_data_pk].source			= my_address;
	stats_data_pk	[stats_nb_data_pk].dest				= dest_final;
	stats_data_pk 	[stats_nb_data_pk].time_emission	= op_sim_time();
	stats_data_pk	[stats_nb_data_pk].pk_size			= (int) op_pk_total_size_get(pkptr);
	stats_data_pk 	[stats_nb_data_pk].type				= is_AP;
	stats_data_pk 	[stats_nb_data_pk].error_from_src	= (next_hop == -1);

	//Debug Messages
	if (DEBUG>1)
		{
			sprintf(msg,"\n\n-------- DATA sent from %d at %f to %d via %d --------\n" , my_address , op_sim_time() , dest_final , next_hop);
			if (is_AP)
				mewlana_down(msg);
			else
				mewlana_up(msg);		
			sprintf(msg, "DATA : I send a data packet toward %d, via %d (pk_id %d, stat_id %d) at %f\n", dest_final , next_hop, current_id-1 ,stats_nb_data_pk , op_sim_time());
			mewlana_debug (msg);
		}

	//Acks + Transmission
	if (next_hop!=-1)
		{
			if (ACK_FOR_DATA)
				add_unicast_ack(next_hop , current_id-1 , pkptr);
			add_address_id_couple(my_address , stats_nb_data_pk);
			pk_send(pkptr);
		}
		
	//Control
	stats_nb_data_pk++;
	if (is_AP)
		stats_nb_data_pk_down++;
	else
		stats_nb_data_pk_up++;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								DEBUG
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void mewlana_ap_reg(char* msg){
	FILE*	file;
	char	str[100];
	
	if  (!debug_ap_reg)
		return;
	
	sprintf(str,"results_mewlana/%d_mewlana_ap_registration.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void mewlana_down(char* msg){
	FILE*	file;
	char	str[100];
	
	if  (!debug_data)
		return;
	
	sprintf(str,"results_mewlana/%d_mewlana_data_download.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void mewlana_up(char* msg){
	FILE*	file;
	char	str[100];
	
	if  (!debug_data)
		return;
	
	sprintf(str,"results_mewlana/%d_mewlana_data_upload.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void mewlana_test(char* msg){
	FILE*	file;
	char	str[100];
	
	if  (!debug_data)
		return;
	
	sprintf(str,"results_mewlana/%d_mewlana_test.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void mewlana_debug(char* msg){
	FILE*	file;
	char	str[100];
	
	if (my_address<10)
		sprintf(str,"results_mewlana/details_per_node/results_0%d.txt",my_address);
	if (my_address>=10)
		sprintf(str,"results_mewlana/details_per_node/results_%d.txt",my_address);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void print_addr_pk_id_list(){
	int					i=0;
	addr_pk_id_couple*	couple;
	char				msg[150];
	
		
	//Common Information
	mewlana_debug ("-------------------------------------------------------------------------\n");
	mewlana_debug ("ID TABLE :\n");		
	mewlana_debug ("-------------------------------------------------------------------------\n\n");
	
	mewlana_debug ("Source	|   Pk Id	|	Timeout \n");
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(addr_pk_id_list)==0)
		{
			mewlana_debug ("\n\n\n");
			return ;
		}	
	
	//For each entry of the list
	for(i=0; i< op_prg_list_size(addr_pk_id_list);i++)
		{  
			couple = (addr_pk_id_couple*) op_prg_list_access(addr_pk_id_list,i);
			//.....compare it
			sprintf(msg,"	%d	|	%d	|	%f\n",couple->address , couple->pk_id , couple->timeout);
			mewlana_debug(msg);
		}
}

void print_routing_table(){
	routing_entry*		entry;
	int					i;
	char				msg[200];
	
	//Updates the table
	delete_timeout_in_routing_table();
		
	//Common Information
	mewlana_debug ("-------------------------------------------------------------------------\n");
	mewlana_debug ("ROUTING TABLE :\n");		
	mewlana_debug ("-------------------------------------------------------------------------\n\n");
	
	mewlana_debug ("Destination	|   Relay	|   Hops	|     Bidirect	|	Timeout \n");
	
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(routing_table)==0)
		{
			mewlana_debug ("\n\n\n");
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(routing_table) ; i++)
		{
			//gets the entry
			entry = (routing_entry*) op_prg_list_access (routing_table, i);

			//Useless, but avoid a 'memory access error' if there is a bug
			if (entry!=NULL)
				{
					//Prints it
					sprintf(msg,"	%d	|	%d	|	%d	|	   %d		|	%f \n" , entry->dest , entry->relay , entry->hops , entry->bidirect , entry->timeout);
					mewlana_debug (msg);
				}
		}
	mewlana_debug ("\n\n\n");
}



void print_ack_table(){
	ack_couple*		entry;
	int				i;
	char			msg[200];
		
	//Common Information
	mewlana_debug ("-------------------------------------------------------------------------\n");
	mewlana_debug ("ACK TABLE :\n");		
	mewlana_debug ("-------------------------------------------------------------------------\n\n");
	
	mewlana_debug ("Destination	|   Pk_id	|	Nb Retries	|     Timeout \n");
	
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(ack_table)==0)
		{
			mewlana_debug ("\n\n\n");
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(ack_table) ; i++)
		{
			//gets the entry
			entry = (ack_couple*) op_prg_list_access (ack_table, i);

			//Useless, but avoid a 'memory access error' if there is a bug
			if (entry!=NULL)
				{
					//Prints it
					sprintf(msg,"	%d	|	%d	|		%d	|	%f \n" , entry->dest , entry->pk_id , entry->nb_retry , entry->timeout);
					mewlana_debug (msg);
				}
		}
	mewlana_debug ("\n\n\n");
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								STATISTICS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//----------------------------------------------------------------
//				Individual Final Stats
//----------------------------------------------------------------

void individual_statistics_generate(){
	char	msg[250];
	
	
	sprintf(msg,"\n\n---------------------- END - %f seconds -------------------------\n\n\n",op_sim_time());
	mewlana_debug(msg);
	
	print_routing_table();	
	print_ack_table();
	print_addr_pk_id_list();
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
	void mewlana_process (void);
	Compcode mewlana_process_init (void **);
	void mewlana_process_diag (void);
	void mewlana_process_terminate (void);
	void mewlana_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
mewlana_process (void)
	{
	int _block_origin = 0;
	FIN (mewlana_process ());
	if (1)
		{
		/* Variables used in state transitions.		*/
		int			intrpt_code;


		FSM_ENTER (mewlana_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (Init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "Init", "mewlana_process () [Init enter execs]")
				{
				//Addresses
				int			addr_attribution;
				char		str[500];
				
				
				
				//Synchronisation with lower levels
				op_intrpt_schedule_self(op_sim_time() + TIME_INIT_MAC,0);
				
				//Gets the time of simulation beginning
				if (begin_time==0)
					begin_time = time(NULL);
				
				//----------------------------------------------------
				//
				//					My address
				//
				//-----------------------------------------------------
				
				op_ima_obj_attr_get(op_id_self(),"Address_Attribution",&addr_attribution); 
				switch(addr_attribution){
						case ADDR_RANDOM :
							//I pick-up my wlan mac address
							op_ima_obj_attr_get(op_topo_parent(op_id_self()),"Wireless LAN MAC Address",&my_address);
							my_address = nb_aps + 1 + op_dist_uniform(LOWER_ADDR_FOR_MULTICAST - nb_aps);
							op_ima_obj_attr_set(op_id_self(),"My_Address",my_address); 	
						break;
						
						case ADDR_WLAN :
							op_ima_obj_attr_get(op_topo_parent(op_id_self()),"Wireless LAN MAC Address",&my_address);
							op_ima_obj_attr_set(op_id_self(),"My_Address",my_address); 	
						break;
						
						case ADDR_CONFIGURED :
							op_ima_obj_attr_get(op_id_self(),"My_Address",&my_address); 	
						break;
						
						case ADDR_MAC_CDCL_FROM_NAME :
							op_ima_obj_attr_get(op_topo_parent(op_id_self()) , "name" , str);
							my_address = atoi(str);
							op_ima_obj_attr_set(op_topo_parent(op_id_self()),"Wireless LAN MAC Address", my_address);
							op_ima_obj_attr_set(op_id_self() , "My_Address" , my_address); 	
						break;
						
						default :
							op_sim_end("The address auto-configuration is not well-configured" , "", "", "");
						break;
					}
				if (my_address==0)
					op_sim_end("Error : we have a null address","Probable Problem with random address and/or with Mac and Ad-hoc Addresses cohabitation) \n","","");
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,mewlana_process)


			/** state (Init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "Init", "mewlana_process () [Init exit execs]")
				{
				}


			/** state (Init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Init", "INIT_AFTER_MAC")
				/*---------------------------------------------------------*/



			/** state (INIT_AFTER_MAC) enter executives **/
			FSM_STATE_ENTER_FORCED (1, state1_enter_exec, "INIT_AFTER_MAC", "mewlana_process () [INIT_AFTER_MAC enter execs]")
				{
				int			addr_attribution;
				char		str[200];
				FILE		*file;
				int 		i,j, addr; 
				char		msg[200];
				//AP Position
				int			process_id , node_id;
				double		XMAX , YMAX;
				int			MOBILITY_MODEL;
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//	Recuperation of simulation parameters
				//
				//-----------------------------------------------------
				
				//The simulation paramaters
				//For this Node
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_CONNECTIONS",	&nb_connections);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG",			&DEBUG);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_AP_REG", 	&debug_ap_reg);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_DATA", 		&debug_data);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_LOAD", 		&debug_load);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DATA_PK_SIZE",		&data_pk_size);
				op_ima_obj_attr_get(op_id_self(),		"Is_AP",			&is_AP); 
				
				if (is_AP)
					nb_aps++;
				
				
				
				
				
				//----------------------------------------------------
				//
				//				General Infos
				//
				//-----------------------------------------------------
				
				//--------------- Various ---------------
				
				current_id 						= op_dist_uniform(30000);				//the first id of the packet I will send
				current_ap_hello_id				= 0;
				
				
				
				
				//----------------------------------------------------
				//
				//				POSITION OF THE AP
				//
				//-----------------------------------------------------
				
				
				
				//The AP is central only if it exists one single AP
				if (is_AP)
					{
						process_id = op_id_self();
						node_id = op_topo_parent (process_id);
						op_ima_sim_attr_get(OPC_IMA_INTEGER, 	"SP_LOW_MOBILITY_MODEL"	, &MOBILITY_MODEL);
						
						//NB : NEITHER_POSITION_NOR_MOBILITY = 5
						if (MOBILITY_MODEL != 5)
							{
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, "X_MAX"  , &XMAX);
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Y_MAX"  , &YMAX);
								op_ima_obj_attr_set(node_id, "x position", XMAX/2);
								op_ima_obj_attr_set(node_id, "y position", YMAX/2);
							}
					}
				
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//		Open the file for out messages
				//
				//-----------------------------------------------------
				
				//protection against arrays overflows
				if (my_address >= MAX_ADDRESS)
					op_sim_end("We have too many nodes","please increase the value of MAX_ADDRESS","in the header block of the mewlana process","");
				if (nb_nodes >= MAX_NB_NODES)
					op_sim_end("We have too many nodes","please increase the value of MAX_NB_NODES","in the header block of the mewlana process","");
				
				
				//----------------------- Stats ---------------------
				my_stat_id = nb_nodes++;							//The first node has id 0
				
				address_to_stat_id	[my_address] = my_stat_id;		//Convert an address into an id
				stat_id_to_address	[my_stat_id] = my_address;		//The inverse
				
				sprintf(list_nodes_without_valid_ap,"");
				
				//--------------------- Per node --------------------
				
				if (my_address<10)
					sprintf(str,"results_mewlana/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
					sprintf(str,"results_mewlana/details_per_node/results_%d.txt",my_address);
				file = fopen(str,"w");
				fclose(file);
				
				
				
				//--------------- Global periodic stats ------------
				
				if (my_stat_id==1)
					{
						for(i=0 ; i < MAX_AP_HELLO_PK ; i++)
							{
								for (j=0; j < MAX_NB_NODES; j++)
									{
										stats_ap_hellos_rcvd [i][j] =0;
									}
							}
						//Stats About Data Packets
						for(i=0; i < MAX_DATA_PK ; i++)
							{
								stats_data_pk [i].source 			= 0;
								stats_data_pk [i].dest 				= 0;
								stats_data_pk [i].pk_size			= 0;
								stats_data_pk [i].hops 				= 0;
								stats_data_pk [i].nb_retry 			= 0;
								stats_data_pk [i].time_emission 	= 0;
								stats_data_pk [i].time_reception 	= 0;
								stats_data_pk [i].error_from_src 	= OPC_FALSE;
							}
						//Stats About AP Registration (delivery ratio...)
						for(i=0; i < MAX_AP_HELLO_PK ; i++)
							{
								for (j=0; j < MAX_NB_NODES ; j++)
									{
										stats_ap_reg[i][j][0] 		= 0;
										stats_ap_reg[i][j][1] 		= 0;
										stats_ap_reg[i][j][2] 		= 0;
										stats_ap_reg_time[i][j][0] 	= 0;
										stats_ap_reg_time[i][j][1]	= 0;
									}
							}
							
						if  (debug_ap_reg)
							{
								sprintf(str,"results_mewlana/%d_mewlana_ap_registration.txt",begin_time);		
								file = fopen(str,"w");
								fclose(file);
							}
						
						if  (debug_data)
							{
								sprintf(str,"results_mewlana/%d_mewlana_data_upload.txt",begin_time);		
								file = fopen(str,"w");
								fclose(file);
				
								sprintf(str,"results_mewlana/%d_mewlana_data_download.txt",begin_time);		
								file = fopen(str,"w");
								fclose(file);
							}
				
						//sprintf(str,"results/%d_mewlana_periodic_stats.txt",begin_time);		
						//file = fopen(str,"w");
						//fclose(file);
						
						if  (debug_load)
							{
								sprintf(str,"results_mewlana/%d_mewlana_network_control.txt",begin_time);
								file = fopen(str,"w");
								fprintf(file , "# Instantaneous Network Control, gathered by packet type\n");
								fprintf(file , "# All flows are in packets per second per node (RET signifies 'Retransmission')\n");
								fprintf(file , "TIME		| 	AP HELLOS	| AP HELLOS RET	| AP REGISTRATIONS| AP REG RET	| 	ACKS		|	HELLO		|	DATA		|	DATA RET	|\n");
								fclose(file);
							}
						
					}
				
				
				
				
				
				//----------------------------------------------------
				//
				//			LISTS INTIALIZATIONS
				//
				//-----------------------------------------------------
				
				
				addr_pk_id_list =  op_prg_list_create();
				addr_pk_id_list =  op_prg_mem_alloc (sizeof(List));
					
				routing_table 	=  op_prg_list_create();
				routing_table 	=  op_prg_mem_alloc (sizeof(List));
				
				ack_table 		=  op_prg_list_create();
				ack_table 		=  op_prg_mem_alloc (sizeof(List));
					
				ici_list		= op_prg_list_create();
				ici_list		= op_prg_mem_alloc (sizeof(List));
								
					
				
				//----------------------------------------------------
				//
				//				INTERRUPTIONS
				//
				//-----------------------------------------------------
				
				if (is_AP)
					op_intrpt_schedule_self (op_sim_time() , AP_HELLO_GENERATE_CODE);
				
				//Periodic Updates
				op_intrpt_schedule_self (op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS , PERIODIC_FUNCTIONS_CODE);
				
				//Hellos
				op_intrpt_schedule_self (op_sim_time() + op_dist_uniform(INTERVALL_HELLO) , HELLO_GENERATE_CODE);
				
				//Topology Figures
				//op_intrpt_schedule_self (op_sim_time() , WRITE_TOPOLOGY_CODE);
				
				//Data Transmission
				if (is_AP)
					for (i=0; i < nb_connections; i++)
						op_intrpt_schedule_self (TIME_BEGIN_NETWORK + op_dist_uniform(INTERVALL_DATA_PK_AP) , PK_DATA_GENERATE_CODE);
				else if (nb_connections > actual_nb_connections)
					{
						op_intrpt_schedule_self (TIME_BEGIN_NETWORK + op_dist_uniform( (double)INTERVALL_DATA_PK_AP / DATA_PK_UPLOAD_RATIO ) , PK_DATA_GENERATE_CODE);
						actual_nb_connections++;
					}
				
				
				}


			/** state (INIT_AFTER_MAC) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "INIT_AFTER_MAC", "mewlana_process () [INIT_AFTER_MAC exit execs]")
				{
				}


			/** state (INIT_AFTER_MAC) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "INIT_AFTER_MAC", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, state2_enter_exec, "idle", "mewlana_process () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,mewlana_process)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "idle", "mewlana_process () [idle exit execs]")
				{
				//printf ("%d - %d - %d - %d - %d\n", op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_SELF, OPC_INTRPT_STRM, OPC_INTRPT_ENDSIM);
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (UNICAST_RETRANSMISSIONS)
			FSM_TEST_COND (PERIODIC_FUNCTIONS)
			FSM_TEST_COND (AP_HELLO_GENERATE)
			FSM_TEST_COND (HELLO_GENERATE)
			FSM_TEST_COND (WRITE_TOPOLOGY)
			FSM_TEST_COND (ENDSIM)
			FSM_TEST_COND (PK_FROM_LOWER)
			FSM_TEST_COND (PK_DATA_GENERATE)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 4, state4_enter_exec, ;, "UNICAST_RETRANSMISSIONS", "", "idle", "RET_UNICAST")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "PERIODIC_FUNCTIONS", "", "idle", "PERIODIC_FUNCONS")
				FSM_CASE_TRANSIT (2, 2, state2_enter_exec, ap_hello();, "AP_HELLO_GENERATE", "ap_hello()", "idle", "idle")
				FSM_CASE_TRANSIT (3, 2, state2_enter_exec, hello();, "HELLO_GENERATE", "hello()", "idle", "idle")
				FSM_CASE_TRANSIT (4, 2, state2_enter_exec, write_topology_figures();, "WRITE_TOPOLOGY", "write_topology_figures()", "idle", "idle")
				FSM_CASE_TRANSIT (5, 5, state5_enter_exec, ;, "ENDSIM", "", "idle", "ENDSIM")
				FSM_CASE_TRANSIT (6, 6, state6_enter_exec, ;, "PK_FROM_LOWER", "", "idle", "FROM_LOWER")
				FSM_CASE_TRANSIT (7, 7, state7_enter_exec, ;, "PK_DATA_GENERATE", "", "idle", "DATA")
				}
				/*---------------------------------------------------------*/



			/** state (PERIODIC_FUNCONS) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "PERIODIC_FUNCONS", "mewlana_process () [PERIODIC_FUNCONS enter execs]")
				{
				//----------------------------------------------------------------
				//				Periodic Functions
				//----------------------------------------------------------------
				
				char	filename[50];
				FILE*	file;
				char	tmp[1000];
				
				
				//Delete all entries which timeout in routing / pk_id / ici table
				delete_timeout_in_routing_table ();
				delete_timeout_in_addr_pk_id_list();
				delete_timeout_in_ici_list();
				
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
				
					 
				//------ STATS Stored in Files -------
				 
						if (my_stat_id+1 == nb_nodes)
							{
							//Periodic general stats
								//File Initialization	
								/*sprintf(filename, "results/%d_mewlana_periodic_stats.txt",begin_time);
								file = fopen (filename, "a");
					
					
								fprintf(file , "\n");
								fclose(file);
							*/
							
							//Periodic stats about network control
								//File Initialization	
								if  (debug_load)
									{
				
										sprintf(filename, "results_mewlana/%d_mewlana_network_control.txt",begin_time);
										file = fopen (filename, "a");
							
										sprintf (tmp, "%f	|", op_sim_time());
										fprintf(file , tmp);
						
										sprintf (tmp, "	%f	|", (double)nb_pk_ap_hello_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_ap_hello_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_ap_hello_retransmission_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_ap_hello_retransmission_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_ap_registration_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_ap_registration_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_ap_registration_retransmission_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_ap_registration_retransmission_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_unicast_ack_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_unicast_ack_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_hello_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_hello_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_data_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_data_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_data_retransmission_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_data_retransmission_instantaneous = 0;
										fprintf(file , tmp);	
					
										fprintf(file , "\n");	
										fclose(file);
									}
							}
				
				
				
				//Global Stats
				
						//Counts the number of nodes Registered currently in AP
						if (is_AP)
							nb_nodes_registered_to_ap += count_nb_bidirect_entries_in_routing_table();
						if ((is_my_ap_valid()) && (!is_AP))
							nb_nodes_which_have_a_valid_ap++;
				
						//Degree
						average_degree +=  count_nb_neighbors();
				
				
				
					}
				
				//Next Stats
				op_intrpt_schedule_self(op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS, PERIODIC_FUNCTIONS_CODE);
				}


			/** state (PERIODIC_FUNCONS) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "PERIODIC_FUNCONS", "mewlana_process () [PERIODIC_FUNCONS exit execs]")
				{
				}


			/** state (PERIODIC_FUNCONS) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "PERIODIC_FUNCONS", "idle")
				/*---------------------------------------------------------*/



			/** state (RET_UNICAST) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "RET_UNICAST", "mewlana_process () [RET_UNICAST enter execs]")
				{
				//retransmissions of all not acknowldged entries
					ack_couple*		couple;
					//Control
					char			msg [500];
					int				i;
					double			older_entry;
					//Random delay before transmitting
					double			delay;
					//Info for/from the packet
					Packet*			pk_dest;
					int				pk_type;
					int				dest_final;
					int				src_init;
					int				stat_id;
				
				sprintf(msg , "%d regarde table ack %d entrees\n" , my_address , op_prg_list_size(ack_table));
				mewlana_up(msg);
				
					//Older entry variable contains the time for which we must schedule an interuption
					older_entry = -1;
					
					//If the ack table is empty, we don't treat it ....
					if (op_prg_list_size(ack_table)!=0)
						{
							//For each entry
							for (i=op_prg_list_size(ack_table)-1 ; i>=0 ; i--)
								{
									//gets the entry
									couple = (ack_couple*) op_prg_list_access (ack_table, i);
							
									//Verifies each entry
									if (couple->timeout <= op_sim_time())
										{
											if (couple->nb_retry < MAX_NB_RETRIES_UNICAST_ACKS)
												{
													//Stats of nb of retransmissions
													op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
													switch (pk_type)
														{
															case DATA_PK_TYPE :
																op_pk_nfd_get(couple->pkptr, "STAT_ID", &stat_id);
																stats_data_pk [stat_id].nb_retry++;
																if (DEBUG>1)
																	{
																		op_pk_nfd_get(couple->pkptr, "DEST_FINAL",&dest_final);
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d (toward %d) with pk_id %d and currently %d retransmissions at %f\n", my_address, couple->dest , dest_final , couple->pk_id , couple->nb_retry+1 , op_sim_time());
																		if(dest_final <= nb_aps)
																			mewlana_up (msg);
																		else
																			mewlana_down (msg);														
																	}
															break;
															case AP_REGISTRATION_PK_TYPE :
																if (DEBUG>1)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , couple->nb_retry+1 , op_sim_time());
																		mewlana_ap_reg (msg);
																	}
																op_pk_nfd_get (couple->pkptr, "SRC_INIT", &src_init);
																stats_ap_reg [couple->pk_id][src_init][3] ++;
															break;
														}
															
												
													//retransmission
													couple->timeout 	= op_sim_time() + TIMEOUT_UNICAST_ACK;
													pk_retransmit_delayed (op_pk_copy(couple->pkptr) , op_dist_uniform(0.001));
											
													//DEBUG
													if (DEBUG>1)
														{
															sprintf(msg, "RETRANSMISSION : we retransmit packet to %d with pk_id %d and currently %d retransmissions at %f\n", couple->dest , couple->pk_id , couple->nb_retry+1 , op_sim_time()+delay);
															mewlana_debug (msg);
														}
												}
				
											//Test for max nb retransmissions
											if (couple->nb_retry + 1 >= MAX_NB_RETRIES_UNICAST_ACKS)
												{
													op_prg_list_remove (ack_table , i);
													op_pk_destroy(couple->pkptr);
													free(couple);
												}
											else
												couple->nb_retry++;							
										}
									if ((couple->timeout < older_entry) || (older_entry==-1))
										older_entry = couple->timeout;
								}
				
				
							//The next verification
							if (older_entry != -1)
								op_intrpt_schedule_self (older_entry , UNICAST_RETRANSMISSIONS_CODE);
						}
				
				
				}


			/** state (RET_UNICAST) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "RET_UNICAST", "mewlana_process () [RET_UNICAST exit execs]")
				{
				}


			/** state (RET_UNICAST) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "RET_UNICAST", "idle")
				/*---------------------------------------------------------*/



			/** state (ENDSIM) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "ENDSIM", "mewlana_process () [ENDSIM enter execs]")
				{
				//----------------------------------------------------------------
				//				SIMULATION END
				//----------------------------------------------------------------
				
				//Collects some stats when the simulation ends
				//CONTROL
					char	filename[50];
					FILE	*file , *data_file;
					int 	i , j;
				//AP HELLOS
					double	ap_hellos_rcvd_total			= 0; 
				//AP REG
					int		nb_sent_ap_reg					= 0;
					int		nb_received_ap_reg				= 0;
					int		hops_ap_reg						= 0;
					int		nb_retransmissions_ap_reg		= 0;
					double	delay_ap_reg					= 0;
				//DURATION
					double	stats_time_duration;
				//DATA
					int		pk_size							= 0;
					//TOTAL
					double	delay_data_pk 					= 0;
					int		nb_data_pk_received				= 0;
					int		throughput_data_pk				= 0;
					int		hops_data_pk					= 0;
					int		nb_break_route_from_source		= 0;
					int		nb_retransmissions_data_pk		= 0;
					//DOWNLOAD
					double	delay_data_pk_down 				= 0;
					int		nb_data_pk_received_down		= 0;
					int		throughput_data_pk_down			= 0;
					int		hops_data_pk_down				= 0;
					int		nb_break_route_from_source_down	= 0;
					int		nb_retransmissions_data_pk_down	= 0;
					//UPLOAD
					double	delay_data_pk_up 				= 0;
					int		nb_data_pk_received_up			= 0;
					int		throughput_data_pk_up			= 0;
					int		hops_data_pk_up					= 0;
					int		nb_break_route_from_source_up	= 0;
					int		nb_retransmissions_data_pk_up	= 0;
				//SPEED
				   	double	SPEED_HIGH_MIN 	= 0;
				   	double	SPEED_HIGH_MAX 	= 0;
				   	double	SPEED_LOW_MIN 	= 0;
				   	double	SPEED_LOW_MAX 	= 0;
					int		speed_class		= 0;
				
					
				//Stats Per node
					individual_statistics_generate();
					
				//Stats about final state
					if (is_my_ap_valid())
						nb_nodes_which_have_a_valid_ap_final++;
					else
						sprintf(list_nodes_without_valid_ap, "%s%d	|	",list_nodes_without_valid_ap,my_address);
					if (is_AP)
						nb_nodes_registered_to_ap_final += count_nb_bidirect_entries_in_routing_table() + 1;	//+1 : Me !
				
				//Speeds
					if (op_ima_obj_attr_exists(op_topo_parent(op_id_self()), "mobility.Speed_Class") == OPC_TRUE)
						{
							op_ima_obj_attr_get(op_topo_parent(op_id_self()), "mobility.Speed_Class", &speed_class);
							switch(speed_class)		
								{
									case LOW_SPEED :
										nb_low_speed_nodes++;
									break;
									case HIGH_SPEED :
										nb_high_speed_nodes++;
									break;
								}
						}
				
				
				//Global Stats
					if (my_stat_id+1 == nb_nodes)
						{
							//Time Duration for Stats Simualtion
							stats_time_duration = op_sim_time()-TIME_BEGIN_STATS;
							
							//General Parameters
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MIN", 	&SPEED_HIGH_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MAX",	&SPEED_HIGH_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MIN", 	&SPEED_LOW_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MAX",	&SPEED_LOW_MAX); 
							op_ima_sim_attr_get(OPC_IMA_INTEGER,"DATA_PK_SIZE",	&pk_size); 
						
							
							//-------------------
							//     AP HELLO
							//-------------------
							for(i=0 ; i < MAX_AP_HELLO_PK ; i++)
								for(j=0 ; j < MAX_NB_NODES ; j++)
									ap_hellos_rcvd_total += stats_ap_hellos_rcvd [i][j];
							
							
							
							//-------------------
							//       DATA
							//-------------------
							if (DEBUG >1)
								{
									sprintf(filename,"results_mewlana/%d_mewlana_debug_pk_data.txt",begin_time);		
									data_file = fopen(filename , "w");
									fprintf(data_file,"SRC	|	DEST	|	SIZE	|	HOPS	|	RETRY	|	SENT		|	REC		|	DELAY\n");	
								}
							for (i=0 ;  i < stats_nb_data_pk ; i++ )
								{
									//The packet was received
									if (stats_data_pk [i].time_reception!=0)
										{
											nb_data_pk_received++;
											throughput_data_pk 			+= stats_data_pk [i].pk_size;
											hops_data_pk 				+= stats_data_pk [i].hops;
											nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
											delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_emission;
											
											if (stats_data_pk [i].type == UPLOAD)
												{
													nb_data_pk_received_up++;
													throughput_data_pk_up 			+= stats_data_pk [i].pk_size;
													hops_data_pk_up 				+= stats_data_pk [i].hops;
													nb_retransmissions_data_pk_up += stats_data_pk [i].nb_retry;
													delay_data_pk_up 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_emission;
												}
											 if (stats_data_pk [i].type == DOWNLOAD)
												{
													nb_data_pk_received_down++;
													throughput_data_pk_down 		+= stats_data_pk [i].pk_size;
													hops_data_pk_down 				+= stats_data_pk [i].hops;
													nb_retransmissions_data_pk_down += stats_data_pk [i].nb_retry;
													delay_data_pk_down 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_emission;
												}
										}
									else
										{
											if (stats_data_pk [i].type == UPLOAD)
												{
													if (stats_data_pk [i].error_from_src)
														nb_break_route_from_source_up++;
												}
											 else if (stats_data_pk [i].type == DOWNLOAD)
												{
													if (stats_data_pk [i].error_from_src)
														nb_break_route_from_source_down++;
												}							
										}
									if (DEBUG >1)
										fprintf(data_file,"%d	|	%d	|	%d	|	%d	|	%d	|	%f	|	%f	|	%f \n", stats_data_pk[i].source , stats_data_pk[i].dest , stats_data_pk[i].pk_size, stats_data_pk[i].hops , stats_data_pk[i].nb_retry , stats_data_pk[i].time_emission , stats_data_pk[i].time_reception,stats_data_pk[i].time_reception-stats_data_pk[i].time_emission);
								}			
							if (DEBUG >1)
								fclose(data_file);
							
							//AP Registrations
							for (i=0 ;  i < stats_nb_ap_hello ; i++ )
								{
									for (j=0; j < nb_nodes ; j++)
										{						
											if (stats_ap_reg [i][j][0] !=0)
												nb_sent_ap_reg ++;
											
											//The packet was received
											if (stats_ap_reg [i][j][1] !=0)
												{
													nb_received_ap_reg++;
													delay_ap_reg				+= stats_ap_reg_time [i][j][1] - stats_ap_reg_time [i][j][0];
													hops_ap_reg 				+= stats_ap_reg [i][j][2];
													nb_retransmissions_ap_reg 	+= stats_ap_reg [i][j][3];
												}
										}
								}
							
							//File Initialization	
							sprintf(filename, "results_mewlana/%d_mewlana_global_stats.txt",begin_time);
							file = fopen (filename, "w");
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, "|                                          Global Statistics for Mewlana                                     |\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				   
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   DURATION                                                |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Nb AP									:	%d\n", nb_aps);
							fprintf(file, "->High Speed \n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_HIGH_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_HIGH_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_high_speed_nodes);
							fprintf(file, "->Low Speed\n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_LOW_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_LOW_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_low_speed_nodes);
							fprintf(file, "Degree								:	%f\n",							(double)average_degree / (nb_nodes * (stats_time_duration/INTERVALL_PERIODIC_FUNCTIONS))  );
							fprintf(file, "Duration (in seconds)						:	%f\n", 					op_sim_time());
							fprintf(file, "Number of Communicating Nodes					:	%d\n", 				nb_connections);
							fprintf(file, "Data packet size							:	%d\n", 						pk_size);
							fprintf(file, "\n\n");
				
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                         DATA                                               |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "TOTAL\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			stats_nb_data_pk );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) nb_data_pk_received / (double)stats_nb_data_pk );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk / (double)nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk / (1024 * 8 * (op_sim_time()-TIME_BEGIN_NETWORK))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk / nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk / hops_data_pk );
							fprintf(file,"\n\n");
						
				
							fprintf(file, "UPLOAD :\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			stats_nb_data_pk_up );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received_up );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) nb_data_pk_received_up / (double)stats_nb_data_pk_up );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk_up / (double)nb_data_pk_received_up );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk_up / (1024 * (op_sim_time()-TIME_BEGIN_NETWORK))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk_up / nb_data_pk_received_up  );
							fprintf(file, "Average Number of error 'no route' from source		:	%d\n",	nb_break_route_from_source_up );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk_up / hops_data_pk_up );
							fprintf(file, "\n\n");
							
							fprintf(file, "DOWNLOAD\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			stats_nb_data_pk_down );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received_down );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) nb_data_pk_received_down / (double)stats_nb_data_pk_down );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk_down / (double)nb_data_pk_received_down );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk_down / (1024 * (op_sim_time()-TIME_BEGIN_NETWORK))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk_down / nb_data_pk_received_down  );
							fprintf(file, "Average Number of error 'no route' from source		:	%d\n",	nb_break_route_from_source_down );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",	(double) nb_retransmissions_data_pk_down / hops_data_pk_down );
							fprintf(file, "\n\n");
				
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   AP HELLOS                                                |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "AP Hellos nb							:	%d\n", 							stats_nb_ap_hello);
							fprintf(file, "Delivery Ratio for Ap-Hellos					:	%f\n", 					(double) ap_hellos_rcvd_total / ((nb_nodes-nb_aps)*stats_nb_ap_hello));
							fprintf(file, "\n");
							fprintf(file, "Final Number of Nodes with a Valid AP			:	%f\n", 				(double) nb_nodes_which_have_a_valid_ap_final );
							fprintf(file, "Final Nodes without a Valid AP				:	%s\n", 					list_nodes_without_valid_ap);
							fprintf(file, "Average Number of Nodes with a Valid AP			:	%f\n", 				(double) nb_nodes_which_have_a_valid_ap / (stats_time_duration/INTERVALL_PERIODIC_FUNCTIONS));
							fprintf(file, "Probability of a Node to have a Valid AP			:	%f\n", 				(double) nb_nodes_which_have_a_valid_ap / ((nb_nodes-nb_aps)*(stats_time_duration/INTERVALL_PERIODIC_FUNCTIONS)));
							fprintf(file, "\n\n");
					
				
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                               AP REGISTRATIONS                                                |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Nb of AP Registration Sent					:	%d\n", 					nb_sent_ap_reg );
							fprintf(file, "Nb of AP Registration Predicted				:	%d\n", 					stats_nb_ap_hello * (nb_nodes - nb_aps) );
							fprintf(file, "Delivery ratio for AP Registration				:	%f\n", 				(double) nb_received_ap_reg / nb_sent_ap_reg );
							fprintf(file, "Nb of retransmissions per AP Registration			:	%f\n", 			(double) nb_retransmissions_ap_reg / nb_received_ap_reg  );
							fprintf(file, "Nb of retransmissions per AP Registration per Hop	:	%f\n",  		(double) nb_retransmissions_ap_reg / hops_ap_reg );
							fprintf(file, "Route Length for AP Registration				:	%f\n", 			  		(double) hops_ap_reg / nb_received_ap_reg );
							fprintf(file, "Delay for AP Registration					:	%f\n", 			  		(double) delay_ap_reg / nb_received_ap_reg );
							fprintf(file, "\n");
							fprintf(file, "Final Number of Nodes registered in AP			:	%f\n", 				(double) nb_nodes_registered_to_ap_final);
							fprintf(file, "Average Number of Nodes registered in AP			:	%f\n", 				(double) nb_nodes_registered_to_ap 		/ (stats_time_duration/INTERVALL_PERIODIC_FUNCTIONS));
							fprintf(file, "Probability for a node to be registered in AP		:	%f\n", 			(double) nb_nodes_registered_to_ap 		/ ((nb_nodes-nb_aps)*stats_time_duration/INTERVALL_PERIODIC_FUNCTIONS));
							fprintf(file, "\n\n");
				
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   Network Control                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
					
							fprintf(file, "--> Average Values per node, per second \n");
							fprintf(file, "AP Hellos								:	%f\n", 			(double) nb_pk_ap_hello_total						/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "AP Hellos Retransmissions					:	%f\n", 		(double) nb_pk_ap_hello_retransmission_total		/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "AP Registrations							:	%f\n", 			(double) nb_pk_ap_registration_total				/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "AP Registrations Retransmissions				:	%f\n", 		(double) nb_pk_ap_registration_retransmission_total	/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Unicast Acks							:	%f\n", 				(double) nb_pk_unicast_ack_total					/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Hellos								:	%f\n", 				(double) nb_pk_hello_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 				(double) nb_pk_data_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 			(double) nb_pk_data_retransmission_total			/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Total without retransmissions					:	%f\n", 	(double) nb_pk_total								/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Total Retransmissions						:	%f\n", 		(double) nb_pk_retransmission_total					/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 			(double) (nb_pk_retransmission_total + nb_pk_total)	/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "\n\n");
						}
				}


			/** state (ENDSIM) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "ENDSIM", "mewlana_process () [ENDSIM exit execs]")
				{
				}


			/** state (ENDSIM) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "ENDSIM", "idle")
				/*---------------------------------------------------------*/



			/** state (FROM_LOWER) enter executives **/
			FSM_STATE_ENTER_FORCED (6, state6_enter_exec, "FROM_LOWER", "mewlana_process () [FROM_LOWER enter execs]")
				{
				//Packet Variable
				Packet*		pkptr;
				int			pk_type;
				
				//Common information in packet
				int			address_dest;
				int			address_dest_final;
				int			address_src;
				int			address_src_init;
				int			pk_id;
				int			stat_id;
				short		ttl;
				short		hops;
				int			id_ap;
				int			next_hop;
				
				//Conditions To handle the packet
				Boolean		is_unicast_for_me;
				Boolean		is_broadcast;
				Boolean		is_ttl_enough;
				Boolean		is_pk_not_seen;
				Boolean		is_bidirect;
				
				//Control
				char		msg[400];
				
				//Delay before packet transmission
				double		delay;
				
				
				/*------------------------------------------------------------------------------------------	
													   INCOMING PACKET 
				-------------------------------------------------------------------------------------------*/					
				
				pkptr = op_pk_get (op_intrpt_strm ());
				op_pk_nfd_get (pkptr, "OPTION_TYPE",&pk_type);
				op_pk_nfd_get (pkptr, "SRC", 		&address_src);
				op_pk_nfd_get (pkptr, "DEST", 		&address_dest);
				op_pk_nfd_get (pkptr, "SRC_INIT", 	&address_src_init);
				op_pk_nfd_get (pkptr, "PK_ID", 		&pk_id);
				op_pk_nfd_get (pkptr, "TTL", 		&ttl);
				
				
				
				
				/*------------------------------------------------------------------------------------------	
													   CONDITIONS FOR PKS 
				-------------------------------------------------------------------------------------------*/					
				is_unicast_for_me 		=	(address_dest == my_address);
				is_broadcast 			=	((address_dest == -1) && (address_src != my_address));
				
				is_ttl_enough 			=	(ttl>0);
				is_pk_not_seen 			=	(addr_pk_id_not_seen(address_src_init , pk_id) || (pk_type == UNICAST_ACK_PK_TYPE));
				
				//The pk must come from a bidirect link, but We can treat it whenever it comes if it is important
				is_bidirect				=	((is_link_bidirect(address_src)) || (pk_type == HELLO_PK_TYPE));
				
				
				//Passive Acknowledgements
				//AP Registrations
				if ((address_src != my_address) && (ACK_FOR_AP_REG) && (pk_type == AP_REGISTRATION_PK_TYPE) && (PROMISCUOUS_FOR_UNICAST))
					delete_unicast_ack(address_src , pk_id);
				//DATA
				if ((address_src != my_address) && (ACK_FOR_DATA) && (pk_type == DATA_PK_TYPE) && (PROMISCUOUS_FOR_UNICAST))
					delete_unicast_ack(address_src , pk_id);
				
				
				//DEBUG
				/*if (pk_type == DATA_PK_TYPE)
					{
						sprintf(msg , "%d -> %d (I=%d) (%d %d %d %d %d) %f\n", address_src , address_dest , my_address , is_bidirect , is_broadcast , is_unicast_for_me, is_ttl_enough , is_pk_not_seen , op_sim_time());
						mewlana_test(msg);
					}
				*/					  
				
				if ( is_bidirect && (is_broadcast || is_unicast_for_me) && is_ttl_enough && is_pk_not_seen )
					{
						
						//Search the type of packet
						switch (pk_type)
							{
								//------------------------------------------	
								//		AP HELLOS
								//-------------------------------------------
								case AP_HELLO_PK_TYPE:
										//I must have received the last hello from the source (else it could be timeouted, and that is problematic for ap-hellos)
										if (timeout_routing_entry (address_src) > op_sim_time() + INTERVALL_HELLO*(TIMEOUT_HELLO-1.1))
											{
												add_address_id_couple(address_src_init , pk_id);
												
												//Gets some info
												op_pk_nfd_get(pkptr, "HOPS",	&hops);
												op_pk_nfd_get(pkptr, "ID_AP",	&id_ap);
								
												//Reception Stats
												stats_ap_hellos_rcvd [pk_id][my_stat_id] = 1;
								
												//Update the routing table
												add_routing_entry (address_src_init, address_src , hops+1, INTERVALL_AP_HELLO*TIMEOUT_AP_HELLO , OPC_TRUE , OPC_TRUE , OPC_TRUE);
												my_ap = address_src_init;
								
												if (DEBUG>4)
													{
														sprintf(msg, "AP HELLO : I received an ap_hello from %d (pk_id=%d) via %d at %f\n", address_src_init ,  pk_id , address_src , op_sim_time());
														mewlana_debug (msg);
													}
								
												//Sends an AP-Registration
												ap_registration_generate(id_ap , pk_id);
								
												//Relays the packets
												if (ttl>1)
													{
														ttl--;hops++;
														op_pk_nfd_set(pkptr, "HOPS", 	hops);
														op_pk_nfd_set(pkptr, "TTL", 	ttl);
														op_pk_nfd_set(pkptr, "SRC", 	my_address);
														pk_send_delayed(op_pk_copy(pkptr), op_dist_uniform (0.05) );
													}
											}
									break;
									
								//------------------------------------------	
								//			REGISTRATION TO AP 
								//-------------------------------------------
								case AP_REGISTRATION_PK_TYPE:
										//Ack
										if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_AP_REG) && (!PROMISCUOUS_FOR_UNICAST))
											acknowledges_unicast_packet(address_src , pk_id);
									
										//Registers the packet as seen
										add_address_id_couple(address_src_init , pk_id);
				
										//Gets some info
										op_pk_nfd_get(pkptr, "HOPS", 	&hops);
										op_pk_nfd_get(pkptr, "ID_AP",  	&id_ap);
									
										//Update the routing table
										add_routing_entry (address_src_init , address_src , hops+1 , INTERVALL_HELLO*TIMEOUT_HELLO , OPC_FALSE , OPC_TRUE , OPC_FALSE);
									
										//FINAL NODE
										if (is_AP)
											{
												if (DEBUG>5)
													{
														sprintf(msg,"AP_REGISTRATION : I register the client %d at %f\n",address_src_init , op_sim_time());
														mewlana_debug(msg);
													}
												if (DEBUG>1)
													{
														sprintf(msg,"FINAL : The AP registers the client %d at %f\n",address_src_init , op_sim_time());
														mewlana_ap_reg(msg);
													}
												//Stats
												stats_ap_reg_time 	[pk_id][address_src_init][1] = op_sim_time();
												stats_ap_reg 		[pk_id][address_src_init][1] = my_address;
												stats_ap_reg 		[pk_id][address_src_init][2] = MAX_NETWORK_RADIUS - ttl + 1;
											}
									
										//RELAY NODE
										if ((ttl>1) && (!is_AP))
											{
												//looks the next relay toward the AP
												next_hop = get_relay_in_routing_table(id_ap);						
												op_pk_nfd_set(pkptr, "DEST", next_hop);
				
												//Common control fields
												ttl--;hops++;
												op_pk_nfd_set(pkptr, "HOPS", 	hops);
												op_pk_nfd_set(pkptr, "TTL", 	ttl);
												op_pk_nfd_set(pkptr, "SRC", 	my_address);
													
												//Delay
												delay = op_dist_uniform (0.1);
												
												//DEBUG
												if (DEBUG>1)
													{
														sprintf(msg, "RELAY : %d relays the packet from %d to %d to join AP %d at %fs\n", my_address , address_src_init , next_hop , id_ap , op_sim_time()+delay);
														mewlana_ap_reg(msg);
													}								
												//If the packet is valid
												if (next_hop != -1)
													{
														if (DEBUG>5)
															{
																sprintf(msg, "AP_REGISTRATION :  I relay the packet from %d to %d to join AP %d at %fs\n",address_src_init , next_hop , id_ap , op_sim_time()+delay);
																mewlana_debug(msg);
															}
									
														//Acks For this apcket
														if (ACK_FOR_AP_REG)
															add_unicast_ack(next_hop , pk_id , pkptr);
												
														//Transmission								
														pk_send_delayed (op_pk_copy(pkptr) , delay );
													}
											}
									
										//acks the packet if I am the final destination....
										if ((is_AP) && (ACK_FOR_AP_REG))
											acknowledges_unicast_packet(address_src , pk_id);
							
									break;
								//------------------------------------------	
								//			ACKNOWLEDGEMENTS
								//-------------------------------------------
								case UNICAST_ACK_PK_TYPE:
										//Registers the packet as seen
										add_address_id_couple(address_src , pk_id);
				
										delete_unicast_ack(address_src , pk_id);				
									break;
									
								//------------------------------------------	
								//			HELLOS
								//-------------------------------------------
								case HELLO_PK_TYPE:
										//Registers the packet as seen
										add_address_id_couple(address_src , pk_id);
				
										update_neighbors(pkptr);
									break;
									
								//------------------------------------------	
								//			DATA
								//-------------------------------------------
								case DATA_PK_TYPE:
										op_pk_nfd_get (pkptr, "STAT_ID", 		&stat_id);
									
										//Ack
										if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_DATA) && (!PROMISCUOUS_FOR_UNICAST))
											acknowledges_unicast_packet(address_src , pk_id);
				
										//Registers the packet as seen
										add_address_id_couple(address_src_init , pk_id);
									
										//Final Destination
										op_pk_nfd_get(pkptr, "DEST_FINAL", &address_dest_final);
									
										//Relays the packets
										if ((ttl>1) && (!is_AP) && (address_dest_final != my_address))
											{
												//looks the next relay toward the AP
												next_hop = get_relay_in_routing_table(address_dest_final);						
												op_pk_nfd_set(pkptr, "DEST", next_hop);
												
												//Common control fields
												ttl--;
												op_pk_nfd_set(pkptr, "TTL", 	ttl);
												op_pk_nfd_set(pkptr, "SRC", 	my_address);
												
												//DEBUG
												if (DEBUG>1)
													{
														sprintf(msg, "->DATA - relay from %d to %d  (src_init %d and toward %d) at %f\n", my_address , next_hop , address_src_init , address_dest_final , op_sim_time());
														if (address_dest_final <= nb_aps)
															mewlana_up(msg);
														else
															mewlana_down(msg);
													}
												//If the packet is valid
												if (next_hop != -1)
													{
														if (DEBUG>1)
															{
																sprintf(msg, "DATA - relay from %d to %d  (src_init %d and toward %d, with pk_id=%d) at %f\n", my_address , next_hop , address_src_init , address_dest_final , pk_id , op_sim_time());
																mewlana_debug(msg);
															}
														
														//Acks For this packet
														if (ACK_FOR_DATA)
															add_unicast_ack(next_hop , pk_id , pkptr);
												
														//Transmission								
														pk_send (op_pk_copy(pkptr));
													}
											}
										if (address_dest_final == my_address)
											{
												//Ack
												acknowledges_unicast_packet(address_src , pk_id);
												
												//Stats
												stats_data_pk [stat_id].time_reception	= op_sim_time();
												stats_data_pk [stat_id].dest			= my_address;
												stats_data_pk [stat_id].hops			= MAX_NETWORK_RADIUS - ttl + 1;
												
												//Debug
												if (DEBUG>1)
													{
														sprintf(msg,"\n-------- DATA received by %d at %f (pk_id %d) (nb hops=%d) --------\n\n\n" , my_address , op_sim_time() , pk_id , MAX_NETWORK_RADIUS - ttl + 1);
														if (is_AP)
															mewlana_up(msg);
														else
															mewlana_down(msg);
														sprintf(msg, "DATA - Reception from %d (src_init %d, pk_id=%d) at %f\n", address_src , address_src_init , pk_id , op_sim_time());
														mewlana_debug(msg);
													}
											}
				
										
									break;
				
							}
					}
					
					
					
				//The packet was treated, we destroy it to free memory
				op_pk_destroy(pkptr);
				}


			/** state (FROM_LOWER) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "FROM_LOWER", "mewlana_process () [FROM_LOWER exit execs]")
				{
				}


			/** state (FROM_LOWER) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "FROM_LOWER", "idle")
				/*---------------------------------------------------------*/



			/** state (DATA) enter executives **/
			FSM_STATE_ENTER_FORCED (7, state7_enter_exec, "DATA", "mewlana_process () [DATA enter execs]")
				{
				int		dest_final;
				int		i;
				int		network_id;
				int		node_remote_id;
				int		process_remote_id;
				int		its_address;
				
				
				/*------------------------------------------------------------------------------------------	
												   THE FINAL DESTINATION
				-------------------------------------------------------------------------------------------*/					
				//The final destination is random if we are the AP, but is the AP if we are a classical node
				if (!is_AP)
					{
						//The destination (the AP, Internet)
						dest_final	= my_ap;
						
						//Identificaiton of the remote localization process
						network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
						node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB))    );
						process_remote_id	= op_id_from_name ( node_remote_id, OPC_OBJMTYPE_QPS, PROCESS_ID_NAME);
					}
				else
					dest_final	= op_dist_uniform (nb_nodes-2)+2;
				
				/*------------------------------------------------------------------------------------------	
											  PACKET GENERATION + TRANSMISSION
				-------------------------------------------------------------------------------------------*/	
				
				for(i=0; i < NB_PK_PER_FLOW ; i++)
					op_intrpt_schedule_call(op_sim_time() + i*INTERARRIVAL_DATA_PK , 0 , schedule_data_pk , dest_final);
				
				
				/*------------------------------------------------------------------------------------------	
															NEXT FLOW
				-------------------------------------------------------------------------------------------*/					
				//I must wake up the next source node
				if (is_AP)
					op_intrpt_schedule_self(op_sim_time() + op_dist_exponential(INTERVALL_DATA_PK_AP*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE);
				else
					op_intrpt_schedule_remote(op_sim_time() + op_dist_exponential( (double)INTERVALL_DATA_PK_AP * NB_PK_PER_FLOW / DATA_PK_UPLOAD_RATIO) , PK_DATA_GENERATE_CODE , process_remote_id);
				}


			/** state (DATA) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "DATA", "mewlana_process () [DATA exit execs]")
				{
				}


			/** state (DATA) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "DATA", "idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,mewlana_process)
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
mewlana_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (mewlana_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (mewlana_process)",
			sizeof (mewlana_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
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
		((mewlana_process_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
mewlana_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
mewlana_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (mewlana_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in mewlana_process_svar function. */
#undef my_address
#undef is_AP
#undef DEBUG
#undef current_id
#undef my_stat_id
#undef addr_pk_id_list
#undef ack_table
#undef current_ap_hello_id
#undef my_ap
#undef debug_ap_reg
#undef debug_data
#undef debug_load
#undef nb_connections
#undef ici_list
#undef data_pk_size
#undef routing_table



void
mewlana_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	mewlana_process_state		*prs_ptr;

	FIN (mewlana_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (mewlana_process_state *)gen_ptr;

	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("DEBUG" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG);
		FOUT;
		}
	if (strcmp ("current_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_id);
		FOUT;
		}
	if (strcmp ("my_stat_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_stat_id);
		FOUT;
		}
	if (strcmp ("addr_pk_id_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->addr_pk_id_list);
		FOUT;
		}
	if (strcmp ("ack_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_table);
		FOUT;
		}
	if (strcmp ("current_ap_hello_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_ap_hello_id);
		FOUT;
		}
	if (strcmp ("my_ap" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_ap);
		FOUT;
		}
	if (strcmp ("debug_ap_reg" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->debug_ap_reg);
		FOUT;
		}
	if (strcmp ("debug_data" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->debug_data);
		FOUT;
		}
	if (strcmp ("debug_load" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->debug_load);
		FOUT;
		}
	if (strcmp ("nb_connections" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->nb_connections);
		FOUT;
		}
	if (strcmp ("ici_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ici_list);
		FOUT;
		}
	if (strcmp ("data_pk_size" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->data_pk_size);
		FOUT;
		}
	if (strcmp ("routing_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->routing_table);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

