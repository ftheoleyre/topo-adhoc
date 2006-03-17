/* Process model C form file: olsr_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char olsr_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 43ED18CF 43ED18CF 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
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

/* Include files.					*/
#include	<oms_dist_support.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>





/*----------------------------------------------------------------------
				     		Parameters		
----------------------------------------------------------------------*/

/* Special attribute values.			*/
#define		TIME_INIT_MAC					5.0		//Time to wait before initialization
#define		TIME_BEGIN_STATS				50.0
#define		TIME_BEGIN_DATA					60.0	//Time to wait before sending data packets
#define		TIME_BEGIN_NETWORK				40.0
#define		TIME_BEGIN_DEBUG				180.0

#define		BROADCAST						-1
#define		PROCESS_ID_NAME					"olsr"

#define		INFINITY_SHORT					256
#define		INFINITY_INT					65535
#define		INFINITY_DOUBLE					999999.0


/*	General parameters	*/
#define		LOW_SPEED						1
#define		HIGH_SPEED						2
#define		PROMISCUOUS_FOR_UNICAST			0

#define		MAX_NB_NODES					200
#define		MAX_NETWORK_RADIUS				15
#define		MAX_ADDRESS						200



/*	General parameters	*/
#define		LOW								0
#define		MEDIUM							1
#define		HIGH							2
#define		MAX								3



/*	For automatic attribution of Addresses		*/
#define		ADDR_RANDOM						0
#define		ADDR_WLAN						1
#define		ADDR_CONFIGURED					2
#define		ADDR_MAC_CDCL_FROM_NAME			3
	



/* Special Addresses (Multicast for APs...) */
#define		ADDR_MULTICAST_AP				255
#define		ADDR_MULTICAST_BACKBONE			256
#define		LOWER_ADDR_FOR_MULTICAST		255			



/* General timeouts */
#define		TIMEOUT_ADDR_MSG_SEQUENCE		20.1
#define		TIMEOUT_ICI						1.0




/* Intervalls for packets and interruptions */
#define		INTERVALL_PERIODIC_FUNCTIONS	1.0



// ROLE
#define		DEAD						0
#define		AP							1
#define		NORMAL						2





/*----------------------------------------------------------------------
						HELLOS			
----------------------------------------------------------------------*/


/*  Timeouts  */
#define		TIMEOUT_HELLO					3.1			//In Hellos-intervals
#define		TIMEOUT_NEIGHBOR				3.1			//In Hellos-intervals
#define		INTERVALL_HELLO					2.0


//LINKS TYPES
#define		LOST_LINK						0
#define		ASYM_LINK						1
#define		SYM_LINK						2


//NEIGHBORS TYPES
#define		NOT_NEIGHBOR					0	
#define		SYM_NEIGHBOR					1	
#define		MPR_NEIGHBOR					2	


//NEIGHBORS LIST
#define	   MPR								2
#define	   SYM								1
#define	   NOT_SYM							0


//PACKETS
#define		NB_MAX_HELLO_FIELDS				50




/*----------------------------------------------------------------------
						MPR			
----------------------------------------------------------------------*/

#define		MIN_MPR							1



/*----------------------------------------------------------------------
						TC			
----------------------------------------------------------------------*/

//TC
#define		TOP_HOLD_TIME					3.1 * INTERVALL_TC
#define		INTERVALL_TC					5.0

//PACKETS
#define		NB_MAX_TC_FIELDS				40

#define		MAX_TC_PK						100000


/*----------------------------------------------------------------------
						DATA		
----------------------------------------------------------------------*/


/* DATA */
#define		MAX_DATA_PK						100000

#define		MAX_NB_LOCAL_REPAIRS_FOR_DATA	3
#define		MAX_NB_REPAIRS_FOR_ONE_NODE		1




/*----------------------------------------------------------------------
						ACKS			
----------------------------------------------------------------------*/


/* Acks	*/
#define		MAX_NB_RETRIES_UNICAST_ACKS		2
//#define		ACK_FOR_DATA					0

#define		TIMEOUT_UNICAST_ACK				0.05	



/*----------------------------------------------------------------------
						TOPOLOGY			
----------------------------------------------------------------------*/


/* Figures for Topology */
#define		THICKNESS_PHYSIC_NEIGHBOR		2
#define		COLOR_AP_CONNECTED				6
#define		COLOR_AP_DISCONNECTED			0
#define		GRAPHIC_XMAX					9000

#define		INTERVALL_FIGURES				60.0


/*----------------------------------------------------------------------
						PACKETS			
----------------------------------------------------------------------*/
//Streams
#define		STRM_FROM_WLAN					0
#define		STRM_TO_WLAN					0

#define		STRM_FROM_ETH					2
#define		STRM_TO_ETH						2

#define		STRM_FROM_HIGHER	   			1
#define		STRM_TO_HIGHER					1


//For Stats
#define		HELLO							1
#define		TC								2

#define		DATA							10
#define		UNICAST_ACK						11


//Packets Type
#define		HELLO_PK_TYPE					1
#define		TC_PK_TYPE						2

#define		DATA_PK_TYPE					10
#define		UNICAST_ACK_PK_TYPE				11





/*----------------------------------------------------------------------
						Interruptions			
----------------------------------------------------------------------*/

/* Interruption codes */
#define		HELLO_GENERATE_CODE				2
#define		PK_DATA_GENERATE_CODE			3
//#define		PK_RREQ_GENERATE_CODE			4

#define		PERIODIC_FUNCTIONS_CODE			10
#define		UNICAST_RETRANSMISSIONS_CODE	11


/* Macro definitions for state		*/
/* transitions.						*/
#define		ENDSIM							(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define 	PK_FROM_ETH						(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_ETH)
#define 	PK_FROM_WLAN					(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_WLAN)
#define		PK_FROM_LOWER					(PK_FROM_ETH || PK_FROM_WLAN)
#define 	PK_DATA_GENERATE				(op_intrpt_code() == PK_DATA_GENERATE_CODE)
#define		PERIODIC_FUNCTIONS				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == PERIODIC_FUNCTIONS_CODE)
#define		UNICAST_RETRANSMISSIONS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == UNICAST_RETRANSMISSIONS_CODE)







/*----------------------------------------------------------------------
						Structures
----------------------------------------------------------------------*/

//-------- MPR ---------
typedef struct{
	int		address;
	double	timeout;
}struct_mpr_selector;


//-------- NEIGHBORHOOD ---------

//1-Neighbors
typedef struct {
	int		address;
	short	type;			// (not) symetric
	int		willingness;
} struct_neighbor;


//1-Neighbors
typedef struct {
	int		relay;
	int		address;
	double	timeout;
} struct_two_neighbor;


//Association main/secondary address
typedef struct{
	int		interface;
	int		main;
	double	timeout;
} struct_intf_association;


//Links
typedef struct{
	int		local_intf;
	int		dist_intf;
	double	sym_timeout;
	double	asym_timeout;
	double	timeout;
} struct_link;





//-------- TC ---------


//Topology repository
typedef struct{
	int		destination;
	int		relay;
	double	timeout;
	int		ansn;			//seq nb of the TC packet which advertised this link
} struct_topology;



//-------- ROUTING TABLE ---------



//Routing table
typedef struct{
	int		destination;
	int		next_hop;
	short	distance;
} struct_routing;






//-------- PK COMMON MANAGEMENT ---------

//For Addr/msg_sequence records
typedef struct {
	int			address;
	int			msg_sequence;
	double		timeout;
} struct_addr_msg_sequence;


//Acks table
typedef struct{
	int			dest;
	int			msg_sequence;
	double 		timeout;
	short		nb_retry;
	short		nb_repairs;
	packet*		pkptr;	
} struct_ack;


//Multiple Ici (one for each packet)
typedef struct{
	Ici*	ici_ptr;
	double	timeout;
} struct_ici;







/*----------------------------------------------------------------------
						Structures For Stats Collect
----------------------------------------------------------------------*/

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
	double	time_generation;
	double	time_emission;
	double	time_reception;
	short	method;
	double	src_x_pos;
	double	src_y_pos;
	double	dest_x_pos;
	double	dest_y_pos;
	char	route[50];
} struct_stats_data;


//TC PK
typedef struct{
	int		source;
	int		nb_forwarders;
	int		nb_receivers;
	double	time_emission;
	double	time_last_reception;
} struct_stats_tc;




/*----------------------------------------------------------------------
	     		Global Variables for Control		
----------------------------------------------------------------------*/

/*	Common	*/
int			begin_time 				= 0;
int			current_nb_connections	= 0;

/* Nb nodes, special nodes... */
int			nb_nodes 				= 0;
int			nb_aps					= 0;
int			nb_aps_expected 		= 0;
int			nb_nodes_expected 		= 0;

/* Speeds */
int			nb_high_speed_nodes 	= 0;
int			nb_low_speed_nodes 		= 0;

/* Degree */
int			average_degree 			= 0;



/*----------------------------------------------------------------------
				     		Statistics		
----------------------------------------------------------------------*/
//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];

//Topology Figures
char		prefix_results_file [50];
char		suffix_results_file [50];
short		stats_nb_position_written;
short		stats_positions		[MAX_NB_NODES][2];						//1- x-coordinate, 2- y-coordinate, 
short		stats_links			[MAX_NB_NODES][MAX_NB_NODES];			//[i][j] 1 If there exists a link between nodes i and j


//STATS
int		stats_specificities	[MAX_NB_NODES];   				//the specificity of the node (if special) : AP / DEAD / NORMAL

double	stats_overheads_pk	[MAX_NB_NODES];					//Overheads associated to one node (in pps)
double	stats_overheads_bits[MAX_NB_NODES];					//Overheads associated to one node (in bps)




/*----------------------------------------------------------------------
			     		Packet Statistics		
----------------------------------------------------------------------*/

//In packets

int			nb_pk_unicast_ack_instantaneous 					= 0;
int			nb_pk_unicast_ack_total 							= 0;

int			nb_pk_hello_instantaneous 							= 0;
int			nb_pk_hello_total 									= 0;

int			nb_pk_tc_instantaneous 								= 0;
int			nb_pk_tc_total 										= 0;

int			nb_pk_data_instantaneous 							= 0;
int			nb_pk_data_total 									= 0;
int			nb_pk_data_retransmission_instantaneous 			= 0;
int			nb_pk_data_retransmission_total 					= 0;


//In bits

int			nb_bits_unicast_ack_instantaneous 					= 0;
int			nb_bits_unicast_ack_total 							= 0;

int			nb_bits_hello_instantaneous 						= 0;
int			nb_bits_hello_total 								= 0;

int			nb_bits_tc_instantaneous 							= 0;
int			nb_bits_tc_total 									= 0;

int			nb_bits_data_instantaneous 							= 0;
int			nb_bits_data_total 									= 0;
int			nb_bits_data_retransmission_instantaneous 			= 0;
int			nb_bits_data_retransmission_total 					= 0;

double		stats_overheads_pk	[MAX_NB_NODES];					//Overheads associated to one node (in pps)
double		stats_overheads_bits[MAX_NB_NODES];					//Overheads associated to one node (in bps)



/*----------------------------------------------------------------------
						    Data 	Packets		
----------------------------------------------------------------------*/
struct_stats_data	stats_data_pk 	[MAX_DATA_PK];

int			stats_nb_data_pk 		= 0;


/*----------------------------------------------------------------------
						    TC 	Packets		
----------------------------------------------------------------------*/
struct_stats_tc	stats_tc_pk 	[MAX_TC_PK];

int			stats_nb_tc_pk 			= 0;


/*----------------------------------------------------------------------
						Functions Prototypes
----------------------------------------------------------------------*/

//Packet
Boolean addr_msg_sequence_not_seen (int addr , int msg_sequence);
void 	pk_send_delayed(Packet* pkptr , double delay);
void 	pk_send(Packet* pkptr);
void 	add_address_id_couple(int addr , int msg_sequence);



//Debug
void 	olsr_debug(char* msg);
void 	olsr_data(char* msg);
void 	olsr_test(char* msg);

void 	print_ack_table();
void	print_links_list();
void	print_neighbors_list();
void	print_two_neighbors_list();
void 	print_mpr_list();
void 	print_mpr_selectors_list();
void	print_topology_list();
void	print_routing_list();


//Utils
void 	add_int_in_list(List* ll , int value);
Boolean is_int_present_in_list(List* list, int value);



//Hellos
void 	update_neighbors (Packet* pkptr);



//1-Neighborhood
Boolean	update_or_create_neighbors_list(int dist_main_intf , Boolean sym_flag ,int willingness);
void 	update_neighbor_type(int addr , short type);
void 	delete_neighbor(int addr);
int		get_nb_neighbors();




//2-Neighborhood
int		two_neighbors_compare(struct_two_neighbor  *a , struct_two_neighbor *b);
Boolean	delete_two_neighbor(int addr , int relay , double timeout);						//Addr=-1 -> whatever the address is
Boolean add_or_update_two_neighbor(int addr , int relay , double validity_time);



//MPR
Boolean is_mpr(int address);

void 	delete_mpr_selector(int addr);
void 	add_mpr_selector(int addr , double timeout);
Boolean is_mpr_selector(int addr);


//Topology
Boolean delete_topology_list(int source , double timeout);
void 	delete_timeouted_topology(int arg_useless , int code);
Boolean add_or_update_topology(int dest , int relay , double timeout , int seq_nb);



//ROUTING
void 	update_routing_list();
void 	dijkstra(short routes[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , int nb_nodes , int src);




//Acks
void	add_unicast_ack(int dest , int msg_sequence , Packet* pkptr);






//Comon Control
Boolean is_integer_present_in_list(List* list, int value);
Boolean add_integer_in_list(List* list, int value);



//DATA
void 	send_data(int dest , int code);
int		set_dest_data_to_next_relay(Packet* pk_dest);

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
	short	                  		DEBUG;
	int	                    		current_id;
	int	                    		my_stat_id;
	List*	                  		addr_msg_sequence_list;
	List*	                  		ack_table;
	Distribution *	         		distrib;
	Boolean	                		DEBUG_DATA;
	List*	                  		ici_list;
	Boolean	                		DEBUG_TOPO;
	int	                    		NB_CONNECTIONS;
	int	                    		DATA_PK_SIZE;
	int	                    		NB_PK_PER_FLOW;
	double	                 		INTERARRIVAL_DATA_PK;
	List*	                  		neighbors_list;
	List*	                  		two_neighbors_list;
	List*	                  		mpr_list;
	List*	                  		mpr_selector_list;
	List*	                  		links_list;
	Boolean	                		DEBUG_MPR;
	Boolean	                		DEBUG_NEIGHBORHOOD;
	int	                    		current_tc_id;
	Boolean	                		DEBUG_TC;
	List*	                  		topology_list;
	List*	                  		routing_list;
	int	                    		current_data_id;
	Boolean	                		DEBUG_CONTROL;
	Boolean	                		DEBUG_OVERHEAD;
	int	                    		is_AP;
	int	                    		ACK_FOR_DATA;
	int	                    		stats_oh_tc_pk;
	int	                    		stats_oh_hello_pk;
	int	                    		stats_oh_unicast_ack_pk;
	int	                    		stats_oh_data_pk;
	int	                    		stats_oh_data_retransmissions_pk;
	int	                    		stats_oh_tc_bits;
	int	                    		stats_oh_hello_bits;
	int	                    		stats_oh_unicast_ack_bits;
	int	                    		stats_oh_data_bits;
	int	                    		stats_oh_data_retransmissions_bits;
	} olsr_process_state;

#define pr_state_ptr            		((olsr_process_state*) SimI_Mod_State_Ptr)
#define my_address              		pr_state_ptr->my_address
#define DEBUG                   		pr_state_ptr->DEBUG
#define current_id              		pr_state_ptr->current_id
#define my_stat_id              		pr_state_ptr->my_stat_id
#define addr_msg_sequence_list  		pr_state_ptr->addr_msg_sequence_list
#define ack_table               		pr_state_ptr->ack_table
#define distrib                 		pr_state_ptr->distrib
#define DEBUG_DATA              		pr_state_ptr->DEBUG_DATA
#define ici_list                		pr_state_ptr->ici_list
#define DEBUG_TOPO              		pr_state_ptr->DEBUG_TOPO
#define NB_CONNECTIONS          		pr_state_ptr->NB_CONNECTIONS
#define DATA_PK_SIZE            		pr_state_ptr->DATA_PK_SIZE
#define NB_PK_PER_FLOW          		pr_state_ptr->NB_PK_PER_FLOW
#define INTERARRIVAL_DATA_PK    		pr_state_ptr->INTERARRIVAL_DATA_PK
#define neighbors_list          		pr_state_ptr->neighbors_list
#define two_neighbors_list      		pr_state_ptr->two_neighbors_list
#define mpr_list                		pr_state_ptr->mpr_list
#define mpr_selector_list       		pr_state_ptr->mpr_selector_list
#define links_list              		pr_state_ptr->links_list
#define DEBUG_MPR               		pr_state_ptr->DEBUG_MPR
#define DEBUG_NEIGHBORHOOD      		pr_state_ptr->DEBUG_NEIGHBORHOOD
#define current_tc_id           		pr_state_ptr->current_tc_id
#define DEBUG_TC                		pr_state_ptr->DEBUG_TC
#define topology_list           		pr_state_ptr->topology_list
#define routing_list            		pr_state_ptr->routing_list
#define current_data_id         		pr_state_ptr->current_data_id
#define DEBUG_CONTROL           		pr_state_ptr->DEBUG_CONTROL
#define DEBUG_OVERHEAD          		pr_state_ptr->DEBUG_OVERHEAD
#define is_AP                   		pr_state_ptr->is_AP
#define ACK_FOR_DATA            		pr_state_ptr->ACK_FOR_DATA
#define stats_oh_tc_pk          		pr_state_ptr->stats_oh_tc_pk
#define stats_oh_hello_pk       		pr_state_ptr->stats_oh_hello_pk
#define stats_oh_unicast_ack_pk 		pr_state_ptr->stats_oh_unicast_ack_pk
#define stats_oh_data_pk        		pr_state_ptr->stats_oh_data_pk
#define stats_oh_data_retransmissions_pk		pr_state_ptr->stats_oh_data_retransmissions_pk
#define stats_oh_tc_bits        		pr_state_ptr->stats_oh_tc_bits
#define stats_oh_hello_bits     		pr_state_ptr->stats_oh_hello_bits
#define stats_oh_unicast_ack_bits		pr_state_ptr->stats_oh_unicast_ack_bits
#define stats_oh_data_bits      		pr_state_ptr->stats_oh_data_bits
#define stats_oh_data_retransmissions_bits		pr_state_ptr->stats_oh_data_retransmissions_bits

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	olsr_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		           NEIGHBORHOOD    UTILS  
//
//					(Lists management, auxiliary functions...)
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//Computes my weight
int my_weight(){
	return (255 * (nb_nodes - my_stat_id) / nb_nodes);
}


//returns the max value
double  maximum_double(double a, double b){
if (a > b)
	return(a);
else
	return(b);
}


//Returns the main terface associated to the local_interface (in our case, we have only ONE interface)
int get_main_of_secondary_interface(int local_intf){
	return(local_intf);
}

//A topology delete occured for the neighbor 'addr'  (in the links advertised, timeouted...)
void topology_delete(int addr){

	//Deletes all 2-neighbors which have 'addr' as relay
	delete_two_neighbor(-1 , addr , INFINITY_DOUBLE);
	
	//Delete 'addr' in the mpr_selector list if it exists
	delete_mpr_selector(addr);
}



//----------------------------------------------------------------
//							NEIGHBORS
//----------------------------------------------------------------




//Is this node in the list of neighbors ?
Boolean is_neighbor(int address){
	int					i;
	struct_neighbor		*neighbor_elem;
	
	//Walks in the list
	for(i=0; i<op_prg_list_size(neighbors_list) ; i++)
		{
			neighbor_elem = (struct_neighbor*) op_prg_list_access(neighbors_list , i);
			if (neighbor_elem->address == address)
				return(OPC_TRUE);
		}
	
	//No neighbor found !
	return(OPC_FALSE);
}

//Is this node in the list of neighbors & is symetric ?
Boolean is_sym_neighbor(int address){
	int					i;
	struct_neighbor		*neighbor_elem;
	
	//Walks in the list
	for(i=0; i<op_prg_list_size(neighbors_list) ; i++)
		{
			neighbor_elem = (struct_neighbor*) op_prg_list_access(neighbors_list , i);
			if ((neighbor_elem->address == address) && (neighbor_elem->type))
				return(OPC_TRUE);
		}
	
	//No neighbor found !
	return(OPC_FALSE);
}


//Returns the number of symetric neighbors
int	get_nb_neighbors(){
	int					i , nb = 0;
	struct_link			*link_elem;
	
	//Walks in the list
	for(i=0; i<op_prg_list_size(links_list) ; i++)
		{
			link_elem = op_prg_list_access(links_list , i);
			if (link_elem->sym_timeout > op_sim_time())
				nb++;
		}
	
	return(nb);
}


//Deletes a neighbor
void delete_neighbor(int addr){
	int					i;
	struct_neighbor		*neigh_elem;
	char				msg[300];
	
	
	//Finds & Deletes the entry if it already exists
	for(i = op_prg_list_size(neighbors_list)-1 ; i>=0 ; i--)
		{
			neigh_elem = op_prg_list_access(neighbors_list , i);
			if (neigh_elem->address == addr)
				{
					neigh_elem = op_prg_list_remove(neighbors_list , i);
					if (DEBUG_NEIGHBORHOOD)
						{
							sprintf(msg, "NEIGHBOR : %d is deleted at %f\n", neigh_elem->address, op_sim_time());
							olsr_debug(msg);
						}
					op_prg_mem_free(neigh_elem);
					
					topology_delete(addr);

					return;
				}
		}
}

//Updates the type of a neighbor
void update_neighbor_type(int addr , short type){
	int					i;
	struct_neighbor		*neigh_elem;
	char				msg[300];
		
	//Finds & Deletes the entry if it already exists
	for(i=0 ; i<op_prg_list_size(neighbors_list); i++)
		{
			neigh_elem = op_prg_list_access(neighbors_list , i);
			if (neigh_elem->address == addr)
				{
					if (DEBUG_NEIGHBORHOOD)
						{
							sprintf(msg, "NEIGHBOR : %d is updated (type %d -> %d) at %f\n", neigh_elem->address, neigh_elem->type , type , op_sim_time());
							olsr_debug(msg);
						}
					
					if ((neigh_elem->type == SYM) && (type != SYM))
						topology_delete(neigh_elem->address);

					neigh_elem->type = type;
					
					return;
				}
		}
}


//updates or creates one entry in the list of neighbors (according to the info of links_list)
Boolean update_or_create_neighbors_list(int dist_main_intf , Boolean sym_flag ,int willingness){
	int					i , j;
	struct_neighbor		*neigh_elem;
	struct_link			*link_elem;
	char				msg[300];
	Boolean				is_one_link_changed = OPC_FALSE;
	
	for(i=0 ; i<op_prg_list_size(neighbors_list); i++)
		{
			neigh_elem = op_prg_list_access(neighbors_list , i);			
			
			//Update
			if (neigh_elem->address == dist_main_intf)
				{	
					//Common info
					neigh_elem->willingness	= willingness;
					
					//Link symetric -> Neighbor symetric (does not need to walk the whole links_list)
					if (sym_flag)
						{
							if (DEBUG_NEIGHBORHOOD)
								{
									sprintf(msg, "NEIGHBOR : %d is updated (type %d, willingness %d) at %f\n", dist_main_intf , SYM , willingness , op_sim_time());
									olsr_debug(msg);
								}
							if (neigh_elem->type != SYM)
								is_one_link_changed = OPC_TRUE;
							neigh_elem->type = SYM;							
							
							return (is_one_link_changed);
						}
					//At least one link symetric -> Neighbor symetric
					else
						{
							//One link is symetric -> OK
							for(j=0 ; j<op_prg_list_size(links_list); j++)
								{
							 		link_elem = op_prg_list_access(links_list , j);
									
									if ((get_main_of_secondary_interface(link_elem->dist_intf) == dist_main_intf) && (link_elem->sym_timeout > op_sim_time()))
										{
											if (DEBUG_NEIGHBORHOOD)
												{
													sprintf(msg, "NEIGHBOR : %d is updated (type %d, willingness %d) at %f\n", dist_main_intf , SYM , willingness , op_sim_time());
													olsr_debug(msg);
												}
											if (neigh_elem->type != SYM)
												is_one_link_changed = OPC_TRUE;
											neigh_elem->type = SYM;
											
											return (is_one_link_changed);
										}
								}

						}
					
					//No symetric link -> asymetric neighbor
					if (DEBUG_NEIGHBORHOOD)
						{
							sprintf(msg, "NEIGHBOR : %d is updated (type %d, willingness %d) at %f\n", dist_main_intf , NOT_SYM , willingness , op_sim_time());
							olsr_debug(msg);
						}
					if (neigh_elem->type != NOT_SYM)
						is_one_link_changed = OPC_TRUE;
					neigh_elem->type = NOT_SYM;
					
					return (is_one_link_changed);
				}
		
		}
	
	if (DEBUG_NEIGHBORHOOD)
		{
			sprintf(msg, "NEIGHBOR : %d is added (type %d, willingness %d) at %f\n", dist_main_intf , sym_flag , willingness , op_sim_time());
			olsr_debug(msg);
		}
	
	//creates the entry
	neigh_elem = op_prg_mem_alloc(sizeof(struct_neighbor));
	neigh_elem->address 	= dist_main_intf;
	neigh_elem->type 		= sym_flag;
	neigh_elem->willingness	= willingness;
	op_prg_list_insert(neighbors_list , neigh_elem , OPC_LISTPOS_TAIL);
	
	if (neigh_elem->type == SYM)
		is_one_link_changed = OPC_TRUE;
	return(is_one_link_changed);
}




//----------------------------------------------------------------
//							2 - NEIGHBORS
//----------------------------------------------------------------

//Deletes a 2-neighbor (addr==-1 -> any 'addr' is possible)
Boolean delete_two_neighbor(int addr , int relay , double timeout){
	int						i;
	struct_two_neighbor		*two_neigh_elem;
	char					msg[300];
	Boolean					is_one_link_changed = OPC_FALSE;
		
	
	//Finds & Deletes the entry if it already exists
	for(i = op_prg_list_size(two_neighbors_list)-1 ; i>=0 ; i--)
		{
			two_neigh_elem = op_prg_list_access(two_neighbors_list , i);
			if ( ((two_neigh_elem->address == addr) || (addr == -1))      && (two_neigh_elem->timeout < timeout) && (two_neigh_elem->relay == relay))
				{
					two_neigh_elem = op_prg_list_remove(two_neighbors_list , i);
					if (DEBUG_NEIGHBORHOOD)
						{
							sprintf(msg, "2-NEIGHBOR : %d is deleted (relay %d) at %f\n", two_neigh_elem->address , two_neigh_elem->relay , op_sim_time());
							olsr_debug(msg);
						}
					op_prg_mem_free(two_neigh_elem);
					
					//At least one 2-neighbor was deleted  !
					is_one_link_changed = OPC_TRUE;
				}
		}
	
	//The entry was not found -> no change
	return(is_one_link_changed);
}

//updates a 2-neighbor
Boolean add_or_update_two_neighbor(int addr , int relay , double validity_time){
	int						i;
	struct_two_neighbor		*two_neigh_elem;
	char					msg[300];
	
	//Updates the entry if it already exists
	for(i=0 ; i<op_prg_list_size(two_neighbors_list); i++)
		{
			two_neigh_elem = op_prg_list_access(two_neighbors_list , i);
			if ((two_neigh_elem->address == addr) && (two_neigh_elem->relay == relay))
				{
					if (DEBUG_NEIGHBORHOOD)
						{
							sprintf(msg, "2-NEIGHBOR : %d is updated (relay %d, timeout %f) at %f\n", addr, relay, op_sim_time() + validity_time , op_sim_time());
							olsr_debug(msg);
						}
					two_neigh_elem->timeout = op_sim_time() + validity_time;
					
					//The node was already present -> The timeout only has changed !
					return (OPC_FALSE);
				}
		}
	
	if (DEBUG_NEIGHBORHOOD)
		{
			sprintf(msg, "2-NEIGHBOR : %d is added (relay %d, timeout %f) at %f\n", addr, relay, op_sim_time() + validity_time , op_sim_time());
			olsr_debug(msg);
		}
	//No entry was found
	two_neigh_elem = op_prg_mem_alloc(sizeof(struct_two_neighbor));
	two_neigh_elem->address = addr;
	two_neigh_elem->relay	= relay;
	two_neigh_elem->timeout	= op_sim_time() + validity_time;
	op_prg_list_insert_sorted(two_neighbors_list, two_neigh_elem, two_neighbors_compare);
	
	//A 2-neighbor was added !
	return(OPC_TRUE);
}




//----------------------------------------------------------------
//							LINKS
//----------------------------------------------------------------





//does it exist one link to 'addr' ?
Boolean exists_link_to(int addr){
	int				i;
	struct_link		*link_elem;
	
	for(i=0 ; i<op_prg_list_size(links_list) ; i++)
		{
			link_elem = op_prg_list_access(links_list , i);
			if ((link_elem->dist_intf == addr) && (link_elem->timeout > op_sim_time()))
				return(OPC_TRUE);
		}
	return(OPC_FALSE);
}

//does it exist one symetric link to 'addr' ?
Boolean exists_symetric_link_to(int addr){
	int				i;
	struct_link		*link_elem;
	
	for(i=0 ; i<op_prg_list_size(links_list) ; i++)
		{
			link_elem = op_prg_list_access(links_list , i);
			if ((link_elem->dist_intf == addr) && (link_elem->sym_timeout > op_sim_time()))
				return(OPC_TRUE);
		}
	return(OPC_FALSE);
}

//Is 'addr' registered as a symetric neighbor ?
Boolean is_symetric_neighbor(int addr){
	int					i;
	struct_neighbor		*neighbor_elem;
	
	for(i=0 ; i<op_prg_list_size(neighbors_list) ; i++)
		{
			neighbor_elem = op_prg_list_access(neighbors_list , i);
			if (neighbor_elem->address == addr)
				return(neighbor_elem->type);
		}
	return(OPC_FALSE);
}

//delete all timeouted links (Hyp: one interface per node (not more))
void delete_timeouted_links(void* arg_useless , int code){
	int				i;
	struct_link		*link_elem;
	double			older_entry;
//	char			msg[300];
	Boolean			is_one_link_changed = OPC_FALSE;
	
	older_entry = op_sim_time() + 100;
		
	
	for(i = op_prg_list_size(links_list)-1 ; i>=0 ; i--)
		{
			link_elem = op_prg_list_access(links_list , i);
							
			//Deletes the timeouted links
			if (link_elem->timeout <= op_sim_time())
				{
					link_elem = op_prg_list_remove(links_list , i);
					if (!exists_link_to(link_elem->dist_intf))
						{
							is_one_link_changed = OPC_TRUE;
							delete_neighbor(link_elem->dist_intf);
						}
					op_prg_mem_free(link_elem);					
				}			
			else 
				{
					//Gets the oldest entry
					if (link_elem->timeout < older_entry) 
						older_entry = link_elem->timeout;

					//Updates the timeouted symetric_links
					if (link_elem->sym_timeout <= op_sim_time())
						{		
							if ((is_symetric_neighbor(link_elem->dist_intf)) && (!exists_symetric_link_to(link_elem->dist_intf)))
								{
									update_neighbor_type(link_elem->dist_intf , NOT_SYM);
									is_one_link_changed = OPC_TRUE;
								}
						}
					//gets the older entry
					else if (link_elem->sym_timeout < older_entry)
						older_entry = link_elem->sym_timeout;
				}
		}
		
	if (older_entry != op_sim_time() + 100)
		op_intrpt_schedule_call(older_entry , 0 , delete_timeouted_links , NULL);
	
	//Update the routing table
	//if (is_one_link_changed)
	//	update_routing_list();
}















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//	                   			 MPR      Selector
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Adds 'addr' in the mpr_selector list
Boolean is_mpr_selector(int addr){
	struct_mpr_selector		*mpr_s_elem;
	int						i;
	
	//Updates the entry if it exists
	for(i=0 ; i<op_prg_list_size(mpr_selector_list); i++)
		{
			mpr_s_elem = op_prg_list_access(mpr_selector_list , i);
			if (mpr_s_elem->address == addr)
				return (OPC_TRUE);
		}
	return(OPC_FALSE);
}


//Adds 'addr' in the mpr_selector list
void add_mpr_selector(int addr , double timeout){
	struct_mpr_selector		*mpr_s_elem;
	int						i;
	
	
	//Updates the entry if it exists
	for(i=0 ; i<op_prg_list_size(mpr_selector_list); i++)
		{
			mpr_s_elem = op_prg_list_access(mpr_selector_list , i);
			if (mpr_s_elem->address == addr)
				{
					mpr_s_elem->timeout = op_sim_time() + timeout;
					return;
				}
		
		}
	
	//Adds one new entry
	mpr_s_elem = op_prg_mem_alloc(sizeof(struct_mpr_selector));
	mpr_s_elem->address = addr;
	mpr_s_elem->timeout = op_sim_time() + timeout;
	op_prg_list_insert(mpr_selector_list , mpr_s_elem , OPC_LISTPOS_TAIL);	
}

//Deletes 'addr' from the mpr_selector list
void delete_mpr_selector(int addr){
	struct_mpr_selector		*mpr_s_elem;
	int						i;
	char					msg[300];
		
	//Updates the entry if it exists
	for(i=0 ; i<op_prg_list_size(mpr_selector_list); i++)
		{
			mpr_s_elem = op_prg_list_access(mpr_selector_list , i);
			if (mpr_s_elem->address == addr)
				{
					mpr_s_elem = op_prg_list_remove(mpr_selector_list , i);
					if (DEBUG_MPR)
						{
							sprintf(msg , "MPR : the mpr-selector %d was deleted (timeout %f) at %f\n", mpr_s_elem->address , mpr_s_elem->timeout , op_sim_time());
							olsr_debug(msg);
						}
					op_prg_mem_free(mpr_s_elem);
					return;
				}
		
		}
}

















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//	                   				MPR
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Is the address (main interface) in the MPR set ?
Boolean is_mpr(int address){
	int		*mpr_elem;
	int		i;
	
	//Searches addresse in the list of MPR ?
	for(i=0; i<op_prg_list_size(mpr_list);  i++)
		{
			mpr_elem = op_prg_list_access(mpr_list , i);
			if (*mpr_elem == address)
				return(OPC_TRUE);
		}
	
	//Not found
	return(OPC_FALSE);
}


//returns the number of 2-neighbors which have 'addr' as relay
int two_degree_of_neighbor(int addr){
	int						i;
	int						nb_two_neighbors;
	struct_two_neighbor		*two_neigh_elem;
		
	//Counts the 2-neighbors which have addr as relay
	for(i=0 ; i<op_prg_list_size(two_neighbors_list); i++)
		{
			two_neigh_elem = op_prg_list_access(two_neighbors_list , i);
			if (two_neigh_elem->relay == addr)
				nb_two_neighbors++;
		}
	return(nb_two_neighbors);
}

//Compares 2 2-neighbors
int two_neighbors_compare(struct_two_neighbor  *a , struct_two_neighbor *b){
	if (a->address > b->address)
		return 1;
	else if (a->address == b->address)
		return 0;
	else
		return -1;
}

//Returns TRUE if there exists at least one element of 'set' not covered
Boolean element_not_covered(int covered[MAX_NB_NODES] , int set[MAX_NB_NODES]){
	int		i;
	char	msg[150];
	
	for(i=0 ; i<MAX_NB_NODES ; i++)
		{
			if ((covered[i]< MIN_MPR) && (set[i]))
				{
					if (DEBUG_MPR)
						{
							sprintf(msg , "	%d is not yet covered\n", stat_id_to_address[i]);
							olsr_debug(msg);
						}
					return(OPC_TRUE);
				}	
		}
	return(OPC_FALSE);
}

//returns the number of 2N that can be covered by addr (and not yet covered)
int get_reachability_of(int addr , int covered[MAX_NB_NODES]){
	int						i;
	int						value = 0;
	struct_two_neighbor		*two_neighbor_elem;
	
	
	for (i=0; i<op_prg_list_size(two_neighbors_list) ; i++)
		{
			two_neighbor_elem = op_prg_list_access(two_neighbors_list , i);
			if ((two_neighbor_elem->relay == addr) && (covered[  address_to_stat_id[two_neighbor_elem->address]] < MIN_MPR ))
				value++;
		}
	
	return(value);	
}


//adds the neighbors of 'node' in covered
void add_covering_of(int covered[MAX_NB_NODES] , int addr){
	int					i;
	char				msg[300];
	struct_two_neighbor	*two_neighbor_elem;
	

	if (DEBUG_MPR)
		sprintf(msg , "		->Nodes covered by %d : " , addr);
	
	for (i=0; i<op_prg_list_size(two_neighbors_list) ; i++)
		{
				
			two_neighbor_elem = op_prg_list_access(two_neighbors_list , i);
			if (two_neighbor_elem->relay == addr)
				{
					if (DEBUG_MPR)
						sprintf(msg , "%s %d |", msg , two_neighbor_elem->address);
					covered [  address_to_stat_id[two_neighbor_elem->address]  ] ++;
				}
		}
	if (DEBUG_MPR)
		{
			sprintf(msg , "%s\n", msg);
			olsr_debug(msg);
		}
}


//Computes the MPR set
void compute_mpr(){
	int						i;
	char					msg[300];
	int						*node_ptr;
	//Creation of the MPR set
	int						covered		[MAX_NB_NODES];
	int						mpr			[MAX_NB_NODES];
	int						neighbor	[MAX_NB_NODES];
	int						two_neighbor[MAX_NB_NODES];
	//Isolated 2-neighbors
	int						previous_addr , previous_relay;
	Boolean					is_two_neighbor_isolated;
	struct_two_neighbor		*two_neighbor_elem;
	struct_neighbor			*neighbor_elem;
	//Greedy part
	int						reachability_tmp;
	int						max_reachability;
	int						max_node;
	
	
	
//--------------- INITIALIZATION ---------------
	
	if (DEBUG_MPR)
		{
			sprintf(msg , "MPR Selection at %f:\n", op_sim_time());
			olsr_debug(msg);
		}
	
	//Re-initialization
	while(op_prg_list_size(mpr_list) != 0)
		{
			node_ptr = op_prg_list_remove(mpr_list, OPC_LISTPOS_HEAD);
			op_prg_mem_free(node_ptr);
		}
	
	//Initialization of auxiliary variables (avoids several walk in the lists)
	for(i=0 ; i<MAX_NB_NODES ; i++)
		{
			covered[i] 		= 0;
			mpr[i] 			= 0;
			neighbor[i] 	= 0;
			two_neighbor[i] = 0;
		}
	for (i=0; i<op_prg_list_size(two_neighbors_list) ; i++)
		{
			two_neighbor_elem = op_prg_list_access(two_neighbors_list , i);
			if (two_neighbor_elem->timeout > op_sim_time())
				two_neighbor[ address_to_stat_id[two_neighbor_elem->address] ] = OPC_TRUE;			
		}
	for (i=0; i<op_prg_list_size(neighbors_list) ; i++)
		{
			neighbor_elem = op_prg_list_access(neighbors_list , i);
			if ((neighbor_elem->type == SYM) || (neighbor_elem->type == MPR))
				neighbor[ address_to_stat_id[neighbor_elem->address] ] = OPC_TRUE;			
		}
	
	//Sorts the list of 2-neighbors (Improves the speed for the detection of isolated 2-Neighbors)
	op_prg_list_sort(two_neighbors_list, two_neighbors_compare);

	
	
	
//--------------- ISOLATED 2-NEIGHBORS ---------------
	
	
	//Adds in the MPR set the N which are unique possible MPR for one N2
	previous_addr = -1;
	is_two_neighbor_isolated = OPC_FALSE;
	for (i=0; i<op_prg_list_size(two_neighbors_list) ; i++)
		{
			two_neighbor_elem = op_prg_list_access(two_neighbors_list , i);
			
			//The previous and current nodes are different
			if (previous_addr != two_neighbor_elem->address)
				{
					//We changed the node, but the previous node was isolated -> adds the relay as MPR
					if ((is_two_neighbor_isolated) && (!mpr	[ address_to_stat_id[previous_relay] ]))
						{
							if (DEBUG_MPR)
								{
									sprintf(msg , "	%d is added in the MPR set to cover the isolated 2-neighbor %d\n", previous_relay , previous_addr);
									olsr_debug(msg);
								}
							mpr		[ address_to_stat_id[previous_relay] ] 	= OPC_TRUE;
							add_covering_of(covered , previous_relay);
						}

					//Nodes are different -> by default, the current node is isolated 
					is_two_neighbor_isolated = OPC_TRUE;
				}
			//The previous and the current nodes are the same -> not isolated
			else
				is_two_neighbor_isolated = OPC_FALSE;
			
			//Keeps this node
			previous_addr 	= two_neighbor_elem->address;
			previous_relay	= two_neighbor_elem->relay;
		}
	
	//The last element
	if ((is_two_neighbor_isolated) && (!mpr	[ address_to_stat_id[previous_relay] ]))
		{	
			if (DEBUG_MPR)
				{
					sprintf(msg , "	%d is added in the MPR set to cover the isolated 2-neighbor %d\n", previous_relay , previous_addr);
					olsr_debug(msg);
				}
			mpr		[ address_to_stat_id[previous_relay] ] 	= OPC_TRUE;
			add_covering_of(covered , previous_relay);
		}	
	
	
//--------------- GREEDY ALGORTIHM ---------------
	
	//NB : if max_reachability == 0 -> No more candidate to cover one node ! (Some isolated nodes are covered by less than MIN_MPR nodes)
	while ((element_not_covered(covered , two_neighbor)) && (max_reachability != 0))
	{
		//Max reachability ?
		max_reachability = 0;
		for(i=0 ; i<nb_nodes; i++)
			{
			if ((!mpr[i]) && (neighbor[i]))
				{
					reachability_tmp = get_reachability_of(stat_id_to_address[i] , covered);
					
					if (DEBUG_MPR)
						{
							sprintf(msg , "	%d has a reachability of %d\n", stat_id_to_address[i] , reachability_tmp);
							olsr_debug(msg);
						}
					if (reachability_tmp > max_reachability)
						{
							max_reachability 	= reachability_tmp;
							max_node			= stat_id_to_address[i];
						}
				}
			}
	
		/*if (max_reachability == 0)
			{
				print_neighbors_list();
				print_two_neighbors_list();
				op_sim_end("Apparently, a 2-neighbor exists", "and no 1-neighbor is present to join it", "The timeouts in lists MUST be changed to avoid bugs","");
			}
		*/
		
		if (max_reachability != 0)
			{
				//Adds the max in the MPR set and adds its neighbors as covered
				if (DEBUG_MPR)
					sprintf(msg, "	%d (reachability %d) is added to the MPR set\n",  max_node , max_reachability);
				mpr[  address_to_stat_id[max_node]  ] = OPC_TRUE;
				add_covering_of(covered , max_node);
			}
	}

	
//--------------- REGISTER THE MPR SET ---------------
	for (i=0; i<nb_nodes ; i++)
		if (mpr[i])
			add_int_in_list(mpr_list , stat_id_to_address[i]);
	
}















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//	                   NEIGHBORHOOD     PACKETS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Generate an hello packet
void hello(int useless_arg, int code){
	//Control
	int				i;
	char			msg[300];
	//Neighbors
	struct_link		*link_elem;
	//Packet
	Packet			*pkptr;
	char			fieldname[50];
		
	//Updates the MPR set
	compute_mpr();
		
	//Prepare the packet
	pkptr = op_pk_create_fmt("olsr_hello");
	op_pk_nfd_set(pkptr , "MSG_SEQUENCE" , 	current_id);
	op_pk_nfd_set(pkptr , "PK_SEQUENCE" , 	current_id++);
	op_pk_nfd_set(pkptr , "SOURCE" , 	  	my_address);
	op_pk_nfd_set(pkptr , "RELAY" , 	  	my_address);
	op_pk_nfd_set(pkptr , "DEST" ,			BROADCAST);
	op_pk_nfd_set(pkptr , "TTL" , 			1);
	op_pk_nfd_set(pkptr , "HOPS" , 			0);
	op_pk_nfd_set(pkptr , "PK_TYPE" , 		HELLO_PK_TYPE);
	op_pk_nfd_set(pkptr , "VTIME" , 		INTERVALL_HELLO * TIMEOUT_HELLO);
	
	op_pk_nfd_set(pkptr , "WILLINGNESS" , 	my_weight());

	
	//For each link
	for(i=1; i <= op_prg_list_size(links_list) ; i++)
		{
			//If we have too many fields in the packet
			if (i==NB_MAX_HELLO_FIELDS)
				op_sim_end("Too many links to add in a Hello packet", "please increase the number of fields in the packet", "and the associated NB_MAX_HELLO_FIELDS","");

			//Gets one link
			link_elem = op_prg_list_access(links_list , i-1);
			
			//Address of the (secondary) interface
			sprintf(fieldname, "ADDRESS_%d", i);
			op_pk_nfd_set(pkptr , fieldname , 	link_elem->dist_intf);
			
			//Status of the link
			sprintf(fieldname, "LINK_TYPE_%d", i);
			if (link_elem->sym_timeout > op_sim_time())
				op_pk_nfd_set(pkptr , fieldname , 	SYM_LINK);
			else if (link_elem->asym_timeout > op_sim_time())
				op_pk_nfd_set(pkptr , fieldname , 	ASYM_LINK);
			else
				op_pk_nfd_set(pkptr , fieldname , 	LOST_LINK);
			
			//Status of the main interface
			sprintf(fieldname, "NEIGH_TYPE_%d", i);
			if (is_mpr(get_main_of_secondary_interface(link_elem->dist_intf)))
				op_pk_nfd_set(pkptr , fieldname , MPR_NEIGHBOR);
			else if (is_sym_neighbor(link_elem->dist_intf))
				op_pk_nfd_set(pkptr , fieldname , SYM_NEIGHBOR);
			else
				op_pk_nfd_set(pkptr , fieldname , NOT_NEIGHBOR);
		}
	
	//Final fields
	op_pk_nfd_set(pkptr , "LINK_SIZE" , 	i-1);	
	
	//Deletes useless fields
	for( ; i<=NB_MAX_HELLO_FIELDS ; i++)
		{
			sprintf(fieldname, "ADDRESS_%d", i);
			if (op_pk_nfd_is_set(pkptr, fieldname))
				{
					op_pk_nfd_strip(pkptr, fieldname);
					sprintf(fieldname, "LINK_TYPE_%d", i);
					op_pk_nfd_strip(pkptr, fieldname);
					sprintf(fieldname, "NEIGH_TYPE_%d", i);
					op_pk_nfd_strip(pkptr, fieldname);
				}			
		}
		
	if (DEBUG_NEIGHBORHOOD) 
		{
			sprintf(msg,"I send an hello (message_sequence=%d) at %f\n",current_id-1,op_sim_time());
			olsr_debug (msg);
		}	
	
//TRANSMISSION
	pk_send(pkptr);
	add_address_id_couple(my_address , current_id-1);
	
	op_intrpt_schedule_call (op_sim_time() + INTERVALL_HELLO + op_dist_uniform(INTERVALL_HELLO/2) , HELLO_GENERATE_CODE , hello , 1);
}


void update_neighbors (Packet* pkptr) {
	//Control
	int				i , j;
	char			msg[300];
	//Neighbors
	struct_link		*link_elem;
	Boolean			link_found;
	//Packet
	char			fieldname[50];
	//Main information
	int				willingness , msg_sequence , source , ttl , nb_links;
	double			vtime;
	//Info on links
	int				address_tmp , link_type_tmp , neigh_type_tmp;
	Boolean			I_found_in_pk;
	Boolean			is_one_link_changed = OPC_FALSE; 		//Must I update the routing table / The mpr set ?
		
		
	//Prepare the packet
	op_pk_nfd_get(pkptr , "MSG_SEQUENCE" , 	&msg_sequence);
	op_pk_nfd_get(pkptr , "SOURCE" , 	  	&source);
	op_pk_nfd_get(pkptr , "TTL" , 			&ttl);
	op_pk_nfd_get(pkptr , "WILLINGNESS" , 	&willingness);
	op_pk_nfd_get(pkptr , "LINK_SIZE" , 	&nb_links);
	op_pk_nfd_get(pkptr , "VTIME" ,		 	&vtime);


	//Updates the status of the link
	link_found = OPC_FALSE;
	for(j=0 ; (j<op_prg_list_size(links_list)) && (!link_found) ; j++)
		{
			link_elem = op_prg_list_access(links_list, j);
				
			//The node was found !
			if (link_elem->dist_intf == source)
				link_found = OPC_TRUE;
		}
	
	//Creates the link entry and inserts it
	if (!link_found)
		{
			//The timeout is at least 'op_sim_time() + vtime'
			if (op_prg_list_size(links_list) == 0)
				op_intrpt_schedule_call(op_sim_time() + vtime , 0 , delete_timeouted_links , NULL);
		
			link_elem = op_prg_mem_alloc(sizeof(struct_link));
			link_elem->timeout 		= op_sim_time() + TIMEOUT_NEIGHBOR * INTERVALL_HELLO;
			link_elem->sym_timeout 	= 0;
			op_prg_list_insert(links_list, link_elem , OPC_LISTPOS_TAIL);
		}
	

	//In both cases, updates the info (potentially recovered further, particularly sym_timeout)
	link_elem->dist_intf 		= source;
	link_elem->local_intf 		= my_address;
	link_elem->asym_timeout 	= op_sim_time() + vtime;

	//I search if I am a symetric neighbor for it !
	I_found_in_pk = OPC_FALSE;
	for(i=1 ; (i<=nb_links) && (!I_found_in_pk) ; i++)
		{
			sprintf(fieldname , "ADDRESS_%d", i);
			op_pk_nfd_get(pkptr , fieldname , 	&address_tmp);
			
			//I am in the list of its neighbors !
			if (get_main_of_secondary_interface(address_tmp) == get_main_of_secondary_interface(my_address))
				{
					sprintf(fieldname , "LINK_TYPE_%d", i);
					op_pk_nfd_get(pkptr , fieldname , 	&link_type_tmp);
					sprintf(fieldname , "NEIGH_TYPE_%d", i);					
					op_pk_nfd_get(pkptr , fieldname , 	&neigh_type_tmp);
					
					switch (link_type_tmp)
						{
							case LOST_LINK:
								//The type of the node changed
								if (is_symetric_neighbor(link_elem->dist_intf))
									{
										if (DEBUG_NEIGHBORHOOD)
											{
												sprintf(msg, "NEIGHBOR : The link to %d is lost at %f\n", source , op_sim_time());
												olsr_debug(msg);
											}
										link_elem->sym_timeout	= op_sim_time() - 1;
										update_neighbor_type(link_elem->dist_intf , NOT_SYM);
										
										is_one_link_changed = OPC_TRUE;
									}
							break;
							case SYM_LINK:
							case ASYM_LINK:
								//The type of the node changed
								if (! is_symetric_neighbor(link_elem->dist_intf))
									is_one_link_changed = OPC_TRUE;
								
								link_elem->sym_timeout	=  op_sim_time() + vtime; 
								link_elem->timeout		= link_elem->sym_timeout + + TIMEOUT_NEIGHBOR * INTERVALL_HELLO;
							break;
						}
					
					//Updates the MPR selector list
					if (neigh_type_tmp == MPR_NEIGHBOR)
						add_mpr_selector(get_main_of_secondary_interface(source) , vtime);
					else
						delete_mpr_selector(get_main_of_secondary_interface(source));
					
					
					I_found_in_pk = OPC_TRUE;
				}
		}
	link_elem->timeout = maximum_double(link_elem->timeout , link_elem->asym_timeout);
	
	
	//Updates or creates the associated neighbor entry in the list
	if (update_or_create_neighbors_list(get_main_of_secondary_interface(source) , link_elem->sym_timeout > op_sim_time() , willingness))
		is_one_link_changed = OPC_TRUE;
	
	//Updates the 2-Neighborhood
	if (link_elem->sym_timeout > op_sim_time())
		{
			for(i=1 ; i<=nb_links ; i++)
				{				
					sprintf(fieldname , "ADDRESS_%d", i);
					op_pk_nfd_get(pkptr , fieldname , 	&address_tmp);			

					//Adds the 2-neighbors
					if ((get_main_of_secondary_interface(address_tmp) !=  get_main_of_secondary_interface(my_address)) && (!is_sym_neighbor(get_main_of_secondary_interface(address_tmp))))
						{
							sprintf(fieldname , "NEIGH_TYPE_%d", i);					
							op_pk_nfd_get(pkptr , fieldname , 	&neigh_type_tmp);
							sprintf(fieldname , "LINK_TYPE_%d", i);
							op_pk_nfd_get(pkptr , fieldname , 	&link_type_tmp);
				
							switch (neigh_type_tmp)
								{
									//Adds the 2-hop neighbors
									case MPR_NEIGHBOR:
									case SYM_NEIGHBOR:
										if (add_or_update_two_neighbor(get_main_of_secondary_interface(address_tmp) , get_main_of_secondary_interface(source) , vtime))
											is_one_link_changed = OPC_TRUE;
									break;
									
									//Deletes all associated 2-hops neighbors
									case NOT_NEIGHBOR:
									//	if (DEBUG_NEIGHBORHOOD)
									//		{
									//			sprintf(msg , "2-NEIGHBOR : %d is no more a symetric neighbor of %d at %f\n", source , address_tmp , op_sim_time());
									//			olsr_debug(msg);
									//		}
									//	delete_two_neighbor(get_main_of_secondary_interface(address_tmp) , get_main_of_secondary_interface(source) , INFINITY_DOUBLE);
									break;
								}
						}
				}		
			
			//Delete all its old 2-neighbors (TIMEOUT < now + vtime -> these 2-neighbors were not in the packet and also not updated)
			if (delete_two_neighbor(-1 , get_main_of_secondary_interface(source), op_sim_time() + vtime))
				is_one_link_changed = OPC_TRUE;
			
		}
	//Deletes all its potential old 2-neighbors
	else if (delete_two_neighbor(-1 , get_main_of_secondary_interface(source) , INFINITY_DOUBLE))
		is_one_link_changed = OPC_TRUE;
			

	
	//Updates the MPR set + Routing table
	if (is_one_link_changed)
		{
			compute_mpr();
			//update_routing_list();
		}

	if (DEBUG_NEIGHBORHOOD) 
		{
			sprintf(msg,"I receive an hello from %d (message_sequence=%d) at %f\n", source , msg_sequence , op_sim_time());
			olsr_debug (msg);
		}	
}




















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//	               		   TOPOLOGY		KNOWLEDGE
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Compares 2 topology_links
int topology_compare(struct_topology  *a , struct_topology *b){
	if (a->relay > b->relay)
		return 1;
	else if (a->relay == b->relay)
		return 0;
	else
		return -1;
}


//Deletes all
Boolean delete_topology_list(int source , double timeout){
	int					i;
	char				msg[350];
	struct_topology		*topology_elem;
	Boolean			   	is_one_link_changed = OPC_FALSE;
	
	//Deletes all timeouted elements
	for(i=op_prg_list_size(topology_list)-1 ; i>=0 ; i--)
		{
			topology_elem = op_prg_list_access(topology_list , i);
			if ((topology_elem->relay == source) && (topology_elem->timeout < timeout))
				{
					if (DEBUG_TC)
						{
							sprintf(msg , "	The link from %d to %d is deleted (timeout %f) after the reception of a TC packet from %d at %f\n", topology_elem->destination , topology_elem->relay , topology_elem->timeout ,  topology_elem->relay , op_sim_time());
							olsr_debug(msg);
						}
					topology_elem = op_prg_list_remove(topology_list , i);
					op_prg_mem_free(topology_elem);
					
					is_one_link_changed = OPC_TRUE;
				}
		}
	
	return(is_one_link_changed);
	
}

//Delete all timeouted entries in the topology list
void delete_timeouted_topology(int arg_useless , int code){
	int					i;
	char				msg[300];
	struct_topology		*topology_elem;
	double				older_entry = -1;
	Boolean				is_one_topology_changed = OPC_FALSE;
	
	//Deletes all timeouted elements
	for(i=op_prg_list_size(topology_list)-1 ; i>=0 ; i--)
		{
			topology_elem = op_prg_list_access(topology_list , i);
			if (topology_elem->timeout <= op_sim_time())
				{
					if (DEBUG_TC)
						{
							sprintf(msg , "	The link from %d to %d is deleted (timeout %f) at %f\n", topology_elem->destination , topology_elem->relay , topology_elem->timeout , op_sim_time());
							olsr_debug(msg);
						}
					topology_elem = op_prg_list_remove(topology_list , i);
					op_prg_mem_free(topology_elem);
					is_one_topology_changed = OPC_TRUE;
				}
			else if ((older_entry > topology_elem->timeout) || (older_entry = -1))
				older_entry = topology_elem->timeout;
		}


	//The next verification
	if (older_entry != -1)		
		op_intrpt_schedule_call(older_entry , 0 , delete_timeouted_topology , NULL);
	
	
	//Updates the routing table
	//if (is_one_topology_changed)
	//	update_routing_list();
}


//Add or Update one topology link in the list
Boolean add_or_update_topology(int dest , int relay , double timeout , int seq_nb){
	int					i;
	char				msg[300];
	struct_topology		*topology_elem;
	Boolean				is_one_link_changed = OPC_FALSE;
	
	//Updates the element if found....
	for(i=0 ; i<op_prg_list_size(topology_list) ; i++)
		{
			topology_elem = op_prg_list_access(topology_list , i);
			
			//The element exists -> updates it !
			if ((topology_elem->destination == dest) && (topology_elem->relay == relay) && (topology_elem->ansn <= seq_nb))
				{
					if (DEBUG_TC)
						{
							sprintf(msg , "	The link from %d to %d is updated (timeout old %f -> new %f) at %f\n", dest , relay , topology_elem->timeout , op_sim_time() + timeout , op_sim_time());
							olsr_debug(msg);
						}
					topology_elem->timeout = op_sim_time() + timeout;
					return (OPC_FALSE);
				}
			//The seq nb is too low -> outdated
			else if ((topology_elem->destination == dest) && (topology_elem->relay == relay) && (topology_elem->ansn > seq_nb))
				return (OPC_FALSE);
		}
	
	//....Or create it
	if (DEBUG_TC)
		{
			sprintf(msg , "	The link from %d to %d is added (timeout %f) at %f\n", dest , relay , op_sim_time() + timeout , op_sim_time());
			olsr_debug(msg);
		}
	if (op_prg_list_size(topology_list) == 0)
		op_intrpt_schedule_call(op_sim_time() + timeout , 0 , delete_timeouted_topology , NULL);
	
	topology_elem = op_prg_mem_alloc(sizeof(struct_topology));
	topology_elem->destination	= dest;
	topology_elem->relay		= relay;
	topology_elem->timeout		= op_sim_time() + timeout;
	topology_elem->ansn			= seq_nb;
	op_prg_list_insert(topology_list , topology_elem , OPC_LISTPOS_TAIL);
	
	return(OPC_TRUE);
	
	//print_topology_list();
}















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//	               		    TC	     PACKETS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Generate a TC packet
void tc(int useless_arg, int code){
	//Control
	char			msg[300];
	int				i;
	//Packet
	Packet			*pkptr;
	char			fieldname[50];
	//Fields
	int				*mpr_elem;
		
	//Updates the MPR set
	compute_mpr();
		
	//Prepare the packet
	pkptr = op_pk_create_fmt("olsr_tc");
	op_pk_nfd_set(pkptr , "MSG_SEQUENCE" , 	current_id++);
	op_pk_nfd_set(pkptr , "PK_SEQUENCE" , 	current_tc_id);
	op_pk_nfd_set(pkptr , "SOURCE" , 	  	my_address);
	op_pk_nfd_set(pkptr , "RELAY" , 	  	my_address);
	op_pk_nfd_set(pkptr , "DEST" ,			BROADCAST);
	op_pk_nfd_set(pkptr , "TTL" , 			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pkptr , "HOPS" , 			0);
	op_pk_nfd_set(pkptr , "PK_TYPE" , 		TC_PK_TYPE);
	
	op_pk_nfd_set(pkptr , "VTIME" , 		TOP_HOLD_TIME);	
	op_pk_nfd_set(pkptr , "ANSN" , 			current_tc_id);
	
	op_pk_nfd_set(pkptr , "STAT_ID" , 		stats_nb_tc_pk);
	

   for(i=1 ; i<=op_prg_list_size(mpr_list) ; i++)
	   {	   
	   		sprintf(fieldname , "ADDRESS_%d", i);
			mpr_elem = op_prg_list_access(mpr_list , i-1);
			op_pk_nfd_set(pkptr , fieldname , *mpr_elem);
	   }


	//Deletes useless fields
	for( ; i<=NB_MAX_TC_FIELDS ; i++)
		{
			sprintf(fieldname, "ADDRESS_%d", i);
			if (op_pk_nfd_is_set(pkptr, fieldname))
				op_pk_nfd_strip(pkptr, fieldname);
		}


//TRANSMISSION
	pk_send(pkptr);
	add_address_id_couple(my_address , current_id-1);

	//Stats
	stats_tc_pk	[stats_nb_tc_pk].source					= my_address;
	stats_tc_pk	[stats_nb_tc_pk].nb_receivers			= 0;
	stats_tc_pk [stats_nb_tc_pk].nb_forwarders			= 1;
	stats_tc_pk [stats_nb_tc_pk].time_emission			= op_sim_time();
	stats_tc_pk [stats_nb_tc_pk].time_last_reception	= 0;
	
	current_tc_id++;
	stats_nb_tc_pk++;
	
	if (DEBUG_TC)
		{
			sprintf(msg,"I send a tc (message_sequence=%d, ansn %d) at %f\n", current_id-1 , current_tc_id-1 , op_sim_time());
			olsr_debug (msg);
		}
	op_intrpt_schedule_call (op_sim_time() + INTERVALL_TC + op_dist_uniform(INTERVALL_TC/4) , 0 , tc , NULL);
}


//Updates the topology after the reception of a TC packet
void update_tc (Packet* pkptr) {
	//Control
	int				i ;
	char			msg[300];
	//Packet
	char			fieldname[50];
	//Main information
	int				ttl , hops , msg_sequence , source , ansn;
	double			vtime;
	//Info on links
	int				address_tmp;
	Boolean			is_one_link_changed = OPC_FALSE;
	
	
	//Prepare the packet
	op_pk_nfd_get(pkptr , "MSG_SEQUENCE" , 	&msg_sequence);
	op_pk_nfd_get(pkptr , "SOURCE" , 	  	&source);
	op_pk_nfd_get(pkptr , "TTL" , 			&ttl);
	op_pk_nfd_get(pkptr , "VTIME" ,		 	&vtime);
	op_pk_nfd_set(pkptr , "TTL" , 			&ttl);
	op_pk_nfd_set(pkptr , "HOPS" , 			&hops);

	op_pk_nfd_get(pkptr , "ANSN" , 			&ansn);
	
	//For each advertised link		
	sprintf(fieldname , "ADDRESS_%d", 1);
	for(i=1 ; op_pk_nfd_is_set(pkptr , fieldname) ; i++)
		{
			op_pk_nfd_get(pkptr , fieldname , 	&address_tmp);
			if (add_or_update_topology(	get_main_of_secondary_interface(address_tmp) , source , vtime , ansn))
				is_one_link_changed = OPC_TRUE;

			
			//Next packet field
			sprintf(fieldname , "ADDRESS_%d", i+1);
		}
	
	//Deletes old links advertised by this node
	if (delete_topology_list(source , op_sim_time() + vtime))
		is_one_link_changed = OPC_TRUE;

	if (DEBUG_TC) 
		{
			sprintf(msg,"I receive a tc packet from %d (message_sequence=%d, ansn=%d) at %f\n", source , msg_sequence , ansn , op_sim_time());
			olsr_debug (msg);
		}
	
//	if (is_one_link_changed)
//		update_routing_list();
}












//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//				   			ROUTES 			FRAMEWORK
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------







//--------------------------------------------------
//
//				ROUTES MANAGEMENT
//
//--------------------------------------------------


//Returns the empty list (remove all elements)
void route_empty(short route[MAX_NB_NODES]){
	int		i;

	for(i=0 ; i < MAX_NB_NODES; i++)
		route[i] = 0;
}

//add one route
void route_add(short route[MAX_NB_NODES], int node){
	route[0]++;
	route[route[0]] = node;
}

//Copy one route to another
void route_copy(short source[MAX_NB_NODES] , short dest[MAX_NB_NODES]){
	int		i;

	for(i=0 ; i < MAX_NB_NODES ; i++)
		dest[i] = source[i];

}

//converts a route to a string
char* route_to_str(short route[MAX_NB_NODES], char* msg){
	int		i;
	int		nb = 0;

	sprintf(msg, "");

	//print the content
	for (i=1 ; i <= route[0] ; i++)
		sprintf(msg, "%s %d", msg , route[i]);
	return(msg);
}


//returns the length of the route
int	route_length(short route[MAX_NB_NODES]){
	return(route[0]);
}

//returns the position^th node of the route
int	route_get_node(short route[MAX_NB_NODES] , int position){
	return(route[position+1]);
}






/*-----------------------------------------------

			Shortest Paths  --  DIJKSTRA

-----------------------------------------------*/


//Is one case set to '1' in the array ?
Boolean exists_vertex(short vertices[MAX_NB_NODES], int nb_nodes){
	int		i;

	for(i=0 ; i < nb_nodes ; i++)
	{
		if (vertices[i])
			return(OPC_TRUE);
	}

	return(OPC_FALSE);

}


//Returns the vertex of vertices which has the minimum cost (-1 if all the nodes have an infinity cost)
int min_cost(short	vertices[MAX_NB_NODES] , short	cost[MAX_NB_NODES] , int nb_nodes ){
	int		i;
	int		min_cost = INFINITY_SHORT;
	int		min_node ;

	//Min cost id
	for(i=0; i<nb_nodes ; i++)
	{
		if ((vertices[i]) && (cost[i] < min_cost))
		{
			min_cost = cost[i];
			min_node = i;
		}

	}

	//No node with a cost less than INFINITY_SHORT
	if (min_cost == INFINITY_SHORT)
		min_node = -1;

	//Result
	return(min_node);
}

//Computes all the routes from src
void dijkstra(short routes[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , int nb_nodes , int src){
	int		i , k ;
	int		min_cost_node;
	short	cost[MAX_NB_NODES];
	short	included[MAX_NB_NODES];
	short	vertices[MAX_NB_NODES];

	//Initialization
	for(i=0; i < nb_nodes ; i++)
	{
		cost[i] = INFINITY_SHORT;
		included[i] = OPC_FALSE;
		vertices[i] = OPC_TRUE;
		route_empty(routes[i]);
	}

	//Info on the source
	cost[src] = 0;
	route_add(routes[src] , src);

	//Takes the vertex V with the min length which was not treated yet
	min_cost_node = min_cost(vertices , cost , nb_nodes);
	do {
		//V is marked as treated
		vertices[min_cost_node] = OPC_FALSE;		
		included[min_cost_node] = OPC_TRUE;

		//Updates all possible costs if the path of other pass through V
		for (k=0; k< nb_nodes ; k++)
		{
			if ((g[k][min_cost_node]) && (cost[k] > cost[min_cost_node]+1))
			{
				//Updates the route
				route_copy(routes[min_cost_node] , routes[k]);
				route_add(routes[k] , k);

				//Updates the associated cost
				cost[k] = cost[min_cost_node]+1;
			}
		}
		
		//Takes the vertex V with the min length which was not treated yet
		min_cost_node = min_cost(vertices , cost , nb_nodes);
	} while (min_cost_node != -1);
	//exists_vertex(vertices, nb_nodes))
}





/*-----------------------------------------------

		Shortest Paths  -- BELLMAN-FORD

-----------------------------------------------*/





//gets the i° node of the route
int get_relay_route_list(List* route , int pos){
	int*	elem;
	
	elem = op_prg_list_access(route, pos);
	return(*elem);
}

//Returns the empty list (remove all elements)
void route_list_empty(List* route){
	int	*elem;

	while (op_prg_list_size(route) > 0)
		{
			elem = op_prg_list_remove(route, OPC_LISTPOS_HEAD);
			op_prg_mem_free(elem);
		}
}

//converts a route to a string
char* route_list_to_str(List * route , char* msg){
	int		i;
	int		*elem;
	
	//initialization
	sprintf(msg, "");
	
	//print the content
	for (i=0 ; i < op_prg_list_size(route) ; i++)
		{	
			elem = op_prg_list_access(route , i);
			sprintf(msg, "%s %d", msg , *elem);
		}
	return(msg);
}

//converts a route to a string
char* route_list_to_str_of_stat_id(List * route , char* msg){
	int		i;
	int		*elem;
	
	//initialization
	sprintf(msg, "");
	
	//print the content
	for (i=0 ; i < op_prg_list_size(route) ; i++)
		{	
			elem = op_prg_list_access(route , i);
			sprintf(msg, "%s %d", msg , address_to_stat_id[*elem]);
		}
	return(msg);
}


//add one route
void add_route_list(List* route , int node){
	int		*elem;
	
	elem = malloc(sizeof(int));
	*elem = node;
	op_prg_list_insert(route , elem , OPC_LISTPOS_TAIL);
}

//Copy one route to another
void copy_route_list(List* source , List * dest){
	int		i;
	int		*elem;
	
	//empty the dest list
	route_list_empty(dest);
	
	//copies the source
	for(i=0 ; i<op_prg_list_size(source) ; i++)
		{
			elem = op_prg_list_access(source, i);
			add_route_list(dest, *elem);
			
			//elem2 = malloc(sizeof(int));
			//*elem2 = *elem;
			//op_prg_list_insert(dest , elem2 , OPC_LISTPOS_TAIL);
		}
}

//Length of the route
int	route_list_length(List* route){
	return(op_prg_list_size(route));
}



//computes shortest routes on the graph with the matrix G
void compute_shortest_routes(List* routes[MAX_NB_NODES][MAX_NB_NODES] , short g[MAX_NB_NODES][MAX_NB_NODES] , int nb_nodes){
	//Control
	int		i , j , s , u , v ;
	//Route length
	int 	length[MAX_NB_NODES][MAX_NB_NODES];	
	//Condition to stop to search new routes in the graph for a particular source
	Boolean	was_one_route_modified_or_added;
	char	msg [300];
	
	//intialization
	for (i=0; i < nb_nodes ; i++)
		for(j=0 ; j < nb_nodes ; j++)
			{
				if (i == j)
					length[i][j] = 0;
				else
					length[i][j] = INFINITY_INT;
				
				route_list_empty(routes[i][j]);
				if (i == j)
					add_route_list(routes[i][j] , stat_id_to_address[i]);
			}
	
	//For each source
	for (s=0 ; s < nb_nodes ; s++)
		{
			do
				{
					was_one_route_modified_or_added = OPC_FALSE;
					//For each edge in the graph
					for (u=0 ; u < nb_nodes ; u++)
						for (v=0 ; v < nb_nodes ; v++)
							{
								// if the route i->u->v is better than the current i->v route, changes it
								if ((g[u][v] != 0) && (1 + length[s][u] < length[s][v]))
									{
										length[s][v] = length[s][u] + 1;										
										copy_route_list(routes[s][u] , routes[s][v]);
										add_route_list(routes[s][v] , stat_id_to_address[v]);
										was_one_route_modified_or_added = OPC_TRUE;
									}							
							}		
				}
			while(was_one_route_modified_or_added);
		}
}







//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//	              	    ROUTING 		TABLE
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Constructs the grah of the network according to the informatin in :
//returns the timeout associated to dest (if not found, returns -1)
double get_timeout_sym_neighbor(int dest){
	int					i;
	struct_link			*link_elem;
	
	//Walks in the list
	for(i=0; i<op_prg_list_size(links_list) ; i++)
		{
			link_elem = op_prg_list_access(links_list , i);
			if (link_elem->dist_intf == dest)
				return(link_elem->sym_timeout);
		}
	
	return(-1);	
}

//   Neighbors / 2-Neighbors / topology LISTS
void construct_graph(short g[MAX_NB_NODES][MAX_NB_NODES]){
	int						i , j;
	char					msg[3000];
	//Neighbors
	struct_neighbor			*neighbor_elem;
	//2-neighbors
	struct_two_neighbor		*two_neighbor_elem;
	//topology
	struct_topology			*topology_elem;
	
	
	//Initialization of the graph
	for (i=0 ; i<nb_nodes ; i++)
		for (j=0 ; j<nb_nodes ; j++)
			g[i][j] = OPC_FALSE;	
	
	
	//1-Neighbors
	if (OPC_FALSE)//(op_sim_time() > 60)
		sprintf(msg , "NEIGHBORS    :    ");
	for(i=0 ; i<op_prg_list_size(neighbors_list) ; i++)
		{
			neighbor_elem = op_prg_list_access(neighbors_list , i);	
			if (neighbor_elem->type == SYM)
				{
					g [my_stat_id]  [address_to_stat_id[neighbor_elem->address]] = OPC_TRUE;
					g [address_to_stat_id[neighbor_elem->address]]  [my_stat_id] = OPC_TRUE;
					
					if (OPC_FALSE)//(op_sim_time() > 60)//((OPC_FALSE) && (my_address == 39))
						sprintf(msg , "%s%d -> %d  ", msg      , my_stat_id ,  address_to_stat_id[neighbor_elem->address]);
				}
		}	
	
	//2-Neighbors
	if (OPC_FALSE)//(op_sim_time() > 60)
		sprintf(msg , "%s\n2-NEIGHBORS    :    ", msg);
	for(i=0 ; i<op_prg_list_size(two_neighbors_list) ; i++)
		{
			two_neighbor_elem = op_prg_list_access(two_neighbors_list , i);	
			if (two_neighbor_elem->timeout > op_sim_time())
				{
					g  [address_to_stat_id[two_neighbor_elem->relay]]   [address_to_stat_id[two_neighbor_elem->address]] = OPC_TRUE;
					g  [address_to_stat_id[two_neighbor_elem->address]]   [address_to_stat_id[two_neighbor_elem->relay]] = OPC_TRUE;
					
					if (OPC_FALSE)//(op_sim_time() > 60)//((OPC_FALSE) && (my_address == 39))
						sprintf(msg , "%s%d -> %d  ", msg,      address_to_stat_id[two_neighbor_elem->address]    , address_to_stat_id[two_neighbor_elem->relay]     );
				}
		}

	//topology
	if (OPC_FALSE)//(op_sim_time() > 60)
		sprintf(msg , "%s\nTOPOLOGY    :    ",msg);
	for(i=0 ; i<op_prg_list_size(topology_list) ; i++)
		{
			topology_elem = op_prg_list_access(topology_list , i);	
			
			//Avoids obsolete links to 1-neighbors
			if ((topology_elem->timeout > op_sim_time()) && (topology_elem->destination != my_address))
				{
					g  [address_to_stat_id[topology_elem->relay]]   [address_to_stat_id[topology_elem->destination]] = OPC_TRUE;
					g  [address_to_stat_id[topology_elem->relay]]   [address_to_stat_id[topology_elem->destination]] = OPC_TRUE;
					
					if (OPC_FALSE)//(op_sim_time() > 60)//(OPC_FALSE) && (my_address == 39))
						sprintf(msg , "%s%d -> %d  ",  msg,       address_to_stat_id[topology_elem->relay]    , address_to_stat_id[topology_elem->destination]     );
				}
		}	
	
	if (OPC_FALSE)//(op_sim_time() > 60)
		{
			sprintf(msg, "%s\n",msg);
			olsr_debug(msg);
		}
	
	//the graph is already symetric, by construction
	
	//Hard debug to represent the local view of the whole network topology
	if (OPC_FALSE)
		{
			olsr_debug("\n---------------------- GRAPH OF THE TOPOLOGY ----------------------------------\n");
			for(i=0 ; i<nb_nodes ; i++)
				{
					strcpy(msg, "");
					for(j=0 ; j<nb_nodes ; j++)				
						sprintf(msg , "%s %d" , msg , g[i][j]);
					sprintf(msg , "%s\n", msg);
					olsr_debug(msg);
				}
			olsr_debug("\n--------------------------------------------------------------------------------\n");
		}
}


//Returns an empty routing table
void flush_routing_table(){
	struct_routing	*routing_elem;
	
	while(op_prg_list_size(routing_list) != 0)
		{
			routing_elem = op_prg_list_remove(routing_list , OPC_LISTPOS_HEAD);
			op_prg_mem_free(routing_elem);
		}
}


//adds an entry in the routing table
void add_routing_entry(int dest_id , int next_hop_id , short distance){
	struct_routing	*routing_elem;
	
	routing_elem = op_prg_mem_alloc(sizeof(struct_routing));

	routing_elem->destination	= stat_id_to_address[dest_id];
	routing_elem->next_hop		= stat_id_to_address[next_hop_id];
	routing_elem->distance		= distance;
	
	op_prg_list_insert(routing_list , routing_elem , OPC_LISTPOS_TAIL);
}


//updates the routing table
void update_routing_list(){
	//Control
	int			i;
	char		msg[300];
	//The graph
	short		g[MAX_NB_NODES][MAX_NB_NODES];
	short		routes[MAX_NB_NODES][MAX_NB_NODES];
	//Temporary variables
	int			dest_id_tmp , next_hop_id_tmp;
	
	if (DEBUG_NEIGHBORHOOD)
		{
			sprintf(msg , "ROUTING LIST UPDATE at %f\n", op_sim_time());
			olsr_debug(msg);
		}
	
	//Constructs the graph of the whole topology
	construct_graph(g);

	
	//Computes shortest routes on this graph
	dijkstra(routes , g , nb_nodes , my_stat_id);
	
	
	//Flush the old routing_table
	flush_routing_table();
		
	//Updates the routing table	
	for(i=0; i<nb_nodes ; i++)
		{
			//If the route is not null and not to me -> adds the entry dest / relay / distance
			if (route_length(routes[i]) > 1)
				{
					//The last node (starts from 0)
					dest_id_tmp 	= route_get_node(routes[i] , route_length(routes[i]) - 1);
					//The second node (starts from 0)
					next_hop_id_tmp	= route_get_node(routes[i] , 1);
					add_routing_entry(  dest_id_tmp    ,  next_hop_id_tmp   ,   route_length(routes[i]) - 1);
				}
		}

 }



//returns the next_hop associated to 'dest' in the routing list
int get_next_hop_from_routing_table(int dest){
	int				i;
	struct_routing	*routing_elem;
	
	update_routing_list();
	
	//Debug
	if (OPC_FALSE)//(OPC_FALSE) && (my_address == 39))
		{
			print_routing_list();
			print_neighbors_list();
			print_two_neighbors_list();
			print_links_list();
			print_topology_list();
		}	
	
	//Walks the routing list
	for(i=0; i<op_prg_list_size(routing_list) ; i++)
		{
			routing_elem = op_prg_list_access(routing_list , i);
			if (routing_elem->destination == dest)
				return(routing_elem->next_hop);
		}
	
	//No entry was found in the routing table
	return(-1);
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
			for(j=0 ; j < MAX_NB_NODES ; j++)
				stats_links[i][j] = 0;
		}
}

//Writes figures containing the current topology
void write_topology_figures(int useless_arg , int code){
	FILE*				pfile;
	char				msg[500];
	short				color , radius;
	double				x , y , x_max , y_max;		//Positions in Opnet  (floats)
	int					x1 , x2 , y1 , y2 ;			//Positions in figure (integers)
	int					i , j;
	char				filename [200];
	struct_link			*link_elem;
	

	//Next Interruption
	op_intrpt_schedule_call(op_sim_time() + INTERVALL_FIGURES , 0 , write_topology_figures , NULL);
	
	
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
	if (op_prg_list_size(links_list)!=0)
		{
			for (i=0; i < op_prg_list_size(links_list) ; i++)
				{
					//Links
					link_elem = op_prg_list_access(links_list , i);
					if (link_elem->sym_timeout > op_sim_time())
						stats_links[my_stat_id][address_to_stat_id[link_elem->dist_intf]] = THICKNESS_PHYSIC_NEIGHBOR;
				}
		}

	
	
	//---------------------------------------
	//			Writes Figures
	//---------------------------------------	
		
	//Writes stats if I'm the last node
	if (stats_nb_position_written == nb_nodes)
		{
	
		//---------------------------------------
		//			Radio Topology
		//---------------------------------------	
		
			//Opens the associated file and 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results_olsr/%solsr_topology_%s%s.fig" , prefix_results_file , msg , suffix_results_file);
			
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
			fprintf(pfile,"#FIG 3.2 \n#Snapshot of The Network Topology for cbrp \nLandscape \nCenter \nInches \nA4 \n100.00 \nSingle \n-2 \n1200 2 \n");						
			fprintf(pfile,"1 3 0 1 0 0 50 -1 15 0.000 1 0.000 0 0 1 1 0 0 0 0\n");
			
			//---------------
			//Nodes Position
			//---------------
			fprintf(pfile,"#NODE POSITIONS AND ADDRESSES\n");
			for(i=0;i<nb_nodes;i++)
				{	
					//Circle to represent the node
					radius = 100;
					sprintf(msg,"1 3 0 1 0 %d 50 -1 15 0.000 1 0.000 %d %d %d %d 0 0 0 0\n", color , (int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)) , (int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX)) , radius , radius);
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
//								 COMMON  FUNCTIONS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------




//Returns 1 if the entry is present in the list, else 0
Boolean is_int_present_in_list(List* list, int value){
	int		i;
	int*	entry;
	
	//empty list
	if (op_prg_list_size(list) == 0)
		return (OPC_FALSE);
	
	//For each entry of the list
	for (i=0; i < op_prg_list_size(list); i++)
		{
			entry = (int*) op_prg_list_access (list, i);
			if (*entry == value)
				return (OPC_TRUE);
		}
	
	//Default Value
	return (OPC_FALSE);
}

//Adds an int in a list
void add_int_in_list(List* ll , int value){
	int		*elem;
	
	elem = op_prg_mem_alloc(sizeof(int));
	*elem = value;
	op_prg_list_insert(ll, elem, OPC_LISTPOS_TAIL);
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

//Deletes all entries that are timeouted
void delete_timeout_in_addr_msg_sequence_list(){
	int					i = 0;
	struct_addr_msg_sequence*	entry;
	char				msg[150];
	
	//If the list is empty
	if (op_prg_list_size(addr_msg_sequence_list)==0)
		return;
	
	//Search if the entry already exists
	while (i< op_prg_list_size(addr_msg_sequence_list))
		{
			entry = (struct_addr_msg_sequence*) op_prg_list_access (addr_msg_sequence_list, i);
			
			//We delete the entry
			if (entry->timeout < op_sim_time())
				{				
					//DEBUG
					if (DEBUG_CONTROL)
						{
							sprintf(msg,"ID-TABLE : deletes the address %d with msg_sequence %d with timeout %f at %f\n", entry->address , entry->msg_sequence , entry->timeout , op_sim_time());
							olsr_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( addr_msg_sequence_list , i);
					op_prg_mem_free(entry);
				}
			else
				i++;
		}
}

//=1 if that packet was already seen, 0 else
Boolean addr_msg_sequence_not_seen (int addr , int msg_sequence) {
	int					i=0;
	struct_addr_msg_sequence*	couple;
	
	//For each entry of the list ...
	for(i=0; i< op_prg_list_size(addr_msg_sequence_list);i++)
		{  
			couple = (struct_addr_msg_sequence*) op_prg_list_access(addr_msg_sequence_list,i);
			//.....compare it
			if ((couple->address == addr) && (couple->msg_sequence == msg_sequence))
				return(OPC_FALSE);
		}
	return (OPC_TRUE);
}

//Adds this packet as already seen
void add_address_id_couple(int addr , int msg_sequence){
	struct_addr_msg_sequence*		couple;
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (struct_addr_msg_sequence*) op_prg_mem_alloc ( sizeof (struct_addr_msg_sequence));
	
	//Info
	couple->address 	= addr;
	couple->msg_sequence		= msg_sequence;
	couple->timeout		= op_sim_time() + TIMEOUT_ADDR_MSG_SEQUENCE;
	
	//Insert it
	op_prg_list_insert( addr_msg_sequence_list, couple, OPC_LISTPOS_TAIL);	
}


//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void stats_about_control_pk_flows(Packet* pkptr){
	char	msg[50];
	int		pk_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "PK_TYPE", &pk_type);
		
	//Gets the type associated to the pk_type
	switch (pk_type)
		{
			case UNICAST_ACK_PK_TYPE :
				type = UNICAST_ACK;
			break;
			case HELLO_PK_TYPE :
				type = HELLO;
			break;
			case DATA_PK_TYPE :
				type = DATA;
			break;
			case TC_PK_TYPE :
				type = TC;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", pk_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case UNICAST_ACK :
				nb_pk_unicast_ack_instantaneous++;
				nb_bits_unicast_ack_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						stats_oh_unicast_ack_pk++;
						stats_oh_unicast_ack_bits += op_pk_total_size_get(pkptr);
						nb_pk_unicast_ack_total++;
						nb_bits_unicast_ack_total += op_pk_total_size_get(pkptr);
					}
			break;
			case HELLO :
				nb_pk_hello_instantaneous++;
				nb_bits_hello_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						stats_oh_hello_pk++;
						stats_oh_hello_bits += op_pk_total_size_get(pkptr);
						nb_pk_hello_total++;
						nb_bits_hello_total += op_pk_total_size_get(pkptr);
					}
			break;
			case DATA :
				nb_pk_data_instantaneous++;
				nb_bits_data_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						stats_oh_data_pk++;
						stats_oh_data_bits += op_pk_total_size_get(pkptr);
						nb_pk_data_total++;
						nb_bits_data_total += op_pk_total_size_get(pkptr);
					}
			break;
			case TC :
				nb_pk_tc_instantaneous++;
				nb_bits_tc_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						stats_oh_tc_pk++;
						stats_oh_tc_bits += op_pk_total_size_get(pkptr);
						nb_pk_tc_total++;
						nb_bits_tc_total += op_pk_total_size_get(pkptr);
					}
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
	int		pk_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "PK_TYPE", &pk_type);
	
	//Gets the type associated to the pk_type
	switch (pk_type)
		{
			case DATA_PK_TYPE :
				type = DATA;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", pk_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case DATA :
				nb_pk_data_retransmission_instantaneous++;
				nb_bits_data_retransmission_instantaneous += op_pk_total_size_get(pkptr);
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
						stats_oh_data_retransmissions_pk++;
						stats_oh_data_retransmissions_bits += op_pk_total_size_get(pkptr);
						nb_pk_data_retransmission_total++;
						nb_bits_data_retransmission_total += op_pk_total_size_get(pkptr);
					}
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Add a new Ici in the ici_list
Ici* add_in_ici_list(){
	struct_ici*		entry;
	
	//Memory allocation (to have a valid entry outside this function)
	entry = (struct_ici*) op_prg_mem_alloc ( sizeof (struct_ici));
	
	//Info
	entry->ici_ptr		= op_ici_create("mac_dest_indication");
	entry->timeout		= op_sim_time() + TIMEOUT_ICI ;
	
	//Insert it
	op_prg_list_insert( ici_list , entry , OPC_LISTPOS_TAIL);	
	
	//Return the Ici
	return(entry->ici_ptr);
}

//Delete timeouted entries
void delete_timeout_in_ici_list(){
	int				i = 0;
	struct_ici*		entry;
	
	//If the list is empty
	if (op_prg_list_size(ici_list)==0)
		return;
	
	//For each entry
	for (i = op_prg_list_size(ici_list)-1 ; i>=0 ; i--)
		{
			entry = (struct_ici*) op_prg_list_access (ici_list, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout < op_sim_time())
				{
					op_prg_list_remove ( ici_list , i);
					op_prg_mem_free(entry);
				}
		}
	}

//Sends the packet with the specified delay
void pk_send_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	Ici*	ici_ptr;
	
	//Stats
	stats_about_control_pk_flows(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", 		&address_dest);
	op_pk_nfd_get (pkptr, "PK_TYPE", 	&pk_type);
	
	//Random delay to avoid synchronization
	if (pk_type != DATA_PK_TYPE)
		delay += op_dist_uniform(0.005);
	
	//Transmission
	if (PROMISCUOUS_FOR_UNICAST)
		address_dest = -1;
	
	//ici	
	ici_ptr = add_in_ici_list();
	op_ici_install(ici_ptr);
	op_ici_attr_set(ici_ptr,"dest_addr",address_dest);
	
	//Sends the packet
	op_pk_send_delayed(pkptr , STRM_TO_WLAN , delay);// + op_dist_uniform(0.001));
}

//Sends the packet without delay
void pk_send (Packet* pkptr){
	pk_send_delayed(pkptr , 0);
}


//Retransmits the packet with the specified delay
void pk_retransmit_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	Ici*	ici_ptr;
	
	//Stats
	stats_about_control_pk_flows_retransmission(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", &address_dest);
	op_pk_nfd_get (pkptr, "PK_TYPE", &pk_type);
	
	//Transmission
	if (PROMISCUOUS_FOR_UNICAST)
		address_dest = -1;
	
	//Ici management
	ici_ptr = add_in_ici_list();
	op_ici_install(ici_ptr);
	op_ici_attr_set(ici_ptr,"dest_addr",address_dest);

	//Transmission
	op_pk_send_delayed(pkptr , STRM_TO_WLAN , delay);
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
void add_unicast_ack(int dest , int msg_sequence , Packet* pkptr){
	struct_ack*		couple;
	
	//If the list is empty, we must schedule the must verification of timeouts in ack_table (else it is already scheduled)
	if (op_prg_list_size (ack_table) == 0)
		op_intrpt_schedule_self (op_sim_time() + TIMEOUT_UNICAST_ACK , UNICAST_RETRANSMISSIONS_CODE);
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (struct_ack*) op_prg_mem_alloc ( sizeof (struct_ack));
	
	//Info
	couple->dest		= dest;
	couple->msg_sequence		= msg_sequence;
	couple->nb_retry	= 0;
	couple->nb_repairs	= 0;
	couple->timeout 	= op_sim_time() + TIMEOUT_UNICAST_ACK ;
	couple->pkptr		= op_pk_copy(pkptr);
	
	//Insert it
	op_prg_list_insert( ack_table , couple , OPC_LISTPOS_TAIL);	
}

//This packet has been acknowledged
void delete_unicast_ack(int dest , int msg_sequence){
	struct_ack*		couple;
	char			msg[200];
	int				i;
	//Info from packet for debug purpose
	int				pk_type;
	
	//If the list is empty -> I exit !
	if (op_prg_list_size(ack_table)==0)
		{
			if (DEBUG_CONTROL)
				{
					sprintf(msg, "ACKS : the entry corresponding to the msg_sequence %d to destination %d was not found at %f\n",msg_sequence, dest , op_sim_time());
					olsr_debug (msg);
				}
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(ack_table) ; i++)
		{
			//gets the entry
			couple = (struct_ack*) op_prg_list_access (ack_table, i);
			
			if ((couple->dest == dest) && (couple->msg_sequence==msg_sequence))
				{
					if (DEBUG_CONTROL)
						{
							op_pk_nfd_get(couple->pkptr, "PK_TYPE", &pk_type);
							sprintf(msg, "ACKS : %d acked the packet with msg_sequence %d at %f\n", dest , msg_sequence , op_sim_time());							
							switch (pk_type)
								{
									case DATA_PK_TYPE:
										olsr_data(msg);
									break;
									default:
										op_sim_end("The packet is unknown", "for the delete unicast ack procedure","","");
									break;
								}
							olsr_debug (msg);
						}
					op_prg_list_remove(ack_table, i);
					op_prg_mem_free(couple);
					return;
				}
		}
	
	if (DEBUG_CONTROL)
		{
			sprintf(msg, "ACKS : the entry corresponding to the msg_sequence %d to destination %d was not found at %f\n",msg_sequence, dest , op_sim_time());
			olsr_debug (msg);
		}	
}

//Sends an unicast ack
void acknowledges_unicast_packet(int address , int msg_sequence){
	char		msg[150];
	Packet*		pkptr;
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("olsr_pk_unicast_ack");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SOURCE" ,		my_address);
	op_pk_nfd_set (pkptr, "RELAY" ,			my_address);
	op_pk_nfd_set (pkptr, "DEST" ,			address);
	op_pk_nfd_set (pkptr, "TTL" ,			1);
	op_pk_nfd_set (pkptr, "PK_TYPE" ,		UNICAST_ACK_PK_TYPE);
	op_pk_nfd_set (pkptr, "MSG_SEQUENCE" ,	msg_sequence);

	if (DEBUG_CONTROL)
		{
			sprintf(msg,"ACKS : we send an active ack to %d (for pk-id %d) at %f\n", address , msg_sequence , op_sim_time());
			olsr_data(msg);
			olsr_debug(msg);
		}

	//Sends it
	pk_send_delayed(pkptr, op_dist_uniform(0.005));
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


//Sends a data packet to destination dest
void send_data(int dest , int code){
	//packets
	Packet		*pk_dest;	
	//Packet fields
	int			next_hop;
	//control
	char		msg[300];
	
	//next hop
	next_hop = get_next_hop_from_routing_table(dest);
	
	//Creation of the packet
	pk_dest = op_pk_create_fmt("olsr_data");
	op_pk_nfd_set(pk_dest , "MSG_SEQUENCE" , 	current_id++);
	op_pk_nfd_set(pk_dest , "PK_SEQUENCE" , 	current_data_id);
	op_pk_nfd_set(pk_dest , "SOURCE" , 	  		my_address);
	op_pk_nfd_set(pk_dest , "RELAY" , 	  		my_address);
	op_pk_nfd_set(pk_dest , "DEST" ,			next_hop);
	op_pk_nfd_set(pk_dest , "DEST_FINAL" ,		dest);
	op_pk_nfd_set(pk_dest , "TTL" , 			MAX_NETWORK_RADIUS-1);
	op_pk_nfd_set(pk_dest , "HOPS" , 			0);
	op_pk_nfd_set(pk_dest , "PK_TYPE" , 		DATA_PK_TYPE);
	op_pk_nfd_set(pk_dest , "STAT_ID" , 		stats_nb_data_pk);
	
	//Data (parameter*32 bits)
	op_pk_bulk_size_set(pk_dest , (int) op_dist_exponential(DATA_PK_SIZE * 8)  );

	//DEBUG
	if (DEBUG_DATA)
		{
			sprintf(msg,"\n\n-------  DATA-PK : data-pk from %d to %d via %d at %f  (pk_id %d) -------\n", my_address , dest , next_hop , op_sim_time() , current_id-1);
			olsr_debug(msg);
			olsr_data(msg);
		}
	
	//Doest it exist one entry in the routing table ?
	if(next_hop != -1)
		{	
			//Stats
			if (stats_nb_data_pk > MAX_DATA_PK)
				op_sim_end("We have too many data packets","please increase the value of MAX_DATA_PK","in the header block of the olsr process","");
			stats_data_pk	[stats_nb_data_pk].source			= my_address;
			stats_data_pk	[stats_nb_data_pk].dest				= dest;
			stats_data_pk	[stats_nb_data_pk].pk_size			= op_pk_bulk_size_get(pk_dest);
			stats_data_pk 	[stats_nb_data_pk].time_emission	= op_sim_time();
			stats_data_pk 	[stats_nb_data_pk].time_generation	= op_sim_time();
			op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stats_nb_data_pk].src_x_pos));	
			op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stats_nb_data_pk].src_y_pos));	
			sprintf(stats_data_pk	[stats_nb_data_pk].route, "%d ", my_address);
	

			//Transmission
			if (ACK_FOR_DATA)
				add_unicast_ack(next_hop , current_id-1 , pk_dest);
			add_address_id_couple(my_address , current_id-1);
			pk_send(pk_dest);
		}
	else
		{
			//Stats
			if (stats_nb_data_pk > MAX_DATA_PK)
				op_sim_end("We have too many data packets","please increase the value of MAX_DATA_PK","in the header block of the olsr process","");
			stats_data_pk	[stats_nb_data_pk].source			= my_address;
			stats_data_pk	[stats_nb_data_pk].dest				= dest;
			stats_data_pk	[stats_nb_data_pk].pk_size			= op_pk_bulk_size_get(pk_dest);
			stats_data_pk 	[stats_nb_data_pk].time_generation	= op_sim_time();
			op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stats_nb_data_pk].src_x_pos));	
			op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stats_nb_data_pk].src_y_pos));	
			sprintf(stats_data_pk	[stats_nb_data_pk].route, "%d ", my_address);
	

			if (DEBUG_DATA)
				{
					sprintf(msg,"-------  DATA-PK : ERROR ! data-pk from %d to %d via %d at %f  (pk_id %d) -> NO entry in the ROUTING TABLE -> DISCARDED -------\n", my_address , dest , next_hop , op_sim_time() , current_id-1);
					olsr_debug(msg);
					olsr_data(msg);
				}
			op_pk_destroy(pk_dest);
		}
	
	
	
	//Control & Stats
	current_data_id++;	
	stats_nb_data_pk++;
}


















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								CPLEX
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//Links stats, node positions....
void compute_stats_about_graph(){
	//x and y coordinates
	double				x , y ; 
	//To verify link connectivity
	struct_link			*link_elem;
	//Control
	char				msg[1000];
	int					i;

	//---------------------------------------
	//			GPS Position
	//---------------------------------------	
	if (my_stat_id < MAX_NB_NODES)
		{
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"x position",&x);
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"y position",&y);
			stats_positions	[my_stat_id][0]	= x;
			stats_positions	[my_stat_id][1]	= y;
			stats_overheads_bits[my_stat_id]	= (stats_oh_unicast_ack_bits + stats_oh_data_retransmissions_bits + stats_oh_tc_bits + stats_oh_hello_bits) / (op_sim_time() - TIME_BEGIN_STATS);
			stats_overheads_pk	[my_stat_id]	= (stats_oh_unicast_ack_pk + stats_oh_data_retransmissions_pk + stats_oh_tc_pk + stats_oh_hello_pk) / (op_sim_time() - TIME_BEGIN_STATS);
			if (is_AP)
				stats_specificities	[my_stat_id]	= AP;
			else
				stats_specificities	[my_stat_id]	= NORMAL;			
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
	if (op_prg_list_size(links_list)!=0)
		{
			for (i=0; i < op_prg_list_size(links_list) ; i++)
				{
					//Links
					link_elem = op_prg_list_access(links_list , i);
					if (link_elem->sym_timeout > op_sim_time())
						stats_links[my_stat_id][address_to_stat_id[link_elem->dist_intf]] = THICKNESS_PHYSIC_NEIGHBOR;
				}
		}
	
	
}




//Writes all files necessary for cplex
int write_cplex_files(){
	//Control
	int			i , j;	
	char		msg[1000];
	int			nb_nodes_connected = 0;
	//Intermediary variables
	List*		routes				[MAX_NB_NODES][MAX_NB_NODES];
	short		g					[MAX_NB_NODES][MAX_NB_NODES];
	double		length_average		=0;
	//Files
	char		filename[150];
	FILE		*cplex_file;
	FILE		*cplex_file_2;

//--------------------------------------------------
//		Pre-Treatments on the matrix transition
//--------------------------------------------------

	//copies the topology in a temporary graph matrix
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			g[i][j] = stats_links[i][j];

	//matrix 1 || 0
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			g[i][j] = g[i][j] > 0;
	
	
	//Symetrical matrix
	for(i=0 ; i<MAX_NB_NODES ; i++)
		for (j=0 ; j<MAX_NB_NODES ; j++)
			if (g[i][j] > g[j][i])
				g[j][i] = g[i][j];

	
	
//--------------------------------------------------
//	CPLEX Format  (overheads in bits per second)
//--------------------------------------------------

	//Opens the associated file
	format_int_to_string( op_sim_time() , msg , 4);
	sprintf(filename,"results_olsr/%scplex_graph_radio_bps_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		printf("Error : we cannot create the file %s\n",filename);
	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_nodes);						
	
	//--------------------
	//Radio Graph Matrix
	//--------------------
	for(i=0 ; i<nb_nodes ; i++)
		{		
			fprintf(cplex_file , "%f ", stats_overheads_bits[i]);				
			for(j=0;j<nb_nodes;j++)
				fprintf(cplex_file,"%d ",  g[i][j]);
			fprintf(cplex_file,"\n");							
		}			
	fclose(cplex_file);
	
//--------------------------------------------------
//	CPLEX Format  (overheads in packets per second)
//--------------------------------------------------

	//Opens the associated file 
	format_int_to_string( op_sim_time() , msg , 4);
	sprintf(filename,"results_olsr/%scplex_graph_radio_pps_%s%S.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		printf("Error : we cannot create the file %s\n",filename);
	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_nodes);						
	
	//--------------------
	//Radio Graph Matrix
	//--------------------
	for(i=0 ; i<nb_nodes ; i++)
		{
			fprintf(cplex_file , "%f ", stats_overheads_pk[i]);

			for(j=0;j<nb_nodes;j++){
				fprintf(cplex_file,"%d ",  g[i][j]);
				if ((i == 3) && (j==0))
					printf("ya le lien 1-4 ? %d\n", g[i][j]);
				}
			fprintf(cplex_file,"\n");							
		}			
	fclose(cplex_file);
	
	
//--------------------------------------------------
//				CPLEX Shortest Routes
//--------------------------------------------------

	//Opens the associated file 
	format_int_to_string( op_sim_time() , msg , 4);
	
	//All ad hoc routes
	sprintf(filename,"results_olsr/%scplex_ad_hoc_routes_id_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file = fopen(filename,"w");
	if (cplex_file==NULL)
		{
			printf("Error : we cannot create the file %s\n",filename);
		}
	
	//All hybrid routes
	sprintf(filename,"results_olsr/%scplex_hybrid_routes_id_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
	cplex_file_2 = fopen(filename,"w");
	if (cplex_file_2 == NULL)
		printf("Error : we cannot create the file %s\n",filename);

	
	//--------
	//Headers
	//--------
	fprintf(cplex_file,"%d\n",nb_nodes * (nb_nodes-1));						
	fprintf(cplex_file_2,"%d\n",nb_nodes-1);						
	
	//---------------------
	//Routes intialization
	//---------------------
	for (i=0 ; i < nb_nodes ; i++)
		for(j=0 ; j < nb_nodes ; j++)
			routes[i][j] = op_prg_list_create();

	//-------------------------
	//List of Shortest Routes
	//-------------------------
	//For each source/destination pair :
	compute_shortest_routes(routes , g , nb_nodes);
	for(i=0;i<nb_nodes;i++)
		for(j=0;j<nb_nodes;j++)
			{
				//All ad hoc routes
				if ((i != j) && (op_prg_list_size(routes[i][j]) != 0))
					{
						length_average += op_prg_list_size(routes[i][j]) - 1;
						route_list_to_str_of_stat_id(routes[i][j] , msg);
						fprintf(cplex_file , "%s -1\n", msg);
					}
				
				//All hybrid routes
				if ((op_prg_list_size(routes[i][j]) != 0) && (stats_specificities[i]==NORMAL) && (stats_specificities[j]==AP))
					{
						nb_nodes_connected ++;
						length_average += op_prg_list_size(routes[i][j]) - 1;
						route_list_to_str_of_stat_id(routes[i][j] , msg);
						fprintf(cplex_file_2 , "%s -1\n", msg);
					}
			}
	fprintf(cplex_file,"-1\n");							
	fclose(cplex_file);
	fprintf(cplex_file_2,"-1\n");							
	fclose(cplex_file_2);
	
	
	
//--------------------------------------------------
//		  MEMORY DESALLOCATION
//--------------------------------------------------
	//---------------------
	//Routes Destruction
	//---------------------
	for (i=0 ; i < nb_nodes ; i++)
		for(j=0 ; j < nb_nodes ; j++)
			{
				route_list_empty(routes[i][j]);
				op_prg_mem_free(routes[i][j]);
			}

	
//--------------------------------------------------
//		  NEXT CPLEX WRITING REQUIRED ?
//--------------------------------------------------

	//CDS not connected -> delete useless files
	if (nb_nodes-nb_aps != nb_nodes_connected)
		{
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results_olsr/%scplex_graph_radio_bps_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			remove(filename);
			sprintf(filename,"results_olsr/%scplex_graph_radio_pps_%s%S.txt" , prefix_results_file , msg , suffix_results_file);
			remove(filename);
			sprintf(filename,"results_olsr/%scplex_ad_hoc_routes_id_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			remove(filename);
			sprintf(filename,"results_olsr/%scplex_hybrid_routes_id_%s%s.txt" , prefix_results_file , msg , suffix_results_file);
			remove(filename);
		}
	
	//All the CDS is connected ?
	return (nb_nodes-nb_aps == nb_nodes_connected);
}


//Compute all stats necessary for cplex-files, and launch the cplex writting
void compute_and_write_cplex_files(){

	//initalization for the first node
	if (my_stat_id == 0)
		stats_variable_reinitialization();
	
	//Computes the global graph according to local information
	compute_stats_about_graph();
	
	//Write cplex statistics
	if (my_stat_id == nb_nodes - 1)
		{
			if (write_cplex_files())
				op_sim_end("We have computed valid cplex files", "all was connected", "we have a representative topology","");
		}
	op_intrpt_schedule_call (op_sim_time()+1.0 , 0 , compute_and_write_cplex_files , -1);
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

void olsr_test(char* msg){
	FILE*	file;
	char	str[200];
	
	if (op_sim_time() < TIME_BEGIN_DEBUG)
		return;
	
	sprintf(str,"results_olsr/%solsr_test%s.txt" , prefix_results_file , suffix_results_file);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}	

void olsr_data(char* msg){
	FILE*	file;
	char	str[200];
	
	if (op_sim_time() < TIME_BEGIN_DEBUG)
		return;
	
	sprintf(str,"results_olsr/%solsr_data%s.txt" , prefix_results_file , suffix_results_file);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void olsr_debug(char* msg){
	FILE*	file;
	char	str[50];
	
	if (op_sim_time() < TIME_BEGIN_DEBUG)
		return;
	
	if (my_address<10)
		sprintf(str,"results_olsr/details_per_node/results_0%d.txt",my_address);
	if (my_address>=10)
		sprintf(str,"results_olsr/details_per_node/results_%d.txt",my_address);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void print_routing_list(){
	struct_routing		*routing_elem;
	int					i;
	char				msg[150];
	
	//if (!DEBUG_ROUTE)
	//	return;
	
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "ROUTING LIST (%f) :\n", op_sim_time());		
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("DEST	|	RELAY	|	DISTANCE\n");
	
	for(i=0; i<op_prg_list_size(routing_list) ; i++)
		{
			routing_elem = op_prg_list_access(routing_list , i);
			
			sprintf(msg, "%d	|	%d	|	%d\n", routing_elem->destination , routing_elem->next_hop , routing_elem->distance );
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_topology_list(){
	struct_topology		*topology_elem;
	int					i;
	char				msg[150];
	
	//if (!DEBUG_TC)
	//	return;
	
	//Sort the topology
	op_prg_list_sort(topology_list, topology_compare);
	
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "TOPOLOGY LIST (%f) :\n", op_sim_time());			
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("DEST	|	RELAY	|	TIMEOUT	|	SEQ NUMBER\n");
	
	for(i=0; i<op_prg_list_size(topology_list) ; i++)
		{
			topology_elem = op_prg_list_access(topology_list , i);
			
			sprintf(msg, "%d	|	%d	|	%f	|	%d\n", topology_elem->destination , topology_elem->relay , topology_elem->timeout , topology_elem->ansn );
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_mpr_selector_list(){
	struct_mpr_selector		*mpr_selector_elem;
	int						i;
	char					msg[150];
	
	//if (!DEBUG_MPR)
	//	return;
		
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "MPR SELECTOR LIST (%f) :\n", op_sim_time());			
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("ADDR	|	TIMEOUT\n");
	
	for(i=0; i<op_prg_list_size(mpr_selector_list) ; i++)
		{
			mpr_selector_elem = op_prg_list_access(mpr_selector_list , i);
			
			sprintf(msg, "%d	|	%f\n", mpr_selector_elem->address , mpr_selector_elem->timeout);
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_mpr_list(){
	int		*mpr_elem;
	int		i;
	char	msg[150];
	
	//if (!DEBUG_MPR)
	//	return;
		
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "MPR LIST (%f) :\n", op_sim_time());		
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("ADDR\n");
	
	for(i=0; i<op_prg_list_size(mpr_list) ; i++)
		{
			mpr_elem = op_prg_list_access(mpr_list , i);
			
			sprintf(msg, "%d | ", *mpr_elem);
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_neighbors_list(){
	struct_neighbor		*neigh_elem;
	int					i;
	char				msg[150];
	
	//if (!DEBUG_NEIGHBORHOOD)
	//	return;
		
		
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "NEIGHBORS LIST (%f) :\n", op_sim_time());			
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("ADDR	|   TYPE	| WILLINGNESS \n");
	
	for(i=0; i<op_prg_list_size(neighbors_list) ; i++)
		{
			neigh_elem = op_prg_list_access(neighbors_list , i);
			
			sprintf(msg, "%d	|	%d	|	%d\n", neigh_elem->address , neigh_elem->type , neigh_elem->willingness);
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_two_neighbors_list(){
	struct_two_neighbor		*two_neigh_elem;
	int						i;
	char					msg[150];
	
	//if (!DEBUG_NEIGHBORHOOD)
	//	return;
		
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "2-NEIGHBORS LIST (%f) :\n", op_sim_time());			
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("ADDR	|   RELAY	| TIMEOUT \n");
	
	for(i=0; i<op_prg_list_size(two_neighbors_list) ; i++)
		{
			two_neigh_elem = op_prg_list_access(two_neighbors_list , i);
			
			sprintf(msg, "%d	|	%d	|	%f\n", two_neigh_elem->address , two_neigh_elem->relay , two_neigh_elem->timeout);
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_links_list(){
	struct_link		*link_elem;
	int				i;
	char			msg[150];
	
	//if (!DEBUG_NEIGHBORHOOD)
	//	return;
		
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "LINKS LIST (%f) :\n", op_sim_time());			
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("DIST	|   LOCAL	|	TIMEOUT_ASYM	|	TIMEOUT_SYM	|	TIMEOUT \n");
	
	for(i=0; i<op_prg_list_size(links_list) ; i++)
		{
			link_elem = op_prg_list_access(links_list , i);
			
			sprintf(msg, "%d	|	%d	|	%f		|	%f	|	%f\n", link_elem->dist_intf , link_elem->local_intf , link_elem->asym_timeout , link_elem->sym_timeout , link_elem->timeout );
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");	
	
}

void print_addr_msg_sequence_list(){
	int					i=0;
	struct_addr_msg_sequence*	couple;
	char				msg[150];
	
	//if (!DEBUG_CONTROL)
	//	return;
	
	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg, "ID TABLE (%f):\n", op_sim_time());		
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("Source	|   Pk Id	|	Timeout \n");
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(addr_msg_sequence_list)==0)
		{
			olsr_debug ("\n\n\n");
			return ;
		}	
	
	//For each entry of the list
	for(i=0; i< op_prg_list_size(addr_msg_sequence_list);i++)
		{  
			couple = (struct_addr_msg_sequence*) op_prg_list_access(addr_msg_sequence_list,i);
			//.....compare it
			sprintf(msg,"	%d	|	%d	|	%f\n",couple->address , couple->msg_sequence , couple->timeout);
			olsr_debug(msg);
		}
	olsr_debug ("\n\n\n");
}



void print_ack_table(){
	struct_ack*		entry;
	int				i;
	char			msg[200];
	
	//if (!DEBUG_CONTROL)
	//	return;

	//Common Information
	olsr_debug ("-------------------------------------------------------------------------\n");
	sprintf (msg , "ACK TABLE (%f) :\n", op_sim_time());		
	olsr_debug(msg);
	olsr_debug ("-------------------------------------------------------------------------\n\n");
	
	olsr_debug ("Destination	|   msg_sequence	|	Nb Retries	|     Timeout \n");
	
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(ack_table)==0)
		{
			olsr_debug ("\n\n\n");
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(ack_table) ; i++)
		{
			//gets the entry
			entry = (struct_ack*) op_prg_list_access (ack_table, i);

			//Useless, but avoid a 'memory access error' if there is a bug
			if (entry!=NULL)
				{
					//Prints it
					sprintf(msg,"	%d	|	%d	|		%d	|	%f \n" , entry->dest , entry->msg_sequence , entry->nb_retry , entry->timeout);
					olsr_debug (msg);
				}
		}
	olsr_debug ("\n\n\n");
}


void print_neighbors(){
op_sim_end("non encore fait\n","","","");
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
	
	if (OPC_TRUE)//DEBUG)
		{
			sprintf(msg,"\n\n---------------------- END - %f seconds -------------------------\n\n\n",op_sim_time());
			olsr_debug(msg);
	
			//Neighborhood
			print_links_list();
			print_neighbors_list();
			print_two_neighbors_list();
	
			//MPR
			print_mpr_list();
			print_mpr_selector_list();

			//TOPOLOGY
			print_topology_list();
	
			//ROUTING TABLE
			print_routing_list();
	
			//Control
			//print_addr_msg_sequence_list();
			//print_ack_table();
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
	void olsr_process (void);
	Compcode olsr_process_init (void **);
	void olsr_process_diag (void);
	void olsr_process_terminate (void);
	void olsr_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
olsr_process (void)
	{
	int _block_origin = 0;
	FIN (olsr_process ());
	if (1)
		{
		/* Variables used in state transitions.		*/
		int			intrpt_code;


		FSM_ENTER (olsr_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (Init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "Init", "olsr_process () [Init enter execs]")
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
			FSM_EXIT (1,olsr_process)


			/** state (Init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "Init", "olsr_process () [Init exit execs]")
				{
				}


			/** state (Init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Init", "INIT_AFTER_MAC")
				/*---------------------------------------------------------*/



			/** state (INIT_AFTER_MAC) enter executives **/
			FSM_STATE_ENTER_FORCED (1, state1_enter_exec, "INIT_AFTER_MAC", "olsr_process () [INIT_AFTER_MAC enter execs]")
				{
				List 		*liste;
				//Control
				int			addr_attribution;
				char		str[100];
				FILE		*file;
				int 		i,j, addr; 
				char		msg[150];
				//Topology
				char		var_name[200];
				int			nb_fixed_nodes , nb_mobile_nodes , is_node_AP;
				//AP Position
				int			process_id , node_id;
				double		XMAX , YMAX;
				int			MOBILITY_MODEL;
				//SPEEDS
				double		low_mob_max , low_mob_min , high_mob_max , high_mob_min;
				//CPLEX
				double		cplex_time;
				
				
				
				//----------------------------------------------------
				//
				//					TOPOLOGY
				//
				//-----------------------------------------------------
				
				
				//NB :   AP / normal nodes
				if (nb_nodes == 0)
					{
						//NB :   AP / normal nodes
						nb_fixed_nodes 		= op_topo_object_count(OPC_OBJTYPE_NDFIX);
						for(i=0 ; i<nb_fixed_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDFIX , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_ID_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
				
						nb_mobile_nodes 	= op_topo_object_count(OPC_OBJTYPE_NDMOB);
						for(i=0 ; i<nb_mobile_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDMOB , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_ID_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
						
						//Names of files for stats
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_LOW_MAX",	&low_mob_max);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_LOW_MIN",	&low_mob_min);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_HIGH_MAX",	&high_mob_max);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE,	"SP_HIGH_MIN",	&high_mob_min);
				
						sprintf(prefix_results_file, "olsr_%d_(%.0lf_%.0lf)_(%.0lf_%.0lf)-%d_", 	nb_nodes_expected + nb_aps_expected , low_mob_min , low_mob_max , high_mob_min , high_mob_max , begin_time);		
						sprintf(suffix_results_file, "");
				}
				
				
				
				
				
				//----------------------------------------------------
				//
				//	Recuperation of simulation parameters
				//
				//-----------------------------------------------------
				
				//The simulation paramaters
				//For this Node
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG",				&DEBUG);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_MPR",			&DEBUG_MPR);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_NEIGHBORHOOD",	&DEBUG_NEIGHBORHOOD);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_TC",				&DEBUG_TC);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_DATA", 			&DEBUG_DATA);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_CONTROL", 		&DEBUG_CONTROL);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_OVERHEAD", 		&DEBUG_OVERHEAD);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_TOPO", 			&DEBUG_TOPO);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_CONNECTIONS", 		&NB_CONNECTIONS);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"DATA_PK_SIZE", 		&DATA_PK_SIZE);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE,	"INTERARRIVAL_DATA_PK", &INTERARRIVAL_DATA_PK);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_PK_PER_FLOW", 		&NB_PK_PER_FLOW);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"ACK_FOR_DATA", 		&ACK_FOR_DATA);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, 	"CPLEX_TIME",			&cplex_time);
				
					
				//The node parameters
				sprintf(var_name , "%s.is_AP" , PROCESS_ID_NAME);
				op_ima_obj_attr_get(op_topo_parent(op_id_self()),	var_name ,	&is_AP); 
				
				
				
				
				
				//----------------------------------------------------
				//
				//				POSITION OF THE AP
				//
				//-----------------------------------------------------
				
				if (is_AP)
					nb_aps++;
				
				//The AP is central only if it exists one single AP
				if ((is_AP) && (nb_aps_expected == 1))
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
				//				POSITION OF THE AP
				//
				//-----------------------------------------------------
				
				
				if(is_AP)
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
				//				General Infos
				//
				//-----------------------------------------------------
				
				//--------------- Various ---------------
				
				current_id 			= op_dist_uniform(30000);				//the first id of the packet I will send
				current_tc_id		= 0;
				current_data_id		= 0;
				
				
				
				
				
				//----------------------------------------------------
				//
				//				Overheads
				//
				//-----------------------------------------------------
				
				stats_oh_tc_pk						= 0;
				stats_oh_hello_pk					= 0;
				stats_oh_data_pk					= 0;
				stats_oh_unicast_ack_pk				= 0;
				stats_oh_data_retransmissions_pk	= 0;
				
				stats_oh_tc_bits					= 0;
				stats_oh_hello_bits					= 0;
				stats_oh_data_bits					= 0;
				stats_oh_unicast_ack_bits			= 0;
				stats_oh_data_retransmissions_bits	= 0;
				
				
				
				
				//----------------------------------------------------
				//
				//		Open the file for out messages
				//
				//-----------------------------------------------------
				
				//-------- protection against arrays overflows -------
				if (my_address >= MAX_ADDRESS)
					op_sim_end("We have too many nodes","please increase the value of MAX_ADDRESS","in the header block of the cdcl_routing process","");
				if (nb_nodes >= MAX_NB_NODES)
					op_sim_end("We have too many nodes","please increase the value of MAX_NB_NODES","in the header block of the cdcl_routing process","");
				
				
				//----------------------- Stats ---------------------
				my_stat_id = nb_nodes++;							//The first node has id 0
				address_to_stat_id	[my_address] = my_stat_id;		//Convert an address into an id
				stat_id_to_address	[my_stat_id] = my_address;		//The inverse
				
				
				//--------------------- Per node --------------------
				
				if (my_address<10)
					sprintf(str,"results_olsr/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
					sprintf(str,"results_olsr/details_per_node/results_%d.txt",my_address);
				file = fopen(str,"w");
				fclose(file);
				
				
				
				//--------------- Global periodic stats ------------
				
				if (my_stat_id==0)
					{
						//Stats About Data Packets
						for(i=0; i < MAX_DATA_PK ; i++)
							{
								stats_data_pk	[i].source 				= 0;
								stats_data_pk	[i].dest 				= 0;
								stats_data_pk	[i].pk_size 			= 0;
								stats_data_pk	[i].hops 				= 0;
								stats_data_pk	[i].nb_retry 			= 0;
								stats_data_pk 	[i].time_emission 		= 0;
								stats_data_pk 	[i].time_reception		= 0;
							}
						
						//Stats About TC Packets
						for(i=0; i < MAX_TC_PK ; i++)
							{
								stats_tc_pk	[i].source 					= 0;
								stats_tc_pk	[i].nb_forwarders 			= 0;
								stats_tc_pk	[i].nb_receivers			= 0;
								stats_tc_pk [i].time_emission 			= 0;
								stats_tc_pk [i].time_last_reception		= 0;
							}
				
						if  (DEBUG_DATA)
							{
								sprintf(str,"results_olsr/%solsr_data%s.txt" , prefix_results_file , suffix_results_file);
								file = fopen(str,"w");
								fprintf(file,"##################################################################\n");
								fprintf(file,"#        DEBUG for DATA Packets Emission/Reception in OLSR       #\n");
								fprintf(file,"##################################################################\n");
								fclose(file);
							}
						if  (DEBUG_OVERHEAD)
							{
								sprintf(str,"results_olsr/%solsr_network_control%s.txt" , prefix_results_file , suffix_results_file);
								file = fopen(str,"w");
								fprintf(file,"##################################################################\n");
								fprintf(file,"#               DEBUG for Flows Overheads in OLSR                #\n");
								fprintf(file,"##################################################################\n");
								fprintf(file , "# All flows are in packets per second per node (RET signifies 'Retransmission')\n");
								fprintf(file , "TIME		| 	ACKS		|	HELLO		|	TC		|	DATA		|	DATA RET\n");
								fclose(file);
							}
						
					}
				
				
				
				
				
				//----------------------------------------------------
				//
				//			LISTS INTIALIZATIONS
				//
				//-----------------------------------------------------
				
					
				//Packet Common
				ici_list					= op_prg_list_create();
				addr_msg_sequence_list		= op_prg_list_create();
				
				//Acks
				ack_table					= op_prg_list_create();
				
				//Links
				links_list					= op_prg_list_create();
				
				
				//Neighbors
				neighbors_list				= op_prg_list_create();
				two_neighbors_list			= op_prg_list_create();
				
				
				//MPR
				mpr_list					= op_prg_list_create();
				mpr_selector_list			= op_prg_list_create();
				
				//TOPOLOGY
				topology_list				= op_prg_list_create();
				
				
				//ROUTING TABLE
				routing_list				= op_prg_list_create();
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//				INTERRUPTIONS
				//
				//-----------------------------------------------------
				
				
				//HELLOS & TC
				op_intrpt_schedule_call (op_sim_time() + op_dist_uniform(INTERVALL_HELLO) ,	0 , hello	, NULL);
				//NB : let the neighborhood/MPR set converge before sending TC packets
				op_intrpt_schedule_call (op_sim_time() + op_dist_uniform(INTERVALL_TC) + 3 * INTERVALL_HELLO ,	0 , tc 		, NULL);
				
				//Topology Figures
				if (DEBUG_TOPO)
					op_intrpt_schedule_call (op_sim_time() , 0 , write_topology_figures , NULL);
				
				//Cplex Files
				if (cplex_time > 0)
					op_intrpt_schedule_call (cplex_time , 0 , compute_and_write_cplex_files , -1);
				
				//Periodic Updates
				op_intrpt_schedule_self (op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS , PERIODIC_FUNCTIONS_CODE);
				
				
				
				//Data Transmission
				//For nb_connections nodes, lauch a flow transmission of data packets
				if (NB_CONNECTIONS > current_nb_connections)
					{
						op_intrpt_schedule_self (TIME_BEGIN_DATA + op_dist_uniform(INTERARRIVAL_DATA_PK*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE);
						current_nb_connections++;
					}
				
				}


			/** state (INIT_AFTER_MAC) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "INIT_AFTER_MAC", "olsr_process () [INIT_AFTER_MAC exit execs]")
				{
				}


			/** state (INIT_AFTER_MAC) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "INIT_AFTER_MAC", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, state2_enter_exec, "idle", "olsr_process () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,olsr_process)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "idle", "olsr_process () [idle exit execs]")
				{
				//printf ("%d - %d - %d - %d - %d\n", op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_SELF, OPC_INTRPT_STRM, OPC_INTRPT_ENDSIM);
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (ENDSIM)
			FSM_TEST_COND (PERIODIC_FUNCTIONS)
			FSM_TEST_COND (PK_DATA_GENERATE)
			FSM_TEST_COND (PK_FROM_LOWER)
			FSM_TEST_COND (UNICAST_RETRANSMISSIONS)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 4, state4_enter_exec, ;, "ENDSIM", "", "idle", "ENDSIM")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "PERIODIC_FUNCTIONS", "", "idle", "PERIODIC_FUNCTIONS")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "PK_DATA_GENERATE", "", "idle", "DATA")
				FSM_CASE_TRANSIT (3, 6, state6_enter_exec, ;, "PK_FROM_LOWER", "", "idle", "FROM_LOWER")
				FSM_CASE_TRANSIT (4, 7, state7_enter_exec, ;, "UNICAST_RETRANSMISSIONS", "", "idle", "RET_UNICAST")
				}
				/*---------------------------------------------------------*/



			/** state (PERIODIC_FUNCTIONS) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "PERIODIC_FUNCTIONS", "olsr_process () [PERIODIC_FUNCTIONS enter execs]")
				{
				//----------------------------------------------------------------
				//				Periodic Functions
				//----------------------------------------------------------------
				
				//Control
				char	filename[50];
				FILE*	file;
				char	tmp[1000];
				int		i;
				
				//Packets common
				void delete_timeout_in_ici_list();
				delete_timeout_in_addr_msg_sequence_list();
				
				
				
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
				
					 
				//------ STATS Stored in Files -------
				 
						if (my_stat_id+1 == nb_nodes)
							{
							//Periodic stats about network control
								//File Initialization	
								if  (DEBUG_OVERHEAD)
									{
				
										sprintf(filename,"results_olsr/%solsr_network_control%s.txt" , prefix_results_file , suffix_results_file);
										file = fopen (filename, "a");
							
										sprintf (tmp, "%f	|", op_sim_time());
										fprintf(file , tmp);
						
										sprintf (tmp, "	%f	|", (double)nb_pk_unicast_ack_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_unicast_ack_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_hello_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_hello_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_tc_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_hello_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_data_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_data_instantaneous = 0;
										fprintf(file , tmp);		
					
										sprintf (tmp, "	%f	|", (double)nb_pk_data_retransmission_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_data_instantaneous = 0;
										fprintf(file , tmp);		
					
										fprintf(file , "\n");	
										fclose(file);
									}
							}
				
				
				
				//Global Stats
					//Degree
						average_degree +=  get_nb_neighbors();
				
				
						
					}
				
				//Next Stats
				op_intrpt_schedule_self(op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS, PERIODIC_FUNCTIONS_CODE);
				}


			/** state (PERIODIC_FUNCTIONS) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "PERIODIC_FUNCTIONS", "olsr_process () [PERIODIC_FUNCTIONS exit execs]")
				{
				}


			/** state (PERIODIC_FUNCTIONS) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "PERIODIC_FUNCTIONS", "idle")
				/*---------------------------------------------------------*/



			/** state (ENDSIM) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "ENDSIM", "olsr_process () [ENDSIM enter execs]")
				{
				//----------------------------------------------------------------
				//				SIMULATION END
				//----------------------------------------------------------------
				
				//Collects some stats when the simulation ends
					//CONTROL
					char	filename[100];
					FILE	*file;
					FILE	*data_file;
					FILE	*tc_file;
					int 	i , j;
					char	msg[2000];
					//DURATION
					double	stats_time_duration;
					//DATA
					int		nb_data_pk							= 0;
					int		nb_data_pk_sent						= 0;
					int		nb_data_pk_received					= 0;
					int		throughput_data_pk					= 0;
					int		hops_data_pk						= 0;
					int		nb_retransmissions_data_pk			= 0;
					double	delay_data_pk 						= 0;
					double	tmp_distance						= 0;
					int		length_distribution	[MAX_NETWORK_RADIUS];
					//TC
					int		nb_tc_pk_sent						= 0;
					int		nb_tc_pk_received					= 0;			//If n nodes received the TC packet -> =n
					int		nb_tc_pk_succesfull					= 0;			//If n nodes received the TC packet -> =1
					int		nb_forwarders_tc_pk					= 0;
					double	delay_tc_pk							= 0;
					//SPEED
				   	double	SPEED_HIGH_MIN 						= 0;
				   	double	SPEED_HIGH_MAX 						= 0;
				   	double	SPEED_LOW_MIN 						= 0;
				   	double	SPEED_LOW_MAX 						= 0;
					int		speed_class							= 0;
					//TOPOLOGY
					double	X_MAX								= 0;
					double	Y_MAX								= 0;
					//OVERHEADS
					double	nb_pk_total							= 0;
					double	nb_bits_total						= 0;
					
				//Stats Per node
					individual_statistics_generate();
				
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
							//Initialization
							for (i=0; i< MAX_NETWORK_RADIUS ; i++)
								length_distribution[i] = 0;
							
							//Time Duration for Stats Simualtion
							stats_time_duration = op_sim_time()-TIME_BEGIN_STATS;
							
							//General Parameters
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MIN", 	&SPEED_HIGH_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MAX",	&SPEED_HIGH_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MIN", 	&SPEED_LOW_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MAX",	&SPEED_LOW_MAX); 
						
				
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "X_MAX",		&X_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Y_MAX",		&Y_MAX); 
							
				
							//-------------------
							//       DATA
							//-------------------
							if (DEBUG_DATA)
								{
									sprintf(filename,"results_olsr/%solsr_debug_pk_data%s.txt" , prefix_results_file , suffix_results_file);
									data_file = fopen(filename , "w");
									fprintf(data_file,"SRC	|	DEST	|	SIZE	|	HOPS	|	RETRY	|	GENERATED	|	SENT		|	RECEIVED	|	DELAY		|	DISTANCE	|	ROUTE\n");	
								}
							for (i=0 ;  i < stats_nb_data_pk ; i++ )
								{
									//The pk is effective (valid final_dest...)
									if (stats_data_pk [i].time_generation != -1)
										nb_data_pk++;
									
									if (stats_data_pk [i].time_emission != 0)
										nb_data_pk_sent++;
									
									//The packet was received
									if (stats_data_pk [i].time_reception != 0)
										{
											nb_data_pk_received++;
											throughput_data_pk 			+= stats_data_pk [i].pk_size;
											hops_data_pk 				+= stats_data_pk [i].hops;
											nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
											delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;
											(length_distribution [stats_data_pk [i].hops]) ++;
										}
									
									tmp_distance = sqrt( pow(stats_data_pk [i].src_x_pos - stats_data_pk [i].dest_x_pos , 2) + pow(stats_data_pk [i].src_y_pos - stats_data_pk [i].dest_y_pos , 2));
									if (DEBUG_DATA)
										fprintf(data_file,"%d		%d		%d		%d		%d		%f		%f		%f		%f		%f		%s \n", stats_data_pk[i].source , stats_data_pk[i].dest , stats_data_pk[i].pk_size, stats_data_pk[i].hops , stats_data_pk[i].nb_retry , stats_data_pk[i].time_generation , stats_data_pk[i].time_emission , stats_data_pk[i].time_reception , stats_data_pk[i].time_reception - stats_data_pk[i].time_emission , tmp_distance , stats_data_pk[i].route);
								}
							if (DEBUG_DATA)
								fclose(data_file);
							
							//-------------------
							//    TC PACKETS
							//-------------------
							if (DEBUG_TC)
								{
									sprintf(filename,"results_olsr/%solsr_debug_pk_tc%s.txt" , prefix_results_file , suffix_results_file);
									tc_file = fopen(filename , "w");
									fprintf(tc_file,"SRC	|	TIME EMISSION	|	TIME LAST_RECEPTION	|	NB FOWARDERS	|	NB RECEIVERS\n");	
								}
							for (i=0 ;  i < stats_nb_tc_pk ; i++ )
								{
									if (stats_tc_pk [i].time_emission != 0)
										nb_tc_pk_sent++;
									
									if (stats_tc_pk [i].time_last_reception != 0)
										{
											nb_tc_pk_succesfull++;
											nb_tc_pk_received	+= stats_tc_pk [i].nb_receivers;
											nb_forwarders_tc_pk	+= stats_tc_pk [i].nb_forwarders;
											delay_tc_pk			+= stats_tc_pk [i].time_last_reception - stats_tc_pk [i].time_emission;
										}	
									
									if (DEBUG_TC)
										fprintf(tc_file,"%d	|	%f		|		%f		|		%d		|		%d\n", stats_tc_pk[i].source , stats_tc_pk[i].time_emission , stats_tc_pk[i].time_last_reception , stats_tc_pk[i].nb_forwarders , stats_tc_pk[i].nb_receivers);
											
								}
							if (DEBUG_TC)
								fclose(tc_file);
								
				
							//File Initialization	
							sprintf(filename,"results_olsr/%solsr_global_stats%s.txt" , prefix_results_file , suffix_results_file);
							file = fopen (filename, "w");
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, "|                                          Global Statistics for OLSR                                        |\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				   
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   PARAMETERS                                               |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "->High Speed \n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_HIGH_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_HIGH_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_high_speed_nodes);
							fprintf(file, "->Low Speed\n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_LOW_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_LOW_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_low_speed_nodes);
							fprintf(file, "Nb MPR per 2-Neighbor						:	%d\n",					MIN_MPR);
							fprintf(file, "Degree								:	%f\n",							(double)average_degree / (nb_nodes * (stats_time_duration/INTERVALL_PERIODIC_FUNCTIONS))  );
							fprintf(file, "X-coordinate max							:	%f\n",						X_MAX);
							fprintf(file, "Y-coordinate max							:	%f\n",						Y_MAX);
							fprintf(file, "Duration (in seconds)						:	%f\n", 					op_sim_time());
							fprintf(file, "Number of Communicating Nodes (i.e. nb of flows)	:	%d\n", 				NB_CONNECTIONS);
							fprintf(file, "Interarrival pk time						:	%f\n", 						INTERARRIVAL_DATA_PK);
							fprintf(file, "Packet Size (in octets)						:	%d\n", 					DATA_PK_SIZE);
							fprintf(file, "Number of packet per flow					:	%d\n", 					NB_PK_PER_FLOW);
							fprintf(file, "\n\n");
				
							
							
										
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                              DATA                                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				
							fprintf(file, "Nb Packets Generated						:	%d\n",  			nb_data_pk );
							fprintf(file, "Nb Packets Sent							:	%d\n",  			nb_data_pk_sent );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received );
							fprintf(file, "Delivery Ratio (for generated pk)				:	%f\n", 		(double) nb_data_pk_received 		/ (double)nb_data_pk );
							fprintf(file, "Delivery Ratio (for sent pk)					:	%f\n", 			(double) nb_data_pk_received 		/ (double)nb_data_pk_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk 				/ (double)nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk 		/ (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk 				/ nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk / hops_data_pk );
							fprintf(file, "\n");
							fprintf(file, "--> Route length distribution \n");
							for (i=1; i< MAX_NETWORK_RADIUS ; i++)
								if (length_distribution[i] != 0)
									fprintf(file, "%d hops								:	%d\n",		i , 	length_distribution[i]);					
							fprintf(file, "\n\n");
				
							
							
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                       TOPOLOGY CONTROL PACKETS                                             |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							
							fprintf(file, "Nb TC Packets Sent						:	%d\n",  			nb_tc_pk_sent );
							fprintf(file, "Delivery Ratio per TC packet					:	%f\n", 			(double) nb_tc_pk_received 		/ ((double) nb_tc_pk_succesfull * (nb_nodes-1)) );				//Receivers : all the nodes except the source
							fprintf(file, "Percentage of forwarders per TC packet			:	%f\n", 		(double) nb_forwarders_tc_pk 	/ ((double) nb_tc_pk_succesfull * (nb_nodes-1)) );
							fprintf(file, "Delay before the last reception				:	%f\n", 			(double) delay_tc_pk 			/ (double) nb_tc_pk_succesfull );
							fprintf(file, "\n\n");
							
							
							
							
							
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   Network Control                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
					
							nb_pk_total = (nb_pk_unicast_ack_total + nb_pk_data_retransmission_total)	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_pk_total += (nb_pk_hello_total + nb_pk_tc_total)							/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes);
							
							fprintf(file, "--> Average Values in packet per node per second \n");
							fprintf(file, "Unicast Acks							:	%f\n", 					(double) nb_pk_unicast_ack_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Hellos								:	%f\n", 					(double) nb_pk_hello_total							/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Tc									:	%f\n", 					(double) nb_pk_tc_total								/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 					(double) nb_pk_data_total							/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 				(double) nb_pk_data_retransmission_total			/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 				(double) nb_pk_total);
							fprintf(file, "\n\n");
							
							nb_bits_total = (nb_bits_unicast_ack_total +nb_bits_data_retransmission_total)	/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);			
							nb_bits_total += (nb_bits_hello_total + nb_bits_tc_total)						/((op_sim_time()-TIME_BEGIN_STATS) * nb_nodes);			
							
							fprintf(file, "--> Average Values in bits per node per second \n");
							fprintf(file, "Unicast Acks							:	%f\n", 					(double) nb_bits_unicast_ack_total						/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Hellos								:	%f\n", 					(double) nb_bits_hello_total							/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Tc									:	%f\n", 					(double) nb_bits_tc_total								/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 					(double) nb_bits_data_total								/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 				(double) nb_bits_data_retransmission_total				/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 				(double) nb_bits_total);
							fprintf(file, "\n\n");
							
						}
				
				  
				}


			/** state (ENDSIM) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "ENDSIM", "olsr_process () [ENDSIM exit execs]")
				{
				}


			/** state (ENDSIM) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "ENDSIM", "idle")
				/*---------------------------------------------------------*/



			/** state (DATA) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "DATA", "olsr_process () [DATA enter execs]")
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
				//The final destination is random
				dest_final	= op_dist_uniform (nb_nodes-2)+2;
				if (dest_final == my_address)
					dest_final ++;
				
				//Identificaiton of the remote localization process
				network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
				node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB))    );
				process_remote_id	= op_id_from_name ( node_remote_id, OPC_OBJMTYPE_QPS, PROCESS_ID_NAME);
				
				/*------------------------------------------------------------------------------------------	
											  PACKET GENERATION + TRANSMISSION
				-------------------------------------------------------------------------------------------*/	
				
				for(i=0; i < NB_PK_PER_FLOW ; i++)
					op_intrpt_schedule_call(op_sim_time() + i*INTERARRIVAL_DATA_PK , 0 , send_data , dest_final);
				
				
				/*------------------------------------------------------------------------------------------	
															NEXT FLOW
				-------------------------------------------------------------------------------------------*/					
				//I must wake up the next source node
				op_intrpt_schedule_remote(op_sim_time() + op_dist_exponential(INTERARRIVAL_DATA_PK*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE , process_remote_id);
				}


			/** state (DATA) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "DATA", "olsr_process () [DATA exit execs]")
				{
				}


			/** state (DATA) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "DATA", "idle")
				/*---------------------------------------------------------*/



			/** state (FROM_LOWER) enter executives **/
			FSM_STATE_ENTER_FORCED (6, state6_enter_exec, "FROM_LOWER", "olsr_process () [FROM_LOWER enter execs]")
				{
				//Packet Variable
				Packet		*pkptr , *pk_dest;
				int			pk_type;
				
				//Common information in packet
				int			address_src;
				int			address_relay;
				int			address_dest;
				int			address_dest_final;
				int			next_hop;
				int			msg_sequence;
				short		ttl;
				short		hops;
				int			stat_id;
				int			ansn;
				
				//Conditions To handle the packet
				Boolean		is_unicast_for_me;
				Boolean		is_broadcast;
				Boolean		is_ttl_enough;
				Boolean		is_pk_not_seen;
				Boolean		is_bidirect;
				
				//Control
				char		msg[250];
				
				/*------------------------------------------------------------------------------------------	
													   INCOMING PACKET 
				-------------------------------------------------------------------------------------------*/					
				
				pkptr = op_pk_get (op_intrpt_strm ());
				op_pk_nfd_get (pkptr, "PK_TYPE",		&pk_type);
				op_pk_nfd_get (pkptr, "SOURCE", 		&address_src);
				op_pk_nfd_get (pkptr, "RELAY", 			&address_relay);
				op_pk_nfd_get (pkptr, "DEST",	 		&address_dest);
				op_pk_nfd_get (pkptr, "MSG_SEQUENCE", 	&msg_sequence);
				op_pk_nfd_get (pkptr, "TTL", 			&ttl);
				op_pk_nfd_get (pkptr, "HOPS", 			&hops);
				
				
					
				
				/*------------------------------------------------------------------------------------------	
													   CONDITIONS FOR PKS 
				-------------------------------------------------------------------------------------------*/					
				is_unicast_for_me 		=	(address_dest == my_address);
				is_broadcast 			=	((address_dest == BROADCAST) && (address_src != my_address));
				
				is_ttl_enough 			=	(ttl>0);
				is_pk_not_seen 			=	(addr_msg_sequence_not_seen(address_src , msg_sequence));
				
				is_bidirect				=	((is_symetric_neighbor(address_relay)) || (pk_type == HELLO_PK_TYPE));
				
				
				
				//DEBUG
				if (pk_type == DATA_PK_TYPE)
					{
						//sprintf(msg,"In %d   %d -> %d -> %d  (id %d  -  type %d  - mpr_s %d) : %d %d %d %d %d %f\n", my_address , address_src , address_relay , address_dest ,  msg_sequence , pk_type , is_mpr_selector(address_relay) ,is_bidirect , is_broadcast , is_unicast_for_me , is_ttl_enough , is_pk_not_seen , op_sim_time());
						//olsr_test(msg);
					}			  
				
				
				
				
				
				if ( (is_broadcast || is_unicast_for_me) && is_ttl_enough && is_pk_not_seen )
					{
						
						//Search the type of packet
						switch (pk_type)
							{
								//------------------------------------------	
								//			ACKNOWLEDGEMENTS
								//-------------------------------------------
								case UNICAST_ACK_PK_TYPE:
				
								//Registers the packet as seen
										add_address_id_couple(address_src , msg_sequence);
				
										delete_unicast_ack(address_src , msg_sequence);				
									break;
								
								
								
								
									
								//------------------------------------------	
								//			HELLOS
								//-------------------------------------------
								case HELLO_PK_TYPE:
				
										//Registers the packet as seen
										add_address_id_couple(address_src , msg_sequence);
								
										//Neighbor Table
										update_neighbors(pkptr);
										
									break;
										
										
										
										
									
								//------------------------------------------	
								//			TC
								//-------------------------------------------
								case TC_PK_TYPE:
								
										if (is_bidirect)
											{
												//Particular fields of data packets
												op_pk_nfd_get(pkptr , "STAT_ID", 	&stat_id);
				
												//Registers the packet as seen
												add_address_id_couple(address_src , msg_sequence);
								
												//Topology
												update_tc(pkptr);
											
												//Stats
												(stats_tc_pk	[stat_id].nb_receivers) ++ ;
												stats_tc_pk 	[stat_id].time_last_reception	= op_sim_time();
								
												//Forwarding if required
												if ((is_mpr_selector(address_relay)) && (ttl > 1))
													{
														//Stats
														(stats_tc_pk [stat_id].nb_forwarders) ++;
				
														//Forwards the packet
														pk_dest = op_pk_copy(pkptr);
														op_pk_nfd_set(pk_dest , "RELAY",	my_address);
														op_pk_nfd_set(pk_dest , "HOPS", 	++hops);
														op_pk_nfd_set(pk_dest , "TTL", 		--ttl);
												
														pk_send_delayed(pk_dest , op_dist_uniform(0.01) );
											
														if (DEBUG_TC)
															{
																op_pk_nfd_get (pkptr, "ANSN", &ansn);
																sprintf(msg, "I forward a TC packet from %d (tc_id %d) via %d at %f\n", address_src , ansn , address_relay , op_sim_time());
																olsr_debug(msg);
															}
													}
										}
										
									break;
									
										
										
										
										
										
								//------------------------------------------	
								//			DATA
								//-------------------------------------------
								case DATA_PK_TYPE:
								
										//Particular fields of data packets
										op_pk_nfd_get(pkptr , "DEST_FINAL", &address_dest_final);
										op_pk_nfd_get(pkptr , "STAT_ID", 	&stat_id);
				
										//Registers the packet as seen
										add_address_id_couple(address_src , msg_sequence);
				
										//Ack
										if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_DATA) && (!PROMISCUOUS_FOR_UNICAST))
											acknowledges_unicast_packet(address_relay , msg_sequence);
				
										//Adds my id as forwarder
										if (strlen(stats_data_pk [stat_id].route) < 45)
											sprintf(stats_data_pk [stat_id].route, "%s | %d ", stats_data_pk [stat_id].route , my_address);
										
									//FINAL DESTINATION
										if (address_dest_final == my_address)
											{
												//Ack
												if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_DATA) && (PROMISCUOUS_FOR_UNICAST))	
													acknowledges_unicast_packet(address_relay , msg_sequence);
												
												//Stats
												stats_data_pk 	[stat_id].time_reception	= op_sim_time();
												stats_data_pk	[stat_id].dest				= my_address;
												stats_data_pk	[stat_id].pk_size			= (int) op_pk_bulk_size_get(pkptr);
												stats_data_pk	[stat_id].hops				= hops + 1;
												op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stat_id].dest_x_pos));	
												op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stat_id].dest_y_pos));	
												
												//Debug
												if (DEBUG_DATA)
													{
														sprintf(msg,"-------- DATA received by %d from %d at %f (msg_sequence %d and stat_id %d) (nb hops=%d) --------\n" , my_address , address_src , op_sim_time() , msg_sequence , stat_id , MAX_NETWORK_RADIUS - ttl + 1);
														olsr_data(msg);
														sprintf(msg, "DATA - Reception from %d (src_init %d, msg_sequence=%d) at %f\n", address_relay , address_src , stat_id , op_sim_time());
														olsr_debug(msg);
													}
											}
				
									//RELAY
										if ((ttl>1) && (address_dest_final != my_address))
											{
												//Next Relay
												next_hop = get_next_hop_from_routing_table(address_dest_final);
												
												//Info
												op_pk_nfd_set(pkptr, "RELAY", 	my_address);
												op_pk_nfd_set(pkptr, "DEST", 	next_hop);
												op_pk_nfd_set(pkptr, "TTL", 	--ttl);
												op_pk_nfd_set(pkptr, "HOPS", 	++hops);
												
												//was one entry found in the routing table ?
												if (next_hop != -1)
													{
														if (DEBUG_DATA)
															{
																sprintf(msg, "->DATA - %d relays from %d to %d  (src_init %d and toward %d) (msg_sequence %d) at %f\n", my_address , address_relay , next_hop , address_src , address_dest_final , msg_sequence , op_sim_time());
																olsr_data(msg);
															}
											
														//Transmission
														if (ACK_FOR_DATA)
															add_unicast_ack(next_hop , msg_sequence , pkptr);
														pk_send(op_pk_copy(pkptr));
													}
												else if (DEBUG_DATA)
													{
														sprintf(msg,"\n\n-------  DATA-PK : ERROR-RELAY in %d ! data-pk from %d to %d via %d at %f  (msg_sequence %d) -> NO entry in the ROUTING TABLE -> DISCARDED -------\n", my_address , address_src , address_dest_final , address_relay, op_sim_time() , msg_sequence);
														olsr_debug(msg);
														olsr_data(msg);
													}
											}
								
									break;
									
								default :
										sprintf(msg, "PK TYPE = %d", pk_type);
										op_sim_end("pk type not known !! in PK_FROM_LOWER", msg, "","");
									break;
				
							}
					}
					
					
					
					
				//The pk was already trated, we destroy it to free memory
				op_pk_destroy(pkptr);
				}


			/** state (FROM_LOWER) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "FROM_LOWER", "olsr_process () [FROM_LOWER exit execs]")
				{
				}


			/** state (FROM_LOWER) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "FROM_LOWER", "idle")
				/*---------------------------------------------------------*/



			/** state (RET_UNICAST) enter executives **/
			FSM_STATE_ENTER_FORCED (7, state7_enter_exec, "RET_UNICAST", "olsr_process () [RET_UNICAST enter execs]")
				{
				//retransmissions of all not acknowldged entries
					struct_ack*		couple;
					//Control
					char			msg [200];
					int				i;
					double			older_entry;
					//Random delay before transmitting
					double			delay;
					//Info for/from the packet
					Packet*			pk_dest;
					int				address_final;
					int				address_src_init;
					int				stat_id;
					int				pk_type;
					int				msg_sequence;
					int				next_hop;
				
				
					//Older entry variable contains the time for which we must schedule an interuption
					older_entry = -1;
				
				//If the ack table is empty, we don't treat it ....
					if (op_prg_list_size(ack_table)!=0)
						{
							//For each entry
							for (i=op_prg_list_size(ack_table)-1 ; i>=0 ; i--)
								{
									//gets the entry
									couple = (struct_ack*) op_prg_list_access (ack_table, i);
									
									//Get packet type
									op_pk_nfd_get(couple->pkptr, "PK_TYPE", 		&pk_type);
									op_pk_nfd_get(couple->pkptr, "MSG_SEQUENCE", 	&msg_sequence);
									op_pk_nfd_get(couple->pkptr, "DEST_FINAL",		&address_final);
							
									//Verifies each entry
									if (couple->timeout <= op_sim_time())
										{
											//Test for max nb retransmissions
											if (couple->nb_retry >= MAX_NB_RETRIES_UNICAST_ACKS)
												{
													op_prg_list_remove (ack_table , i);
													free(couple);
												}						
											else if (couple->nb_retry < MAX_NB_RETRIES_UNICAST_ACKS)
												{
													op_pk_nfd_get(couple->pkptr, "STAT_ID",&stat_id);
				
													//Stats of nb of retransmissions
													switch (pk_type)
														{
															case DATA_PK_TYPE :
																stats_data_pk [stat_id].nb_retry++;
																if (DEBUG_DATA)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with msg_sequence %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->msg_sequence , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
																		olsr_data (msg);
																	}
															break;
															default:
																op_sim_end("This Packet type is unknown","For the unicast ack retransmission procedure","","");
															break;
														}
															
												
													//retransmission
													couple->timeout = op_sim_time() + TIMEOUT_UNICAST_ACK;
													couple->nb_retry++;	
													delay = op_dist_uniform(0.002);
													pk_retransmit_delayed (op_pk_copy(couple->pkptr) , delay);			
													
													//Next verification for the ack table
													if ((couple->timeout < older_entry) || (older_entry==-1))
														older_entry = couple->timeout;
				
													//DEBUG
													if (DEBUG_CONTROL)
														{
															sprintf(msg, "RETRANSMISSION : we retransmit packet to %d with msg_sequence %d and currently %d retransmissions at %f\n", couple->dest , couple->msg_sequence , couple->nb_retry+1 , op_sim_time()+delay);
															olsr_debug (msg);
														}							
												}
										}
									else if ((couple->timeout < older_entry) || (older_entry==-1))
										older_entry = couple->timeout;
								}
				
				
							//The next verification
							if (older_entry != -1)
								op_intrpt_schedule_self (older_entry , UNICAST_RETRANSMISSIONS_CODE);
						}
				
				
				}


			/** state (RET_UNICAST) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "RET_UNICAST", "olsr_process () [RET_UNICAST exit execs]")
				{
				}


			/** state (RET_UNICAST) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "RET_UNICAST", "idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,olsr_process)
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
olsr_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (olsr_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (olsr_process)",
			sizeof (olsr_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
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
		((olsr_process_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
olsr_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
olsr_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (olsr_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in olsr_process_svar function. */
#undef my_address
#undef DEBUG
#undef current_id
#undef my_stat_id
#undef addr_msg_sequence_list
#undef ack_table
#undef distrib
#undef DEBUG_DATA
#undef ici_list
#undef DEBUG_TOPO
#undef NB_CONNECTIONS
#undef DATA_PK_SIZE
#undef NB_PK_PER_FLOW
#undef INTERARRIVAL_DATA_PK
#undef neighbors_list
#undef two_neighbors_list
#undef mpr_list
#undef mpr_selector_list
#undef links_list
#undef DEBUG_MPR
#undef DEBUG_NEIGHBORHOOD
#undef current_tc_id
#undef DEBUG_TC
#undef topology_list
#undef routing_list
#undef current_data_id
#undef DEBUG_CONTROL
#undef DEBUG_OVERHEAD
#undef is_AP
#undef ACK_FOR_DATA
#undef stats_oh_tc_pk
#undef stats_oh_hello_pk
#undef stats_oh_unicast_ack_pk
#undef stats_oh_data_pk
#undef stats_oh_data_retransmissions_pk
#undef stats_oh_tc_bits
#undef stats_oh_hello_bits
#undef stats_oh_unicast_ack_bits
#undef stats_oh_data_bits
#undef stats_oh_data_retransmissions_bits



void
olsr_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	olsr_process_state		*prs_ptr;

	FIN (olsr_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (olsr_process_state *)gen_ptr;

	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
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
	if (strcmp ("addr_msg_sequence_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->addr_msg_sequence_list);
		FOUT;
		}
	if (strcmp ("ack_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_table);
		FOUT;
		}
	if (strcmp ("distrib" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->distrib);
		FOUT;
		}
	if (strcmp ("DEBUG_DATA" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_DATA);
		FOUT;
		}
	if (strcmp ("ici_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ici_list);
		FOUT;
		}
	if (strcmp ("DEBUG_TOPO" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_TOPO);
		FOUT;
		}
	if (strcmp ("NB_CONNECTIONS" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_CONNECTIONS);
		FOUT;
		}
	if (strcmp ("DATA_PK_SIZE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DATA_PK_SIZE);
		FOUT;
		}
	if (strcmp ("NB_PK_PER_FLOW" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_PK_PER_FLOW);
		FOUT;
		}
	if (strcmp ("INTERARRIVAL_DATA_PK" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->INTERARRIVAL_DATA_PK);
		FOUT;
		}
	if (strcmp ("neighbors_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->neighbors_list);
		FOUT;
		}
	if (strcmp ("two_neighbors_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->two_neighbors_list);
		FOUT;
		}
	if (strcmp ("mpr_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->mpr_list);
		FOUT;
		}
	if (strcmp ("mpr_selector_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->mpr_selector_list);
		FOUT;
		}
	if (strcmp ("links_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->links_list);
		FOUT;
		}
	if (strcmp ("DEBUG_MPR" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_MPR);
		FOUT;
		}
	if (strcmp ("DEBUG_NEIGHBORHOOD" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_NEIGHBORHOOD);
		FOUT;
		}
	if (strcmp ("current_tc_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_tc_id);
		FOUT;
		}
	if (strcmp ("DEBUG_TC" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_TC);
		FOUT;
		}
	if (strcmp ("topology_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->topology_list);
		FOUT;
		}
	if (strcmp ("routing_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->routing_list);
		FOUT;
		}
	if (strcmp ("current_data_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_data_id);
		FOUT;
		}
	if (strcmp ("DEBUG_CONTROL" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_CONTROL);
		FOUT;
		}
	if (strcmp ("DEBUG_OVERHEAD" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_OVERHEAD);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("ACK_FOR_DATA" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ACK_FOR_DATA);
		FOUT;
		}
	if (strcmp ("stats_oh_tc_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_tc_pk);
		FOUT;
		}
	if (strcmp ("stats_oh_hello_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_hello_pk);
		FOUT;
		}
	if (strcmp ("stats_oh_unicast_ack_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_unicast_ack_pk);
		FOUT;
		}
	if (strcmp ("stats_oh_data_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_data_pk);
		FOUT;
		}
	if (strcmp ("stats_oh_data_retransmissions_pk" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_data_retransmissions_pk);
		FOUT;
		}
	if (strcmp ("stats_oh_tc_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_tc_bits);
		FOUT;
		}
	if (strcmp ("stats_oh_hello_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_hello_bits);
		FOUT;
		}
	if (strcmp ("stats_oh_unicast_ack_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_unicast_ack_bits);
		FOUT;
		}
	if (strcmp ("stats_oh_data_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_data_bits);
		FOUT;
		}
	if (strcmp ("stats_oh_data_retransmissions_bits" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_oh_data_retransmissions_bits);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

